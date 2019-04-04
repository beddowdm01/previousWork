/*Author: w16014375*/
/*The spaceship is controlled by the player is used to destroy rocks and aliens by
initialising bullets. collisions with rocks and plasma destroy it. It can translate, rotate
and shoot bullets. If health becomes 0 gets destroyed.*/
/*last edited: 26/12/2018*/

#include "spaceship.h"

Spaceship::Spaceship()
{
	objectActive = false;
}

void Spaceship::initialise(ObjectManager* pObjectManager)//initialises the Spaceship, recieves ObjectManager pointer
{
	velocity.set(0, 0);
	position.set(0, 0);
	angle = 0.0;
	objectActive = true;
	size = 1.0;
	pOM = pObjectManager;//sets object manager pointer = pOM
	LoadImage(L"Spaceship.bmp");

	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	sWidth = pDrawEngine->GetScreenWidth();
	sHeight = pDrawEngine->GetScreenHeight();
	
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	shootSound = pSE->LoadWav(L"shoot.wav");//loads sound for shooting
}

void Spaceship::update(float frameTime)//updates the Spaceship
{
	hitBox.PlaceAt(position, 3);//creates hitbox

	spaceshipX = position.XValue;//gets the Spaceship x pos
	spaceshipY = position.YValue;//gets the Spaceship y pos
	if (spaceshipX > sWidth) {//if the Spaceship goes off screen bring it back on at the opposite side of the screen.
		position.set(float(-sWidth), spaceshipY);
	}
	else if (spaceshipX < -sWidth) {
		position.set(float(sWidth), spaceshipY);
	}
	else if (spaceshipY > sHeight) {
		position.set(spaceshipX, float(-sHeight));
	}
	else if (spaceshipY < -sHeight) {
		position.set(spaceshipX, float(sHeight));
	}

	MyInputs* pInputs = MyInputs::GetInstance();//gets the user input
	pInputs->SampleKeyboard();
	timer = timer - frameTime;//decreases the timer by frametime
	
	if (timer < 0) {//if timer is less than 0 make it = to 0
		timer = 0;
	}
	
	if (pInputs->KeyPressed(DIK_W))//if w is pressed, accelerate ship
	{
		acceleration.setBearing(angle, 150);
		velocity = velocity + acceleration * frameTime;
	}
	
	if (pInputs->KeyPressed(DIK_A))//if a is pressed, turn ship
	{
		angle = angle - 0.03f;
	}

	if (pInputs->KeyPressed(DIK_S))//if s is pressed, reverse ship
	{
		acceleration.setBearing(angle, -50);
		velocity = velocity + acceleration * frameTime;			
	}
	
	if (pInputs->KeyPressed(DIK_D))//if d is pressed, turn ship
	{
		angle = angle + 0.03f;
	}
	
	if (pInputs->KeyPressed(DIK_SPACE) && timer == 0)//if space is pressed play shoot sound and create a Bullet
	{
		Bullet*pBullet = new Bullet();//creates a Bullet
		pBullet->initialise(position, angle);//passed the ship position and angle to Bullet initialise
		pOM->addObject(pBullet);//adds Bullet to object list using manager pointer
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(shootSound);
		timer = delay;
	}
	aTimer = aTimer - frameTime;
	if (aTimer <= 0)//if Alien time has run out, send ship pos
	{
		Message* pMessage = new Message();
		pMessage->initialise(this, "shipPos", position, spaceshipX, spaceshipY);
		pOM->addMessage(pMessage);
		aTimer = 2;
	}
	friction = -0.5 * velocity;//simulates fricition
	velocity = velocity + friction * frameTime;
	position = position + velocity * frameTime;
}

IShape2D* Spaceship::getShape()//gets ship hitbox
{
	return &hitBox;
}

Vector2D Spaceship::getPos()
{
	return position;
}

void Spaceship::processCollision(GameObject* pOthObj)//if ship collides with objects create an Explosion and make Spaceship inactive
{
    std::string objectType = pOthObj->getType();
	if (objectType == "rock")
	{
		Message* pMessage = new Message();
		pMessage->initialise(this, "spaceshipHit", position, 20.0, 100.0);
		pOM->addMessage(pMessage);
	}
	if (objectType == "plasma")
	{
		Message* pMessage = new Message();
		pMessage->initialise(this, "spaceshipHit", position, 20.0, 50.0);
		pOM->addMessage(pMessage);
	}
}


void Spaceship::handleMessage(Message* hMessage)
{
	if (hMessage->getEvent() == "outOfHealth")
	{
			Explosion* pExplosion = new Explosion();//create Explosion
			pExplosion->initialise(position);//initialise Explosion
			pOM->addObject(pExplosion);//add Explosion to object list
			objectActive = false;	
	}

}

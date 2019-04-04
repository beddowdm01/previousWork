/*Author: w16014375*/
/*Has all the functions which the alien object requires.
The alien in game is an enemy that shoots at the player.*/
/*last edited: 26/12/2018*/
#include "alien.h"

Alien::Alien()
{
	objectActive = false;
}
void Alien::Initialise(ObjectManager* pObjectManager)//initialises Alien
{
	velocity.set(4.0f, 0.0f);//sets a velocity for Alien
	position.set(-1700, 500);
	angle = 0.0;
	pOM = pObjectManager;
	objectActive = true;
	size = float(0.2);
	LoadImage(L"heavy.bmp");
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	sWidth = pDrawEngine->GetScreenWidth();
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	shootSound = pSE->LoadWav(L"shoot.wav");//loads sound for shooting
}
void Alien::update(float frameTime)//updates Alien using frametime
{
	hitBox.PlaceAt(position, 20);//gives the Alien a hit box = to 10 at current position
	position = position + velocity;//moves Alien
	float AlienPosX = position.XValue;
	if (AlienPosX > sWidth) {//if the Alien goes off screen bring it back on at the opposite side of the screen.
		objectActive = false;
	}
}

IShape2D* Alien::getShape()//gets the Alien hitbox
{
	return &hitBox;
}
void Alien::processCollision(GameObject* pOthObj)//processes Alien collisons
{
	if (pOthObj->getType() == "Bullet")
	{
		Message* pMessage = new Message();
		pMessage->initialise(this, "addScore", position, 100, 0);//add score Message if player destroys Alien
		pOM->addMessage(pMessage);
		Explosion* pExplosion = new Explosion();//create Explosion
		pExplosion->initialise(position);//initialise Explosion
		pOM->addObject(pExplosion);//add Explosion to object list
		objectActive = false;//makes Rock inactive if it collides with an object

	}
	if (pOthObj->getType() == "rock")
	{
		Explosion* pExplosion = new Explosion();//create Explosion
		pExplosion->initialise(position);//initialise Explosion
		pOM->addObject(pExplosion);//add Explosion to object list
		objectActive = false;//makes Rock inactive if it collides with an object
	}
}
void Alien::handleMessage(Message* pMessage)//processes Alien collisons
{
	if (pMessage->getEvent() == "shipPos")
	{
			float shipPosX = pMessage->getData1();//gets the ship data
			float shipPosY = pMessage->getData2();
			Vector2D shipPos = Vector2D(shipPosX, shipPosY);
			angle = (shipPos - position).angle();//makes the Alien angle = saceship position
			Plasma*pPlasma = new Plasma();//creates a Bullet
			pPlasma->initialise(position, angle);//passed the ship position and angle to Bullet initialise
			pOM->addObject(pPlasma);//adds Bullet to object list using manager pointer
			MySoundEngine* pSE = MySoundEngine::GetInstance();
			pSE->Play(shootSound);
	
	}
}
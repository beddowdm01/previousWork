/*Author: w16014375*/
/*Rocks are collidable objects that can collide with the player, aliens, bullets and plasma.
They will appear at the opposite side of the screen if they go off-screen*/
/*last edited: 26/12/2018*/

#include "rock.h"



Rock::Rock()
{
	objectActive = false;
}
	
void Rock::initialise(ObjectManager* pObjectManager)//initialises Rocks
{
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	sWidth = pDrawEngine->GetScreenWidth();
	sHeight = pDrawEngine->GetScreenHeight();

	velocity.set(float(rand() % 10 - 7), float(rand() % 10 - 7));//sets a random velocity for Rocks
	position.set(float(rand() % (sWidth*2) - sWidth), float(rand() % (sHeight*2) - sHeight));//sets a random position for Rocks
	pOM = pObjectManager;
	angle = 0.0;
	rockHealth = 100;
	objectActive = true;

	size = float(rand()%2-1.5);//sets a random size
	int random = (rand() % 4) + 1;//creates a random number variable

	    
	//sets different Rock images depending on the random variable in order to have a variety of Rocks
	if (random == 1) {
		LoadImage(L"rock1.bmp");
	}
	else if (random == 2) {
		LoadImage(L"rock2.bmp");
	}
	else if (random == 3) {
		LoadImage(L"rock3.bmp");
	}
	else if (random == 4) {
		LoadImage(L"rock4.bmp");
	}
}
void Rock::update(float frameTime)//updates Rock using frametime
{

	hitBox.PlaceAt(position, (50*size));//gives the Rock a hit box = to 40 at current position
	position = position + velocity;//moves Rocks
	rockX = position.XValue;//gets the Rock x pos
	rockY = position.YValue;//gets the Rock y pos
	if (rockX > sWidth) {//if the Rock goes off screen bring it back on at the opposite side of the screen.
		position.set(float(-sWidth), rockY);
	}
	else if (rockX < -sWidth) {
		position.set(float(sWidth), rockY);
	}
	else if (rockY > sHeight) {
		position.set(rockX, float(-sHeight));
	}
	else if (rockY < -sHeight) {
		position.set(rockX, float(sHeight));
	}

}

IShape2D* Rock::getShape()//gets the Rock hitbox
{
	return &hitBox;
}

void Rock::processCollision(GameObject* pOthObj)//processes Rock collisons
{
	if (pOthObj->getType() == "Bullet")
	{
		rockHealth = rockHealth - 50;
		Message* pMessage = new Message();
		pMessage->initialise(this, "addScore", position, 40, 0);
		pOM->addMessage(pMessage);
		if (rockHealth <= 0)
		{
			Message* pMessage = new Message();
			pMessage->initialise(this, "RockDestroyed", position, 40, 0);
			pOM->addMessage(pMessage);
			Explosion* pExplosion = new Explosion();//create Explosion
			pExplosion->initialise(position);//initialise Explosion
			pOM->addObject(pExplosion);//add Explosion to object list
			objectActive = false;//makes Rock inactive if it collides with an object
		}
	}
}
void Rock::handleMessage(Message* hMessage)
{

}


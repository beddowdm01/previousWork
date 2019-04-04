/*Author: w16014375*/
/*Creates bullets and moves the bullets depending on their velocity.
Uses an image file from resources, messages are sent from object on
collision of bullets.*/
/*last edited: 26/12/2018*/
#include "bullet.h"

Bullet::Bullet()
{
	objectActive = false;
}

void Bullet::initialise(Vector2D shipPos, float shipAngle)//initialises, ship position and angle passed
{
	angle = shipAngle;
	position = shipPos;//sets the values in to variables
	
	velocity.setBearing(angle, 10);//sets the bearing for the velocity
	objectActive = true;//makes object active
	size= 6.0;
	LoadImage(L"Bullet.bmp");//loads image
	
}

void Bullet::update(float frameTime)//updates Bullet using frametime
{
	position = position + velocity;
	hitBox.PlaceAt(position, 6);
	bTime = bTime - frameTime;
	if (bTime <= 0)//if Bullet time has run out, make Bullet inactive
	{
		objectActive = false;
	}
}

IShape2D* Bullet::getShape()//gets the hitbox
{
	return &hitBox;
}

void Bullet::processCollision(GameObject* pOthObj)//makes object inactive if collides with object
{
	std::string objectType = pOthObj->getType();
	if (objectType == "rock")
	{
		objectActive = false;
	}
	if (objectType == "Alien")
	{
		objectActive = false;
	}
}


void Bullet::handleMessage(Message* hMessage)
{

}
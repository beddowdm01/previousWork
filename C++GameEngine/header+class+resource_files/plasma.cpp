/*Author: w16014375*/
/*The plasma is fire by the enemy alien class, deals damage to the player if the plasma collides
with the player.*/
/*last edited: 26/12/2018*/
#include "plasma.h"

Plasma::Plasma()
{
	objectActive = false;
}

void Plasma::initialise(Vector2D shipPos, float shipAngle)//initialises, ship position and angle passed
{
	angle = shipAngle;
	position = shipPos;//sets the values in to variables

	velocity.setBearing(angle, 12);//sets the bearing for the velocity
	objectActive = true;//makes object active
	size = 1.0;
	LoadImage(L"Plasma.bmp");//loads image

}

void Plasma::update(float frameTime)//updates Plasma using frametime
{
	position = position + velocity;
	hitBox.PlaceAt(position, 15);
	bTime = bTime - frameTime;
	if (bTime <= 0)//if Plasma time has run out, make Plasma inactive
	{
		objectActive = false;
	}
}

IShape2D* Plasma::getShape()//gets the hitbox
{
	return &hitBox;
}

void Plasma::processCollision(GameObject* pOthObj)//makes object inactive if collides with object
{
	std::string objectType = pOthObj->getType();
	if (objectType == "rock")
	{
		objectActive = false;
	}
	if (objectType == "Spaceship")
	{
		objectActive = false;
	}
}


void Plasma::handleMessage(Message* hMessage)
{

}
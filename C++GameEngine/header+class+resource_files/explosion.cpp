/*Author: w16014375*/
/*Creates an explosion animation using 9 images, explosions are ctreated when other objects are destroyed.*/
/*last edited: 26/12/2018*/
#include "explosion.h"

Explosion::Explosion()
{
	objectActive = false;//starts as inactive
}
void Explosion::initialise(Vector2D objPos)//creates the object and makes it active
{
	position = objPos;
	objectActive = true;
	size = 1;
	LoadImage(L"Explosion1.bmp");
}

void Explosion::update(float frameTime)//updates the Explosion using frametime
{
	if (objectActive == true)//only if object is active
	{
		for (int x = 2; x < 9; x++)//loads images sequentially to animate the Explosion
		{
			timer = timer - frameTime;

			if (timer < 0) {
				timer = 0;
			}
			if (x == 2 && timer == 0)
			{
				LoadImage(L"Explosion2.bmp");
				timer = 0.5;
			}
			if (x == 3 && timer == 0)
			{
				LoadImage(L"Explosion3.bmp");
				timer = 0.5;
			}
			if (x == 4 && timer == 0)
			{
				LoadImage(L"Explosion4.bmp");
				timer = 0.5;
			}
			if (x == 5 && timer == 0)
			{
				LoadImage(L"Explosion5.bmp");
				timer = 0.5;
			}
			if (x == 6 && timer == 0)
			{
				LoadImage(L"Explosion6.bmp");
				timer = 0.5;
			}
			if (x == 7 && timer == 0)
			{
				LoadImage(L"Explosion7.bmp");
				timer = 0.5;
			}
			if (x == 8 && timer == 0)
			{
				LoadImage(L"Explosion8.bmp");
				timer = 0.5;
				objectActive = false;
			}
		}
	}
}
IShape2D* Explosion::getShape()//gets the hitbox for the Explosion
{
	return &hitBox;
}

void Explosion::processCollision(GameObject* pOthObj)
{

}


void Explosion::handleMessage(Message* hMessage)
{

}
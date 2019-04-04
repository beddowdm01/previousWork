/*Author: w16014375*/
/*hud which displays information to the user such as score and health.
calculates the current hud scores depending on messages received from other objects.*/
/*last edited: 26/12/2018*/

#include "hud.h"


Hud::Hud()
{
	objectActive = false;
}

void Hud::initialise(ObjectManager* pObjectManager)
{
	currentHealth = 100;
	currentScore = 0;
	objectActive = true;
	pOM = pObjectManager;
	LoadImage(L"Spaceship.bmp");
	size = 0;
	destroyedRocks = 0;
}

void Hud::update(float frameTime)//updates Rock using frametime
{
	MyDrawEngine::GetInstance()->WriteInt(100, 0, currentScore, MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(100, 100, currentHealth, MyDrawEngine::WHITE);
}

void Hud::handleMessage(Message* hMessage)
{
	if (hMessage->getEvent() == "addScore")//adds score to the player score
	{

		currentScore = currentScore + int(hMessage->getData1());
	}
	if (hMessage->getEvent() == "spaceshipHit")//removes score and damages the player
	{
		currentScore = currentScore - int(hMessage->getData1());
		currentHealth = currentHealth - int(hMessage->getData2());
		
		if (currentHealth <= 0)//if the player runs out of health send a message
		{
			currentHealth = 0;
			Message* pMessage = new Message();
			pMessage->initialise(this, "outOfHealth", position, 0, 0);
			pOM->addMessage(pMessage);
		}
	}
	if (hMessage->getEvent() == "RockDestroyed")//tracks how many rocks have been destroyed
	{
		destroyedRocks += 1;
		if (destroyedRocks == 2) {
			Alien* pAlien = new Alien();//create Explosion
			pAlien->Initialise(pOM);//initialise Explosion
			pOM->addObject(pAlien);//add Explosion to object list
			pOM->canReceiveMessages(pAlien);
		}
		if (destroyedRocks == 8) {
			for (int i = 0; i < 8; i++) 
			{
				Rock*temp2 = new Rock();
				temp2->initialise(pOM);
				pOM->addObject(temp2);
				pOM->canReceiveMessages(temp2);
				destroyedRocks = 0;
			}
		}
	}
}


void Hud::processCollision(GameObject* pOthObj)//processes Rock collisons
{

}

IShape2D* Hud::getShape()//gets the Rock hitbox
{
	return &hitBox;
}

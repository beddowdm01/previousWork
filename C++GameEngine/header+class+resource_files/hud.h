/*Author: w16014375*/
/*This is the hud header file, it inherits from the gameobject class and
has all the functions and variables for the hud which shows information to
the user on screen whilst also storing data such a s score and health*/
/*last edited: 22/12/2018*/
#pragma once
#include "objectManager.h"
#include "alien.h"
#include "rock.h"

class Hud : public GameObject
{
private:
	int currentScore;//player score
	Circle2D hitBox;//hitbox
	int currentHealth;//player health
	int destroyedRocks;//amount of destroyed rocks
	ObjectManager* pOM;//pointer to object manager
	Message* pM;//pointer to message class
public:
	Hud();
	void initialise(ObjectManager* pObjectManager);
	void handleMessage(Message* pMessage);
	void update(float timeFrame);
	void processCollision(GameObject* pOthObj);
	IShape2D* getShape();
};

/*Author: w16014375*/
/*This is the alien header file, it inherits from the gameobject class and 
has all the functions and variables for the Alien which is an enemy in the game.*/
/*last edited: 22/12/2018*/
#pragma once
#include "gameObject.h"
#include "objectManager.h"
#include "mysoundengine.h"
#include "plasma.h"
#include "explosion.h"

class Alien : public GameObject
{
private:
	Vector2D velocity;//variables for the alien
	Vector2D shipPos;
	Circle2D hitBox;
	double shootDelay = 2;
	int alienHealth = 100;
	float bearing;
	SoundIndex shootSound;
	int sWidth;
	ObjectManager* pOM;//pointer to object manager
public:
	//public Rock functions
	Alien();
	void Initialise(ObjectManager* pObjectManager);
	void update(float timeFrame);
	IShape2D* getShape();
	void processCollision(GameObject* pOthObj);
	void handleMessage(Message* pMessage);
	virtual std::string getType()
	{
		return "Alien";
	};
};


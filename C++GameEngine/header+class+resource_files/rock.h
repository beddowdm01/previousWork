/*Author: w16014375*/
/*This is the rock header file, it inherits from the gameobject class and
has all the functions and variables for the rock which is an object in game
which the player can collide with and also shoot to gain score points.*/
/*last edited: 22/12/2018*/
#pragma once
#include "objectManager.h"
#include "explosion.h"

class Rock : public GameObject
{
private:
	//private variables for Rocks
	Vector2D velocity;
	Circle2D hitBox;
	float rockX;
	float rockY;
	int sHeight;
	int sWidth;
	int rockHealth;
	ObjectManager* pOM;//pointer to object manager
public:
	//public Rock functions
	Rock();
	void initialise(ObjectManager* pObjectManager);
	void update(float timeFrame);
	IShape2D* getShape();
	void processCollision(GameObject* pOthObj);
	void handleMessage(Message* pMessage);
	virtual std::string getType()
	{
		return "rock";
	};

};


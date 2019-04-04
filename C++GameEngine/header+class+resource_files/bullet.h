/*Author: w16014375*/
/*This is the bullet header file, it inherits from the gameobject class and
has all the functions and variables for the bullet which is an object fired from 
the spaceship and deals damage to other objects*/
/*last edited: 22/12/2018*/
#pragma once
#include "gameObject.h"

class Bullet : public GameObject
{
private:
	//private Bullet variables
	Vector2D velocity;
	float bTime = 2.0;//how long the Bullets are active for
	Circle2D hitBox;
public:
	//public functions
	Bullet();
	void initialise(Vector2D shipPos, float shipAngle);
	void update(float frameTime);
	IShape2D* getShape();
	void processCollision(GameObject* pOthObj);
	void handleMessage(Message* pMessage);
	virtual std::string getType()
	{
		return "Bullet";
	};
};
/*Author: w16014375*/
/*This is the explosion header file, it inherits from the gameobject class and
has all the functions and variables for the explosion which is created by other classes
to display explosions on screen.
and is.*/
/*last edited: 22/12/2018*/
#pragma once
#include "gameObject.h"

class Explosion : public GameObject
{
private:
	//hitbox for the Explosion
	Circle2D hitBox;
public:
	//public functions for Explosion
	Explosion();
	void initialise(Vector2D shipPos);
	void update(float frameTime);
	float timer;
	IShape2D* getShape();
	void processCollision(GameObject* pOthObj);
	void handleMessage(Message* pMessage);
	virtual std::string getType()
	{
		return "Explosion";
	};
};
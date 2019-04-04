/*Author: w16014375*/
/*This is the plasma header file, it inherits from the gameobject class and
has all the functions and variables for the plasma which are projectiles shot by
the alien class.*/
/*last edited: 22/12/2018*/
#pragma once
#include "gameObject.h"

class Plasma : public GameObject
{
private:
	//private Plasma variables
	Vector2D velocity;
	float bTime = 3.0;//how long the Plasma is active for
	Circle2D hitBox;
public:
	//public functions
	Plasma();
	void initialise(Vector2D shipPos, float shipAngle);
	void update(float frameTime);
	IShape2D* getShape();
	void processCollision(GameObject* pOthObj);
	void handleMessage(Message* pMessage);
	virtual std::string getType()
	{
		return "plasma";
	};
};

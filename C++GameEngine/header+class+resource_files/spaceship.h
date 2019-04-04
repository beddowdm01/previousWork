/*Author: w16014375*/
/*This is the spaceship header file, it inherits from the gameobject class and
has all the functions and variables for the spaceship which is the object the player
controls during gameplay. It can shoot, move and rotate as well as shoot bullets, 
which are created by the bullet class.*/
/*last edited: 22/12/2018*/
#pragma once
#include "bullet.h"
#include "objectManager.h"
#include "explosion.h"
#include "myinputs.h"


class Spaceship: public GameObject
{
private:
	//private variables for Spaceship
	Vector2D velocity;
	Vector2D friction;
	Vector2D acceleration;
	SoundIndex shootSound;
	float spaceshipX;
	float spaceshipY;
	int sHeight;
	int sWidth;
	double timer = 0;//timer for shooting delay
	double delay = 0.5;//delay for shooting
	double aTimer = 2;
	ObjectManager* pOM;//pointer to object manager
	Circle2D hitBox;//hitbox of ship
public:
	//public Spaceship functions
	Spaceship();
	void initialise(ObjectManager* pObjectManager);
	void update(float timeFrame);
	IShape2D* getShape();
	Vector2D getPos();
	void processCollision(GameObject* pOthObj);
	void handleMessage(Message* pMessage);
	virtual std::string getType()
	{
		return "Spaceship";
	};
};


/*Author: w16014375*/
/*This is the message header file, it inherits from the gameobject class and
has all the functions and variables for messages which are used by other classes
to pass messages from one to another.*/
/*last edited: 22/12/2018*/
#pragma once
#include "objectManager.h"
#include <string>
class GameObject;

class Message
{
private:
	GameObject* from;//what object the message is from
	std::string type;//the type of message
	Vector2D pos;//the pos of the object
	float data1;//variables to store data
	float data2;
public:
	Message();
	void initialise( GameObject* from, std::string type, Vector2D pos, float data1, float data2);

	std::string getEvent()
	{
		return type;//returns the message type
	};
	Vector2D getPos()
	{
		return pos;//returns the pos stored in the message
	};
	float getData1()
	{
		return data1;//returns some data stored in the message
	};
	float getData2()
	{
		return data2;//returns some more data stored in the message
	};
};

/*Author: w16014375*/
/*This is the game object header that all game objects such as rocks will inherit from
it has variables and functions that all game objects will use. */
/*last edited: 22/12/2018*/
#pragma once
#include "Shapes.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include <string>
class Message;


class GameObject 
{
protected:
	//protected GameObject variables for inherited classes to use
	Vector2D position;
	float angle;
	PictureIndex image;
	bool objectActive;
	float size;
	void LoadImage(wchar_t* filename);
public:
	//public gameObject methods
	GameObject();
	virtual ~GameObject();
	bool oActive();
	Vector2D oPosition();
	virtual void Render();//renders object
	virtual void processPosition(Vector2D oPosition);//processes its position
	virtual IShape2D* getShape()=0;//pure virtual function for other objects to overwrite
	virtual void processCollision(GameObject* pOthObj)=0;//pure virtual function for other objects to overwrite
	virtual void handleMessage(Message* pMessage) = 0;//pure virtual function for other objects to overwrite
	virtual void update(float frameTime)=0;//pure virtual function for other objects to overwrite
	virtual std::string getType()//returns object type
	{
		return "GameObject";
	};
};
/*Author: w16014375*/
/*This is the objectmanager header file which is used to handle all objects in the game.
It updates deletes and checks for collisions, it is also the class which handles the sending
of messages from every other class.*/
/*last edited: 22/12/2018*/
#pragma once
#include "gameObject.h"
#include "gametimer.h"
#include "message.h"
#include <list>

class ObjectManager
{
	private:
		std::list<GameObject*>recMessages;//list of objects that can receive Messages
		std::list<GameObject*>pObjects;//list of pointers to GameObjects
		std::list<Message*>pMessages;//list of pointers to Messages
		GameTimer theTimer;//Timer for the game
		int oX;
		int oY;
		std::string obj1;
		double frameTime;//used for timing/updating
	public://functions to manage objects
		ObjectManager();
		void addObject(GameObject* pNewObject);
		void updateAll();//updates all objects
		void renderAll();//renders all objects
		void canReceiveMessages(GameObject* pNewObject);//adds objects to a list that can receive messages
		void clearMessages();//clears messages
		void deleteAll();//deletes all objects
		void deleteInactive();//deletes inactive objects
		void checkAllCollisions();//checks for collisions
		void addMessage(Message* pNewMessage);//adds a message to the list
		void dispatchMessages();//sends all messages
};
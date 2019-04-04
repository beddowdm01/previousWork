/*Author: w16014375*/
/*This is the objectmanager.cpp it handles the objects of the game by storing in a list and by 
updating checking for collisions, sending and storing messages as well as deleting
inactive objects and messages. Also deletes objects at the end of the game*/
/*last edited: 22/12/2018*/

#include "gameObject.h"
#include "objectManager.h"
#include <algorithm>

ObjectManager::ObjectManager()
{

}

void ObjectManager::addObject(GameObject* pNewObject)
{
	pObjects.push_back(pNewObject);
}

void ObjectManager::updateAll()//updates objects
{
	MyDrawEngine::GetInstance()->WriteText(0, 0, L"Score:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteText(0, 100, L"Health:", MyDrawEngine::WHITE);//displays score and health
	theTimer.mark();
	frameTime = theTimer.mdFrameTime;//sets the frameTime value
	for (GameObject* pNObject : pObjects)//for every object pointer in the list
	{
		pNObject->update(float(frameTime));//runs the objects update function
	}
	checkAllCollisions();//checks if any objects are colliding
	dispatchMessages();//sends all Messages to objects that can receive them
	clearMessages();//clears all Messages that have been sent
	deleteInactive();//deletes objects that are inactive
}

void ObjectManager::clearMessages()//deletes all Messages and sets pointers to null
{
	for (Message* &nextMessagePointer : pMessages)//loops through all Messages
	{
		delete nextMessagePointer;
		nextMessagePointer = nullptr;//sets them to nullpointer
	}

	auto iter = std::remove(pMessages.begin(), pMessages.end(), nullptr);
	pMessages.erase(iter, pMessages.end());//removes all nullptrs from the list
}

void ObjectManager::renderAll()//renders each object
{
	for (GameObject* pNObject : pObjects)
	{
		pNObject->Render();
	}
}

void ObjectManager::canReceiveMessages(GameObject* pNewObject)
{
	recMessages.push_back(pNewObject);
}

void ObjectManager::deleteAll()//deletes all objects and sets pointers to null
{
	for (GameObject* &nextObjectPointer : pObjects)
	{
			delete nextObjectPointer;
			auto iter = std::remove(recMessages.begin(), recMessages.end(), nextObjectPointer);
			recMessages.erase(iter, recMessages.end());
			nextObjectPointer = nullptr;
	}
	auto iter = std::remove(pObjects.begin(), pObjects.end(), nullptr);
	pObjects.erase(iter, pObjects.end());
}

void ObjectManager::deleteInactive()// deletes any inactive objects
{
	for (GameObject* &nextObjectPointer : pObjects)
	{
		if (nextObjectPointer->GameObject::oActive() == false)
		{
			delete nextObjectPointer;
			auto iter = std::remove(recMessages.begin(), recMessages.end(), nextObjectPointer);
			recMessages.erase(iter, recMessages.end());
			nextObjectPointer = nullptr;
		}
	}

	auto iter = std::remove(pObjects.begin(), pObjects.end(), nullptr);
	pObjects.erase(iter, pObjects.end());	

}

void ObjectManager::checkAllCollisions()//checks for collisions
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	for (it1 = pObjects.begin(); it1 != pObjects.end(); it1++)
	{
		for (it2 = std::next(it1); it2 != pObjects.end(); it2++)
		{
			if ((*it1)->getShape()->Intersects(*((*it2)->getShape())))//gets the object shapes for both iterators and checks intersection
			{
				(*it1)->processCollision(*it2);//if collides process the collision for each object
				(*it2)->processCollision(*it1);
			}
				
		}
	}
}
void ObjectManager::addMessage(Message* pNewMessage)
{
	pMessages.push_back(pNewMessage);
}

void ObjectManager::dispatchMessages()
{
	for (Message* pNMessage : pMessages)//for every Message pointer in the list
	{
		for (GameObject* pNObject : recMessages)
		{
			pNObject->handleMessage(pNMessage);//runs the handle function
		}
	}
}

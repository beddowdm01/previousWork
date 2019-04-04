/*Author: w16014375*/
/*Inherited by other classes. Has functions and variables that game objects will reuire
which includes loading the images and rendering the object*/
/*last edited: 26/12/2018*/

#include "shapes.h"
#include "mydrawengine.h"
#include "gamecode.h"
#include "gameObject.h"

GameObject::GameObject() 
{
	objectActive = false;
}
GameObject::~GameObject()
{

}

void GameObject::LoadImage(wchar_t* filename)//loads the image for the object
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(filename);
}

void GameObject::Render()//renders the game object
{
	if (objectActive == true)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, size, angle);
	}

}

void GameObject::processPosition(Vector2D oPosition) //processes position of the object
{
		
}

bool GameObject::oActive()//returns if the object is active
{
	return objectActive;
}

Vector2D GameObject::oPosition()//returns the object position
{
	return position;
}

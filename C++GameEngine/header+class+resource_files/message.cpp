/*Author: w16014375*/
/*Messages are uses to send information to other objects,
these objects can then react differently depending on the message infomration received.*/
/*last edited: 26/12/2018*/
#include "message.h"

Message::Message()
{

}

void Message::initialise(GameObject* from, std::string type, Vector2D pos, float data1, float data2)
{
	this->from = from;//makes all the passed variables = to the variables of the message
	this->type = type;
	this->pos = pos;
	this->data1 = data1;
	this->data2 = data2;
}


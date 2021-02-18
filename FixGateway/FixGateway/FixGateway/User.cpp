#include "User.h"

void FixGateway::User::setID(const std::string& id)
{
	_id = id;
}

const std::string& FixGateway::User::getID()
{
	return _id;
}

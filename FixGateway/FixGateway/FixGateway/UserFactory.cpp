#include "UserFactory.h"

using namespace FixGateway;

UserFactory* UserFactory::s_instance = 0;

User* UserFactory::newUser()
{
	return new User();
}

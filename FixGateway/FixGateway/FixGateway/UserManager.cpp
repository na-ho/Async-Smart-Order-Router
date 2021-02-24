#include <fmt/format.h>

#include "UserManager.h"

using namespace FixGateway;

bool UserManager::checkAuthorization(const std::string& userName, const std::string& password)
{
    // TODO: implement user system


    return true;
}

void UserManager::insertUser(std::string userID, User* user)
{
    _users.insert(std::move(userID), user);
}

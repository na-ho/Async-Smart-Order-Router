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
    _mpUser.insert(std::move(userID), user);
    //fmt::print("user size: {}\n", _mpUser.size());
}

#pragma once

#include <string>
#include <cuckoohash_map.hh>

#include "User.h"

class UserManager
{
public:
	bool checkAuthorization(const std::string &userName, const std::string &password);
	
private:
	libcuckoo::cuckoohash_map<std::string, User*> _mpUser;
};

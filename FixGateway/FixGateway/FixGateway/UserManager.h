#pragma once

#include <string>
#include <cuckoohash_map.hh>

#include "User.h"

namespace FixGateway
{
	class UserManager
	{
	public:
		bool checkAuthorization(const std::string& userName, const std::string& password);

		void insertUser(std::string userID, User* user);
	private:
		libcuckoo::cuckoohash_map<std::string, User*> _mpUser;
	};

}
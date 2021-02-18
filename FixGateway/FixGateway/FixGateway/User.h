#pragma once

#include <string>

namespace FixGateway
{
	class User
	{
	public:
		void setID(const std::string &id);
		const std::string& getID();

	private:
		std::string _id;

	};
}
#include "OrderManager.h"


SOR::OrderManager* SOR::OrderManager::s_instance = 0;

void SOR::OrderManager::addNewOrder(std::string user_id, std::string client_order_id, std::string symbol, std::string server_id
	, int side, int preferred_venue_id, float price, float qty)
{
	User* user = NULL;
	if (!_users.find(user_id, user))
	{
		user = new User();
		user->set(std::move(user_id), std::move(server_id));
	}
	else {
		user->checkSet_server_id(std::move(server_id));
	}

	user->addOrder(std::move(client_order_id), std::move(symbol), preferred_venue_id, side, price, qty);
}

#include "User.h"

void SOR::User::set(std::string user_id, std::string server_id)
{
	_user_id = std::move(user_id);
	_server_id = std::move(server_id);
}

void SOR::User::checkSet_server_id(std::string server_id)
{
	if (_server_id != server_id) {
		_server_id = server_id;
	}
}

void SOR::User::addOrder(std::string client_order_id, std::string symbol, int preferred_venue_id, int side, float price, float qty)
{
	// TODO: user memory pool
	Order* order = new Order();
	_orders.insert(client_order_id, order);
	order->set(this, std::move(client_order_id), std::move(symbol), preferred_venue_id, side, price, qty);
	
	// calculate route order
	order->caculate_send_route();
}

#include <fmt/format.h>

#include "libs/hffix/hffix.hpp"
#include "libs/sole.hpp"
#include "libs/fast_float/fast_float.h"

#include "Server.h"
#include "Session.h"
#include "FixGatewayData.h"
#include "UserFactory.h"

#include "schemas/order_fixg_sor_generated.h"

using boost::asio::ip::tcp;

using namespace FixGateway;

Server::Server(boost::asio::io_context& io_context, short port)
	: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	_userMgr = FixGatewayData::instance()->getUserMgr();
	_msgBus = FixGatewayData::instance()->getMsgBus();
	_server_id = FixGatewayData::instance()->getServer_id();

	initFixLogon();
	initFixOrder();

	do_accept();
}

FixGateway::Server::~Server()
{

}

void Server::do_accept()
{
	_acceptor.async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
		{
			if (!ec)
			{
				socket.set_option(boost::asio::ip::tcp::no_delay(true));
				std::shared_ptr<Session> session = std::make_shared<Session>(std::move(socket), &_fixMsgLambda);
				session->start();
			}

			do_accept();
		});
}

void Server::initFixLogon()
{
	_fixMsgLambda.emplace("A", [this](hffix::message_reader* reader, Session* session) {
		fmt::print("login\n");
		hffix::message_reader::const_iterator i = reader->begin();
		if (reader->find_with_hint(hffix::tag::SenderCompID, i)) {
			auto userId = i++->value().as_string();
			fmt::print("userId : {}\n", userId);
			if (reader->find_with_hint(hffix::tag::RawData, i)) {
				auto password = i++->value().as_string();
				if (_userMgr->checkAuthorization(userId, password)) {
					// insert into map
					auto user = UserFactory::instance()->newUser();
					user->setID(userId);
					session->setUser(user);
					_userMgr->insertUser(std::move(userId), user);
					session->write_fix_login(userId, "A", "Login succeed");
				}
				else {
					session->write_fix_login(userId, "5", "Password invalid");
				}
			}
			else {
				// cannot find password
				session->write_fix_login(userId, "5", "Cannot find password");
			}
		}
	});


}

void Server::initFixOrder()
{
	_fixMsgLambda.emplace("D", [this](hffix::message_reader* reader, Session* session) {
		fmt::print("order\n");
		hffix::message_reader::const_iterator i = reader->begin();
		if (reader->find_with_hint(hffix::tag::ClOrdID, i)) {
			std::string client_order_id(i->value().begin(), i->value().end());
			fmt::print("ClOrdID : {}\n", client_order_id);
			i++;
			if (reader->find_with_hint(hffix::tag::Side, i)) {
				auto side = i->value().as_int<int>();
				fmt::print("Side : {}\n", side);
				i++;
				if (reader->find_with_hint(hffix::tag::Symbol, i)) {
					std::string symbol(i->value().begin(), i->value().end());
					fmt::print("symbol : {}\n", side);
					i++;
					if (reader->find_with_hint(hffix::tag::OrderQty, i)) {
						float qty = 0.0f;
						fast_float::from_chars(i->value().begin(), i->value().end(), qty);
						fmt::print("qty : {}\n", qty);
						i++;
						if (reader->find_with_hint(hffix::tag::Price, i)) {
							float price = 0.0f;
							fast_float::from_chars(i->value().begin(), i->value().end(), price);
							fmt::print("price : {}\n", price);

							flatbuffers::FlatBufferBuilder builder;
							auto order_user_id = builder.CreateString(session->getUser()->getID());
							auto order_server_id = builder.CreateString(_server_id);
							auto order_client_order_id = builder.CreateString(client_order_id);
							auto order_symbol = builder.CreateString(symbol);
							auto order_serializaition = MsgSerialization::CreateOrder_FIXG_SOR(builder, order_user_id, order_server_id, 1
								, order_client_order_id, order_symbol, side, price, qty);
							builder.Finish(order_serializaition);

							_msgBus->publish(MSGBUS_FIXG_SOR_ORDER, (const char*)builder.GetBufferPointer(), builder.GetSize());

						}
					}
				}
			}
			
			
		}
	});
}

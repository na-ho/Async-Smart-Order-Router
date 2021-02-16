#include <memory>
#include <fmt/format.h>

#include "libs/hffix/hffix.hpp"
#include "FixGateway.h"
#include "libs/sole.hpp"

#include "Server.h"
#include "Session.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
    do_accept();
}

void Server::do_accept()
{

    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            //   boost::uuids::uuid uuid = boost::uuids::random_generator()();
       //        std::cout << uuid << std::endl;
             //  sole::uuid u0 = sole::uuid0(), u1 = sole::uuid1(), u4 = sole::uuid4();



            //   fmt::print("Peer IP: {}, {}\n", socket.remote_endpoint().address().to_string(), socket.remote_endpoint().port());
           //    auto source = fmt::format("{}{}", socket.remote_endpoint().address().to_string(), socket.remote_endpoint().port());
           //    sole::uuid u4 = sole::rebuild(source);
            auto u4 = sole::uuid4();
            //   boost::multiprecision::uint128_t combined = u4.ab << 64 | u4.cd;
            //   boost::multiprecision::uint128_t  test;
            //   fmt::print("do_accept {}\n", u4.base62());
            fmt::print("do_accept {}, {}\n", u4.ab, u4.cd);
            //   fmt::print("do_accept {}\n", combined);
            fmt::print("do_accept {}, {}\n", socket.remote_endpoint().data()->sa_family, socket.remote_endpoint().port());

            if (!ec)
            {
                socket.set_option(boost::asio::ip::tcp::no_delay(true));
                std::make_shared<Session>(std::move(socket))->start();
            }

            do_accept();
        });
}

void Server::initFixLogon()
{
    auto lambda1 = [](hffix::message_reader &reader) { return i; };
    auto lambda2 = [](std::string s) { return s; };


    mpFixMsgLambda["A"] = lambda1;
    mpFixMsgLambda["second"] = lambda2;


}

#include <memory>
#include <fmt/format.h>

#include "libs/hffix/hffix.hpp"
#include "FixGateway.h"
#include "libs/sole.hpp"

#include "Server.h"
#include "Session.h"

#include <boost/any.hpp>

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, short port)
    : _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
    initFixLogon();
    do_accept();
}

void Server::do_accept()
{

    _acceptor.async_accept(
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
                std::shared_ptr<Session> session = std::make_shared<Session>(std::move(socket), &_mpFixMsgLambda);
                session->start();
            }

            do_accept();
        });
}

void Server::initFixLogon()
{
    auto lambdaFixA = []( hffix::message_reader *reader, Session *session) { 
        fmt::print("login\n");
        hffix::message_reader::const_iterator i = reader->begin();
        if (reader->find_with_hint(hffix::tag::SenderCompID, i)) {
            auto userId = i++->value().as_string();
            fmt::print("userId : {}\n", userId);
            if (reader->find_with_hint(hffix::tag::RawData, i)) {
                auto password = i++->value().as_string();
               // if (session->_userMgr->checkAuthorization(userId, password)) {
                if(true){
                    // insert into map
                }
                else {
                    session->write_fix_login(userId, "Password invalid");
                }
            }
            else {
                // cannot find password
                session->write_fix_login(userId, "Cannot find password");
            }
        }
    };
  //  auto lambda2 = [](std::string s) { return s; };


    //_mpFixMsgLambda["A"] = lambdaFixA;
  //  mpFixMsgLambda["second"] = lambda2;

  //  auto lambda1 = [](int i) { std::cout << "test : " << i << std::endl; };

    //std::map < std::string, std::function < void(hffix::message_reader*, Session*) >> map1;
    _mpFixMsgLambda.emplace("A", lambdaFixA);

}

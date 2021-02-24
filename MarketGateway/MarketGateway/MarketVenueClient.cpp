#include "libs/hffix/hffix.hpp"

#include "MarketVenueClient.h"

MarketGateway::MarketVenueClient::MarketVenueClient(boost::asio::io_context& io_context)
    :_io_context(io_context),
    _socket(io_context)
{
}

HASHMAP_LAMBDA_MSG_FIX* MarketGateway::MarketVenueClient::getFixMsgLambda()
{
    return &_fixMsgLambda;
}

void MarketGateway::MarketVenueClient::connect(const std::string& ip, const std::string& port)
{
    boost::asio::ip::tcp::resolver resolver(_io_context);
    auto endpoints = resolver.resolve(ip, port);
    do_connect(endpoints);
}

void MarketGateway::MarketVenueClient::do_connect(boost::asio::ip::tcp::resolver::results_type& endpoints)
{
    boost::asio::async_connect(_socket, endpoints,
        [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint)
        {
            if (!ec)
            {
                do_read();
            }
        });
}


void MarketGateway::MarketVenueClient::do_read()
{
     buffer_read_length = 0;
    _socket.async_read_some(boost::asio::buffer(_buffer, chunksize),
        [this](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                buffer_read_length += length;
                hffix::message_reader reader(_buffer, length);

                for (; reader.is_complete(); reader = reader.next_message_reader()) {
                    if (reader.is_valid()) {
                        auto msgType = reader.message_type()->value().as_string();
                        auto handleFunctionIt = _fixMsgLambda.find(msgType);
                        if (handleFunctionIt != _fixMsgLambda.end()) {
                            handleFunctionIt->second(&reader, this);
                        }
                    }
                }
                buffer_read_length = reader.buffer_end() - reader.buffer_begin();
                if (buffer_read_length > 0) {
                    std::memmove(_buffer, reader.buffer_begin(), buffer_read_length);
                }
            }

            do_read();
        });

}

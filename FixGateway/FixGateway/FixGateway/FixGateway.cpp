// FixGateway.cpp : Defines the entry point for the application.
//


#include <fmt/format.h>

//#include <boost/uuid/uuid.hpp>
//#include <boost/uuid/uuid_generators.hpp>
//#include <boost/uuid/uuid_io.hpp>

#include "Server.h"
#include "FixGatewayData.h"

using namespace std;


int main()
{
    auto fixGatewayData = FixGatewayData::instance(); // warmup
    fmt::print("Start listening...\n");
    try
    {
        boost::asio::io_context io_context;

        Server s(io_context, 1234);

        io_context.run();
    }
    catch (std::exception& e)
    {
        fmt::print("Exception: {}\n", e.what());
    }


	return 0;
}

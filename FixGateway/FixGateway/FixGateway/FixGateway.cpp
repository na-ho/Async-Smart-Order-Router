#include <fmt/format.h>

#include "Server.h"
#include "FixGatewayData.h"
#include "UserFactory.h"

using namespace std;

void warmUp() {
    FixGateway::FixGatewayData::warmUp();
    FixGateway::UserFactory::warmUp();
}

int main()
{
    // temp for testing, in production has to be set from external
    const std::string server_id = "1";

    warmUp();
    FixGateway::FixGatewayData::instance()->setServer_id(server_id);
    FixGateway::FixGatewayData::instance()->init();

    fmt::print("Start listening...\n");
    try
    {
        boost::asio::io_context io_context;

        FixGateway::Server s(io_context, 1234);

        io_context.run();
    }
    catch (std::exception& e)
    {
        fmt::print("Exception: {}\n", e.what());
    }


	return 0;
}

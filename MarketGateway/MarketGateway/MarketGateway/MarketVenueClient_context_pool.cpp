
#include "MarketVenueClient_context_pool.h"


MarketGateway::MarketVenueClient_context_pool::MarketVenueClient_context_pool(std::size_t pool_size)
{
    if (pool_size == 0)
        throw std::runtime_error("io_context_pool size is 0");

    for (auto i = 0; i < pool_size; ++i)
    {
        _io_contexts.push_back(new boost::asio::io_context);
    }
}

void MarketGateway::MarketVenueClient_context_pool::run()
{
    _threads.clear();
    for (auto io_context : _io_contexts) {
        auto member_function = static_cast<boost::asio::io_context::count_type(boost::asio::io_context::*)()>(&boost::asio::io_context::run);
        _threads.emplace_back(std::thread(member_function, io_context));
    }

    for (auto& th : _threads) {
        th.join();
    }
}

void MarketGateway::MarketVenueClient_context_pool::stop()
{
    for (auto io_context : _io_contexts) {
        io_context->stop();
    }
}

MarketGateway::MarketVenueClient_context_pool::type_io_contexts* MarketGateway::MarketVenueClient_context_pool::get_io_contexts()
{
    return &_io_contexts;
}

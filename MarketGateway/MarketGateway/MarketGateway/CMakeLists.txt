cmake_minimum_required (VERSION 3.8)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

include_directories("./libs/libcuckoo")

find_package(fmt)
find_package(Boost REQUIRED COMPONENTS date_time)
find_package(cnats)
find_package(Flatbuffers)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${FLATBUFFERS_INCLUDE_DIR})

add_executable (MarketGateway "MarketGateway.cpp"  "Handler_SOR_order.h"  "MarketVenueClient.h" "MarketVenueClient.cpp" "Factory_handle_market_type_a.h" "Factory_handle_market_type.h" "Gateway.h" "Gateway.cpp" "MarketVenueClient_context_pool.h" "MarketVenueClient_context_pool.cpp" "Handler.h" "Handler_SOR_order.cpp")

target_link_libraries(MarketGateway PRIVATE fmt::fmt-header-only;Boost::date_time)
target_compile_features(MarketGateway PRIVATE cxx_std_17)
target_link_libraries(MarketGateway PRIVATE cnats::nats_static)
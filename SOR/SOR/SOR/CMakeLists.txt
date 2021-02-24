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

add_executable (SOR "SOR.cpp"  "HandlerOrder.cpp" "MsgBus.h" "MshBus.cpp" "MarketsData.h" "MarketsData.cpp" "HandlerMarketData.cpp" "Handler.h"  "MarketVenue.h" "MarketVenue.cpp" "MarketEntity.h" "MarketEntity.cpp" "MarketSymbolData.h" "MarketSymbolData.cpp" "Order.h" "OrderManager.h" "User.h" "OrderManager.cpp" "User.cpp" "Order.cpp")

target_link_libraries(SOR PRIVATE fmt::fmt-header-only;Boost::date_time)
target_compile_features(SOR PRIVATE cxx_std_17)
target_link_libraries(SOR PRIVATE cnats::nats_static)

# CMakeList.txt : CMake project for SOR, include source and define
# project specific logic here.
#
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
# Add source to this project's executable.
add_executable (SOR "SOR.cpp" "SOR.h" "HandlerOrder.cpp" "MsgBus.h" "MshBus.cpp" "MarketData.h" "MarketData.cpp" "HandlerMarketData.cpp" "Handler.h" "Handler.cpp")

target_link_libraries(SOR PRIVATE fmt::fmt-header-only;Boost::date_time)
target_compile_features(SOR PRIVATE cxx_std_17)
target_link_libraries(SOR PRIVATE cnats::nats_static)


cmake_minimum_required (VERSION 3.8)

find_package(fmt)
find_package(cnats)
find_package(Flatbuffers)

include_directories(${FLATBUFFERS_INCLUDE_DIR})

add_executable (FeedHandler "FeedHandler.cpp"  "GenerateSymbol.h" "GenerateSymbol.cpp" "MsgBus.cpp")
target_link_libraries(FeedHandler PRIVATE fmt::fmt-header-only)
target_compile_features(FeedHandler PRIVATE cxx_std_17)
target_link_libraries(FeedHandler PRIVATE cnats::nats_static)


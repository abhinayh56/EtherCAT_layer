cmake_minimum_required(VERSION 3.28.3)
project(ethercat_layer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        OFF)

#include_directories(
#    /usr/local/etherlab/include
#)

set(EtherCAT_LIB_PATH /usr/local/etherlab/lib/libethercat.a)

# Add EC_master sources
add_subdirectory(src/Ec_master)
add_subdirectory(src/Ec_slave)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Ec_master
    Ec_slave
)

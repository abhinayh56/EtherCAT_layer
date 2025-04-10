cmake_minimum_required(VERSION 3.28.3)
project(ethercat_layer)

# Set include directories for EtherCAT headers
include_directories(
    /usr/local/etherlab/include  # Path to the ecrt.h header
)

# Set the path to the EtherCAT library and specify the library
set(EtherCAT_LIB_PATH /usr/local/etherlab/lib/libethercat.a)

# Create the executable from the source code
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${EtherCAT_LIB_PATH})

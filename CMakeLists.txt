cmake_minimum_required(VERSION 3.28.3)
project(ethercat_layer VERSION 1.0.0 LANGUAGES CXX)

# Global compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find EtherCAT library
#find_library(ETHERCAT_LIB ethercat PATHS /usr/local/etherlab/lib REQUIRED)
#set(EtherCAT_LIB_PATH ${ETHERCAT_LIB})
set(EtherCAT_LIB_PATH /usr/local/etherlab/lib/libethercat.a)

# Add subdirectories
add_subdirectory(src/Ec_master)
add_subdirectory(src/Ec_slave)
add_subdirectory(src/Ec_slave_base)
add_subdirectory(src/Ec_slave_base_motor_drive)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Ec_master
    Ec_slave
    Ec_slave_base
    Ec_slave_base_motor_drive
)

# Installation targets
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

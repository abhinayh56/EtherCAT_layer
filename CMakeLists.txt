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
add_subdirectory(src/Ec_app)
add_subdirectory(src/Ec_slave)
add_subdirectory(src/Ec_slave_base)
add_subdirectory(src/Ec_slave_base_motor_drive)
add_subdirectory(src/Ec_slave_base_digital_in)
add_subdirectory(src/Ec_slave_base_digital_out)
add_subdirectory(src/Ec_slave_base_analog_in)
add_subdirectory(src/Ec_slave_base_rs232)
add_subdirectory(src/Ec_slave_base_coupler)
add_subdirectory(src/Ec_slave_base_junction)
add_subdirectory(src/Ec_time)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Ec_app
    Ec_slave
    Ec_slave_base
    Ec_slave_base_motor_drive
    Ec_slave_base_digital_in
    Ec_slave_base_digital_out
    Ec_slave_base_analog_in
    Ec_slave_base_rs232
    Ec_slave_base_coupler
    Ec_slave_base_junction
    Ec_time
    )

# Installation targets
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_library(Ec_slave_base_motor_drive
    Ec_slave_base_motor_drive.cpp
)

target_include_directories(Ec_slave_base_motor_drive
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_slave_base
    PUBLIC ../Ec_utils
)

target_link_libraries(Ec_slave_base_motor_drive
    PRIVATE ${EtherCAT_LIB_PATH}
)

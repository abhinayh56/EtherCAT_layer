add_library(Ec_slave_motor_drive_base
    Ec_slave_motor_drive_base.cpp
)

target_include_directories(Ec_slave_motor_drive_base
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_slave_base
    PUBLIC ../Ec_utils
)

target_link_libraries(Ec_slave_motor_drive_base
    PRIVATE ${EtherCAT_LIB_PATH}
)

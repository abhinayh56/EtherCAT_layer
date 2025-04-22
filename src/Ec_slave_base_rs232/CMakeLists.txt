add_library(Ec_slave_base_rs232
    Ec_slave_base_rs232.cpp
)

target_include_directories(Ec_slave_base_rs232
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_slave_base
    PUBLIC ../Ec_utils
)

target_link_libraries(Ec_slave_base_rs232
    PRIVATE ${EtherCAT_LIB_PATH}
)

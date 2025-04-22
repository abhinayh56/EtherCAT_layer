add_library(Ec_slave_base_analog_in
    Ec_slave_base_analog_in.cpp
)

target_include_directories(Ec_slave_base_analog_in
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_slave_base
    PUBLIC ../Ec_utils
)

target_link_libraries(Ec_slave_base_analog_in
    PRIVATE ${EtherCAT_LIB_PATH}
)

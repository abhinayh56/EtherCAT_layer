add_library(Ec_slave_base_coupler
    Ec_slave_base_coupler.cpp
)

target_include_directories(Ec_slave_base_coupler
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_slave_base
    PUBLIC ../Ec_utils
)

target_link_libraries(Ec_slave_base_coupler
    PRIVATE ${EtherCAT_LIB_PATH}
)

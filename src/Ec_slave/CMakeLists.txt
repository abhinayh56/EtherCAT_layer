# Create library for EC_master module
add_library(Ec_slave
    ../Ec_slave_base/Ec_slave_base.cpp
    ../Ec_slave_base/Ec_slave_base.h
    Ec_slave_ek_1100.cpp
    Ec_slave_ek_1122.cpp
    Ec_slave_el_2008.cpp
    Ec_slave_el_1008.cpp
    Ec_slave_rfid.cpp
    Ec_slave_mact.cpp
    Ec_slave_ingenia.cpp
)

# Include directories
target_include_directories(Ec_slave
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_slave_base
    PRIVATE ${ETHERLAB_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(Ec_slave
    PRIVATE ${EtherCAT_LIB_PATH}
)

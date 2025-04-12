# Create library for EC_master module
add_library(Ec_slave
    ../Ec_slave_base/Ec_slave_base.cpp
    ../Ec_slave_base/Ec_slave_base.h
    Ec_slave_7.cpp
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

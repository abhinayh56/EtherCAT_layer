# Create library for EC_master module
add_library(Ec_master
    Ec_master.cpp
    Ec_master.h
)

# Include directories
target_include_directories(Ec_master
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_slave_base
    PRIVATE ${ETHERLAB_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(Ec_master
    PRIVATE ${EtherCAT_LIB_PATH}
)

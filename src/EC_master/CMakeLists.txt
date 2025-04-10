# Create library for EC_master module
add_library(EC_master
    Ec_master.cpp
    Ec_master.h
)

# Include directories
target_include_directories(EC_master
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${ETHERLAB_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(EC_master
    PRIVATE ${EtherCAT_LIB_PATH}
)

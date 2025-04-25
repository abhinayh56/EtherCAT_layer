# Create library for EC_master module
add_library(Ec_app
    Ec_app.cpp
    Ec_app.h
)

# Include directories
target_include_directories(Ec_app
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_slave_base
    PRIVATE ${ETHERLAB_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(Ec_app
    PRIVATE ${EtherCAT_LIB_PATH}
)

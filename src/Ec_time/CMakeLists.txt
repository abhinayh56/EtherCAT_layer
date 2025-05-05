add_library(Ec_time
    Ec_time.cpp
)

target_include_directories(Ec_time
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ../Ec_utils
)

target_link_libraries(Ec_time
    PRIVATE ${EtherCAT_LIB_PATH}
)

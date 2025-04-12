# Ec_slave_base module configuration
add_library(Ec_slave_base INTERFACE)

target_include_directories(Ec_slave_base
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# Install headers
install(
    FILES 
        Ec_slave_base.h
        Ec_slave_base.cpp
    DESTINATION 
        include/ethercat_layer
    COMPONENT 
        Development
)

# Export target
install(TARGETS Ec_slave_base
    EXPORT ethercat_layerTargets
    INCLUDES DESTINATION include
)

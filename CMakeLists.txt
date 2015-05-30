cmake_minimum_required(VERSION 2.8)

project(jgr_sys)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(GetVersion)

# -----------------------------------------------------------------------------
# Compiler setup
# -----------------------------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -fvisibility=hidden")
endif(CMAKE_COMPILER_IS_GNUCC)

# -----------------------------------------------------------------------------
# Configure include directories and headers
# -----------------------------------------------------------------------------
include_directories(include)
install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# -----------------------------------------------------------------------------
# Source
# -----------------------------------------------------------------------------
add_subdirectory(src)

add_subdirectory(doc)

# -----------------------------------------------------------------------------
# cmake config installation
# -----------------------------------------------------------------------------

configure_file(jgr_sys-config.cmake.in jgr_sys-config.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/jgr_sys-config.cmake" 
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/jgr_sys)

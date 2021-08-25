#----------------------------------------------------------------------------------------------------
# File: CMakeLists.txt
# Name: Jianwei Sun
# Date: 8/22/2021
# Desc: CMake configuration file for the Minesweeper game
#----------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15.2)
project(minesweeper)

# Configure to build for the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configure debug or release mode by setting the EXOUL8_DEBUG environment variable to TRUE or FALSE
if($ENV{MINESWEEPER_DEBUG})
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Debug" FORCE)
    message(STATUS "DEBUG mode")
else()
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Release" FORCE)
    message(STATUS "RELEASE mode")
endif()

# Compiler dependent optimization flags
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/Ox")
endif()

# Sets the install prefix dirctory. Otherwise, pass in to cmake through the -DCMAKE_INSTALL_PREFIX flag on the command line
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE PATH ${CMAKE_SOURCE_DIR} FORCE)
endif()

# Suppress generation of ZERO_CHECK targets. A ZERO_CHECK target regenerates the cmake configuration
set(CMAKE_SUPPRESS_REGENERATION true)

# Qt 5.13.0 requires the Qt5_DIR environment variable to be set to the qtbase directory
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 REQUIRED COMPONENTS 
    Core 
    Gui 
    Widgets
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(Qt5_FOUND)
    message(STATUS "Qt5 FOUND")
endif()

# Include windows SDK files
include_directories($ENV{WINDOWS_SDK_INCLUDE_DIR})

# Include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find project specific source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/*.hpp
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/resources/resources.qrc
)

# Add the executable
if($ENV{MINESWEEPER_DEBUG})
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_FILES}
    )
else()
    add_executable(${PROJECT_NAME} WIN32
        ${PROJECT_SOURCE_FILES}
    )
endif()

# Specify 3rd party static libraries to link against
target_link_libraries(${PROJECT_NAME} 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets
)

# Install the executable
install(TARGETS ${PROJECT_NAME})
#----------------------------------------------------------------------------------------------------
# File: CMakeLists.txt
# Name: Jianwei Sun
# Date: 8/22/2021
# Desc: CMake configuration file for the Minesweeper game
#----------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15.2)
project(Minesweeper)

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

# Set the output
if($ENV{MINESWEEPER_DEBUG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/debug)
else()
    set(RELEASE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/packages/com.vendor.product/data)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RELEASE_OUTPUT_DIRECTORY})
    set(INSTALLER_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/release)
    file(MAKE_DIRECTORY ${INSTALLER_OUTPUT_DIRECTORY})
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

# Set the icon for Windows
if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${PROJECT_SOURCE_DIR}/resources/resources.rc")
endif()

# Add the executable
if($ENV{MINESWEEPER_DEBUG})
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_FILES}
        ${APP_ICON_RESOURCE_WINDOWS}
    )
else()
    add_executable(${PROJECT_NAME} WIN32
        ${PROJECT_SOURCE_FILES}
        ${APP_ICON_RESOURCE_WINDOWS}
    )
endif()

# Specify 3rd party static libraries to link against
target_link_libraries(${PROJECT_NAME} 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets
)

# Package the release for Windows
if(NOT $ENV{MINESWEEPER_DEBUG} AND WIN32)
    message(STATUS "Creating Windows installer")
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS $ENV{Qt5_DIR})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E
            env PATH=$ENV{Qt5_DIR} "${WINDEPLOYQT_EXECUTABLE}"
            ${RELEASE_OUTPUT_DIRECTORY}/${PROJECT_NAME}.exe
        COMMENT "Running windeployqt..."
    )

    find_program(BINARYCREATOR_EXECUTABLE binarycreator HINTS $ENV{QT_BINARYCREATOR_DIR})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E
            env PATH=$ENV{QT_BINARYCREATOR_DIR} "${BINARYCREATOR_EXECUTABLE}"
            --offline-only
            -c ${PROJECT_SOURCE_DIR}/config/config.xml
            -p ${PROJECT_SOURCE_DIR}/packages
            ${INSTALLER_OUTPUT_DIRECTORY}/${PROJECT_NAME}Installer.exe
        COMMENT "Running binarycreator..."
    )
endif()
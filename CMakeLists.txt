cmake_minimum_required(VERSION 3.5)

set(projectName mcalculator)

project(${projectName} VERSION 0.6.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_C_COMPILER gсс)
set(CMAKE_CXX_COMPILER g++)

option(BUILD_TESTS "Build test." OFF)

set(SRC_DIR src)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/winico.rc")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)


add_executable(${projectName} WIN32
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/techprocess.cpp
    ${SRC_DIR}/operation.cpp
    ${SRC_DIR}/parser.cpp
    ${SRC_DIR}/complex_dependance.cpp
    ${SRC_DIR}/measurement.cpp
    ${SRC_DIR}/techprocess_viewer.cpp
    ${SRC_DIR}/gui_techlist.cpp
    ${SRC_DIR}/material_entry.cpp
    ${SRC_DIR}/inputnumberqvalidator.cpp
    ${SRC_DIR}/img.qrc
    ${app_icon_resource_windows}
)

target_include_directories(${projectName} PUBLIC  ${Qt5_INCLUDE_DIR})
target_link_libraries(${projectName} Qt5::Core Qt5::Gui Qt5::Widgets)

if (BUILD_TEST)
    find_package(Catch2 REQUIRED)
    add_executable(${projectName}_test
        test/main_test.cpp
        ${SRC_DIR}/techprocess.cpp
        ${SRC_DIR}/operation.cpp
        ${SRC_DIR}/parser.cpp
        ${SRC_DIR}/complex_dependance.cpp
        ${SRC_DIR}/measurement.cpp
        ${SRC_DIR}/techprocess_viewer.cpp
        ${SRC_DIR}/material_entry.cpp
    )
    target_link_libraries(${projectName}_test PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Catch2::Catch2)
    include(CTest)
    include(Catch)
    catch_discover_tests(${projectName}_test)
endif()



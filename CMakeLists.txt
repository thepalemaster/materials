cmake_minimum_required(VERSION 3.1)

set(projectName materialsQt)

project(${projectName} VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_C_COMPILER gсс)
set(CMAKE_CXX_COMPILER g++)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(${projectName}
main_q.cpp
techprocess.cpp
operation.cpp
parser.cpp
measurement.cpp
techprocess_viewer.cpp
gui_techlist.cpp
material_entry.cpp
)

#install(TARGETS ${projectName} RUNTIME DESTINATION bin)

target_include_directories(${projectName} PUBLIC  ${Qt5_INCLUDE_DIR} )#)${Qt5Widgets_INCLUDE_DIRS})#)${Qt5Core_INCLUDE_DIR})
target_link_libraries(${projectName} Qt5::Core Qt5::Gui Qt5::Widgets)


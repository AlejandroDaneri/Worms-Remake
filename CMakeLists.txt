cmake_minimum_required(VERSION 2.8)
project(worms)

message("[INFO] Librerias necesarias: \n")
message("-Gtkmm version 3.0:")
message("sudo apt-get install libgtkmm-3.0-dev\n")
message("-SDL version 2:")
message("sudo apt-get install libsdl2-mixer-dev\n")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED)

find_package (Threads REQUIRED)
find_package (SDL2 REQUIRED)
find_package (SDL2_Mixer REQUIRED)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=c++11" )

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${SDL2_INCLUDE_DIR})


MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list RELATIVE ${PROJECT_SOURCE_DIR} *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(headers_list)
include_directories(${headers_list})
include_directories(${PROJECT_SOURCE_DIR}/src/Yaml/include)

file(GLOB_RECURSE CLIENT_SOURCES "client*.cpp")
file(GLOB_RECURSE SERVER_SOURCES "server*.cpp")
file(GLOB_RECURSE EDITOR_SOURCES "editor*.cpp")
file(GLOB_RECURSE EDITCLI_SOURCES "editcli*.cpp")
file(GLOB_RECURSE COMMON_SOURCES "common*.cpp")
file(GLOB_RECURSE BOX2D_SOURCES "b2*.cpp")
file(GLOB_RECURSE YAML_SOURCES "yaml*.cpp")

add_library(box2d ${BOX2D_SOURCES})
add_library(yaml ${YAML_SOURCES})
add_library(common ${COMMON_SOURCES})
add_library(editcli ${EDITCLI_SOURCES})


add_executable(client ${CLIENT_SOURCES})
add_executable(server ${SERVER_SOURCES})
add_executable(editor ${EDITOR_SOURCES})

target_link_libraries(client m ${GTKMM_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} common editcli ${SDL2_LIBRARY})
target_link_libraries(editor m yaml ${GTKMM_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} common editcli)
target_link_libraries(server m box2d yaml ${CMAKE_THREAD_LIBS_INIT} common)

#install() aca se podria poner para instalar el gtkmm si no se tiene


set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})


cmake_minimum_required(VERSION 3.8)
project(worms)

set(CMAKE_CXX_STANDARD 17)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

#install() aca se podria poner para instalar el gtkmm si no se tiene

#file(GLOB CLIENT_SOURCES "src/Client/*.cpp" "src/Client/*.h")
#add_executable(client src/client_main.cpp ${CLIENT_SOURCES})
#target_link_libraries(client ${GTKMM_LIBRARIES})

#file(GLOB SERVER_SOURCES "src/Server/*.cpp" "src/Server/*.h")
#add_executable(server src/server_main.cpp ${SERVER_SOURCES})
#target_link_libraries(server ${GTKMM_LIBRARIES})

#### HAY QUE VER LA FORMA DE QUE INCLUYA LOS SUBDIRECTORIOS TAMBIEN####

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

file(GLOB EDITOR_SOURCES "src/Editor/*.cpp" "src/Editor/*.h")
add_executable(editor src/editor_main.cpp ${EDITOR_SOURCES})

target_link_libraries(editor ${GTKMM_LIBRARIES})

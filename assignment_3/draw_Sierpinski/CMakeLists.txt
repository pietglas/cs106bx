project(sierpinksi)
cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(SFML_INCLUDE_DIR "/home/piet/Projects/Libraries/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/piet/Projects/Libraries/SFML-2.5.1/lib")
set(SFML_DIR "/home/piet/Projects/Libraries/lib/cmake")

link_directories(SFML_LIBRARIES_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS network audio graphics window system)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(triangle triangle.cpp)
target_link_libraries(triangle sfml-graphics sfml-window sfml-system)
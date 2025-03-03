cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(audacious-plugin-sort)

# General options
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Finding Audacious
include(FindPkgConfig)
PKG_SEARCH_MODULE(AUDACIOUS REQUIRED audacious>=3.10)
add_definitions(${AUDACIOUS_CFLAGS})


find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

# Creating RPC plugin
add_library(audacious-plugin-sort SHARED main.cc)

target_link_libraries(audacious-plugin-sort PUBLIC ${AUDACIOUS_LDFLAGS} PRIVATE Qt5::Widgets Qt5::Core)

target_include_directories(audacious-plugin-sort PUBLIC ../audacious/src/)

install(TARGETS audacious-plugin-sort DESTINATION /usr/lib/audacious/General/)

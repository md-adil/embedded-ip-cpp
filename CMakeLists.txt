cmake_minimum_required(VERSION 3.13)

set(projectName embedded-ip)

project(${projectName})

add_library(
    events
    events/emitter.cpp
    events/handler.cpp
)

add_library(
    util
    util/json.cpp
    util/url.cpp
    libs/cJSON/cJSON.c
    util/random.cpp
    util/base64.cpp
)

add_library(
    websocket
    websocket/client.cpp
)

add_executable(${projectName} main.cpp)

find_package( Threads )
target_link_libraries( ${projectName} ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(${projectName} websocket events util)

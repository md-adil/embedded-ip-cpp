cmake_minimum_required(VERSION 3.13)

set(projectName rtos-websocket)

project(${projectName})

add_library(
    events
    src/events/emitter.h
    src/events/emitter.cpp
    src/events/handler.h
    src/events/handler.cpp
)

add_library(
    util
    src/util/json.h
    src/util/json.cpp
    src/util/url.h
    src/util/url.cpp
    libs/cJSON/cJSON.h
    libs/cJSON/cJSON.c
    src/util/random.h
    src/util/random.cpp
    src/util/base64.h
    src/util/base64.cpp
)

add_library(
    websocket
    src/websocket/client.h    
    src/websocket/client.cpp
)

add_executable(${projectName} src/main.cpp)

target_link_libraries(${projectName} websocket events util)

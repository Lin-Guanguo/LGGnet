cmake_minimum_required(VERSION 3.5)

project(lggnet_tool)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
    Buffer.cc
    Log.cc    
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        .
)
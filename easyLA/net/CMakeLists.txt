cmake_minimum_required(VERSION 3.5)

project(easyLA_net)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
    Channel.cc
    EventLoop.cc   
 "TCPServer.h")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        .
)

target_link_libraries(${PROJECT_NAME}
	easyLA_tool
)
cmake_minimum_required(VERSION 3.5)

project(easyLA_tool)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
    Buffer.cc
    ClientSocket.cc
    ConnectionSocket.cc
    Process.cc
    ServerSocket.cc
    SocketAPI.cc
    Thread.cc
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        .
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        pthread
)
project(main)

set(CMAKE_CXX_STANDARD 17)

link_directories(
    ../../../build/easyLA/tool
    ../../../build/easyLA/net
)

add_executable(${PROJECT_NAME} 
    main.cc
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        easyLA_tool
        easyLA_net
)

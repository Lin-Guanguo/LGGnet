cmake_minimum_required(VERSION 3.5)

project(easyLATest)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
	"test.cc"
)

target_link_libraries(${PROJECT_NAME}
	easyLA_tool
	easyLA_net
)

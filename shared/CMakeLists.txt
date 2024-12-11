cmake_minimum_required(VERSION 3.29)

add_library(shared STATIC
	src/controller_input.c
)

target_include_directories(shared PUBLIC ${CMAKE_SOURCE_DIR}/shared/include)

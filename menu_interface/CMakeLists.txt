cmake_minimum_required(VERSION 3.29)

add_executable(interface)

set_target_properties(interface PROPERTIES 
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/menu_interface/
)

target_include_directories(interface PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/shared/include
)
target_link_libraries(interface PRIVATE ncurses shared) 
target_compile_options(interface PRIVATE
	$<$<C_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
)

add_subdirectory(src)

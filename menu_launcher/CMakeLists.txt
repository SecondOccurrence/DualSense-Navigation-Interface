cmake_minimum_required(VERSION 3.29)

add_executable(launcher)

set_target_properties(launcher PROPERTIES 
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/menu_launcher/
)

target_include_directories(launcher PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/shared/include
)

target_link_libraries(launcher PRIVATE ncurses shared) 
target_compile_options(launcher PRIVATE
	$<$<C_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
)

add_subdirectory(src)

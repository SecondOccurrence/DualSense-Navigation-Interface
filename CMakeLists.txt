cmake_minimum_required(VERSION 3.29)

project(DualSenseMenu
	DESCRIPTION "DualSense Controller Interface for Navigation."
	LANGUAGES C)

#add_executable(output)

#set_target_properties(output PROPERTIES 
#	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
#)

#target_include_directories(output PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(output PRIVATE ncurses) 
#target_compile_options(output PRIVATE
#	$<$<C_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
#)

add_subdirectory(shared)
add_subdirectory(menu_launcher)
add_subdirectory(menu_interface)

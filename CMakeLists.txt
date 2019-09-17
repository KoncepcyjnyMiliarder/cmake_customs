cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

project(my_sort)

add_executable(${PROJECT_NAME} main.cpp)

#custom target used for running the comparison
add_custom_target(compare_program_outputs
	COMMAND sort test_case > original_sort_res
	COMMAND ${PROJECT_NAME} test_case > my_sort_res
	COMMAND diff original_sort_res my_sort_res
	DEPENDS ${PROJECT_NAME}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Comparing sort results"
)

#generate a test case just before building the app
add_custom_command(
	TARGET ${PROJECT_NAME}
	PRE_BUILD
	COMMAND for i in `seq 1 100`$<SEMICOLON> do < /dev/urandom tr -dc a-z0-9 | head -c20$<SEMICOLON> echo$<SEMICOLON> done > test_case
        COMMENT "Generating 100 alphanum strings of length 20"
)

#after build, run the comparison by calling make on custom target
add_custom_command(TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_MAKE_PROGRAM} compare_program_outputs
	COMMENT "Running comparison"
)

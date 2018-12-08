function(potato_setup_compile_options)
	cmake_parse_arguments(PARSE_ARGV 0 POTATO_FUNC "" "TARGET" "")
	
	message("Applying options for ${POTATO_FUNC_TARGET}") 

	# Enable warnings and C++17
	target_compile_options(${POTATO_FUNC_TARGET} PUBLIC $<$<CXX_COMPILER_ID:GNU>:-std=c++17;-Wall;-Wextra;-pedantic>)
	target_compile_options(${POTATO_FUNC_TARGET} PUBLIC $<$<CXX_COMPILER_ID:Clang>:-std=c++17;-Weverything;-Wno-c++98-compat;-Wno-c++98-compat-pedantic>)
	target_compile_options(${POTATO_FUNC_TARGET} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/std:c++latest;/W4>)
endfunction()
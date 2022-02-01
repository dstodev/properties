include(GoogleTest)

find_package(HelpParseArguments REQUIRED)

function(help_gtest_library target)
	help_parse_arguments(args
		""
		"SUFFIX"
		"SOURCES;LIBRARIES"
	)

	if (args_SUFFIX)
		set(target_name "${target}_${args_SUFFIX}")
	else()
		set(target_name "${target}_test")
	endif()

	add_executable(${target_name}
		${args_SOURCES}
	)
	target_link_libraries(${target_name}
		PRIVATE
			${target}
			${args_LIBRARIES}
			gtest_main
	)
	gtest_discover_tests(${target_name})
endfunction()

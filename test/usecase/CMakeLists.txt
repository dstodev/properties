find_package(HelpGTestLibrary REQUIRED)

help_gtest_library(property
	SUFFIX char_test
	SOURCES
		test_char.cxx
)

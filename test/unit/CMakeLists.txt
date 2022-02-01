find_package(HelpGTestLibrary REQUIRED)

help_gtest_library(property
	SOURCES
		test_property.cxx
)

target_compile_features(property_test
	PRIVATE
		cxx_std_17
)

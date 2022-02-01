set(target_name "property")

add_library(${target_name} INTERFACE)

target_include_directories(${target_name}
	INTERFACE
		${CMAKE_CURRENT_LIST_DIR}
)
target_compile_features(${target_name}
	INTERFACE
		cxx_std_11
)

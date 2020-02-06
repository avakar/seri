cmake_minimum_required(VERSION 3.12)
project(avakar_seri CXX)

add_library(avakar_seri INTERFACE)
target_compile_features(avakar_seri INTERFACE cxx_std_17)
target_include_directories(avakar_seri INTERFACE include)

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13")
	cmake_policy(SET CMP0076 NEW)
	target_sources(avakar_seri INTERFACE
		include/avakar/seri/endian.h
		include/avakar/seri/packed_int.h
		include/avakar/seri/serialize.h
		include/avakar/seri/stdint.h
		include/avakar/seri/store.h
		include/avakar/seri.h
		)
endif()

add_library(avakar::seri ALIAS avakar_seri)

include(CTest)

if (BUILD_TESTING)
	include(FetchContent)
	FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG d10b9bd02e098476670f5eb0527d2c7281476e8a
		GIT_SHALLOW YES
		)

	FetchContent_GetProperties(Catch2)
	if (NOT catch2_POPULATED)
		FetchContent_Populate(Catch2)
		add_subdirectory("${catch2_SOURCE_DIR}" "${catch2_BINARY_DIR}")
	endif()

	include(${catch2_SOURCE_DIR}/contrib/Catch.cmake)

	add_executable(avakar_seri_test EXCLUDE_FROM_ALL
		test/test.cpp
		test/test1.cpp
		)
	target_link_libraries(avakar_seri_test PUBLIC avakar::seri Catch2::Catch2)

	catch_discover_tests(avakar_seri_test)
endif()

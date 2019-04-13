cmake_minimum_required(VERSION 3.8)

project(avakar_seri CXX)

cmake_policy(SET CMP0076 NEW)

add_library(avakar_libseri INTERFACE)
target_compile_features(avakar_libseri INTERFACE cxx_std_17)
target_sources(avakar_libseri INTERFACE
	include/avakar/seri/endian.h
	include/avakar/seri/packed_int.h
	include/avakar/seri/serialize.h
	include/avakar/seri/stdint.h
	include/avakar/seri/store.h
	include/avakar/seri.h
	)
target_include_directories(avakar_libseri INTERFACE include)

add_subdirectory(deps/Catch2)

include(CTest)
include(deps/Catch2/contrib/Catch.cmake)

add_executable(avakar_libseri_test
	test/test.cpp
	test/test1.cpp
)
target_link_libraries(avakar_libseri_test PUBLIC avakar_libseri Catch2::Catch2)

catch_discover_tests(avakar_libseri_test)

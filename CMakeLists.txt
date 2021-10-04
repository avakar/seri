cmake_minimum_required(VERSION 3.12)
project(avakar_seri CXX)

include(FetchContent)
FetchContent_Declare(avakar.mutest SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/mutest")
FetchContent_MakeAvailable(avakar.mutest)

add_library(avakar_seri INTERFACE)
target_compile_features(avakar_seri INTERFACE cxx_std_20)
target_include_directories(avakar_seri INTERFACE include)

if ("${CMAKE_VERSION}" VERSION_GREATER_EQUAL 3.19)
	cmake_policy(SET CMP0076 NEW)
	target_sources(avakar_seri PRIVATE
		include/avakar/seri/endian.h
		include/avakar/seri/packed_int.h
		include/avakar/seri/serialize.h
		include/avakar/seri/stdint.h
		include/avakar/seri/store.h
		include/avakar/seri.h
		src/seri.natvis
		src/bswap.h
		)
endif()

add_library(avakar::seri ALIAS avakar_seri)

add_mutest(test/test1.cpp avakar::seri)

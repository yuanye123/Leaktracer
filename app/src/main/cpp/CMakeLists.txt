cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(DEPS_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI})
message(STATUS "path : ${DEPS_LIB_PATH}")

set(DEPS_LIB_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/hal ${CMAKE_CURRENT_SOURCE_DIR}/libleaktracer/include)
message(STATUS "path : ${DEPS_LIB_INC_PATH}")
link_directories(${DEPS_LIB_PATH})

include_directories(${DEPS_LIB_INC_PATH})

add_library(
        leak
        SHARED
        native-lib.cpp
        libleaktracer/src/AllocationHandlers.cpp
        libleaktracer/src/MemoryTrace.cpp
)

target_link_libraries(
        leak
        log
        android
        z
)
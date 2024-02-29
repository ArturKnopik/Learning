cmake_minimum_required(VERSION 3.20)


project(CMakeProject CXX)

add_executable(CMakeProject main.cpp)

target_sources(CMakeProject PRIVATE
    src/ClassExample.cpp
)

set_target_properties(CMakeProject PROPERTIES CXX_STANDARD 20)
set_target_properties(CMakeProject PROPERTIES CXX_STANDARD_REQUIRED ON)

set(LOGGER_PATH "../LoggerDll/x64/Debug")

target_include_directories(CMakeProject PUBLIC "../LoggerDll/")
target_include_directories(CMakeProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(CMakeProject PUBLIC ${LOGGER_PATH})
target_link_libraries(CMakeProject PUBLIC LoggerDll)


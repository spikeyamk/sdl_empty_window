cmake_minimum_required(VERSION 3.28)
project(upper C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp
	lib/upper.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    include
)

add_subdirectory(lib/inner)

target_link_libraries(${PROJECT_NAME} PRIVATE
    inner
)
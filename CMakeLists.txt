cmake_minimum_required(VERSION 3.15)
project(discord-random-quote)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.14.2
)
FetchContent_MakeAvailable(cpr)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(discord-random-quote
    src/main.cpp
    include/third-party/whereami/whereami.c
)
target_include_directories(discord-random-quote PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include/third-party/whereami
)
target_link_libraries(discord-random-quote PRIVATE cpr::cpr)

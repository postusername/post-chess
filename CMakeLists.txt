cmake_minimum_required(VERSION 3.22)

project(chess-cpp)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

add_executable(chess-cpp ${SOURCES})
add_custom_command(TARGET chess-cpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:chess-cpp>/data)

find_package(Threads REQUIRED)
target_link_libraries(chess-cpp Threads::Threads)
target_link_libraries(chess-cpp sfml-system sfml-window sfml-graphics sfml-audio)

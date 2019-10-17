cmake_minimum_required(VERSION 3.1)
project(Ghost_in_the_cell)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog REQUIRED)
find_package(cxxopts REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_compile_options(-DSPDLOG_COMPILED_LIB -Wall -Werror -Wextra)

# Create directories
file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY lib)

include_directories(
        src
        src/Arena
        src/Objects
        src/Player
        src/Program
        src/Simulation
        src/Logging)

add_subdirectory(src/Logging)
add_subdirectory(src/Objects)
add_subdirectory(src/Player)
add_subdirectory(src/Program)
add_subdirectory(src/Simulation)

# Main executable

add_executable(main
        ${LOGGING_HEADERS}
        ${OBJECT_HEADERS}
        # ${PLAYER_SOURCES}
        ${SIMULATION_HEADERS}
        src/sample.hpp
        src/main.cpp
        src/StringUtils.hpp)

target_link_libraries(main
        logging
        objects
        player
        program
        simulation)

# Test executable

add_executable(tests
        test/InjectableBoard.cpp
        test/InjectableBoard.hpp
        test/Objects/TestPosition.cpp
        test/Objects/TestPosition.hpp
        test/Objects/TestBoard.cpp
        test/Objects/TestBoard.hpp
        test/Objects/Stream/TestEntityStringBuilder.cpp
        test/Objects/Stream/TestEntityStringBuilder.hpp
        test/Objects/Stream/TestEntityWriter.cpp
        test/Objects/Stream/TestEntityWriter.hpp
        test/TestStringUtils.cpp
        test/TestStringUtils.hpp
        test/TestUtils.cpp
        test/TestUtils.hpp
        # src/Logging.hpp
        # src/Simulation/Configuration.cpp
        # src/Simulation/Configuration.hpp
        src/StringUtils.hpp
        test/test.cpp)

target_link_libraries(tests
        logging
        objects)

target_include_directories(tests PUBLIC test)

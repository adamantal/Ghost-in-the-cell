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

# objects library

set(OBJECT_SOURCES
        src/Objects/Board.cpp
        src/Objects/Entity.cpp
        src/Objects/Factory.cpp
        src/Objects/Position.cpp
        src/Objects/Id.cpp
        src/Objects/Link.cpp
        src/Objects/Metrics/BoardMetrics.cpp
        src/Objects/MovingEntity.cpp
        src/Objects/Owner.cpp
        src/Objects/Troop.cpp
        src/Objects/Stream/EntityWriter.cpp
        src/Objects/Stream/EntityStringBuilder.cpp
        src/Objects/Stream/InitStringBuilder.cpp)

set(OBJECT_HEADERS
        src/Objects/Board.hpp
        src/Objects/Bomb.hpp
        src/Objects/Distance.hpp
        src/Objects/Entity.hpp
        src/Objects/Factory.hpp
        src/Objects/Position.hpp
        src/Objects/Id.hpp
        src/Objects/Link.hpp
        src/Objects/Metrics/BoardMetrics.hpp
        src/Objects/MoveException.hpp
        src/Objects/MovingEntity.hpp
        src/Objects/Owner.hpp
        src/Objects/Troop.hpp
        src/Objects/Stream/EntityWriter.hpp
        src/Objects/Stream/EntityStringBuilder.hpp
        src/Objects/Stream/InitStringBuilder.hpp)

add_library(objects
        ${OBJECT_SOURCES})

target_link_libraries(objects
        logging)

# player library

add_library(player
        src/Player/HumanPlayer.cpp
        src/Player/LazyPlayer.cpp
        src/Player/RandomPlayer.cpp)

# simulation library

set(SIMULATION_SOURCES
        src/Simulation/Configuration.cpp
        src/Simulation/Simulation.cpp
        src/Simulation/SimulationEntity.cpp)

set(SIMULATION_HEADERS
        src/Simulation/Configuration.hpp
        src/Simulation/SimulationEntity.hpp
        src/Simulation/Simulation.hpp
        src/Simulation/simulation.hpp)

add_library(simulation
        ${SIMULATION_SOURCES})

# Main executable

add_executable(main
        ${LOGGING_HEADERS}
        ${OBJECT_HEADERS}
        # ${PLAYER_SOURCES}
        ${SIMULATION_HEADERS}
        src/sample.hpp
        src/main.cpp
        src/StringUtils.hpp
        src/Program/Engine.cpp
        src/Program/Engine.hpp
        src/Program/Game.cpp
        src/Program/Game.hpp)

target_link_libraries(main
        logging
        objects
        player
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

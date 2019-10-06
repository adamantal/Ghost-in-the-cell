cmake_minimum_required(VERSION 3.1)
project(Ghost_in_the_cell)

set(CMAKE_CXX_STANDARD 17)

if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-DSPDLOG_COMPILED_LIB -Wall -Werror -Wextra)

# Create directories for the logs
# TODO create this by the program, not during compilation
file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY bin/logs)
file(MAKE_DIRECTORY bin/logs/runs)

set(SRC_DIRS
        PUBLIC src
        PUBLIC src/Arena
        PUBLIC src/Objects
        PUBLIC src/Player
        PUBLIC src/Program)

set(OBJECT_SOURCES
        src/Objects/Board.cpp
        src/Objects/Board.hpp
        src/Objects/Bomb.hpp
        src/Objects/Distance.hpp
        src/Objects/Entity.cpp
        src/Objects/Entity.hpp
        src/Objects/Factory.cpp
        src/Objects/Factory.hpp
        src/Objects/Position.cpp
        src/Objects/Position.hpp
        src/Objects/Id.cpp
        src/Objects/Id.hpp
        src/Objects/Link.cpp
        src/Objects/Link.hpp
        src/Objects/Metrics/BoardMetrics.cpp
        src/Objects/Metrics/BoardMetrics.hpp
        src/Objects/MoveException.hpp
        src/Objects/MovingEntity.cpp
        src/Objects/MovingEntity.hpp
        src/Objects/Owner.cpp
        src/Objects/Owner.hpp
        src/Objects/Troop.cpp
        src/Objects/Troop.hpp
        src/Objects/Stream/EntityWriter.cpp
        src/Objects/Stream/EntityWriter.hpp
        src/Objects/Stream/EntityStringBuilder.cpp
        src/Objects/Stream/EntityStringBuilder.hpp
        src/Objects/Stream/InitStringBuilder.cpp
        src/Objects/Stream/InitStringBuilder.hpp)

set(PLAYER_SOURCES
        src/Player/HumanPlayer.cpp
        src/Player/HumanPlayer.hpp
        src/Player/Player.hpp
        src/Player/LazyPlayer.cpp
        src/Player/LazyPlayer.hpp
        src/Player/RandomPlayer.cpp
        src/Player/RandomPlayer.hpp
        src/Player/DummyPlayer.hpp)

set(LOGGING_SOURCES
        src/logging.cpp
        src/logging.hpp)

add_executable(main
        src/sample.hpp
        src/main.cpp
        src/Configuration.cpp
        src/Configuration.hpp
        src/StringUtils.hpp
        ${LOGGING_SOURCES}
        ${OBJECT_SOURCES}
        ${PLAYER_SOURCES}
        src/Program/Engine.cpp
        src/Program/Engine.hpp
        src/Program/Game.cpp
        src/Program/Game.hpp)

target_link_libraries(main PRIVATE spdlog::spdlog)

target_include_directories(main ${SRC_DIRS})

add_executable(tests
        ${OBJECT_SOURCES}
        ${LOGGING_SOURCES}
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
        src/logging.cpp
        src/logging.hpp
        src/Configuration.cpp
        src/Configuration.hpp
        src/StringUtils.hpp
        test/test.cpp)

target_link_libraries(tests PRIVATE spdlog::spdlog)

target_include_directories(tests ${SRC_DIRS})
target_include_directories(tests PUBLIC test)

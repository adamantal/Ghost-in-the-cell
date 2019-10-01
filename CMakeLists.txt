cmake_minimum_required(VERSION 3.1)
project(Ghost_in_the_cell)

set(CMAKE_CXX_STANDARD 17)

if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-DSPDLOG_COMPILED_LIB -Wall -Werror -Wextra)

# Create directories for the logs
file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY bin/logs)
file(MAKE_DIRECTORY bin/logs/runs)

include_directories(src)
include_directories(src/Arena)
include_directories(src/Player)
include_directories(src/Objects)
include_directories(src/Program)

set(OBJECT_SOURCES
        src/Arena/Arena.cpp
        src/Arena/Arena.hpp
        src/Objects/Board.cpp
        src/Objects/Board.hpp
        src/Objects/Bomb.hpp
        src/Objects/Distance.hpp
        src/Objects/Entity.cpp
        src/Objects/Entity.hpp
        src/Objects/Factory.cpp
        src/Objects/Factory.hpp
        src/Objects/Helper/Position.cpp
        src/Objects/Helper/Position.hpp
        src/Objects/Id.cpp
        src/Objects/Id.hpp
        src/Objects/Link.cpp
        src/Objects/Link.hpp
        src/Objects/Metrics/BoardMetrics.cpp
        src/Objects/Metrics/BoardMetrics.hpp
        src/Objects/MoveException.hpp
        src/Objects/MovingEntity.cpp
        src/Objects/MovingEntity.hpp
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

add_executable(main
        src/logging.cpp
        src/logging.hpp
        src/main.cpp
        ${OBJECT_SOURCES}
        ${PLAYER_SOURCES}
        src/Program/Engine.cpp
        src/Program/Engine.hpp
        src/Program/Game.cpp
        src/Program/Game.hpp)

target_link_libraries(main PRIVATE spdlog::spdlog)

add_executable(tests
        ${OBJECT_SOURCES}
        src/Test/InjectableBoard.cpp
        src/Test/InjectableBoard.hpp
        src/Objects/Helper/TestPosition.cpp
        src/Objects/Helper/TestPosition.hpp
        src/Objects/Owner.cpp
        src/Objects/TestBoard.cpp
        src/Objects/TestBoard.hpp
        src/Objects/Stream/TestEntityStringBuilder.cpp
        src/Objects/Stream/TestEntityStringBuilder.hpp
        src/Objects/Stream/TestEntityWriter.cpp
        src/Objects/Stream/TestEntityWriter.hpp
        src/Test/TestUtils.cpp
        src/Test/TestUtils.hpp
        src/logging.cpp
        src/logging.hpp
        src/test.cpp)

target_link_libraries(tests PRIVATE spdlog::spdlog)

cmake_minimum_required(VERSION 3.1)
project(Ghost_in_the_cell)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(src/MyProgram)
include_directories(src/Objects)
include_directories(src/Program)
include_directories(src/Test)

set(OBJECT_SOURCES
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

add_executable(Ghost_in_the_cell
        src/main.cpp
        src/MyProgram/MyProgram.cpp
        src/MyProgram/MyProgram.hpp
        ${OBJECT_SOURCES}
        src/Program/DummyPlayer.hpp
        src/Program/Engine.cpp
        src/Program/Engine.hpp
        src/Program/Game.cpp
        src/Program/Game.hpp
        src/Program/Player.hpp
        src/Program/RandomPlayer.cpp
        src/Program/RandomPlayer.hpp)

add_executable(Test
        ${OBJECT_SOURCES}
        src/Objects/Helper/TestPosition.cpp
        src/Objects/Helper/TestPosition.hpp
        src/Objects/TestBoard.cpp
        src/Objects/TestBoard.hpp
        src/Objects/Stream/TestEntityStringBuilder.cpp
        src/Objects/Stream/TestEntityStringBuilder.hpp
        src/Objects/Stream/TestEntityWriter.cpp
        src/Objects/Stream/TestEntityWriter.hpp
        src/Test/TestUtils.cpp
        src/Test/TestUtils.hpp
        src/test.cpp src/Objects/Helper/InjectableBoard.cpp src/Objects/Helper/InjectableBoard.hpp)

cmake_minimum_required(VERSION 3.12)
project(Ghost_in_the_cell)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(src/Objects)
include_directories(src/Program)

add_executable(Ghost_in_the_cell
        src/Objects/Battle.cpp
        src/Objects/Battle.hpp
        src/Objects/Board.cpp
        src/Objects/Board.hpp
        src/Objects/Bomb.hpp
        src/Objects/Distance.hpp
        src/Objects/Entity.cpp
        src/Objects/Entity.hpp
        src/Objects/Factory.cpp
        src/Objects/Factory.hpp
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
        src/Program/DummyPlayer.hpp
        src/Program/Engine.cpp
        src/Program/Engine.hpp
        src/Program/Game.cpp
        src/Program/Game.hpp
        src/Program/Player.hpp
        src/MyProgram/MyProgram.cpp
        src/main.cpp src/MyProgram/MyProgram.hpp)

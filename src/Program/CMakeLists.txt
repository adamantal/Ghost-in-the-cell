set(PROGRAM_HEADERS
        Engine.hpp
        Game.hpp)

add_library(program
        Engine.cpp
        Game.cpp)

target_link_libraries(program
        objects)

set(SIMULATION_HEADERS
        Configuration.hpp
        SimulationEntity.hpp
        Simulation.hpp
        simulation.hpp)

add_library(simulation
        Configuration.cpp
        Simulation.cpp
        SimulationEntity.cpp)

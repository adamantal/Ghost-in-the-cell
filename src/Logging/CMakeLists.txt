set(LOGGING_HEADERS
        Logging.hpp)

add_library(logging STATIC
        Logging.cpp)

target_link_libraries(logging
        spdlog::spdlog
        stdc++fs)

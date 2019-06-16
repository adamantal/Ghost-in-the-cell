#include "Id.hpp"

Id NextId() {
    static Id id = MIN_ID;
    return id++;
}

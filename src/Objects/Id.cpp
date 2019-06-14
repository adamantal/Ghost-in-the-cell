#include "Id.hpp"

Id nextId() {
    static Id id = MIN_ID;
    return id++;
}

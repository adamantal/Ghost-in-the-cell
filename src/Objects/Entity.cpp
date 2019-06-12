#include "Entity.hpp"

Entity::Entity(Id id, Owner owner) :
        id(id),
        owner(owner) {
}

Owner Entity::getOwner() const {
    return owner;
}

Id Entity::getId() const {
    return id;
}

void Entity::setOwner(Owner newOwner) {
    owner = newOwner;
}

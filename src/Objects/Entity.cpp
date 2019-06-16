#include "Entity.hpp"

Entity::Entity(Id id, Owner owner) :
        id(id),
        owner(owner) {
}

Owner Entity::GetOwner() const {
    return owner;
}

Id Entity::GetId() const {
    return id;
}

void Entity::SetOwner(Owner newOwner) {
    owner = newOwner;
}

#include "Entity.hpp"

Entity::Entity(int a1, int a2):
    id(a1),
    owner(Player(a2)) {}

Player Entity::getOwner() const {
  return owner;
}

int Entity::getId() const {
  return id;
}

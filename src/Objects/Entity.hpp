#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <memory>

#include "Owner.hpp"
#include "Id.hpp"

class Entity;

typedef std::shared_ptr<Entity> EntityPtr;

class Entity {
private:
    Id id;
    Owner owner;

public:
    Entity(Id, Owner);

    Owner GetOwner() const;
    void SetOwner(Owner);
    Id GetId() const;
};

#endif // ENTITY_HPP_INCLUDED

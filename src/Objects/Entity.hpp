#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include "Player.hpp"

class Entity {
  protected:
    int id;
    Player owner;

  public:
    Entity(){}
    Entity(int a1, int a2);

    Player getOwner() const;
    int getId() const ;
};

#endif // ENTITY_HPP_INCLUDED

#include "EntityWriter.hpp"
#include "EntityStringBuilder.hpp"

short EntityWriter::convertOwner(Owner entityOwner, Owner owner) {
    if (entityOwner == Neutral) {
        return 0;
    } else {
        return (entityOwner == owner) ? (short) 1 : (short) -1;
    }
}

std::string EntityWriter::write(const FactoryConstPtr& factory, Owner owner) {
    EntityStringBuilder esb(factory->getId(),
                            EntityTypes::FACTORY,
                            convertOwner(factory->getOwner(), owner));

    return esb.setArg2(factory->getCyborgs()).
            setArg3(factory->getProduction()).
            setArg4(factory->getBadTurns()).
            build();
}

std::string EntityWriter::write(const TroopConstPtr& troop, Owner owner) {
    EntityStringBuilder esb(troop->getId(),
                            EntityTypes::TROOP,
                            convertOwner(troop->getOwner(), owner));

    return esb.setArg2(troop->getOrigin()->getId()).
            setArg3(troop->getTarget()->getId()).
            setArg4(troop->getCyborgs()).
            setArg5(troop->getTurns()).
            build();
}

std::string EntityWriter::write(const BombConstPtr& bomb, Owner owner) {
    EntityStringBuilder esb(bomb->getId(),
                            EntityTypes::BOMB,
                            convertOwner(bomb->getOwner(), owner));
    bool visible = bomb->getOwner() == owner;
    esb.setArg2(bomb->getOrigin()->getId());
    if (visible) {
        esb.setArg3(bomb->getTarget()->getId())
        .setArg4(bomb->getTurns());
    } else {
        esb.setArg3((short) -1)
        .setArg4((short)-1);
    }
    return esb.build();
}

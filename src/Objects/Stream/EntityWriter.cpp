#include "EntityWriter.hpp"
#include "EntityStringBuilder.hpp"

short EntityWriter::convertOwner(Owner entityOwner, Owner owner) {
    if (entityOwner == Neutral) {
        return 0;
    } else {
        return (entityOwner == owner) ? (short) 1 : (short) -1;
    }
}

std::string EntityWriter::Write(const FactoryConstPtr &factory, Owner owner) {
    EntityStringBuilder esb(factory->GetId(),
                            EntityTypes::FACTORY,
                            convertOwner(factory->GetOwner(), owner));

    return esb.SetArg2(factory->GetCyborgs()).
            SetArg3(factory->GetProduction()).
            SetArg4(factory->GetBadTurns()).
            Build();
}

std::string EntityWriter::Write(const TroopConstPtr &troop, Owner owner) {
    EntityStringBuilder esb(troop->GetId(),
                            EntityTypes::TROOP,
                            convertOwner(troop->GetOwner(), owner));

    return esb.SetArg2(troop->GetOrigin()->GetId()).
            SetArg3(troop->GetTarget()->GetId()).
            SetArg4(troop->GetCyborgs()).
            SetArg5(troop->GetTurns()).
            Build();
}

std::string EntityWriter::Write(const BombConstPtr &bomb, Owner owner) {
    EntityStringBuilder esb(bomb->GetId(),
                            EntityTypes::BOMB,
                            convertOwner(bomb->GetOwner(), owner));
    bool visible = bomb->GetOwner() == owner;
    esb.SetArg2(bomb->GetOrigin()->GetId());
    if (visible) {
        esb.SetArg3(bomb->GetTarget()->GetId())
                .SetArg4(bomb->GetTurns());
    } else {
        esb.SetArg3((short) -1)
                .SetArg4((short) -1);
    }
    return esb.Build();
}

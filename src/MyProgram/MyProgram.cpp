#include "MyProgram.hpp"

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

//enum Action{MOVE, BOMB, WAIT, MSG};

std::vector<int> Heuristic::Table::getEstimatedCyborgsFromZeroTime(int id, int zerotime) { // positive is ours, negative is not ours
    //initialised timeline
    std::vector<int> timeline, troopline;
    for (int i = 0; i < 20; i++) timeline.push_back(0);
    for (int i = 0; i < 20; i++) troopline.push_back(0);

    if (factories[id].getOwner() != Heuristic::Player::Us) {
        timeline[0] = -1 * zerotime;
    }
    if (factories[id].getOwner() == Heuristic::Player::Us) {
        timeline[0] = zerotime;
    }

    for (auto troopit = begin(troops); troopit != end(troops); troopit++) {
        if (troopit->getTarget() == id) {
            int t = troopit->getAmount();
            if (troopit->getOwner() == Heuristic::Player::Us) {
                troopline[troopit->getTime()] += t;
            } else {
                troopline[troopit->getTime()] -= t;
            }
        }
    }

    Heuristic::Player currentowner = factories[id].getOwner();
    int currentamount = timeline[0];
    for (int i = 1; i < 20; i++) {
        timeline[i] = timeline[i - 1] + int(currentowner) * factories[id].getNetProductionAtRound(i);

        if (currentowner == Heuristic::Player::Neutral) {
            if (troopline[i] > 0) {
                timeline[i] += troopline[i];
                if (timeline[i] > 0) {
                    currentowner == Heuristic::Player::Us;
                }
            } else if (troopline[i] < 0) {
                timeline[i] -= troopline[i];
                if (timeline[i] > 0) {
                    timeline[i] *= -1;
                    currentowner == Heuristic::Player::Enemy;
                }
            }
        } else if (currentowner == Heuristic::Player::Us) {
            timeline[i] += troopline[i];
            if (timeline[i] < 0) {
                currentowner = Heuristic::Player::Enemy;
            }
        } else if (currentowner == Heuristic::Player::Enemy) {
            timeline[i] += troopline[i];
            if (timeline[i] > 0) {
                currentowner = Heuristic::Player::Enemy;
            }
        }
    }
    return timeline;
}

std::vector<int> Heuristic::Table::getEstimatedCyborgs(int id) { // positive is ours, negative is not ours
    //initialised timeline
    std::vector<int> timeline, troopline;
    for (int i = 0; i < 20; i++) timeline.push_back(0);
    for (int i = 0; i < 20; i++) troopline.push_back(0);

    if (factories[id].getOwner() != Heuristic::Player::Us) {
        timeline[0] = -1 * int(factories[id].getNumberOfCyborgs());
    }
    if (factories[id].getOwner() == Heuristic::Player::Us) {
        timeline[0] = factories[id].getNumberOfCyborgs();
    }

    for (auto troopit = begin(troops); troopit != end(troops); troopit++) {
        if (troopit->getTarget() == id) {
            int t = troopit->getAmount();
            if (troopit->getOwner() == Heuristic::Player::Us) {
                troopline[troopit->getTime()] += t;
            } else {
                troopline[troopit->getTime()] -= t;
            }
        }
    }

    Heuristic::Player currentowner = factories[id].getOwner();
    int currentamount = timeline[0];
    for (int i = 1; i < 20; i++) {
        timeline[i] = timeline[i - 1] + int(currentowner) * factories[id].getNetProductionAtRound(i);

        if (currentowner == Heuristic::Player::Neutral) {
            if (troopline[i] > 0) {
                timeline[i] += troopline[i];
                if (timeline[i] > 0) {
                    currentowner = Heuristic::Player::Us;
                }
            } else if (troopline[i] < 0) {
                timeline[i] -= troopline[i];
                if (timeline[i] > 0) {
                    timeline[i] *= -1;
                    currentowner = Heuristic::Player::Enemy;
                }
            }
        } else if (currentowner == Heuristic::Player::Us) {
            timeline[i] += troopline[i];
            if (timeline[i] < 0) {
                currentowner = Heuristic::Player::Enemy;
            }
        } else if (currentowner == Heuristic::Player::Enemy) {
            timeline[i] += troopline[i];
            if (timeline[i] > 0) {
                currentowner = Heuristic::Player::Enemy;
            }
        }
    }
    return timeline;
}

Heuristic::Factory* Heuristic::Table::evacuateFrom(Heuristic::Factory *f) {
    Heuristic::Factory *closestid = nullptr;
    int closestvalue = 99;
    for (auto it = begin(factories); it != end(factories); it++) {
        if (it->second.getId() != f->getId()) {
            if (getDistance((it->second).getId(), f->getId()) < closestvalue) {
                closestvalue = getDistance((it->second).getId(), f->getId());
                closestid = &it->second;
            }
        }
    }
    return closestid;
}

bool MyProgram::setup(std::string input) {
    std::stringstream ss(input);

    int factoryCount; // the number of factories
    ss >> factoryCount;
    int linkCount; // the number of links between factories
    ss >> linkCount;

    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        ss >> factory2 >> distance >> factory1;
        table.addLink(factory1, factory2, distance);
    }

    return true;
}

std::string MyProgram::getResponse(std::string input) {
    std::stringstream ss(input);

    int entityCount; // the number of entities (e.g. factories and troops)
    ss >> entityCount;
    //initializing table:
    for (int i = 0; i < entityCount; i++) {
        int entityId;
        string entityType;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        ss >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5;
        if (entityType == "FACTORY") {
            table.addFactory(entityId, arg1, arg2, arg3, arg4);
        } else if (entityType == "TROOP") {
            table.addTroop(entityId, arg1, arg2, arg3, arg4, arg5);
        } else if (entityType == "BOMB") {
            table.addBomb(entityId, arg1, arg2, arg3, arg4);
        } else {
            throw "ERROR: UNKNOWN ENTITY TYPE";
        }
    }

    /*vector<int> v = table.getEstimatedCyborgs(1);
    for (int i = 0; i < 20; i++) cerr << v[i] << " ";
    cerr << ";";*/

    //set up bomb processor
    if (!table.hostileBombExist() && bombPredictionExist) {
        bombPredictionExist = false;
        bombPredictionId = -1;
        bombPredictionTurns = 0;
    }
    if (table.hostileBombExist() && !bombPredictionExist) {
        //set bomb to the most
        map<int, int> m;
        Heuristic::Bomb b = table.getOneBomb();

        vector<Heuristic::Factory *> ours = table.ourFactories();
        int maxid = -1;
        int maxvalue = -1;

        for (auto it = begin(ours); it != end(ours); it++) {
            if ((*it)->getNetProductionAtRound(0) > maxvalue && b.getFrom() != (*it)->getId()) {
                maxvalue = (*it)->getNetProductionAtRound(0);
                maxid = (*it)->getId();
            }
        }

        //choose max, and set
        bombPredictionExist = true;
        bombPredictionId = maxid;
        bombPredictionTurns = table.getDistance(bombPredictionId, b.getFrom());
    }
    if (bombPredictionExist) {
        if (bombPredictionTurns != 0) {
            //MY SECOND, IMPROVED IDEA:
            Heuristic::Factory *from = table.getFactory(bombPredictionId);
            if (bombPredictionTurns == 1 && from->getOwner() == Heuristic::Player::Us) {
                Heuristic::Factory *to = table.evacuateFrom(from);
                if (from != nullptr && to != nullptr) {
                    table.sendTroop(from, to->getId(), from->getNumberOfCyborgs());
                }
            }
            bombPredictionTurns--;
        }
    }

    //First we want to defend our troops:
    vector<Heuristic::Factory *> ours = table.ourFactories();
    map<int, vector<Heuristic::Factory> > priorhelp; //Prioritized map of our endangered factories

    for (auto it = begin(ours); it != end(ours); it++) {
        int k = (*it)->getId();
        if (!table.isSecured(k)) {
            priorhelp[(*it)->getProduction()].push_back(*(*it));
        }
    }
    //writing out
    /*int summ = 0;
    for (auto it = begin(priorhelp); it != end(priorhelp); it++) summ += it->second.size();
    cerr << "Must defend " << summ << " of our troops." << endl;*/

    for (int i = 3; i >= 0; i--) {
        for (auto it = begin(priorhelp[i]); it != end(priorhelp[i]); it++) {
            vector<Heuristic::Factory *> c = table.getEveryFactory();
            for (auto itc = begin(c); itc != end(c); itc++) {
                if ((*itc)->getId() != (*it).getId()) {
                    if ((*itc)->getOwner() == 1) {
                        try {
                            table.sendTroop(*itc, (*it).getId(),
                                            min(table.minRequired((*it).getId()),
                                                (*itc)->getNumberOfCyborgs()));
                        } catch (char const *k) {
                            //std::cerr << k;
                        }
                    }
                }
            }
        }
    }
    //improve?
    //TODO: DO IMPROVE
    if (table.netAllCyborgs() > 0) {
        vector<Heuristic::Factory *> fs = table.getEveryFactory();
        for (auto it = begin(fs); it != end(fs); it++) {
            if ((*it)->getOwner() == Heuristic::Player::Us && (*it)->getProduction() != 3 &&
                (*it)->getNumberOfCyborgs() >= 10 && table.isSecured((*it)->getId())) {
                vector<int> params = {(*it)->getId()};
                table.command("INC", params);
            }
        }
    }

    //then conquer new ones:
    //vector<int> k = table.getEstimatedCyborgs(7);
    /*cerr << "THE VECTOR: ";
    for (auto itveck = begin(k); itveck != end(k); itveck++) cerr << *itveck << " ";
    cerr << "END "<< endl;*/

    for (auto it = begin(ours); it != end(ours); it++) {
        if (table.isSecured((*it)->getId())) {
            map<double, vector<Heuristic::Factory *> > att = table.attackableTargetsFrom((*it)->getId());
            for (auto i = att.rbegin(); i != att.rend(); i++) {
                for (auto ita = begin(att[i->first]); ita != end(att[i->first]); ita++) {
                    //cerr << "attackable id: " << (*ita)->getId() << endl;
                    int j = 1;
                    const int safeId = 11234;
                    for (; j < (*it)->getNumberOfCyborgs(); j++) {
                        //cerr << j << "cycle" << endl;
                        (*it)->decreaseNumberOfCyborgs(j);
                        table.makeTemporaryTroop(safeId, (*it)->getId(), (*ita)->getId(), j,
                                                 table.getDistance((*it)->getId(), (*ita)->getId()));

                        if (!table.isSecuredFromZero((*it)->getId(), (*it)->getNumberOfCyborgs() - j)) {
                            //cerr << "broken bc not secured" << endl;
                            if (j == 1) j = 0;
                            break;
                        }
                        vector<int> k = table.getEstimatedCyborgs((*ita)->getId());
                        //cerr << "THE VECTOR: ";
                        //for (auto itveck = begin(k); itveck != end(k); itveck++) cerr << *itveck << " ";
                        //cerr << "END "<< endl;

                        //cerr << "Value of cybs in the jth round at attackable:" << k[table.getDistance((*it)->getId(),(*ita)->getId())] << endl;
                        if (k[table.getDistance((*it)->getId(), (*ita)->getId())] > 0) {
                            //cerr << "broken bc already sent enough troops" << endl;
                            break;
                        }
                        (*it)->increaseNumberOfCyborgs(j);
                        table.deleteTemporaryTroops(safeId);
                    }
                    (*it)->increaseNumberOfCyborgs(j);
                    table.deleteTemporaryTroops(safeId);
                    //cerr << "j is " << j << " after the loop." << endl;
                    if (j >= 1) {
                        try {
                            table.sendTroop(&(*(*it)), (*ita)->getId(), j);
                        } catch (const string k) {
                            //cerr << k << endl;
                        }
                    }
                }
            }
        }
    }

    //sending bombs:
    if (table.doWeHaveBombs() && !table.ourBombIsEnRoute()) {
        vector<Heuristic::Factory *> all = table.getEveryFactory();
        for (auto it = begin(all); it != end(all); it++) {
            if ((*it)->getOwner() == Heuristic::Player::Us && table.searchForNotCommandedFactory((*it)->getId())) {
                int maxenem = -1, maxamount = -1;
                for (auto enem = begin(all); enem != end(all); enem++) {
                    if ((*enem)->getOwner() == Heuristic::Player::Enemy) {
                        if (maxamount < (*enem)->getNetProductionAtRound(0)) {
                            maxamount = (*enem)->getNetProductionAtRound(0);
                            maxenem = (*enem)->getId();
                        }
                    }
                }
                if (maxenem != -1) {
                    table.sendBomb((*it)->getId(), maxenem);
                    table.decreaseNumOfBombs();
                    break;
                }
            }
        }
    }

    std::string returnString = table.writeCommands();
    table.clearContent();
    track++;
    return returnString;
}

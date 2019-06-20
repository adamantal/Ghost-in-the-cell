#ifndef MYPROGRAM_HPP
#define MYPROGRAM_HPP

#include <map>
#include <sstream>
#include <string>
#include <vector>
//#include <algorithm>
//#include <set>

#include "Program/Player.hpp"

namespace Heuristic {
    enum Player {
        Us = 1, Neutral = 0, Enemy = -1
    };

    struct Command {
        std::string type;
        std::vector<int> parameters;

        Command(std::string t, std::vector<int> p) : type(t), parameters(p) {}
    };

    class Entity {
    protected:
        int id;
        Heuristic::Player owner;

    public:
        Entity() {}
        Entity(int a1, int a2) : id(a1), owner(Heuristic::Player(a2)) {}

        Heuristic::Player getOwner() const {
            return owner;
        }

        int getId() {
            return id;
        }
    };

    struct Link {
    public:
        int dist;
        int fac1;
        int fac2;

        Link(int d, int a1, int a2) : dist(d), fac1(a1), fac2(a2) {}

        int whichIs(int k) {
            if (fac1 == k) {
                return 1;
            } else if (fac2 == k) {
                return 2;
            } else {
                return 0;
            }
        }

        bool either(int k) {
            return (fac1 == k) || (fac2 == k);
        }

        int other(int k) const {
            if (k == fac1) {
                return fac2;
            } else if (k == fac2) {
                return fac1;
            } else {
                throw "Others have bad pointer";
            }
        }

        bool operator<(const Link &rhs) const {
            return dist < rhs.dist;
        }

        bool operator==(const Link &rhs) const {
            return (dist == rhs.dist && fac1 == rhs.fac1 && fac2 == rhs.fac2);
        }

        int get1() const {
            return fac1;
        }

        int get2() const {
            return fac2;
        }

        int getDist() const {
            return dist;
        }
    };

    class Factory : public Heuristic::Entity {
    private:
        unsigned int cyborgs;
        unsigned short production;
        unsigned short badturns;
    public:
        Factory() {}

        Factory(int i, int a1, int a2, int a3, int a4) :
                Heuristic::Entity(i, a1), cyborgs(a2), production(a3), badturns(a4) {}

        int getNumberOfCyborgs() const {
            return cyborgs;
        }

        int getProduction() const {
            return production;
        }

        int getNetProductionAtRound(int k) const {
            if (k < badturns) {
                return 0;
            } else {
                return production;
            }
        }

        bool isnormal() const {
            return badturns == 0 ? true : false;
        }

        int turnsToNormal() const {
            return badturns;
        }

        void decreaseNumberOfCyborgs(int n) {
            //cerr << "Decreasing num of cyb at factory " << id << " from " << to_string(getNumberOfCyborgs()) << " by " << n << endl;
            if (n <= getNumberOfCyborgs()) {
                cyborgs -= n;
            } else {
                throw (std::string("Invalid decrease of cyborgs from") + std::to_string(getNumberOfCyborgs()) + " by " +
                       std::to_string(n) + " at factory " + std::to_string(id));
            }
        }

        void increaseNumberOfCyborgs(int n) {
            //cerr << "Increaseing num of cyb at factory " << id << " from " << to_string(getNumberOfCyborgs()) << " by " << n << endl;
            cyborgs += n;
        }
    };

    class MovingEntity : public Heuristic::Entity {
    protected:
        int from;
        int target;
    public:
        MovingEntity(int i, int a1, int a2, int a3) :
                Heuristic::Entity(i, a1), from(a2), target(a3) {}

        int getTarget() {
            return target;
        }

        int getFrom() {
            return from;
        }
    };

    class Troop : public MovingEntity {
    private:
        unsigned int number;
        unsigned int remainingTurns;
    public:
        Troop(int i, int a1, int a2, int a3, int a4, int a5) :
                MovingEntity(i, a1, a2, a3), number(a4), remainingTurns(a5) {}

        int getTime() {
            if (remainingTurns == 0) {
                throw "Error: Troop with id " + std::to_string(getId()) + " has 0 remaining turns left.\n";
            }
            return remainingTurns;
        }

        int getAmount() {
            return number;
        }
    };

    class Bomb : public MovingEntity {
    private:
        //note that the target is not known, if it is hostile
        unsigned int remainingTurns;
    public:
        Bomb(int i, int a1, int a2, int a3, int a4) :
                MovingEntity(i, a1, a2, a3), remainingTurns(a4) {}

        int getTarget() {
            if (getOwner() == Heuristic::Player::Enemy) {
                throw "Error: you want to get a not known target!\n";
            } else {
                return target;
            }
        }

        int getTime() {
            return remainingTurns;
        }
    };

    class Table {
    private:
        //main things:
        std::map<int, Factory> factories; //id-Factory mapping
        std::vector<Troop> troops;
        std::vector<Bomb> bombs;
        std::vector<Link> links; //distances
        std::vector<Command> commands;
        unsigned short mybombs = 2;

    public:

        void addFactory(int i, int a1, int a2, int a3, int a4) {
            Factory tmp(i, a1, a2, a3, a4);
            factories[i] = tmp;
        }

        void addTroop(int i, int a1, int a2, int a3, int a4, int a5) {
            Troop tmp(i, a1, a2, a3, a4, a5);
            //cerr << "The id of the troop is " << i << endl;
            troops.push_back(tmp);
        }

        void addBomb(int i, int a1, int a2, int a3, int a4) {
            Bomb tmp(i, a1, a2, a3, a4);
            bombs.push_back(tmp);
        }

        void addLink(int i1, int i2, int i3) {
            Link tmp(i1, i2, i3);
            links.push_back(tmp);
        }

        std::vector<Factory *> ourFactories() {
            std::vector<Factory *> returnable;
            for (auto it = begin(factories); it != end(factories); it++) {
                if (((*it).second).getOwner() == 1) {
                    returnable.push_back(&(it->second));
                }
            }
            return returnable;
        }

        double getHeuristicValue(Factory *f) {
            double k = 0.0;
            k += double(f->getProduction()) - f->getNumberOfCyborgs();
            return k;
        }

        double getHeuristicValueFromId(int id, Factory *targ) {
            double k = 0.0;
            k -= getDistance(id, targ->getId());
            if (targ->getOwner() != Heuristic::Player::Enemy) {
                k += 4.0;
            }
            k += targ->getProduction() * 2;
            k -= targ->getNumberOfCyborgs() * 0.4;

            //k +=  double(targ->getProduction())*(double(targ->getOwner()) / double(getDistance(id, targ->getId()))) - double(targ->getNumberOfCyborgs());
            return k;
        }

        std::map<double, std::vector<Factory *> > attackableTargets() { //targetProduction x targets structure
            std::map<double, std::vector<Factory *> > ret;
            for (auto it = begin(factories); it != end(factories); it++) {
                if ((it->second).getOwner() != Heuristic::Player::Us) {
                    ret[getHeuristicValue(&(*it).second)].push_back(&(it->second));
                }
            }
            return ret;
        }

        std::map<double, std::vector<Factory *> > attackableTargetsFrom(int id) { //targetProduction x targets structure
            std::map<double, std::vector<Factory *> > ret;
            for (auto it = begin(factories); it != end(factories); it++) {
                if ((it->second).getOwner() != Heuristic::Player::Us && (it->second).getId() != id) {
                    ret[getHeuristicValueFromId(id, &(*it).second)].push_back(&(it->second));
                }
            }
            return ret;
        }

        int getDistance(int id1, int id2) {
            if (id1 == id2) {
                throw "ids are the same, it is very bad: " + std::to_string(id1);
            }
            for (auto it = begin(links); it != end(links); it++) {
                if (it->either(id1) && it->either(id2)) {
                    return it->dist;
                }
            }
            throw "Some bad id-s are given!";
        }

        void sendTroop(Factory *from, int target, int amount) {
            if (amount != 0) {
                //cerr << "SENT from " <<from->getId() << " to " << target << ", " << amount << " number of troops" << endl;
                addTroop(999, 1, from->getId(), target, amount, getDistance(from->getId(), target));
                from->decreaseNumberOfCyborgs(amount);
                std::vector<int> v = {from->getId(), target, amount};
                command("MOVE", v);
            }
        }

        bool searchForNotCommandedFactory(int k) {
            for (auto it = begin(commands); it != end(commands); it++) {
                if (it->type == "MOVE") {
                    if (it->parameters[0] == k) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool doWeHaveBombs() {
            return mybombs > 0;
        }

        bool ourBombIsEnRoute() {
            for (auto it = begin(bombs); it != end(bombs); it++) {
                if (it->getOwner() == Heuristic::Player::Us) {
                    return true;
                }
            }
            return false;
        }

        void decreaseNumOfBombs() {
            mybombs--;
        }

        void sendBomb(int from, int target) {
            std::vector<int> v = {from, target};
            command("BOMB", v);
        }

        void command(std::string t, std::vector<int> params) {
            Command tmp(t, params);
            commands.push_back(tmp);
        }

        std::string writeCommands() {
            std::stringstream ss;
            if (commands.size() == 0)
                ss << "WAIT";
            else {
                for (unsigned int i = 0; i < commands.size(); i++) {
                    ss << commands[i].type << " ";
                    for (unsigned int j = 0; j < commands[i].parameters.size() - 1; j++) {
                        ss << commands[i].parameters[j] << " ";
                    }
                    ss << commands[i].parameters[commands[i].parameters.size() - 1];
                    if (i != commands.size() - 1) {
                        ss << ";";
                    }
                }
            }
            ss << "\n";
            return ss.str();
        }

        bool hostileBombExist() {
            if (bombs.size() == 0) return false;
            for (auto it = begin(bombs); it != end(bombs); it++) {
                if (it->getOwner() == Heuristic::Player::Enemy) return true;
            }
            return false;
        }

        Bomb getOneBomb() {
            for (auto it = begin(bombs); it != end(bombs); it++) {
                if (it->getOwner() == Heuristic::Player::Enemy) {
                    return *it;
                }
            }
            throw "No enemy bomb was found!";
        }

        std::vector<int> getEstimatedCyborgsFromZeroTime(int id, int zerotime);
        std::vector<int> getEstimatedCyborgs(int id);

        int firstBadRound(int id) {
            std::vector<int> timel = getEstimatedCyborgs(id);
            for (unsigned int i = 0; i < timel.size(); i++) {
                if (timel[i] < 0) return i;
            }
            return -1;
        }

        bool isSecured(int id) {
            std::vector<int> timel = getEstimatedCyborgs(id);
            /*for (auto it = begin(timel); it != end(timel); it++) cerr << *it << " ";
            cerr << endl;*/
            if (timel[19] > 0) return true;
            return false;
        }

        bool isSecuredFromZero(int id, int zeroturn) {
            std::vector<int> timel = getEstimatedCyborgsFromZeroTime(id, zeroturn);
            /*for (auto it = begin(timel); it != end(timel); it++) cerr << *it << " ";
            cerr << endl;*/
            for (unsigned int i = 0; i < timel.size(); i++) {
                if (timel[i] < 0) return false;
            }
            return true;
        }

        int minRequired(int id) {
            if (firstBadRound(id) == -1) return 0;
            return -getEstimatedCyborgs(id)[firstBadRound(id)];
        }

        int netAllCyborgs() {
            int balance = 0;
            for (auto it = begin(factories); it != end(factories); it++) {
                balance += (it->second).getNumberOfCyborgs() * ((it->second).getOwner());
            }
            for (auto it = begin(troops); it != end(troops); it++) {
                balance += (it->getAmount()) * (it->getOwner());
            }
            return balance;
        }

        void clearContent() {
            bombs.clear();
            troops.clear();
            commands.clear();
            factories.clear();
        }

        Factory *getFactory(int id) {
            return &factories[id];
        }

        std::vector<Link> getAllLinks() {
            return links;
        }

        std::vector<Factory *> getEveryFactory() {
            std::vector<Factory *> v;
            for (auto it = begin(factories); it != end(factories); it++) {
                v.push_back(&(it->second));
            }
            return v;
        }

        void makeTemporaryTroop(int id, int from, int to, int amount, int turns) {
            //void addTroop(int i, int a1, int a2, int a3, int a4, int a5) {
            addTroop(id, Heuristic::Player::Us, from, to, amount, turns);
        }

        void deleteTemporaryTroops(int k) {
            //cerr << "The size of the troops is " << troops.size() << endl;
            for (auto it = begin(troops); it != end(troops); it++) {
                /*cerr << "Ongoing.. ";
                cerr << "The id of the observed troops is " << it->getId() << endl;*/
                if (it->getId() == k) {
                    troops.erase(it);
                    break;
                }
            }
        }

        Factory *evacuateFrom(Factory *f);
    };
}

class MyProgram : public Player {
private:
    bool bombPredictionExist = false;
    int bombPredictionId = true;
    int bombPredictionTurns = 0;
    int track = 0;
    Heuristic::Table table;

public:
    virtual bool Setup(std::string) override final;
    virtual std::string GetResponse(std::string) override final;
};

#endif // MYPROGRAM_HPP

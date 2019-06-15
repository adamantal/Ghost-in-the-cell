#include "RandomPlayer.hpp"

#include <map>
#include <set>
#include <sstream>

bool RandomPlayer::setup(std::string setupString) {
    return true;
}

std::string RandomPlayer::getResponse(std::string inputString) {
    std::stringstream ss(inputString);
    int entityCount; // the number of entities (e.g. factories and troops)
    ss >> entityCount;

    std::map<int, int> myFactoriesIdUnit;
    std::set<int> otherFactories;

    for (int i = 0; i < entityCount; i++) {
        int entityId;
        std::string entityType;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        ss >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5;
        if (entityType == "FACTORY") {
            if (arg1 == 1) {
                myFactoriesIdUnit[entityId] = arg2;
            } else {
                otherFactories.insert(entityId);
            }
        }
    }

    std::stringstream output;

    for (auto const& [key, val] : myFactoriesIdUnit) {
        if (otherFactories.empty()) {
            break;
        }
        if (val >= 3) {
            auto k = otherFactories.rbegin();
            output << "MOVE " << key << " " << *k << " " << val << "\n";
        }
    }
    return output.str();
}
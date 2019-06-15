#include "Board.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <random>
#include <sstream>
#include <iostream>

#include "src/Objects/Stream/EntityWriter.hpp"
#include "src/Objects/Stream/InitStringBuilder.hpp"

std::string Board::getInitializationInput() const {
    InitStringBuilder builder(factories.size(), links.size());
    for (const LinkConstPtr &link : links) {
        builder.addLink(link);
    }
    return builder.build();
}

void Board::moveEntities() {
    for (TroopPtr &troop : troops) {
        troop->move();
    }
    for (BombPtr &bomb : bombs) {
        bomb->move();
    }
}

std::string Board::getInputForOwner(Owner owner) const {
    std::stringstream output;
    output << (factories.size() + troops.size() + bombs.size()) << "\n";
    for (const FactoryPtr &factory : factories) {
        output << EntityWriter::write(factory, owner) << "\n";
    }
    for (const TroopPtr &troop : troops) {
        output << EntityWriter::write(troop, owner) << "\n";
    }
    for (const BombPtr &bomb : bombs) {
        output << EntityWriter::write(bomb, owner) << "\n";
    }
    return output.str();
}

void Board::produceNewCyborgs() {
    for (const FactoryPtr &factory : factories) {
        factory->produceNewCyborgs();
    }
}

void Board::solveBattles() {
    // filter arriving troops
    std::list<TroopPtr> arrivedTroops;
    std::copy_if(troops.begin(), troops.end(), std::back_inserter(arrivedTroops),
                 [](const TroopPtr &troop) { return troop->getTurns() == 0; });
    if (arrivedTroops.empty()) {
        return;
    }

    // collect troops by target factory
    std::map<FactoryPtr, std::list<TroopPtr>> arrives;
    for (const TroopPtr &arrivedTroop : arrivedTroops) {
        arrives[arrivedTroop->getTarget()].push_back(arrivedTroop);
    }

    // resolve battles:
    for (auto const&[factory, troops] : arrives) {
        unsigned int player1Troops = std::accumulate(troops.begin(), troops.end(), 0,
                                                     [](unsigned int sum, const TroopPtr &troop) {
                                                         return (troop->getOwner() == Player1) ? sum +
                                                                                                 troop->getCyborgs()
                                                                                               : sum;
                                                     });
        unsigned int player2Troops = std::accumulate(troops.begin(), troops.end(), 0,
                                                     [](unsigned int sum, const TroopPtr &troop) {
                                                         return (troop->getOwner() == Player2) ? sum +
                                                                                                 troop->getCyborgs()
                                                                                               : sum;
                                                     });
        if (player1Troops == player2Troops)
            continue;

        if (player1Troops != 0 && player2Troops != 0) {
            unsigned int minValue = std::min(player1Troops, player2Troops);
            player1Troops -= minValue;
            player2Troops -= minValue;
        }

        Owner winnerOwner = (player1Troops != 0) ? Player1 : Player2;
        unsigned int winnerTroops = (player1Troops != 0) ? player1Troops : player2Troops;
        if (factory->getOwner() == winnerOwner) {
            factory->troopsArrived(winnerTroops);
        } else {
            unsigned int cyborgs = factory->getCyborgs();
            if (cyborgs >= winnerTroops) {
                factory->decreaseCyborgs(winnerTroops);
            } else {
                factory->decreaseCyborgs(cyborgs);
                winnerTroops -= cyborgs;

                factory->takeOver(winnerTroops, winnerOwner);
            }
        }
    }
}

void Board::explodeBombs() {
    if (!bombs.empty()) {
        // filter arrived bombs
        std::list<BombPtr> arrivedBombs;
        std::copy_if(bombs.begin(), bombs.end(), std::back_inserter(arrivedBombs),
                     [](const BombPtr &bomb) { return bomb->getTurns() == 0; });
        if (arrivedBombs.empty()) {
            return;
        }

        std::for_each(arrivedBombs.begin(), arrivedBombs.end(),
                      [](const BombPtr &bomb) { bomb->getTarget()->bombExploded(); });
    }
}

bool Board::checkWinningCondition() const {
    unsigned int player1score = 0;
    unsigned int player2score = 0;

    for (const FactoryPtr &factory : factories) {
        if (factory->getOwner() == Player1) {
            player1score += factory->getCyborgs();
        } else {
            player2score += factory->getCyborgs();
        }
    }
    for (const TroopPtr &troop : troops) {
        if (troop->getOwner() == Player1) {
            player1score += troop->getCyborgs();
        } else {
            player2score += troop->getCyborgs();
        }
    }

    if (player1score == 0 || player2score == 0) {
        Owner endangeredPlayer = (player1score == 0) ? Player1 : Player2;
        unsigned int production = std::accumulate(factories.begin(), factories.end(), 0,
                                                  [](unsigned int sum, const FactoryPtr &factory) {
                                                      return sum + factory->getProduction();
                                                  });
        if (production == 0) {
            // Game over
            std::cout << "The game is over for " << (endangeredPlayer ? "Player1" : "Player2") << ". The table for him: " << std::endl;
            std::cout << getInputForOwner(endangeredPlayer);
            return true;
        }
    }
    return false;
}

BoardPtr Board::createDefault() {
    return createRandom(0);
}

void Board::digestOwnerOutput(std::string output, Owner owner) {
    std::stringstream ss(output);
    while (!ss.eof()) {
        std::string command;
        ss >> command;
        if (command == "WAIT") {
            continue;
        } else if (command == "MOVE") {
            Id originId, targetId;
            unsigned int number;
            ss >> originId >> targetId >> number;
            for (const FactoryPtr &factory : factories) {
                if (factory->getId() == originId) {
                    if (factory->getOwner() == owner) {
                        FactoryPtr targetFactory = nullptr;
                        for (const FactoryPtr &possibleTarget : factories) {
                            if (possibleTarget->getId() == targetId) {
                                targetFactory = possibleTarget;
                                break;
                            }
                        }
                        if (targetFactory != nullptr) {
                            TroopPtr newTroop =
                                    std::make_shared<Troop>(nextId(),
                                                            owner,
                                                            factory,
                                                            targetFactory,
                                                            factory->getPosition().distance(
                                                                    targetFactory->getPosition()) / 800,
                                                            number);
                            troops.push_back(newTroop);
                        }
                    }
                    break;
                }
            }
        } else if (command == "BOMB") {
            //TODO implement these
        } else if (command == "INC") {

        } else if (command == "MSG") {

        }
    }
}

BoardPtr Board::createRandom() {
    std::random_device dev;
    return createRandom(dev());
}

BoardPtr Board::createRandom(int seed) {
    std::cout << "Populating Board object" << std::endl;

    std::mt19937 rng(seed);
    BoardPtr board = std::make_shared<Board>();

    std::uniform_int_distribution<std::mt19937::result_type> factoryDist(MIN_FACTORY_COUNT, MAX_FACTORY_COUNT);
    unsigned int factoryCount = factoryDist(rng);

    // factoryCount must be odd
    if (factoryCount % 2 == 0) {
        factoryCount++;
    }

    unsigned int FACTORY_RADIUS = factoryCount > 10 ? 600 : 700;
    int minSpaceBetweenFactories = 2 * (FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES);

    Position middle(WIDTH / 2, HEIGHT / 2);
    board->factories.push_back(
            std::make_shared<Factory>(nextId(), Owner::Neutral, middle, 0, 0));

    std::uniform_int_distribution<std::mt19937::result_type> widthDist(FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES,
                                                                       WIDTH / 2 - FACTORY_RADIUS +
                                                                       EXTRA_SPACE_BETWEEN_FACTORIES);
    std::uniform_int_distribution<std::mt19937::result_type> heightDist(FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES,
                                                                        HEIGHT - FACTORY_RADIUS +
                                                                        EXTRA_SPACE_BETWEEN_FACTORIES);
    std::uniform_int_distribution<std::mt19937::result_type> productionDist(MIN_PRODUCTION_RATE, MAX_PRODUCTION_RATE);
    std::uniform_int_distribution<std::mt19937::result_type> firstUnitDist(PLAYER_INIT_UNITS_MIN,
                                                                           PLAYER_INIT_UNITS_MAX);

    std::cout << "Factory count determined" << std::endl;

    for (Id i = nextId(); i < factoryCount - 1; i = nextId()) {
        bool valid;
        Position pos(WIDTH + 1, HEIGHT + 1);
        do {
            valid = true;
            pos = Position(widthDist(rng), heightDist(rng));
            for (const FactoryPtr &factory : board->factories) {
                if (factory->getPosition().distance(pos) < minSpaceBetweenFactories) {
                    valid = false;
                    break;
                }
            }
        } while (!valid);

        if (pos.getX() == WIDTH + 1) {
            throw "Position couldn't be determined";
        }

        unsigned int productionRate = productionDist(rng);
        Position counterPos(WIDTH - pos.getX(), HEIGHT - pos.getY());
        if (i == 1) {
            unsigned int firstUnitCount = firstUnitDist(rng);
            board->factories.push_back(
                    std::make_shared<Factory>(i, Owner::Player1, pos, firstUnitCount, productionRate));
            board->factories.push_back(
                    std::make_shared<Factory>(nextId(), Owner::Player2, counterPos, firstUnitCount, productionRate));
        } else {
            std::uniform_int_distribution<std::mt19937::result_type> unitDist(0, 5 * productionRate);
            unsigned int unitCount = unitDist(rng);
            board->factories.push_back(
                    std::make_shared<Factory>(i, Owner::Neutral, pos, unitCount, productionRate));
            board->factories.push_back(
                    std::make_shared<Factory>(nextId(), Owner::Neutral, counterPos, unitCount, productionRate));

        }
    }
    std::cout << "Factories generated" << std::endl;

    unsigned int totalProductionRate = std::accumulate(board->factories.begin(), board->factories.end(), 0,
                                                       [](unsigned int sum, FactoryPtr factory) {
                                                           return sum + factory->getProduction();
                                                       });

    // Make sure that the initial accumulated production rate for all the factories is at least MIN_TOTAL_PRODUCTION_RATE
    for (const FactoryPtr &factory : board->factories) {
        if (totalProductionRate >= MIN_TOTAL_PRODUCTION_RATE) {
            break;
        }
        if (factory->getProduction() < MAX_PRODUCTION_RATE) {
            factory->increaseProductionDuringSetup();
            totalProductionRate++;
        }
    }
    std::cout << "Total production verified" << std::endl;

    for (unsigned int i = 0; i < board->factories.size(); i++) {
        for (unsigned int j = i + 1; j < board->factories.size(); j++) {
            const FactoryPtr &factory1 = board->factories[i];
            const FactoryPtr &factory2 = board->factories[j];
            board->links.push_back(
                    std::make_shared<const Link>(
                            factory1->getPosition().distance(factory2->getPosition()),
                            factory1,
                            factory2));
        }
    }
    std::cout << "Links added" << std::endl;

    std::cout << "Board has been successfully populated" << std::endl;

    return board;
}

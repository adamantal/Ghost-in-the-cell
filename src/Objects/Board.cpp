#include "Board.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <random>
#include <sstream>

#include "src/Objects/Stream/EntityWriter.hpp"
#include "src/Objects/Stream/InitStringBuilder.hpp"

std::string Board::getInitializationInput() const {
    InitStringBuilder builder(factories.size(), links.size());
    for (const LinkPtr& link : links) {
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
            return true;
        }
    }
    return false;
}

BoardPtr Board::createDefault() {
    return createRandom(0);
}

void Board::digestOwnerOutput(std::string output, Owner owner) {
    // TODO implement this
}

BoardPtr Board::createRandom() {
    std::random_device dev;
    return createRandom(dev());
}

BoardPtr Board::createRandom(int seed) {
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
    board->factories.push_back(std::make_shared<Factory>(0, Owner::Neutral, middle, 0, 0));

    std::uniform_int_distribution<std::mt19937::result_type> widthDist(FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES,
            WIDTH / 2 - FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES);
    std::uniform_int_distribution<std::mt19937::result_type> heightDist(FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES,
            HEIGHT - FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES);
    std::uniform_int_distribution<std::mt19937::result_type> productionDist(MIN_PRODUCTION_RATE, MAX_PRODUCTION_RATE);

    unsigned short i = 0;
    while (i < factoryCount - 1) {
        Position pos(widthDist(rng), heightDist(rng));
        bool valid = true;
        for (const FactoryPtr& factory : board->factories) {
            if (factory->getPosition().distance(pos) < minSpaceBetweenFactories) {
                valid = false;
                break;
            }
        }

        if (valid) {
            unsigned int productionRate = productionDist(rng);
            if (i == 1) {
                int unitCount;
                if (customInitialUnitCount != null && customInitialUnitCount >= PLAYER_INIT_UNITS_MIN
                    && customInitialUnitCount <= PLAYER_INIT_UNITS_MAX) {
                    unitCount = customInitialUnitCount;
                } else {
                    unitCount = PLAYER_INIT_UNITS_MIN + random.nextInt(PLAYER_INIT_UNITS_MAX - PLAYER_INIT_UNITS_MIN + 1);
                }
                this.factories[i++] = new Factory(players[0], x, y, unitCount, productionRate);
                this.factories[i++] = new Factory(players[1], WIDTH - x, HEIGHT - y, unitCount, productionRate);
            } else {
                int unitCount = random.nextInt(5 * productionRate + 1);
                this.factories[i++] = new Factory(null, x, y, unitCount, productionRate);
                this.factories[i++] = new Factory(null, WIDTH - x, HEIGHT - y, unitCount, productionRate);
            }
        }
    }

    // TODO implement this
    return board;
}

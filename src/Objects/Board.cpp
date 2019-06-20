#include "Board.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <random>
#include <sstream>

#include "spdlog/spdlog.h"

#include "Test/TestUtils.hpp" // TODO remove this

#include "Objects/Stream/EntityWriter.hpp"
#include "Objects/Stream/InitStringBuilder.hpp"

std::string Board::GetInitializationInput() const {
    InitStringBuilder builder(factories.size(), links.size());
    for (const LinkConstPtr &link : links) {
        builder.AddLink(link);
    }
    return builder.Build();
}

void Board::MoveEntities() {
    for (TroopPtr &troop : troops) {
        troop->Move();
    }
    for (BombPtr &bomb : bombs) {
        bomb->Move();
    }
}

std::string Board::GetInputForOwner(Owner owner) const {
    std::stringstream output;
    output << (factories.size() + troops.size() + bombs.size()) << "\n";
    for (const FactoryPtr &factory : factories) {
        output << EntityWriter::Write(factory, owner) << "\n";
    }
    for (const TroopPtr &troop : troops) {
        output << EntityWriter::Write(troop, owner) << "\n";
    }
    for (const BombPtr &bomb : bombs) {
        output << EntityWriter::Write(bomb, owner) << "\n";
    }
    return output.str();
}

void Board::ProduceNewCyborgs() {
    for (const FactoryPtr &factory : factories) {
        factory->ProduceNewCyborgs();
    }
}

void Board::SolveBattles() {
    if (troops.empty()) {
        return;
    }

    // filter arriving troops
    std::list<TroopPtr> arrivedTroops;
    {
        std::list<TroopPtr>::iterator troopIt = troops.begin();
        while (troopIt != troops.end()) {
            TroopPtr troop = *troopIt;
            if (troop->GetTurns() == 0) {
                arrivedTroops.push_back(*troopIt);
                troopIt = troops.erase(troopIt);
            } else {
                troopIt++;
            }
        }
    }

    if (arrivedTroops.empty()) {
        return;
    }

    // collect troops by target factory
    std::map<FactoryPtr, std::list<TroopPtr>> arrives;
    for (const TroopPtr &arrivedTroop : arrivedTroops) {
        arrives[arrivedTroop->GetTarget()].push_back(arrivedTroop);
    }

    // resolve battles:
    for (auto const&[factory, troops] : arrives) {
        unsigned int player1Troops = std::accumulate(troops.begin(), troops.end(), 0,
                                                     [](unsigned int sum, const TroopPtr &troop) {
                                                         return (troop->GetOwner() == Player1) ? sum +
                                                                                                 troop->GetCyborgs()
                                                                                               : sum;
                                                     });
        unsigned int player2Troops = std::accumulate(troops.begin(), troops.end(), 0,
                                                     [](unsigned int sum, const TroopPtr &troop) {
                                                         return (troop->GetOwner() == Player2) ? sum +
                                                                                                 troop->GetCyborgs()
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
        if (factory->GetOwner() == winnerOwner) {
            factory->TroopsArrived(winnerTroops);
        } else {
            unsigned int cyborgs = factory->GetCyborgs();
            if (cyborgs >= winnerTroops) {
                factory->DecreaseCyborgs(winnerTroops);
            } else {
                factory->DecreaseCyborgs(cyborgs);
                winnerTroops -= cyborgs;

                factory->TakeOver(winnerTroops, winnerOwner);
            }
        }
    }
}

void Board::ExplodeBombs() {
    if (!bombs.empty()) {
        // filter arrived bombs
        std::list<BombPtr> arrivedBombs;
        std::copy_if(bombs.begin(), bombs.end(), std::back_inserter(arrivedBombs),
                     [](const BombPtr &bomb) { return bomb->GetTurns() == 0; });
        if (arrivedBombs.empty()) {
            return;
        }

        std::for_each(arrivedBombs.begin(), arrivedBombs.end(),
                      [](const BombPtr &bomb) { bomb->GetTarget()->BombExploded(); });
    }
}

bool Board::CheckWinningCondition() const {
    unsigned int player1score = 0;
    unsigned int player2score = 0;

    for (const FactoryPtr &factory : factories) {
        if (factory->GetOwner() == Player1) {
            player1score += factory->GetCyborgs();
        } else if (factory->GetOwner() == Player2) {
            player2score += factory->GetCyborgs();
        }
    }
    for (const TroopPtr &troop : troops) {
        if (troop->GetOwner() == Player1) {
            player1score += troop->GetCyborgs();
        } else {
            player2score += troop->GetCyborgs();
        }
    }

    if (player1score == 0 || player2score == 0) {
        Owner endangeredPlayer = (player1score == 0) ? Player1 : Player2;
        unsigned int production = std::accumulate(factories.begin(), factories.end(), 0,
                                                  [endangeredPlayer] (unsigned int sum, const FactoryPtr &factory) {
                                                      return (factory->GetOwner() == endangeredPlayer) ? sum +
                                                                                                         factory->GetProduction()
                                                                                                       : sum;
                                                  });
        if (production == 0) {
            // Game over
            SPDLOG_INFO("The game is over for {}. The table is the following:\n{}.",
                endangeredPlayer ? "Player1" : "Player2",
                GetInputForOwner(endangeredPlayer));
            return true;
        }
    }
    return false;
}

BoardPtr Board::CreateDefault() {
    return CreateRandom(0);
}

void Board::DigestOwnerOutput(std::string output, Owner owner) {
    std::stringstream ss(output);
    std::string item;
    while (std::getline(ss, item, ';')) {
        std::string command;
        std::stringstream line(item);
        line >> command;
        if (command == "WAIT") {
            continue;
        } else if (command == "MOVE") {
            Id originId, targetId;
            unsigned int number;
            line >> originId >> targetId >> number;
            for (const FactoryPtr &factory : factories) {
                if (factory->GetId() == originId) {
                    if (factory->GetOwner() == owner) {
                        FactoryPtr targetFactory = nullptr;
                        for (const FactoryPtr &possibleTarget : factories) {
                            if (possibleTarget->GetId() == targetId) {
                                targetFactory = possibleTarget;
                                break;
                            }
                        }
                        if (targetFactory != nullptr) {
                            TroopPtr newTroop =
                                    std::make_shared<Troop>(NextId(),
                                                            owner,
                                                            factory,
                                                            targetFactory,
                                                            factory->GetPosition().Distance(
                                                                    targetFactory->GetPosition()) / 800,
                                                            number);
                            troops.push_back(newTroop);
                            factory->DecreaseCyborgs(number);
                        }
                    }
                    break;
                }
            }
        } else if (command == "BOMB") {
            // TODO implement these
        } else if (command == "INC") {
            // TODO implement these
        } else if (command == "MSG") {
            // TODO implement these
        }
    }
}

BoardPtr Board::CreateRandom() {
    std::random_device dev;
    return CreateRandom(dev());
}

BoardPtr Board::CreateRandom(int seed) {
    SPDLOG_INFO("populating Board object");

    std::mt19937 rng(seed);
    BoardPtr board = std::make_shared<Board>();

    std::uniform_int_distribution<std::mt19937::result_type> factoryDist(MIN_FACTORY_COUNT, MAX_FACTORY_COUNT);
    unsigned int factoryCount = factoryDist(rng);

    // factoryCount must be odd
    if (factoryCount % 2 == 0) {
        factoryCount++;
    }

    unsigned int FACTORY_RADIUS = factoryCount > 10 ? 600 : 700;
    unsigned int minSpaceBetweenFactories = 2 * (FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES);

    Position middle(WIDTH / 2, HEIGHT / 2);
    board->factories.push_back(
            std::make_shared<Factory>(NextId(), Owner::Neutral, middle, 0, 0));

    std::uniform_int_distribution<std::mt19937::result_type> widthDist(FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES,
                                                                       WIDTH / 2 - FACTORY_RADIUS +
                                                                       EXTRA_SPACE_BETWEEN_FACTORIES);
    std::uniform_int_distribution<std::mt19937::result_type> heightDist(FACTORY_RADIUS + EXTRA_SPACE_BETWEEN_FACTORIES,
                                                                        HEIGHT - FACTORY_RADIUS +
                                                                        EXTRA_SPACE_BETWEEN_FACTORIES);
    std::uniform_int_distribution<std::mt19937::result_type> productionDist(MIN_PRODUCTION_RATE, MAX_PRODUCTION_RATE);
    std::uniform_int_distribution<std::mt19937::result_type> firstUnitDist(PLAYER_INIT_UNITS_MIN,
                                                                           PLAYER_INIT_UNITS_MAX);

    SPDLOG_DEBUG("factory count determined");

    for (Id i = NextId(); i < factoryCount - 1; i = NextId()) {
        bool valid;
        Position pos(WIDTH + 1, HEIGHT + 1);
        do {
            valid = true;
            pos = Position(widthDist(rng), heightDist(rng));
            for (const FactoryPtr &factory : board->factories) {
                if (factory->GetPosition().Distance(pos) < minSpaceBetweenFactories) {
                    valid = false;
                    break;
                }
            }
        } while (!valid);

        if (pos.GetX() == WIDTH + 1) {
            throw "Position couldn't be determined";
        }

        unsigned int productionRate = productionDist(rng);
        Position counterPos(WIDTH - pos.GetX(), HEIGHT - pos.GetY());
        if (i == 1) {
            unsigned int firstUnitCount = firstUnitDist(rng);
            board->factories.push_back(
                    std::make_shared<Factory>(i, Owner::Player1, pos, firstUnitCount, productionRate));
            board->factories.push_back(
                    std::make_shared<Factory>(NextId(), Owner::Player2, counterPos, firstUnitCount, productionRate));
        } else {
            std::uniform_int_distribution<std::mt19937::result_type> unitDist(0, 5 * productionRate);
            unsigned int unitCount = unitDist(rng);
            board->factories.push_back(
                    std::make_shared<Factory>(i, Owner::Neutral, pos, unitCount, productionRate));
            board->factories.push_back(
                    std::make_shared<Factory>(NextId(), Owner::Neutral, counterPos, unitCount, productionRate));

        }
    }
    SPDLOG_DEBUG("factories generated");

    unsigned int totalProductionRate = std::accumulate(board->factories.begin(), board->factories.end(), 0,
                                                       [](unsigned int sum, FactoryPtr factory) {
                                                           return sum + factory->GetProduction();
                                                       });

    // Make sure that the initial accumulated production rate for all the factories is at least MIN_TOTAL_PRODUCTION_RATE
    for (const FactoryPtr &factory : board->factories) {
        if (totalProductionRate >= MIN_TOTAL_PRODUCTION_RATE) {
            break;
        }
        if (factory->GetProduction() < MAX_PRODUCTION_RATE) {
            factory->IncreaseProductionDuringSetup();
            totalProductionRate++;
        }
    }
    SPDLOG_DEBUG("total production verified");

    for (unsigned int i = 0; i < board->factories.size(); i++) {
        for (unsigned int j = i + 1; j < board->factories.size(); j++) {
            const FactoryPtr &factory1 = board->factories[i];
            const FactoryPtr &factory2 = board->factories[j];
            board->links.push_back(
                    std::make_shared<const Link>(
                            factory1->GetPosition().Distance(factory2->GetPosition()),
                            factory1,
                            factory2));
        }
    }
    SPDLOG_DEBUG("links added");
    SPDLOG_INFO("Board has been successfully populated");

    return board;
}

BoardMetrics Board::GetBoardMetrics() const {
    unsigned int score1 = 0, score2 = 0, production1 = 0, production2 = 0;
    for (FactoryConstPtr factory : factories) {
        if (factory->GetOwner() == Owner::Player1) {
            score1 += factory->GetCyborgs();
            production1 += factory->GetProduction();
        } else if (factory->GetOwner() == Owner::Player2) {
            score2 += factory->GetCyborgs();
            production2 += factory->GetProduction();
        }
    }
    for (TroopConstPtr troop : troops) {
        if (troop->GetOwner() == Owner::Player1) {
            score1 += troop->GetCyborgs();
        } else if (troop->GetOwner() == Owner::Player2) {
            score2 += troop->GetCyborgs();
        }
    }
    return BoardMetrics(score1, score2, production1, production2);
}

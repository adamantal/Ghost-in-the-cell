#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include<string>
#include<memory>

class Player;
typedef std::shared_ptr<Player> PlayerPtr;

class Player {
public:
    virtual bool setup(std::string) = 0;
    virtual std::string getResponse(std::string input) = 0;
};

#endif // PLAYER_HPP_INCLUDED

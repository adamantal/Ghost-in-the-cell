#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include<string>
#include<memory>

class Player;
typedef std::shared_ptr<Player> PlayerPtr;

class Player {
public:
    virtual bool Setup(std::string) = 0;
    virtual std::string GetResponse(std::string) = 0;
};

#endif // PLAYER_HPP_INCLUDED

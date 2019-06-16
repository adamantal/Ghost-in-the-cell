#include "Owner.hpp"

Owner OtherPlayer(Owner owner) {
    if (owner == Player1) {
        return Player2;
    } else if (owner == Player2) {
        return Player1;
    } else {
        throw "OtherPlayed called on non player Owner!";
    }
}

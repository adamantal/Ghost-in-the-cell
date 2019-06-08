#ifndef TROOP_HPP_INCLUDED
#define TROOP_HPP_INCLUDED

#include "MovingEntity.hpp"

class Troop: public MovingEntity {
	private:
		unsigned int number;
		unsigned int remainingTurns;
	public:
    Troop(int i, int a1, int a2, int a3, int a4, int a5):
        MovingEntity(i,a1,a2,a3),number(a4),remainingTurns(a5){}
    int getTime() {
        if (remainingTurns == 0){
            throw "Error: Troop with id " + to_string(getId()) + " has 0 remaining turns left.\n";
        }
        return remainingTurns;
    }
    int getAmount(){
        return number;
    }
};

#endif // TROOP_HPP_INCLUDED

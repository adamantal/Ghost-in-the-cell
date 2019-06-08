#ifndef FACTORY_HPP_INCLUDED
#define FACTORY_HPP_INCLUDED

#include "Entity.hpp"

class Factory : public Entity {
	private:
		unsigned int cyborgs;
		unsigned short production;
		unsigned short badturns;

	public:
		Factory(int i, int a1, int a2, int a3, int a4):
			Entity(i,a1),cyborgs(a2),production(a3),badturns(a4){}
		int getNumberOfCyborgs() const {
			return cyborgs;
		}
		int getProduction() const {
			return production;
		}
		int getNetProductionAtRound(int k) const {
			if (k < badturns){
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
            if (n <= getNumberOfCyborgs()) {
                cyborgs -= n;
            } else {
                throw (std::string("Invalid decrease of cyborgs from") + to_string(getNumberOfCyborgs()) + " by " + to_string(n) + " at factory " + to_string(id));
            }
		}
		void increaseNumberOfCyborgs(int n) {
			cyborgs += n;
		}
};

#endif // FACTORY_HPP_INCLUDED

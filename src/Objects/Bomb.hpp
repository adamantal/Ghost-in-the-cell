#ifndef BOMB_HPP_INCLUDED
#define BOMB_HPP_INCLUDED

class Bomb : public MovingEntity {
	private:
     //note that the target is not known, if it is hostile
		unsigned int remainingTurns;

	public:
		Bomb(int i, int a1, int a2, int a3, int a4):
			MovingEntity(i,a1,a2,a3), remainingTurns(a4){}
    int getTarget(){
      if (getOwner() == Player::Enemy){
        throw "Error: you want to get a not known target!\n";
      } else {
        return target;
      }
    }
    int getTime(){
      return remainingTurns;
    }
};

#endif // BOMB_HPP_INCLUDED

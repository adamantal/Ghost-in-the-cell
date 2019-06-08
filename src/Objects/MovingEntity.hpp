#ifndef MOVINGENTITY_HPP_INCLUDED
#define MOVINGENTITY_HPP_INCLUDED

class MovingEntity : public Entity {
  protected:
    int from;
    int target;

  public:
    MovingEntity(int i, int a1, int a2, int a3):
        Entity(i,a1),from(a2),target(a3){}
    int getTarget(){
        return target;
    }
    int getFrom(){
        return from;
    }
};

#endif // MOVINGENTITY_HPP_INCLUDED

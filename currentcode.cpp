#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

enum Player{Us=1, Neutral=0, Enemy=-1};

//enum Action{MOVE, BOMB, WAIT, MSG};

struct Command{
    string type;
    vector<int> parameters;
    Command(string t, vector<int> p):type(t),parameters(p){}
};

class Entity{
  protected:
    int id;
    Player owner;
  public:
    Entity(){}
    Entity(int a1, int a2):id(a1),owner(Player(a2)){}
    Player getOwner()const {
      return owner;
    }
    int getId(){
      return id;
    }
};

class Factory: public Entity{
	private:
		int cyborgs;
		int production;
		int badturns;
	public:
    Factory(){}
		Factory(int i, int a1, int a2, int a3, int a4):
			Entity(i,a1),cyborgs(a2),production(a3),badturns(a4){}
		int getNumberOfCyborgs()const{
			return cyborgs;
		}
		int getProduction()const{
			return production;
		}
		int getNetProductionAtRound(int k) const {
			if (k <= badturns){
				return 0;
			} else {
				return production;
			}
		}
		bool isnormal() const{
			return badturns == 0 ? true : false;
		}
		int turnsToNormal()const{
			return badturns;
		}
		void decreaseNumberOfCyborgs(int n){
			cyborgs -= n;
		}
		void increaseNumberOfCyborgs(int n){
			cyborgs += n;
		}
};
class Troop: public Entity{
	private:
		int from;
		int target;
		int number;
		int remainingTurns;
	public:
		Troop(){}
		Troop(int i, int a1, int a2, int a3, int a4, int a5):
			Entity(i,a1),from(a2),target(a3),number(a4),remainingTurns(a5){}
		int getTarget(){
			return target;
		}
		int getTime(){
      if (remainingTurns == 0){
        cout << "Remaining Turns is zero -- from: " << to_string(from) << ", target: " << to_string(target) << ", number: " << to_string(number);
        throw "err";
      }
			return remainingTurns;
		}
		int getAmount(){
			return number;
		}
};
class Bomb: public Entity{
	private:
		int from;
		int target; //note that it is known, if it is hostile
		int remainingTurns;
	public:
		Bomb(){}
		Bomb(int i, int a1, int a2, int a3, int a4):
			Entity(i,a1), from(a2), target(a3), remainingTurns(a4){}
		int getFrom(){
			return from;
		}
    int getTime(){
      return remainingTurns;
    }
};

struct Link{
	public:
	int dist;
	int fac1;
	int fac2;
	Link(int d, int a1, int a2):dist(d),fac1(a1),fac2(a2){}
	int whichIs(int k){
		if (fac1 == k) {
			return 1;
		} else if (fac2 == k){
			return 2;
		} else {
			return 0;
		}
	}
	bool either(int k){
		return (fac1 == k) || (fac2 == k);
	}
	int other(int k)const{
		if (k == fac1) {
			return fac2;
		} else if (k == fac2){
			return fac1;
		} else {
			throw "Others have bad pointer";
		}
	}
	bool operator<(const Link& rhs)const{
		return dist < rhs.dist;
	}
	bool operator==(const Link& rhs)const{
		return (dist == rhs.dist && fac1 == rhs.fac1 && fac2 == rhs.fac2);
	}
	int get1()const{
		return fac1;
	}
	int get2()const{
		return fac2;
	}
	int getDist() const{
		return dist;
	}
};

class Table{
    private:
      //main things:
      map<int,Factory> factories; //id-Factory mapping
      vector<Troop> troops;
      vector<Bomb> bombs;

      vector<Link> links; //distances

      vector<Command> commands;

      unsigned short mybombs = 2;
    public:
		Table(){}
		void addFactory(int i, int a1, int a2, int a3, int a4) {
			Factory tmp(i,a1, a2, a3, a4);
			factories[i] = tmp;
		}
		void addTroop(int i, int a1, int a2, int a3, int a4, int a5) {
			Troop tmp(i,a1, a2, a3, a4, a5);
			troops.push_back(tmp);
		}
		void addBomb(int i, int a1, int a2, int a3, int a4) {
			Bomb tmp(i,a1, a2, a3, a4);
			bombs.push_back(tmp);
		}
		void addLink(int i1, int i2, int i3) {
			Link tmp(i1, i2,i3);
			links.push_back(tmp);
		}
        int bombProcedure(){
			return -1;
		}
		int isAlwaysOwnedByMe();
		void writeAllTheLinks(int k){
			if (k == 3) {
				for (auto it = begin(links); it != end(links); it++){
					cerr << "[" << it->get1() << " " << it->get2() << " " << it->getDist() << "]" << endl;
				}
			}
		}
		vector<Factory> ourFactories(){
			vector<Factory> returnable;
			for (auto it = begin(factories); it != end(factories); it++) {
				if (((*it).second).getOwner() == 1) {
					returnable.push_back(it -> second);
				}
			}
			return returnable;
		}
		double getHeuristicValue(Factory* f){
			double k = 0.0;
			k += double(f->getProduction()) - f->getNumberOfCyborgs();
			return k;
		}
    double getHeuristicValueFromId(int id, Factory* targ){
			double k = 0.0;
			k +=  double(targ->getProduction())*(double(targ->getOwner()) * double(getDistance(id, targ->getId()))) - double(targ->getNumberOfCyborgs()) - double(getDistance(id, targ->getId()));
			return k;
		}
    map<double, vector<Factory*> > attackableTargets(){ //targetProduction x targets structure
  		map<double, vector<Factory*> > ret;
  		for (auto it = begin(factories); it != end(factories); it++) {
  			if ((it->second).getOwner() != Player::Us) {
  				ret[getHeuristicValue(&(*it).second)].push_back(&(it->second));
  			}
  		}
  		return ret;
		}
    map<double, vector<Factory*> > attackableTargetsFrom(int id){ //targetProduction x targets structure
  		map<double, vector<Factory*> > ret;
  		for (auto it = begin(factories); it != end(factories); it++) {
  			if ((it->second).getOwner() != Player::Us) {
  				ret[getHeuristicValueFromId(id,&(*it).second)].push_back(&(it->second));
  			}
  		}
  		return ret;
		}
		vector<Factory*> getNeighbors(int id){
			vector<Factory*> ret = getEveryFactory();
			for (auto it = begin(ret); it != end(ret); it ++){
				if ((*it)->getId() == id){
					ret.erase(it);
					break;
				}
			}
			return ret;
		}
		int getDistance(int id1, int id2){
			if (id1 == id2){
				cout << id1 << " ";
				throw "ids are the same, it is very bad: " + id1;
			}
			for (auto it = begin(links); it != end(links); it++) {
				if (it->either(id1) && it-> either(id2)) {
					return it->dist;
				}
			}
			throw "";
		}
		void sendTroop(Factory* from, int target, int amount){
			addTroop(999,1,from->getId(),target,amount,getDistance(from->getId(),target));
			from->decreaseNumberOfCyborgs(amount);
			vector<int> v = {from->getId(), target, amount};
			command("MOVE",v);
		}
		void command(string t, vector<int> params){
			Command tmp(t,params);
			commands.push_back(tmp);
		}
    void writeCommands(){
			if (commands.size() == 0) std::cout << "WAIT";
			else {
				for (unsigned int i = 0; i < commands.size(); i++){
					cout << commands[i].type << " ";
					for (unsigned int j = 0; j < commands[i].parameters.size() - 1; j++){
						cout << commands[i].parameters[j] << " ";
					}
					cout << commands[i].parameters[commands[i].parameters.size()-1];
					if (i != commands.size() - 1) {
						cout << ";";
					}
				}
			}
		}
		void endTurn(){
			cerr << "end";
			cout << endl;
		}
		bool hostileBombExist(){
			if (bombs.size() == 0) return false;
			for (auto it = begin(bombs); it != end(bombs);it++){
				if (it->getOwner() == Player::Enemy) return true;
			}
			return false;
		}
		vector<Factory*> getEveryFactory(){
			vector<Factory*> neighbors;
			for (map<int,Factory>::iterator it = factories.begin(); it != factories.end(); it++){ //instead of this, we should use iterator
				Factory* tmp = &it->second;
				neighbors.push_back(tmp);
			}
			/*for (auto it = begin(factories); it != end(factories);it++) {
			}*/
			return neighbors;
		}
		Bomb getBomb() {
			return bombs[bombs.size()-1];
		}

		vector<int> getEstimatedCyborgs(int id) { // positive is ours, negative is not ours
      //initialised timeline
      vector<int> timeline;
      for (int i = 0; i < 20; i++) timeline.push_back(0);
      timeline[0] = factories[id].getNumberOfCyborgs();

      if (factories[id].getOwner() != Player::Neutral){
        for (auto troopit = begin(troops); troopit != end(troops); troopit++){
          if (troopit->getTime() >= 20){ cout << "Uhh;"; cerr << "Uhh;";}
          if (troopit->getTarget() == id){
            int t = troopit->getAmount();
            if (troopit->getOwner() == Player::Us) {
              timeline[troopit->getTime()] += t;
            } else {
              int g = troopit->getTime();
              timeline[g] += t;
            }
          }
        }
        for (int i = 1; i < 20; i++){
          if (timeline[i-1] >= 0) {
            timeline[i] += timeline[i-1] + factories[id].getNetProductionAtRound(i);
          } else {
            timeline[i] += timeline[i-1] - factories[id].getNetProductionAtRound(i);
          }
        }
      } else {
        bool isNeutral = true;
        vector<int> estimate;
        for (int i = 0; i < 20; i++) estimate.push_back(0);

        for (auto troopit = begin(troops); troopit != end(troops); troopit++){
          if (troopit->getTime() >= 20){ cout << "Uhh;"; cerr << "Uhh;";}
          if (troopit->getTarget() == id){
            int t = troopit->getAmount();
            if (troopit->getOwner() == Player::Us) {
              estimate[troopit->getTime()] += t;
            } else {
              int g = troopit->getTime();
              estimate[g] += t;
            }
          }
        }
        for (int i = 1; i < 20; i++) {
          if (isNeutral) {
            if (estimate[i] > 0) {
              timeline[i] = timeline[i-1] + estimate[i];
              if (timeline[i] > 0) {
                isNeutral = false;
              }
            }else {
              timeline[i] = timeline[i-1] - estimate[i];
              if (timeline[i] > 0) {
                isNeutral = false;
                timeline[i] *= -1;
              }
            }
          } else {
            if (timeline[i-1] >= 0) {
              timeline[i] += timeline[i-1] + factories[id].getNetProductionAtRound(i) + estimate[i];
            } else {
              timeline[i] += timeline[i-1] - factories[id].getNetProductionAtRound(i) + estimate[i];
            }
          }
        }
      }
      return timeline;
		}
		int firstBadRound(int id) {
      getEstimatedCyborgs(id);
			vector<int> timel = getEstimatedCyborgs(id);
			for (int i = 0; i < timel.size(); i++) {
				if (timel[i] < 0) return i;
			}
			return 21;
		}
    bool isSecured(int id){
      int c = firstBadRound(id);
      if (c > 20) {
        return true;
      }
      return false;
    }
		int minRequired(int id){
			return -getEstimatedCyborgs(id)[firstBadRound(id)];
		}
		void clearContent(int i){
			if (i <= 0) {
  			bombs.clear();
  			troops.clear();
  			commands.clear();
  			factories.clear();
			} else {
        cout << "1";
				bombs.clear();
				cout << "2";
				troops.clear();
				cout << "3";
				commands.clear();
				cout << "4";
				factories.clear();
			}
		}
		Factory* getFactory(int id){
			return &factories[id];
		}
		vector<Link> getAllLinks(){
			return links;
		}
};


int main()
{
    int factoryCount; // the number of factories
    cin >> factoryCount; cin.ignore();
    int linkCount; // the number of links between factories
    cin >> linkCount; cin.ignore();

    Table table;
    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        cin >> factory2 >> distance >> factory1; cin.ignore();
        table.addLink(factory1, factory2, distance);
        //cerr << "[" << factory1 << " " << factory2 << " " << distance << "]"<<endl;
    }
    //table.writeAllTheLinks(3);
    bool bombPredictionExist = false;
    int bombPredictionId = true;
    int bombPredictionTurns = 0;

    // game loop
    int track = 0;

    while (1) {
        int entityCount; // the number of entities (e.g. factories and troops)
        cin >> entityCount; cin.ignore();
        //initializing table:
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            int arg5;
            cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5; cin.ignore();
            if (entityType == "FACTORY") {
      				table.addFactory(entityId, arg1, arg2, arg3, arg4);
      			} else if (entityType == "TROOP") {
      				table.addTroop(entityId, arg1, arg2, arg3, arg4, arg5);
      			} else if (entityType == "BOMB") {
      				table.addBomb(entityId, arg1, arg2, arg3, arg4);
      			} else {
      				cout << "ERROR: UNKNOWN ENTITY TYPE";
      			}
        }

        //cout << "MSG 1;";

        /*vector<int> v = table.getEstimatedCyborgs(1);
        for (int i = 0; i < 20; i ++) std::cout << v[i] << endl;
        std::cout << "END" << endl;
        */
        //set up bomb processor
    if (!table.hostileBombExist() && bombPredictionExist) {
      cout << "MSG NOTANYMORE;";
			bombPredictionExist = false;
			bombPredictionId = -1;
      bombPredictionTurns = 0;
		}
    if (table.hostileBombExist() && !bombPredictionExist) {
      cout << "MSG NEWBOMBDETECTED;";
			//set bomb to the most
			map<int, int> m; //num of cyborgs - id map
			Bomb b = table.getBomb();

      vector<Factory> ours = table.ourFactories();
      int maxid = -1;
      int maxvalue = -1;

      for (auto it = begin(ours); it != end(ours); it++) {
        if (it->getNumberOfCyborgs() > maxvalue) {
          maxvalue = it->getNumberOfCyborgs();
          maxid = it->getId();
        }
      }

			//choose max, and set
			bombPredictionExist = true;
			bombPredictionId = maxid;
      bombPredictionTurns = table.getDistance(bombPredictionId, b.getFrom());
		}
		if (bombPredictionExist){
      cout << "MSG BOMBEXIST;";
			Bomb b = table.getBomb(); // Entity(i,a1),from(a2),target(a3),number(a4),remainingTurns(a5){}
			table.addTroop(10000,-1,b.getFrom(),bombPredictionId,max((table.getFactory(bombPredictionId)->getNumberOfCyborgs())/2,10),bombPredictionTurns);
			for (int i = 1; i < 6; i++){
				table.addTroop(10000 + i,-1,b.getFrom(),bombPredictionId,table.getFactory(bombPredictionId)->getProduction(),bombPredictionTurns + i);
			}
      bombPredictionTurns--;
		}

    //First we want to defend our troops:

    vector<Factory> ours = table.ourFactories();
    map<int,vector<Factory> > priorhelp; //Prioritized map of our endangered factories
    /*for (int i = 0; i < 4; i ++){
			vector<Factory*> t;
			priorhelp[i] = t;
		}*/

    for (auto it = begin(ours); it != end(ours); it++) {
      int k = (*it).getId();
			if (it->getId() != 0 && !table.isSecured(k)) {
				priorhelp[(*it).getProduction()].push_back(*it);
			}
		}
		for (int i = 3; i >= 0; i--){
			for (auto it = begin(priorhelp[i]); it != end(priorhelp[i]); it++) {
				vector<Factory*> c = table.getNeighbors((*it).getId());
				for (auto itc = begin(c); itc != end(c); itc++) {
					if ((*itc)->getId() == (*it).getId()) std::cerr << "AJJAJ";
					if ((*itc)->getOwner() == 1) {
						try {
							table.sendTroop(*itc,(*it).getId(),min(table.minRequired((*it).getId()),(*itc)->getNumberOfCyborgs()));
						} catch (char const * k) {
							std::cerr << k;
						}
					}
				}
			}
		}
    //cout << "MSG 3;";
    //then conquer new ones:

    for (auto it = begin(ours); it != end(ours); it++){
      if (table.isSecured((*it).getId())){
        map<double, vector<Factory*> > att = table.attackableTargetsFrom(it->getId());
        for (auto i = att.rbegin(); i != att.rend(); i++){
    		  for (auto ita = begin(att[i->first]); ita != end(att[i->first]); ita++){
    				int j = 0;
    				for (; j < (*it).getNumberOfCyborgs();j++){
    					(*it).decreaseNumberOfCyborgs(j);
    					if(!table.isSecured(it->getId())) {
    						break;
    					}
              vector<int> k = table.getEstimatedCyborgs((*ita)->getId());
              if (k[table.getDistance(it->getId(),(*ita)->getId())] > 0) {
                break;
              }
    					(*it).increaseNumberOfCyborgs(j);
    				}
    				j -= 1;
    				if (j != 0 && j != -1) {
    					try {
    						table.sendTroop(&(*it),(*ita)->getId(),j); //Factory* from, int target, int amount
    					} catch (char const * k){
    						std::cerr << k;
    					}
    				}
    			}
    		}
    	}
    }
    //cout << "MSG 4;";
    table.writeCommands();
    table.clearContent(0);
    track++;
    table.endTurn();
  }
}

#ifdef DONT_COMPILE

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
		unsigned int cyborgs;
		unsigned short production;
		unsigned short badturns;
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
			if (k < badturns){
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
      //cerr << "Decreasing num of cyb at factory " << id << " from " << to_string(getNumberOfCyborgs()) << " by " << n << endl;
      if (n <= getNumberOfCyborgs()) {
			   cyborgs -= n;
      } else {
        throw (std::string("Invalid decrease of cyborgs from") + to_string(getNumberOfCyborgs()) + " by " + to_string(n) + " at factory " + to_string(id));
      }
		}
		void increaseNumberOfCyborgs(int n){
      //cerr << "Increaseing num of cyb at factory " << id << " from " << to_string(getNumberOfCyborgs()) << " by " << n << endl;
			cyborgs += n;
		}
};
class MovingEntity: public Entity{
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
class Troop: public MovingEntity{
	private:
		unsigned int number;
		unsigned int remainingTurns;
	public:
		Troop(int i, int a1, int a2, int a3, int a4, int a5):
			MovingEntity(i,a1,a2,a3),number(a4),remainingTurns(a5){}
		int getTime(){
      if (remainingTurns == 0){
        throw "Error: Troop with id " + to_string(getId()) + " has 0 remaining turns left.\n";
      }
			return remainingTurns;
		}
		int getAmount(){
			return number;
		}
};
class Bomb: public MovingEntity{
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
      //cerr << "The id of the troop is " << i << endl;
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
    int averageDistance(){
      int counter = 0;
      double avg = 0;
      for (auto it = begin(links); it != end(links); it++){
        avg = (avg * double(counter) + double(it->getDist())) / double(++counter);
      }
      return avg;
    }
		vector<Factory*> ourFactories(){
			vector<Factory*> returnable;
			for (auto it = begin(factories); it != end(factories); it++) {
				if (((*it).second).getOwner() == 1) {
					returnable.push_back(&(it -> second));
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
      k -= getDistance(id,targ->getId());
      if (targ->getOwner() != Player::Enemy){
        k += 4.0;
      }
      k += targ->getProduction()*2;
      k -= targ->getNumberOfCyborgs()*0.4;

			//k +=  double(targ->getProduction())*(double(targ->getOwner()) / double(getDistance(id, targ->getId()))) - double(targ->getNumberOfCyborgs());
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
  			if ((it->second).getOwner() != Player::Us && (it->second).getId() != id) {
  				ret[getHeuristicValueFromId(id,&(*it).second)].push_back(&(it->second));
  			}
  		}
  		return ret;
		}
		int getDistance(int id1, int id2){
			if (id1 == id2){
				cout << id1 << " " << id2 << " are the same! :( ";
				throw "ids are the same, it is very bad: " + to_string(id1);
			}
			for (auto it = begin(links); it != end(links); it++) {
				if (it->either(id1) && it-> either(id2)) {
					return it->dist;
				}
			}
      cout << "1: " << id1 << ", 2: " << id2 << ".";
			throw "Some bad id-s are given!";
		}
		void sendTroop(Factory* from, int target, int amount){
      if (amount != 0) {
        //cerr << "SENT from " <<from->getId() << " to " << target << ", " << amount << " number of troops" << endl;
    		addTroop(999,1,from->getId(),target,amount,getDistance(from->getId(),target));
    		from->decreaseNumberOfCyborgs(amount);
    		vector<int> v = {from->getId(), target, amount};
    		command("MOVE",v);
      }
		}
    bool searchForNotCommandedFactory(int k){
      for (auto it = begin(commands); it != end(commands); it++){
        if (it->type == "MOVE"){
          if (it->parameters[0] == k){
            return false;
          }
        }
      }
      return true;
    }
    bool doWeHaveBombs() {
      return mybombs > 0;
    }
    bool ourBombIsEnRoute(){
      for (auto it = begin(bombs); it != end(bombs); it++){
        if (it->getOwner() == Player::Us) {
          return true;
        }
      }
      return false;
    }
    void decreaseNumOfBombs() {
      mybombs--;
    }
    void sendBomb(int from, int target) {
      vector<int> v = {from, target};
      command("BOMB",v);
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
		Bomb getOneBomb() {
      for (auto it = begin(bombs); it != end(bombs); it++) {
        if (it->getOwner() == Player::Enemy) {
          return *it;
        }
      }
      throw "No enemy bomb was found!";
		}
    void cerrHeurValueFrom(int id){
      for (auto it = begin(factories); it != end(factories); it++) {
        if (it->first != id) {
          cerr << "(id: " << it->first << ",val:" << getHeuristicValueFromId(id, &(it->second)) << ") ";
        }
      }
    }
    vector<int> getEstimatedCyborgsFromZeroTime(int id, int zerotime) { // positive is ours, negative is not ours
      //initialised timeline
      vector<int> timeline, troopline;
      for (int i = 0; i < 20; i++) timeline.push_back(0);
      for (int i = 0; i < 20; i++) troopline.push_back(0);

      if (factories[id].getOwner() != Player::Us) {
        timeline[0] = -1 * zerotime;
      }
      if (factories[id].getOwner() == Player::Us) {
        timeline[0] = zerotime;
      }

      for (auto troopit = begin(troops); troopit != end(troops); troopit++){
        if (troopit->getTime() > 20){ cout << "Uhh;"; cerr << "Uhh;";}
        if (troopit->getTarget() == id){
          int t = troopit->getAmount();
          if (troopit->getOwner() == Player::Us) {
            troopline[troopit->getTime()] += t;
          } else {
            troopline[troopit->getTime()] -= t;
          }
        }
      }

      Player currentowner = factories[id].getOwner();
      int currentamount = timeline[0];
      for (int i = 1; i < 20; i++){
        timeline[i] = timeline[i-1] + int(currentowner) * factories[id].getNetProductionAtRound(i);

        if (currentowner == Player::Neutral) {
          if (troopline[i] > 0) {
            timeline[i] += troopline[i];
            if (timeline[i] > 0) {
              currentowner == Player::Us;
            }
          } else if (troopline[i] < 0) {
            timeline[i] -= troopline[i];
            if (timeline[i] > 0) {
              timeline[i] *= -1;
              currentowner == Player::Enemy;
            }
          }
        } else if (currentowner == Player::Us) {
          timeline[i] += troopline[i];
          if (timeline[i] < 0) {
            currentowner = Player::Enemy;
          }
        } else if (currentowner == Player::Enemy) {
          timeline[i] += troopline[i];
          if (timeline[i] > 0) {
            currentowner = Player::Enemy;
          }
        }
      }
      return timeline;
		}
		vector<int> getEstimatedCyborgs(int id) { // positive is ours, negative is not ours
      //initialised timeline
      vector<int> timeline, troopline;
      for (int i = 0; i < 20; i++) timeline.push_back(0);
      for (int i = 0; i < 20; i++) troopline.push_back(0);

      if (factories[id].getOwner() != Player::Us) {
        timeline[0] = -1 * int(factories[id].getNumberOfCyborgs());
      }
      if (factories[id].getOwner() == Player::Us) {
        timeline[0] = factories[id].getNumberOfCyborgs();
      }

      for (auto troopit = begin(troops); troopit != end(troops); troopit++){
        if (troopit->getTime() > 20){ cout << "Uhh;"; cerr << "Uhh;";}
        if (troopit->getTarget() == id){
          int t = troopit->getAmount();
          if (troopit->getOwner() == Player::Us) {
            troopline[troopit->getTime()] += t;
          } else {
            troopline[troopit->getTime()] -= t;
          }
        }
      }

      Player currentowner = factories[id].getOwner();
      int currentamount = timeline[0];
      for (int i = 1; i < 20; i++){
        timeline[i] = timeline[i-1] + int(currentowner) * factories[id].getNetProductionAtRound(i);

        if (currentowner == Player::Neutral) {
          if (troopline[i] > 0) {
            timeline[i] += troopline[i];
            if (timeline[i] > 0) {
              currentowner == Player::Us;
            }
          } else if (troopline[i] < 0) {
            timeline[i] -= troopline[i];
            if (timeline[i] > 0) {
              timeline[i] *= -1;
              currentowner == Player::Enemy;
            }
          }
        } else if (currentowner == Player::Us) {
          timeline[i] += troopline[i];
          if (timeline[i] < 0) {
            currentowner = Player::Enemy;
          }
        } else if (currentowner == Player::Enemy) {
          timeline[i] += troopline[i];
          if (timeline[i] > 0) {
            currentowner = Player::Enemy;
          }
        }
      }
      return timeline;
		}

		int firstBadRound(int id) {
			vector<int> timel = getEstimatedCyborgs(id);
			for (unsigned int i = 0; i < timel.size(); i++) {
				if (timel[i] < 0) return i;
			}
			return -1;
		}
    bool isSecured(int id) {
      vector<int> timel = getEstimatedCyborgs(id);
      /*for (auto it = begin(timel); it != end(timel); it++) cerr << *it << " ";
      cerr << endl;*/
      if (timel[19] > 0) return true;
      return false;
    }
    bool isSecuredFromZero(int id, int zeroturn) {
      vector<int> timel = getEstimatedCyborgsFromZeroTime(id,zeroturn);
      /*for (auto it = begin(timel); it != end(timel); it++) cerr << *it << " ";
      cerr << endl;*/
      for (int i = 0; i < timel.size(); i++) {
        if (timel[i] < 0) return false;
      }
      return true;
    }
		int minRequired(int id){
      if (firstBadRound(id) == -1) return 0;
			return -getEstimatedCyborgs(id)[firstBadRound(id)];
		}
    int netAllCyborgs() {
      int balance = 0;
      for (auto it = begin(factories); it != end(factories); it++) {
        balance += (it->second).getNumberOfCyborgs() * ((it->second).getOwner());
      }
      for (auto it = begin(troops); it != end(troops); it++) {
        balance += (it->getAmount()) * (it->getOwner());
      }
      return balance;
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
    vector<Factory*> getEveryFactory(){
      vector<Factory*> v;
      for (auto it = begin(factories); it != end(factories); it++){
        v.push_back(&(it->second));
      }
      return v;
    }
    void makeTemporaryTroop(int id, int from, int to, int amount, int turns){
      //void addTroop(int i, int a1, int a2, int a3, int a4, int a5) {
      addTroop(id, Player::Us, from, to, amount, turns);
    }
    void deleteTemporaryTroops(int k){
      //cerr << "The size of the troops is " << troops.size() << endl;
      for (auto it = begin(troops); it != end(troops); it++) {
        /*cerr << "Ongoing.. ";
        cerr << "The id of the observed troops is " << it->getId() << endl;*/
        if (it->getId() == k) {
          troops.erase(it);
          break;
        }
      }
    }
    Factory* evacuateFrom(Factory* f) {
      Factory* closestid = nullptr;
      int closestvalue = 99;
      for (auto it = begin(factories); it != end(factories); it++) {
        if (it->second.getId() != f->getId()) {
          if (getDistance((it->second).getId(),f->getId()) < closestvalue) {
            closestvalue = getDistance((it->second).getId(),f->getId());
            closestid = &it->second;
          }
        }
      }
      return closestid;
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
    }
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

        vector<int> v = table.getEstimatedCyborgs(1);
        for (int i = 0; i < 20; i ++) cerr << v[i] << " ";
        cerr << ";";


        //table.cerrHeurValueFrom(1);



    //set up bomb processor
    if (!table.hostileBombExist() && bombPredictionExist) {
      //cout << "MSG NOTANYMORE;";
			bombPredictionExist = false;
			bombPredictionId = -1;
      bombPredictionTurns = 0;
		}
    if (table.hostileBombExist() && !bombPredictionExist) {
      //cout << "MSG NEWBOMBDETECTED;";
			//set bomb to the most
			map<int, int> m;
			Bomb b = table.getOneBomb();

      vector<Factory*> ours = table.ourFactories();
      int maxid = -1;
      int maxvalue = -1;

      for (auto it = begin(ours); it != end(ours); it++) {
        if ((*it)->getNetProductionAtRound(0) > maxvalue && b.getFrom() != (*it)->getId()) {
          maxvalue = (*it)->getNetProductionAtRound(0);
          maxid = (*it)->getId();
        }
      }

			//choose max, and set
			bombPredictionExist = true;
			bombPredictionId = maxid;
      bombPredictionTurns = table.getDistance(bombPredictionId, b.getFrom());
		}
		if (bombPredictionExist){
      if (bombPredictionTurns != 0) {
        //cout << "MSG BOMBEXIST;";

        //MY SECOND, IMPROVED IDEA:
        Factory* from = table.getFactory(bombPredictionId);
        if (bombPredictionTurns == 1 && from->getOwner() == Player::Us) {
          Factory* to = table.evacuateFrom(from);
          if (from != nullptr && to != nullptr) {
            table.sendTroop(from, to->getId(), from->getNumberOfCyborgs());
          }
        }


        /// THIS WAS MY PRIMAL IDEA:
        /*
        Bomb b = table.getOneBomb(); // Entity(i,a1),from(a2),target(a3),number(a4),remainingTurns(a5){}
  			table.addTroop(10000,-1,b.getFrom(),bombPredictionId,max((table.getFactory(bombPredictionId)->getNumberOfCyborgs())/2,10),bombPredictionTurns);
  			for (int i = 1; i < 6; i++){
  				table.addTroop(10000 + i,-1,b.getFrom(),bombPredictionId,table.getFactory(bombPredictionId)->getProduction(),bombPredictionTurns + i);
  			}
        */

        bombPredictionTurns--;
      }
		}


    //First we want to defend our troops:
    vector<Factory*> ours = table.ourFactories();
    map<int,vector<Factory> > priorhelp; //Prioritized map of our endangered factories
    /*for (int i = 0; i < 4; i ++){
			vector<Factory*> t;
			priorhelp[i] = t;
		}*/

    for (auto it = begin(ours); it != end(ours); it++) {
      int k = (*it)->getId();
			if (!table.isSecured(k)) {
				priorhelp[(*it)->getProduction()].push_back(*(*it));
			}
		}
    //writing out
    int summ = 0;
    for (auto it = begin(priorhelp); it != end(priorhelp); it++) summ += it->second.size();
    cerr << "Must defend " << summ << " of our troops." << endl;

		for (int i = 3; i >= 0; i--){
			for (auto it = begin(priorhelp[i]); it != end(priorhelp[i]); it++) {
				vector<Factory*> c = table.getEveryFactory();
				for (auto itc = begin(c); itc != end(c); itc++) {
					if ((*itc)->getId() != (*it).getId()) {
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
		}
    //improve?
    //TODO: DO IMPROVE
    if (table.netAllCyborgs() > 0) {
      vector<Factory*> fs = table.getEveryFactory();
      for (auto it = begin(fs); it != end(fs); it++){
        if ((*it)->getOwner() == Player::Us && (*it)->getProduction() != 3 && (*it)->getNumberOfCyborgs() >= 10 && table.isSecured((*it)->getId())) {
          vector<int> params = {(*it)->getId()};
          table.command("INC", params);
        }
      }
    }

    //then conquer new ones:
    //vector<int> k = table.getEstimatedCyborgs(7);
    /*cerr << "THE VECTOR: ";
    for (auto itveck = begin(k); itveck != end(k); itveck++) cerr << *itveck << " ";
    cerr << "END "<< endl;*/

    for (auto it = begin(ours); it != end(ours); it++){
      if (table.isSecured((*it)->getId())){
        map<double, vector<Factory*> > att = table.attackableTargetsFrom((*it)->getId());
        for (auto i = att.rbegin(); i != att.rend(); i++){
    		  for (auto ita = begin(att[i->first]); ita != end(att[i->first]); ita++){
            //cerr << "attackable id: " << (*ita)->getId() << endl;
    				int j = 1;
            const int safeId = 11234;
    				for (; j < (*it)->getNumberOfCyborgs();j++) {
              //cerr << j << "cycle" << endl;
    					(*it)->decreaseNumberOfCyborgs(j);
              table.makeTemporaryTroop(safeId,(*it)->getId(), (*ita)->getId(), j, table.getDistance((*it)->getId(),(*ita)->getId()));

    					if(!table.isSecuredFromZero((*it)->getId(), (*it)->getNumberOfCyborgs() - j)) {
                //cerr << "broken bc not secured" << endl;
                if (j == 1) j = 0;
    						break;
    					}
              vector<int> k = table.getEstimatedCyborgs((*ita)->getId());
              //cerr << "THE VECTOR: ";
              //for (auto itveck = begin(k); itveck != end(k); itveck++) cerr << *itveck << " ";
              //cerr << "END "<< endl;

              //cerr << "Value of cybs in the jth round at attackable:" << k[table.getDistance((*it)->getId(),(*ita)->getId())] << endl;
              if (k[table.getDistance((*it)->getId(),(*ita)->getId())] > 0) {
                //cerr << "broken bc already sent enough troops" << endl;
                break;
              }
    					(*it)->increaseNumberOfCyborgs(j);
              table.deleteTemporaryTroops(safeId);
    				}
            (*it)->increaseNumberOfCyborgs(j);
            table.deleteTemporaryTroops(safeId);
            //cerr << "j is " << j << " after the loop." << endl;
    				if (j >= 1) {
              try {
    						table.sendTroop(&(*(*it)),(*ita)->getId(),j);
              } catch (const string k) {
                cerr << k << endl;
              }
    				}
    			}
    		}
    	}
    }

    //sending bombs:
    if (table.doWeHaveBombs() && !table.ourBombIsEnRoute()) {
      vector<Factory*> all = table.getEveryFactory();
      for (auto it = begin(all); it != end(all); it++){
        if ((*it)->getOwner() == Player::Us && table.searchForNotCommandedFactory((*it)->getId())) {
          int maxenem = -1, maxamount = -1;
          for (auto enem = begin(all); enem != end(all); enem++) {
            if ((*enem)->getOwner() == Player::Enemy) {
              if (maxamount < (*enem)->getNetProductionAtRound(0)) {
                maxamount = (*enem)->getNetProductionAtRound(0);
                maxenem = (*enem)->getId();
              }
            }
          }
          if (maxenem != -1) {
            table.sendBomb((*it)->getId(), maxenem);
            table.decreaseNumOfBombs();
            break;
          }
        }
      }
    }

    table.writeCommands();
    table.clearContent(0);
    track++;
    table.endTurn();
  }
}

#endif // DONT_COMPILE

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

enum EntityType{FACTORY, TROOP, BOMB};
 
struct Command{
    string type;
    vector<int> parameters;
};

class Factory{
	private:
		int id;
		Player owner;
		int cyborgs;
		int production;
		int badturns;
	public:
		Factory(){}
		Factory(int i, int a1, int a2, int a3, int a4):
			id(i),owner(Player(a1)),cyborgs(a2),production(a3),badturns(a4){}
		Player getOwner()const {
			return owner;
		}
		int getNumberOfCyborgs()const{
			return cyborgs;
		}
		int getProduction()const{
			return production;
		}
		int getNetProduction()const{
			if (badturns == 0){
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
};
class Troop{
	private:
		int id;
		Player owner;
		int from;
		int target;
		int number;
		int remainingTurns;
	public:
		Troop(){}
		Troop(int i, int a1, int a2, int a3, int a4, int a5):
			id(i),owner(Player(a1)),from(a2),target(a3),number(a4),remainingTurns(a5){}
		int getTarget(){
			return target;
		}
		Player getOwner(){
			return owner;
		}
};
class Bomb{
	private:
		int id;
		Player owner;
		int from;
		int target; //note that it is known, if it is hostile
		int remainingTurns;
	public:
		Bomb(){}
		Bomb(int i, int a1, int a2, int a3, int a4):
			id(i), owner(Player(a1)), from(a2), target(a3), remainingTurns(a4){}
		int time(){
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
};
 
class Table{
    private:
        //main things:
        map<int,Factory> factories; //id-Factory mapping
        vector<Troop> troops;
        vector<Bomb> bombs;
    
        //distances:
        vector<Link> links;
        
        vector<Command> commands;
    public:
		Table(){}
		Table(vector<Link> *l):links(*l){}
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
        int isBombAGoodIdea();
        int getResolvedNumberOfCyborg(int turn);
		int isAlwaysOwnedByMe();
        map<int,Factory*> attackableTargets(){
			map<int,Factory*> returnable;
			for (auto itl = begin(links); itl != end(links); itl++) {
				Link k = *itl;
				Factory* f1 = &factories[itl->fac1];
				Factory* f2 = &factories[itl->fac2];
				if (f1->getOwner() == 1){
					if (f2->getOwner() != 1) {
						returnable[itl->fac2] = f2;
					}
				} else {
					if (f2-> getOwner() == 1) {
						returnable[itl->fac1] = f1;
					}
				}
			}
			return returnable;
		}
        void writeCommands(){
			for (int i = 0; i < commands.size(); i++){
				cout << commands[i].type << " ";
				for (int j = 0; j < commands[i].parameters.size() - 1; j++){
					cout << commands[i].parameters[j] << " ";
				}
				cout << commands[i].parameters[commands[i].parameters.size()-1];
				if (i != commands.size() - 1) {
					cout << ";";
				}
			}
			cout << endl;
		}
		bool hostileBombExist(){
			return (bombs.size() > 0);
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
		Factory* getFactoryFromId(int id) {
			return &factories[id];
		}
		vector<int> getEstimatedCyborgs(int id) {
			int prod = factories[id].getProduction();
			int amount = factories[id].getNumberOfCyborgs();
			
			vector<int> timeline;
			timeline.push_back(amount);
			for (int i = 1; i < 20; i++) timeline.push_back(0);
			
			for (auto it = begin(troops); it < end(troops); it++) {
				if (it->getTarget() == id) {
					if (factories[id].getOwner() == it->getOwner()) {
						timeline[it->getTime()] += it->getAmount();
					} else{
						timeline[it->getTime()] -= it->getAmount();
					}
				}
				//TODOOOO: complete this
			}
		}
};
 
 
int main()
{
    int factoryCount; // the number of factories
    cin >> factoryCount; cin.ignore();
    int linkCount; // the number of links between factories
    cin >> linkCount; cin.ignore();
    
    vector<Link> links;
    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        cin >> factory1 >> factory2 >> distance; cin.ignore();
        Link tmp(factory1, factory2,distance);
        links.push_back(tmp);
    }
    
    bool bombPredictionExist = false;
    int bombPredictionId = true;
    
    // game loop
    while (1) {
		Table table(&links);
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

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        cout << "WAIT";
        
        //set up bomb processor
        if (!table.hostileBombExist() && bombPredictionExist) {
			bombPredictionExist = false;
			bombPredictionId = 0;
		}
        if (table.hostileBombExist() && !bombPredictionExist) {
			//set bomb to the most 
			map<int, int> m; //num of cyborgs - id map
			Bomb b = table.getBomb();
			for (auto itl = begin(links); itl != end(links); itl++) {
				if (itl->dist == b.time() + 1) {
					Factory* f1 = table.getFactoryFromId(itl->fac1);
					Factory* f2 = table.getFactoryFromId(itl->fac2);
					if (f1->getOwner() == 1){
						if (f2->getOwner() != 1) {
							m[f1->getNumberOfCyborgs()] = itl->fac1;
						}
					} else {
						if (f2-> getOwner() == 1) {
							m[f2->getNumberOfCyborgs()] = itl->fac2;
						}
					}
				}
			}
			
			//choose max, and set
			auto maxit = max_element(m.begin(), m.end());
			bombPredictionExist = true;
			bombPredictionId = m[maxit->second];
			
		}
        
        set<int> priortargets;
        int targetslevel = 0;        
        
        //Target prioritizations:
        vector<Factory*> fac = table.getEveryFactory();
            for (int i = 0; i < fac.size(); i++) {
                if (entityTypes[i] == "FACTORY" && arg1s[i] != +1 && arg3s[i] >= targetslevel) {
                    for (int j = 0; j < linkCount; j++) {
                        if (factory1s[j] == entityIds[i]) {
                            for (int ii = 0; ii < entityCount; ii++){
                                if (entityIds[ii] == factory2s[j]) {
                                    if (arg1s[ii] == 1) {
                                        if (arg3s[i] > targetslevel) priortargets.clear();
                                        targetslevel = arg3s[i];
                                        priortargets.insert(entityIds[i]);
                                    }
                                    break;
                                }
                            }
                        }
                        if (factory2s[j] == entityIds[i]) {
                            for (int ii = 0; ii < entityCount; ii++){
                                if (entityIds[ii] == factory1s[j]) {
                                    if (arg1s[ii] == 1) {
                                        if (arg3s[i] > targetslevel) priortargets.clear();
                                        targetslevel = arg3s[i];
                                        priortargets.insert(entityIds[i]);
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        cout << "MSG " << priortargets.size() << ";";
        
        //For each node we have, lets move our troops towards: if node has no enemy neigh -> move away, if it has, then store it to the
        
        
        for (int i = 0; i < entityCount; i++) { //iterare over our factories
            if (entityTypes[i] == "FACTORY" && arg1s[i] == 1) {
                for (int j = 0; j < linkCount; j++){  //iterate over its neighbors
                    if (factory1s[j] == entityIds[i] && entityTypes[i] == "FACTORY") {
                        for (int k = 0; k < entityCount; k++) {
                            if (entityIds[k] == factory2s[j]){
                                if (arg1s[k] == 0 && arg2s[i] > 3) {
                                    cout << ";MOVE " << entityIds[i] << " " << entityIds[k] << " " << max(3,arg2s[i]/2);
                                    arg2s[i]-=max(arg2s[i]-3,arg2s[i]/2);
                                    j = linkCount;
                                    k = entityCount;
                                }
                            }
                        }
                    }
                    if (factory2s[j] == entityIds[i]  && entityTypes[i] == "FACTORY") {
                        for (int k = 0; k < entityCount; k++) {
                            if (entityIds[k] == factory1s[j]){
                                if (arg1s[k] == 0 && arg2s[i] > 3) {
                                    cout << ";MOVE " << entityIds[i] << " " << entityIds[k] << " " << max(3,arg2s[i]/2);
                                    arg2s[i]-=max(arg2s[i]-3,arg2s[i]/2);
                                    j = linkCount;
                                    k = entityCount;
                                }
                            }
                        }
                    }
                }
            }
        }
            for (int i = 0; i < entityCount; i++) {
            if (entityTypes[i] == "FACTORY" && arg1s[i] == 1) {
                for (int j = 0; j < linkCount; j++){
                    if (factory1s[j] == entityIds[i] && entityTypes[i] == "FACTORY") {
                        for (int k = 0; k < entityCount; k++) {
                            if (entityIds[k] == factory2s[j]){
                                if (arg1s[k] == -1 && arg2s[i] > 3) {
                                    cout << ";MOVE " << entityIds[i] << " " << entityIds[k] << " " << max(3,arg2s[i]/2);
                                    arg2s[i]-=max(arg2s[i]-3,arg2s[i]/2);
                                    j = linkCount;
                                    k = entityCount;
                                }
                            }
                        }
                    }
                    if (factory2s[j] == entityIds[i]  && entityTypes[i] == "FACTORY") {
                        for (int k = 0; k < entityCount; k++) {
                            if (entityIds[k] == factory1s[j]){
                                if (arg1s[k] == -1 && arg2s[i] > 3) {
                                    cout << ";MOVE " << entityIds[i] << " " << entityIds[k] << " " << max(3,arg2s[i]/2);
                                    arg2s[i]-=max(arg2s[i]-3,arg2s[i]/2);
                                    j = linkCount;
                                    k = entityCount;
                                }
                            }
                        }
                    }
                }
        }
        }
        // Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
        cout << endl;
    }
}

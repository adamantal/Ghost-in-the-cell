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
    Command(string t, vector<int> p):type(t),parameters(p){}
};

class Factory{
	private:
		int id;
		Player owner;
		int cyborgs;
		int production;
		int badturns;
	public:
		Factory():id(0),owner(Player(0)),cyborgs(0),production(0),badturns(0){}
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
		void decreaseNumberOfCyborgs(int n){
			cyborgs -= n;
		}
		void increaseNumberOfCyborgs(int n){
			cyborgs += n;
		}
		int getId(){
			//cout << "MSG " << id << " " << owner << " " << cyborgs << " " << production << " " << badturns << ";";
			return id;
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
		int getTime(){
			return remainingTurns;
		}
		int getAmount(){
			return number;
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
		int getFrom(){
			return from;
		}
		int getTime(){
			return remainingTurns;
		}
		Player getOwner(){
			return owner;
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
    
        //distances:
        vector<Link> links;
        
        vector<Command> commands;
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
        int isBombAGoodIdea();
		int isAlwaysOwnedByMe();
		void writeAllTheLinks(){
			for (auto it = begin(links); it != end(links); it++){
				cerr << "[" << it->get1() << " " << it->get2() << " " << it->getDist() << "]" << endl;
			}
		}
		vector<Factory*> ourFactories(){
			vector<Factory*> returnable;
			for (auto it = begin(factories); it != end(factories); it++) {
				if ((&it -> second) ->getOwner() == 1) {
					returnable.push_back(&it -> second);
				}
			}
			return returnable;
		}
        map<int, map<Link,Factory*> > attackableTargets(){ //target -> link x fromOurFactory structure
			map<int, map<Link,Factory*> > ret;
			for (int i = 0; i < 4; i++){
				map<Link,Factory*> tmp;
				ret[i] = tmp;
			}
			for (auto itl = begin(links); itl != end(links); itl++) {
				Link k = *itl;
				Factory* f1 = &factories[itl->fac1];
				Factory* f2 = &factories[itl->fac2];
				if (f1->getOwner() == 1){
					if (f2->getOwner() != 1) {
						ret[f2->getProduction()][k] = f1;
					}
				} else {
					if (f2-> getOwner() == 1) {
						ret[f1->getProduction()][k] = f2;
					}
				}
			}
			return ret;
		}
		vector<Factory*> getNeighbors(int id){
			vector<Factory*> ret;
			for (auto it = begin(links); it != end(links); it++){
				if (it->either(id)) {
					ret.push_back(&factories[it->other(id)]);
				}
			}
			return ret;
		}
		int getDistance(int id1, int id2){
			if (id1 == id2) throw "ids are the same, it is very bad";
			for (auto it = begin(links); it != end(links); it++) {
				if (it->either(id1) && it-> either(id2)) {
					return it->dist;
				}
			}
			throw "";
		}
		void sendTroop(Factory* from, int target, int amount, int distance){
			addTroop(999,1,from->getId(),target,amount,distance);
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
			}
		}
		void endTurn(){
			cout << endl;
		}
		bool hostileBombExist(){
			if (bombs.size() == 0) return false;
			for (auto it = begin(bombs); it != end(bombs);it++){
				if (it->getOwner() == -1) return true;
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
			}
			for (int i = 1; i < 20; i++){
				if (timeline[i-1] >= 0) {
					timeline[i] += factories[i].getProduction();
				} else {
					timeline[i] -= factories[i].getProduction();
				}
				timeline[i] += timeline[i-1];
			}
			return timeline;
		}
		bool isSecured(int id){
			if (firstBadRound(id) == -1) return true;
			return false;
		}
		int firstBadRound(int id) {
			vector<int> timeline = getEstimatedCyborgs(id);
			for (int i = 0; i < timeline.size(); i++){
				if (timeline[i] < 0) return i;
			}
			return -1;
		}
		int minRequired(int id){
			return -getEstimatedCyborgs(id)[firstBadRound(id)];
		}
		void clearContent(int i){
			if (i <= 0) {
			bombs.clear();
			bombs.clear();
			troops.clear();
			commands.clear();
			factories.clear();
			} else {
				bombs.clear();
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
    table.writeAllTheLinks();
    bool bombPredictionExist = false;
    int bombPredictionId = true;
    
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
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        //cerr << "something";
        //set up bomb processor
        if (!table.hostileBombExist() && bombPredictionExist) {
			bombPredictionExist = false;
			bombPredictionId = 0;
		}
        if (table.hostileBombExist() && !bombPredictionExist) {
			//set bomb to the most 
			map<int, int> m; //num of cyborgs - id map
			Bomb b = table.getBomb();
			vector<Link> links = table.getAllLinks();
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
		if (bombPredictionExist){
			Bomb b = table.getBomb();
			table.addTroop(65536,-1,b.getFrom(),bombPredictionId,max((table.getFactoryFromId(bombPredictionId)->getNumberOfCyborgs())/2,10),b.time());
			for (int i = 1; i < 6; i++){
				table.addTroop(65536 + i,-1,b.getFrom(),bombPredictionId,table.getFactoryFromId(bombPredictionId)->getProduction(),b.time() + i);
			}
		}
        set<int> priortargets;
        int targetslevel = 0;
        
        //First we want to defend our troops:
        
        vector<Factory*> ours = table.ourFactories();
        map<int,vector<Factory*> > priorhelp; //Prioritized map of our endangered factories
        for (int i = 0; i < 4; i ++){
			vector<Factory*> t;
			priorhelp[i] = t;
		}
		
        cout << "MSG OK;";
        for (auto it = begin(ours); it != end(ours); it++){
			if (!table.isSecured((*it)->getId())){
				priorhelp[(*it)->getProduction()].push_back(*it);
			}
		}
		for (int i = 3; i >= 0; i--){
			for (auto it = begin(priorhelp[i]); it != end(priorhelp[i]); it++) {
				vector<Factory*> c = table.getNeighbors((*it)->getId());
				for (auto itc = begin(c); itc != end(c); itc++) {
					if ((*itc)->getOwner() == 1) {
						try {
						table.sendTroop(*itc,(*it)->getId(),min(table.minRequired((*it)->getId()),(*itc)->getNumberOfCyborgs()),table.getDistance((*itc)->getId(),(*it)->getId()));
						} catch (char const * k) {
							std:cerr << k;
						}
					}
				}				
			}
		}
        //conquer new ones
        map<int, map<Link,Factory*> > att = table.attackableTargets();
        for (int i = 3; i >= 0; i--){
			for (auto it = begin(att[i]); it != end(att[i]); it++){
				//std::cout << "(" << std::distance(begin(att[i]),it) << ")";
				//cout << it->second->getId() << " ";
				if (table.isSecured(it->second->getId())) {
					int j = 0;
					for (; j < it->second->getNumberOfCyborgs();j++){
						it->second->decreaseNumberOfCyborgs(j);
						if(!table.isSecured(it->second->getId())){
							break;
						}
						it->second->increaseNumberOfCyborgs(j);
					}
					j -= 1;
					if (j != 0 && j != -1) {
						try {
						table.sendTroop(it->second,(it->first).other(it->second->getId()),j,it->first.dist); //Factory* from, int target, int amount, const int distance
						} catch (char const * k){
							std::cerr << k;
						}
					}
				}
			}
			//cout << "i" << i;
		}
		//cout << "!";
        table.writeCommands();
        //table.writeAllTheLinks();
        table.clearContent(0);
        track++;
        table.endTurn();
    }
}

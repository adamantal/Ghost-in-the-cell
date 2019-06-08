#ifndef TABLE_HPP_INCLUDED
#define TABLE_HPP_INCLUDED

class Table {
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

#endif // TABLE_HPP_INCLUDED

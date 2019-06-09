#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include "Objects/Table.hpp"

using namespace std;

int _main()
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

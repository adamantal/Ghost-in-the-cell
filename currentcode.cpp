#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
enum Action{MOVE, BOMB, WAIT, MSG};
 
struct Command{
    Action type;
};
 
class Table{
    private:
        //main things:
        int entityCount;
        vector<int> entityIds;
        vector<string> entityTypes;
        vector<int> arg1s;
        vector<int> arg2s;
        vector<int> arg3s;
        vector<int> arg4s;
        vector<int> arg5s;
    
        //distances:
        int factoryCount;  
        int linkCount;
        vector<int> distances;
        vector<int> factory2s;
        vector<int> factory1s;
        
        vector<Command> commands;
    public:
        int isBombAGoodIdea();
        int getResolvedNumberOfCyborg(int turn);
        int isAlwaysOwnedByMe();
        set<int> iterateOverAttackableTargets();
        void writeCommands();
};
 
 
int main()
{
    int factoryCount; // the number of factories
    cin >> factoryCount; cin.ignore();
    int linkCount; // the number of links between factories
    cin >> linkCount; cin.ignore();
    vector<int> distances;
    vector<int> factory2s;
    vector<int> factory1s;
    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        cin >> factory1 >> factory2 >> distance; cin.ignore();
        factory1s.push_back(factory1);
        factory2s.push_back(factory2);
        distances.push_back(distance);
    }
    
    // game loop
    while (1) {
        int entityCount; // the number of entities (e.g. factories and troops)
        cin >> entityCount; cin.ignore();
        
        vector<int> entityIds;
        vector<string> entityTypes;
        vector<int> arg1s;
        vector<int> arg2s;
        vector<int> arg3s;
        vector<int> arg4s;
        vector<int> arg5s;
        
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            int arg5;
            cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5; cin.ignore();
            
            entityIds.push_back(entityId);
            entityTypes.push_back(entityType);
            arg1s.push_back(arg1);
            arg2s.push_back(arg2);
            arg3s.push_back(arg3);
            arg4s.push_back(arg4);
            arg5s.push_back(arg5);
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        cout << "WAIT";
        
        set<int> priortargets;
        int targetslevel = 0;
        //Target prioritizations:
        for (int i = 3; i > 0; i--) {
            for (int i = 0; i < entityCount; i++) {
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
        }
        cout << "MSG " << priortargets.size() << ";";
        
        //For each node we have, lets move our troops towards: if node has no enemy neigh -> move away, if it has, then store it to the
        
        
        for (int i = 0; i < entityCount; i++) {
            if (entityTypes[i] == "FACTORY" && arg1s[i] == 1) {
                for (int j = 0; j < linkCount; j++){
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

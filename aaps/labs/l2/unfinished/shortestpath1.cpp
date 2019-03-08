#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Dijkstra.cpp"
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    int nodes, edges, queries, startI;
    do{
        cin >> nodes;
        cin >> edges;
        cin >> queries;
        cin >> startI;
        if(nodes == 0 && edges == 0 && queries == 0 && startI == 0){
            break;
        }

        Dijkstra dijkstra;

        for(int n = 0; n < nodes; n++){
            dijkstra.addNode(n);
        }

        for(int m = 0; m < edges; m++){
            int from, to, cost;
            cin >> from;
            cin >> to;
            cin >> cost;

            dijkstra.addEdge(from, to, cost);
        }

        map<int, pair<int, Node*>> paths = dijkstra.shortest_paths(startI);
        for(int q = 0; q < queries; q++){
            int toFind;
            cin >> toFind;
            if(paths.find(toFind) != paths.end()){
                cout << paths[toFind].first << endl;
            } else{
                cout << "Impossible"<< endl;
            }
        }

        cout << endl;

    } while(nodes != 0 || edges != 0 || queries != 0 || startI != 0);
    return 0;
}

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

    int intersections, streets;

    cin >> intersections;
    cin >> streets;

    int startIntersection, endIntersection, startTime, georgeIntersections;
    cin >> startIntersection;
    cin >> endIntersection;
    cin >> startTime;
    cin >> georgeIntersections;

    vector<int> georgePath;

    for(int i = 0; i < georgeIntersections; i++){
        int in;
        cin >> in;
        georgePath.push_back(in);
    }

    Dijkstra dijkstra = Dijkstra();

    for(int i = 1; i <= intersections; i++){
        dijkstra.addNode(i);
    }

    map<pair<int, int>, int> roadToCost;
    for(int m = 0; m < streets; m++){
        int from, to, cost;
        cin >> from;
        cin >> to;
        cin >> cost;
        roadToCost[minmax(from, to)] = cost;
    }

    map<pair<int, int>, pair<int, int>> georgePathCost;
    int lastInter = georgePath[0];
    int totCost = 0;
    for(int i = 1; i < georgeIntersections; i++){
        int elem = georgePath[i];
        georgePathCost[minmax(lastInter, elem)] = pair<int, int>(totCost, roadToCost[minmax(lastInter, elem)]);
        totCost += roadToCost[minmax(lastInter, elem)];
        lastInter = elem;
    }

    for(auto roadCost: roadToCost){
        if(georgePathCost.count(roadCost.first) > 0){
            /*cout << ";;;" << endl;
            cout << georgePathCost[roadCost.first].first << endl;
            cout << georgePathCost[roadCost.first].second << endl;
            cout << max(0, georgePathCost[roadCost.first].first - startTime) << endl;
            cout << max(0, georgePathCost[roadCost.first].first + georgePathCost[roadCost.first].second - startTime) << endl;
            */
            dijkstra.addEdge(roadCost.first.first, 
                    roadCost.first.second, 
                    roadCost.second, 
                    max(0, georgePathCost[roadCost.first].first - startTime),
                    max(0, georgePathCost[roadCost.first].first + georgePathCost[roadCost.first].second - startTime),
                    true
                    );
            dijkstra.addEdge(roadCost.first.second, 
                    roadCost.first.first, 
                    roadCost.second, 
                    max(0, georgePathCost[roadCost.first].first - startTime),
                    max(0, georgePathCost[roadCost.first].first + georgePathCost[roadCost.first].second - startTime),
                    true
                    );
        } else{
            dijkstra.addEdge(roadCost.first.first, 
                    roadCost.first.second, 
                    roadCost.second
                    );
            dijkstra.addEdge(roadCost.first.second, 
                    roadCost.first.first, 
                    roadCost.second
                    );
        }
    }

    map<int, pair<int, Node*>> paths = dijkstra.shortest_paths(startIntersection);

    cout << paths[endIntersection].first << endl;

    return 0;
}

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Dijkstra.cpp"
using namespace std;

int width, height;

int nodeIndex(int w, int h){
    return w + h * width;
}

void addEdges(int w, int h, int val, Dijkstra& solver){
    int edgeCosts[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    edgeCosts[val] = 0;

    vector<tuple<int, int, int>> edgesToAdd;

    if(h > 0){
        edgesToAdd.push_back(tuple<int, int, int>(0, w, h-1));
        if(w > 0){
            edgesToAdd.push_back(tuple<int, int, int>(7, w-1, h-1));
        }
        if(w < width - 1){
            edgesToAdd.push_back(tuple<int, int, int>(1, w+1, h-1));
        }
    }

    if(h < height - 1){
        edgesToAdd.push_back(tuple<int, int, int>(4, w, h+1));
        if(w > 0){
            edgesToAdd.push_back(tuple<int, int, int>(5, w-1, h+1));
        }
        if(w < width - 1){
            edgesToAdd.push_back(tuple<int, int, int>(3, w+1, h+1));
        }
    }

    if(w > 0){
        edgesToAdd.push_back(tuple<int, int, int>(6, w-1, h));
    }
    if(w < width - 1){
        edgesToAdd.push_back(tuple<int, int, int>(2, w+1, h));
    }

    for (auto tup: edgesToAdd){
        solver.addEdge(nodeIndex(w, h), nodeIndex(get<1>(tup), get<2>(tup)), edgeCosts[get<0>(tup)]);
    }

}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> width;
    cin >> height;

    Dijkstra solver = Dijkstra();
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            solver.addNode(nodeIndex(w, h));
        }
    }

    for(int h = 0; h < height; h++){
        string in;
        cin >> in;
        for(int w = 0; w < width; w++){
            int val = in[w] - '0';

            addEdges(w, h, val, solver);
        }
    }

    int trips;
    cin >> trips;

    for(int trip = 0; trip < trips; trip++){
        int xs, ys, xe, ye;
        cin >> ys;
        cin >> xs;
        cin >> ye;
        cin >> xe;

        //cout << nodeIndex(xs-1, ys-1) << endl;
        //cout << nodeIndex(xe-1, ye-1) << endl;

        map<int, pair<int, Node*>> solved = solver.shortest_paths(nodeIndex(xs-1, ys-1), nodeIndex(xe-1, ye-1));
        //vector<Node*> path = solver.constructPath(solved[nodeIndex(xe-1, ye-1)].second);

        cout << solved[nodeIndex(xe-1, ye-1)].first << endl;

        /*for(auto elem: path){
            cout << elem->index << " - ";
        }
        cout << endl;
        cout << "---" << endl;*/

    }


    return 0;
}

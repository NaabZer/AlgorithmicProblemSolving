#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <math.h>
using namespace std;
struct Edge;
struct Node;

const int INF = 1000000;

struct Node{
    int index;
    vector<Edge*> neighbors;
    int cost;
    Node* parent;
};

struct Edge{
    Node* from;
    Node* to;
    int cost;
    int timeOne;
    int timeTwo;
};

// Comparator for node priority_queue
struct NodeCompare{
    bool operator() (pair<int, Node*> first, pair<int, Node*> second){
        return first.first > second.first;
    }
};

class Dijkstra{
    unordered_map<int, Node*> nodes;
    vector<Edge*> edges;

    public:
    Dijkstra(){}

    ~Dijkstra(){
        for(auto nodePair: nodes){
            delete nodePair.second;
        }
        for(auto edge: edges){
            delete edge;
        }
    }

    void addNode(int index){
        Node* n = new Node();
        n->index = index;
        nodes[index] = n;
    }

    void addEdge(int from, int to, int cost, int startTime, int endTime){
        Edge* e = new Edge();
        Node* fromN = nodes[from];
        Node* toN = nodes[to];

        e->from = fromN;
        e->to = toN;
        e->cost = cost;
        e->timeOne = startTime;
        e->timeTwo = endTime;

        fromN->neighbors.push_back(e);
        edges.push_back(e);
    }
    
    void addEdge(int from, int to, int cost, int startTime, int endTime, bool isClosedInterval){
        // If closed interval
        if(isClosedInterval){
            addEdge(from, to, cost, endTime, startTime);
        } else{
            addEdge(from, to, cost, startTime, endTime);
        }
    }

    void addEdge(int from, int to, int cost, int intervalTime){
        addEdge(from, to, cost, intervalTime, -1);
    }

    void addEdge(int from, int to, int cost){
        addEdge(from, to, cost, -1, -1);
    }

    map<int, pair<int, Node*>> shortest_paths(int startIndex){

        for(auto n_pair: nodes){
            n_pair.second->cost = -1;
            n_pair.second->parent = NULL;
        }

        map<int, pair<int, Node*>> ret;

        unordered_set<Node*> visited;
        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, NodeCompare> queue;

        nodes[startIndex]->cost = 0;
        queue.push(pair<int, Node*>(0, nodes[startIndex]));

        while(!queue.empty()){
            Node* elem = queue.top().second;
            queue.pop();
            if(visited.count(elem) > 0){
                continue;
            }
            visited.insert(elem);

            for(auto edge: elem->neighbors){
                Node* neighbor = edge->to;
                if(visited.count(neighbor) == 0){
                    int newCost;

                    if(edge->timeOne != -1 && edge->timeTwo == -1){
                        // If timeOne is defined while timeEnd is -1, we have an repeating "opening"
                        int nextTimeSlot = int(ceil(edge->timeOne / elem->cost)) * edge->timeOne;
                        newCost = nextTimeSlot + edge->cost;
                    } else if (edge->timeOne != -1 && edge->timeTwo != -1){
                        // If timeOne and timeTwo is defined, we have a interval
                        if(edge->timeOne < edge->timeTwo){
                            //If timeOne < timeTwo, we have an open interval (can only pass through between)
                            if(elem->cost > edge->timeTwo){
                                newCost = INF;
                            } else if (elem->cost > edge->timeOne){
                                newCost = elem->cost + edge->cost;
                            } else{
                                newCost = edge->timeOne + edge->cost;
                            }
                        } else {
                            //If timeOne > timeTwo, we have an closed interval (can NOT pass through between)
                            if(elem->cost < edge->timeOne && elem->cost > edge->timeTwo){
                                newCost = edge->timeOne + edge->cost;
                            } else{
                                newCost = elem->cost + edge->cost;
                            }
                        }
                    } else{
                        // Else we have no timeslot (any time is valid)
                        newCost = elem->cost + edge->cost;
                    }
                    if(neighbor->cost == -1 || neighbor->cost > newCost){
                        neighbor->cost = newCost;
                        neighbor->parent = elem;
                    }
                    queue.push(pair<int, Node*>(newCost, neighbor));
                }
            }

            ret[elem->index] = pair<int, Node*>(elem->cost, elem);
        }

        return ret;
    }

    vector<Node*> constructPath(Node* goalNode){
        vector<Node*> path;

        Node* curNode = goalNode;
        path.push_back(curNode);
        while(curNode->parent != NULL){
            curNode = curNode->parent;
            path.push_back(curNode);
        }

        reverse(path.begin(), path.end());
        return path;
    }

};

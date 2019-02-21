#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
using namespace std;

template<typename T>
struct Node{
    T value;
    Node* parent;
    int r;

    string toString(){
        string out = "Node: " + to_string(value) + ", Parent: " + to_string(parent->value) + ", Rank: " + to_string(r);
        return out;
    }
};

template<typename T>
struct UnionFind{
    unordered_map<T, Node<T>*> nodes;

    UnionFind(vector<T>& nodesIn){
        for(auto elem: nodesIn){
            Node<T>* node = (Node<T>*) malloc(sizeof(Node<T>*)); 
            node->value = elem;
            node->r = 0;
            nodes[elem] = node;
            nodes[elem]->parent = nodes[elem];
        }
    }

    UnionFind(int elems){
        for(int i = 1; i < elems+1; i++){
            Node<T>* node = (Node<T>*) malloc(sizeof(Node<T>*)); 
            node->value = i;
            node->r = 0;
            nodes[i] = node;
            nodes[i]->parent = nodes[i];
        }
    }


    T Find(T elem){
        if(nodes[elem]->parent != nodes[elem]){
            nodes[elem]->parent = nodes[Find(nodes[elem]->parent->value)];
        }

        return(nodes[elem]->parent->value);
    }

    bool Same(T first, T second){
        return(Find(first) == Find(second));
    }

    void Union(T first, T second){
        Node<T>* firstRoot = nodes[Find(first)];
        Node<T>* secondRoot = nodes[Find(second)];

        if(firstRoot->r < secondRoot->r){
            firstRoot->parent = secondRoot;
        } else if(firstRoot->r > secondRoot->r){
            secondRoot->parent = firstRoot;
        } else{
            firstRoot->parent = secondRoot;
            firstRoot->r++;
        }
    }

    string toString(vector<T>& nodesIn){
        for(auto elem: nodesIn){
            cout << nodes[elem]->toString() << endl;
        }
        return "";
    }
};

int main(){
    int elems, conns;
    cin >> elems;
    cin >> conns;

    UnionFind<int> UF = UnionFind<int>(elems);

    for(int c = 0; c < conns; c++){
        int a, b;
        cin >> a;
        cin >> b;
        UF.Union(a, b);
    }

    set<int> unconnected;
    int rootP = UF.Find(1);
    for(int c = 1; c < elems+1; c++){
        if(UF.Find(c) != rootP){
            unconnected.insert(c);
        }
    }

    if(unconnected.size() == 0){
        cout << "Connected" << endl;
    }else {
        for(auto elem: unconnected){
            cout << elem << endl;
        }
    }

    return 0;
}

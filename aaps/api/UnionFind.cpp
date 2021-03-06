#include <iostream>
#include <vector>
#include <string>
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

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "UnionFind.cpp"


int main(){
    ios_base::sync_with_stdio(false);
    int elems, operations;

    cin >> elems;
    cin >> operations;

    vector<int> values(elems, 0);
    for(int i = 0; i < elems; i++){
        values[i] = i;
    }

    UnionFind<int> uf = UnionFind(values);

    for(int i = 0; i < operations; i++){
        char op;
        int arg1, arg2;

        cin >> op;
        cin >> arg1;
        cin >> arg2;

        if(op == '?'){
            bool result = uf.Same(arg1, arg2);
            if(result){
                cout << "yes" << endl;
            } else{
                cout << "no" << endl;
            }
        } else{
            uf.Union(arg1, arg2);
        }

    }

    return 0;
}

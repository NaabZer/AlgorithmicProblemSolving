#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <list>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);

    int n = 0;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> leaves;
    queue<int> v;
    map<int, int> leftInV;
    vector<int> u;
    int biggestValInV = 0;

    for(int i = 1; i <= n+1; i++){
        leftInV[i] = 0;
    }

    for(int i = 1; i < n+1; i++){
        int in;
        cin >> in;
        v.push(in);
        leftInV[in]++;
        if(in > biggestValInV){
            biggestValInV = in;
        }
    }

    for(int i = 1; i <= n+1; i++){
        if(leftInV[i] == 0){
            leaves.push(i);
        }
    }

    while(!v.empty()){
        int u_elem = leaves.top();
        leaves.pop();

        if(u_elem > biggestValInV){
            cout << "Error" << endl;
            return 0;
        }

        u.push_back(u_elem);

        int v_elem = v.front();
        v.pop();
        leftInV[v_elem]--;
        if(leftInV[v_elem] == 0){
            leaves.push(v_elem);
            if(v_elem == biggestValInV){
                int i = v_elem;
                while(leftInV[i] == 0 and i > 0){
                    i--;
                }
                biggestValInV = i;
            }
        }

    }

    for(int elem: u){
        cout << elem << endl;
    }

    return 0;
}

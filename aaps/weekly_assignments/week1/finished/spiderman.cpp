#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


pair<string, int> pd[1001][40];
int moves;

pair<string, int> solve(int i, int h, vector<int> moveList){
    if(i == moves){
        if(h == 0) return pair<string, int>("", 0);
        return pair<string, int>("", -1);
    }

    if(pd[h][i].second != -2){
        return pd[h][i];
    }

    pair<string, int> down("", -1);
    if(h - moveList[i] >= 0){
        down = solve(i+1, h - moveList[i], moveList);
    }
    pair<string, int> up = solve(i+1, h + moveList[i], moveList);


    if(down.second != -1 && (down.second < up.second || up.second == -1)){
        pair<string, int> res = pair<string, int>("D" + down.first, max(h, down.second));
        pd[h][i] = res;
        return res;
    } else if(up.second != -1){
        pair<string, int> res = pair<string, int>("U" + up.first, max(h, up.second));
        pd[h][i] = res;
        return res;
    } else{
        pd[h][i] = pair<string, int>("XD", -1);;
        return pair<string, int>("XD", -1);
    }

}


int main(){
    ios_base::sync_with_stdio(false);
    int cases;

    cin >> cases;

    for(int c = 0; c < cases; c++){
        cin >> moves;
        vector<int> moveList(moves, 0);
        for(int m = 0; m < moves; m++){
            cin >> moveList[m];
        }

        for(int i = 0; i < 1001; i++){
            for(int j = 0; j < 40; j++){
                pd[i][j] = pair<string, int>("", -2);
            }
        }

        pair<string, int> solved = solve(0, 0, moveList);

        if(solved.second != -1){
            cout << solved.first << endl;
        } else{
            cout << "IMPOSSIBLE" << endl;
        }

    }
    return 0;
}

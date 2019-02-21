#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[100][8];
int priests;
int PriestPrefs[100][8];

int stateAfterMove(int state, int move){
    if(move == 0){
        if((state & 4) == 4){
            return state - 4;
        } else{
            return state + 4;
        }
    } else if(move == 1){
        if((state & 2) == 2){
            return state - 2;
        } else{
            return state + 2;
        }
    }else{
        if((state & 1) == 1){
            return state - 1;
        } else{
            return state + 1;
        }
    }
}

int solve(int state, int priest){
    if(priest == priests){
        return state;
    }
    if(dp[priest][state] != -1){
        return dp[priest][state];
    }

    int states[3];

    states[0] = solve(stateAfterMove(state, 0), priest+1);
    states[1] = solve(stateAfterMove(state, 1), priest+1);
    states[2] = solve(stateAfterMove(state, 2), priest+1);

    int bestStateNum = 0;
    int bestStateVal = -1;
    for (int i = 0; i < 3; i++){
        if(PriestPrefs[priest][states[i]] > bestStateVal){
            bestStateNum = i;
            bestStateVal = PriestPrefs[priest][states[i]];
        }
    }
    int bestState = states[bestStateNum];
    dp[priest][state] = bestState;

    return bestState;
}

string stateString(int state){
    switch(state){
        case 0: return "NNN"; 
        case 1: return "NNY";
        case 2: return "NYN";
        case 3: return "NYY";
        case 4: return "YNN";
        case 5: return "YNY";
        case 6: return "YYN";
        case 7: return "YYY";
        default: return "RIP";
    }
}

int main(){
    ios_base::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for(int c = 0; c < cases; c++){
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 8; j++){
                dp[i][j] = -1;
            }
        }

        cin >> priests;

        for(int i = 0; i < priests; i++){
            for(int j = 0; j < 8; j++){
                int in;
                cin >> in;
                PriestPrefs[i][j] = 8-in;
            }
        }

        int solvedState = solve(0, 0);
        cout << stateString(solvedState) << endl;
    }

    return 0;
}

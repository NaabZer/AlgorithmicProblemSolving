#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

// onesUsed, twosUsed, threesUsed
int dp[301][151][101]; //-1 unassigned, 1 false, 2 true

int totLen;
int totBricks, totOnes, totTwos, totThrees;
bool solved = false;


bool solve(vector<int>& bricks, int ones, int twos, int threes, int width, int curElem){
    //cout << string(ones+twos+threes, '-') << ones << ", " << twos << ", " << threes << endl;
    if(width > totLen){
        return false;
    }
    if(solved){
        return true;
    }
    if(curElem > totBricks){
        return false;
    }
    if(dp[ones][twos][threes] != -1){
        //cout << string(ones+twos+threes, '-')<< "FOUND OLD" << endl;
        return dp[ones][twos][threes] == 2;
    }

    bool rSolved = false;

    if(ones < totOnes && width + 1 == totLen){
        //cout << string(ones+twos+threes, '-')<< "SOLVED" << endl;
        solved = true;
        return true;
    } else if(ones < totOnes && bricks[curElem] != 1){
        bricks[curElem] -= 1;
        rSolved = rSolved || solve(bricks, ones+1, twos, threes, width+1, curElem);
        bricks[curElem] += 1;
    }

    if(twos < totTwos && width + 2 == totLen){
        //cout << string(ones+twos+threes, '-')<< "SOLVED" << endl;
        solved = true;
        return true;
    } else  if(twos < totTwos && bricks[curElem] == 3){
        bricks[curElem] -= 2;
        rSolved = rSolved || solve(bricks, ones, twos+1, threes, width+2, curElem);
        bricks[curElem] += 2;
    } else if(twos < totTwos && bricks[curElem] == 1 && bricks[curElem+1] != 1){
        bricks[curElem+1] -= 1;
        rSolved = rSolved || solve(bricks, ones, twos+1, threes, width+2, curElem+1);
        bricks[curElem+1] += 1;
    }

    if(threes < totThrees && width + 3 == totLen){
        //cout << string(ones+twos+threes, '-')<< "SOLVED" << endl;
        solved = true;
        return true;
    }else if(threes < totThrees && bricks[curElem] == 1 && bricks[curElem] == 3){
        bricks[curElem+1] -= 2;
        rSolved = rSolved || solve(bricks, ones, twos, threes+1, width+3, curElem+1);
        bricks[curElem+1] += 2;
    } else if(threes < totThrees && bricks[curElem] == 2 && bricks[curElem+1] != 1){
        bricks[curElem+1] -= 1;
        rSolved = rSolved || solve(bricks, ones, twos, threes+1, width+3, curElem+1);
        bricks[curElem+1] += 1;
    } else if (threes < totThrees && bricks[curElem] == 1 && bricks[curElem+1] == 1 && bricks[curElem+2] != 1){
        bricks[curElem+2] -= 1;
        rSolved = rSolved || solve(bricks, ones, twos, threes+1, width+3, curElem+2);
        bricks[curElem+2] += 1;
    }

    dp[ones][twos][threes] = rSolved ? 2 : 1;

    return rSolved || solved;
}

int main(){
    ios_base::sync_with_stdio(false);

    cin >> totBricks;
    cin >> totOnes;
    cin >> totTwos;
    cin >> totThrees;

    for(int o = 0; o <= totOnes; o++){
        for(int t = 0; t <= min(150, totTwos); t++){
            for(int th = 0; th <= min(100, totThrees); th++){
                dp[o][t][th] = -1;
            }
        }
    }
    
    vector<int> brickLens;
    for(int b = 0; b < totBricks; b++){
        int val;
        cin >> val;
        brickLens.push_back(val);
        totLen += val;
    }
    brickLens.push_back(-1);
    brickLens.push_back(-1);

    bool solved = solve(brickLens, 0, 0, 0, 0, 0);

    if(solved){
        cout << "YES" << endl;
    } else{
        cout << "NO" << endl;
    }



    return 0;
}

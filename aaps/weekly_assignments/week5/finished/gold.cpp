#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int W, H;
bool visited[50][50] = {{false}};
string Map[50];
vector<bool> availableMoves(int x, int y){
    vector<bool> ret(4, false);

    // If trap nearby, no more moves.
    if( (x != 0 && Map[y].at(x-1) == 'T') ||
        (x != W-1 && Map[y].at(x+1) == 'T') ||
        (y != 0 && Map[y-1].at(x) =='T') ||
        (y != H-1 && Map[y+1].at(x) == 'T') 
      ){
        return ret;
    }

    if(y != 0 && !visited[y-1][x] && Map[y-1].at(x) != '#' ){
        ret[0] = true;
    }
    if(x != W-1 && !visited[y][x+1] && Map[y].at(x+1) != '#' ){
        ret[1] = true;
    }
    if(y != H-1 && !visited[y+1][x] && Map[y+1].at(x) != '#' ){
        ret[2] = true;
    }
    if(x != 0 && !visited[y][x-1] && Map[y].at(x-1) != '#' ){
        ret[3] = true;
    }

    return ret;
}

int treasures = 0;

void solve(int x, int y){
    if(Map[y].at(x) == 'G'){
        treasures++;
    }
    visited[y][x] = true;

    vector<bool> moves = availableMoves(x, y);

    if(moves[0] && !visited[y-1][x]){
        solve(x, y-1);
    }
    if(moves[1] && !visited[y][x+1]){
        solve(x+1, y);
    }
    if(moves[2] && !visited[y+1][x]){
        solve(x, y+1);
    }
    if(moves[3] && !visited[y][x-1]){
        solve(x-1, y);
    }
}

int main(){
    ios_base::sync_with_stdio(false);

    cin >> W;
    cin >> H;

    W = W - 2;
    H = H - 2;


    for(int h = 0; h <= H + 2; h++){
        string in;
        cin >> in;
        if(h != 0 && h < H+1){
            Map[h-1] = in.substr(1, W);
        }
    }

    int startX, startY;
    bool found = false;
    for(int y = 0; y < H; y++){
        if(found){
            break;
        }
        for(int x = 0; x < W; x++){
            if(Map[y].at(x) == 'P'){
                startX = x;
                startY = y;
                found = true;
                break;
            }
        }
    }

    solve(startX, startY);

    cout << treasures << endl;

    return 0;
}

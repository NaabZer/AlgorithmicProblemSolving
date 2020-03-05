#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int BOARD_SIZE=8;
pair<int, int> possibleMoves[BOARD_SIZE] = {make_pair(-1, -2), make_pair(1, -2), 
                                            make_pair(2, -1), make_pair(2, 1),
                                            make_pair(-1, 2), make_pair(1, 2),
                                            make_pair(-2, -1), make_pair(-2, 1)};

bool visited[BOARD_SIZE][BOARD_SIZE];
int biggest_depth = 0;
vector<string> biggests_poss;

string posToStr(int col, int row){
    char colC = col + 'a';
    char rowC = row + '1';
    string out = string(1, colC) + string(1, rowC);
    return out;
}

void getHidingSpot(int col, int row){
    queue<tuple<int, int, int>> frontier;
    frontier.push(make_tuple(0, col, row));
    visited[col][row] = true;

    while(!frontier.empty()){
        auto elem = frontier.front();
        frontier.pop();
        int eDepth = get<0>(elem);
        int eCol = get<1>(elem);
        int eRow = get<2>(elem);

        if (eDepth > biggest_depth){
            biggest_depth = eDepth;
            biggests_poss.clear();
        }
        if (eDepth == biggest_depth){
            biggests_poss.push_back(posToStr(eCol, eRow));
        }

        for(auto move: possibleMoves){
            int nCol = eCol + move.first;
            int nRow = eRow + move.second;
            if(nCol > 7 || nCol < 0 || nRow > 7 || nRow < 0){
                continue;
            }
            if(!visited[nCol][nRow]){
                visited[nCol][nRow] = true;
                frontier.push(make_tuple(eDepth + 1, nCol, nRow));
            }
        }
    }
}


int main(){
    ios_base::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for(int c = 0; c < cases; c++){
        string pos;
        cin >> pos;
        int col;
        int row;

        col = pos[0] - 'a';
        row = pos[1] - '1';

        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                visited[i][j] = false;
            }
        }
        biggest_depth = 0;
        biggests_poss.clear();

        getHidingSpot(col, row);

        auto sortF = [](const string&  e1, const string& e2){
            if(e1[1] == e2[1]){
                return e1[0] < e2[0];
            } 
            return e1[1] > e2[1];
        };

        sort(biggests_poss.begin(), biggests_poss.end(), sortF);
        cout << biggest_depth;
        for(auto bing: biggests_poss){
            cout << " " << bing;
        }
        cout << endl;
    }
    return 0;
}

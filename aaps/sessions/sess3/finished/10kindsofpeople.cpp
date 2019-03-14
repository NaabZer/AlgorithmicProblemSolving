#include <iostream>

#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

bool area[1000][1000];
int areas[1000][1000];
int area_c = 0;
int height, width;

int solve(pair<int, int> start, pair<int, int> end){
    //cout << "end: " << end.first << ", " << end.second << endl;
    bool startVal = area[start.first][start.second];
    bool solved = false;

    set<pair<int, int>> visited;
    queue<pair<int, int>> frontier;

    frontier.push(start);

    int count = 0;
    while (frontier.size() > 0 ){//&& !solved){
        pair<int, int> front = frontier.front();
        frontier.pop();


        //cout << front.first << ", " << front.second << endl;
        if(front == end){
            solved = true;
            //break;
        }

        int y = front.first;
        int x = front.second;
        areas[y][x] = area_c;

        if(y > 0){
            pair<int, int> newPair(y-1, x);
            if (visited.count(newPair) == 0 && area[newPair.first][newPair.second] == startVal){
                frontier.push(newPair);
                visited.insert(newPair);
            }
        }
        if(y < height - 1){
            pair<int, int> newPair(y + 1, x);
            if (visited.count(newPair) == 0 && area[newPair.first][newPair.second] == startVal){
                frontier.push(newPair);
                visited.insert(newPair);
            }
        }

        if(x > 0){
            pair<int, int> newPair(y, x - 1);
            if (visited.count(newPair) == 0 && area[newPair.first][newPair.second] == startVal){
                frontier.push(newPair);
                visited.insert(newPair);
            }
        }
        if(x < width - 1){
            pair<int, int> newPair(y, x + 1);
            if (visited.count(newPair) == 0 && area[newPair.first][newPair.second] == startVal){
                frontier.push(newPair);
                visited.insert(newPair);
            }
        }
    }

    area_c++;

    if(solved && startVal){
        return 1;
    } else if(solved && !startVal){
        return 0;
    } else{
        return -1;
    }
}

int main(){
    ios_base::sync_with_stdio(false);

    cin >> height;
    cin >> width;

    //cout << height << endl;

    for(int h = 0; h < height; h++){
        string in;
        cin >> in;
        for(int w = 0; w < width; w++){
            area[h][w] = in[w] - '0' == 1;
            areas[h][w] = -1;
        }
    }

    int cases;
    cin >> cases;

    for (int c = 0; c < cases; c++){
        int xs, ys, xe, ye;
        cin >> ys;
        cin >> xs;
        cin >> ye;
        cin >> xe;

        int solved;
        if (areas[ys-1][xs-1] == -1){
            solved = solve(pair<int, int>(ys-1, xs-1), pair<int, int>(ye-1, xe-1));
        } else {
            if(areas[ys-1][xs-1] != areas[ye-1][xe-1]){
                solved = -1;
            }else{
                solved = (area[ys-1][xs-1]) ? 1 : 0;
            }
        }
        if(solved == 1){
            cout << "decimal" << endl;
        } else if(solved == 0){
            cout << "binary" << endl;
        } else{
            cout << "neither" << endl;
        }
    }



    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);

    int length, height;

    cin >> length;
    cin >> height;

    unordered_map<int, int> ceil;
    unordered_map<int, int> floor;
    for(int h = 1; h < height; h++){
        ceil[h] = 0;
        floor[h] = 0;
    }

    for(int l = 0; l < length; l++){
        int val;
        cin >> val;
        if(l % 2 == 0){
            floor[val] += 1;
        } else{
            ceil[val] += 1;
        }
    }


    for(int h = 2; h < height; h++){
        floor[height-h] += floor[height-h+1];
        ceil[height-h] += ceil[height-h+1];
    }

    unordered_map<int, int> hSum;
    for(int h = 1; h <= height; h++){
        hSum[h] = floor[h] + ceil[height-h+1];
    }

    int bestV = -1;
    int numBest = 0;
    for(int h = 1; h <= height; h++){
        if(bestV == -1 || hSum[h] < bestV){
            numBest = 1;
            bestV = hSum[h];
        } else if (hSum[h] == bestV){
            numBest++;
        }
    }

    cout << bestV << " " << numBest << endl;


    return 0;
}

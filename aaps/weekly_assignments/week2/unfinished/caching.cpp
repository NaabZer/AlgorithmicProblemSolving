#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;



int main(){
    ios_base::sync_with_stdio(false);

    int cSize, objects, accesses;

    cin >> cSize;
    cin >> objects;
    cin >> accesses;

    vector<int> reads(accesses, 0);

    for(int a = 0; a < accesses; a++){
        cin >> reads[a];
    }



    return 0;
}

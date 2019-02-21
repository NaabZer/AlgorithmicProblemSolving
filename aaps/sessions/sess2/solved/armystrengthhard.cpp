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

    int cases;
    cin >> cases;

    for(int c = 0; c < cases; c++){
        int godM, mechM;
        cin >> godM;
        cin >> mechM;

        set<int> god;
        set<int> mech;

        for(int m = 0; m < godM; m++){
            int val;
            cin >> val;
            god.insert(val);
        }

        for(int m = 0; m < mechM; m++){
            int val;
            cin >> val;
            mech.insert(val);
        }

        while(god.size() != 0 && mech.size() != 0){
            if(*god.begin() < *mech.begin()){
                god.erase(god.begin());
            } else {
                mech.erase(mech.begin());
            }
        }

        if(god.size() != 0){
            cout << "Godzilla" << endl;
        } else{
            cout << "MechaGodzilla" << endl;
        }
    }

    return 0;
}

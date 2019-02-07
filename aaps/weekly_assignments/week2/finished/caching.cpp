#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

queue<int> accessQueue[100000];

struct classcomp {
  bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const {
      if(lhs.first == rhs.first){
          return lhs.second < rhs.second;
      } else{
          return lhs.first>rhs.first;
      }
  }
};

int main(){
    ios_base::sync_with_stdio(false);

    int cSize, objects, nAccesses;

    cin >> cSize;
    cin >> objects;
    cin >> nAccesses;


    vector<int> accesses(nAccesses, 0);
    int accessElem;
    for(int a = 0; a < nAccesses; a++){
        cin >> accessElem;

        accessQueue[accessElem].push(a);
        accesses[a] = accessElem;
    }

    for(int o = 0; o < objects; o++){
        accessQueue[o].pop();
        accessQueue[o].push(1000001);
    }


    int count = 0;

    set<pair<int, int>, classcomp> worst_queue;
    set<int> cache;
    map<int, int> cacheTimes;

    for(int a = 0; a < nAccesses; a++){

        /*for(auto& val: cache){
            cout << val << ", ";
        }
        cout << endl;*/

        if(cache.count(accesses[a]) == 0){
            if(cache.size() >= cSize){
                auto firstE = worst_queue.begin();
                cache.erase(firstE->second);
                worst_queue.erase(firstE);
            } 
            
            if(accesses[a] == 0){
                //cout << accessQueue[accesses[a]].front() << endl;
            }
            worst_queue.insert(pair<int, int>(accessQueue[accesses[a]].front(), accesses[a]));
            cacheTimes[accesses[a]] = accessQueue[accesses[a]].front(); 
            accessQueue[accesses[a]].pop();

            cache.insert(accesses[a]);

            count++;
        } else{
            if(accesses[a] == 0){
                //cout << accessQueue[accesses[a]].front() << endl;
            }
            auto curElem = worst_queue.find(pair<int, int>(cacheTimes[accesses[a]], accesses[a]));
            worst_queue.erase(curElem);

            worst_queue.insert(pair<int, int>(accessQueue[accesses[a]].front(), accesses[a]));
            cacheTimes[accesses[a]] = accessQueue[accesses[a]].front(); 
            accessQueue[accesses[a]].pop();
        }
        //cout << "A: " << a << ", Top: " << (*worst_queue.begin()).first << ", " << (*worst_queue.begin()).second << ", val: " << accesses[a] << endl;
        //cout << "--------" << endl;
    }

    cout << count << endl;

    return 0;
}

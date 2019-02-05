#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);

    long long candies, children;

    cin >> candies;
    cin >> children;

    long long sumCandies = 0;

    vector<long long> wants(children, 0);
    vector<long long> gets(children, 0);

    for(int i = 0; i < children; i++){
        long long c;
        cin >> c;
        sumCandies += c;
        wants[i] = c;
    }

    sort(wants.begin(), wants.end(), [](auto& i, auto& j){return i > j;});

    long long HigherAmtChildren = 0;
    long long givenCandies = 0;
    long long givenPerHigh = 0;
    long long highestIndex = 0;
    while(true){
        long long currentHighestValue = wants[highestIndex];
        for(int i = highestIndex; i < children; i++){
            if(wants[i] < currentHighestValue) break;
            highestIndex = i;
        }

        long long rest = candies - givenCandies;
        if(highestIndex == children - 1){
            HigherAmtChildren = (rest) % children;
            givenPerHigh += (rest) / children;
            break;
        }

        long long toGive = currentHighestValue - wants[highestIndex+1];
        if(rest < (highestIndex+1) * toGive){
            HigherAmtChildren = rest % (highestIndex+1);
            givenPerHigh += rest / (highestIndex+1);
            break;
        }
        else{
            givenPerHigh += toGive;
            givenCandies += (highestIndex+1) * toGive;
            highestIndex++;
        }
    }


    long long lostPer = wants[0] - givenPerHigh;

    long long ans = (highestIndex + 1 - HigherAmtChildren) * lostPer*lostPer + HigherAmtChildren * (lostPer-1) * (lostPer-1);

    for(int i = highestIndex+1; i < children; i++){
        ans += wants[i]*wants[i];
    }

    cout << ans << endl;

    return 0;
}

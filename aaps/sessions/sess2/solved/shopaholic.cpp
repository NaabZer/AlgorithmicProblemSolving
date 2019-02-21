#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool comp (const int& lhs, const int& rhs) {
    return lhs > rhs;
}

int main(){
    ios_base::sync_with_stdio(false);

    int items;
    cin >> items;

    vector<int> products;

    for(int i = 0; i < items; i++){
        int prodCost;
        cin >> prodCost;
        products.push_back(prodCost);
    }
    sort(products.begin(), products.end(), comp);

    long long discount = 0;
    int it = 0;

    for(auto cost: products){
        if(++it % 3 == 0){
            discount += cost;
        }
    }

    cout << discount << endl;
 
    return 0;
}

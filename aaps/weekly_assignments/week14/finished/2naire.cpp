#include <iomanip>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>
using namespace std;

int n;
double t;

double solve(int n, double expected_val){
    if(n == 0){
        return expected_val;
    }
    double exp_prob = (1 + t)/2;
    double pdf = 1/(1 - t);
    double diff = (1 << (n-1)) / expected_val;

    double exp_val;
    if(diff <= t){
        exp_val = exp_prob * expected_val;
    }else{
        exp_val = (diff - t)*pdf * (1 << (n-1)) +
                  (1 - diff) * (diff + 1) * pdf * expected_val/2;
    }
    
    return solve(n-1, exp_val);
}

int main() {
    ios_base::sync_with_stdio(false);

    while(true) {
        cin >> n >> t;
        if (n == 0 && t == 0){
            break;
        }
        double exp_val = solve(n, 1 << n);
        cout << fixed << setprecision(3) << exp_val << endl;
    }
}

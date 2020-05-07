#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

const int MAX_VAL = 10001;

vector<bool>isprime(MAX_VAL , true); 
vector<int>prime; 
vector<int>SPF(MAX_VAL); 

vector<int>ishappy(MAX_VAL, -1);
  
void manipulated_seive(int N){ 
    // 0 and 1 are not prime 
    isprime[0] = isprime[1] = false ; 
  
    // Fill rest of the entries 
    for (int i=2; i<N ; i++) 
    { 
        // If isPrime[i] == True then i is 
        // prime number 
        if (isprime[i]) 
        { 
            // put i into prime[] vector 
            prime.push_back(i); 
  
            // A prime number is its own smallest 
            // prime factor 
            SPF[i] = i; 
        } 
  
        // Remove all multiples of  i*prime[j] which are 
        // not prime by making isPrime[i*prime[j]] = false 
        // and put smallest prime factor of i*Prime[j] as prime[j] 
        // [ for exp :let  i = 5 , j = 0 , prime[j] = 2 [ i*prime[j] = 10 ] 
        // so smallest prime factor of '10' is '2' that is prime[j] ] 
        // this loop run only one time for number which are not prime 
        for (long long int j=0; 
             j < (int)prime.size() && 
             i*prime[j] < N && prime[j] <= SPF[i]; 
             j++) 
        { 
            isprime[i*prime[j]]=false; 
  
            // put smallest prime factor of i*prime[j] 
            SPF[i*prime[j]] = prime[j] ; 
        } 
    } 
} 

bool calculate_happy(int val){
    if(val == 1){
        return true;
    }
    if(ishappy[val] == 1){
        return true;
    } else if(ishappy[val] == 0){
        return false;
    } else if (ishappy[val] == -2){
        ishappy[val] = 0;
        return false;
    }
    ishappy[val] = -2;

    string val_str = to_string(val);
    int new_val = 0;
    for(char v: val_str){
        new_val += pow(v - '0', 2);
    }

    bool happy = calculate_happy(new_val);
    ishappy[val] = happy;
    return happy;
}


int main(){
    ios_base::sync_with_stdio(false);
    manipulated_seive(10001);

    int inputs;
    cin >> inputs;
    for(int lines = 0; lines < inputs; lines++){
        int i;
        int val;
        cin >> i >> val;

        if(isprime[val]){
            if(calculate_happy(val)){
                cout << i << " " << val << " " << "YES" << endl;
            } else{
                cout << i << " " << val << " " << "NO" << endl;
            }

        }else{
            cout << i << " " << val << " " << "NO" << endl;
        }

    }


    return 0;
}

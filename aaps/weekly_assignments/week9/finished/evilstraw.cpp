#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

bool valid_palindrome(string str){
    vector<int> cc(26,0);
    for(char c: str){
        cc[c-'a']++;
    }

    bool single = false;
    for(int i = 0; i < cc.size(); i++){
        int count = cc[i];
        if(count % 2 != 0){
            if(!single){
                single=true;
            }else{
                return false;
            }
        }
    }
    if(str.length() % 2 == 0 && single){
        return false;
    }
    return true;
}

int palindrome_swaps(string str){
    if(!valid_palindrome(str)){
        return -1;
    }

    int len = str.length();

    int count = 0;
    int l = 0;
    int r = len - 1;

    while(r > l){
        if(str[l] != str[r]){
            int p = r;
            while(p > l && str[p] != str[l]){
                p--;
            }

            if(p == l){
                swap(str[l], str[l+1]);
                count++;
            } else{
                while(p < r){
                    swap(str[p], str[p+1]);
                    count++;
                    p++;
                }
                l++;
                r--;
            }
        } else{
            l++;
            r--;
        }
    }

    return count;
}


int main(){
    ios_base::sync_with_stdio(false);
    int cases;
    cin >> cases;
    string in;
    for(int c = 0; c < cases; c++){
        cin >> in;
        int swaps = palindrome_swaps(in);
        if(swaps == -1){
            cout << "Impossible" << endl;
        } else {
            cout << swaps << endl;
        }
    }
    return 0;
}

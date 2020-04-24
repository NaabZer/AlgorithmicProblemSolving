#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int cases;
    cin >> cases;

    for(int c = 0; c < cases; c++){
        int length, suffixes;
        cin >> length >> suffixes;
        
        string outString(length, '*');

        bool invalid = false;

        for(int s = 0; s < suffixes; s++){
            int pos;
            string suffix;
            cin >> pos >> suffix;

            int stringPos = pos - 1;

            int starPos = -1;
            for(int i = 0; i < suffix.length(); i++){
                if(suffix[i] == '*'){
                    starPos = i;
                    break;
                } else if(outString[stringPos + i] != '*' && outString[stringPos + i] != suffix[i]){
                    invalid = true;
                    break;
                } else{
                    outString[stringPos + i] = suffix[i];
                }
            }

            if(starPos != -1){
                int shiftedPos = length - suffix.length();
                for(int i = starPos + 1; i < suffix.length(); i++){
                    if(outString[shiftedPos + i] != '*' && outString[shiftedPos + i] != suffix[i]){
                        invalid = true;
                        break;
                    } else{
                        outString[shiftedPos + i] = suffix[i];
                    }

                }
            }

        }
        if(outString.find("*") != string::npos){
            invalid = true;
        }

        if(invalid){
            cout << "IMPOSSIBLE" << endl;
        } else{
            cout << outString << endl;
        }

    }
    return 0;
}

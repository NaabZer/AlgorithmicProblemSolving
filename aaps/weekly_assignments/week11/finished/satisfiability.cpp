#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(const std::string &s, char delim) {
    vector<string> out;
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        out.push_back(item);
    }
    return out;
}

int main(){
    ios_base::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for(int c = 0; c < cases; c++){
        int n;
        int m;
        cin >> n >> m;
        cin.ignore();

        vector<vector<int>> rules;

        //construct rules
        for(int rule = 0; rule < m; rule++){
            vector<int> sub_rule(n, 0);

            string line;
            getline(cin, line);
            vector<string> split_line = split(line,' ');

            bool unneccessary = false;

            for(string item: split_line){
                if(item[0] == 'v'){
                    continue;
                }

                int value = 1;
                if(item[0] == '~'){
                    value = -1;
                    item = item.substr(1, string::npos);
                }

                int idx = stoi(item.substr(1, string::npos)) - 1;
                
                if(sub_rule[idx] * value == -1){
                    unneccessary = true;
                }
                sub_rule[idx] = value;
            }
            if(!unneccessary){
                rules.push_back(sub_rule);
            }
        }

        bool possible = false;
        for(int i = 0; i < 1 << n; i++){
            bool working_vars = true;
            for(auto sub_rule: rules){
                bool working_rule = false;

                for(int j = 0; j < n; j++){
                    if((i&(1<<j)) >= 1 && sub_rule[j] == 1){
                        working_rule = true;
                    } else if((i&(1<<j)) == 0 && sub_rule[j] == -1){
                        working_rule = true;
                    }
                }
                if(!working_rule){
                    working_vars = false;
                    break;
                }
            }
            if(working_vars){
                possible = true;
                break;
            }

        }

        if(possible){
            cout << "satisfiable" << endl;
        } else{
            cout << "unsatisfiable" << endl;
        }
    }

    return 0;
}

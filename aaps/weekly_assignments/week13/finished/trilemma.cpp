#include <iostream> 
#include <vector>
#include <utility> // for pair 
#include <cmath> // for math functions 
using namespace std; 
  
const double PI = 3.1415926535897932;

float degrees[3];
float lengths[3];
  
// returns square of distance b/w two points 
int lengthSquare(pair<int,int> X, pair<int,int> Y) 
{ 
    int xDiff = X.first - Y.first; 
    int yDiff = X.second - Y.second; 
    return xDiff*xDiff + yDiff*yDiff; 
} 
  
void getAngles(pair<int,int> A, pair<int,int> B, 
                pair<int,int> C) { 
    // Square of lengths be a2, b2, c2 
    int a2 = lengthSquare(B,C); 
    int b2 = lengthSquare(A,C); 
    int c2 = lengthSquare(A,B); 
  
    // length of sides be a, b, c 
    float a = sqrt(a2); 
    float b = sqrt(b2); 
    float c = sqrt(c2); 
    lengths[0] = a;
    lengths[1] = b;
    lengths[2] = c;
  
    // From Cosine law 
    float alpha = acos((b2 + c2 - a2)/(2*b*c)); 
    float beta = acos((a2 + c2 - b2)/(2*a*c)); 
    float gamma = acos((a2 + b2 - c2)/(2*a*b)); 
  
    // Converting to degree 
    degrees[0] = alpha * 180.0 / PI; 
    degrees[1] = beta * 180.0 / PI; 
    degrees[2] = gamma * 180.0 / PI; 
} 

int main() {
    ios_base::sync_with_stdio(false);
    
    int cases;
    cin >> cases;

    for(int c = 0; c < cases; c++){
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        float area = x1 * (y2 - y3) +  
            x2 * (y3 - y1) +  
            x3 * (y1 - y2);


        pair<int,int> A = make_pair(x1, y1); 
        pair<int,int> B = make_pair(x2, y2); 
        pair<int,int> C = make_pair(x3, y3); 

        getAngles(A, B, C);

        bool invalid = false;
        if(area == 0){
            invalid = true;
        }

        cout << "Case #" << c+1 << ":";
        if(!invalid){
            if(lengths[0] == lengths[1] || lengths[0] == lengths[2] ||
                    lengths[1] == lengths[2]){
                cout << " isosceles";
            } else{
                cout << " scalene";
            }


            if(degrees[0] == 90 || degrees[1] == 90 || degrees[2] == 90){
                cout << " right";
            }else if(degrees[0] > 90 || degrees[1] > 90 || degrees[2] > 90){
                cout << " obtuse";
            }else{
                cout << " acute";
            }
        } else{
            cout << " not a";
        }
        cout << " triangle" << endl;
    }

}

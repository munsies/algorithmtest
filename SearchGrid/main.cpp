#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class T>
void display(const vector<vector<T>> &vec) {
    for (size_t i = 0; i < vec.size(); i++)
        {
        for (size_t j = 0; j < vec[i].size(); j++)
            {
            cout << vec[i][j] << " ";
            }    
        cout << endl;
        }
} 

vector <vector<int>> world = {         
                                {0,0,1,0,0,0},
                                {0,0,1,0,0,0},
                                {0,0,0,0,1,0},
                                {0,0,1,1,1,0},
                                {0,0,0,0,1,0},
                                };
int motion[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };                                 

int main() {
//    vector<vector<int>>::iterator it;
    int cost = 0;
    int it = world[0][0];
    int i = 0;
    int j = 0;
    int g_temp = 1;
    while(i < world.size() && j < world[0].size()) {
        
        for (int m = 0; m<4; m++) {
            i = i + motion[m][0];
            j = j + motion[m][1];
            cout << i << "and" << j << endl;
            if (i >= 0 and i <= 4 and j >= 0 and j <= 5) {
                int g = i + j;
                if (world[i][j] == 0 && g <= g_temp) {
                   world[i][j] = 1;
                   cost ++; 
                   g_temp = g;
                }
            }
        }
            
    
            
   
    }
//    for (int i = 0; i < world.size(); i++) { 
//        for (auto it = world[i].begin(); it != world[i].end(); it++)
//            *it = 1;
//            
////            cout << *it << " "; 
//        cout << endl; 
//    } 
    
   cout << cost << endl;
    return 0;
    
}
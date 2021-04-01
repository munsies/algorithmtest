#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <iomanip>

using namespace std;

vector <vector<int>> world = {         
                                {0,1,0,0,0,0},
                                {0,1,0,0,0,0},
                                {0,1,0,0,0,0},
                                {0,1,0,1,1,0},
                                {0,0,0,1,1,0},
                                };
                                
vector <vector<int>> heuristic = {         
                                {9,8,7,6,5,4},
                                {8,7,6,5,4,3},
                                {7,6,5,4,3,2},
                                {6,5,4,3,2,1},
                                {5,4,3,2,1,0},
                                };                                
                                
vector <vector<int>> steps = {         
                                {-1,-1,-1,-1,-1,-1},
                                {-1,-1,-1,-1,-1,-1},
                                {-1,-1,-1,-1,-1,-1},
                                {-1,-1,-1,-1,-1,-1},
                                {-1,-1,-1,-1,-1,-1},
                                };
                                
vector <vector<int>> actions = {         
                                {0,-1,-1,-1,-1,-1},
                                {-1,-1,-1,-1,-1,-1},
                                {-1,-1,-1,-1,-1,-1},
                                {-1,-1,-1,-1,-1,-1},
                                {-1,-1,-1,-1,-1,-1},
                                };
                                
vector <vector<char>> policy = {         
                                {'#','#','#','#','#','#'},
                                {'#','#','#','#','#','#'},
                                {'#','#','#','#','#','#'},
                                {'#','#','#','#','#','#'},
                                {'#','#','#','#','#','#'},
                                };
                                
int motion[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };

char delta_name[] = { '^', '<', 'v', '>', '\0'};

    deque<pair<int, int> > open = {{0,0}};
    deque<int> count = {0};
    int cost = 0;
    int gi = 4;
    int gj = 5;

template <class T>
void display(const vector<vector<T>> &vec) {
    for (size_t i = 0; i < vec.size(); i++)
        {
        for (size_t j = 0; j < vec[i].size(); j++)
            {
            cout <<setw(4)<< vec[i][j] << setw(4);
            }    
        cout << endl;
        }
} 

void display(deque<pair<int, int> > open) {
    while (!open.empty()) {
        int aa = (open.front()).first; 
        int ab = (open.front()).second; 
        cout << aa <<"," << ab << endl;
        open.pop_front();
    }
}

bool PairExist(deque<pair<int, int> > open,int i,int j) {
    bool pair = false;
    while (!open.empty()) {
        int aa = (open.front()).first; 
        int ab = (open.front()).second; 
        if (aa == i && ab == j)
            pair = true;
//        cout << aa <<"," << ab << endl;
        open.pop_front();
    }
    return pair;
}


deque<pair<int, int>> expand(deque<pair<int, int> > open, int i_orig, int j_orig,int g_temp) {
    int c = 0;
    int f_init = 0;
    
    for (int m = 0; m<4; m++) {
            int i = i_orig + motion[m][0];
            int j = j_orig + motion[m][1];
            
//            cout << i << "and" << j << endl;
            if ((i >= 0 and i <= 4 and j >= 0 and j <= 5) and world[i][j] == 0 ) {
//                cout << "i came here!" << endl;
                bool pair = PairExist(open,i,j);
                if (!pair) {
                    cost = g_temp+1;
                    
                    if (c == 0) {
                        f_init = heuristic[i][j] + cost;
                        open.push_back({i,j});
                        count.push_back(cost);
                        actions[i][j] = m;
                    }
                    else {
                        int f = heuristic[i][j] + cost;
                        if (f < f_init) {
                            open.pop_back();
                            count.pop_back();
                            open.push_back({i,j});
                            count.push_back(cost);
                            actions[i][j] = m;
                            f_init = f;
                        }
//                        else if (f == f_init) {
//                            open.push_back({i,j});
//                            count.push_back(cost);
//                            actions[i][j] = m;
//                        }
                    }
                   
//                    open.push_back({i,j});
//                    count.push_back(cost);
                    
//                    cout << "here" << "cost:" << cost << endl;
//                display(open); 
                }
                c = c+1;
            }
    }
    return open;
}


                                 

int main() {
//    vector<vector<int>>::iterator it;
//    int cost = 0;
//    int it = world[0][0];
    int i = 0;
    int j = 0;
    int g_temp ;
    int step = 0;

//    cout <<  world.size() << endl;
//    cout <<  world[0].size() << endl;
    
    while(!open.empty()) {
//                  world[0][0] = 1;
                  g_temp = count.front();
                  open = expand(open,i,j,g_temp); 
//                  cout << "here2" << endl;
//                  display(open);  
                  
                  i = (open.front()).first; 
                  j = (open.front()).second;
                  world[i][j] = 1;
                  steps[i][j] = step;
                  step++;
                  if (i == gi && j == gj) {
                      cout << "Goal Reached :" << i << "," << j << ":"<< cost << endl;
                      break;
                  }
                  open.pop_front();
                  count.pop_front();
                  i = (open.front()).first; 
                  j = (open.front()).second;
                  
                  if (open.empty())
                      cout << "Fail to reach the goal." << endl; 

    }

display(steps);
cout << "---------------------" << endl;
display(actions);
cout << "---------------------" << endl;
 
int x = gi;   
int y = gj;

policy[x][y] = '*';  
//cout << motion[actions[x][y]][0] << endl;
//cout << motion[actions[x][y]][1] << endl;
while ( x != 0 or y != 0) {
//    cout << "I am here" << endl;
    int x2 = x - motion[actions[x][y]][0]; 
    int y2 = y - motion[actions[x][y]][1]; 
    policy[x2][y2] = delta_name[actions[x][y]];
    x = x2;
    y = y2;
    
}  
    

    display(policy);
    cout << "---------------------" << endl;
    return 0;
    
}
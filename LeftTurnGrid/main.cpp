#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <math.h>

using namespace std;

class Map {
    public:
    const static int worldWidth = 6;
    const static int worldHeight = 5;
    vector <vector<vector<int>>> world = {         
                                {{1,-1},{1,-1},{1,-1},{0,-1},{0,-1},{0,-1}},
                                {{1,-1},{1,-1},{1,-1},{0,-1},{1,-1},{0,-1}},
                                {{0,-1},{0,-1},{0,-1},{0,-1},{0,-1},{0,-1}},
                                {{1,-1},{1,-1},{1,-1},{0,-1},{1,-1},{1,-1}},
                                {{1,-1},{1,-1},{1,-1},{0,-1},{1,-1},{1,-1}},
                                };
                                
//    vector <vector<int>> steps = {         
//                                {99,99,99,99,99,99},
//                                {99,99,99,99,99,99},
//                                {99,99,99,99,99,99},
//                                {99,99,99,99,99,99},
//                                {99,99,99,99,99,99},
//                                };
//                                
//    vector <vector<int>> actions = {         
//                                {-1,-1,-1,-1,-1,-1},
//                                {-1,-1,-1,-1,-1,-1},
//                                {-1,-1,-1,-1,-1,-1},
//                                {-1,-1,-1,-1,-1,-1},
//                                {-1,-1,-1,0,-1,-1},
//                                };
//                                
    vector <vector<char>> policy = {         
                                {' ',' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' ',' '},
                                 };
};                                 

class Planner : Map {
    public:                                                                
    vector<vector<int>> motion = { {-1,0}, {0,-1}, {1,0}, {0,1} };
    vector <int> action = {-1,0,1};
    vector <char> action_name = {'R','#','L'};
    vector <int> cost = {2,1,2}; //right,straight,left
    vector <int> start = {4,3,0};
    vector <int> goal = {2,0,1};
    
};
template <class T>
void display2D(const vector<vector<T>> &vec) {
    for (size_t i = 0; i < vec.size(); i++)
        {
        for (size_t j = 0; j < vec[i].size(); j++)
            {
            cout <<setw(4)<< vec[i][j] << setw(4);
            }    
        cout << endl;
        }
} 

template <class T>
void display3D(const vector<vector<vector<T>>> &vec) {
    for (size_t i = 0; i < vec.size(); i++)
        {
        for (size_t j = 0; j < vec[i].size(); j++)
            {
                cout << setw(4);
                cout << "{"; 
                for (size_t k = 0; k < 2; k++) {
                    cout << vec[i][j][k] << ","; }
                cout << "} ";
                cout << setw(4);
            }    
        cout << endl;
        }
} 

vector<int> orient_find(int prev_orient,int m) {
    vector <int> move= {0,1,2}; //right,straight,left
    int g = 0;
    if (prev_orient == 0) {
        if (m == 0 ) { // or m ==2
            g = move[1];  
            return {0,g};
        }
        else if (m == 1) {
            g = move[2];
            return {1,g};
        }
        else if (m == 3) {
            g = move[0];
            return {3,g};
        }
        else {
            g = 99;
            return {0,99};
        }
    }
    else if (prev_orient == 1) {
        if (m == 0) {
            g = move[0];
            return {0,g};
        }
        else if (m == 1 ) { // m = 3
            g = move[1];
            return {1,g};
        }
        else if (m == 2) {
            g = move[2];
            return {2,g};
        }
        else {
            g = 99;
            return {1,99};
        }
    } 
    else if (prev_orient == 2) {
        if ( m ==2) { // m == 0
            g = move[1];
            return {2,g};
        }
        else if (m == 1) {
            g = move[0];
            return {1,g};
        }
        else if (m == 3) {
            g = move[2];
            return {3,g};
        }
        else {
            g = 99;
            return {2,99};
        }
    } 
    else if (prev_orient == 3) {
        if (m == 0) {
            g = move[2];
            return {0,g};
        }
        else if (m == 3) { // m == 1
            g = move[1];
            return {3,g};
        }
        else if (m == 2) {
            g = move[0];
            return {2,g};
        }
        else {
            g = 99;
            return {3,g};
        }
    } 
}

void search(Map map,Planner planner) { 

    vector <vector<vector<int>>> closed(map.worldHeight,vector<vector<int>>(map.worldWidth,vector<int>(2,99)));
    closed[planner.start[0]][planner.start[1]][0] = 0; // define action
    closed[planner.start[0]][planner.start[1]][1] = 0; // define cost
    map.world[planner.start[0]][planner.start[1]][0] = 1;
    map.world[planner.start[0]][planner.start[1]][1] = 0;
        
    int g_temp = 0;
    int i_temp = planner.start[0];
    int j_temp = planner.start[1];
    int orient = planner.start[2];
    
    int g = 0;
//    int count = 0;
    
    vector<vector<int>> open;
    open.push_back( {g_temp,i_temp,j_temp,orient});
    
    while (!open.empty()) {
        sort(open.begin(), open.end());
        display2D(open);
        cout << "************************" << endl; 
        
        vector <int> expand = {open[0][0],open[0][1],open[0][2],open[0][3]};
        open.erase(open.begin());
        g_temp = expand[0];
        i_temp = expand[1];
        j_temp = expand[2];
        orient = expand[3];
//        cout << "I came here!" << endl;
        
        if (i_temp == planner.goal[0] && j_temp == planner.goal[1]) {
            cout << "Goal Reached :" << g_temp<< "," << i_temp <<"," << j_temp << endl;

            break;
        }
        
        for (size_t m = 0; m < planner.motion.size(); m++) {
            int i = i_temp + planner.motion[m][0];
            int j = j_temp + planner.motion[m][1];
            
            vector <int> orient_action = {0,0};
            orient_action = orient_find(orient,m);
            int orient_current = orient_action[0];
            int step = orient_action[1];
            cout << "step::"<< step << endl;
            if (step != 99)
                g = g_temp + planner.cost[step];
            else
                g = g_temp + 99;
                
            if ((i >= 0 and i < map.worldHeight and j >= 0 and j < map.worldWidth) and map.world[i][j][0] == 0 and g < 100 and (orient_current != map.world[i][j][1] or g < closed[i][j][1])) {
//            map.world[i][j][0] = 1;
            
//            int g = g_temp + planner.cost[step];
//            if (g < closed[i][j][1]) {
                open.push_back({g,i,j,orient_current});
                closed[i_temp][j_temp][0] = step;
//                closed[i][j][0] = planner.action[step];
                closed[i][j][1] = g;
                map.world[i][j][1] = orient_current;
//            }
            }
        }  
//        } display3D(map.world);
//          } display2D(open);
        cout << "************************" << endl;  
        
    }
        
        
     display3D(closed); 
     cout << "************************" << endl;
     display3D(map.world); 
//     display2D(open);
}   

int main() {
    
    Map map;
    Planner planner;
    
//    display3D(map.world);
//
    search(map,planner);
    
    return 0;
}
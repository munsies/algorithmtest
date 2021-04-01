#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/* TODO: Define a Map class
   Inside the map class, define the mapWidth, mapHeight and grid as a 2D vector
*/
class Map {
    public:
    const static int mapWidth = 6;
    const static int mapHeight = 5;
    vector<vector<int>> grid = {         
                                {0,1,0,0,0,0},
                                {0,1,0,0,0,0},
                                {0,1,0,0,0,0},
                                {0,1,0,0,0,0},
                                {0,0,0,1,1,0}
                                };    
                       
};

/* TODO: Define a Planner class
*/
class Planner : Map {
    public:
    vector<int> start = {0,0};
    vector<int> goal = {mapHeight-1,mapWidth-1};
    int cost = 1;
    vector<vector<int>> movements = { {-1,0}, {0,-1}, {1,0}, {0,1} };
    char movements_arrows[5] = { '^', '<', 'v', '>', '\0'};
};


template <class T>
void print2DVector(const vector<vector<T>> &vec) {
    for (size_t i = 0; i < vec.size(); i++)
        {
        for (size_t j = 0; j < vec[i].size(); j++)
            {
            cout <<setw(4)<< vec[i][j] << setw(4);
            }    
        cout << endl;
        }
} 

/*#### TODO: Code the search function which will generate the expansion list ####*/
// You are only required to print the final triplet values
void search(Map map, Planner planner)
{
    vector<vector<int>> closed(map.mapHeight,vector<int>(map.mapWidth,0));
    closed[planner.start[0]][planner.start[0]] = 1;
    
    vector<vector<int>> expansion(map.mapHeight,vector<int>(map.mapWidth,-1));
    vector<vector<int>> actions(map.mapHeight,vector<int>(map.mapWidth,-1));
    vector<vector<char>> policy(map.mapHeight,vector<char>(map.mapWidth,'-'));
    
    int g_temp = 0;
    int i_temp = planner.start[0];
    int j_temp = planner.start[1];
    
    int count = 0;
    
    vector<vector<int>> open;
    open.push_back( {g_temp,i_temp,j_temp});
    
    while(!open.empty()) {
        
        vector <int> expand = {open[0][0],open[0][1],open[0][2]};
        open.erase(open.begin());
        g_temp = expand[0];
        i_temp = expand[1];
        j_temp = expand[2];
        expansion[i_temp][j_temp] = count;
        count++;
        if (i_temp == planner.goal[0] && j_temp == planner.goal[1]) {
            cout << "Goal Reached :" << g_temp<< "," << i_temp <<"," << j_temp << endl;

            break;
        }

        for (int m = 0; m < planner.movements.size(); m++) {
            int i = i_temp + planner.movements[m][0];
            int j = j_temp + planner.movements[m][1];
            
            if ((i >= 0 and i < map.mapHeight and j >= 0 and j <= map.mapWidth) and map.grid[i][j] == 0 and closed[i][j] == 0) {
                map.grid[i][j] = 1;
                int g = g_temp+1;
                closed[i][j] = g;
                open.push_back({g,i,j});
                actions[i][j] = m;

                
//                cout << "I came here" << endl;
            }
        
        }
    
    } 
    int x = planner.goal[0];
    int y = planner.goal[1];
    
    policy[x][y] = '*';  

    while ( x != 0 or y != 0) {
//    cout << "I am here" << endl;
        int x2 = x - planner.movements[actions[x][y]][0]; 
        int y2 = y - planner.movements[actions[x][y]][1]; 
        policy[x2][y2] = planner.movements_arrows[actions[x][y]];
        x = x2;
        y = y2;
    
} 

  print2DVector(policy);
}

/*############ Don't modify the main function############*/
int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;
    
    // Search for the expansions
    search(map, planner);
 
     
/*
    // Print classes variables
    cout << "Map:" << endl;
    print2DVector(map.grid);
    cout << "Start: " << planner.start[0] << " , " << planner.start[1] << endl;
    cout << "Goal: " << planner.goal[0] << " , " << planner.goal[1] << endl;
    cout << "Cost: " << planner.cost << endl;
    cout << "Robot Movements: " << planner.movements_arrows[0] << " , " << planner.movements_arrows[1] << " , " << planner.movements_arrows[2] << " , " << planner.movements_arrows[3] << endl;
    cout << "Delta:" << endl;
    print2DVector(planner.movements);
*/
    return 0;
}

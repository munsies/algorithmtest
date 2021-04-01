#include <iostream>
#include <vector>
#include <algorithm>
#include "Python.h"
#include "../library/matplotlibcpp.h" //Graph Library

namespace plt = matplotlibcpp;
using namespace std;

// Print 2D vectors coordinate values
void print2DVector(vector<vector<int> > vec)
{
     // Sorting the vector for grading purpose
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[0].size(); ++j) {
                cout << vec[i][j] << "  ";
        }
        cout << endl;
    }
}

// ***TODO: Check for duplicate coordinates inside a 2D vector and delete them*** //
vector<vector<int> > delete_duplicate(vector<vector<int> > C)
{
    sort(C.begin(), C.end());
    vector <int> ci = {C[0][0],C[0][1]}; 
    for (auto it = C.begin()+1; it != C.end();) {
        if(*it == ci) {
            C.erase(it);
        }
        else  {
            ci = *it;
            it++;
        }
    }
    
    return C;
}

// ***TODO: Compute the Minkowski Sum of two vectors***//
vector<vector<int> > minkowski_sum(vector<vector<int> > A, vector<vector<int> > B)
{
    vector<vector<int>> C ;

    for (int i =0; i < A.size(); i++) {
        for (int j =0; j < B.size(); j++) {
            int x = A[i][0] + B[j][0];
            int y = A[i][1] + B[j][1];
            vector <int> ci = {x,y}; 
            C.push_back(ci);
        }
    }
 
    print2DVector(C);
    cout <<"*********************" << endl;
    
    C = delete_duplicate(C);
    return C;
}

void visualization(vector<vector<int> > vec) {
    
    plt::title("minkowski");
    plt::xlim(-5, 5);
    plt::ylim(-5, 5);
    plt::grid(true);
    for (auto it = vec.begin(); it != vec.end();) {
        vector <int> ci = {*it};
        double x1 = ci[0];
        double y1 = ci[1];
        it++;
        vector <int> cl = {*it};
        double x2 = cl[0];
        double y2 = cl[1];
        plt::plot({x1,x2},{y1,y2},"ro");
        
    }
        //Save the image and close the plot
    plt::save("./images/Minkowski_Sum.png");
//    plt::clf();
        
}

int main()
{
    // ***TODO: Define the coordinates of triangle A and B using 2D vectors*** //
    vector<vector<int> > A = { {0,-1}, {0,1}, {1,0} };
    vector<vector<int> > B = { {0,0}, {1,1}, {1,-1} };

    // Compute the minkowski sum of triangle A and B
    vector<vector<int> > C;

    C = minkowski_sum(A, B);

    // Print the resulting vector   
    print2DVector(C);
    cout << "Hello" << endl;
    visualization(C);
    

    return 0;
}
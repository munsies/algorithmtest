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

vector <vector<char>> world = {         
                                {'R','G','G','R','R'},
                                {'R','R','G','R','R'},
                                {'R','R','G','G','R'},
                                {'R','R','R','R','R'}
                                };
                                
vector <char> measurements = {'G', 'G', 'G', 'G', 'G'};
vector <vector<int>> motion = { {0,0},{0,1},{1,0},{1,0},{0,1}};
double sensor_right = 0.7;
double p_move = 0.8;
vector<vector<double>> q;

vector<vector<double>> move(vector<vector<double>> p, int U, int V) {
    q = p;
    //cout << p.size() << endl;
    //cout << p[1].size() << endl;
    for (size_t i = 0; i < p.size(); i++) {
        for (size_t j = 0; j < p[i].size(); j++) {
            signed int k = i+U;
            signed int l = j+V;
            
            if (k >= int(p.size())) 
                k = k - p.size(); 
            if (l >= int(p[i].size())) 
                l = l - p[i].size();
            
            q.at(k).at(l) = p.at(i).at(j)*p_move + p.at(k).at(l)*(1-p_move)  ;
            
            
                
        }
    }
    
    return q;
}


vector<vector<double>> sense(vector<vector<double>> p, char z) {
    
    //vector <double> q;
    double prob;
    for (size_t i = 0; i < p.size(); i++) {
        for (size_t j = 0; j < p[i].size(); j++) {
            if (world.at(i).at(j) == z) {
                prob = p.at(i).at(j) * sensor_right;
                q.at(i).at(j) = prob; 
            }
            else {
                prob = p.at(i).at(j) * (1-sensor_right);
                q.at(i).at(j) = prob; 
                 }
        }
    }
    double sum = 0;
    for (size_t i = 0; i < p.size(); i++) {
        for (size_t j = 0; j < p[i].size(); j++) {
            sum = sum + q.at(i).at(j);
        }
    }
    for (size_t i = 0; i < p.size(); i++) {
        for (size_t j = 0; j < p[i].size(); j++) {
            q.at(i).at(j) = q.at(i).at(j)/sum;
        }
    }
    
    return q;    
}
    
int main() {
    int n = 4;
    int m = 5;
    double elem = 1/double(n*m);
    vector<vector<double>> p(n,vector<double> (m,elem));
    
     
    for (size_t l = 0; l < measurements.size(); l++) {
        int U = motion[l][0];
        int V = motion[l][1];
        //cout << U << "   " << V << endl;
        
        display(p);
        q = move(p,U,V);
        p = q;
        
        char z = measurements[l];
        cout << z << endl;
        display(p);
        q = sense(p,z);
        p = q;
    }
    //cout << p.size() << endl;
    //display(world);
    cout << "Fianl" << endl;
    display(p);
    return 0;
    
}
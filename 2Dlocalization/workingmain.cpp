/*
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
                                {'G','G','G'},
                                {'G','R','G'},
                                {'G','R','G'}
                                };
                                
vector <char> measurements = {'R', 'R'};
vector <vector<int>> motion = { {0,0},{1,0}};
double sensor_right = 1.0;
double p_move = 0.5;
vector<vector<double>> q;

vector<vector<double>> move(vector<vector<double>> p, int U, int V) {
    q = p;
    for (size_t i = 0; i < p.size(); i++) {
        for (size_t j = 0; j < p[i].size(); j++) {
            signed int k = i+U;
            if (k >= int(p.size())) {
                //cout << "I was here" << endl;
                k = k - p.size();
                if (i == 0)
                    q.at(k).at(j) = p.at(i).at(j)*p_move + p.at(k).at(j)*(1-p_move)  ;
                else if (i == p.size()-1)
                    q.at(k).at(j) = p.back().at(j)*p_move + p.at(k).at(j)*(1-p_move) ;
                else    
                    q.at(k).at(j) = p.at(i).at(j)*p_move + p.at(k).at(j)*(1-p_move) ; 
            }
            else if (k < 0) {
                //cout << "I was here" << endl;
                k = int(p.size()) + k;
                if (i == 0)
                    q.at(k).at(j) = p.at(i).at(j)*p_move + p.at(k).at(j)*(1-p_move)  ;
                else if (i == p.size()-1)
                    q.at(k).at(j) = p.back().at(j)*p_move + p.at(k).at(j)*(1-p_move) ;
                else    
                    q.at(k).at(j) = p.at(i).at(j)*p_move + p.at(k).at(j)*(1-p_move) ; 
            }  
            else {
                //cout << "I was here" << endl;
                if (i == 0)
                    q.at(k).at(j) = p.at(i).at(j)*p_move + p.at(k).at(j)*(1-p_move)  ;
                else if (i == p.size()-1)
                    q.at(k).at(j) = p.back().at(j)*p_move + p.at(k).at(j)*(1-p_move) ;
                else    
                    q.at(k).at(j) = p.at(i).at(j)*p_move + p.at(k).at(j)*(1-p_move) ; 
            } 
            
            
            signed int l = j+V;
        if (l >= int(p[i].size())) {
                //cout << "I was here" << endl;
                l = l - p[i].size();
                
            if (V > 0) {
                cout << "I was here third" << endl;
                if (j == 0)
                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move)  ;
                else if (j == p.size()-1)
                    q.at(i).at(l) = p.at(i).back()*p_move + p.at(i).at(l)*(1-p_move) ;
                else    
                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move) ; 
            } 
//            else if (V < 0) {
//                //cout << "I was here2" << endl;
//                if (j == 0)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move ;
//                else if (j == p.size()-1)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move;
//                else    
//                    q.at(i).at(l) = p.at(i).at(j)*p_move; 
//            }
//            else {
//                if (j == 0)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move);
//                else if (j == p.size()-1)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move);
//                else    
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move);  
//                //cout << "I was here3" << endl;
//            }    
        }
                
               // q.at(i).at(l) = p.at(i).at(j)*p_move;
            
        else if (l < 0) {
                cout << "I was here2" << endl;
            l = int(p[i].size()) + l;
            if (V > 0) {
                //cout << "I was here second" << endl;
                if (j == 0)
                    q.at(i).at(l) = p.at(i).at(j)*p_move ;
                else if (j == p.size()-1)
                    q.at(i).at(l) = p.at(i).at(j)*p_move;
                else    
                    q.at(i).at(l) = p.at(i).at(j)*p_move; 
            } 
//            else if (V < 0) {
//                if (j == 0)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move ;
//                else if (j == p.size()-1)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move;
//                else    
//                    q.at(i).at(l) = p.at(i).at(j)*p_move; 
//            } 
//            else {
//                if (j == 0)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move) ;
//                else if (j == p.size()-1)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move);
//                else    
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move);  
//                //cout << "I was here3" << endl;
//            }   
        }
        else {//q.at(i).at(l) = p.at(i).at(j)*p_move;
            if (V > 0) {
                cout << "I was here first" << endl;
                if (j == 0)
                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move) ;
                else if (j == p.size()-1)
                    q.at(i).at(l) = p.at(i).back()*p_move + p.at(i).at(l)*(1-p_move) ;
                else    
                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move) ; 
            } 
//            else if (V < 0) {
//                if (j == 0)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move;
//                else if (j == p.size()-1)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move;
//                else    
//                    q.at(i).at(l) = p.at(i).at(j)*p_move; 
//            } 
//            else {
//                if (j == 0)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move) ;
//                else if (j == p.size()-1)
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move);
//                else    
//                    q.at(i).at(l) = p.at(i).at(j)*p_move + p.at(i).at(l)*(1-p_move);  
//                //cout << "I was here3" << endl;
//            }   
        }
        }

    
        //cout << endl;
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
    int n = 3;
    int m = 3;
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
    
}*/

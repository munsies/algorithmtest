#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class T>
void display(const vector<T> &vec) {
    cout << "[ ";
    for (auto elem: vec) 
        cout << elem << " ";
    cout << "]" << endl;
}

string arr[] = {"green","red","red","green","green"};
vector <string> world(arr,arr + sizeof(arr)/sizeof(std::string));

double phit = 0.6;
double pmiss = 0.2;
double pExact = 0.8;
double pOvershoot = 0.1;
double pUndershoot = 0.1;

vector <double> sense(vector<double>p,string z) {
    
    vector <double> q;
    double prob;
    for (size_t i = 0; i< p.size(); i++) {
        if (world.at(i) == z) {
            prob = p.at(i) * phit;
            q.push_back(prob); 
            }
        else {
            prob = p.at(i) * pmiss;
            q.push_back(prob);
            
        }
    }
    double sum = 0;
    for (size_t i = 0; i< p.size(); i++) {
        sum = sum + q.at(i);
    }
        for (size_t i = 0; i< p.size(); i++) {
        q.at(i) = q.at(i)/sum;
    }
    
    return q;    
}

vector <double> move(vector<double>p,int U) {
    vector <double> q;
    q = p;
    
    for (size_t i = 0; i< p.size(); i++) {
        signed int l = i+U;
        
        if (l >= int(p.size())) {
            //cout << "I was here" << endl;
            l = l - p.size();
            
            if (U > 0) {
                if (i == 0)
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pUndershoot+p.back() * pOvershoot;
                else if (i == p.size()-1)
                    q.at(l) = p.at(i)*pExact+p.front()*pUndershoot+p.at(i-1) * pOvershoot;
                else    
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pUndershoot+p.at(i-1)*pOvershoot; 
            } 
            else if (U < 0) {
                if (i == 0)
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pOvershoot+p.back()*pUndershoot;
                else if (i == p.size()-1)
                    q.at(l) = p.at(i)*pExact+p.front()*pOvershoot+p.at(i-1)*pUndershoot;
                else    
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pOvershoot+p.at(i-1)*pUndershoot;         
            }
        }
        else if (l < 0) {
            //cout << "I was here2" << endl;
            l = int(p.size()) +(l);
            if (U > 0) {
                if (i == 0)
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pUndershoot+p.back() * pOvershoot;
                else if (i == p.size()-1)
                    q.at(l) = p.at(i)*pExact+p.front()*pUndershoot+p.at(i-1) * pOvershoot;
                else    
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pUndershoot+p.at(i-1)*pOvershoot; 
            } 
            else if (U < 0) {
                if (i == 0)
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pOvershoot+p.back()*pUndershoot;
                else if (i == p.size()-1)
                    q.at(l) = p.at(i)*pExact+p.front()*pOvershoot+p.at(i-1)*pUndershoot;
                else    
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pOvershoot+p.at(i-1)*pUndershoot;         
            }
            //q.at(l) = p.at(i);            
        } 
        else { //cout << "I was here3" << endl; 
            if (U > 0) {
                if (i == 0)
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pUndershoot+p.back() * pOvershoot;
                else if (i == p.size()-1)
                    q.at(l) = p.at(i)*pExact+p.front()*pUndershoot+p.at(i-1) * pOvershoot;
                else    
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pUndershoot+p.at(i-1)*pOvershoot; 
            } 
            else if (U < 0) {
                if (i == 0)
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pOvershoot+p.back()*pUndershoot;
                else if (i == p.size()-1)
                    q.at(l) = p.at(i)*pExact+p.front()*pOvershoot+p.at(i-1)*pUndershoot;
                else    
                    q.at(l) = p.at(i)*pExact+p.at(i+1)*pOvershoot+p.at(i-1)*pUndershoot;         
            }
        //q.at(l) = p.at(i); 
        }  
            
    }
    return q; 
}

int main() {
    
    int size = 5;
    
    string arr2[] = {"red","red"};
    vector <string> measurements(arr2,arr2 + sizeof(arr2)/sizeof(std::string));
    int U = 1;
    vector <double> p;
    vector <double> q;
    
    vector <int> motion = {1,1};
       
    double elem;
    elem = 1/double(size);
    
    for (int i = 0;i<size;i++) {
        p.push_back(elem);
    }
    //p.at(1) = 1;
    cout << p.size();
    display (p);
    for (size_t l = 0; l < measurements.size(); l++) {
        string z =  measurements[l];
        cout << z << endl;
        q = sense(p,z);
        p = q;
        U = motion[l];
        q = move(p,U);
        p = q;
    }
//    for (size_t m = 0; m < 1001; m++) {
//        q = move(p,U);
//        p = q;
//    }

    
    //display(measurements);
    display(q);
    //display(world);
    return 0;
    
}
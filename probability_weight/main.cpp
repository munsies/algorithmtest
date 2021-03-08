#include <iostream>
#include <vector>

using namespace std;

//double w[] = { 0.6, 1.2, 2.4, 0.6, 1.2 };//You can also change this to a vector

//TODO: Define a  ComputeProb function and compute the Probabilities
vector <double> w = {0.6, 1.2, 2.4, 0.6, 1.2 };

vector <double> ComputeProb(vector <double> w) {

    double sum = 0;
    for (size_t i =0; i< w.size(); i++) {
        sum = w[i] + sum;        
    }

    vector <double> prob;
    for (size_t i =0; i< w.size(); i++) {
        double p = w[i] / sum;
        prob.push_back(p);
    }
    return prob;
}


int main()
{
    //TODO: Print Probabilites each on a single line:
    //P1=Value
    //:
    //P5=Value
    vector <double> prob;
    //cout << w.size();
    prob = ComputeProb(w);
    
    for (size_t i = 0; i < w.size(); i++) {
        cout << prob.at(i) << endl;        
    }
       
    
    
    return 0;
}
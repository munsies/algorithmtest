#include <iostream>
#include <math.h>
#include <tuple>
#include "Core" // Eigen Library
#include "LU"   // Eigen Library
#include <iomanip>

using namespace std;
using namespace Eigen;



vector <vector<double>> dh_table = {         
                                {90,350,675,0},
                                {0,1150,0,90},
                                {90,-41,0,0},
                                {-90,0,1200,0},
                                {90,0,0,0},
                                {0,0,215,0}
                                };                                


MatrixXf DHome(double alpha, double a, double d, double theta) {
    
    alpha = alpha * M_PI / 180;
    theta = theta * M_PI / 180;
    
    MatrixXf H(4,4);
    H << cos(theta), -sin(theta)*cos(alpha), sin(theta)*sin(alpha), a*cos(theta),
         sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha), a*sin(theta),
         0, sin(alpha), cos(alpha), d,
         0, 0, 0, 1;

//    H << cos(theta), -sin(theta), 0, a,
//         sin(theta)*cos(alpha), cos(theta)*cos(alpha), -sin(alpha), -sin(alpha)*d,
//         sin(theta)*sin(alpha), cos(theta)*sin(alpha), cos(alpha), cos(alpha)*d,
//         0, 0, 0, 1;
         
    return H;
}

VectorXd R_to_Cart(MatrixXf H) {
    VectorXd V(6);
    
    V(0) = H(0,3);
    V(1) = H(1,3);
    V(2) = H(2,3);
    
    V(3) = atan2(H(2,1),H(2,2));
    V(4) = atan2(-H(2,0),sqrt(pow(H(2,1),2)+pow(H(2,2),2)));
    V(5) = atan2(H(1,0),H(0,0));
    
    return V;
} 

int main() {
    std::cout<<"My Tempelate"<< std::endl;
    
    vector<double> q = {0,-70,90,0,0,0};
     q[0] = -q[0];
//     q[1] = -q[1];
   q[1] = -q[1]-90; 
   q[2] = -q[2]+90; 
//   q[2] = q[2]; 
//   q[2] = (q[2]-q[1]);
   q[4] = -q[4];
   q[3] = -q[3];
   q[5] = -q[5];
    
    MatrixXf m(4,4);
    MatrixXf m_prev(4,4);
    m_prev << 1, 0, 0, 0,
              0, 1, 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1;
    
    for (size_t i = 0; i < dh_table.size(); i++) {
        double alpha = dh_table[i][0];
        double a = dh_table[i][1];
        double d = dh_table[i][2];
        double theta = dh_table[i][3];
        
        theta = theta+q[i];
        
        m = DHome(alpha,a,d,theta);
        
        m = m_prev * m;
        
        m_prev = m;
        
        cout.setf(ios::fixed, ios::floatfield);
        
       
        
    }
       
    cout << m << endl;
    
    VectorXd pos(6);
    pos = R_to_Cart(m);
    
    double w = pos(3) * 180 / M_PI;
    double p = pos(4) * 180 / M_PI;
    double r = pos(5) * 180 / M_PI;
    
    cout << "x: " << pos(0) << " y: " << pos(1) << " z: " << pos(2) << endl;
    cout << "w: " << w << " p: " << p << " r: " << r << endl;
    
    return 0;
    
}
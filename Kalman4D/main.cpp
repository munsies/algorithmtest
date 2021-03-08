#include <iostream>
#include <math.h>
#include <tuple>
#include "Core" // Eigen Library
#include "LU"   // Eigen Library

using namespace std;
using namespace Eigen;



tuple<MatrixXf, MatrixXf> kalman_filter(MatrixXf x, MatrixXf P, MatrixXf u, MatrixXf F, MatrixXf H, MatrixXf R, MatrixXf I)
{
MatrixXf measurements(4,2);
//measurements << 5,10,6,8,7,6,8,4,9, 2,10, 0;

measurements << 1,4,6,0,11,-4,16,-8;


                        
    for (auto n = 0; n <measurements.rows() ; n++) {
        //****** TODO: Kalman-filter function********//
        // Prediction
        // Code the Prediction
        // Compute x and P
        
        x << (F * x) + u; 
        P << F * P * F.transpose();   
        // Measurement Update
        // Code the Measurement Update
        // Initialize and Compute Z, y, S, K, x, and P
        
        MatrixXf Z(1,2);
        Z << measurements(n,0), measurements(n,1);
        
        MatrixXf y(2,1);
        y << Z.transpose() - (H * x);
        
        MatrixXf S(2,2);
        S << H * P * H.transpose() + R;
        
        MatrixXf K(4,2);
        K << P * H.transpose() * S.inverse();
        
        x << x + (K * y);
        
        
        P << (I - (K * H)) * P;
    
     
        
    }

    return make_tuple(x, P);
}

int main()
{
    //initial_xy = [-4., 8.]
    MatrixXf initial_xy(2,1);
    initial_xy << -4, 8;

    double dt = 0.1;

    MatrixXf x(4,1); 
    x << initial_xy(0,0), 
         initial_xy(1,0),
         0., 
         0.; // initial state (location and velocity)
//         
//    MatrixXf u(4,1);
//    u << 0.,0.,0.,0.; //external motion

    //MatrixXf x(2, 1);// Initial state (location and velocity) 
    //x << 0,
    //	 0; 
    
    MatrixXf P(4, 4);//Initial Uncertainty
    P << 0, 0, 0, 0, 
    	 0, 0, 0, 0,
         0, 0, 1000, 0,
         0, 0, 0, 1000; 
         
    MatrixXf u(4, 1);// External Motion
    u << 0,
    	 0,
         0,
         0; 
         
    MatrixXf F(4, 4);//Next State Function
    F << 1, 0, dt, 0,
    	 0, 1, 0, dt,
         0, 0, 1, 0,
         0, 0, 0, 1; 
         
    MatrixXf H(2, 4);//Measurement Function
    H << 1, 0, 0, 0,
    	 0, 1, 0, 0;
 
    MatrixXf R(2, 2); //Measurement Uncertainty
    R << 0.1, 0,
         0, 0.1;
         
    MatrixXf I(4, 4);// Identity Matrix
    I << 1, 0, 0, 0,
    	 0, 1, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1; 

    tie(x, P) = kalman_filter(x, P, u, F, H, R, I);
    cout << "x= " << x << endl;
    cout << "P= " << P << endl;

    return 0;
}
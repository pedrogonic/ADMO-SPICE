
#ifndef LESolver_hpp
#define LESolver_hpp

#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

class LESolver {
    
    public :
        vector<double> cramer(vector<vector<double> > A, vector<double>B);
    double det(vector<vector<double> >M,long l);
    
    private :
    
    
};

#endif /* LESolver_hpp */

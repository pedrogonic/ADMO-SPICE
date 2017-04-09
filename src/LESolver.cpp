
#include "LESolver.hpp"

vector<double> LESolver::cramer(vector<vector<double> > A, vector<double> B) {
    vector<double> R = vector<double>();
    vector<vector<double> > aux;
    
    double den = 0;
    
    if(A.size() != B.size() || A.size() != A[0].size())
        throw 8;
    
    for (long i = 0; i < A.size(); i++)
        R.push_back(0);
    
    
    
    
    
    try {
        //det(A)
        den = det(A,-1);
        
        //Division by zero
        if (den == 0)
            throw 9;
        
        for (int r = 0; r < R.size(); r++) {
            aux = A;
            for (long i = 0; i < A.size(); i++)
                aux[i][r] = B[i];
            R[r] = det(aux,-1)/den;
        }
        
    }catch(exception &e) {
        throw e;
    }
    
    return R;
}

double LESolver::det(vector<vector<double> > M,long l) {
    double res = 0;
    
    if (M.size() != M[0].size())
        throw 8;
    
    if (l != -1) {
        M.erase(M.begin()+l);
        for (long i = 0; i < M.size(); i++)
            M[i].erase(M[i].begin());
    }
    
    if (M.size() == 1)
        return M[0][0];
    else {
        for (long i = 0; i < M.size(); i++) {
            if (M[i][0] != 0)
                res += pow(-1,i)*M[i][0]*det(M,i);
        }
    }
    
    return res;
}
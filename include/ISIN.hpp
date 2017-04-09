
#ifndef ISIN_hpp
#define ISIN_hpp

#include <stdio.h>
#include <string>
#include <math.h>

#define PI 3.14159265

using namespace std;

class ISIN {
    
    private :
        string name;
        string node1;
        string node2;
        double A0;
        double A;
        double f;
        double ta;
        double alfa;
        double psi;
        int cycles;
    
    public :
        ISIN();
        ISIN(string name,
             string node1,
             string node2,
             double A0,
             double A,
             double f,
             double ta,
             double alfa,
             double psi,
             int cycles);
        string getName();
        string getNode1();
        string getNode2();
        double getI(double t);
    
};

#endif /* ISIN_hpp */

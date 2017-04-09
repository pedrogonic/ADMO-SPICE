
#ifndef VPULSE_hpp
#define VPULSE_hpp

#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

class VPULSE {
    
    private :
    string name;
    string node1;
    string node2;
    double V1;
    double V2;
    double ta;
    double ts;
    double td;
    double ton;
    double P;
    int cycles;
    
    public :
    VPULSE();
    VPULSE(string name,
           string node1,
           string node2,
           double V1,
           double V2,
           double ta,
           double ts,
           double td,
           double ton,
           double P,
           int cycles);
    string getName();
    string getNode1();
    string getNode2();
    double getV(double t);
    
};
#endif /* VPULSE_hpp */

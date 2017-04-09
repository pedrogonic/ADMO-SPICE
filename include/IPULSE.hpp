
#ifndef IPULSE_hpp
#define IPULSE_hpp

#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

class IPULSE {
    
    private :
        string name;
        string node1;
        string node2;
        double I1;
        double I2;
        double ta;
        double ts;
        double td;
        double ton;
        double P;
        int cycles;
    
    public :
        IPULSE();
        IPULSE(string name,
               string node1,
               string node2,
               double I1,
               double I2,
               double ta,
               double ts,
               double td,
               double ton,
               double P,
               int cycles);
        string getName();
        string getNode1();
        string getNode2();
        double getI(double t);
    
};


#endif /* IPULSE_hpp */


#ifndef Inductor_hpp
#define Inductor_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Inductor {
    
    private :
    string name;
    string node1;
    string node2;
    double L;
    double i0; //i(t0)
    double v0; //v(t0)
    double v1; //v(t0-deltaT)
    double v2; //v(t0-2deltaT)
    
    public :
        Inductor();
        Inductor(string name,
                 string node1,
                 string node2,
                 double L,
                 double i0);
        string getName();
        string getNode1();
        string getNode2();
        double getR(double deltaT, int ADMOn);
        double getV(double deltaT, int ADMOn);
        void updateValues(double newI0, double newV0, bool first);
    
};

#endif /* Inductor_hpp */

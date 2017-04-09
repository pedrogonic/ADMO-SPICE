
#ifndef VSIN_hpp
#define VSIN_hpp

#include <stdio.h>
#include <string>
#include <math.h>

#define PI 3.14159265

using namespace std;

class VSIN {
    
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
    VSIN();
    VSIN(string name,
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
    double getV(double t);
    
};


#endif /* VSIN_hpp */

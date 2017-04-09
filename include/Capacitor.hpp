
#ifndef Capacitor_hpp
#define Capacitor_hpp

#include <stdio.h>

#include <string>

using namespace std;

class Capacitor {
    
    private :
        string name;
        string node1;
        string node2;
        double C;
        double v0; //v(t0)
        double i0; //i(t0)
        double i1; //i(t0-deltaT)
        double i2; //i(t0-2deltaT)
        double lastG;
        double lastI;
        bool currCtrl;
    
    public :
        Capacitor();
        Capacitor(string name,
                 string node1,
                 string node2,
                 double C,
                 double v0);
        string getName();
        string getNode1();
        string getNode2();
        double getG(double deltaT, int ADMOn);
        double getR(double deltaT, int ADMOn);
        double getI(double deltaT, int ADMOn);
        void updateValues(double newV0, bool first);
        void setCurrCtrl(bool newCurrCtrl);
        bool getCurrCtrl();
        double getI0();
    
};

#endif /* Capacitor_hpp */

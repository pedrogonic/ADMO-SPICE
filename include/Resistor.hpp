
#ifndef Resistor_hpp
#define Resistor_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Resistor {
    
    private :
        string name;
        string node1;
        string node2;
        double val;
        bool currCtrl;
    
    public :
        Resistor();
        Resistor(string name,string node1,string node2,double val);
        string getName();
        string getNode1();
        string getNode2();
        double getR();
        double getG();
        void setCurrCtrl(bool newCurrCtrl);
        bool getCurrCtrl();
    
};

#endif /* Resistor_hpp */

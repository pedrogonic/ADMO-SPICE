
#ifndef NLResistor_hpp
#define NLResistor_hpp

#include <stdio.h>
#include <string>

using namespace std;

class NLResistor {
    
    private :
        string name;
        string node1;
        string node2;
        double v1;
        double i1;
        double v2;
        double i2;
        double v3;
        double i3;
        double v4;
        double i4;
        bool currCtrl;
    
    public :
        NLResistor();
        NLResistor(string newName,string node1,string node2,
                   double newv1,double newi1,
                   double newv2,double newi2,
                   double newv3,double newi3,
                   double newv4,double newi4);
        string getName();
        string getNode1();
        string getNode2();
        double getG0(double vnode1,double vnode2);
        double getR0(double vnode1,double vnode2);
        double getI0(double vnode1,double vnode2);
        void setCurrCtrl(bool newCurrCtrl);
        bool getCurrCtrl();
    
};

#endif /* NLResistor_hpp */


#ifndef Switch_hpp
#define Switch_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Switch {
    
    private :
        string name;
        string node1;
        string node2;
        string ctrlnode1;
        string ctrlnode2;
        double Gon;
        double Goff;
        double vref;
        bool currCtrl;
    
    public :
    Switch();
    Switch(string name,
          string node1,
          string node2,
          string ctrlnode1,
          string ctrlnode2,
          double Gon,
          double Goff,
          double vref);
    string getName();
    string getNode1();
    string getNode2();
    string getCtrlNode1();
    string getCtrlNode2();
    double getG(double vnode1,double vnode2);
    double getR(double vnode1,double vnode2);
    void setCurrCtrl(bool newCurrCtrl);
    bool getCurrCtrl();
    
};

#endif /* Switch_hpp */

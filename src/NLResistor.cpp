
#include "NLResistor.hpp"
#include "Utils.hpp"
#include <stdio.h>
#include <iostream>

NLResistor::NLResistor() {}

NLResistor::NLResistor(string newName,string newNode1,string newNode2,
                       double newv1,double newi1,
                       double newv2,double newi2,
                       double newv3,double newi3,
                       double newv4,double newi4) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    v1 = newv1;
    i1 = newi1;
    v2 = newv2;
    i2 = newi2;
    v3 = newv3;
    i3 = newi3;
    v4 = newv4;
    i4 = newi4;
    currCtrl = false;
}

string NLResistor::getName() {return name;}

string NLResistor::getNode1() {return node1;}

string NLResistor::getNode2() {return node2;}

void NLResistor::setCurrCtrl(bool newCurrCtrl) {currCtrl = true;}

bool NLResistor::getCurrCtrl() {return currCtrl;}

double NLResistor::getG0(double vnode1, double vnode2) {
    double v = vnode1 - vnode2;
    if (MY_DEBUG) {
        std::cout << "tensao : "<<v<<std::endl;
        std::cout << "teste : "<<v1<<","<<v2<<","<<v3<<","<<v4<<std::endl;
        std::cout << "teste : "<<i1<<","<<i2<<","<<i3<<","<<i4<<std::endl;
    }
    
    double G0 = 0;
    
    if (v < v2) {
        G0 = (i2 - i1) / (v2 - v1);
    }
    else if (v >= v2 && v < v3) {
        G0 = (i3 - i2) / (v3 - v2);
    }
    else if (v >= v3) {
        G0 = (i4 - i3) / (v4 - v3);
    }
    
    return G0;
}

double NLResistor::getR0(double vnode1, double vnode2) {
    return 1/getG0(vnode1, vnode2);
}

double NLResistor::getI0(double vnode1, double vnode2) {
    double v = vnode1 - vnode2;
    
    double G0 = NLResistor::getG0(vnode1, vnode2);
    double I0 = 0;

    if (v < v2)
        I0 = i2 - G0 * v2;
    else if (v >= v2 && v < v3)
        I0 = i3 - G0 * v3;
    else if (v >= v3)
        I0 = i4 - G0 * v4;
    
    return I0;
}

#include "Switch.hpp"

Switch::Switch() {}

Switch::Switch(string newName,
             string newNode1,
             string newNode2,
             string newCtrlnode1,
             string newCtrlnode2,
             double newGon,
             double newGoff,
             double newVref) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
//    newCtrlnode1 = ctrlnode1;
//    newCtrlnode2 = ctrlnode2;
    ctrlnode1 = newCtrlnode1;
    ctrlnode2 = newCtrlnode2;
    Gon = newGon;
    Goff = newGoff;
    vref = newVref;
    currCtrl = false;
}

string Switch::getName() {return name;}

string Switch::getNode1() {return node1;}

string Switch::getNode2() {return node2;}

string Switch::getCtrlNode1() {return ctrlnode1;}

string Switch::getCtrlNode2() {return ctrlnode2;}

void Switch::setCurrCtrl(bool newCurrCtrl) {currCtrl = true;}

bool Switch::getCurrCtrl() {return currCtrl;}

double Switch::getG(double vnode1, double vnode2) {
    double v = vnode1 - vnode2;
    
    if (v >= vref)
        return Gon;
    else
        return Goff;
}

double Switch::getR(double vnode1, double vnode2) {
    return 1/getG(vnode1, vnode2);
}
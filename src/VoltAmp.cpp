
#include "VoltAmp.hpp"

VoltAmp::VoltAmp() {}

VoltAmp::VoltAmp(string newName,
                 string newNode1,
                 string newNode2,
                 string newCtrlnode1,
                 string newCtrlnode2,
                 double newAv) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    ctrlnode1 = newCtrlnode1;
    ctrlnode2 = newCtrlnode2;
    Av = newAv;
}

string VoltAmp::getName() {return name;}

string VoltAmp::getNode1() {return node1;}

string VoltAmp::getNode2() {return node2;}

string VoltAmp::getCtrlNode1() {return ctrlnode1;}

string VoltAmp::getCtrlNode2() {return ctrlnode2;}

double VoltAmp::getAv() {return Av;}

#include "VDC.hpp"

VDC::VDC() {}

VDC::VDC(string newName,string newNode1, string newNode2, double newV) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    V = newV;
}

string VDC::getName() {return name;}

string VDC::getNode1() {return node1;}

string VDC::getNode2() {return node2;}

double VDC::getV() {return V;}
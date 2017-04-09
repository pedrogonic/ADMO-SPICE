
#include "IDC.hpp"

IDC::IDC() {}

IDC::IDC(string newName,string newNode1, string newNode2, double newI) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    I = newI;
}

string IDC::getName() {return name;}

string IDC::getNode1() {return node1;}

string IDC::getNode2() {return node2;}

double IDC::getI() {return I;}
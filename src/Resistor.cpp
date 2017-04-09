
#include "Resistor.hpp"

using namespace std;

Resistor::Resistor(){}

Resistor::Resistor(string newName,string newNode1,string newNode2,double newVal) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    val = newVal;
    currCtrl = false;
}

string Resistor::getName(){
    return name;
}

string Resistor::getNode1() {
    return node1;
}

string Resistor::getNode2() {
    return node2;
}

double Resistor::getR() {
    return val;
}

double Resistor::getG() {
    return 1/val;
}

void Resistor::setCurrCtrl(bool newCurrCtrl) {currCtrl = true;}

bool Resistor::getCurrCtrl() {return currCtrl;}
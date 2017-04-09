
#include "Capacitor.hpp"

Capacitor::Capacitor() {}

Capacitor::Capacitor(string newName,
                   string newNode1,
                   string newNode2,
                   double newC,
                   double newv0) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    C = newC;
    v0 = newv0;
    i0 = 0;
    i1 = 0;
    i2 = 0;
    lastG = 0;
    lastI = 0;
    currCtrl = false;
}

string Capacitor::getName() {return name;}

string Capacitor::getNode1() {return node1;}

string Capacitor::getNode2() {return node2;}

bool Capacitor::getCurrCtrl() {return currCtrl;}

double Capacitor::getI0() {return i0;}

void Capacitor::setCurrCtrl(bool newCurrCtrl) {currCtrl = true;}

double Capacitor::getG(double deltaT, int ADMOn) {
    switch (ADMOn) {
        case 1 : lastG = C / deltaT;
            break;
        case 2 : lastG = 2 * C / deltaT;
            break;
        case 3 : lastG = 12 * C / (5 * deltaT);
            break;
        case 4 : lastG = 8 * C / (3 * deltaT);
            break;
    }
    return lastG;
}

double Capacitor::getR(double deltaT, int ADMOn) {return 1/getG(deltaT, ADMOn);}

double Capacitor::getI(double deltaT, int ADMOn) {
    switch (ADMOn) {
        case 1 : lastI = C * v0 / deltaT;
            break;
        case 2 : lastI = i0 + 2 * C * v0 / deltaT;
            break;
        case 3 : lastI = (8 * i0 - i1) / 5 + 12 * C * v0 / (5*deltaT);
            break;
        case 4 : lastI = (19 * i0 - 5 * i1 + i2) / 9 + 8 * C * v0 / (3*deltaT);
            break;
    }
    return lastI;
}

void Capacitor::updateValues(double newV0, bool first) {
    double newI0 = newV0 * lastG - lastI;
    
    if (first) {
        i2 = newI0;
        i1 = newI0;
    }
    else {
        i2 = i1;
        i1 = i0;
    }
    i0 = newI0;
    v0 = newV0;
}

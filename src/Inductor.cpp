
#include "Inductor.hpp"

Inductor::Inductor() {}

Inductor::Inductor(string newName,
                   string newNode1,
                   string newNode2,
                   double newL,
                   double newi0) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    L = newL;
    i0 = newi0;
    v0 = 0;
    v1 = 0;
    v2 = 0;
}

string Inductor::getName() {return name;}

string Inductor::getNode1() {return node1;}

string Inductor::getNode2() {return node2;}

double Inductor::getR(double deltaT, int ADMOn) {
    switch (ADMOn) {
        default : return L / deltaT; // default = case 1 (Backward Euler)
            break;
        case 2 : return  2 * L / deltaT;
            break;
        case 3 : return 12 * L / (5 * deltaT);
            break;
        case 4 : return 8 * L / (3 * deltaT);
            break;
    }
}

double Inductor::getV(double deltaT, int ADMOn) {
    switch (ADMOn) {
        default : return L * i0 / deltaT; // default = case 1 (Backward Euler)
            break;
        case 2 : return v0 + 2 * L * i0 / deltaT;
            break;
        case 3 : return (8 * v0 - v1) / 5 + 12 * L * i0 / (5*deltaT);
            break;
        case 4 : return (19 * v0 - 5 * v1 + v2) / 9 + 8 * L * i0 / (3*deltaT);
            break;
    }
}

void Inductor::updateValues(double newI0, double newV0, bool first) {
    if (first) {
        v2 = newV0;
        v1 = newV0;
    }
    else {
        v2 = v1;
        v1 = v0;
    }
    v0 = newV0;
    i0 = newI0;
}
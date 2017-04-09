
#include "ISIN.hpp"

ISIN::ISIN() {}

ISIN::ISIN(string newName,
           string newNode1,
           string newNode2,
           double newA0,
           double newA,
           double newF,
           double newTa,
           double newAlfa,
           double newPsi,
           int newCycles) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    A0 = newA0;
    A = newA;
    f = newF;
    ta = newTa;
    alfa = newAlfa;
    psi = newPsi;
    cycles = newCycles;
}

string ISIN::getName() {return name;}

string ISIN::getNode1() {return node1;}

string ISIN::getNode2() {return node2;}

double ISIN::getI(double t) {
    if (t <= ta) {
        
        return A0 + A * sin(PI/180*psi);
    }
    else if (cycles != 0 && t >= cycles / f + ta){
        
        //amortecimento contínuo
        //return A0 + A * exp(-alfa*(t-ta)) * sin(PI/180*psi);
        
        //final constante
        double tfinal = cycles / f + ta;
        return A0 + A * exp(-alfa*(tfinal-ta)) * sin(PI/180*psi);
    }
    else {
        
        return A0 + A * exp(-alfa*(t-ta)) * sin(2*PI*f*(t-ta)+PI/180*psi);
    }
}
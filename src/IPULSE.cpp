
#include "IPULSE.hpp"

IPULSE::IPULSE() {}

IPULSE::IPULSE(string newName,
               string newNode1,
               string newNode2,
               double newI1,
               double newI2,
               double newta,
               double newts,
               double newtd,
               double newton,
               double newP,
               int newcycles) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    I1 = newI1;
    I2 = newI2;
    ta = newta;
    ts = newts;
    td = newtd;
    ton = newton;
    P = newP;
    cycles = newcycles;
}

string IPULSE::getName() {return name;}

string IPULSE::getNode1() {return node1;}

string IPULSE::getNode2() {return node2;}

double IPULSE::getI(double t) {
    double n = t / P;
    
    if(n > cycles && cycles >0) {
        return I1;
    }
    else {
        double T = t - floor(n)*P;
        
        if ( T < ta || T >= (ta + ts + ton + td) )
            return I1;
        else  if ( (ta+ts) <= T && T < (ta + ts + ton) )
            return I2;
        else if ( ta <= T && T < (ta + ts) ) {
            if (ts == 0 ) //Not happening. Failproofing
                return I2;
            else
                return I1 + (I2-I1)*(T-ta)/ts;
        }
        else { // ( (ta + ts + ton) <= T && T < (ta + ts + ton + td) )
            if (td == 0 ) //Not happening. Failproofing
                return I1;
            else
                return I2 + (I1-I2)*(T-ta-ts-ton)/td;
        }
    }
}
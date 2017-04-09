
#include "VPULSE.hpp"

VPULSE::VPULSE() {}

VPULSE::VPULSE(string newName,
               string newNode1,
               string newNode2,
               double newV1,
               double newV2,
               double newta,
               double newts,
               double newtd,
               double newton,
               double newP,
               int newcycles) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    V1 = newV1;
    V2 = newV2;
    ta = newta;
    ts = newts;
    td = newtd;
    ton = newton;
    P = newP;
    cycles = newcycles;
}

string VPULSE::getName() {return name;}

string VPULSE::getNode1() {return node1;}

string VPULSE::getNode2() {return node2;}

double VPULSE::getV(double t) {
    double n = t / P;
    
    if(n > cycles && cycles >0) {
        return V1;
    }
    else {
        double T = t - floor(n)*P;
        
        if ( T < ta || T >= (ta + ts + ton + td) )
            return V1;
        else  if ( (ta+ts) <= T && T < (ta + ts + ton) )
            return V2;
        else if ( ta <= T && T < (ta + ts) ) {
            if (ts == 0 ) //Not happening. Failproofing
                return V2;
            else
                return V1 + (V2-V1)*(T-ta)/ts;
        }
        else { // ( (ta + ts + ton) <= T && T < (ta + ts + ton + td) )
            if (td == 0 ) //Not happening. Failproofing
                return V1;
            else
                return V2 + (V1-V2)*(T-ta-ts-ton)/td;
        }
    }
}
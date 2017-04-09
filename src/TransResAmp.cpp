
#include "TransResAmp.hpp"

TransResAmp::TransResAmp() {}

TransResAmp::TransResAmp(string newName,
                           string newNode1,
                           string newNode2,
                           string newCtrlnode1,
                           string newCtrlnode2,
                           double newRm) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    ctrlnode1 = newCtrlnode1;
    ctrlnode2 = newCtrlnode2;
    Rm = newRm;
    currCtrlIndex = "";
}

string TransResAmp::getName() {return name;}

string TransResAmp::getNode1() {return node1;}

string TransResAmp::getNode2() {return node2;}

string TransResAmp::getCtrlNode1() {return ctrlnode1;}

string TransResAmp::getCtrlNode2() {return ctrlnode2;}

double TransResAmp::getRm() {return Rm;}

void TransResAmp::setCurrCtrlIndex(string newIndex) {currCtrlIndex = newIndex;}

string TransResAmp::getCurrCtrlIndex() {return currCtrlIndex;}
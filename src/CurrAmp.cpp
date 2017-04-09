
#include "CurrAmp.hpp"

CurrAmp::CurrAmp() {}

CurrAmp::CurrAmp(string newName,
                 string newNode1,
                 string newNode2,
                 string newCtrlnode1,
                 string newCtrlnode2,
                 double newAi) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    ctrlnode1 = newCtrlnode1;
    ctrlnode2 = newCtrlnode2;
    Ai = newAi;
    currCtrlIndex = "";
}

string CurrAmp::getName() {return name;}

string CurrAmp::getNode1() {return node1;}

string CurrAmp::getNode2() {return node2;}

string CurrAmp::getCtrlNode1() {return ctrlnode1;}

string CurrAmp::getCtrlNode2() {return ctrlnode2;}

double CurrAmp::getAi() {return Ai;}

void CurrAmp::setCurrCtrlIndex(string newIndex) {currCtrlIndex = newIndex;}

string CurrAmp::getCurrCtrlIndex() {return currCtrlIndex;}
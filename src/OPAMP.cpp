
#include "OPAMP.hpp"

OPAMP::OPAMP() {}

OPAMP::OPAMP(string newName,
             string newNode1,
             string newNode2,
             string newCtrlnode1,
             string newCtrlnode2) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    ctrlnode1 = newCtrlnode1;
    ctrlnode2 = newCtrlnode2;
}

string OPAMP::getName() {return name;}

string OPAMP::getNode1() {return node1;}

string OPAMP::getNode2() {return node2;}

string OPAMP::getCtrlNode1() {return ctrlnode1;}

string OPAMP::getCtrlNode2() {return ctrlnode2;}
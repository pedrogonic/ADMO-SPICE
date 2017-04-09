
#include "TransCondAmp.hpp"

TransCondAmp::TransCondAmp() {}

TransCondAmp::TransCondAmp(string newName,
                 string newNode1,
                 string newNode2,
                 string newCtrlnode1,
                 string newCtrlnode2,
                 double newGm) {
    name = newName;
    node1 = newNode1;
    node2 = newNode2;
    ctrlnode1 = newCtrlnode1;
    ctrlnode2 = newCtrlnode2;
    Gm = newGm;
}

string TransCondAmp::getName() {return name;}

string TransCondAmp::getNode1() {return node1;}

string TransCondAmp::getNode2() {return node2;}

string TransCondAmp::getCtrlNode1() {return ctrlnode1;}

string TransCondAmp::getCtrlNode2() {return ctrlnode2;}

double TransCondAmp::getGm() {return Gm;}
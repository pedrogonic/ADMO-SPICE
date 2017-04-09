
#ifndef OPAMP_hpp
#define OPAMP_hpp

#include <stdio.h>
#include <string>

using namespace std;

class OPAMP {
    
    private :
        string name;
        string node1;
        string node2;
        string ctrlnode1;
        string ctrlnode2;
    
    public :
        OPAMP();
        OPAMP(string name,
              string node1,
              string node2,
              string ctrlnode1,
              string ctrlnode2);
        string getName();
        string getNode1();
        string getNode2();
        string getCtrlNode1();
        string getCtrlNode2();
    
};

#endif /* OPAMP_hpp */

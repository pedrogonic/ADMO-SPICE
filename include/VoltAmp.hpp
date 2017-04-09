
#ifndef VoltAmp_hpp
#define VoltAmp_hpp

#include <stdio.h>
#include <string>

using namespace std;

class VoltAmp {
    
    private :
        string name;
        string node1;
        string node2;
        string ctrlnode1;
        string ctrlnode2;
        double Av;
    
    public :
        VoltAmp();
        VoltAmp(string name,
                string node1,
                string node2,
                string ctrlnode1,
                string ctrlnode2,
                double Av);
        string getName();
        string getNode1();
        string getNode2();
        string getCtrlNode1();
        string getCtrlNode2();
        double getAv();
    
};

#endif /* VoltAmp_hpp */


#ifndef VDC_hpp
#define VDC_hpp

#include <stdio.h>
#include <string>

using namespace std;

class VDC {
    
    protected :
        string name;
        string node1;
        string node2;
        double V;
    
    public :
        VDC();
        VDC(string name,string node1, string node2, double V);
        string getName();
        string getNode1();
        string getNode2();
        double getV();
    
};

#endif /* VDC_hpp */

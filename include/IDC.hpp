
#ifndef IDC_hpp
#define IDC_hpp

#include <stdio.h>
#include <string>

using namespace std;

class IDC {
    
    private :
        string name;
        string node1;
        string node2;
        double I;
    
    public :
        IDC();
        IDC(string name,string node1, string node2, double I);
        string getName();
        string getNode1();
        string getNode2();
        double getI();
    
};

#endif /* IDC_hpp */

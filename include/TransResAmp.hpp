
#ifndef TransResAmp_hpp
#define TransResAmp_hpp

#include <stdio.h>
#include <string>

using namespace std;

class TransResAmp {
    
    private :
        string name;
        string node1;
        string node2;
        string ctrlnode1;
        string ctrlnode2;
        double Rm;
        string currCtrlIndex;
    
    public :
        TransResAmp();
        TransResAmp(string name,
                     string node1,
                     string node2,
                     string ctrlnode1,
                     string ctrlnode2,
                     double Rm);
        string getName();
        string getNode1();
        string getNode2();
        string getCtrlNode1();
        string getCtrlNode2();
        double getRm();
        void setCurrCtrlIndex(string newIndex);
        string getCurrCtrlIndex();
    
};

#endif /* TransResAmp_hpp */

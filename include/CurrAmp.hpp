
#ifndef CurrAmp_hpp
#define CurrAmp_hpp

#include <stdio.h>
#include <string>

using namespace std;

class CurrAmp {
    
    private :
        string name;
        string node1;
        string node2;
        string ctrlnode1;
        string ctrlnode2;
        double Ai;
        string currCtrlIndex;
    
    public :
        CurrAmp();
        CurrAmp(string name,
                string node1,
                string node2,
                string ctrlnode1,
                string ctrlnode2,
                double Ai);
        string getName();
        string getNode1();
        string getNode2();
        string getCtrlNode1();
        string getCtrlNode2();
        double getAi();
        void setCurrCtrlIndex(string newIndex);
        string getCurrCtrlIndex();
    
};

#endif /* CurrAmp_hpp */

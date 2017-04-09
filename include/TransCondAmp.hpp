
#ifndef TransCondAmp_hpp
#define TransCondAmp_hpp

#include <stdio.h>
#include <string>

using namespace std;

class TransCondAmp {
    
    private :
        string name;
        string node1;
        string node2;
        string ctrlnode1;
        string ctrlnode2;
        double Gm;
    
    public :
        TransCondAmp();
        TransCondAmp(string name,
                string node1,
                string node2,
                string ctrlnode1,
                string ctrlnode2,
                double Gm);
        string getName();
        string getNode1();
        string getNode2();
        string getCtrlNode1();
        string getCtrlNode2();
        double getGm();
    
};


#endif /* TransCondAmp_hpp */

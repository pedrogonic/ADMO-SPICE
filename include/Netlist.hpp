
#ifndef Netlist_hpp
#define Netlist_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h> 
#include <algorithm>

#include "Utils.hpp"
#include "Resistor.hpp"
#include "NLResistor.hpp"
#include "Switch.hpp"
#include "Inductor.hpp"
#include "Capacitor.hpp"
#include "VoltAmp.hpp"
#include "CurrAmp.hpp"
#include "TransCondAmp.hpp"
#include "TransResAmp.hpp"
#include "IDC.hpp"
#include "ISIN.hpp"
#include "IPULSE.hpp"
#include "VDC.hpp"
#include "VSIN.hpp"
#include "VPULSE.hpp"
#include "OPAMP.hpp"

using namespace std;

class Netlist {
    
    private :
        vector<string> nodeList;
        vector<string> innerNodeList;
        vector<Resistor> rList;
        vector<NLResistor> nlrList;
        vector<Switch> switchList;
        vector <Inductor> lList;
        vector <Capacitor> cList;
        vector<VoltAmp> voltAmpList;
        vector<CurrAmp> currAmpList;
        vector<TransCondAmp> transCondAmpList;
        vector<TransResAmp> transResAmpList;
        vector<IDC> iDCList;
        vector<ISIN> iSINList;
        vector<IPULSE> iPULSEList;
        vector<VSIN> vSINList;
        vector<VDC> vDCList;
        vector<VPULSE> vPULSEList;
        vector<OPAMP> opampList;
        map<int,int> equivCols;
        map<int,int> equivLines;
        vector<string> unknownsList;
        vector<double> aprox;
        vector<bool> convergence;
        void updateValues();
        long originalSize;
        double finalTime;
        double step;
        int innerStep;
        int n; //AdamsMoulton order
        void checkAddNode(string newNode);
        long getNodePos(string nodeName);
        vector<vector<double> > matrixA;
        vector<double> matrixB;
        bool first;
        vector<double> addCCurr();
    
    public :
        Netlist();
        long getNodesCount();
        void addResistor(Resistor newResistor);
        void addNLResistor(NLResistor newNLResistor);
        void addSwitch(Switch newSwitch);
        void addL(Inductor newL);
        void addC(Capacitor newC);
        void addVoltAmp(VoltAmp newVoltAmp);
        void addCurrAmp(CurrAmp newCurrAmp);
        void addTransCondAmp(TransCondAmp newTransCondAmp);
        void addTransResAmp(TransResAmp newTransResAmp);
        void addIDC(IDC newIDC);
        void addISIN(ISIN newISIN);
        void addIPULSE(IPULSE newIPULSE);
        void addVDC(VDC newVDC);
        void addVSIN(VSIN newVSIN);
        void addVPULSE(VPULSE newVPULSE);
        void addOPAMP(OPAMP newOPAMP);
        void setParams(double newFinalTime,double newStep,int newN,int newInnerStep);
        vector<double> getAprox();
        double getFinalTime();
        double getStep();
        int getInnerStep();
        int getN();
        void sortNodelist();
        bool checkGround();
        vector<string> getUnknownsList();
        void mna(double time, bool first);
        vector<vector<double> > getMatrixA();
        vector<double> getMatrixB();
        bool checkConvergence(vector<double>);
        void newAprox();
        vector<double> getResult();
    
};

#endif /* Netlist_hpp */

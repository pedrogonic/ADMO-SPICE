
#include "Netlist.hpp"

Netlist::Netlist() {
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
    
    nodeList = vector<string>();
    innerNodeList = vector<string>();
    rList = vector<Resistor>();
    nlrList = vector<NLResistor>();
    switchList = vector<Switch>();
    lList = vector<Inductor>();
    cList = vector<Capacitor>();
    voltAmpList = vector<VoltAmp>();
    transCondAmpList = vector<TransCondAmp>();
    transResAmpList = vector<TransResAmp>();
    iDCList = vector<IDC>();
    iSINList = vector<ISIN>();
    iPULSEList = vector<IPULSE>();
    vDCList = vector<VDC>();
    vSINList = vector<VSIN>();
    vPULSEList = vector<VPULSE>();
    opampList = vector<OPAMP>();
    unknownsList = vector<string>();
    aprox = vector<double>();
    convergence = vector<bool>();
    originalSize = 0;
    finalTime = 0;
    step = 0;
    innerStep = 0;
    n = 0;
    matrixA = vector<vector<double> >();
    matrixB = vector<double>();
    equivCols = map<int,int>();
    equivLines = map<int,int>();
}

void Netlist::setParams(double newFinalTime,double newStep,int newN,int newInnerStep){
    finalTime = newFinalTime;
    step = newStep;
    innerStep = newInnerStep;
    n = newN;
}

vector<double> Netlist::getAprox() {return aprox;}

double Netlist::getFinalTime() {return finalTime;}

double Netlist::getStep() {return step;}

int Netlist::getInnerStep() {return innerStep;}

int Netlist::getN() {return n;}

vector<vector<double> > Netlist::getMatrixA() {return matrixA;}

vector<double> Netlist::getMatrixB() {return matrixB;}


long Netlist::getNodesCount() {
    long size = 0;
    size = nodeList.size();
    return size;
}

vector<string> Netlist::getUnknownsList() {
    
    //long index = nodeList.size();
    
    for (int i = 0; i < vDCList.size(); i++)
        innerNodeList.push_back(vDCList[i].getName());
    
    for (int i = 0; i < vSINList.size(); i++)
        innerNodeList.push_back(vSINList[i].getName());
    
    for (int i = 0; i < vPULSEList.size(); i++)
        innerNodeList.push_back(vPULSEList[i].getName());
    
    for (int i = 0; i < voltAmpList.size(); i++)
        innerNodeList.push_back(voltAmpList[i].getName());
    
    for (int i = 0; i < lList.size(); i++)
        innerNodeList.push_back(lList[i].getName());
    
    for (int i = 0; i < currAmpList.size(); i++)
        innerNodeList.push_back(currAmpList[i].getName()+"ctrl");
    
    for (int i = 0; i < transResAmpList.size(); i++) {
        innerNodeList.push_back(transResAmpList[i].getName()+"ctrl");
        innerNodeList.push_back(transResAmpList[i].getName());
    }
    
    originalSize = nodeList.size() + innerNodeList.size();
    
    for (int i = 0; i < nodeList.size(); i++)
        unknownsList.push_back("e" + nodeList[i]);
    
    for (int i = 0; i < innerNodeList.size(); i++)
        unknownsList.push_back("j" + innerNodeList[i]);
    
    for (int i = 0; i < cList.size(); i++) {
        if(!cList[i].getCurrCtrl())
            unknownsList.push_back("j" + cList[i].getName());
    }
    
    for (int i = 0; i < unknownsList.size() ; i++)
        aprox.push_back(0);
    for (int i = 0; i < vDCList.size(); i++) {
        if (vDCList[i].getNode2() == nodeList[0])
            aprox[pos(nodeList,vDCList[i].getNode1())] = vDCList[i].getV();
        else if (vDCList[i].getNode1() == nodeList[0])
            aprox[pos(nodeList,vDCList[i].getNode2())] = -vDCList[i].getV();
    }
    for (int i = 0; i < vSINList.size(); i++){
        if (vSINList[i].getNode2() == nodeList[0])
            aprox[pos(nodeList,vSINList[i].getNode1())] = vSINList[i].getV(0);
        else if (vSINList[i].getNode1() == nodeList[0])
            aprox[pos(nodeList,vSINList[i].getNode2())] = -vSINList[i].getV(0);
    }
    for (int i = 0; i < vPULSEList.size(); i++){
        if (vPULSEList[i].getNode2() == nodeList[0])
            aprox[pos(nodeList,vPULSEList[i].getNode1())] = vPULSEList[i].getV(0);
        else if (vSINList[i].getNode1() == nodeList[0])
            aprox[pos(nodeList,vPULSEList[i].getNode2())] = -vPULSEList[i].getV(0);
    }
    
    //elimination of columns and lines caused by OPAMPs
    vector<string> auxNodes = nodeList;
    equivLines = map<int,int>();
    equivCols = map<int,int>();
    for (int i = 0; i < opampList.size(); i++) {
        int n1 = pos(nodeList, opampList[i].getNode1());
        int n2 = pos(nodeList, opampList[i].getNode2());
        int n3 = pos(nodeList, opampList[i].getCtrlNode1());
        int n4 = pos(nodeList, opampList[i].getCtrlNode2());
        
        if (n1 < n2)
            equivLines.insert(pair<int,int>(n2,n1));
        else
            equivLines.insert(pair<int,int>(n1,n2));
        
        if (n3 < n4)
            equivCols.insert(pair<int,int>(n4,n3));
        else
            equivCols.insert(pair<int,int>(n3,n4));
    }
    
    //prints
    if(VERBOSE) {
        map<int,int>::reverse_iterator p2;
        for(p2 = equivCols.rbegin();p2 != equivCols.rend();++p2) {
            cout << "Columns to add: " << p2->second<<","<<p2->first<<", delete "<<p2->first<<endl;
        }
    }
    
    if(VERBOSE) {
        map<int,int>::reverse_iterator p1;
        for(p1 = equivLines.rbegin();p1 != equivLines.rend();++p1) {
            cout << "Lines to add: " << p1->second<<","<<p1->first<<", delete "<<p1->first<<endl;
        }
    }
    
    if(VERBOSE)
        cout << endl;
    
    return unknownsList;
}

void Netlist::mna(double t,bool newFirst) {
    first = newFirst;
    matrixA = vector<vector<double> >();
    matrixB = vector<double>();
    double deltaT = step/innerStep;
    int order = n;
    if (first) {
        deltaT /= INITIAL_STEP_DIVIDER;
        order = 1;
    }
    
    //Zeroing
    vector<double> zeroes = vector<double> ();
    for (int i = 0; i < originalSize; i++)
        zeroes.push_back(0);
    
    matrixB = zeroes;
    for (int i = 0; i < originalSize; i++)
        matrixA.push_back(zeroes);
    
    //Placing components
    long i1 = 0;
    long i2 = 0;
    long i3 = 0;
    long i4 = 0;
    long i5 = 0;
    long i6 = 0;
    double v1 = 0;
    
    //Resistor
    for (long i = 0; i < rList.size(); i++) {
        i1 = pos(nodeList,rList[i].getNode1());
        i2 = pos(nodeList,rList[i].getNode2());
        matrixA[i1][i1] += rList[i].getG();
        matrixA[i2][i2] += rList[i].getG();
        matrixA[i1][i2] -= rList[i].getG();
        matrixA[i2][i1] -= rList[i].getG();
    }
    //NLResistor
    for (long i = 0; i < nlrList.size(); i++) {
        i1 = pos(nodeList,nlrList[i].getNode1());
        i2 = pos(nodeList,nlrList[i].getNode2());
        v1 = nlrList[i].getG0(aprox[i1],aprox[i2]);
        matrixA[i1][i1] += v1;
        matrixA[i2][i2] += v1;
        matrixA[i1][i2] -= v1;
        matrixA[i2][i1] -= v1;
        if (MY_DEBUG)
            cout <<"G0 " <<v1<< " ================================================"<<endl;
        v1 = nlrList[i].getI0(aprox[i1],aprox[i2]);
        if (MY_DEBUG)
            cout <<"I0 " <<v1<< " ================================================"<<endl;
        matrixB[i1] -= v1;
        matrixB[i2] += v1;
    }
    //Switch
    for (long i = 0; i < switchList.size(); i++) {
        i1 = pos(nodeList,switchList[i].getNode1());
        i2 = pos(nodeList,switchList[i].getNode2());
        i3 = pos(nodeList,switchList[i].getCtrlNode1());
        i4 = pos(nodeList,switchList[i].getCtrlNode2());
        v1 = switchList[i].getG(aprox[i3],aprox[i4]);
        matrixA[i1][i1] += v1;
        matrixA[i2][i2] += v1;
        matrixA[i1][i2] -= v1;
        matrixA[i2][i1] -= v1;
        if (MY_DEBUG) {
            cout << switchList[i].getCtrlNode1()<<","<< switchList[i].getCtrlNode2()<<"=================="<< endl;
            cout << i3<<","<< i4<<"=================="<< endl;
            cout << aprox[i3]<<","<< aprox[i4]<<"=================="<< endl;
            cout << v1 << endl;
        }
    }
    //Inductor
    for (long i = 0; i < lList.size(); i++) {
        i1 = pos(nodeList,lList[i].getNode1());
        i2 = pos(nodeList,lList[i].getNode2());
        i3 = nodeList.size() + pos(innerNodeList,lList[i].getName());
        matrixA[i1][i3] += 1;
        matrixA[i2][i3] -= 1;
        matrixA[i3][i1] -= 1;
        matrixA[i3][i2] += 1;
        matrixA[i3][i3] += lList[i].getR(deltaT,order);
        matrixB[i3] += lList[i].getV(deltaT,order);
    }
    //Capacitor
    for (long i = 0; i < cList.size(); i++) {
        i1 = pos(nodeList,cList[i].getNode1());
        i2 = pos(nodeList,cList[i].getNode2());
        v1 = cList[i].getG(deltaT,order);
        matrixA[i1][i1] += v1;
        matrixA[i2][i2] += v1;
        matrixA[i1][i2] -= v1;
        matrixA[i2][i1] -= v1;
        v1 = cList[i].getI(deltaT,order);
        matrixB[i1] += v1;
        matrixB[i2] -= v1;
    }
    //VDC
    for (long i = 0; i < vDCList.size(); i++) {
        i1 = pos(nodeList,vDCList[i].getNode1());
        i2 = pos(nodeList,vDCList[i].getNode2());
        i3 = nodeList.size() + pos(innerNodeList,vDCList[i].getName());
        matrixA[i1][i3] += 1;
        matrixA[i2][i3] -= 1;
        matrixA[i3][i1] -= 1;
        matrixA[i3][i2] += 1;
        matrixB[i3] -= vDCList[i].getV();
    }
    //VSIN
    for (long i = 0; i < vSINList.size(); i++) {
        i1 = pos(nodeList,vSINList[i].getNode1());
        i2 = pos(nodeList,vSINList[i].getNode2());
        i3 = nodeList.size() + pos(innerNodeList,vSINList[i].getName());
        matrixA[i1][i3] += 1;
        matrixA[i2][i3] -= 1;
        matrixA[i3][i1] -= 1;
        matrixA[i3][i2] += 1;
        matrixB[i3] -= vSINList[i].getV(t);
    }
    //VPULSE
    for (long i = 0; i < vPULSEList.size(); i++) {
        i1 = pos(nodeList,vPULSEList[i].getNode1());
        i2 = pos(nodeList,vPULSEList[i].getNode2());
        i3 = nodeList.size() + pos(innerNodeList,vPULSEList[i].getName());
        matrixA[i1][i3] += 1;
        matrixA[i2][i3] -= 1;
        matrixA[i3][i1] -= 1;
        matrixA[i3][i2] += 1;
        matrixB[i3] -= vPULSEList[i].getV(t);
    }
    //Voltage Amplifier
    for (long i = 0; i < voltAmpList.size(); i++) {
        i1 = pos(nodeList,voltAmpList[i].getNode1());
        i2 = pos(nodeList,voltAmpList[i].getNode2());
        i3 = pos(nodeList,voltAmpList[i].getCtrlNode1());
        i4 = pos(nodeList,voltAmpList[i].getCtrlNode2());
        i5 = nodeList.size() + pos(innerNodeList,voltAmpList[i].getName());
        v1 = voltAmpList[i].getAv();
        matrixA[i1][i5] += 1;
        matrixA[i2][i5] -= 1;
        matrixA[i5][i1] -= 1;
        matrixA[i5][i2] += 1;
        matrixA[i5][i3] += v1;
        matrixA[i5][i4] -= v1;
    }
    //Current Amplifier
    for (long i = 0; i < currAmpList.size(); i++) {
        i1 = pos(nodeList,currAmpList[i].getNode1());
        i2 = pos(nodeList,currAmpList[i].getNode2());
        i3 = pos(nodeList,currAmpList[i].getCtrlNode1());
        i4 = pos(nodeList,currAmpList[i].getCtrlNode2());
        i5 = nodeList.size() + pos(innerNodeList,currAmpList[i].getName()+"ctrl");
        v1 = currAmpList[i].getAi();
        matrixA[i1][i5] += v1;
        matrixA[i2][i5] -= v1;
        matrixA[i3][i5] += 1;
        matrixA[i4][i5] -= 1;
        matrixA[i5][i3] -= 1;
        matrixA[i5][i4] += 1;
    }
    //TransConductance Amplifier
    for (long i = 0; i < transCondAmpList.size(); i++) {
        i1 = pos(nodeList,transCondAmpList[i].getNode1());
        i2 = pos(nodeList,transCondAmpList[i].getNode2());
        i3 = pos(nodeList,transCondAmpList[i].getCtrlNode1());
        i4 = pos(nodeList,transCondAmpList[i].getCtrlNode2());
        v1 = transCondAmpList[i].getGm();
        matrixA[i1][i3] += v1;
        matrixA[i1][i4] -= v1;
        matrixA[i2][i3] -= v1;
        matrixA[i2][i4] += v1;
    }
    //TransImpedance Amplifier
    for (long i = 0; i < transResAmpList.size(); i++) {
        i1 = pos(nodeList,transResAmpList[i].getNode1());
        i2 = pos(nodeList,transResAmpList[i].getNode2());
        i3 = pos(nodeList,transResAmpList[i].getCtrlNode1());
        i4 = pos(nodeList,transResAmpList[i].getCtrlNode2());
        i5 = nodeList.size() + pos(innerNodeList,transResAmpList[i].getName()+"ctrl");
        i6 = nodeList.size() + pos(innerNodeList,transResAmpList[i].getName());
        matrixA[i3][i5] += 1;
        matrixA[i4][i5] -= 1;
        matrixA[i5][i3] -= 1;
        matrixA[i5][i4] += 1;
        matrixA[i1][i6] += 1;
        matrixA[i2][i6] -= 1;
        matrixA[i6][i1] -= 1;
        matrixA[i6][i2] += 1;
        matrixA[i6][i5] += transResAmpList[i].getRm();
    }
    //IDC
    for (long i = 0; i < iDCList.size(); i++) {
        v1 = iDCList[i].getI();
        matrixB[pos(nodeList,iDCList[i].getNode1())] -= v1;
        matrixB[pos(nodeList,iDCList[i].getNode2())] += v1;
    }
    //ISIN
    for (long i = 0; i < iSINList.size(); i++) {
        v1 = iSINList[i].getI(t);
        matrixB[pos(nodeList,iSINList[i].getNode1())] -= v1;
        matrixB[pos(nodeList,iSINList[i].getNode2())] += v1;
    }
    //IPULSE
    for (long i = 0; i < iPULSEList.size(); i++) {
        v1 = iPULSEList[i].getI(t);
        matrixB[pos(nodeList,iPULSEList[i].getNode1())] -= v1;
        matrixB[pos(nodeList,iPULSEList[i].getNode2())] += v1;
    }
    //OPAMP
    //add columns
    map<int,int>::reverse_iterator p;
    for(p = equivCols.rbegin();p != equivCols.rend();++p) {
        //move first to second
        for (long i = 0; i < nodeList.size(); i++)
            matrixA[i][p->second] += matrixA[i][p->first];
    }
    //add lines
    for(p = equivLines.rbegin();p != equivLines.rend();++p) {
        //move first to second
        for (long c = 0; c < nodeList.size(); c++)
            matrixA[p->second][c] += matrixA[c][p->first];
    }
    //remove lines
    for(p = equivLines.rbegin();p != equivLines.rend();++p) {
        //delete first
        matrixA.erase(matrixA.begin()+p->first);
        matrixB.erase(matrixB.begin()+p->first);
    }
    //remove columns
    for(p = equivCols.rbegin();p != equivCols.rend();++p) {
        //delete first
        for (long i = nodeList.size()+innerNodeList.size()-equivLines.size()-1; i > 0; i--)
            matrixA[i].erase(matrixA[i].begin()+p->first);
    }
    
    //Remove GROUND
    matrixB.erase(matrixB.begin());
    matrixA.erase(matrixA.begin());
    for(int i = 0; i < matrixA.size();i++)
        matrixA[i].erase(matrixA[i].begin());
    
}

bool Netlist::checkGround() {
    if (nodeList[0] == "0")
        return true;
    else
        return false;
}

bool Netlist::checkConvergence(vector<double> result) {
    //transformar result pra mesma dimensao do aprox usando equivalencias
    result.insert(result.begin(),0);
    vector<double> resultExp = result;
    map<int,int>::iterator p;
    for(p = equivCols.begin();p != equivCols.end();++p)
        resultExp.insert(resultExp.begin()+p->first,resultExp[p->second]);
    
    bool conv = true;
    convergence = vector<bool>();
    
    for (long i = 0; i < originalSize; i++)
        convergence.push_back(true);
        
    for (long i = 0; i < resultExp.size()-innerNodeList.size(); i++) {
        bool insideConv = true;
        //double err = fabs(resultExp[i] - aprox[i]);
        double err = fabs(resultExp[i] - aprox[i])/resultExp[i];
        if (err > ERROR_TOLERANCE)
            insideConv = false;
        convergence[i] = insideConv;
        if (!insideConv) {
            conv = false;
        }
    }
    
    //Update aproximation with last result
    
    aprox = resultExp;
    
    
    //Update Capacitors e Inductors
    if (conv)
        updateValues();
    
    
    if (MY_DEBUG) {
        cout << "aprox"<<endl;
        for (long i = 0; i <aprox.size();i++)
            cout << aprox[i] << "   ";
        cout << endl;
        cout << "convergence"<<endl;
        for (long i = 0; i <convergence.size();i++)
            cout << convergence[i] << "   ";
        cout << endl;
    }
    
    if (DEBUG_APROX) {
        cout << "aprox"<<endl;
        for (long i = 0; i <aprox.size();i++)
            cout << aprox[i] << "   ";
        cout << endl;
        cout << "convergence"<<endl;
        for (long i = 0; i <convergence.size();i++)
            cout << convergence[i] << "   ";
        cout << endl;
    }
    
    return conv;
}

void Netlist::newAprox() {
    //unsigned int time_ui = static_cast<unsigned int>( time(NULL) );
    //srand( time_ui );
//    time_t seconds;
//    time(&seconds);
//    srand((unsigned int) seconds);
    
    for (long i = 0; i < convergence.size(); i++){
        if (!convergence[i]) {
            double n = (rand() % RANDOM_RANGE)*pow(-1,rand()% 2);
            if (DEBUG_APROX)
                cout << "new aprox: " <<n<<endl;
            aprox[i] = n;
        }
    }
}

void Netlist::updateValues() {
    for (long i = 0; i < lList.size(); i++)
        lList[i].updateValues(aprox[nodeList.size()+vDCList.size()+vSINList.size()+vPULSEList.size()+voltAmpList.size()+i]
                              , aprox[pos(nodeList,lList[i].getNode1())]-aprox[pos(nodeList,lList[i].getNode2())], first);
    for (long i = 0; i < cList.size(); i++)
        cList[i].updateValues(aprox[pos(nodeList,cList[i].getNode1())]-aprox[pos(nodeList,cList[i].getNode2())], first);
}

vector<double> Netlist::addCCurr() {
    vector<double> ret = vector<double>();
    for (long i = 0; i < cList.size(); i++)
        ret.push_back(cList[i].getI0());
    return ret;
}

vector<double> Netlist::getResult() {
    vector<double> aux = aprox;
    vector<double> cCurr = addCCurr();
    aux.insert(aux.end(),cCurr.begin(),cCurr.end());
    
    return aux;
}

void Netlist::checkAddNode(string newNode) {
    if (nodeList.empty() && newNode != "")
        nodeList.push_back(newNode);
    else if(std::find(nodeList.begin(),nodeList.end(),newNode) == nodeList.end()  && newNode != "")
        nodeList.push_back(newNode);
}

void Netlist::sortNodelist() {
    sort(nodeList.begin(),nodeList.end());
    if(VERBOSE) {
        cout << nodeList.size() << " nodes:" <<endl;
        cout << nodeList[0];
        for (int i = 1;i < nodeList.size(); i++)
            cout << SEPARATOR << nodeList[i];
        cout << endl << endl;
    }
}

long Netlist::getNodePos(string nodeName) {
    long pos = find(nodeList.begin(),nodeList.end(),nodeName) - nodeList.begin();
    return pos;
}

void Netlist::addResistor(Resistor newResistor){
    rList.push_back(newResistor);
    Netlist::checkAddNode(newResistor.getNode1());
    Netlist::checkAddNode(newResistor.getNode2());
}

void Netlist::addNLResistor(NLResistor newNLResistor){
    nlrList.push_back(newNLResistor);
    Netlist::checkAddNode(newNLResistor.getNode1());
    Netlist::checkAddNode(newNLResistor.getNode2());
}

void Netlist::addSwitch(Switch newSwitch){
    switchList.push_back(newSwitch);
    Netlist::checkAddNode(newSwitch.getNode1());
    Netlist::checkAddNode(newSwitch.getNode2());
    Netlist::checkAddNode(newSwitch.getCtrlNode1());
    Netlist::checkAddNode(newSwitch.getCtrlNode2());
}

void Netlist::addL(Inductor newL) {
    lList.push_back(newL);
    Netlist::checkAddNode(newL.getNode1());
    Netlist::checkAddNode(newL.getNode2());
}
void Netlist::addC(Capacitor newC) {
    cList.push_back(newC);
    Netlist::checkAddNode(newC.getNode1());
    Netlist::checkAddNode(newC.getNode2());
}

void Netlist::addVoltAmp(VoltAmp newVoltAmp){
    voltAmpList.push_back(newVoltAmp);
    Netlist::checkAddNode(newVoltAmp.getNode1());
    Netlist::checkAddNode(newVoltAmp.getNode2());
    Netlist::checkAddNode(newVoltAmp.getCtrlNode1());
    Netlist::checkAddNode(newVoltAmp.getCtrlNode2());
}

void Netlist::addCurrAmp(CurrAmp newCurrAmp){
    currAmpList.push_back(newCurrAmp);
    Netlist::checkAddNode(newCurrAmp.getNode1());
    Netlist::checkAddNode(newCurrAmp.getNode2());
    Netlist::checkAddNode(newCurrAmp.getCtrlNode1());
    Netlist::checkAddNode(newCurrAmp.getCtrlNode2());
}

void Netlist::addTransCondAmp(TransCondAmp newTransCondAmp){
    transCondAmpList.push_back(newTransCondAmp);
    Netlist::checkAddNode(newTransCondAmp.getNode1());
    Netlist::checkAddNode(newTransCondAmp.getNode2());
    Netlist::checkAddNode(newTransCondAmp.getCtrlNode1());
    Netlist::checkAddNode(newTransCondAmp.getCtrlNode2());
}

void Netlist::addTransResAmp(TransResAmp newTransResAmp){
    transResAmpList.push_back(newTransResAmp);
    Netlist::checkAddNode(newTransResAmp.getNode1());
    Netlist::checkAddNode(newTransResAmp.getNode2());
    Netlist::checkAddNode(newTransResAmp.getCtrlNode1());
    Netlist::checkAddNode(newTransResAmp.getCtrlNode2());
}

void Netlist::addIDC(IDC newIDC){
    iDCList.push_back(newIDC);
    Netlist::checkAddNode(newIDC.getNode1());
    Netlist::checkAddNode(newIDC.getNode2());
}

void Netlist::addISIN(ISIN newISIN){
    iSINList.push_back(newISIN);
    Netlist::checkAddNode(newISIN.getNode1());
    Netlist::checkAddNode(newISIN.getNode2());
}

void Netlist::addIPULSE(IPULSE newIPULSE){
    iPULSEList.push_back(newIPULSE);
    Netlist::checkAddNode(newIPULSE.getNode1());
    Netlist::checkAddNode(newIPULSE.getNode2());
}

void Netlist::addVDC(VDC newVDC){
    vDCList.push_back(newVDC);
    Netlist::checkAddNode(newVDC.getNode1());
    Netlist::checkAddNode(newVDC.getNode2());
}

void Netlist::addVSIN(VSIN newVSIN){
    vSINList.push_back(newVSIN);
    Netlist::checkAddNode(newVSIN.getNode1());
    Netlist::checkAddNode(newVSIN.getNode2());
}

void Netlist::addVPULSE(VPULSE newVPULSE){
    vPULSEList.push_back(newVPULSE);
    Netlist::checkAddNode(newVPULSE.getNode1());
    Netlist::checkAddNode(newVPULSE.getNode2());
}

void Netlist::addOPAMP(OPAMP newOPAMP){
    opampList.push_back(newOPAMP);
    Netlist::checkAddNode(newOPAMP.getNode1());
    Netlist::checkAddNode(newOPAMP.getNode2());
    Netlist::checkAddNode(newOPAMP.getCtrlNode1());
    Netlist::checkAddNode(newOPAMP.getCtrlNode2());
}
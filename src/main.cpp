
#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <time.h>

#include "Netlist.hpp"
#include "LESolver.hpp"

int main(int argc, const char * argv[]) {

	clock_t tStart = clock();
	bool tranAnalysis = false;
	
	
	//USAGE
	if (argc != 2) {
		string extension = "";
		if (WINDOWS)
			extension = ".exe";
		cout << "usage: admo" << extension << " input_file"<<endl;
		return 11;
	}
	
	
	//GET ARGS
	string filename;
	filename = argv[1];
	
	//Initializing Netlist
	Netlist netlist;
	
	//Reading .net file and adding components
	string line;
	vector<string> param;
	int lineNr = 2;
	vector<string> unknownsList;
	try {
		ifstream myfile(filename, ios_base::binary);
		if (myfile.is_open())
		{
			if(VERBOSE)
				cout << "Netlist: " << endl;
			getline (myfile,line); //skip first
			while ( getline (myfile,line) )
			{
				//Delete end of line cross-platform
				string::size_type pos = 0;
				while ( ( pos = line.find (13,pos) ) != string::npos ) //delete '\r' or CR
					line.erase ( pos, 1 );
				pos = 0;
				while ( ( pos = line.find (10,pos) ) != string::npos ) //delete '\n' or LF
					line.erase ( pos, 1 );
				if(VERBOSE)
					cout << line <<endl;
				
				param = split(line, ' ');
				try {
					switch (param[0][0]) {
						case 'R':
							if (param.size() < 4)
								throw(1);
							netlist.addResistor(Resistor(param[0],param[1],param[2],stod(param[3])));
							break;
						case 'N':
							if (param.size() < 11)
								throw(1);
							netlist.addNLResistor(NLResistor(param[0],param[1],param[2]
																		 ,stod(param[3]),stod(param[4]),stod(param[5])
																		 ,stod(param[6]),stod(param[7]),stod(param[8])
																		 ,stod(param[9]),stod(param[10])));
							break;
						case '$' :
							if (param.size() < 8)
								throw(1);
							if(MY_DEBUG)
								cout << param[3]<<","<<param[4]<<endl;
							netlist.addSwitch(Switch(param[0],param[1],param[2],param[3],param[4]
															 ,stod(param[5]),stod(param[6]),stod(param[7])));
							break;
						case 'L': {
							if (param.size() < 4)
								throw(1);
							double ic = 0;
							if (param.size() > 4)
								ic = stod(param[4].substr(3));
							netlist.addL(Inductor(param[0],param[1],param[2],stod(param[3]),ic));
							break;
						}
						case 'C': {
							if (param.size() < 4)
								throw(1);
							double ic = 0;
							if (param.size() > 4)
								ic = stod(param[4].substr(3));
							netlist.addC(Capacitor(param[0],param[1],param[2],stod(param[3]),ic));
							break;
						}
						case 'E':
							if (param.size() < 6)
								throw(1);
							netlist.addVoltAmp(VoltAmp(param[0],param[1],param[2],param[3],param[4],stod(param[5])));
							break;
						case 'F':
							if (param.size() < 6)
								throw(1);
							netlist.addCurrAmp(CurrAmp(param[0],param[1],param[2],param[3],param[4],stod(param[5])));
							break;
						case 'G':
							if (param.size() < 6)
								throw(1);
							netlist.addTransCondAmp(TransCondAmp(param[0],param[1],param[2],param[3],param[4],stod(param[5])));
							break;
						case 'H':
							if (param.size() < 6)
								throw(1);
							netlist.addTransResAmp(TransResAmp(param[0],param[1],param[2],param[3],param[4],stod(param[5])));
							break;
						case 'I': {
							if (param.size() < 5)
								throw(1);
							if (param[3] == "DC")
								netlist.addIDC(IDC(param[0],param[1],param[2],stod(param[4])));
							else if(param[3] == "SIN") {
								if (param.size() < 11)
									throw(1);
								netlist.addISIN(ISIN(param[0],param[1],param[2]
														   ,stod(param[4]),stod(param[5]),stod(param[6])
														   ,stod(param[7]),stod(param[8]),stod(param[9]),stoi(param[10])));
							}
							else if(param[3] == "PULSE") {
								if (param.size() < 12)
									throw(1);
								netlist.addIPULSE(IPULSE(param[0],param[1],param[2]
																 ,stod(param[4]),stod(param[5]),stod(param[6]),stod(param[7])
																 ,stod(param[8]),stod(param[9]),stod(param[10]),stoi(param[11])));
							}
							break;
						}
						case 'V': {
							if (param.size() < 5)
								throw(1);
							if (param[3] == "DC")
								netlist.addVDC(VDC(param[0],param[1],param[2],stod(param[4])));
							else if(param[3] == "SIN") {
								if (param.size() < 11)
									throw(1);
								netlist.addVSIN(VSIN(param[0],param[1],param[2]
														   ,stod(param[4]),stod(param[5]),stod(param[6])
														   ,stod(param[7]),stod(param[8]),stod(param[9]),stoi(param[10])));
							}
							else if(param[3] == "PULSE") {
								if (param.size() < 12)
									throw(1);
								netlist.addVPULSE(VPULSE(param[0],param[1],param[2]
																 ,stod(param[4]),stod(param[5]),stod(param[6]),stod(param[7])
																 ,stod(param[8]),stod(param[9]),stod(param[10]),stoi(param[11])));
							}
							break;
						}
						case 'O': {
							netlist.addOPAMP(OPAMP(param[0],param[1],param[2],param[3],param[4]));
							break;
						}
						case '.':
							if (param[0] != ".TRAN")
								throw 4;
							if (param.size() < 6)
								throw 1;
							if (stoi(param[3].substr(4)) < 1 || stoi(param[3].substr(4)) > 4)
								throw 5;
							netlist.setParams(stod(param[1]), stod(param[2]), stoi(param[3].substr(4)), stod(param[4]));
							tranAnalysis = true;
							break;
						case '*':
							break;
						default:
							throw 3;
							break;
					}
				}catch(const std::invalid_argument& ia){
					throw 2;
				}catch(exception& e) {
					cout << "Standard exception: " << e.what() << endl;
					throw -1;
				}
				lineNr++;
			}
			myfile.close();
			if(!tranAnalysis)
				throw 7;
			if(VERBOSE)
				cout << endl;
		}
		
		else
			throw(0);
	}catch(int e){
		//TODO : class for exceptions
		cout << "Exception: ";
		switch (e) {
			case 0 :
				cout << "Unable to open file " << filename <<endl;
				break;
			case 1 :
				cout << "Bad parameters. Error at line: " << lineNr <<endl;
				break;
			case 2 :
				cout << "Bad value. Error at line: " << lineNr <<endl;
				break;
			case 3 :
				cout << "Unsupported component at line: " << lineNr <<endl;
				break;
			case 4 :
				cout << "Unsupported type of analysis" <<endl;
				break;
			case 5 :
				cout << "Unsupported Adams Moulton order. Available options: 1 ~ 4." <<endl;
				break;
			case 7 :
				cout << "No Analysis type configuration." <<endl;
				break;
			default :
				break;
		}
		cout << endl << "Execution time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" <<endl;
		return e;
	}
	
	vector<vector<double> > resultOut = vector<vector<double> >();
	
	//sort nodelist
	netlist.sortNodelist();
	
	//check ground
	if (!netlist.checkGround()) {
		cout << endl << "Exception: ";
		cout << "Please specify GROUND node by naming it '0'."<<endl;
		cout << endl << "Execution time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" <<endl;
		return 6;
	}
	
	//get answer array
	unknownsList = netlist.getUnknownsList();
	
	if(VERBOSE ){
		cout << "Unknown: " << endl;
		cout << unknownsList[0];
		for (int i = 1;i < unknownsList.size(); i++)
			cout << SEPARATOR + unknownsList[i];
		cout << endl;
	}
	
	//unknownsList.insert(unknownsList.begin(),"t");
	
	
	//First aproximation
	if(VERBOSE) {
		vector<double> aprox = netlist.getAprox();
		cout <<endl<< "First aproximation:" <<endl;
		cout << aprox[0];
		for (int i = 1;i < aprox.size(); i++)
			cout << SEPARATOR << aprox[i];
		cout << endl << endl;
	}
	
	
	cout << "====BEGIN====" << endl;
	
	
	//Solve
	LESolver le;
	double stepControl = 0;
	bool first = true;
	bool newtonRaphson = false;
	bool newAprox = false;
	bool impossible = false;
	int newtonRaphsonCount1 = 0;
	int newtonRaphsonCount2 = 0;
	vector<double> matrixB;
	vector<vector<double> > matrixA;
	vector<double> result;
	vector<double> solution;
	for (double time = 0;time < netlist.getFinalTime(); time += netlist.getStep()/netlist.getInnerStep()) {
		
		if (time != 0)
			first = false;
		
		//Newton-Rapshon loop
		while (!newtonRaphson) {
			
			newtonRaphsonCount1++;
			if (MY_DEBUG || DEBUG_APROX) {
				cout << "Newton Raphson count 1: "<< newtonRaphsonCount1<<endl;
			}
			if (newtonRaphsonCount1 == MAX_NR1) {
				newtonRaphsonCount1 = 0;
				newtonRaphsonCount2++;
				
				if (MY_DEBUG || DEBUG_APROX) {
					cout << "Newton Raphson count 2: "<<newtonRaphsonCount2<<endl;
				}
				if (newtonRaphsonCount2 == MAX_NR2) {
					if (impossible) {
						cout << endl << "Impossible system.";
					} else {
						cout << endl << "Exception: ";
						cout << "Convergence failed after " << MAX_NR2 << " randomizations at time " << time << endl;
					}
					cout << endl << "Execution time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" <<endl;
					return 10;
				}
				
				//Get new first aproximation
				//if (first) {
					netlist.newAprox();
					newAprox = true;
					impossible = false;
				/*}
				else {
					cout << endl << "Exception: ";
					cout << "Convergence failed after " << MAX_NR1 << " aproximations!" << endl;\
					cout << endl << "Execution time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" <<endl;
					return 10;
				}*/
			}
			
			//[A]*[unknown] = [B], passing time and if it's the first time, in which case deltaT = deltaT/INITIAL_STEP_DIVIDER
			netlist.mna(time,first);
			
			//Get [A] and [B]
			matrixA = netlist.getMatrixA();
			matrixB = netlist.getMatrixB();
			
			//Print [A] and [B]
			if (VERBOSE && first && newtonRaphsonCount1 == 1 && newtonRaphsonCount2 == 0) {
				cout << "Initial matrix A:" << endl;
				for (int i = 0; i<matrixA.size();i++) {
					for (int c = 0; c<matrixA[i].size();c++)
						cout << matrixA[i][c] << "   ";
					cout <<endl;
				}
				cout << endl <<"Initial matrix B:" << endl;
				for (int i = 0; i<matrixB.size();i++) {
						cout << matrixB[i] << endl;
				}
				cout <<endl;
			}
			
			//Pass [A] and [B] to Cramer, getting [Result]
			try {
				solution = le.cramer(matrixA,matrixB);
			}catch (int e) {
				switch (e) {
					case 8 :
						cout << "Internal error: unmatching matrices sizes." << endl;
						cout << endl << "Execution time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" <<endl;
						return 8;
						break;
					case 9 :
						//cout << "0 den"<<endl;
						impossible = true;
						newtonRaphsonCount1 = MAX_NR1-1;
					default :
						break;
				}
			}
			
			//Pass [Result] to netlist. Check with aproximation.
			if (!impossible)
				newtonRaphson = netlist.checkConvergence(solution);
			
		}
		
		
		//Getting final result for current time
		result = netlist.getResult();
		
		if(MY_DEBUG) {
			for (int i = 0; i<result.size();i++) {
				cout << result[i] << "   ";
			}
			cout <<endl;
		}
		
		
		if (stepControl == 0) {
			//copy result to vector<double> result;
			result.insert(result.begin(),time);
			resultOut.push_back(result);
		}
		
		//print
		if(MY_DEBUG) {
			cout <<"time " << time << endl;
			for (int i = 0; i<matrixA.size();i++) {
				for (int c = 0; c<matrixA[i].size();c++)
					cout << matrixA[i][c] << "   ";
				cout <<endl;
			}
			for (int i = 0; i<matrixB.size();i++) {
				cout << matrixB[i] << endl;
			}
			cout <<endl;
		}
		
		stepControl += netlist.getStep()/netlist.getInnerStep();
		if (stepControl == netlist.getStep())
			stepControl = 0;
		
		newtonRaphson = false;
		newtonRaphsonCount1 = 0;
		newtonRaphsonCount2 = 0;
	}
	
	
	cout << "=====END=====" << endl;
	
	
	//Generating output file
	vector<string> path1 = split(filename,'\\'); //Getting path for Win
	vector<string> path2 = split(path1[path1.size()-1],'/'); //Getting path for Unix
	string outname = path2[path2.size()-1].substr(0,path2[path2.size()-1].size()-4); //Removing ".net"
	
	string sep = "/";
	if (WINDOWS)
		sep = "\\";
	outname = "output"+sep+outname+"."+OUT_EXT;
	
	ofstream outFile;
	outFile.open(outname);
	
	outFile << "t";
	for (long i = 0; i < unknownsList.size(); i++)
		outFile << SEPARATOR << unknownsList[i];
	outFile << endl;
	for (long i = 0; i < resultOut.size(); i++) {
		outFile << resultOut[i][0];
		for (long c = 1; c < resultOut[i].size(); c++)
			outFile << SEPARATOR << resultOut[i][c];
		outFile << endl;
	}
	
	outFile.close();
	cout << "Generated output file " + outname <<endl;
	
	cout << "Execution time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" <<endl;
		
    return 0;
}

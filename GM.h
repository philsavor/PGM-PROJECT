/*
 * GM.h
 *
 *  Created on: Mar 25, 2013
 *      Author: Vibhav Gogate
 *				The University of Texas at Dallas
 *				All rights reserved
 */

#ifndef GM_H_
#define GM_H_

#include <iostream>
#include <fstream>
#include <set>
#include "Variable.h"
#include "Function.h"
#include "Hgr.h"

using namespace std;

struct GM
{
	vector<Variable*> variables;
	vector<Function*> functions;
	void readUAIGM(char* uaifilename);
	void generateHmetisInput();  //generate hmetis input file from UAI format
	void generateSeparator(vector<int>& separator,Hgr& hgr);
    void outputSeparator(vector<int>separator,int level,int num_child,string output_file);
    void generateHgrFile(Hgr& hgr, int level,int num_child);
    void splitHgrFile(Hgr& hgr, int level);
	void getSeparatorAndSplit(int level,int num_child,string outputFile);   //arguments: level , num_child
    void outputResult(string outputFile);   //output info about pseudo tree
};

#endif /* GM_H_ */

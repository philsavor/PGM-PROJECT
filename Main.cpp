/*
 * Main.cpp
 *
 *  Created on: Mar 25, 2013
 *      Author: Vibhav Gogate
 *				The University of Texas at Dallas
 *				All rights reserved
 */




#include "GM.h"

int main(int argc, char* argv[])
{
//	if (argc < 2){
//		cerr<<"Usage: "<<argv[0]<<" <uaifile> <evidfile>\n";
//		exit(-1);
//	}
	GM gm;
//	gm.readUAIGM(argv[1]);

	/*generate hmetis input file from UAI format
	 *    *.uai -> ghrs/hgr.0.0
	 */
	gm.generateHmetisInput();

	/*use hmetis input file hgr.0.0 to get separator nodes and output them to output File
	 *then split hgr.0.0 into hgr.1.0 and hgr.1.1
	 *Divide-and-Conquer
	 */
	string output_file = "pesudo_tree.out";
	gm.getSeparatorAndSplit(0,0,output_file);   //arguments: level , num_child
	gm.outputResult(output_file);   //output info about pseudo tree

}

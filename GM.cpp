/*
 * GM.cpp
 *
 *  Created on: Mar 25, 2013
 *      Author: Vibhav Gogate
 *				The University of Texas at Dallas
 *				All rights reserved
 */
#include "GM.h"
#include <fstream>
#include <cstdlib>
#include <set>
#include <string>
using namespace std;
void GM::readUAIGM(char* uaifilename) {
	ifstream infile(uaifilename);
	if(!infile.good()){
		cerr<<"Error opening GM file\n";
		exit(-1);
	}
	int num_variables;
	string tmp_string;
	infile >> tmp_string;
	if (tmp_string.compare("BAYES") == 0) {
		infile >> num_variables;
		// Read domains
		variables = vector<Variable*>(num_variables);
		for (int i = 0; i < num_variables; i++) {
			variables[i] = new Variable();
			variables[i]->id=i;
			infile>>variables[i]->d;
		}
		int num_functions;
		infile >> num_functions;
		vector<vector<Variable*> > parents(num_functions);
		vector<int> func_order(num_functions);
		for (int i = 0; i < num_functions; i++) {
			// Read parents of variables
			int num_parents;
			infile >> num_parents;
			num_parents--;
			vector<Variable*> curr_parents(num_parents);
			for (int j = 0; j < num_parents; j++) {
				int temp;
				infile >> temp;
				curr_parents[j] = variables[temp];
			}
			int var;
			infile >> var;
			parents[var] = curr_parents;
			func_order[i]=var;
		}
		functions = vector<Function*>(num_functions);
		for (int i = 0; i < num_functions; i++) {

			int var=func_order[i];
			int num_probabilities;
			infile>>num_probabilities;
			functions[var] = new Function();
			functions[var]->id=i;
			vector<Variable*> unsorted_variables;
			functions[var]->variables=parents[var];
			functions[var]->variables.push_back(variables[var]);
			unsorted_variables=functions[var]->variables;
			sort(functions[var]->variables.begin(), functions[var]->variables.end(),less_than_comparator_variable);
			functions[var]->table = vector < ldouble > (num_probabilities);
			for (int j = 0; j < num_probabilities; j++) {
				Variable::setAddress(unsorted_variables, j);
				infile>>functions[var]->table[Variable::getAddress(functions[var]->variables)];
			}
		}
	} else  {
		infile >> num_variables;
		// Read domains
		variables = vector<Variable*>(num_variables);
		for (int i = 0; i < num_variables; i++) {
			variables[i] = new Variable();
			variables[i]->id = i;
			infile >> variables[i]->d;
		}
		int num_functions;
		infile >> num_functions;
		vector < vector<Variable*> > scope(num_functions);
		for (int i = 0; i < num_functions; i++) {
			// Read parents of variables
			int num_vars_in_func;
			infile >> num_vars_in_func;
			scope[i] = vector<Variable*>(num_vars_in_func);
			for (int j = 0; j < num_vars_in_func; j++) {
				int temp;
				infile >> temp;
				scope[i][j] = variables[temp];
			}
		}
		functions = vector<Function*>(num_functions);
		for (int i = 0; i < num_functions; i++) {
			int num_probabilities;
			infile >> num_probabilities;
			functions[i] = new Function();
			functions[i]->id=i;
			functions[i]->variables=scope[i];
			sort(functions[i]->variables.begin(), functions[i]->variables.end(),less_than_comparator_variable);
			functions[i]->table = vector < ldouble > (num_probabilities);
			for (int j = 0; j < num_probabilities; j++) {
				Variable::setAddress(scope[i], j);
				infile >> functions[i]->table[Variable::getAddress(functions[i]->variables)];
			}
		}
	}
	infile.close();
}

void GM::generateHmetisInput(){

}

void GM::generateSeparator(vector<int>& separator,Hgr& hgr){
    //get separator nodes using hgr.l.n and hgr.l.n.part2
	int num_edges = hgr.edges.size();
	int num_nodes = hgr.nodes.size()-1;
	//set separator
	int count = 0;
	    for(int i = 0 ; i < num_edges; i++){
	    	int sector0 = hgr.edges[i]->nodes[0]->getSectorId();
	    	int sector1 = hgr.edges[i]->nodes[1]->getSectorId();
	    	if(sector0 != sector1){
	    		hgr.edges[i]->nodes[0]->setSeparator(true);
	    		hgr.edges[i]->nodes[1]->setSeparator(true);
	    		count ++;
	    	}
	    }
	    cout<<"count:"<<count<<endl;
	    int num_sector0_nonSprt = 0;
	    int num_sector1_nonSprt = 0;
	    for(int i = 1 ; i <= num_nodes; i++){
	        if(hgr.nodes[i]->getSectorId() == 0 && hgr.nodes[i]->isSeparator()== false)
	        	num_sector0_nonSprt ++;

	        if(hgr.nodes[i]->getSectorId() == 1 && hgr.nodes[i]->isSeparator()== false)
	            num_sector1_nonSprt ++;
	    }
	    if(num_sector0_nonSprt <= num_sector1_nonSprt){
	    	for(int i = 1 ; i <= num_nodes; i++){
	    	     if(hgr.nodes[i]->getSectorId() == 0 && hgr.nodes[i]->isSeparator()== true)
	    	    	 hgr.nodes[i]->setSeparator(false);
	    	}
	    }else{
	    	for(int i = 1 ; i <= num_nodes; i++){
	    	    if(hgr.nodes[i]->getSectorId() == 1 && hgr.nodes[i]->isSeparator()== true)
	    	    	hgr.nodes[i]->setSeparator(false);
	    	}
	    }

	    separator = vector<int>(0);
	    for(int i = 1 ; i <= num_nodes; i++){
	    	 if(hgr.nodes[i]->isSeparator()== true)
	    	     separator.push_back(hgr.nodes[i]->original_id);
	    }
}

void GM::outputSeparator(vector<int>separator,int level,int num_child,string output_file){
	ofstream outfile;
	outfile.open (output_file, ios::out | ios::app);
	for(int i = 0 ; i < separator.size(); i++){
		outfile << separator[i] << " " << level << " " << num_child <<endl;
	}
	if(separator.size() == 0)
		outfile << "0" << " " << level << " " << num_child <<endl;
}

void GM::generateHgrFile(Hgr& hgr, int level,int num_child){
     string file_path = "./hgrs/hgr." + to_string(level) + "." + to_string(num_child);
     ofstream outfile(file_path);
     outfile << hgr.edges.size() <<" ";
     outfile << hgr.nodes.size()-1<<endl;
     for(int i = 0 ; i < hgr.edges.size(); i++){
    	 outfile<< hgr.edges[i]->nodes[0]->id<<" "
    			<< hgr.edges[i]->nodes[1]->id<<endl;
     }

     outfile.close();

     string original_file_path = "./hgrs/hgr." + to_string(level) + "."
    		                     + to_string(num_child)+ ".original";
     ofstream orifile(original_file_path);
     for(int i = 1 ; i < hgr.nodes.size(); i++){
    	 orifile<< hgr.nodes[i]->id<<" "
         << hgr.nodes[i]->original_id<<endl;
      }

    outfile.close();
}

void GM::splitHgrFile(Hgr& hgr,int level){
    //generate child file: hgr.(l+1).0, hgr.(l+1).1,  ,hgr.(l+1).*.original
    for(int i = 0 ; i < hgr.edges.size(); i++){
    	if(hgr.edges[i]->nodes[0]->isSeparator()==true ||
    	   hgr.edges[i]->nodes[1]->isSeparator()==true	){
    		hgr.edges.erase(hgr.edges.begin() + i);
    		i--;
    	}
    }
    for(int i = 1 ; i < hgr.nodes.size();i++){
    	if(hgr.nodes[i]->isSeparator() == true){
    		hgr.nodes.erase(hgr.nodes.begin()+i);
    		i--;
    	}
    }
    vector<Node*> nodes0(1),nodes1(1);
    vector<Edge*> edges0(0),edges1(0);
    for(int i = 0 ; i < hgr.edges.size(); i++){
        if(hgr.edges[i]->nodes[0]->getSectorId()==0 ){
        	edges0.push_back(hgr.edges[i]);
        }else
        	edges1.push_back(hgr.edges[i]);
    }
    for(int i = 1 ; i < hgr.nodes.size(); i++){
        if(hgr.nodes[i]->getSectorId()==0 ){
        	nodes0.push_back(hgr.nodes[i]);
        }else
        	nodes1.push_back(hgr.nodes[i]);
    }
    Hgr hgr0;
    hgr0.edges = edges0;
    hgr0.nodes = nodes0;

    Hgr hgr1;
    hgr1.edges = edges1;
    hgr1.nodes = nodes1;

    for(int i = 1 ; i < hgr0.nodes.size(); i++){
        hgr0.nodes[i]->id = i;
    }
    for(int i = 1 ; i < hgr1.nodes.size(); i++){
        hgr1.nodes[i]->id = i;
    }

    generateHgrFile(hgr0,level,0);
    generateHgrFile(hgr1,level,1);
}


//Divide-and-Conquer
/*e.g. input file:hgr.l.n
 *0.if only 0/1/2 nodes in hgr.l.n, write nodes to output_file
 *1.generate file hgr.l.n.part2 using shmetis
 *2.get separator nodes using hgr.l.n and hgr.l.n.part2
 *3.write separator nodes to output_file
 *4.generate child file: hgr.(l+1).0, hgr.(l+1).1
 *5.divide-and-conquer : getSeparatorAndSplit(l+1,0,output_file)
 *                       getSeparatorAndSplit(l+1,1,output_file)
 */
void GM::getSeparatorAndSplit(int level,int num_child,string output_file){
	if(level==0 && num_child==0){
		string command = "rm " + output_file;
		const char *cmd = command.c_str();
		system(cmd);
	}

	//1.generate file hgr.l.n.part2 using shmetis
	string folder_path = "./hgrs/";
	string hgr_file_name = "hgr." + to_string(level) + "." + to_string(num_child);
	string hgr_file_path = folder_path + hgr_file_name;
	string hgr_original_file_path = folder_path + hgr_file_name + ".original";
	if(level == 0) hgr_original_file_path = "";

	//if only 0/1/2 nodes in hgr.l.n, write nodes to output_file
	ifstream infile(hgr_file_path);
    int num_nodes;
    infile >> num_nodes; //first value
    infile >> num_nodes; //second value
    if(num_nodes < 3) {
    	Hgr hgr;
    	hgr.readHgrFiles(hgr_file_path,"",hgr_original_file_path);
    	ofstream outfile;
        outfile.open (output_file, ios::out | ios::app);
    	for(int i = 1 ; i < hgr.nodes.size(); i++){
    	    outfile << hgr.nodes[i]->original_id << " " << level << " " << num_child <<endl;
    	}
    	if(num_nodes==0)
    		outfile << "0" << " " << level << " " << num_child <<endl;
    	return;
    }

    //generate file hgr.l.n.part2
    string shmetis_path = folder_path + "shmetis";
    string command = shmetis_path + " " + hgr_file_path + " " + to_string(2) + " " + to_string(5) ;
    const char * cmd = command.c_str();
    system( cmd ) ;

    //2.get separator nodes using hgr.l.n and hgr.l.n.part2
    string hgr_part2_file_path = hgr_file_path + ".part.2";
    vector<int> separator;
    Hgr hgr;
    hgr.readHgrFiles(hgr_file_path,hgr_part2_file_path,hgr_original_file_path);
    generateSeparator(separator,hgr);
    cout<<"--------------------"<<endl;
    hgr.output();
    cout<<"--------------------"<<endl;
    //3.write separator nodes to output_file
    outputSeparator(separator,level,num_child,output_file);

    //4.generate child file: hgr.(l+1).0, hgr.(l+1).1 ,hgr.(l+1).*.original
    splitHgrFile(hgr,level+1);

    //5.divide-and-conquer
    getSeparatorAndSplit(level+1,0,output_file);
    getSeparatorAndSplit(level+1,1,output_file);
}

void GM::outputResult(string outputFile){

}

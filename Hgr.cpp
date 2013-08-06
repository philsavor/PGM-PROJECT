/*
 * Hgr.cpp
 *
 *  Created on: May 9, 2013
 *      Author: xiangyu
 */

#include "Hgr.h"
#include <fstream>

Hgr::Hgr() {
	// TODO Auto-generated constructor stub

}

Hgr::~Hgr() {
	// TODO Auto-generated destructor stub
}

void Hgr::readHgrFiles(string hgr_file_path,string hgr_part2_file_path,string hgr_original_file_path){
	//1.read from hgr_file_path
	const char* hgr_file = hgr_file_path.c_str();
	ifstream hgrfile(hgr_file);
    if(!hgrfile.good()){
		cerr<<"Error opening hgr file\nPath:" <<hgr_file_path<<endl ;
		exit(-1);
	}
	int num_edges;
	int num_nodes;
	hgrfile >> num_edges;
	hgrfile >> num_nodes;
	nodes = vector<Node*>(num_nodes+1);
	for (int i = 1; i <= num_nodes; i++) {
		nodes[i] = new Node();
		nodes[i]->original_id = i;
		nodes[i]->id=i;
	}
	edges = vector<Edge*>(num_edges);
	for (int i = 0; i < num_edges; i++) {
		edges[i] = new Edge();
		edges[i]->id=i;
		vector<Node*> nodes_in_edge(2);
		for(int i = 0 ; i < 2; i++){
			int value;
			hgrfile >> value;
			nodes_in_edge[i] = nodes[value];
		}
		edges[i]->nodes = nodes_in_edge;
	}
    hgrfile.close();

	//2.read from hgr_part2_file_path
    if(hgr_part2_file_path != "") {
    	const char* hgr_part2_file = hgr_part2_file_path.c_str();
        ifstream hgrfilepart2(hgr_part2_file);
    	for(int i = 1 ; i <= num_nodes; i++){
    	    int value;
    	    hgrfilepart2 >> value;
    	    nodes[i]->setSectorId(value);
    	}
    	hgrfilepart2.close();
    }

    //3.read from hgr_original_file_path
    if(hgr_original_file_path != "") {
        const char* hgr_original_file = hgr_original_file_path.c_str();
        ifstream hgrfileorg(hgr_original_file);
        for(int i = 1 ; i <= num_nodes; i++){
            int value;
            hgrfileorg >> value;
            hgrfileorg >> value;
            nodes[i]->original_id = value;
        }
        hgrfileorg.close();
    }

}

void Hgr::output(){
	for(int i = 1 ; i < nodes.size();i++){
         nodes[i]->output();
	}
	for(int i = 0 ; i < edges.size();i++){
         edges[i]->output();
	}
}


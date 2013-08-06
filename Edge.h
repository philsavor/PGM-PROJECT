/*
 * Edge.h
 *
 *  Created on: May 9, 2013
 *      Author: xiangyu
 */

#ifndef EDGE_H_
#define EDGE_H_

#include<iostream>
#include<vector>
#include"Util.h"
#include"Node.h"

using namespace std;

class Edge {
public:
	int id;
	vector<Node*> nodes;
	Edge():id(-1){}
	virtual ~Edge();
	void output();
};

#endif /* EDGE_H_ */

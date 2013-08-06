/*
 * Node.cpp
 *
 *  Created on: May 9, 2013
 *      Author: xiangyu
 */

#include "Node.h"


Node::~Node() {
	// TODO Auto-generated destructor stub
}

void Node::output(){
	cout<<"Node num:"<<id
		<<" separator:"<<isSeparator()
		<<" sector id:"<<getSectorId()<<endl;
}


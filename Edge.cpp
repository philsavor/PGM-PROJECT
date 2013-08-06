/*
 * Edge.cpp
 *
 *  Created on: May 9, 2013
 *      Author: xiangyu
 */

#include "Edge.h"


Edge::~Edge() {
	// TODO Auto-generated destructor stub
}

void Edge::output(){
    cout<<"Edge num:"<<id<<" : "<<nodes[0]->id<<" "<<nodes[1]->id
    		<<" separator:"<<nodes[0]->isSeparator()<<" "<<nodes[1]->isSeparator()
    		<<" sector id:"<<nodes[0]->getSectorId()<<" "<<nodes[1]->getSectorId()<<endl;
}


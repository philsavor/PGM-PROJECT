/*
 * Node.h
 *
 *  Created on: May 9, 2013
 *      Author: xiangyu
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
using namespace std;

class Node {
public:
	int id;
	int original_id;

	Node():
		original_id(-1),id(-1),if_separator(false),sector_id(-1){
	}
	virtual ~Node();
	inline bool isSeparator(){return if_separator;}
	inline void setSeparator(bool value){if_separator = value;}
    inline int getSectorId(){ return sector_id; }
    inline void setSectorId(int value){sector_id = value;}
    void output();

private:
	bool if_separator;
	int sector_id;
};

#endif /* NODE_H_ */

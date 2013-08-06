/*
 * Hgr.h
 *
 *  Created on: May 9, 2013
 *      Author: xiangyu
 */

#ifndef HGR_H_
#define HGR_H_

#include<vector>
#include"Node.h"
#include"Edge.h"

using namespace std;

class Hgr {
public:
	vector<Node*> nodes;
    vector<Edge*> edges;

	Hgr();
	virtual ~Hgr();
	void readHgrFiles(string hgr_file_path,string hgr_part2_file_path,string hgr_original_file_path);
	void output();
};

#endif /* HGR_H_ */

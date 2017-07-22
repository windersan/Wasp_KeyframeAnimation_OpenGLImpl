#pragma once

#include "Joint.h"
#include "matrix34.h"
#include <string>
#include "core.h"
#include "vector3.h"
#include <vector>

class Skeleton {
public:
	Skeleton();

	int indx = 0;

	std::vector<Joint*>jointsx;
	void populate(Joint* j) ;


	Tokenizer* WAND;
	Joint* ROOT;
	Matrix34 WROOT;
	Matrix34 identt;
	void Set();
	void Reset(const char* filename);
	bool Load(Tokenizer* WAND, const char* filename);
	void Update(Matrix34);
	void Draw();	
};
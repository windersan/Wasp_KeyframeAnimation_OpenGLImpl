#pragma once

#include <vector>
#include "matrix34.h"
#include "token.h"
#include "Triangle.h"
#include "skinweights.h"
#include "weightlist.h"
#include "Skeleton.h"



using namespace std;

class Skin {
public:
	Skin();

	bool Load(Tokenizer* WAND, const char* filename);

	void Update(Skeleton skeleton);

	void Draw();

	////////////////////////////////////////////////////////////////////
	vector<Vector3>positions;
	vector<Vector3>normals;
	vector<Weightlist>skinweights;
	vector<Triangle>triangles;
	vector<Matrix34>bindings;
	////////////////////////////////////////////////////////////////////
	vector<Vector3>u;
	Matrix34 M;
	Vector3 vprime;
	////////////////////////////////////////////////////////////////////			
};
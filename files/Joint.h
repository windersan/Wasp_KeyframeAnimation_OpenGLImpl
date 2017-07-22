#pragma once

#include "vector3.h"
#include "token.h"
#include "matrix34.h"
#include <vector>
#include <iostream>
#include <string>


class Joint {
public:

	Joint();

	std::vector<float> DOF;
//	std::vector<Channel>channels;

	//static std::vector<Joint*>* JOINTS;

	char name[30];
	
	std::string names;
	
	Vector3* OFFSET = new Vector3;
	Vector3 offset = *OFFSET;
	Vector3* BOXMIN = new Vector3;
	Vector3 boxmin = *BOXMIN;
	Vector3* BOXMAX = new Vector3;
	Vector3 boxmax = *BOXMAX;
	Vector3* POSE = new Vector3;
	Vector3 pose = *POSE;
	Vector3* ROTMIN = new Vector3;
	Vector3 rotmin = *ROTMIN;
	Vector3* ROTMAX = new Vector3;
	Vector3 rotmax = *ROTMAX;

	Matrix34* I = new Matrix34;
	Matrix34 T = *I;
	Matrix34* M = new Matrix34;
	Matrix34 W = *M;
	Matrix34* N = new Matrix34;
	Matrix34 L = *N;
	Matrix34* O = new Matrix34;
	Matrix34 W_P = *O;

	std::vector<Joint*>CHILDREN;
	std::vector<Joint>children;

	void Update(Matrix34 W_P);                     
	bool Load(Tokenizer* WAND);
	void AddChild(Joint);
	void Draw();

};






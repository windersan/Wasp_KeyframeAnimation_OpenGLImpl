#pragma once


#include <vector>
#include "keyframe.h"



using namespace std;

class Channel {
public:

	Channel();
	char extrap_in[20];
	char extrap_out[20];
	vector<Keyframe>keyframes;

	float f(float);

	vector<float>HermiteCurve;
	void Precompute();

	float p0;
	float p1;
	float v0;
	float v1;
	float t0;
	float t1;
	float t;
	float k = 0;

	
};


////extrap choices: constant, linear, cycle, cycle_offset, bounce
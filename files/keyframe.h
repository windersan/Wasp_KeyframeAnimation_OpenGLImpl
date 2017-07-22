#pragma once

class Keyframe {
public:
	Keyframe();

	float Time;
	float Value;
	char TangentIn[20];
	char TangentOut[20];
	
	float A, B, C, D; 



	float vin, vout;

	float p0;
	float p1;
	float v0;
	float v1;
	float t0;
	float t1;

};





#pragma once
#include "channel.h"
#include <vector>
#include "token.h"

using namespace std;

class Animation {
public:

	Animation();

	bool Load(Tokenizer* WAND, const char* filename);

	static int time;
	float t_i;
	float t_f;

	static vector<Channel>* CHANNELS;
	static vector<Channel> channels;


	void CalculateTangentData();



	
};



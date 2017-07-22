#include "animation.h"
#include "token.h"
#include <iostream>

Animation::Animation() {
	


}

vector<Channel> Animation::channels;
int Animation::time = 0;

bool Animation::Load(Tokenizer* WAND, const char* filename) {

	WAND->Open(filename);
	WAND->FindToken("range");
	t_i = WAND->GetFloat();
	t_f = WAND->GetFloat();
	WAND->FindToken("numchannels");
	
	std::cout << "lololl";

	while (1) {
		char temp[256];
		WAND->GetToken(temp);
		if (strcmp(temp, "channel") == 0) {
						
			Channel* CHAN = new Channel;
			
			WAND->FindToken("extrapolate");
			WAND->GetToken(CHAN->extrap_in);
			WAND->GetToken(CHAN->extrap_out);
			cout << channels.size();
			WAND->FindToken("keys");
		
			int v = WAND->GetFloat();
			cout << endl<<"size of keyframesvector: " << v<<endl;
			WAND->FindToken("{");
			for (int j = 0; j < v ; j++) {
				Keyframe* KEY = new Keyframe;
				
				cout << "size of chan->keyframes is: "<<CHAN->keyframes.size() << endl;
		
				KEY->Time = WAND->GetFloat();
				KEY->Value = WAND->GetFloat();
				WAND->GetToken(KEY->TangentIn);
				WAND->GetToken(KEY->TangentOut);
				CHAN->keyframes.push_back(*KEY);
				cout << endl << "CHAN->keyframes[j].Time: " << CHAN->keyframes[j].Time<<endl<<endl;
		
			}
			if (CHAN->keyframes.size() <10) {
				CHAN->Precompute(); cout <<endl<<"k = "<< CHAN->k<<endl; 
			}
			channels.push_back(*CHAN);
			WAND->FindToken("}");
			WAND->FindToken("}");			

		}

		else if (strcmp(temp, "}") == 0) return true;
		else WAND->SkipLine();

	}

	


}


void Animation::CalculateTangentData() {

	for (int ii = 0; ii < channels.size(); ii++) {
		channels[0].Precompute();

	}

}



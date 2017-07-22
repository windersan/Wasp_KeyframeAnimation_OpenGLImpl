#include "channel.h"
#include "core.h"
#include <iostream>

Channel::Channel(){}




void Channel::Precompute() {													//loads up hermite constants and tangents


	if (keyframes.size() == 1) {
		k = keyframes[0].Value;
	}

	else if (keyframes.size() == 2) {
		std::cout << "OOPS";
		k = (keyframes[1].Value - keyframes[0].Value) / (keyframes[1].Time - keyframes[0].Time);
	}


	else if (keyframes.size() > 2) {
		std::cout << "here our keyframes is larger than 2";
		
		for (int i = 0; i < keyframes.size(); i++) {
			cout << endl << "here i =:" << i << endl;
			if (strcmp(keyframes[i].TangentIn, "linear")==0) {
				if (i == 0) { keyframes[i].vin = 1; }
				if (i>0)keyframes[i].vin = (keyframes[i].Value - keyframes[i-1].Value) / (keyframes[i].Time - keyframes[i-1].Time);
			}
			 if (strcmp(keyframes[i].TangentOut, "linear") == 0) {
				 if (i == (keyframes.size() - 1))keyframes[i].vout = (keyframes[i].Value - keyframes[i - 1].Value) / (keyframes[i].Time - keyframes[i - 1].Time);
				 else keyframes[i].vout = (keyframes[i + 1].Value - keyframes[i].Value) / (keyframes[i + 1].Time - keyframes[i].Time);
			}

			 if (strcmp(keyframes[i].TangentIn, "smooth") == 0) {
				if(i == 0)keyframes[i].vin = (keyframes[i + 1].Value - keyframes[i].Value) / (keyframes[i + 1].Time - keyframes[i].Time);             //no i-1 term if i = 0
				else if(i==(keyframes.size()-1))  keyframes[i].vin = (keyframes[i].Value - keyframes[i - 1].Value) / (keyframes[i].Time - keyframes[i - 1].Time);  //no i+1 term for the last keyframe
				else  keyframes[i].vin = (keyframes[i + 1].Value - keyframes[i - 1].Value) / (keyframes[i + 1].Time - keyframes[i - 1].Time);
			}
			 if (strcmp(keyframes[i].TangentOut, "smooth") == 0) {
				 if (i == 0)keyframes[i].vout = (keyframes[i + 1].Value - keyframes[i].Value) / (keyframes[i + 1].Time - keyframes[i].Time);             //no i-1 term if i = 0
				 else if (i==(keyframes.size()-1)) keyframes[i].vout = (keyframes[i].Value - keyframes[i - 1].Value) / (keyframes[i].Time - keyframes[i - 1].Time);  //no i+1 term for the last keyframe
				 else keyframes[i].vout = (keyframes[i + 1].Value - keyframes[i - 1].Value) / (keyframes[i + 1].Time - keyframes[i - 1].Time);
			}
			 if (strcmp(keyframes[i].TangentIn, "flat") == 0) {
				keyframes[i].vin = 0;
			}
			 if (strcmp(keyframes[i].TangentOut, "flat") == 0) {
				keyframes[i].vout = 0;
			}
			 
		}
		for (int i = 0; i < (keyframes.size() - 1); i++) {										

			keyframes[i].A = 2 * keyframes[i].Value - 2 * keyframes[i + 1].Value + keyframes[i].vout * (keyframes[i + 1].Time - keyframes[i].Time) + keyframes[i + 1].vin * (keyframes[i + 1].Time - keyframes[i].Time);
			cout << "for i: "<< i<< endl << "A = " << keyframes[i].A;
			keyframes[i].B = -3 * keyframes[i].Value + 3 * keyframes[i + 1].Value - 2 * keyframes[i].vout * (keyframes[i + 1].Time - keyframes[i].Time) - keyframes[i + 1].vin * (keyframes[i + 1].Time - keyframes[i].Time);
			keyframes[i].C = keyframes[i].vout * (keyframes[i + 1].Time - keyframes[i].Time);
			keyframes[i].D = keyframes[i].Value;
		}
		
	}


}


float Channel::f(float t) {
		
	if (keyframes.size() == 1) {
		
		return k;
	}

	else if (keyframes.size() == 2) {
		return k * t;									
	}

	else if (keyframes.size() > 2) {

		for (int i = 0; i < keyframes.size(); i++) {			
			float timeconst = keyframes[i].Time;
		}


		
		for (int i = 0; i < (keyframes.size() - 1); i++) {

			if (t > keyframes[i].Time && t < keyframes[i + 1].Time) {
				
				float u = (t - keyframes[i].Time) / (keyframes[i + 1].Time - keyframes[i].Time);												
								
				float x = keyframes[i].D + u * (keyframes[i].C + u * (keyframes[i].B + u * keyframes[i].A));													
			
				float g = keyframes[i].A*u*u*u + keyframes[i].B*u*u + keyframes[i].C*u + keyframes[i].D;
			
					return x;
			}
		}

		if (t < keyframes[0].Time) {
			if (strcmp(extrap_in, "constant") == 0){
				return keyframes[0].Value;
			}

			else if (strcmp(extrap_in, "cycle") == 0){
				float tprime = t + (keyframes[keyframes.size() - 1].Time - keyframes[0].Time);
				return f(tprime);
			}
			
		}
		if (t > keyframes[(keyframes.size()-1)].Time) {
			if (strcmp(extrap_out, "constant") == 0) {
				return keyframes[(keyframes.size() - 1)].Value;
			}
			else if (strcmp(extrap_out, "cycle") == 0) {				
				float tprime = t - (keyframes[keyframes.size() - 1].Time - keyframes[0].Time);
				return f(tprime);
			}
	
		}
				
	}
		
}
#include "Joint.h"
#include "token.h"
#include <vector>

#include <map>
#include <utility>
#include <iostream>

std::vector<Matrix34>w;
std::vector<Vector3>min;
std::vector<Vector3>max;

Joint::Joint() {
	
	offset.Zero(); 
	boxmin.Zero();
	boxmax.Zero();
	pose.Zero();
	rotmin.Set(-10000,-10000,-10000);
	rotmax.Set(10000,10000,10000);

	L = Matrix34();
	W = Matrix34();
	W_P = Matrix34();
	T = Matrix34();

	std::vector<Joint*>CHILDREN;

	std::vector<Joint>children;
}

void Joint::Update(Matrix34 parent) {
	
	L.Identity();
	T.Identity();
	if (rotmin.x >= pose.x) { pose.x = rotmin.x; }
	if (rotmax.x <= pose.x) { pose.x = rotmax.x; }
		

	T.MakeRotateX(pose.x); 
		L.Dot(T, L);

		if (rotmin.y >= pose.y) { pose.y = rotmin.y; }
		if (rotmax.y <= pose.y) { pose.y = rotmax.y; }

	T.MakeRotateY(pose.y); 
	L.Dot(T,L); 

	if (rotmin.z >= pose.z) { pose.z = rotmin.z; }
	if (rotmax.z<= pose.z) { pose.z = rotmax.z; }

	T.MakeRotateZ(pose.z); 
	L.Dot(T,L); 
	
	T.MakeTranslate(offset);
	L.Dot(T, L);
	
	W.Dot(parent, L);			

		

for (int i = 0; i < children.size(); i++)
	{
		children[i].Update(W);
	}															
}


bool Joint::Load(Tokenizer* WAND) {
	
	
	WAND->FindToken("{");
	while (1) {
		char temp[256];
		WAND->GetToken(temp);
		if (strcmp(temp, "offset") == 0) {
			offset.x = WAND->GetFloat();
			offset.y = WAND->GetFloat();
			offset.z = WAND->GetFloat();
			
		}
		else if (strcmp(temp, "boxmin") == 0) {

			boxmin.x = WAND->GetFloat();
			boxmin.y = WAND->GetFloat();
			boxmin.z = WAND->GetFloat();
		}
		else if (strcmp(temp, "boxmax") == 0) {

			boxmax.x = WAND->GetFloat();
			boxmax.y = WAND->GetFloat();
			boxmax.z = WAND->GetFloat();
		}
		else if (strcmp(temp, "pose") == 0) {

			pose.x = WAND->GetFloat();
			pose.y = WAND->GetFloat();
			pose.z = WAND->GetFloat();		
			
		}
		else if (strcmp(temp, "rotxlimit") == 0) {
			rotmin.x = WAND->GetFloat();
			rotmax.x = WAND->GetFloat();
			
		}
		else if (strcmp(temp, "rotylimit") == 0) {
			rotmin.y = WAND->GetFloat();
			rotmax.y = WAND->GetFloat();
			
		}
		else if (strcmp(temp, "rotzlimit") == 0) {
			rotmin.z = WAND->GetFloat();
			rotmax.z = WAND->GetFloat();
			
		}

		
		else if (strcmp(temp, "balljoint") == 0) {
			Joint* jnt = new Joint;
		CHILDREN.push_back(jnt);
			
		char temp1[30]; 
			WAND->GetToken(temp1);
						
			for (int i = 0; i<30; i++)
			{
				printf("%c", temp1[i]);

				jnt->name[i] = temp1[i];
			}
				
			jnt->Load(WAND);
			AddChild(*jnt);
									
		}
		else if (strcmp(temp, "}") == 0) return true;
		else WAND->SkipLine(); 
	}
}


void Joint::AddChild(Joint child){
	
	children.push_back(child);
	
}


void Joint::Draw() {

		
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(W);
		drawWireBox(boxmin.x, boxmin.y, boxmin.z, boxmax.x, boxmax.y, boxmax.z);
	

	for (int i = 0; i < children.size(); i++)
	{
		children[i].Draw();
	}
}






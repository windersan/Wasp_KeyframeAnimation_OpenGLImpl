#include "Skeleton.h"
#include "matrix34.h"
#include "token.h"
#include <string>
#include "cube.h"
#include <iostream>
#include <cmath>

Skeleton::Skeleton() {

	
	Set();
}

void Skeleton::Set() {
	WAND = new Tokenizer;
	WROOT.Identity();
	identt.Identity();

	
}

void Skeleton::Reset(const char* filename) {
	WAND = new Tokenizer;
	WROOT.Identity();
	identt.Identity();
	Load(WAND, filename);
	Update(identt);
	Draw();
}

bool Skeleton::Load(Tokenizer* WAND, const char* filename) {
	Tokenizer token;
	WAND->Open(filename);
	WAND->FindToken("balljoint");
	ROOT = new Joint;

	char temp1[30];
	WAND->GetToken(temp1);
	for (int i = 0; i < 30; i++) {ROOT->name[i] = temp1[i];}

	ROOT->Load(WAND);

	populate(ROOT);

	WAND->Close();		
		
	return true;

}

void Skeleton::Update(Matrix34 parent) {
	ROOT->Update(parent);

}

void Skeleton::Draw() {
	
	for (int i = 0; i < jointsx.size(); i++) {
		jointsx[i]->Draw();
	}


}

void Skeleton::populate(Joint* j) {
	
	jointsx.push_back(j);

		for (int i = 0; i < j->children.size(); i++)
		{
			populate(&j->children[i]);
		}
		std::cout<<std::endl<<"size of jointsx" << jointsx.size()<<std::endl;

}
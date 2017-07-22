#include "Skin.h"
#include <vector>
#include "matrix34.h"
#include "Triangle.h"
#include "weightlist.h"
#include "skinweights.h"



using namespace std;

Skin::Skin() {

}

bool Skin::Load(Tokenizer* WAND, const char* filename) {

	WAND->Open(filename);

	while (1) {
		char temp[256];
		WAND->GetToken(temp);

		if (strcmp(temp, "positions") == 0) {

			positions.resize(WAND->GetFloat());

			WAND->FindToken("{");
			for (unsigned int i = 0; i < positions.size(); i++) {
				positions[i].x = WAND->GetFloat();
				positions[i].y = WAND->GetFloat();
				positions[i].z = WAND->GetFloat();
			}

			WAND->FindToken("}");
		}

		if (strcmp(temp, "normals") == 0) {

			normals.resize(WAND->GetFloat());
			WAND->FindToken("{");
			for (unsigned int i = 0; i < normals.size(); i++) {
				normals[i].x = WAND->GetFloat();
				normals[i].y = WAND->GetFloat();
				normals[i].z = WAND->GetFloat();
			}
			WAND->FindToken("}");
		}

		if (strcmp(temp, "skinweights") == 0) {

			skinweights.resize(WAND->GetFloat());
			WAND->FindToken("{");
			for (unsigned int i = 0; i < skinweights.size(); i++) {

				skinweights[i].weightlist.resize(WAND->GetFloat());

				for (unsigned int j = 0; j < skinweights[i].weightlist.size(); j++) {

					skinweights[i].weightlist[j].indx = WAND->GetFloat();
					skinweights[i].weightlist[j].weight = WAND->GetFloat();
					
				}

			}
			WAND->FindToken("}");
		}

		if (strcmp(temp, "triangles") == 0) {

			triangles.resize(WAND->GetFloat()); std::cout << "triangles = " << triangles.size();
			WAND->FindToken("{");
			for (unsigned int i = 0; i < triangles.size(); i++) {
				triangles[i].vrtx1 = WAND->GetFloat();
				triangles[i].vrtx2 = WAND->GetFloat();
				triangles[i].vrtx3 = WAND->GetFloat();
			}
			WAND->FindToken("}");
		}

		if (strcmp(temp, "bindings") == 0) {

			bindings.resize(WAND->GetFloat());

			for (unsigned int i = 0; i < bindings.size(); i++) {
				WAND->FindToken("matrix {");
				
				bindings[i].a.x = WAND->GetFloat();
				bindings[i].a.y = WAND->GetFloat();
				bindings[i].a.z = WAND->GetFloat();
				bindings[i].b.x = WAND->GetFloat();
				bindings[i].b.y = WAND->GetFloat();
				bindings[i].b.z = WAND->GetFloat();
				bindings[i].c.x = WAND->GetFloat();
				bindings[i].c.y = WAND->GetFloat();
				bindings[i].c.z = WAND->GetFloat();
				bindings[i].d.x = WAND->GetFloat();
				bindings[i].d.y = WAND->GetFloat();
				bindings[i].d.z = WAND->GetFloat();

				bindings[i].Inverse();
									
			}
		
			WAND->FindToken("}");

		}

		else if (strcmp(temp, "}") == 0) return true;
		else WAND->SkipLine();

	}	
}




void Skin::Update(Skeleton skeleton) {
	
	u.resize(positions.size());

	for (unsigned int i = 0; i < u.size(); i++) {
		u[i].x = 0;
		u[i].y = 0;
		u[i].z = 0;
		
		for (unsigned int j = 0; j < skinweights[i].weightlist.size(); j++) {

			Matrix34 UU = skeleton.jointsx[skinweights[i].weightlist[j].indx]->W;

			UU.a.x = UU.a.x * skinweights[i].weightlist[j].weight;
			UU.a.y = UU.a.y *skinweights[i].weightlist[j].weight;
			UU.a.z = UU.a.z *skinweights[i].weightlist[j].weight;
			UU.b.x = UU.b.x *skinweights[i].weightlist[j].weight;
			UU.b.y = UU.b.y *skinweights[i].weightlist[j].weight;
			UU.b.z = UU.b.z *skinweights[i].weightlist[j].weight;
			UU.c.x = UU.c.x *skinweights[i].weightlist[j].weight;
			UU.c.y = UU.c.y *skinweights[i].weightlist[j].weight;
			UU.c.z = UU.c.z *skinweights[i].weightlist[j].weight;
			UU.d.x = UU.d.x *skinweights[i].weightlist[j].weight;
			UU.d.y = UU.d.y *skinweights[i].weightlist[j].weight;
			UU.d.z = UU.d.z *skinweights[i].weightlist[j].weight;

			Matrix34 VV = bindings[skinweights[i].weightlist[j].indx];
					
			M.Dot(UU,VV);
					
			M.Transform(positions[i], vprime);

			u[i].x += vprime.x;
			u[i].y += vprime.y;
			u[i].z += vprime.z;
					
		}		
	}			
}




void Skin::Draw() {


	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.2, 0.3);    
	
	
	for (unsigned i = 0; i < triangles.size(); i++) {



		glNormal3f(normals[triangles[i].vrtx1].x, normals[triangles[i].vrtx1].y, normals[triangles[i].vrtx1].z);
		glVertex3f(u[triangles[i].vrtx1].x, u[triangles[i].vrtx1].y, u[triangles[i].vrtx1].z);

		glNormal3f(normals[triangles[i].vrtx2].x, normals[triangles[i].vrtx2].y, normals[triangles[i].vrtx2].z);
		glVertex3f(u[triangles[i].vrtx2].x, u[triangles[i].vrtx2].y, u[triangles[i].vrtx2].z);

		glNormal3f(normals[triangles[i].vrtx3].x, normals[triangles[i].vrtx3].y, normals[triangles[i].vrtx3].z);
		glVertex3f(u[triangles[i].vrtx3].x, u[triangles[i].vrtx3].y, u[triangles[i].vrtx3].z);
	}


	glEnd();

}







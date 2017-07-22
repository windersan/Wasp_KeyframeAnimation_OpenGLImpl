////////////////////////////////////////
// tester.cpp
////////////////////////////////////////

#include "tester.h"
#include "token.h"
#include <iostream>
#include "Joint.h"
#include "Skeleton.h"
#include <vector>
#include "cube.h"
#include "matrix34.h"
#include <cmath>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include "BMPimage.h"
#include <chrono>
#include "animation.h"
#include "windows.h"
#include "grid.h"

#define WINDOWTITLE	"Spinning Cube"
using namespace std;
using namespace std::chrono;
////////////////////////////////////////////////////////////////////////////////

static Tester *TESTER;

Matrix34* M1 = new Matrix34;
Matrix34 W1 = *M1;

Vector3* OFFSET1 = new Vector3;
Vector3  offset1 = *OFFSET1;
Vector3* BOXMIN1 = new Vector3;
Vector3 boxmin1 = *BOXMIN1;
Vector3* BOXMAX1 = new Vector3;
Vector3 boxmax1 = *BOXMAX1;
Vector3* POSE1 = new Vector3;
Vector3 pose1 = *POSE1;



int main(int argc, char **argv) 
{

	

glutInit(&argc, argv);
	TESTER = new Tester(argc, argv);
	
	TESTER->tick = GetTickCount();





glutMainLoop();
	
	


	return 0;
}

////////////////////////////////////////////////////////////////////////////////

// These are really HACKS to make glut call member functions instead of static functions

															
static void display()									{TESTER->Draw();}
static void idle()										{TESTER->Update();}
static void resize(int x,int y)							{TESTER->Resize(x,y);}
static void keyboard(unsigned char key,int x,int y)		{TESTER->Keyboard(key,x,y);}
static void mousebutton(int btn,int state,int x,int y)	{TESTER->MouseButton(btn,state,x,y);}
static void mousemotion(int x, int y)					{TESTER->MouseMotion(x,y);}

////////////////////////////////////////////////////////////////////////////////


Tester::Tester(int argc, char **argv) {


	cout << "FILENAME:";

	const char* filename;
	string sfilename;
	cin >> sfilename;
	filename = sfilename.c_str();
	MySkeleton.Reset(filename);
	Tokenizer* WANDA = new Tokenizer;
	MyAnim.Load(WANDA, "wasp_walk.anim");
	WANDA->Close();

	for (int h = 0; h < MyAnim.channels.size();h++)


	///////////////////////////////////////////////////////////////////////   
	

		



	cout << "skin";
	const char* kfilename;
	string skfilename;
	cin >> skfilename;
	kfilename = skfilename.c_str();



	Tokenizer* WANDX = new Tokenizer;
	MySkin.Load(WANDX, kfilename);	
	WANDX->Close();

	


	WinX=640;
	WinY=480;
	LeftDown=MiddleDown=RightDown=false;
	MouseX=MouseY=0;

	// Create the window
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( WinX, WinY );
	glutInitWindowPosition( 0, 0 );
	WindowHandle = glutCreateWindow( WINDOWTITLE );


	glutSetWindowTitle( WINDOWTITLE );
	glutSetWindow( WindowHandle );

	

	/////////////////////////////////////// lighting parameters
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.8,3,-1,0.0 };
	GLfloat white_light[] = { 0.3,0.7,1.0,1.0 };
	GLfloat lmodel_ambient[] = { 0.1,0.4,0.1,1.0 };

	//////////////

	GLfloat light1_ambient[] = { 0.2,0.2,0.2,1 };  // 0.2,0.2,0.5,1 };
	GLfloat light1_diffuse[] = { 1,1.0,1,1.0 };   //0.5,1.0,0.9,1.0 
	GLfloat light1_specular[] = { 1,1,1,1 };     //{ 0,1,0,1 };
	GLfloat light1_position[] = { -2,-2,1,1 };  // -2,-2,1,1 };
	GLfloat spot_direction[] = { -1,-1,0 };

	/////////////
	GLfloat light_position2[] = { 0,-5,0,0.0 };
	GLfloat white_light2[] = { 0.0,1,0.0,1.0 };
	// Background color
	glClearColor( 0.0, 0., 0.0, 0.0 );                                      //originally at 1

	/////////////////////// lighting

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


		glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, white_light2);
		
////		
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT1);

	// Callbacks


	glutDisplayFunc( display );
	glutIdleFunc( idle );


	glutKeyboardFunc( keyboard );
	glutMouseFunc( mousebutton );
	glutMotionFunc( mousemotion );
	glutPassiveMotionFunc( mousemotion );
	glutReshapeFunc( resize );



	// Initialize components

	Cam.SetAspect(float(WinX)/float(WinY));

	
}

////////////////////////////////////////////////////////////////////////////////

Tester::~Tester() {
	glFinish();
	glutDestroyWindow(WindowHandle);
}

////////////////////////////////////////////////////////////////////////////////
float aug = 0;
void Tester::Update() {
	
	// Update the components in the world


		
	int test = tick - GetTickCount();
	if (test <= 0) {
		tick += 40; aug += 0.04;
		float ttt = aug;
		tt = aug;
			
		MySkeleton.jointsx[0]->offset.x = MyAnim.channels[0].f(ttt);
			MySkeleton.jointsx[0]->offset.y = MyAnim.channels[1].f(ttt);
			MySkeleton.jointsx[0]->offset.z = MyAnim.channels[2].f(ttt);
		for (int jl = 0; jl < MySkeleton.jointsx.size(); jl++) {  
	
			MySkeleton.jointsx[jl]->pose.x = MyAnim.channels[(3 * jl) + 3].f(ttt);
				MySkeleton.jointsx[jl]->pose.y =  MyAnim.channels[(3 * jl) + 4].f(ttt );
				MySkeleton.jointsx[jl]->pose.z = MyAnim.channels[(3 * jl) + 5].f(ttt);
		}


}
		Cam.Update();
		Cube.Update();

		MySkeleton.Update(W1);
		MySkin.Update(MySkeleton);



		// Tell glut to re-display the scene
		glutSetWindow(WindowHandle);
		glutPostRedisplay();
	
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Reset() {
	Cam.Reset();
	Cam.SetAspect(float(WinX)/float(WinY));

	Cube.Reset();

	

}

////////////////////////////////////////////////////////////////////////////////

void Tester::Draw() {

	// Begin drawing scene
	glViewport(0, 0, WinX, WinY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	showinfo();

	// Draw components
	Cam.Draw();		// Sets up projection & viewing matrices
	Cube.Draw();
	//MySkeleton.Draw();

	

	MySkin.Draw();

	drawGrid(10.0f, 1.0f, MySkeleton, MyAnim, MySkeleton.indx);
	
	// Finish drawing scene
	glFinish();
	glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Quit() {
	glFinish();
	glutDestroyWindow(WindowHandle);
	exit(0);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Resize(int x,int y) {
	WinX = x;
	WinY = y;
	Cam.SetAspect(float(WinX)/float(WinY));
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Keyboard(int key,int x,int y) {
	
	switch (key) {
		
		case 0x1b:		// Escape
			Quit();
			break;
		case 'q':
			Reset();
			break;


		case 'a':
			--MySkeleton.indx;
			for (int i = 0; i < 30; i++)
			{
				current[i] = MySkeleton.jointsx[MySkeleton.indx]->name[i];
					
					printf("%c", MySkeleton.jointsx[MySkeleton.indx]->name[i]);
			}
			break;
		
		case 's':
			++MySkeleton.indx;
			for (int i = 0; i < 30; i++)
			{
				current[i] = MySkeleton.jointsx[MySkeleton.indx]->name[i];
				printf("%c", MySkeleton.jointsx[MySkeleton.indx]->name[i]);
			}
			break;

		case 'e':

				MySkeleton.jointsx[MySkeleton.indx]->pose.x -= 0.1;
				cout << "pose.x changed to: " << MySkeleton.jointsx[MySkeleton.indx]->pose.x << endl;
				break;

		case 'r':
			
			MySkeleton.jointsx[MySkeleton.indx]->pose.x += 0.1;
			cout << "pose.x changed to: " << MySkeleton.jointsx[MySkeleton.indx]->pose.x << endl;
			break;

		case 'd':

				MySkeleton.jointsx[MySkeleton.indx]->pose.y -= 0.1;
				cout << "pose.y changed to: " << MySkeleton.jointsx[MySkeleton.indx]->pose.y << endl;
				break;

		case 'f':

				MySkeleton.jointsx[MySkeleton.indx]->pose.y += 0.1;
				cout << "pose.y changed to: " << MySkeleton.jointsx[MySkeleton.indx]->pose.y << endl;
				break;

			case 'c':

				MySkeleton.jointsx[MySkeleton.indx]->pose.z -= 0.1;
				cout << "pose.z changed to: " << MySkeleton.jointsx[MySkeleton.indx]->pose.z << endl;

				

				break;

		case 'v':

				MySkeleton.jointsx[MySkeleton.indx]->pose.z += 0.1;
				cout << "pose.z changed to: " << MySkeleton.jointsx[MySkeleton.indx]->pose.z << endl;
				break;

			



	}
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseButton(int btn,int state,int x,int y) {
	if(btn==GLUT_LEFT_BUTTON) {
		LeftDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_MIDDLE_BUTTON) {
		MiddleDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_RIGHT_BUTTON) {
		RightDown = (state==GLUT_DOWN);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseMotion(int nx,int ny) {
	int dx = nx - MouseX;
	int dy = -(ny - MouseY);

	MouseX = nx;
	MouseY = ny;

	// Move camera
	// NOTE: this should really be part of Camera::Update()
	if(LeftDown) {
		const float rate=1.0f;
		Cam.SetAzimuth(Cam.GetAzimuth()+dx*rate);
		Cam.SetIncline(Cam.GetIncline()-dy*rate);
	}
	if(RightDown) {
		const float rate=0.01f;
		Cam.SetDistance(Cam.GetDistance()*(1.0f-dx*rate));
	}
}

////////////////////////////////////////////////////////////////////////////////





void Tester::showinfo()
{
	// backup current model-view matrix
	glPushMatrix();                     // save current modelview matrix
	glLoadIdentity();                   // reset modelview matrix

										// set to 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);        // switch to projection matrix
	glPushMatrix();                     // save current projection matrix
	glLoadIdentity();                   // reset projection matrix
	gluOrtho2D(0, WinX, 0, WinY); // set to orthogonal projection
	


	float color[4] = { 1, 1, 1, 1 };

	

	drawString(current, 0, WinY - 13, color, GLUT_BITMAP_8_BY_13);
	



	// restore projection matrix
	glPopMatrix();                   // restore to previous projection matrix

									 // restore modelview matrix
	glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
	glPopMatrix();                   // restore to previous modelview matrix
}



void Tester::drawString(const char *str, int x, int y, float color[4], void *font)
{
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
	glDisable(GL_TEXTURE_2D);

	glColor4fv(color);          // set text color
	glRasterPos2i(x, y);        // place text position

								// loop all characters in the string
	while (*str)
	{
		glutBitmapCharacter(font, *str);
		++str;
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopAttrib();
}
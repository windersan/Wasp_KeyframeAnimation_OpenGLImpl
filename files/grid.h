#pragma once
#include "core.h"
#include "animation.h"


void drawGrid(float size, float step, Skeleton skel, Animation anim, int jj)
{
	// disable lighting
	glDisable(GL_LIGHTING);

	// 20x20 grid


	glBegin(GL_POINT);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 3, 3);
	glEnd;


	glBegin(GL_LINES);

	glColor3f(0.5f, 0.5f, 0.5f);
	for (float i = step; i <= size; i += step)
	{
		glVertex3f(-size, 0, i);   // lines parallel to X-axis
		glVertex3f(size, 0, i);
		glVertex3f(-size, 0, -i);   // lines parallel to X-axis
		glVertex3f(size, 0, -i);

		glVertex3f(i, 0, -size);   // lines parallel to Z-axis
		glVertex3f(i, 0, size);
		glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
		glVertex3f(-i, 0, size);
	}

	glColor3f(0, 0, 1);

	for (float i = 0; i < 4; i += 0.05)
	{
		glVertex3f(i-7, anim.channels[(3*jj)+3].f(i)+2, 0);
		glVertex3f(i+0.05-7, anim.channels[(3 * jj) + 3].f(i+0.05)+2, 0);
	}

	for (float i = 0; i < 4; i += 0.05)
	{
		glVertex3f(i-2, anim.channels[(3 * jj) + 4].f(i) + 2, 0);
		glVertex3f(i-2 + 0.05, anim.channels[(3 * jj) + 4].f(i + 0.05) + 2, 0);
	}

	for (float i = 0; i < 4; i += 0.05)
	{
		glVertex3f(i+3, anim.channels[(3 * jj) + 5].f(i) + 2, 0);
		glVertex3f(i + 0.05+3, anim.channels[(3 * jj) + 5].f(i + 0.05) + 2, 0);
	}

	glColor3f(0, 1,0 );
	glVertex3f(-8, 2, 0);
	glVertex3f(-7, 2, 0);

	for (float i = 0; i < anim.channels[(3 * jj) + 3].keyframes.size(); i++) {
		glVertex3f(anim.channels[(3 * jj) + 3].keyframes[i].Time - 7, -1, 0);
		glVertex3f(anim.channels[(3 * jj) + 3].keyframes[i].Time - 7, 5, 0);
	}
	for (float i = 0; i < anim.channels[(3 * jj) + 4].keyframes.size(); i++) {
		glVertex3f(anim.channels[(3 * jj) + 4].keyframes[i].Time - 2, -1, 0);
		glVertex3f(anim.channels[(3 * jj) + 4].keyframes[i].Time - 2, 5, 0);
	}
	for (float i = 0; i < anim.channels[(3 * jj) + 5].keyframes.size(); i++) {
		glVertex3f(anim.channels[(3 * jj) + 5].keyframes[i].Time + 3, -1, 0);
		glVertex3f(anim.channels[(3 * jj) + 5].keyframes[i].Time + 3, 5, 0);
	}


	glColor3f(1, 0, 0);
	for (float i = 0; i < anim.channels[(3 * jj) + 3].keyframes.size(); i++) {
		glVertex3f(anim.channels[(3 * jj) + 3].keyframes[i].Time - 7, anim.channels[(3 * jj) + 3].keyframes[i].Value + 2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 3].keyframes[i].Time - 6.9, anim.channels[(3 * jj) + 3].f(anim.channels[(3 * jj) + 3].keyframes[i].Time+0.1)+2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 3].keyframes[i].Time - 7, anim.channels[(3 * jj) + 3].keyframes[i].Value + 2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 3].keyframes[i].Time - 7.1, anim.channels[(3 * jj) + 3].f(anim.channels[(3 * jj) + 3].keyframes[i].Time - 0.1) + 2, 0.01);
	}
	for (float i = 0; i < anim.channels[(3 * jj) + 4].keyframes.size(); i++) {
		glVertex3f(anim.channels[(3 * jj) + 4].keyframes[i].Time - 2, anim.channels[(3 * jj) + 4].keyframes[i].Value + 2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 4].keyframes[i].Time - 1.9, anim.channels[(3 * jj) + 4].f(anim.channels[(3 * jj) + 4].keyframes[i].Time + 0.1) + 2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 4].keyframes[i].Time - 2, anim.channels[(3 * jj) + 4].keyframes[i].Value + 2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 4].keyframes[i].Time - 2.1, anim.channels[(3 * jj) + 4].f(anim.channels[(3 * jj) + 4].keyframes[i].Time - 0.1) + 2, 0.01);
	}
	for (float i = 0; i < anim.channels[(3 * jj) + 5].keyframes.size(); i++) {
		glVertex3f(anim.channels[(3 * jj) + 5].keyframes[i].Time + 3, anim.channels[(3 * jj) + 5].keyframes[i].Value + 2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 5].keyframes[i].Time + 3.1, anim.channels[(3 * jj) + 5].f(anim.channels[(3 * jj) + 5].keyframes[i].Time + 0.1) + 2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 5].keyframes[i].Time + 3, anim.channels[(3 * jj) + 5].keyframes[i].Value + 2, 0.01);
		glVertex3f(anim.channels[(3 * jj) + 5].keyframes[i].Time + 2.9, anim.channels[(3 * jj) + 5].f(anim.channels[(3 * jj) + 5].keyframes[i].Time - 0.1) + 2, 0.01);
	}





	// x-axis
	glColor3f(1, 0, 0);
	glVertex3f(-size, 0, 0);
	glVertex3f(size, 0, 0);

	// z-axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -size);
	glVertex3f(0, 0, size);

	glEnd();





	// enable lighting back
	glEnable(GL_LIGHTING);
}


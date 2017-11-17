#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glut.h>
#else
#include <GL/glut.h>
#endif
#include "AnimRig.h"
#ifndef M_PI
#define M_PI 3.14159265
#endif

using namespace std;

// -------- ROTATION VARS --------------
float xpos = 0, ypos = 0, zpos = 0, xdir = 0, ydir = 0, zdir = -1, angle = 0, mugState = 0, mugHeight = 0;

// -------- KEYPRESS VARS --------------
float downmove = 0.0, downangle = 0.0;

// -------- MOODY LIGHTING -------------
GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat specular[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat position[] = { 0, 0, 0 };
/*
Global Rig variables
*/
CultistRig_0 *cultist_0_rig, //Gianni Cultist
*cultist_1_rig;	//Phillip cultist

Model *ritual_altar, *tree, *leaves, *coffee_cup;

// -------- DRAW FIGURES  ------------------
void renderScene() {
	/* Draw the test skeleton
	skull.drawNonTextured(colorArray);
	mainRig.drawRig();
	*/

	glPushMatrix();
	glTranslatef(0, -2, 0);	//Moves everything onto eye-level
	glPushMatrix();	//head-cultist, a cultist1 model
	glTranslatef(0, 0, -36.6);
	(*cultist_0_rig).drawRig();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5.87319, 0, -31.86742);
	glRotatef(-72, 0, 1, 0);
	(*cultist_1_rig).drawRig();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.87319, 0, -31.86742);
	glRotatef(72, 0, 1, 0);
	(*cultist_1_rig).drawRig();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.94876, 0, -24.74819);
	glRotatef(72 * 2, 0, 1, 0);
	(*cultist_1_rig).drawRig();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.74876, 0, -24.74819);
	glRotatef(-72 * 2, 0, 1, 0);
	(*cultist_1_rig).drawRig();
	glPopMatrix();
       
	glPushMatrix();
	glTranslatef(-2.29, 0, -41.855);
	(*tree).drawTextured();
	(*leaves).drawTextured();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(12.27256, 0, -24.2);
	(*tree).drawTextured();
	(*leaves).drawTextured();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-13.05, 0, -10.5);
	(*tree).drawTextured();
	(*leaves).drawTextured();
	glPopMatrix();
	
	
	if (mugHeight > 1) mugState = 1;
	else if (mugHeight < -1) mugState = 0;
	if (mugState == 0) {
		mugHeight += 0.01;
	}
	else if (mugState == 1) {
		mugHeight -= 0.01;
	}
	glPushMatrix();
	glTranslatef(0, 2.52870 + mugHeight, -30);
	(*coffee_cup).drawTextured();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.35, -30);
	(*ritual_altar).drawTextured();
	glPopMatrix();
	glPopMatrix();
}

void initializeModels() {
	Model cultist_0_bottom("cultist_0_bottom.obj", 0, 0, 0, { "cultist_0_robe_top" }, "cultist_0.bmp");
	Model cultist_0_top("cultist_0_robe_top.obj", 0, 1.49405, 0, {}, "cultist_0.bmp");
	Model cultist_0_hands("cultist_0_hands.obj", 0, 1.13319, 0, {}, "cultist_0.bmp");
	vector<Model> cultistVector = {
		cultist_0_bottom, cultist_0_top, cultist_0_hands
	};
	CultistRig_0 *cult_0Rig = new CultistRig_0(cultistVector);
	cultist_0_rig = cult_0Rig;

	Model cultist_1_bottom("cultist_0_bottom.obj", 0, 0, 0, { "cultist_0_robe_top" }, "cultist_1.bmp");
	Model cultist_1_top("cultist_0_robe_top.obj", 0, 1.49405, 0, {}, "cultist_1.bmp");
	Model cultist_1_hands("cultist_0_hands.obj", 0, 1.13319, 0, {}, "cultist_1.bmp");
	vector<Model> cultistVector1 = {
		cultist_1_bottom, cultist_1_top, cultist_1_hands
	};
	CultistRig_0 *cult_1Rig = new CultistRig_0(cultistVector1);
	cultist_1_rig = cult_1Rig;

	Model *altar = new Model("ritual_altar.obj", 0, 0, 0, {}, "ritual_altar.bmp");
	ritual_altar = altar;
	Model *tree1 = new Model("tree.obj", 0, 0, 0, {}, "bark.bmp");
	tree = tree1;
	Model *leaf1 = new Model("leaves.obj", 0, 0, 0, {}, "leafing.bmp");
	leaves = leaf1;
	Model *mug = new Model("coffee_cup.obj", 0, 0, 0, {}, "coffee_tex.bmp");
	coffee_cup = mug;
}


// ------- OTHER CODE  ------------------
void animate() {
	(*cultist_0_rig).doAnimate();
	(*cultist_1_rig).doAnimate();
	
	glutPostRedisplay();
}

void init() {
	initializeModels();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ambient);
	glShadeModel(GL_SMOOTH);
}

void camera() {
	gluLookAt(xpos, ypos, zpos,
		xpos + xdir, ypos + ydir, zpos + zdir,
		0, 1, 0);
}

void setpos(float downmove) {
    xpos += downmove * xdir;
    cout << "xpos" << xpos << endl;
    if (xpos > 5)
	xpos = 4.9;
    if (xpos < -5)
	xpos = -4.9;
    ypos += downmove * ydir;
    if (ypos > 5)
	ypos = 4.9;
    if (ypos < -5)
	ypos = -4.9;
    zpos += downmove * zdir;
    cout << "zpos: " << zpos << endl;
    if (zpos > 40)
	zpos = 39.9;
    if (zpos < -24.3) {
	zpos = -24.2;
    }
}


void setangle(float downangle) {
	angle += downangle;
	xdir = sin(angle);
	zdir = -cos(angle);
}

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (downmove)
		setpos(downmove);
	if (downangle)
		setangle(downangle);
	camera();
	animate();
	renderScene();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
	exit(0);
	break;
    case 'r':
	xpos = ypos = zpos = 0;
        xdir = ydir = 0;
	zdir = -1;
	angle = 0;
	break;
    }
}

void keyboard_down(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		downangle = -0.02f;
		break;
	case GLUT_KEY_RIGHT:
		downangle = 0.02f;
		break;
	case GLUT_KEY_UP:
		downmove = 0.1f;
		break;
	case GLUT_KEY_DOWN:
		downmove = -0.1f;
		break;
	}
}

void keyboard_up(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:

	case GLUT_KEY_RIGHT:
		downangle = 0.0f;
		break;
	case GLUT_KEY_UP:

	case GLUT_KEY_DOWN:
		downmove = 0.0f;
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Test");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_down);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(keyboard_up);

	glutMainLoop();
	return 0;
}

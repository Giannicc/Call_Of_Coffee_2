/**
	Created by:
	Gianni Ciccarelli and Phillip Wells
	
	CS300, Project 3
	The Call of Coffee 2:
		the Coffee Calls Back...
**/
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#ifndef M_PI
#define M_PI 3.14159265
#endif
#define TAU (2 * M_PI)
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include "AnimRig.h"
using namespace std;
int colorArray[] = {
	255, 255, 255
};
Model arm_left_lower("arm_left_lower.obj", 0.82596, 4.21011, -0.02102, { "hand_left" });
Model arm_left_upper("arm_left_upper.obj", 0.67702, 5.62719, -0.05725, { "arm_left_lower" });
Model arm_right_lower("arm_right_lower.obj", -0.82596, 4.21011, -0.02102, { "hand_right" });
Model arm_right_upper("arm_right_upper.obj", -0.67702, 5.62719, -0.05725, { "arm_right_lower" });
Model skull("final_skull.obj", 0, 0, 0, {});
Model foot_left("foot_left.obj", 0.27710, 0.30598, 0.06849, {});
Model foot_right("foot_right.obj", -0.27710, 0.30598, 0.06849, {});
Model hand_left("hand_left.obj", 0.84435, 3.34702, -0.44979, {});
Model hand_right("hand_right.obj", -0.84435, 3.34702, -0.44979, {});
Model leg_left_lower("leg_left_lower.obj", 0.33641, 1.78488, -0.03953, { "foot_left" });
Model leg_left_upper("leg_left_upper.obj", 0.39565, 3.64407, -0.11636, { "leg_left_lower" });
Model leg_right_lower("leg_right_lower.obj", -0.33641, 1.78488, -0.03953, { "foot_right" });
Model leg_right_upper("leg_right_upper.obj", -0.39565, 3.64407, -0.11636, { "leg_right_lower" });
Model skeleton_body("skeleton_body.obj", 0, 0, 0, {
	"arm_left_upper",
	"arm_right_upper",
	"leg_left_upper",
	"leg_right_upper"});
vector<Model> skelebones = {
	skeleton_body,
	arm_left_lower,
	arm_left_upper,
	arm_right_lower,
	arm_right_upper,
	foot_left,
	foot_right,
	hand_left,
	hand_right,
	leg_left_lower,
	leg_left_upper,
	leg_right_lower,
	leg_right_upper
};

Rig mainRig(skelebones);

Model cultist_0_bottom("cultist_0_bottom.obj", 0, 0, 0, { "cultist_0", "cultist_0_hands" });
Model cultist_0_top("cultist_0.obj", 0, 1.49405, 0, {});
Model cultist_0_hands("cultist_0_hands.obj", 0, 1.13319, 0, {});
vector<Model> cultistVector = {
	cultist_0_bottom, cultist_0_top, cultist_0_hands
};
CultistRig_0 cult_0Rig(cultistVector);

//Global vars to store the angle of rotation of the model
static GLfloat angle = 0;
static GLfloat angle2 = 0;

//Motion variables for the mouse rotation capability
static int moving = 0, startx = 0, starty = 0;

void animate() {
	cult_0Rig.doAnimate();
	glutPostRedisplay();
}

void renderScene() {
	/* Draw the test skeleton
	skull.drawNonTextured(colorArray);
	mainRig.drawRig();
	*/
	glPushMatrix();
	glTranslatef(0, 2.0, 0);
	cult_0Rig.drawRig();
	glPopMatrix();
}

//Init function for more openGL stuff
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-4.0,
		4.0,
		0.0,
		8.0,
		-8.0,
		8.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Setup initial OpenGL rendering state. */
	glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	renderScene();
	glPopMatrix();
	glutSwapBuffers();
}

//OpenGL clear function
void clear()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-4.0,
		4.0,
		0.0,
		8.0,
		-8.0,
		8.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Mouse control function
static void mouse(int button, int state, int x, int y)
{
	/* Rotate the scene with the left mouse button. */
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP) {
			moving = 0;
		}
	}
}

//OpenGL keyboard input
//	'q':  exit
//	'r':  begin random rotation of skeleton limbs
//	's':  stop random rotation of skeleton limbs
void keyboard(unsigned char key, int x, int y) {
#pragma unused(x, y)
	switch (key) {
	case 'q':
		exit(0);
		break;
	case 'r':
		glutIdleFunc(animate);
		break;
	case 's':
		glutIdleFunc(NULL);
		break;
	default:
		break;
	}
	display();
}

static void motion(int x, int y)
{
	if (moving) {
		angle = (angle + (x - startx));
		angle2 = (angle2 + (y - starty));
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}

//OpenGL reshape function
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(
			-4.0,
			4.0,
			0.0 * (GLfloat)h / (GLfloat)w,
			8.0 * (GLfloat)h / (GLfloat)w,
			-8.0,
			8.0);
	else
		glOrtho(
			-4.0 * (GLfloat)w / (GLfloat)h,
			4.0 * (GLfloat)w / (GLfloat)h,
			0.0,
			8.0,
			-8.0,
			8.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("The Call of Coffee 2");

	/* Register assorted GLUT callback routines. */
	init();
	glutIdleFunc(NULL);
	glutReshapeFunc(reshape);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}
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
#include "ReadObj.h"
using namespace std;
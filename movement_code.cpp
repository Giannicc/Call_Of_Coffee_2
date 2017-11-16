#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265
#endif

// -------- ROTATION VARS --------------
float xpos = 0, ypos = 0, zpos = 0, xdir = 0, ydir = 0, zdir = -1, angle = 0;

// -------- DELETE ME ------------------
void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void renderScene(void) {
    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 SnowMen
    for(int i = -3; i < 3; i++)
	for(int j=-3; j < 3; j++) {
	    glPushMatrix();
	    glTranslatef(i*10.0, -1, j * 10.0);
	    drawSnowMan();
	    glPopMatrix();
	}
}

// ------- DELETE ME ------------------

void init () {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
}

void camera () {
    gluLookAt(xpos, ypos, zpos,
	      xpos + xdir, ypos + ydir, zpos + zdir,
	      0, 1, 0);
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();  
    camera();
    renderScene();
    glutSwapBuffers();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
    float rot_amount = 0.3f;
    switch (key) {
    case 'q':
	exit(0);
	break;
    case 'a':
	angle -= 0.01f;
	xdir = sin(angle);
	zdir = -cos(angle);
	break;
    case 'd':
	angle += 0.01f;
	xdir = sin(angle);
	zdir = -cos(angle);
	break;
    case 'w':
	xpos += xdir * rot_amount;
	ypos += ydir * rot_amount;
	zpos += zdir * rot_amount;
	break;
    case 's':
	xpos -= xdir * rot_amount;
	ypos -= ydir * rot_amount;
	zpos -= zdir * rot_amount;
	break;
    }
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); 
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100); 
    glutCreateWindow ("Test");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape); 
    glutKeyboardFunc (keyboard);
    glutMainLoop ();
    return 0;
} 

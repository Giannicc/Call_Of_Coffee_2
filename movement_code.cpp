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

// -------- KEYPRESS VARS --------------
float downmove = 0.0, downangle = 0.0;

// -------- MOODY LIGHTING -------------
GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat diffuse[] = {0.3, 0.3, 0.3, 1.0};
GLfloat specular[] = {0.3, 0.3, 0.3, 1.0};
GLfloat position[] = {0, 0, 1};

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

void camera () {
    gluLookAt(xpos, ypos, zpos,
	      xpos + xdir, ypos + ydir, zpos + zdir,
	      0, 1, 0);
}

void setpos(float downmove) {
    xpos += downmove * xdir;
    ypos += downmove * ydir;
    zpos += downmove * zdir;
}

void setangle(float downangle) {
    angle += downangle;
    xdir = sin(angle);
    zdir = -cos(angle);
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (downmove)
	setpos(downmove);
    if (downangle)
	setangle(downangle);
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
	exit(0);
	break;
    }
}

void keyboard_down (int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
	downangle = -0.02f;
	break;
    case GLUT_KEY_RIGHT:
	downangle = 0.02f;
	break;
    case GLUT_KEY_UP:
	downmove = 0.5f;
	break;
    case GLUT_KEY_DOWN:
	downmove = -0.5f;
	break;
    }
}

void keyboard_up (int key, int x, int y) {
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
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard_down);
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(keyboard_up);
    
    glutMainLoop ();
    return 0;
} 

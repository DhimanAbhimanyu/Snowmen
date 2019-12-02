#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <cstring>

#include "vertex.hpp"

static float theta = 0.0, modTheta = 0.0, aspectRatio;
static float x = 0.0f, y = 1.75f, z = 5.0f;
static float lx = 0.0f, ly = 0.0f, lz = -1.0f;
static int modPos = 0, height, width;
static void *font;
static GLint snowmenDisplayList;

static int frame, tm, tmBase = 0;
static char s[30];

static void initWindow();

void changeSize(int newWidth, int newHeight)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(newHeight == 0)
		newHeight = 1;

	width = newWidth;
	height = newHeight;
	aspectRatio = 1.0f * width / height;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// Set the clipping volume
	gluPerspective(45, aspectRatio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		  x + lx, y + ly, z + lz,
		  0.0f, 1.0f, 0.0f);
}

void drawSnowMan()
{
	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body 
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

GLuint createDL()
{
	GLuint snowManDL;

	// Create the id for the list
	snowManDL = glGenLists(2);

	// Draw snowman
	glNewList(snowManDL+1, GL_COMPILE);
	drawSnowMan();
	glEndList();

	// start list
	glNewList(snowManDL, GL_COMPILE);
	// call the function that contains the rendering commands
	for(int i = -3; i < 3; i++)
		for(int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 0, j * 10.0);
			glCallList(snowManDL + 1);
			glPopMatrix();
		}
	// endList
	glEndList();

	return(snowManDL);
}

void initScene()
{
	glEnable(GL_DEPTH_TEST);
	snowmenDisplayList = createDL();
}

void orientMe(float ang)
{
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
		  x + lx, y + ly, z + lz,
		  0.0f, 1.0f, 0.0f);
}


void moveMeFlat(int i)
{
	x = x + i * (lx * 0.1);
	z = z + i * (lz * 0.1);
	glLoadIdentity();
	gluLookAt(x, y, z,
		  x + lx, y + ly, z + lz,
		  0.0f, 1.0f, 0.0f);
}

void setOrthographicProjection()
{
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, width, 0, height);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -height, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection()
{
	// set the current matrix to GL_PROJECTION
	glMatrixMode(GL_PROJECTION);
	// restore previous settings
	glPopMatrix();
	// get back to GL_MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, char *string)
{
	char *c;
	// set position to start drawing fonts
	glRasterPos2f(x, y);
	// loop all the characters in the string
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void displayInfo(void)
{
	glColor3f(0.0f, 1.0f, 1.0f);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(30, 15, (char *) "GLUT Tutorial @ 3D Tech");
	renderBitmapString(30, 35, s);
	renderBitmapString(30, 55, (char *) "Esc - Quit");
	glPopMatrix();
	resetPerspectiveProjection();
}

void saveFPS(void)
{
	frame++;
	tm = glutGet(GLUT_ELAPSED_TIME);
	if (tm - tmBase > 1000) {
		sprintf(s, "FPS:%4.2f", frame * 1000.0 / (tm - tmBase));
		tmBase = tm;  
		frame = 0;
	}
}

void renderScene(void)
{
	if (modPos)
		moveMeFlat(modPos);
	if (modTheta) {
		theta += modTheta;
		orientMe(theta);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f,  100.0f);
	glVertex3f( 100.0f, 0.0f,  100.0f);
	glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 Snow Men
	glCallList(snowmenDisplayList);
 
	// saveFPS();
	// displayInfo();
	
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void pressKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		modTheta = -0.01f;
		break;

	case GLUT_KEY_RIGHT:
		modTheta = 0.01f;
		break;

	case GLUT_KEY_UP:
		modPos = 1;
		break;

	case GLUT_KEY_DOWN:
		modPos = -1;
		break;
	}
}

void releaseKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		if (modTheta < 0.0f) modTheta = 0.0f;
		break;

	case GLUT_KEY_RIGHT:
		if (modTheta > 0.0f) modTheta = 0.0f;
		break;

	case GLUT_KEY_UP:
		if (modPos > 0) modPos = 0;
		break;

	case GLUT_KEY_DOWN:
		if (modPos < 0)
			modPos = 0;
		break;
	}
}

void initWindow()
{
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	initScene();
}

int main(int argc, char **argv)
{
	font = GLUT_BITMAP_8_BY_13;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutCreateWindow("Snowmen");

	// register all callbacks
	initWindow();

	glutMainLoop();

	return(0);
}

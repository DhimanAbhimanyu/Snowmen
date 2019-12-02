#include <iostream>
#include <cmath>
#include <cstring>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "vector3f.hpp"
#include "consts.hpp"

static float aspectRatio;
static int height, width;
static GLint snowmenDisplayList;

static void initializeWindow(void);
static void initScene(void);
static GLuint createDisplayList(void);
static void displayScene(void);
static void drawSnowMan(void);
static void procKeys(unsigned char key, int x, int y);
static void modifySize(int newWidth, int newHeight);
static void setCameraPosition(void);

static Vector3f getSphereVertex(Vector3f centre, float radius,
				float theta, float phi);

static void drawArc(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3,
		    int numPoints);
static void drawArm(Vector3f start, float length, Vector3f dirVector);
static void drawButtons(Vector3f centre, float radius, int num);
static void drawEyes(Vector3f trans, float radius, float seperation);
static void drawHat(Vector3f centre, Vector3f axis,
		    float radius, float height, float brimRadius);
static void drawMuffler();
static void drawSunglasses();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Snowmen");
	// Set the background's color
	glClearColor(COLOR_BACKGROUND.getR(), COLOR_BACKGROUND.getG(),
		     COLOR_BACKGROUND.getB(), 0.0f);
	// Enable Anti-aliasing
	glEnable(GL_LINE_SMOOTH);

	// Finish off initializing the window
	initializeWindow();

	// Enter GLUT's loop
	glutMainLoop();

	return(0);
}

void initializeWindow(void)
{
	// Set the display callback
	glutDisplayFunc(displayScene);

	// Set the idle callback
	glutIdleFunc(displayScene);

	// Set the callback for when the size of the window changes
	glutReshapeFunc(modifySize);

	// Set up the callbacks for the keyboard
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(procKeys);

	// Initialize the scene to be displayed
	initScene();
}

void initScene(void)
{
	snowmenDisplayList = createDisplayList();
}

GLuint createDisplayList(void)
{
	// Create two lists
	GLuint snowMenDisplayList = glGenLists(2);

	// Add an snowman to the 2nd list
	glNewList(snowMenDisplayList + 1, GL_COMPILE);
	drawSnowMan();
	glEndList();

	// Begin the 1st list i.e. the one containing the snowmen
	glNewList(snowMenDisplayList, GL_COMPILE);
	// Add the snowmen
	for(int i = 0; i < 1; i++)
		for(int j = 0; j < 1; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 0, j * 10.0);
			glCallList(snowMenDisplayList + 1);
			glPopMatrix();
		}
	// End the 1st list
	glEndList();

	return snowMenDisplayList;
}

void displayScene(void)
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the ground
	glColor3f(COLOR_GROUND.getR(), COLOR_GROUND.getG(),
		  COLOR_GROUND.getB());
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f,  100.0f);
	glVertex3f( 100.0f, 0.0f,  100.0f);
	glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	// TBD Draw Trees

	// Draw the Snow Men
	glCallList(snowmenDisplayList);

	glFlush();
	glutSwapBuffers();
}

void drawSnowMan(void)
{
	// TBD
	// - Figure Must be Unique
	// - Must contain at least 10 primitives!

	glColor3f(COLOR_BODY.getR(), COLOR_BODY.getG(),
		  COLOR_BODY.getB());

	// Lower Body
	glTranslatef(0.0f, 0.5f, 0.0f);
	glutSolidSphere(0.5f, 30, 30);

	// Upper Body
	glTranslatef(0.0f, 0.5f, 0.0f);
	glutSolidSphere(0.375f, 30, 30);

	// Buttons
	glColor3f(COLOR_BUTTON.getR(), COLOR_BUTTON.getG(),
		  COLOR_BUTTON.getB());
	drawButtons(Vector3f(0.0f, 0.0f, 0.0f), 0.375f, 5);

	// Head
	glColor3f(COLOR_HEAD.getR(), COLOR_HEAD.getG(),
		  COLOR_HEAD.getB());
	glTranslatef(0.0f, 0.5f, 0.0f);
	glutSolidSphere(0.25f, 30, 30);

	// Arms
	glColor3f(COLOR_ARM.getR(), COLOR_ARM.getG(),
		  COLOR_ARM.getB());
	drawArm(Vector3f(0.375f, -0.5f, 0.0f), 1.0f,
		Vector3f(0.707f, 0.25f, 0.707f));
	drawArm(Vector3f(-0.375f, -0.5f, 0.0f), 1.0f,
		Vector3f(-0.707f, 0.25f, 0.707f));

	// Eyes
	glColor3f(COLOR_EYE.getR(), COLOR_EYE.getG(),
		  COLOR_EYE.getB());
	drawEyes(Vector3f(0.05f, 0.10f, 0.18f), 0.05f, -0.15f);

	// Nose
	glColor3f(COLOR_NOSE.getR(), COLOR_NOSE.getG(),
		  COLOR_NOSE.getB());
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 25, 5);

	// Mouth
	glColor3f(COLOR_MOUTH.getR(), COLOR_MOUTH.getG(),
		  COLOR_MOUTH.getB());
	glLineWidth(3);
	Vector3f centre(0.0f, -0.1875f, 0.025f);
	drawArc(getSphereVertex(centre, 0.25f, -M_PI / 4, -M_PI / 4),
		getSphereVertex(centre, 0.25f, -M_PI / 8, -M_PI / 8),
		getSphereVertex(centre, 0.25f, M_PI / 8, M_PI / 8),
		getSphereVertex(centre, 0.25f, M_PI / 4, M_PI / 4),
		50);

	// Hat
	drawHat(Vector3f(0.0f, 0.4f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f),
		0.15f, 0.375f, 0.025);

	// Muffler
	drawMuffler();

	// Sunglasses
	drawSunglasses();
}

// Get tbe co-ordinate of a point upon a sphere
// ref. https://en.wikipedia.org/wiki/Sphere#Equations_in_three-dimensional_space
Vector3f getSphereVertex(Vector3f centre, float radius,
			 float theta, float phi)
{
	return Vector3f(centre.getX() + radius * sin(theta) * cos(phi),
			centre.getY() + radius * sin(theta) * sin(phi),
			centre.getZ() + radius * cos(theta));
}

void drawButtons(Vector3f centre, float radius, int num)
{
	glLineWidth(6);
	glPushMatrix();
	for (float theta = -M_PI * 3.0f / 8.0f, inc = M_PI * 3.0f / (8.0f * num);
	     theta <= M_PI * 3.0f / 8.0f; theta += inc + inc) {
		Vector3f buttonCentre = getSphereVertex(
			centre, radius, theta + inc,
			copysignf(M_PI / 2, theta + inc));
		Vector3f axis = buttonCentre - centre;

		Vector3f pos = Vector3f(0,0, radius / 2);
		float angle = Vector3f::angleRad(axis, Vector3f(0, 0, 1)) / PIby180;

		pos = pos.rotate(Vector3f(axis.getY(), axis.getX(), 0), angle);
		buttonCentre -= pos;

		glPushMatrix();

		glTranslatef(buttonCentre.getX(), buttonCentre.getY(),
			     buttonCentre.getZ());
		glRotatef(theta, axis.getY(), axis.getX(), 0);

		glutSolidSphere(0.0375, 25, 25);		

		glPopMatrix();
	}
	glPopMatrix();
}

void drawArm(Vector3f start, float length, Vector3f dirVector)
{
	glPushMatrix();
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(start.getX(), start.getY(), start.getZ());
	Vector3f end(start.getX() + dirVector.getX() * length,
		     start.getY() + dirVector.getY() * length,
		     start.getZ() + dirVector.getZ() * length);
	glVertex3f(end.getX(), end.getY(), end.getZ());
	glEnd();

	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(end.getX(), end.getY(), end.getZ());
	Vector3f finger(end.getX() + dirVector.getX() * length / 4,
			end.getY() + dirVector.getY() * length / 4,
			end.getZ() + dirVector.getZ() * length / 4);
	glVertex3f(finger.getX(), finger.getY(), finger.getZ());
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(end.getX(), end.getY(), end.getZ());
	glVertex3f(finger.getX(), finger.getY() + 0.1f, finger.getZ() + 0.1f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(end.getX(), end.getY(), end.getZ());
	glVertex3f(finger.getX(), finger.getY() + 0.1f, finger.getZ() - 0.1f);
	glEnd();

	glPopMatrix();
}

void drawEyes(Vector3f trans, float radius, float seperation)
{
	glPushMatrix();
	glTranslatef(trans.getX(), trans.getY(), trans.getZ());
	glutSolidSphere(radius, 25, 25);
	glTranslatef(seperation, 0.0f, 0.0f);
	glutSolidSphere(radius, 25, 25);
	glPopMatrix();
}

// Quit upon 'Esc' or 'q'
void procKeys(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q') exit(0);
}

void modifySize(int newWidth, int newHeight)
{
	// Ensure that the newHeight is not zero
	if(newHeight == 0) newHeight = 1;

	width = newWidth;
	height = newHeight;
	aspectRatio = ((float) width) / ((float) height);

	// Set the viewport to encompass the entire window
	glViewport(0, 0, width, height);

	setCameraPosition();
}

void setCameraPosition(void)
{
	const float SZ = 3.125f;
	
	// Reset the coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up the orthographic projection
	if (width > height)
		// width is smaller, go from -SZ .. SZ in width
		glOrtho(-SZ, SZ, -SZ / aspectRatio,
			SZ / aspectRatio, -1.0f, 1.0f);
	else
		// height is smaller, go from -SZ .. SZ in height
		glOrtho(-SZ * aspectRatio, SZ * aspectRatio, -SZ,
			SZ, -1.0f, 1.0f);
}

// Draw an Arc on a Sphere by Using a Cubic Bezier Curve
// ref. https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Cubic_B%C3%A9zier_curves
void drawArc(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f p3,
	     int numPoints)
{
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for (int idx = 0; idx <= numPoints; idx++) {
		float t = ((float) idx) / numPoints;
		float a = (1.0f - t) * (1.0f - t) * (1.0f - t);
		float b = 3.0f * (1.0f - t) * (1.0f - t) * t;
		float c = 3.0f * (1.0f - t) * t * t;
		float d = t * t * t * t;
		glVertex3f(a * p0.getX() + b * p1.getX()
			   + c * p2.getX() + d * p3.getX(),
			   a * p0.getY() + b * p1.getY()
			   + c * p2.getY() + d * p3.getY(),
			   a * p0.getZ() + b * p1.getZ()
			   + c * p2.getZ() + d * p3.getZ());
	}
	glEnd();
	glPopMatrix();
}

void drawHat(Vector3f centre, Vector3f axis,
	     float radius, float height, float brimRadius)
{
	Vector3f pos = Vector3f(0,0, height / 2);
	float theta = Vector3f::angleRad(axis, Vector3f(0, 0, 1)) / PIby180;

	pos = pos.rotate(Vector3f(axis.getY(), axis.getX(), 0), theta);
	centre -= pos;

	glPushMatrix();

	glTranslatef(centre.getX(), centre.getY(), centre.getZ());
	glRotatef(theta, axis.getY(), axis.getX(), 0);

	glColor3f(COLOR_HAT.getR(), COLOR_HAT.getG(),
		  COLOR_HAT.getB());
	glutSolidCylinder(radius, height, 50, 50);

	glColor3f(COLOR_HAT_BRIM.getR(), COLOR_HAT_BRIM.getG(),
		  COLOR_HAT_BRIM.getB());
	glutSolidTorus(radius, radius + brimRadius,
		       50, 50);

	glPopMatrix();
}

void drawMuffler()
{
	// TBD
	glPushMatrix();
	glBegin(GL_LINES);
	glEnd();
	glPopMatrix();
}

void drawSunglasses()
{
	// TBD
	glPushMatrix();
	glBegin(GL_LINES);
	glEnd();
	glPopMatrix();
}

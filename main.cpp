#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

#include <time.h>
#include <stdio.h>

#include "vectors.hpp"
#include "draw.hpp"
#include "rotation.hpp"

#include "display_colors.hpp"
#include "light0_consts.hpp"
#include "consts.hpp"
#include "display.hpp"
#include "displaygroupfunc.hpp"
#include "globals.hpp"
#include "shading.hpp"
#include "tree_set.hpp"

static const GLfloat THETA = 22.5;
static const GLfloat MOD_THETA = 0.025;
static const GLfloat SCALE = 0.8;
static const GLfloat SCALING_FACTOR = 1.25;
static const GLfloat SCALING_RATIO = 25;
static const GLfloat MOD_Y_POS = 0.5;
static const GLfloat ZNEAR = 1;
static const GLfloat ZFAR = 1000;
static const GLfloat MOD_Z = 5;
static const Vector3f POS = Vector3f(0, 20, 80);
static const GLfloat TIMER_FUNC_INTERVAL = 100;

// TBD add sub-menus
// Define possible values for the menu
enum MENU_VALS {MENU_SOLID, MENU_WIREFRAME,
		MENU_SINGLE, MENU_INWARD, MENU_OUTWARD, MENU_TANGENT,
		MENU_GROUP, MENU_QUIT};

static GLfloat theta = THETA, modTheta = MOD_THETA, scale = SCALE;
static Vector3f pos = POS;
static GLfloat thetaPos = THETA;
static GLfloat radiusPos;
static GLfloat zNear = ZNEAR;
static GLfloat zFar = ZFAR;

static float aspectRatio;	// The aspect ratio of the window
static int height, width;	// The height and the width of the window

// The id of the menu
static int clickId = 0;

static Rotation currRotation, oldRotation;

static Vector4f lightPosition = LIGHT0_POSITION;

// The object used for drawing solid shapes
static Draw drawSolid(glutSolidSphere, glutSolidCube,
		      glutSolidTorus, glutSolidCone);
// The object used for drawing wire-frame shapes
static Draw drawWire(glutWireSphere, glutWireCube,
		     glutWireTorus, glutWireCone);

static TreeSet trees;

// The display group func
DisplayGroupFunc displayGroupFunc;

// A pointer to object that is currently being used for drawing
Draw *drawCurr = &drawSolid;

static void initializeWindow(void);	// Init the window
static void initLighting(void);
static void initMaterial(void);

static void setView(void);
static void orientMe(float& theta, float& modTheta);
//static void moveMe(Vector3f& pos, float& modPos, Vector3f& deltaPos);
static void displayScene(void);		// Display the scene on the window
static void rotationUpdate(void);

// The handler for the keys
static void procKeys(unsigned char key, int x, int y);
static void pressKey(int key, int x, int y);
static void releaseKey(int key, int x, int y);
// The handler for when the window is resized
static void modifySize(int newWidth, int newHeight);
// TBD
static void setCoordSystem(void);
// The handler for the idle function
static void idleFunc(void);

// The handler for the timer function
static void timerFunc(int data);

// Quit from application, with the specified return code
static void quit(int code = 0);

// The handler for the menu
static void clickMenu(int value);
// Initialize the menu
static void initMenu(void);

static void printInfo(void);

static void setLightPosition(void);

static void drawGround(void);

static inline void setRadiusPos(void)
{
	radiusPos = sqrt(pos.getX() * pos.getX() + pos.getZ() * pos.getZ());
}

static inline void setLightfv(const GLenum light, const GLenum pname,
			      const GLfloat r, const GLfloat g,
			      const GLfloat b, const GLfloat w)
{
	GLfloat params[] = {r, g, b, w};
	glLightfv(light, pname, params);
}

inline void setMaterialfv(const GLenum face, const GLenum pname,
			  const GLfloat r, const GLfloat g,
			  const GLfloat b, const GLfloat w)
{
	GLfloat params[] = {r, g, b, w};
	glMaterialfv(face, pname, params);
}

// Seed rand() with current time
void seedRand(void)
{
	srand(time(NULL));
}

int main(int argc, char **argv)
{
	seedRand();

	// Initialize GLUT
	glutInit(&argc, argv);
	// Setup the display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window's initial size
	glutInitWindowSize(800, 640);
	// Set the window's initial positon
	glutInitWindowPosition(100, 100);
	// Create the window
	glutCreateWindow("Snowmen");
	// Initialize GLEW
	glewInit();
	// Set the background's color
	glClearColor(DISPLAY_COLOR_BACKGROUND.getR(),
		     DISPLAY_COLOR_BACKGROUND.getG(),
		     DISPLAY_COLOR_BACKGROUND.getB(), 0);
	// Enable Anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	// Enable Lighting
	glEnable(GL_LIGHTING);
	// Enable Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthRange(-50, 50);

	// Finish off initializing the window
	initializeWindow();

	// Set up the shaders
	createShaders();

	// Enter GLUT's loop
	glutMainLoop();

	return(0);
}

// Wrap up initting the window by setting up callbacks
void initializeWindow(void)
{
	// Start off by drawing solid object
	displayGroupFunc.selectRandDisplay();

	// Init radius of pos
	setRadiusPos();

	// Set the display callback
	glutDisplayFunc(displayScene);

	// Set the callback for when the size of the window changes
	glutReshapeFunc(modifySize);

	// Set up the callbacks for the keyboard
	glutKeyboardFunc(procKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// Set the idle function
	glutIdleFunc(idleFunc);

	glutTimerFunc(TIMER_FUNC_INTERVAL, timerFunc, 0);
	
	// Setup the menu
	initMenu();

	// Setup the material
	initMaterial();

	// Setup the coordinate system
	setView();
}

void initTrees(void)
{
}

void timerFunc(int data)
{
	//printf("hit timerFunc\n");
	glutPostRedisplay();
	//glutTimerFunc(TIMER_FUNC_INTERVAL, timerFunc, 0);
}

void initLighting(void)
{
	setLightfv(GL_LIGHT0, GL_AMBIENT,
		   LIGHT0_AMBIENT.getR(),
		   LIGHT0_AMBIENT.getG(),
		   LIGHT0_AMBIENT.getB(),
		   LIGHT0_AMBIENT.getA());
	setLightfv(GL_LIGHT0, GL_DIFFUSE,
		   LIGHT0__DIFFUSE.getR(),
		   LIGHT0__DIFFUSE.getG(),
		   LIGHT0__DIFFUSE.getB(),
		   LIGHT0__DIFFUSE.getA());
	setLightfv(GL_LIGHT0, GL_SPECULAR,
		   LIGHT0_SPECULAR.getR(),
		   LIGHT0_SPECULAR.getG(),
		   LIGHT0_SPECULAR.getB(),
		   LIGHT0_SPECULAR.getA());
	setLightPosition();

	glEnable(GL_LIGHT0);
}

void setLightPosition(void)
{
	//printf("lightPosition (%f, %f, %f)\n",
	//       lightPosition.getX(), lightPosition.getY(),
	//       lightPosition.getZ());

	setLightfv(GL_LIGHT0, GL_POSITION,
		   lightPosition.getX(),
		   lightPosition.getY(),
		   lightPosition.getZ(),
		   lightPosition.getW());
}

void initMaterial(void)
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	setMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, 1, 1, 1, 1);
	setMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, 0, 0, 0, 1);
}

// Initialize the menu
void initMenu(void)
{
	// Create a new menu
	clickId = glutCreateMenu(clickMenu);

	// Add entries to it
	glutAddMenuEntry("Solid Figures", MENU_SOLID);
	glutAddMenuEntry("Wire-frame Figures", MENU_WIREFRAME);
	glutAddMenuEntry("Single Snowman", MENU_SINGLE);
	glutAddMenuEntry("Inward Facing Circle of Snowmen", MENU_INWARD);
	glutAddMenuEntry("Outward Facing Circle of Snowmen", MENU_OUTWARD);
	glutAddMenuEntry("Tangent Facing Circle of Snowmen", MENU_TANGENT);
	glutAddMenuEntry("Groups of Snowmen", MENU_GROUP);
	glutAddMenuEntry("Quit", MENU_QUIT);

	// Attach the menu to the right button of the mouse
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// The handler for the menu
void clickMenu(int value)
{
	switch (value) {
	case MENU_SOLID:
		// Switch to drawing solid figures
		drawCurr = &drawSolid;
		glutPostRedisplay();
		break;
	case MENU_WIREFRAME:
		// Switch to drawing wire-frame figures
		drawCurr = &drawWire;
		glutPostRedisplay();
		break;
	case MENU_SINGLE:
		// Switch to displaying a single snowman
		displayGroupFunc.selectDisplayListOne();
		glutPostRedisplay();
		break;
	case MENU_INWARD:
		// Switch to displaying a bunch of snowmen
		// in a circle, who face the center of the circle
		displayGroupFunc.selectDisplayListInward();
		glutPostRedisplay();
		break;
	case MENU_OUTWARD:
		// Switch to displaying a bunch of snowmen
		// in a circle, who face away from the center of the circle
		displayGroupFunc.selectDisplayListOutward();
		glutPostRedisplay();
		break;
	case MENU_TANGENT:
		// Switch to displaying a bunch of snowmen
		// in a circle, who face along the tangent of the circle
		displayGroupFunc.selectDisplayListTangent();
		glutPostRedisplay();
		break;
	case MENU_GROUP:
		// Switch to displaying groups of snowmen
		displayGroupFunc.selectDisplayListGroup();
		glutPostRedisplay();
		break;
	case MENU_QUIT:
		// Quit from the application
		quit();
		break;
	}
}

void setView(void)
{
	//printf("pos (%f, %f, %f)\n", pos.getX(), pos.getY(), pos.getZ());

	glLoadIdentity();
	if (pos.getY() < 0)
		pos.setY(0);
	gluLookAt(pos.getX(), pos.getY(), pos.getZ(),
		  //pos.getX() + deltaPos.getX(), 0, pos.getZ() + deltaPos.getZ(),
		  0, 0, 0,
		  //-pos.getX(), 0, -pos.getZ(),
		  0, 1, 0);
	//glRotatef(theta, 0, 1, 0);

	// Setup the lighting
	initLighting();
}

void orientMe(float& theta, float& modTheta)
{
	if (modTheta == 0)
		return;

	theta += modTheta;
	modTheta = 0;
	Rotation::adjustTheta(theta);

	GLfloat radTheta = Rotation::deg2Rad(theta);
	lightPosition.setX(sin(radTheta));
	lightPosition.setZ(-cos(radTheta));
	setLightPosition();

	setView();
}

#if 0
void moveMe(Vector3f& pos, float& modPos, Vector3f& deltaPos)
{
	if (modPos == 0)
		return;

	pos.setX(pos.getX() + modPos * deltaPos.getX());
	pos.setZ(pos.getZ() + modPos * deltaPos.getZ());

	setView();
}
#endif

// Display the current state of the scene upon the window
void displayScene(void)
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	// Update the rotation parameters
	rotationUpdate();

	// Draw the ground
	drawGround();

	// Draw the current list of snowmen
	displayGroupFunc.getDisplayCurr()->draw();

	// Draw Trees
	trees.draw();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void drawGround(void)
{
	glPushMatrix();
	float size = 200;
	Vector3f centre(0, -size / 2, 0);
	glTranslatef(centre.getX(), centre.getY(), centre.getZ());
	glColor3f(DISPLAY_COLOR_GROUND.getR(), DISPLAY_COLOR_GROUND.getG(),
		  DISPLAY_COLOR_GROUND.getB());
	drawCurr->drawCube(size);
	glPopMatrix();
}

void rotationUpdate(void)
{
	//printf("%f %f\n",
	//       currRotation.getRotationX(), currRotation.getRotationY());

	// Rotate about the Y axis for animation
	glRotatef(currRotation.getRotationY(), 0, 1, 0);

	// Rotate about the X axis
	glRotatef(currRotation.getRotationX(), 1, 0, 0);
}

// Quit from the application
void quit(int code)
{
	// Destroy the menu
	if (clickId) {
		glutDetachMenu(GLUT_RIGHT_BUTTON);
		glutDestroyMenu(clickId);
	}
	// Exit with the passed code
	exit(code);
}

// Handle the keys depressed
void procKeys(unsigned char key, int x, int y)
{
	switch (key) {
	// Quit upon 'Esc' or 'q'
	case 27:
	case 'q':
		quit();
		break;

	case '0':
		// Display a single snowman
		displayGroupFunc.selectDisplayListOne();
		glutPostRedisplay();
		break;

	case '1':
		// Display snowmen facing inward
		displayGroupFunc.selectDisplayListInward();
		glutPostRedisplay();
		break;

	case '2':
		// Display snowmen facing outward
		displayGroupFunc.selectDisplayListOutward();
		glutPostRedisplay();
		break;

	case '3':
		// Display snowmen facing along the tangent
		displayGroupFunc.selectDisplayListTangent();
		glutPostRedisplay();
		break;

	case 'g':
		// Display groups of snowmen
		displayGroupFunc.selectDisplayListGroup();
		glutPostRedisplay();
		break;

	case 'a':
		// Start rotating in a clockwise direction
		// along the Y axis
		currRotation.decRotationY();
		glutPostRedisplay();
		break;

	case 'd':
		// Start rotating in a counter-clockwise direction
		// along the Y axis
		currRotation.incRotationY();
		glutPostRedisplay();
		break;

	case 'x':
		// Stop rotating about the Y axis and reset the rotation
		currRotation.reset();
		lightPosition = LIGHT0_POSITION;
		setLightPosition();
		setView();
		theta = THETA;
		modTheta = MOD_THETA;
		scale = SCALE;
		thetaPos = THETA;
		pos = POS;
		setRadiusPos();
		glutPostRedisplay();
		break;

	case 'p':
		// Pause rotating about the Y axis
		currRotation.pauseAnimationY();
		glutPostRedisplay();
		break;

	case 'w':
		// Rotate by ROTATION_DELTA about the X axis
		currRotation.incRotationX();
		glutPostRedisplay();
		break;

	case 's':
		// Rotate by ROTATION_DELTA about the X axis
		currRotation.decRotationX();
		glutPostRedisplay();
		break;

	case '-':
		// Zoom in
		scale *= SCALING_FACTOR;
		setCoordSystem();
		glutPostRedisplay();
		break;

	case '+':
		// Zoom out
		scale /= SCALING_FACTOR;
		setCoordSystem();
		glutPostRedisplay();
		break;

	case 'i':
		printInfo();
		break;

	case 'h':
		modTheta -= MOD_THETA;
		orientMe(theta, modTheta);
		glutPostRedisplay();
		break;

	case 'l':
		modTheta += MOD_THETA;
		orientMe(theta, modTheta);
		break;

	case 'k':
		setView();
		glutPostRedisplay();
		break;

	case 'j':
		setView();
		glutPostRedisplay();
		break;

	case 'r':
		if (drawCurr == &drawWire) {
			// Switch to drawing solid figures
			drawCurr = &drawSolid;
			glutPostRedisplay();
		} else if (drawCurr == &drawSolid) {
			// Switch to drawing wire-frame figures
			drawCurr = &drawWire;
			glutPostRedisplay();
		}
	}
}

void pressKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		thetaPos -= MOD_THETA;
		break;

	case GLUT_KEY_RIGHT:
		thetaPos += MOD_THETA;
		break;

	case GLUT_KEY_UP:
		pos.setY(pos.getY() + MOD_Y_POS);
		break;

	case GLUT_KEY_DOWN:
		pos.setY(pos.getY() - MOD_Y_POS);
		break;
	}
}

void releaseKey(int key, int x, int y)
{
	GLfloat radThetaPos;
	switch (key) {
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
		//printf("thetaPos %f\n", thetaPos);
		radThetaPos = Rotation::deg2Rad(thetaPos);
		pos.setX(radiusPos * sin(radThetaPos));
		pos.setZ(radiusPos * cos(radThetaPos));
		break;

	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		break;

	default:
		return;
	}

	setView();
	glutPostRedisplay();
}

//  The callback for when the size of the window changes
void modifySize(int newWidth, int newHeight)
{
	//printf("modifySize(%d, %d)\n", newWidth, newHeight);

	// Ensure that the newHeight is not zero
	if(newHeight == 0) newHeight = 1;

	// Update the width, height and aspect ratio
	width = newWidth;
	height = newHeight;
	aspectRatio = ((float) width) / ((float) height);

	// TBD
	setCoordSystem();

	// Set the position of the camera
	setView();
}

void setCoordSystem(void)
{
	//printf("scale %f, aspectRatio %f\n", scale, aspectRatio);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(SCALING_RATIO * scale, aspectRatio, zNear, zFar);

	// Set the viewport to encompass the entire window
	glViewport(0, 0, width, height);

	// Switch to the modelview matrix
	glMatrixMode(GL_MODELVIEW);
}

// The idle callback
void idleFunc(void)
{
	if (currRotation.rotating()) {
		currRotation.update();
		glutPostRedisplay();
	}
}

void printInfo(void)
{
	printf("theta %f, modTheta %f, scale %f\n", theta, modTheta, scale);
	//printf("zNear %f, zFar %f\n", zNear, zFar);
	printf("pos (%f, %f, %f)\n",
	       pos.getX(), pos.getY(), pos.getZ());
	printf("currRotation (%f %f %f %f)\n", currRotation.getRotationY(),
	       currRotation.getRotationX(), currRotation.getRotationYDelta(),
	       currRotation.getRotateY());
}

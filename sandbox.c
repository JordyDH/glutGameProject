#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "glutGameLibs.h"

GLdouble xlens = 1.0, ylens = 1.0, zlens = 3.0;
GLdouble xref = 1.0, yref = 1.0, zref = 0.0;
GLdouble xvw = 0.0, yvw = 1.0, zvw = 0.0;
GLdouble xmin = -2.0, xmax = 4.0, ymin = -2.0, ymax = 3.0;
GLdouble near = 0.1, far = 10.0;
GLdouble hoek = 60.0;
GLfloat ttx = 0.25, tty = 0.25, ttz = 0.25;
GLint lijnen = 0;
GLubyte projectie = 'p';

int togle = 0;
void kubus();

void myinit(void)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}



void kubus(void)
{
	double color = sin((double)glutGameSystickGet()/100);
	if(color<0) color *= -1.0;
	glColor3f(color,0,1.0-color);
	glutSolidCube(1);
	glColor3f(0,0,0);
	glLineWidth(3);
	glutWireCube(1);
}

int main( int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glutInitWindowPosition(1920+10,10);
	glutInitWindowSize(800, 800);
	glutCreateWindow("SANDOX GLUTGAME");
    	myinit();

	glutGameInit();
	glutGameRenderSceneSet(kubus);
	glutGameMainLoop();
}

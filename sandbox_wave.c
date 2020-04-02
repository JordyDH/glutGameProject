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

uint32_t buffer;

void myinit(void)
{
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}



void cube(void)
{
	glutSolidCube(1);
	//glPushAttrib(GL_CURRENT_BIT);
	//glColor3f(0,0,0);
	//glLineWidth(3);
	//glutWireCube(1);
	//glPopAttrib();
}

double angle = 0;
uint64_t w = 51;
uint64_t lastsystick = 0;
uint64_t cube_id = 0;
double miny = 0;
double dist(double x0, double y0, double x1, double y1)
{
	return sqrt((double)pow(x0-x1,2)+(double)pow(y0-y1,2));
}
void world()
{
	if(lastsystick != glutGameSystickGet())
	{
		angle -= 0.08;
		lastsystick = glutGameSystickGet();
	}
	double h = 0;
	double offset = 0;
	for(int z = 0; z < w; z++)
	{
	for(int x = 0; x < w; x++)
	{
		//calc parameters
		offset = ((((dist(x,z,w/2,w/2)/w)*2)-1)*M_PI*1.5);
		h = (double)((sin(angle+offset)+1)/2)*(double)(w/2);
		// Place cube
		glPushMatrix();
		glTranslatef(x,1,-z);
		glScalef(1,h+miny,1);
		glColor3f(h/(double)(w/2),0,1.0-h/(double)(w/2));
		//glColor3f(h/(double)(w/2),0,0);
		glCallList(cube_id);
		glPopMatrix();
	}
		offset -= 0.02;
	}
}

int main( int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_CULL_FACE);;
	glCullFace(GL_FRONT);
	glutInitWindowPosition(1920+10,10);
	glutInitWindowSize(800, 800);
	glutCreateWindow("SANDOX GLUTGAME");
    	myinit();

	glutGameInit();
/*
	glutGameObjectobject *obj;
	obj = glutGameObjectsAlloc_object();
	(*obj).x = i;
	(*obj).y = j;
	(*obj).z = -k;
	(*obj).callback = kubus;
	(*obj).id = 0;
*/

	cube_id = glGenLists(1);
	glNewList(cube_id, GL_COMPILE);
	cube();
	glEndList();

	glutGameRenderSceneSet(world);
	glutGameMainLoop();
}

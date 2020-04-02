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
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}


void fullkubus(int x, int y, int z, float size)
{
		glVertex3d(x-(size/2),y-(size/2),z+(size/2));
		glVertex3d(x+(size/2),y-(size/2),z+(size/2));
		glVertex3d(x+(size/2),y+(size/2),z+(size/2));
		glVertex3d(x-(size/2),y+(size/2),z+(size/2));
		glVertex3d(x+(size/2),y-(size/2),z+(size/2));
		glVertex3d(x+(size/2),y-(size/2),z-(size/2));
		glVertex3d(x+(size/2),y+(size/2),z-(size/2));
		glVertex3d(x+(size/2),y+(size/2),z+(size/2));
		glVertex3d(x-(size/2),y-(size/2),z-(size/2));
		glVertex3d(x+(size/2),y-(size/2),z-(size/2));
		glVertex3d(x+(size/2),y+(size/2),z-(size/2));
		glVertex3d(x-(size/2),y+(size/2),z-(size/2));
		glVertex3d(x-(size/2),y-(size/2),z+(size/2));
		glVertex3d(x-(size/2),y-(size/2),z-(size/2));
		glVertex3d(x-(size/2),y+(size/2),z-(size/2));
		glVertex3d(x-(size/2),y+(size/2),z+(size/2));
		glVertex3d(x-(size/2),y-(size/2),z-(size/2));
		glVertex3d(x+(size/2),y-(size/2),z-(size/2));
		glVertex3d(x+(size/2),y-(size/2),z+(size/2));
		glVertex3d(x-(size/2),y-(size/2),z+(size/2));
		glVertex3d(x-(size/2),y+(size/2),z-(size/2));
		glVertex3d(x+(size/2),y+(size/2),z-(size/2));
		glVertex3d(x+(size/2),y+(size/2),z+(size/2));
		glVertex3d(x-(size/2),y+(size/2),z+(size/2));
}

void kubus(void)
{
	glPushMatrix();
	glScalef(0.5,0.5,0.5);
	glutSolidCube(1);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0,0,0);
	glLineWidth(3);
	glutWireCube(1);
	glPopMatrix();
	glutWireCube(1);
	glPopAttrib();
}

void world()
{
	double color = sin((double)glutGameSystickGet()/100);
	if(color<0) color *= -1.0;
	glColor3f(color,0.0,1.0-color);
	glutGameRenderAllObjects();
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

	glutGameObjectobject *obj;
	for(int k = 0; k < 10; k++)
	{
	for(int j = 0; j < 10; j++)
	{
	for(int i = 0; i < 10; i++)
	{
		obj = glutGameObjectsAlloc_object();
		(*obj).x = i;
		(*obj).y = j;
		(*obj).z = -k;
		(*obj).callback = kubus;
		(*obj).id = 0;
	}
	}
	}
	//Pre render the world
	glutGameRenderCompileList();

	glShadeModel(GL_FLAT);
	glutGameRenderSceneSet(world);
	glutGameMainLoop();
}

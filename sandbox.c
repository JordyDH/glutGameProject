#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "glutGameLibs.h"
#include "perlin.h"

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
#define SIZE 80
#define SCALE 0.02
double terrain[SIZE][SIZE];

void myinit(void)
{
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	genterain();
}

uint64_t terrain_id = 0;
void terrain_render()
{

	for(int y = 0; y < SIZE-1; y++){
	for(int x = 0; x < SIZE-1; x++){
/*
	glColor3f(terrain[x][y]/10,0,1.0-terrain[x][y]/10);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f((double)x, terrain[x][y],(double)y);
		glVertex3f((double)x, terrain[x][y+1],(double)(y+1));
		glVertex3f((double)(x+1), terrain[x+1][y],(double)(y));
		glVertex3f((double)(x+1), terrain[x+1][y+1],(double)(y+1));
	glEnd();
*/
//	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1,1,1);
	glBegin(GL_LINE_STRIP);
		glVertex3f((double)x*SCALE, terrain[x][y],(double)y*SCALE);
		glVertex3f((double)x*SCALE, terrain[x][y+1],(double)(y+1)*SCALE);
		glVertex3f((double)(x+1)*SCALE, terrain[x+1][y+1],(double)(y+1)*SCALE);
		glVertex3f((double)(x+1)*SCALE, terrain[x+1][y],(double)(y)*SCALE);
		glVertex3f((double)x*SCALE, terrain[x][y],(double)y*SCALE);
		glVertex3f((double)(x+1)*SCALE, terrain[x+1][y+1],(double)(y+1)*SCALE);
	glEnd();
//	glPopAttrib();

	}
	}
}

double offset = 0;
void genterain()
{
	for(int x = 0; x < SIZE; x++)
	{
		for(int y = 0; y < SIZE; y++){
			terrain[x][y] = Perlin_Get2d(offset+(double)x*SCALE,(double)y*SCALE, 0.5, 10);
		}
	}
}
uint64_t base_systick=0;
void world()
{
	if(base_systick != glutGameSystickGet())
	{
		offset += 0.05;
		base_systick = glutGameSystickGet();
		genterain();
		if(terrain_id)glDeleteLists(terrain_id,1);
		terrain_id = glGenLists(1);
		glNewList(terrain_id, GL_COMPILE);
		terrain_render();
		glEndList();
	}
	//terrain_render();
	glCallList(terrain_id);
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
	terrain_id = glGenLists(1);
	glNewList(terrain_id, GL_COMPILE);
	terrain_render();
	glEndList();

	glutGameRenderSceneSet(world);
	glutGameMainLoop();
}

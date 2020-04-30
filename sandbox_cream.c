#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "glutGameLibs.h"
#include "InitJPG.h"

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

tImageJPG *jpgp;
GLsizei aantaltx = 4;
GLuint texobj[4];

void myinit(void)
{
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glGenTextures(aantaltx, texobj);

	jpgp = LoadJPG("tex1.jpg");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texobj[0]);
	printf("%d %d\n",(*jpgp).sizeX, (*jpgp).sizeY);
	glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, jpgp->sizeX, jpgp->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, jpgp->data);

	jpgp = LoadJPG("tex2.jpg");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texobj[1]);
	printf("%d %d\n",(*jpgp).sizeX, (*jpgp).sizeY);
	glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, jpgp->sizeX, jpgp->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, jpgp->data);

	jpgp = LoadJPG("tex3.jpg");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texobj[2]);
	printf("%d %d\n",(*jpgp).sizeX, (*jpgp).sizeY);
	glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, jpgp->sizeX, jpgp->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, jpgp->data);

	jpgp = LoadJPG("tex4.jpg");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texobj[3]);
	printf("%d %d\n",(*jpgp).sizeX, (*jpgp).sizeY);
	glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, jpgp->sizeX, jpgp->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, jpgp->data);
}


void world()
{
	//glColor3f(1,0,0);
	GLUquadricObj *obj;
	obj = gluNewQuadric();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texobj[2]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gluQuadricTexture(obj,GL_TRUE);
	gluQuadricDrawStyle(obj,GLU_FILL);
	glRotated(90,1,0,0);
	gluCylinder(obj,1,1,5,20,20);
	glPopMatrix();
	gluDeleteQuadric(obj);

	obj = gluNewQuadric();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texobj[0]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gluQuadricTexture(obj,GL_TRUE);
	gluQuadricDrawStyle(obj,GLU_FILL);
	glTranslatef(5,0,0);
	gluSphere(obj,1,50,50);
	glPopMatrix();
	gluDeleteQuadric(obj);

	obj = gluNewQuadric();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texobj[1]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gluQuadricTexture(obj,GL_TRUE);
	gluQuadricDrawStyle(obj,GLU_FILL);
	glRotated(90,1,0,0);
	glTranslatef(5,0,0);
	gluCylinder(obj,1,0,5,20,20);
	glPopMatrix();
	gluDeleteQuadric(obj);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texobj[3]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);	glVertex3f(-10,-10,-5);
		glTexCoord2f(0,2);	glVertex3f(-10,10,-5);
		glTexCoord2f(2,2);	glVertex3f(10,10,-5);
		glTexCoord2f(2,0);	glVertex3f(10,-10,-5);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texobj[3]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPushMatrix();
	glTranslatef(20,0,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);	glVertex3f(-10,-10,-5);
		glTexCoord2f(0,1);	glVertex3f(-10,10,-5);
		glTexCoord2f(1,1);	glVertex3f(10,10,-5);
		glTexCoord2f(1,0);	glVertex3f(10,-10,-5);
	glEnd();
	glPopMatrix();
}

int main( int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
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
	glutGameRenderSceneSet(world);
	glutGameMainLoop();
}

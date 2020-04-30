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

	jpgp = LoadJPG("sky1.jpg");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texobj[0]);
	printf("%d %d\n",(*jpgp).sizeX, (*jpgp).sizeY);
	glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, jpgp->sizeX, jpgp->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, jpgp->data);
	jpgp = LoadJPG("dumy.jpg");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texobj[1]);
	printf("%d %d\n",(*jpgp).sizeX, (*jpgp).sizeY);
	glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB, jpgp->sizeX, jpgp->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, jpgp->data);

}
#define THIRD (double)1/3
void skybox(uint32_t id)
{
	double a = 0.001;
	double b = 0.001;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glPushMatrix();
	glScalef(50,50,50);
	//glRotated(180,1,0,0);
	glRotated((double)glutGameSystickGet()/100,1,0,0);
	glRotated((double)glutGameSystickGet()/200,0,1,0);
	glRotated((double)glutGameSystickGet()/300,0,0,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.25+a,THIRD+a);	glVertex3f(-1,-1,-1);
		glTexCoord2f(0.50,THIRD+a);	glVertex3f( 1,-1,-1);
		glTexCoord2f(0.5,THIRD*2-a);	glVertex3f( 1, 1,-1);
		glTexCoord2f(0.25,THIRD*2-a);	glVertex3f(-1, 1,-1);

		glTexCoord2f(0.5,THIRD+a);	glVertex3f( 1,-1,-1);
		glTexCoord2f(0.75,THIRD+a);	glVertex3f( 1,-1, 1);
		glTexCoord2f(0.75,THIRD*2-a);	glVertex3f( 1, 1, 1);
		glTexCoord2f(0.5,THIRD*2-a);	glVertex3f( 1, 1,-1);

		glTexCoord2f(1.0,THIRD+a);	glVertex3f(-1,-1, 1);
		glTexCoord2f(0.75,THIRD+a);	glVertex3f( 1,-1, 1);
		glTexCoord2f(0.75,THIRD*2-a);	glVertex3f( 1, 1, 1);
		glTexCoord2f(1.0,THIRD*2-a);	glVertex3f(-1, 1, 1);

		glTexCoord2f(0.25,THIRD+a);	glVertex3f(-1,-1,-1);
		glTexCoord2f(0.0,THIRD+a);	glVertex3f(-1,-1, 1);
		glTexCoord2f(0.0,THIRD*2-a);	glVertex3f(-1, 1, 1);
		glTexCoord2f(0.25,THIRD*2-a);	glVertex3f(-1, 1,-1);

		glTexCoord2f(0.25+b,THIRD*2-a);	glVertex3f(-1, 1,-1);
		glTexCoord2f(0.50-b,THIRD*2-a);	glVertex3f( 1, 1,-1);
		glTexCoord2f(0.50-b,1.0);	glVertex3f( 1, 1, 1);
		glTexCoord2f(0.25+b,1.0);	glVertex3f(-1, 1, 1);

		glTexCoord2f(0.25+b,THIRD);	glVertex3f(-1,-1,-1);
		glTexCoord2f(0.50-b,THIRD);	glVertex3f( 1,-1,-1);
		glTexCoord2f(0.50-b,0.0);	glVertex3f( 1,-1, 1);
		glTexCoord2f(0.25+b,0.0);	glVertex3f(-1,-1, 1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void cube(uint32_t id)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	for(int x = 0; x < 4; x++)
	{
	glRotatef(90,0,1,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);	glVertex3f(-1,-1,-1);
		glTexCoord2f(1,0);	glVertex3f( 1,-1,-1);
		glTexCoord2f(1,1);	glVertex3f( 1, 1,-1);
		glTexCoord2f(0,1);	glVertex3f(-1, 1,-1);
	glEnd();
	}
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);	glVertex3f(-1, 1,-1);
		glTexCoord2f(1,0);	glVertex3f( 1, 1,-1);
		glTexCoord2f(1,1);	glVertex3f( 1, 1, 1);
		glTexCoord2f(0,1);	glVertex3f(-1, 1, 1);

		glTexCoord2f(0,0);	glVertex3f(-1,-1,-1);
		glTexCoord2f(1,0);	glVertex3f( 1,-1,-1);
		glTexCoord2f(1,1);	glVertex3f( 1,-1, 1);
		glTexCoord2f(0,1);	glVertex3f(-1,-1, 1);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void world()
{
	skybox(texobj[0]);
	//cube(texobj[1]);
	glPushMatrix();
	glScalef(0.01,0.01,0.01);
	skybox(texobj[0]);
	glPopMatrix();
	//glutSolidCube(1);
}

int main( int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("SANDOX GLUTGAME");
    	//glutFullScreen(); 
	myinit();

	glutGameInit();
	glutGameRenderSceneSet(world);
	glutGameMainLoop();
}

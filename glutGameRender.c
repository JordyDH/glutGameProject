////////////////////////////////////////////////////////////////////
//
//	glutGameRender by Jordy de Hoon
//	MIT LICENSE , goto www.github.com/JordyDH/glutGameControl
//
////////////////////////////////////////////////////////////////////
#define  GLUT_GAMEC_VERSION "0.2"
//#define  GLUTGAME_DEBUG_INFO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "glutGameLibs.h"

//////////////////////////////////// FUNCTION POINTERS ////////////////////////////////////
void (*RenderScene_fnc)() = 0x00;	//Callback function to render the 3D scene
void (*RenderScene2D_fnc)() = 0x00;	//Callback function to render the 2D scene

//////////////////////////////////// [GLUTGAME RENDER FUNCTION]  ////////////////////////////////////
double	framecounter = 0;
int	timebase = 0;
double	fps = 0;
uint64_t screen_width = 0, screen_height = 0;

uint64_t glutGameRenderScreenWidth()
{
	return screen_width;
}

uint64_t glutGameRenderScreenHeight()
{
	return screen_height;
}

/*
* Function: void glutGameRenderSceneSet()
* -----------------------------
* Binds a callback fucntion to render the world
*/
void glutGameRenderSceneSet(void (*fnc_p)())
{
	RenderScene_fnc = fnc_p;
}

/*
* Function: void glutGameRenderScene()
* -----------------------------
* Calls the callback function to render or define the world
*/
void glutGameRenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutGameCameraRender();

	if(RenderScene_fnc!=0x00)
		(*RenderScene_fnc)();
	glutGameRenderLocalAxis();
}


void glutGameRender2DScene()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0,screen_width,screen_height,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);

	if(RenderScene2D_fnc != 0x00)
		(*RenderScene2D_fnc)();
	glutGameRenderOnScreenInfo();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

/*
* Function: void glutGameRender()
* -----------------------------
* The main function glut backend uses to render the world
* and player view.
*/
void glutGameRender()
{
	glutGameRenderScene();
	glutGameRender2DScene();
	#ifdef GLUTGAME_RENDER_DUBBELBUFFER
		glutSwapBuffers();
	#else
		glFinish();
		glFlush();
	#endif
	glutGameRenderFPS();
	#ifdef GLUTGAME_RENDER_SHOWFPS
	printf("[GLUTGAME][RENDER] FPS: %.3lf\n",glutGameRenderGetFPS());
	#endif
}

/*
* Function: void glutGameRescale()
* -----------------------------
* Used to update the camera aspect ratio and parameters
* when the screen size is changed.
* Inputs:
*	n_w : new width in pixels of the window
*	n_h : new height in pixels of the window
*/
void glutGameRescale(GLint n_w, GLint n_h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)n_w/n_h,  GLUTGAME_PLAYER_NEARSIGHT, GLUTGAME_PLAYER_FARSIGHT);
	glViewport(0, 0, n_w, n_h);
	screen_width = n_w; screen_height = n_h;
}

/*
* Function: void glutGameRenderFPS()
* -----------------------------
* Calculate the FPS of the current session.
*/
void glutGameRenderFPS()
{
	framecounter++;
	int time = glutGet(GLUT_ELAPSED_TIME);
	if(time - timebase > 100)
	{
		fps = framecounter*1000.0/(time-timebase);
		timebase = time;
		framecounter = 0;
	}
}

/*
* Function: void glutGameGetFPS()
* -----------------------------
* Returns the current FPS of the running session.
*/
double glutGameRenderGetFPS()
{
	return fps;
}


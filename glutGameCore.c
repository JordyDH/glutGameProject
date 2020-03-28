////////////////////////////////////////////////////////////////////
//
//	glutGameCore by Jordy de Hoon
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

//CONTROL REGISTER
extern uint64_t GLUTGAME_CONTROL_REG;
//////////////////////////////////// LIB VARS ////////////////////////////////////
double	*rotation_lr;
double	*rotation_ud;

double	*xl, *yl, *zl;
double	*xPos, *yPos, *zPos;

int render_time = 0;
unsigned int systick = 0;

glutGameObjectplayer mainplayer;
//////////////////////////////////// LIB FUNCTION ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ONLY CHANGE THE FUNCTION IF YOU KNOW WHAT YOU ARE DOING OR IF YOU JUST WANT TO EXPERIMENT
// SO HAVE A NICE EXPERIENCE, WHEN YOU HAVE PROBLEMS TO IMPLEMENT A FEATURE (NOT BUG ;) )
// OPEN A FEATURE REQUEST TICKET ON GITHUB

//////////////////////////////////// GLUTGAME CORE FUNCTIONS ////////////////////////////////////

/*
* Function: void glutGameInit()
* -----------------------------
* Initialise the glutGame enviroment with the options defines.
* returns nothing
*/
void test()
{

}
void glutGameInit()
{
	xl = &mainplayer.xl;
	yl = &mainplayer.yl;
	zl = &mainplayer.zl;
	xPos = &mainplayer.base.x;
	yPos = &mainplayer.base.y;
	zPos = &mainplayer.base.z;
	rotation_ud = &mainplayer.rotation_y;
	rotation_lr = &mainplayer.rotation_xz;

	glutGameControlInit(&mainplayer);
	glutDisplayFunc(glutGameRender);
	glutReshapeFunc(glutGameRescale);
	glutTimerFunc(0,glutGameIdle,0);
	glutTimerFunc(GLUTGAME_SYSTICK_INTERVAL,glutGameSystickService,0);
	glutGameCameraInit(&mainplayer,0,0,5);
}

/*
* Function: void glutGameMainLoop()
* -----------------------------
* Last function to be called, this will start the internal main loop service.
* returns nothing
*/
void glutGameMainLoop()
{
	glutMainLoop();
}

/*
* Function: void glutGameMainIdle()
* -----------------------------
* The internal idle function, is called when there a no events triggerd
* returns nothing
*/
void glutGameIdle()
{
	glutPostRedisplay();
	glutTimerFunc(0,glutGameIdle,0);
}

/*
* Function: void glutSystickService()
* -----------------------------
* Handles the systick of the world.
* returns nothing
*/
void glutGameSystickService(unsigned int systick_old)
{
	if(systick!=systick_old)printf("[GLUTGAME][WARNING] : Callback older systick, skipped a render?\n");
	systick++;
	glutTimerFunc(GLUTGAME_SYSTICK_INTERVAL,glutGameSystickService,systick);
}

/*
* Function: void glutSystickGet()
* -----------------------------
* Returns the current value of the systick of the world
* Value can overflow and return to 0.
*
*/
unsigned int glutGameSystickGet()
{
	return systick;
}



//////////////////////////////////// GLUTGAME IN GAME DEBUG FUNCTIONS ////////////////////////////////////


void glutGameRenderLocalAxis()
{
	//Draw the world axis in front of the camera
	//TODO Change lengt into define
	double lengt = 0.04;
	double mod_x, mod_y, mod_z;
	if(GLUTGAME_CONTROL_REG & (0x01 << 6))
	{
		glDisable(GL_DEPTH_TEST);
		glLineWidth(4);
		glBegin(GL_LINES);
			glColor3f(0,0,0);
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+((*zl)));
			glVertex3d((*xPos)+((*xl))+lengt,(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+((*zl)));
			glColor3f(0,0,0);
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+((*zl)));
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT+lengt,(*zPos)+((*zl)));
			glColor3f(0,0,0);
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+((*zl)));
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+lengt+((*zl)));
		glEnd();
		glLineWidth(2);
		glBegin(GL_LINES);
			glColor3f(1,0,0);
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+((*zl)));
			glVertex3d((*xPos)+((*xl))+lengt,(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+((*zl)));
			glColor3f(0,1,0);
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+((*zl)));
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT+lengt,(*zPos)+((*zl)));
			glColor3f(0,0,1);
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+((*zl)));
			glVertex3d((*xPos)+((*xl)),(*yPos)+((*yl))+GLUTGAME_PLAYER_HEIGHT,(*zPos)+lengt+((*zl)));
		glEnd();
		glEnable(GL_DEPTH_TEST);

	}
}

void glutBitmapString(void *font, char *text)
{
	for(;(*text)!='\0';text++)
	{
		//glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(*text));
		glutBitmapCharacter(font,(*text));
	}
}

void glutGameRenderOnScreenInfo()
{
	glColor3f(0,0,0);
	char text[30];
	//itoa(systick,text,10);
	glRasterPos2f(5,20);
	sprintf(text,"%s%s","glutGameCore Version dev.",GLUT_GAMEC_VERSION);
	glutBitmapString(GLUT_BITMAP_9_BY_15,text);
	glRasterPos2f(5,40);
	sprintf(text,"%s%d","systick: ",systick);
	glutBitmapString(GLUT_BITMAP_9_BY_15,text);
	glRasterPos2f(5,60);
	sprintf(text,"[%s%.3f]","xPos: ",(*xPos));
	glutBitmapString(GLUT_BITMAP_9_BY_15,text);
	sprintf(text,"[%s%.3f]"," yPos: ",(*yPos));
	glutBitmapString(GLUT_BITMAP_9_BY_15,text);
	sprintf(text,"[%s%.3f]"," zPos: ",(*zPos));
	glutBitmapString(GLUT_BITMAP_9_BY_15,text);
	glRasterPos2f(5,80);
	sprintf(text,"[%s%.3f]","rotation_xz: ",sin((*rotation_lr)));
	glutBitmapString(GLUT_BITMAP_9_BY_15,text);
	sprintf(text,"[%s%.3f]"," rotation_y: ",(*rotation_ud));
	glutBitmapString(GLUT_BITMAP_9_BY_15,text);
	glRasterPos2f(5,100);
	sprintf(text,"[%s%3.2lf]","FPS: ",glutGameRenderGetFPS());
	glutBitmapString(GLUT_BITMAP_9_BY_15,text);
}

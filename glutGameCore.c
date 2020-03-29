////////////////////////////////////////////////////////////////////
//
//	glutGameCore by Jordy de Hoon
//	MIT LICENSE , goto www.github.com/JordyDH/glutGameControl
//
////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "glutGameLibs.h"

//////////////////////////////////// LIB VARS ////////////////////////////////////
uint64_t systick = 0;
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
* The default player model will be linked to the other modules.
* Timer functions are for scheduling task of the engine.
* returns nothing
*/
void glutGameInit()
{
	glutDisplayFunc(glutGameRender);
	glutReshapeFunc(glutGameRescale);
	glutTimerFunc(0,glutGameIdle,0);
	glutTimerFunc(GLUTGAME_SYSTICK_INTERVAL,glutGameSystickService,0);

	glutGameControlInit(&mainplayer);
	glutGameCameraInit(&mainplayer,0,0,5);
	glutGameDebugInit(&mainplayer);
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

/*
* Function: glutGameObjectplayer *glutGameMainPlayerGet()
* -----------------------------
* Returns the adress in the memory where the mainplayer is stored
*/
glutGameObjectplayer *glutGameMainPlayerGet()
{
	return &mainplayer;
}




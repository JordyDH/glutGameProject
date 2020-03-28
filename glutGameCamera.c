////////////////////////////////////////////////////////////////////
//
//	glutGameCamera by Jordy de Hoon
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

//TODO Change to pointer or something better than extern
extern uint64_t GLUTGAME_CONTROL_REG;
double	*rotation_lr;
double	*rotation_ud;

double	*xl, *yl, *zl;
double	*xPos, *yPos, *zPos;

//////////////////////////////////// [GLUTGAME CAMERA FUNCTIONS] ////////////////////////////////////
// These are the function to control (translate, rotate) the camera) around the world.

/*
* Function: void glutGameInitCamera() --> glutGameCameraInit()
* -----------------------------
* Intialise the camera with the defaulth values.
* Inputs:
*	x : x location of the camera
* 	y : y location of the camera (GLUTGAME_PLAYER_HEIGHT is not included)
*	z : z location of the camera
* returns nothing
*/
void glutGameCameraInit(glutGameObjectplayer *player, double x, double y, double z)
{
	xPos = &(*player).base.x;
	yPos = &(*player).base.y;
	zPos = &(*player).base.z;
	xl = &(*player).xl;
	yl = &(*player).yl;
	zl = &(*player).zl;
	rotation_lr = &(*player).rotation_xz;
	rotation_ud = &(*player).rotation_y;

	(*xPos) = x; (*yPos) = y; (*zPos) = z;
	(*xl) = 0; (*yl) = 0; (*zl) = 0;
	(*rotation_lr) = 0;
	(*rotation_ud) = 0;
	glutGameRotateCamera(0,0);
}

/*
* Function: void glutGameRenderCamera() --> glutGameCameraRender()
* -----------------------------
* Renders the camera at a specific location with a specific rotation.
* returns nothing
*/
void glutGameCameraRender()
{
	gluLookAt((*xPos),(*yPos)+GLUTGAME_PLAYER_HEIGHT,(*zPos), (*xPos)+(*xl),(*yPos)+GLUTGAME_PLAYER_HEIGHT+(*yl),(*zPos)+(*zl), 0,1,0);
}

void glutGameCameraPlace(double x, double y, double z, double rotation_xz, double rotation_y)
{
	(*xPos) = x; (*yPos) = y; (*zPos) = z;
	(*rotation_lr) = rotation_xz;
	(*rotation_ud) = rotation_y;
}



void glutGameRotateCamera(double dxa, double dya)
{
	(*rotation_lr) += dxa;
	(*rotation_ud) -= dya;
	if((*rotation_ud) > 1.5) (*rotation_ud) = 1.5;
	else if((*rotation_ud) < -1.5) (*rotation_ud) = -1.5;
	(*xl) = sin((*rotation_lr)) * cos((*rotation_ud));
	(*zl) = -cos((*rotation_lr)) * cos((*rotation_ud));
	(*yl) = sin((*rotation_ud));
}

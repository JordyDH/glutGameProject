////////////////////////////////////////////////////////////////////
//
//	glutGameObjects by Jordy de Hoon
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

//////////////////////////////////// [LIB VARS] /////////////////////////////////////////////////////

//////////////////////////////////// [GLUTGAME OBJECT FUNCTIONS] ////////////////////////////////////

glutGameObjectobject *glutGameObjectsAlloc_object()
{
	return (glutGameObjectobject*)calloc(1,sizeof(glutGameObjectobject));
}

glutGameObjectplayer *glutGameObjectsAlloc_player()
{
	return (glutGameObjectobject*)calloc(1,sizeof(glutGameObjectplayer));
}

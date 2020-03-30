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
static glutGameObjectList *objectList = 0x00;
//////////////////////////////////// [GLUTGAME OBJECT FUNCTIONS] ////////////////////////////////////

glutGameObjectList *glutGameObjectsGetList()
{
	return objectList;
}

glutGameObjectobject *glutGameObjectsAlloc_object()
{
	glutGameObjectobject *p;
	p = (glutGameObjectobject*)calloc(1,sizeof(glutGameObjectobject));
	glutGameObjectsAddList(p,GLUTGAME_STRUCTID_OBJECT);
	return p;
}

glutGameObjectplayer *glutGameObjectsAlloc_player()
{
	glutGameObjectplayer *p;
	p = (glutGameObjectplayer*)calloc(1,sizeof(glutGameObjectplayer));
	glutGameObjectsAddList(p,GLUTGAME_STRUCTID_PLAYER);
	return p;
}

void glutGameObjectsAddList(void *element, uint8_t id)
{
	//If there are no elements in the list --> Add one empty element, first element
	if(objectList == 0)
		objectList = calloc(1,sizeof(glutGameObjectList));
	//Place a moving pointer at the start of the list
	glutGameObjectList *p;
	p  = objectList;
	//Search for the end of the list
	while((*p).next != 0x00)
		p = (*p).next;
	//End found
	(*p).struct_id = id;
	(*p).object = element;	//Load element in list.
	(*p).next = calloc(1,sizeof(glutGameObjectList));	//Allocate new space for a new entry (future)
}

//Structs for boundingboxes, objects and players.
#ifndef __GLUTGAME_OBJECTS_H__
#define __GLUTGAME_OBJECTS_H__
typedef struct {
	double xmin, ymin, zmin;	//First point of the bounding box
	double xmax, ymax, zmax;	//Seccond point of the boinding box
} boundingbox;

typedef struct {
	void (*callback)();		//Linked callback function
	uint64_t id;			//Id of the objects (handy for VBO's)
	double x, y, z;			//x y z translate of the object
	double rot_x, rot_y, rot_z;	//x y z rotation of the object
	boundingbox bb;			//bounding box
} glutGameObjectobject;

typedef struct {
	glutGameObjectobject base;	//Player is a base object
	double xl, yl, zl;		//Looking point of the player
	double rotation_xz;		//Head rotation (left/right) of the player
	double rotation_y;		//Head rotation (up/down) of the player
} glutGameObjectplayer;


glutGameObjectobject *glutGameObjectsAlloc_object();
glutGameObjectplayer *glutGameObjectsAlloc_player();

#endif


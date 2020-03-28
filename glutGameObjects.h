//Structs for boundingboxes, objects and players.
#ifndef __GLUTGAME_OBJECTS_H__
#define __GLUTGAME_OBJECTS_H__
typedef struct {
	double xmin, ymin, zmin;
	double xmax, ymax, zmax;
} boundingbox;

typedef struct {
	double x, y, z;
	double rot_x, rot_y, rot_z;
	boundingbox bb;
} glutGameObjectobject;

typedef struct {
	glutGameObjectobject base;
	double xl, yl, zl;
	double rotation_xz;
	double rotation_y;
} glutGameObjectplayer;
#endif


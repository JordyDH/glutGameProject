#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "glutGameLibs.h"
#include "InitJPG.h"

int togle = 0;
void kubus();
glutGameObjectobject *reff_obj;
uint64_t systick = 0;
uint16_t points = 300;

void myinit(void)
{
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

}

uint8_t toggle_physics = 0;
uint8_t toggle_sim = 0;
void cube(glutGameObjectobject *self)
{
	glLineWidth(1);
	glColor3f(1,1,1);
	glutSolidSphere((*self).state,10,10);
	glColor3f(0,0,1);
	glutWireSphere((*self).state,10,10);
	glLineWidth(3);
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f((*self).velocity.x,0,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,(*self).velocity.y,0);
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,(*self).velocity.z);
	glEnd();
}

void keyboard(unsigned int key)
{
	//printf("%c\n",key);
	if( key == 'x') toggle_physics = ~toggle_physics;
	if( key == 'X') toggle_sim = ~toggle_sim;
	if( key == 'p')
	{
		glutGameObjectobject *obj = glutGameObjectsAlloc_object();
		(*obj).x = 10;
		(*obj).state = 1.0;
		(*obj).callback = cube;
		(*obj).physics = 1;
		(*obj).velocity.x = 0.00;
		(*obj).velocity.y = 0.00;
		(*obj).velocity.z = 1.0;
		(*obj).mass = 100.0;
	}
	if( key == '+')
	{
		(*reff_obj).velocity.z += 1;
		printf("%lf \n",(*reff_obj).velocity.z);
	}
	if( key == '-')
	{
		(*reff_obj).velocity.z -= 1;
		printf("%lf \n",(*reff_obj).velocity.z);
	}
	if( key == '9')
	{
		(*reff_obj).velocity.z += 0.01;
		printf("%lf \n",(*reff_obj).velocity.z);
	}
	if( key == '6')
	{
		(*reff_obj).velocity.z -= 0.01;
		printf("%lf \n",(*reff_obj).velocity.z);
	}
	if( key == '8')
	{
		(*reff_obj).velocity.z += 0.001;
		printf("%lf \n",(*reff_obj).velocity.z);
	}
	if( key == '5')
	{
		(*reff_obj).velocity.z -= 0.001;
		printf("%lf \n",(*reff_obj).velocity.z);
	}
	if( key == '7')
	{
		(*reff_obj).velocity.z += 0.0001;
		printf("%lf \n",(*reff_obj).velocity.z);
	}
	if( key == '4')
	{
		(*reff_obj).velocity.z -= 0.0001;
		printf("%lf \n",(*reff_obj).velocity.z);
	}
	if( key == '1')
	{
		points++;
	}
	if( key == '2')
	{
		if(points>0)points--;
	}
}


//Physics function for space
double dist3(double x0, double y0, double z0, double x1, double y1, double z1)
{
	double a = sqrt(((x0-x1)*(x0-x1)) + ((y0-y1)*(y0-y1)));
	return sqrt((a*a) + ((z0-z1)*(z0-z1)));
}

void pseudo_physics()
{
	if(glutGameSystickGet() == systick)return;
	systick = glutGameSystickGet();
	if(toggle_physics==0x00) return;
	glutGameObjectList *object;
	glutGameObjectobject *p;
	//Update velocity of objects
	object = glutGameObjectsGetList();
	for(;object!=0;object = (*object).next)
	{
		if((*object).struct_id == GLUTGAME_STRUCTID_OBJECT)
		{
			p = (*object).object;
			//Calculate distance to center 0,0,0
			if((*p).physics)
			{
				(*p).mem0 += 0.001;
				(*p).x = (*p).mem1 * cos((*p).mem0);
				(*p).z = (*p).mem2 * sin((*p).mem0);
			}
		}

	}
}

void gravity(glutGameObjectobject *p0, glutGameObjectobject *p1)
{
	//Calculate the force between terrestrial objects
	double G = 0.00005;
	double r = dist3((*p0).x, (*p0).y, (*p0).z, (*p1).x, (*p1).y, (*p1).z);
	double force = G * ((*p0).mass * (*p1).mass ) / (r*r);
	double angle_xy = atan2((*p0).y - (*p1).y, (*p0).x - (*p1).x);
	double angle_z  = atan2((*p0).z - (*p1).z, (*p0).y - (*p1).y);
	//Append this force to the velocity vector
	double acc0 = force/(*p0).mass;
	double acc1 = force/(*p1).mass;
	(*p1).velocity.x += cos(angle_xy) * acc1;
	(*p0).velocity.x += (-1) * cos(angle_xy) * acc0;
	(*p1).velocity.y += sin(angle_xy) * acc1;
	(*p0).velocity.y += (-1) * sin(angle_xy) * acc0;
	(*p1).velocity.z += sin(angle_z) * acc1;
	(*p0).velocity.z += (-1) * sin(angle_z) * acc0;
}
void physics()
{
	if(glutGameSystickGet() == systick)return;
	systick = glutGameSystickGet();
	if(toggle_physics==0x00) return;
	glutGameObjectList *object;
	glutGameObjectobject *p;
	//Update velocity of objects
	object = glutGameObjectsGetList();
	for(;object!=0;object = (*object).next)
	{
		if((*object).struct_id == GLUTGAME_STRUCTID_OBJECT)
		for(glutGameObjectList *obj = (*object).next; obj!=0x00 ; obj = (*obj).next)
		{
			if((*obj).struct_id == GLUTGAME_STRUCTID_OBJECT)
			{
				gravity((*object).object,(*obj).object);
			}
		}


	}

	//Update object location with the velocity vector
	object = glutGameObjectsGetList();
	for(;object!=0;object = (*object).next)
	{
		if((*object).struct_id == GLUTGAME_STRUCTID_OBJECT)
		{
			p = (*object).object;
			if((*p).physics)
			{
				(*p).x += (*p).velocity.x * 0.01;
				(*p).y += (*p).velocity.y * 0.01;
				(*p).z += (*p).velocity.z * 0.01;
			}
		}
	}

}

void simPhysx(uint16_t steps, uint16_t skips, glutGameObjectobject *reff)
{
	if(toggle_sim == 0)return;
	glutGameObjectList *object;
	glutGameObjectobject *p;
	glutGameObjectobject obj[1000];
	uint16_t noObjects = 0;
	object = glutGameObjectsGetList();
	//Copy object list
	for(;object!=0;object = (*object).next)
	{
		if((*object).struct_id == GLUTGAME_STRUCTID_OBJECT)
		{
			p = (*object).object;
			memcpy(&obj[noObjects],p,sizeof(glutGameObjectobject));
			noObjects++;
		}
	}

	for(int k = 0; k < steps * skips; k++)
	{
	for(int i = 0; i < noObjects; i++)
	{
		//Draw 3D pixel of current location
		if((float)(k%skips) == 0)
		{
			glColor3f(1.0-(float)i/noObjects,(float)i/noObjects,0);
			glLineWidth(3);
			glBegin(GL_POINTS);
				glVertex3f(obj[i].x , obj[i].y, obj[i].z);
			glEnd();
		}
		//Calculate new velocity vectors
		for(int j = i+1; j < noObjects; j++)
		{
			gravity(&obj[i], &obj[j]);
		}
	}
	//Calculate new position with velocity vector
	for(int i = 0; i < noObjects; i++)
	{
		if(obj[i].physics == 0)continue;
		obj[i].x += obj[i].velocity.x * 0.01;
		obj[i].y += obj[i].velocity.y * 0.01;
		obj[i].z += obj[i].velocity.z * 0.01;
	}
	}
}

void world()
{
	glutGameRenderAllObjects();
	simPhysx(points,100,reff_obj);
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
	glutGameKeyboardSetFunc(keyboard);
	glutGameControlEnable();
	glutGameRenderSceneSet(world);

	glutGameObjectobject *obj = glutGameObjectsAlloc_object();
	(*obj).callback = cube;
	(*obj).state = 1.0;
	(*obj).velocity.x = 0.00;
	(*obj).velocity.y = 0.00;
	(*obj).velocity.z = 0.0;
	(*obj).mass = 1000;
//	glutGameObjectsAddList(obj,0);

	obj = glutGameObjectsAlloc_object();
	(*obj).callback = cube;
	(*obj).state = 1.0;
	(*obj).physics = 1;
	(*obj).velocity.x = 0.00;
	(*obj).velocity.y = 0.00;
	(*obj).velocity.z = 1.0;
	(*obj).mass = 1000;
	(*obj).z = 10;
	(*obj).x = 10;
	reff_obj = obj;
/*

	obj = glutGameObjectsAlloc_object();
	(*obj).callback = cube;
	(*obj).physics = 1;
	(*obj).x = 50.0;
	(*obj).state = 5.0;
	(*obj).velocity.x = 0.00;
	(*obj).velocity.y = 0.00;
	(*obj).velocity.z = -10.00;
	(*obj).mass = 100000.0;
	reff_obj = obj;
*/

	glutGameSetIdleFunc(physics);
	glutGameMainLoop();

}

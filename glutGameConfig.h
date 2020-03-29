#ifndef __GLUTGAME_CONFIG_H__
#define __GLUTGAME_CONFIG_H__
#define GLUTGAME_VERSION "dev.0.2"
//#define  GLUTGAME_DEBUG_INFO
//////////////////////////////////// CONTROLS ////////////////////////////////////
#define GLUTGAME_CONTROL_FORW	'z'	//Moves the camera forwards	--Bit 0 in control reg
#define GLUTGAME_CONTROL_BACK	's'	//Moves the camera backwards	--Bit 1 in control reg
#define GLUTGAME_CONTROL_LEFT	'q'	//Moves the camera left		--Bit 2 in control reg
#define GLUTGAME_CONTROL_RIGHT	'd'	//Moves the camera right	--Bit 3 in control reg
#define GLUTGAME_CONTROL_UP	'a'	//Moves the camera up		--Bit 4 in control reg
#define GLUTGAME_CONTROL_DOWN	'e'	//Moves the camera down		--Bit 5 in control reg
#define GLUTGAME_CONTROL_AXIS	'i'	//Renders the axis		--Bit 6 in control reg
#define GLUTGAME_CONTROL_USEREG
#define GLUTGAME_CONTROL_TIMER	1
//////////////////////////////////// PLAYER MODEL ////////////////////////////////////
#define GLUTGAME_PLAYER_HEIGHT		1.0	//Default player height, possition of the camera
#define GLUTGAME_PLAYER_BASESPEED	0.075	//Default step size
#define GLUTGAME_PLAYER_NEARSIGHT	0.01
#define GLUTGAME_PLAYER_FARSIGHT	100

//////////////////////////////////// RENDER SETTINGS ////////////////////////////////////
#define GLUTGAME_RENDER_FAST			//Renders the scene as fast a possible.
//#define GLUTGAME_RENDER_DUBBELBUFFER		//Enable dubbel buffering for render.
#define GLUTGAME_SYSTICK_INTERVAL	10
#endif

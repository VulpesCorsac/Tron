#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "main.h"
#include "initConstants.hpp"
#include "mesh.h"
#include "gui.h"

/*
	class handling window creation, menu and game rendering, and providing functions to handle keyboard input
	(will handle mouse too, probably)
*/

class CGEngine
{
private:
	int resX, resY;

	void go2D();
public:
	CGUI* gui;
	Init_Constants* ic;

	void cycle();
	void draw();
	void start();
	CGEngine(Init_Constants* aic);
};

#endif // RENDER_H_INCLUDED

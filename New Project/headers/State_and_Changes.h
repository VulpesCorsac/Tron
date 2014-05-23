#ifndef STATE_AND_CHANGES_H_INCLUDED
#define STATE_AND_CHANGES_H_INCLUDED

#include "stdafx.h"
#include "Server.h"

struct State {
	int Players_Ammount;
	double *x; // Player x coordinate
	double *y; // Player y coordinate
	double *dx; // Player direction x coordinate
	double *dy; // Player direction y coordinate
};

struct Changes {
	char *Is_dead;
	int New_Walls;
};

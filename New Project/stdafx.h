// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED

#define FREEGLUT_STATIC

#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <assert.h>

//#define GLEW_STATIC wtf it doesn't work but k

#include <glew.h>
#include <glm/glm.hpp>

#include <windows.h>
#include <gl\gl.h>

#include "glext.h"

#include "glut.h"
#include "freeglut_ext.h"

using namespace std;

#include "GeoGeometry\GeoGeometry.hpp"
#include "headers\InitConstants.h"
#include "headers\LightCycle.h"
#include "headers\Wall.h"
#include "headers\Rocket.h"
#include "headers\Player.h"
#include "headers\Bomb.h"
#include "headers\Game.h"
#include "headers\Game_Engine.h"

#define fori(i, n) for (int i = 0; i < n; i++)
#define forvec(vType, vName, i) for (vector<vType>::iterator i = vName.begin(); i != vName.end(); i++)

#endif // STDAFX_H_INCLUDED

//disables deprecation warning
#pragma warning( disable : 4996 )

// TODO: reference additional headers your program requires here

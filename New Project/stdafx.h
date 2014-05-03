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

#define fori(i, n) for (int i = 0; i < n; i++)
#define forvec(vType, vName, i) for (vector<vType>::iterator i = vName.begin(); i != vName.end(); i++)

#endif // STDAFX_H_INCLUDED


// TODO: reference additional headers your program requires here

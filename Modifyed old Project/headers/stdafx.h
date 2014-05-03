#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED

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

#include <windows.h>
#include <gl\gl.h>

#include "glext.h"

#include "glut\glut.h"
#include "glut\freeglut_ext.h"

using namespace std;

#define fori(i, n) for (int i = 0; i < n; i++)
#define forvec(vType, vName, i) for (vector<vType>::iterator i = vName.begin(); i != vName.end(); i++)

#endif // STDAFX_H_INCLUDED

#pragma once

#include "Headers\main.h"

#define GLDB_VERTEX 0
#define GLDB_UV 1
#define GLDB_INDEX 2
#define GLDB_NORMALS 3
#define GLDB_COLOR 4

#define GLDB_COUNT 5

struct CDrawBuffers
{
	GLuint bufs[5];
	void updBuff(int id, int sz, const void* data);
	void allocBuff(int id, int sz, const void* data, GLuint memType = GL_STATIC_DRAW);
	void relBuffers();
	CDrawBuffers();
	~CDrawBuffers();
};

class CGEngine;

class CGLTexture
{
private:
public:
	GLuint texInd;
	Point sz;
	bool load(const char* path);
	void select(CGEngine* ge);
	CGLTexture();
	~CGLTexture();
};

struct CSprite
{
	CGLTexture* tex;
	Point f, t;
	CDrawBuffers sprBuf;

	//render must be in 2D mode to work properly
	void render(CGEngine* ge, Point lt, bool centered = false);
};
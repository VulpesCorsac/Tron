#pragma once

#include "Headers\main.h"

class CGLTexture
{
private:
	GLuint texInd;
public:
	Point sz;
	bool load(const char* path);
	void select();
	CGLTexture();
	~CGLTexture();
};

struct CSprite
{
	CGLTexture* tex;
	Point f, t;

	//render must be in 2D mode to work properly
	void render(Point lt, bool centered = false);
};
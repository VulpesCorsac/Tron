
#pragma once

#include "graph2D.h"

class CMesh
{
private:
	GLuint vBuff, uvBuff, iBuff, nBuff;
	CGLTexture* bTex;
public:

	void setTexture(CGLTexture * tex);
	bool loadFrom(const char* src);
	CMesh();
	~CMesh();
};

#pragma once

#include "graph2D.h"

class CMesh
{
private:
	CDrawBuffers bf;
	CGLTexture* bTex;
public:

	void setTexture(CGLTexture * tex);
	bool loadFrom(const char* src);
	CMesh();
	~CMesh();
};
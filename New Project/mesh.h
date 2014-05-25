
#pragma once

#include "graph2D.h"

class CGEngine;

struct renQuad
{
	glm::vec3 v[4], n[4];
	glm::vec2 uv[4];
	void defaultUV(float tx = 1.0f, float ty = 1.0f);
	void defaultUV(glm::vec2 t1, glm::vec2 t2);
	void setNormal(glm::vec3 a);
	void autoNormal();
	void autoNormalSmooth();
};

class CMesh
{
private:
	CDrawBuffers bf;
	CGLTexture* bTex;
	int bufQ_size, qSize, bufI_size;
	vector<glm::vec3> q_v, q_n;
	vector<glm::vec2> q_uv;
	vector<unsigned short> q_i;
public:
	void appendQuad(renQuad& q);
	void toBuffer(bool isDyn = false, bool clrTemp = true);
	void draw(CGEngine* gEng);
	void setTexture(CGLTexture * tex);
	bool loadFrom(const char* src);
	CMesh();
	~CMesh();
};
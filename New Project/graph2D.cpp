#include "stdafx.h"
#include "headers\gengine.h"
#include "SOIL\soil.h"

bool CGLTexture::load(const char* path)
{
	//using SOIL
	printf("Loading texture : %s ..", path);
	int w, h, ch;
	UCHAR* img = SOIL_load_image(path, &w, &h, &ch, SOIL_LOAD_AUTO);
	if (!img)
	{
		assert(false);
		return false;
	}
	sz.x = (type) w;
	sz.y = (type) h;

	texInd = SOIL_create_OGL_texture(img, w, h, ch, 0, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT);
	delete img;
	if (!texInd)
	{
		assert(false);
		return false;
	};
	printf("done\n");
	return true;
}

void CGLTexture::select(CGEngine* ge)
{
	assert(texInd);
	ge->selTexture(texInd);
}

CGLTexture::CGLTexture()
{
	texInd = 0;
}

CGLTexture::~CGLTexture()
{
	if (texInd)
		glDeleteTextures(1, &texInd);
}

void CSprite::render(CGEngine* ge, Point lt, bool centered)
{
	tex->select(ge);
	/*
	Point t1(f.x / tex->sz.x, f.y / tex->sz.y);
	Point t2(t.x / tex->sz.x, t.y / tex->sz.y);
	*/
	if (centered)
	{
		lt -= (t - f) * 0.5;
	}
	Point tt = lt + (t - f);

	ge->setBuffs(sprBuf);
	ge->renderTrans2D(2, lt, tt);

	//deprecated method but ok for now
	/*
	glBegin(GL_QUADS);
	glTexCoord2f(t1.x, t1.y);
	glVertex3f(lt.x, lt.y, 0.0);
	glTexCoord2f(t2.x, t1.y);
	glVertex3f(tt.x, lt.y, 0.0);
	glTexCoord2f(t2.x, t2.y);
	glVertex3f(tt.x, tt.y, 0.0);
	glTexCoord2f(t1.x, t2.y);
	glVertex3f(lt.x, tt.y, 0.0);
	glEnd();*/
}
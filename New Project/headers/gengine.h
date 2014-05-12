#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "main.h"
#include "InitConstants.h"
#include "mesh.h"
#include "gui.h"

/*
	class handling window creation, menu and game rendering, and providing functions to handle keyboard input
	(will handle mouse too, probably)
*/


class CGEngine
{
private:
	const int shdm_tex = 0,  shdm_fnt = 1;

	int resX, resY;

	CDrawBuffers sBufs;	//buffers for sprite rendering

	GLuint drawProg1, drawProgFnt, drawProg3D;

	GLuint unv_2DTRM, unv_2Dtex, unv_3DTRM;	// transformation matrix for 2D/3D shaders
	GLuint unv_2DF_clr;

	CGLTexture* menuTex;
	CSprite* testSpr;

	glm::mat4 TRM_2d;

	int shdMode_2D;	//current 2D shading mode

	void go2D();
	void initRender();
	void load();
public:
	CGUI* gui;
	Init_Constants* ic;

	void setRasterTrg(Point p);
	void renderTrans2D(int ne, Point lt, Point rb);
	CSprite* makeSprite(CGLTexture* tex, Point lt, Point rb);
	void setBuffs(CDrawBuffers& bf);
	void drawQuad(Point f, Point t, Point ft, Point tt);

	void selTexture(GLuint tx);
	void selColor(const glm::vec4 &clr);




	void cycle();
	void draw();
	void start();
	CGEngine(Init_Constants* aic);
};

#endif // RENDER_H_INCLUDED

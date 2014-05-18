#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "main.h"
#include "InitConstants.h"
#include "mesh.h"
#include "gui.h"

#include "Server.h"
#include "Client.h"


/*
	class handling window creation, menu and game rendering, and providing functions to handle keyboard input
	(will handle mouse too, probably)
*/


class CGEngine
{
private:
	const int shdm_tex = 0,  shdm_fnt = 1;

	int resX, resY;
	bool isExit;
	volatile bool isServerExit;	//signal variable , main >> server
	volatile bool serverKill;	//signal variable , server >> main

	CDrawBuffers sBufs;	//buffers for sprite rendering

	GLuint drawProg1, drawProgFnt, drawProg3D;

	GLuint unv_2DTRM, unv_2Dtex, unv_3DTRM;	// transformation matrix for 2D/3D shaders
	GLuint unv_2Dclr, unv_2DF_clr;

	CGLTexture* menuTex;
	CSprite* testSpr;

	glm::mat4 TRM_2d;
	glm::vec4 cColorMod;


	HANDLE hTh_Server;	//server's thread handle and threadiid
	DWORD hThId_Server;


	int mState;

	int shdMode_2D;	//current 2D shading mode

	void go2D();
	void initRender();
	void load();
public:
	Point mPos;
	CGUI* gui;
	Init_Constants* ic;

	CServer* cServer;
	CClient* cClient;

	void doExit();
	void setRasterTrg(Point p);
	void renderTrans2D(int ne, Point lt, Point rb);
	CSprite* makeSprite(CGLTexture* tex, Point lt, Point rb);
	void setBuffs(CDrawBuffers& bf);
	void drawQuad(Point f, Point t, Point ft, Point tt);

	void selTexture(GLuint tx);
	void selFontColor(const glm::vec4 &clr);
	void setColorMod(const glm::vec4 &clr);

	bool goHosting();
	bool goJoining(const char* ip);
	void shutdownServer();

	void onKey(unsigned char key);

	bool isKeyPressed(int vkey);
	bool isKeyJustPressed(int vkey);


	void svth_Entry();	//entry point for server thread

	void cycle();
	void draw();
	void start();
	CGEngine(Init_Constants* aic);
};

#endif // RENDER_H_INCLUDED

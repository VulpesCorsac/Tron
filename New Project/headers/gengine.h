#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "main.h"
#include "InitConstants.h"
#include "mesh.h"
#include "gui.h"

#include "Server.h"
#include "Client.h"

#include "Game.h"

/*
	class handling window creation, menu and game rendering, and providing functions to handle keyboard input
	(will handle mouse too, probably)
*/
struct CCurScene;
class CWallRender;

class CGEngine
{
private:

	__int64 lpTime, dtTime;

	int lKeys[256];
	void updKeyboard();

	const int shdm_tex = 0,  shdm_fnt = 1;

	int resX, resY;
	bool isExit;
	volatile bool isServerExit;	//signal variable , main >> server
	volatile bool serverKill;	//signal variable , server >> main

	CDrawBuffers sBufs;	//buffers for sprite rendering

	GLuint drawProg1, drawProgFnt, drawProg3D, drawProg3DL;

	GLuint unv_2DTRM, unv_2Dtex, unv_3DTRM, unv_3DLTRM, unv_3DLM, unv_2DFTRM;	// transformation matrix for 2D/3D shaders
	GLuint unv_2Dclr, unv_2DF_clr;
	GLuint unv_3Dtex, unv_3Dclr, unv_3DLtex, unv_3DLclr;
	GLuint unv_3DL_refl;

	GLuint VertexArrayID;

	CSprite* testSpr;

	int lPlayer;

	glm::mat4 TRM_2d, TRM_3d;
	glm::vec4 cColorMod;


	HANDLE hTh_Server;	//server's thread handle and threadiid
	DWORD hThId_Server;


	int mState;

	int shdMode_2D;	//current 2D shading mode
	bool is3D;

	void go2D();
	void go3D();
	void initRender();
	void load();

	//scene rendering stuff

	vector<float> pAngs;

	glm::mat4 projMat, camMat, pcMat, wrldMat, pcwMat;

	glm::vec3 cam_Pos, cam_Trg, cam_Up;
	glm::vec3 cam_Pos_t, cam_Trg_t;	//target state

	CGLTexture* menuTex, *gridTex, *gridTex2, *whiteTex, *wallTex;
	CMesh* gridMesh, *motoMesh, *gridMesh2;

	//size (x,z) ; spacing and line width
	void updCamera();
	void updMatrices();

	//
	void buildScene(Game* gm, CCurScene& cs);
	//more specific drawscene.
	void drawScene(CCurScene& cs, glm::mat4 &tr);

	CWallRender* wRender;

	CMesh* generateGridMesh(int nx, int ny, float sp, float w);
	CMesh* generateGridMesh2(int nx, int ny, float sp);
public:
	Game* rGame;

	Point mPos;
	CGUI* gui;
	Init_Constants* ic;

	CServer* cServer;
	CClient* cClient;

	GLuint cTex;

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

	void drawScene(Game* gm);
	void prepForScene(Game* gm);

	void setGame(Game* gm);

	void svth_Entry();	//entry point for server thread

	void cycle();
	void draw();
	void start();
	CGEngine(Init_Constants* aic);
};

#endif // RENDER_H_INCLUDED

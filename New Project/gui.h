#pragma once

#include "graph2D.h"

//2D gui
// used by CGEngine

class CGEngine;
class CGUI;

#define GSCR_MENU 1
#define GSCR_HOSTING 2
#define GSCR_IP 3
#define GSCR_LOBBY 4
#define GSCR_GAME 5

class CGUIElement
{
private:
	Point pp, sz, fsz;
	const char* ctxt;
	CSprite* rSpr;
	CGUI* gui;
	bool isClicked;
	bool isHl;
public:

	glm::vec4 fntColor;
	void render(CGEngine * eng);
	bool getClick();
	void setText(const char* txt);
	void click(Point p);
	void think(CGEngine * eng);
	CGUIElement(CGUI* agui, const Point &pos, CSprite* spr);
};

class CGUI
{
private:
	int cScr;
	vector<CGUIElement*> els;

	CGUIElement* b_Host, *b_Client, *b_Exit, *b_Layout, *b_IP, *b_Connect, *b_Info, *b_Players, *b_Info2, *b_Info3;
	CGUIElement* b_HInfo1, *b_HInfo2;

	char cIp[64], cBuff[128], cBuff2[128], cBuff3[128], cBuff4[128];

	CGLTexture* menuTex;
	void clearScreen();
public:
	CGEngine* gEng;
	int rX, rY;
	Point cMousePos;
	void addElement(CGUIElement* e);

	void enterScreen(int id);
	void init();

	void keyPress(unsigned char key);
	void think(Point mPos, int mState);
	void render();

	CGUI(CGEngine* ge, int resX, int resY);
};
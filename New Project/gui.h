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
public:

	void render(CGEngine * eng);

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

	CGUIElement* b_Host, *b_Client, *b_Exit, *b_Layout;

	CGLTexture* menuTex;
	void clearScreen();
public:
	CGEngine* gEng;
	void addElement(CGUIElement* e);

	void enterScreen(int id);
	void init();

	void think();
	void render();

	CGUI(CGEngine* ge);
};
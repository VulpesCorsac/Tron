#include "stdafx.h"
#include "headers\gengine.h"

void CGUI::clearScreen()
{
	forvec(CGUIElement*, els, i) delete *i;
	els.clear();
}

void CGUI::addElement(CGUIElement* e)
{
	els.push_back(e);
}

void CGUI::enterScreen(int id)
{
	if (id == cScr) return;
	clearScreen();

	if (id == GSCR_MENU)
	{
		b_Host = new CGUIElement(this, Point(300, 200), gEng->makeSprite(menuTex, Point(20, 30), Point(20+65, 30+24)));
		b_Client = new CGUIElement(this, Point(300, 300), gEng->makeSprite(menuTex, Point(20, 30), Point(20 + 65, 30 + 24)));
		b_Host->setText("Host");
		b_Client->setText("Join");

	}
	cScr = id;
}

void CGUI::init()
{
	menuTex = new CGLTexture();
	menuTex->load("menuTex.png");


}

void CGUI::think()
{
	forvec(CGUIElement*, els, i)
	{
		(*i)->think(gEng);
	}
}

void CGUI::render()
{
	forvec(CGUIElement*, els, i)
	{
		(*i)->render(gEng);
	}
}

CGUI::CGUI(CGEngine* ge)
{
	gEng = ge;
	cScr = 0;
}
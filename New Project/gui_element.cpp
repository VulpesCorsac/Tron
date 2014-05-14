#include "stdafx.h"
#include "headers\gengine.h"


void CGUIElement::setText(const char* txt)
{
	ctxt = txt;
	fsz.y = -0.5f * glutBitmapHeight(GLUT_BITMAP_9_BY_15);
	fsz.x = glutBitmapLength(GLUT_BITMAP_9_BY_15, (unsigned const char*) txt);
}

void CGUIElement::click(Point p)
{
	p -= pp;

}

void CGUIElement::think(CGEngine * eng)
{

}

CGUIElement::CGUIElement(CGUI* agui, const Point &pos, CSprite* spr)
{
	ctxt = NULL;
	pp = pos;
	rSpr = spr;
	if (rSpr)
	{
		sz = rSpr->t - rSpr->f;
	}
	else {
		sz = Point(0, 0);
	}
	gui = agui;
	gui->addElement(this);
}

void CGUIElement::render(CGEngine * eng)
{
	if (ctxt);
	{
		gui->gEng->setRasterTrg(pp - fsz * 0.5f);
		gui->gEng->selColor(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
		glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)ctxt);
	}
	if (rSpr)
	{
		rSpr->render(eng, pp, true);
	}
}
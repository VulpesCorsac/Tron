#include "stdafx.h"
#include "headers\gengine.h"


void CGUIElement::setText(const char* txt)
{
	ctxt = txt;
	fsz.y = -0.5f * glutBitmapHeight(GLUT_BITMAP_9_BY_15);
	fsz.x = (type) glutBitmapLength(GLUT_BITMAP_9_BY_15, (unsigned const char*) txt);
}

bool CGUIElement::getClick()
{
	if (isClicked)
	{
		isClicked = false;
		return true;
	}
	else {
		return false;
	}
}

void CGUIElement::click(Point p)
{
	p -= pp - sz * 0.5f;
	if (p.x < 0 || p.y < 0) return;
	if (p.x > sz.x || p.y > sz.y) return;
	isClicked = true;
}

void CGUIElement::think(CGEngine * eng)
{
	Point p = (gui->cMousePos - (pp  - sz * 0.5f));
	isHl = (p.x < sz.x) && (p.y < sz.y) && (p.x > 0) && (p.y > 0);
//	if (isHl) printf("HH");
}

CGUIElement::CGUIElement(CGUI* agui, const Point &pos, CSprite* spr)
{
	ctxt = NULL;
	pp = pos;
	rSpr = spr;
	isClicked = false;
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
	if (ctxt)
	{
		gui->gEng->setRasterTrg(pp - fsz * 0.5f);
		gui->gEng->selFontColor(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
		glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)ctxt);
	}
	if (rSpr)
	{
	//	printf("HH\n");
		if (isHl)
		{
	//		printf("JJ\n");
			gui->gEng->setColorMod(glm::vec4(1.4, 1.4, 1.0, 1.0));
		}
		rSpr->render(eng, pp, true);
		if (isHl)
			gui->gEng->setColorMod(glm::vec4(1.0, 1.0, 1.0, 1.0));
	}
}
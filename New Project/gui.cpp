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
		b_Host = new CGUIElement(this, Point(rX / 2.0f, rY * 0.2f), gEng->makeSprite(menuTex, Point(20, 30), Point(20+65, 30+24)));
		b_Client = new CGUIElement(this, Point(rX / 2.0f, rY * 0.3f), gEng->makeSprite(menuTex, Point(20, 30), Point(20 + 65, 30 + 24)));
		b_Exit = new CGUIElement(this, Point(rX / 2.0f, rY * 0.4f), gEng->makeSprite(menuTex, Point(20, 30), Point(20 + 65, 30 + 24)));
		b_Host->setText("Host");
		b_Client->setText("Join");
		b_Exit->setText("Quit");
	}
	else if (id == GSCR_IP)
	{
		CGUIElement* el = new CGUIElement(this, Point(rX / 2.0f, rY * 0.3f), NULL);
		el->setText("Enter server IP : ");

		b_IP = new CGUIElement(this, Point(rX / 2.0f, rY * 0.5f), NULL);
		b_IP->setText("127.0.0.1");
		strcpy_s(cIp, "127.0.0.1");

		b_Info = new CGUIElement(this, Point(rX / 2.0f, rY * 0.4f), NULL);
		b_Info->setText("  ");

		b_Connect = new CGUIElement(this, Point(rX / 2.0f, rY * 0.7f), gEng->makeSprite(menuTex, Point(20, 30), Point(20 + 65, 30 + 24)));
		b_Connect->setText("Connect");
		b_Exit = new CGUIElement(this, Point(rX / 2.0f, rY * 0.8f), gEng->makeSprite(menuTex, Point(20, 30), Point(20 + 65, 30 + 24)));
		b_Exit->setText("Back");
	}
	else if (id == GSCR_HOSTING)
	{
		CGUIElement* el = new CGUIElement(this, Point(rX / 2.0f, rY * 0.2f), NULL);
		el->setText("Waiting for players ... ");

		b_Players = new CGUIElement(this, Point(rX / 2.0f, rY * 0.4f), NULL);
		b_Players->setText("Connected : 0/12");

		b_Connect = new CGUIElement(this, Point(rX / 2.0f, rY * 0.7f), gEng->makeSprite(menuTex, Point(20, 30), Point(20 + 65, 30 + 24)));
		b_Connect->setText("Start");
		b_Exit = new CGUIElement(this, Point(rX / 2.0f, rY * 0.8f), gEng->makeSprite(menuTex, Point(20, 30), Point(20 + 65, 30 + 24)));
		b_Exit->setText("Close");
	}
	cScr = id;
}

void CGUI::init()
{
	menuTex = new CGLTexture();
	menuTex->load("menuTex.png");
}

void CGUI::keyPress(unsigned char key)
{
	if (cScr == GSCR_IP)
	{
		if ((key >= '0' && key <= '9') || (key == '.'))
		{
			b_Info->setText(" ");

			int l = strlen(cIp);
			if (l < 32)
			{
				cIp[l] = key;
				cIp[l+1] = 0;
				b_IP->setText(cIp);
			}
		}
		else if (key == VK_BACK)
		{
			int l = strlen(cIp);
			if (l > 0)
			{
				cIp[l - 1] = 0;
				b_IP->setText(cIp);
			}
		}
	}
}

void CGUI::think(Point mPos, int mState)
{
	cMousePos = mPos;
	forvec(CGUIElement*, els, i)
	{
		(*i)->think(gEng);
	}
	if (mState & 1)
	{
		forvec(CGUIElement*, els, i)
			(*i)->click(mPos);
	}

	if (cScr == GSCR_MENU)
	{
		if (b_Exit->getClick())
		{
			gEng->doExit();
		}
		else if (b_Client->getClick())
		{
			enterScreen(GSCR_IP);
		}
		else if (b_Host->getClick())
		{
			if (gEng->goHosting())
			{
				enterScreen(GSCR_HOSTING);
			}
		}
	}
	else if (cScr == GSCR_IP)
	{
		if (b_Connect->getClick() || gEng->isKeyPressed(VK_RETURN))
		{
			if (gEng->goJoining(cIp))
			{
				enterScreen(GSCR_LOBBY);
			}
			else {
				b_Info->setText("Connection failed");
			}
		}
		else if (b_Exit->getClick())
		{
			enterScreen(GSCR_MENU);
		}
	}
	else if (cScr == GSCR_HOSTING)
	{
		int np = gEng->cServer->getPlCount();
		sprintf_s(cBuff, "Connected : %d/12", np);
		b_Players->setText(cBuff);

		if (b_Exit->getClick())
		{
			gEng->shutdownServer();
			enterScreen(GSCR_MENU);
		}
		else if (b_Connect->getClick())
		{
			if (gEng->cServer->startgame())
			{
				enterScreen(GSCR_GAME);
			}
		}
	}
}

void CGUI::render()
{
	forvec(CGUIElement*, els, i)
	{
		(*i)->render(gEng);
	}
}

CGUI::CGUI(CGEngine* ge, int resX, int resY)
{
	gEng = ge;
	cScr = 0;
	rX = resX;
	rY = resY;
	cIp[0] = 0;
}
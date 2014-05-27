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
	else if (id == GSCR_GAME)
	{
		b_Info = new CGUIElement(this, Point(rX / 2.0f, rY * 0.04f), NULL);
		b_Info->setText("Game In Progress");
		b_Info->fntColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

		b_Info2 = new CGUIElement(this, Point(rX / 2.0f, rY * 0.08f), NULL);
		b_Info2->setText("");
		b_Info2->fntColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

		b_Info3 = new CGUIElement(this, Point(rX / 2.0f, rY * 0.12f), NULL);
		b_Info3->setText("");
		b_Info3->fntColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

		b_HInfo1 = new CGUIElement(this, Point(rX / 4.0f, rY * 0.04f), NULL);
		b_HInfo1->setText("");
		b_HInfo1->fntColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

		b_HInfo2 = new CGUIElement(this, Point(rX / 4.0f, rY * 0.08f), NULL);
		b_HInfo2->setText("");
		b_HInfo2->fntColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

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
		else if (b_Connect->getClick())	//start game
		{
			if (gEng->cServer->startgame())
			{
				enterScreen(GSCR_GAME);

				/*

				gEng->rGame = new Game();

				Player pl;
				pl.MyCycle.Current_Point = Point2D<double>(0.5, 0.5);
				pl.MyCycle.Direction = Point2D<double>(1, 0);

				gEng->rGame->Players.push_back(pl);

				gEng->setGame(gEng->rGame);*/
			}
		}
	}
	else if (cScr == GSCR_GAME)
	{
		if (gEng->rGame)
		{
			int npl = (int) gEng->rGame->Players.size();
			int alpl = 0;
			forvec(Player, gEng->rGame->Players, i)
			{
				if (i->Alive) alpl++;
			}

			sprintf_s(cBuff, "Game Active : %d/%d", alpl, npl);
			if (gEng->cClient && gEng->cClient->gameFinish) sprintf_s(cBuff, "Restarting...");
			b_Info->setText(cBuff);


			if (gEng->isLAlive)
			{
				b_Info2->setText("");
			}
			else if (gEng->cClient && gEng->cClient->gameFinish)
			{
				if (gEng->cClient->gResult >= 0 && gEng->rGame)
				{
					sprintf_s(cBuff2, "Team %d won!", gEng->cClient->gResult + 1);
				}
				else {
					sprintf_s(cBuff2, "Tie");
				}
				b_Info2->setText(cBuff2);
			} else
			{
				sprintf_s(cBuff2, "Spectating player %d", gEng->cSpecPlayer+1);
				b_Info2->setText(cBuff2);
			}

			if (gEng->cClient)
			{
				sprintf_s(cBuff3, "loss recv : %d/%d, skips : %d", gEng->cClient->nPacketLossRcv,
					gEng->cClient->nPacketShuffle, gEng->cClient->nLags);
				b_HInfo1->setText(cBuff3);
				sprintf_s(cBuff4, "frm srv : %d, cl %d", gEng->cClient->lSrvFrame, gEng->cClient->cClFrame);
				b_HInfo2->setText(cBuff4);
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
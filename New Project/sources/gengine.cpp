#include "stdafx.h"
#include "headers\gengine.h"

/*
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;*/


CGEngine* g_render;

void r_mouseMove(int x, int y)
{
	g_render->mPos = Point((type)x, (type)y);
}

void r_display(void) {
	g_render->draw();
}

void r_cycle()
{
	g_render->cycle();
}

void r_keyb(unsigned char key, int x, int y)
{
	g_render->onKey(key);
}

// ------------------------------------- various ----------------------------------------------

const int buf_szm[5] = { sizeof(float)* 3, sizeof(float)* 2, sizeof(unsigned short), sizeof(float)* 3, sizeof(float)* 4 };

void CDrawBuffers::updBuff(int id, int sz, const void* data)
{
	assert(id >= 0 && id < GLDB_COUNT);
	GLenum trg = id == GLDB_INDEX ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;
	glBindBuffer(trg, bufs[id]);
	if (sz)
		glBufferData(trg, sz * buf_szm[id], data, GL_DYNAMIC_DRAW);
}

void CDrawBuffers::allocBuff(int id, int sz,const void* data, GLuint memType)
{
	//glBindVertexArray(0);
	assert(id >= 0 && id < GLDB_COUNT);
	glGenBuffers(1, bufs + id);
	GLenum trg = id == GLDB_INDEX ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;
	glBindBuffer(trg, bufs[id]);
	if (sz)
	{
		glBufferData(trg, sz * buf_szm[id], data, memType);
	}
}

CDrawBuffers::CDrawBuffers()
{
	fori(i, GLDB_COUNT) bufs[i] = 0;
}

void CDrawBuffers::relBuffers()
{
	glDeleteBuffers(GLDB_COUNT, bufs);
	fori(i, GLDB_COUNT) bufs[i] = 0;
}

CDrawBuffers::~CDrawBuffers()
{
	glDeleteBuffers(GLDB_COUNT, bufs);
}

// ------------------------------------ shaders loading -------------------------------------------

string readShaderCode(const char* path)
{
	ifstream sStream(path, ios::in);
	string code;
	if (sStream.is_open())
	{
		std::string Line = "";
		while (getline(sStream, Line))
			code += "\n" + Line;
		sStream.close();
	}
	else {
		assert(false);	//shader file not found
	}
	return code;
}

GLuint compileShader(const char * path, GLuint shType)
{
	string shCode = readShaderCode(path);
	GLuint sh = glCreateShader(shType);

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", path);
	char const * shPointer = shCode.c_str();
	glShaderSource(sh, 1, &shPointer, NULL);
	glCompileShader(sh);

	// Check Vertex Shader
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(sh, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> errMsg(InfoLogLength);
	if (InfoLogLength > 0)
		glGetShaderInfoLog(sh, InfoLogLength, NULL, &errMsg[0]);
	else
		errMsg.push_back(0);
	printf("%s\n", &errMsg[0]);

	return sh;
}

GLuint linkProgram(GLuint shd1, GLuint shd2 = 0, GLuint shd3 = 0)
{
	GLuint prog = glCreateProgram();
	glAttachShader(prog, shd1);
	if (shd2) glAttachShader(prog, shd2);
	if (shd3) glAttachShader(prog, shd3);
	glLinkProgram(prog);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(prog, GL_LINK_STATUS, &Result);
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> errMsg(max(InfoLogLength, int(1)));
	glGetProgramInfoLog(prog, InfoLogLength, NULL, &errMsg[0]);
	printf("%s", &errMsg[0]);

	return prog;
}

// ----------------------------------- CGEngine --------------------------------------------

void CGEngine::load()
{
	menuTex = new CGLTexture();
	menuTex->load("menuTex.png");

	gridTex = new CGLTexture();
	gridTex->load("gridTex.png");

	gridTex2 = new CGLTexture();
	gridTex2->load("gridTex2.png");

	whiteTex = new CGLTexture();
	whiteTex->load("whiteTex.png");

	wallTex = new CGLTexture();
	wallTex->load("wallTex.png");

	bombTex = new CGLTexture();
	bombTex->load("bombTex.png");

	rockTex = new CGLTexture();
	rockTex->load("rocketTex.png");

	testSpr = makeSprite(menuTex, Point(20, 30), Point(20+25, 30+24));

	gridMesh = generateGridMesh(400, 400, 1.0f, 0.05f);
	gridMesh2 = generateGridMesh2(400, 400, 1.0f);

	motoMesh = new CMesh();
	motoMesh->loadFrom("models\\cycle.objm");
	motoMesh->setTexture(whiteTex);
}

void CGEngine::initRender()
{
	printf( "Initializating render\n");

	printf("Loading shaders\n");
	GLuint vShader, fShader, fShaderF, vShader3D, fShader3D, vShader3DL, fShader3DL;
	vShader = compileShader("shaders\\vertex.sh", GL_VERTEX_SHADER);
	fShader = compileShader("shaders\\fragment.sh", GL_FRAGMENT_SHADER);
	fShaderF = compileShader("shaders\\fragment_font.sh", GL_FRAGMENT_SHADER);


	vShader3D = compileShader("shaders\\vertex_3D.sh", GL_VERTEX_SHADER);
	fShader3D = compileShader("shaders\\fragment_3D.sh", GL_FRAGMENT_SHADER);
	vShader3DL = compileShader("shaders\\vertex_3DL.sh", GL_VERTEX_SHADER);
	fShader3DL = compileShader("shaders\\fragment_3DL.sh", GL_FRAGMENT_SHADER);

	printf("Linking drawing programs\n");
	drawProg1 = linkProgram(vShader, fShader);
	drawProgFnt = linkProgram(vShader, fShaderF);
	drawProg3D = linkProgram(vShader3D, fShader3D);
	drawProg3DL = linkProgram(vShader3DL, fShader3DL);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteShader(fShaderF);
	glDeleteShader(vShader3D);
	glDeleteShader(fShader3D);
	glDeleteShader(vShader3DL);
	glDeleteShader(fShader3DL);

	// getting uniform variables handles

	unv_2DTRM = glGetUniformLocation(drawProg1, "TRM");
	unv_2Dtex = glGetUniformLocation(drawProg1, "texSampler");
	unv_2Dclr = glGetUniformLocation(drawProg1, "clcl");

	unv_2DFTRM = glGetUniformLocation(drawProgFnt, "TRM");
	unv_2DF_clr = glGetUniformLocation(drawProgFnt, "rclr");

	unv_3Dtex = glGetUniformLocation(drawProg3D, "cTex");
	unv_3Dclr = glGetUniformLocation(drawProg3D, "cClr");
	unv_3DTRM = glGetUniformLocation(drawProg3D, "MVP");
	
	unv_3DLtex = glGetUniformLocation(drawProg3DL, "cTex");
	unv_3DLclr = glGetUniformLocation(drawProg3DL, "cClr");
	unv_3DLTRM = glGetUniformLocation(drawProg3DL, "MVP");
	unv_3DLM = glGetUniformLocation(drawProg3DL, "M");
	unv_3DL_refl = glGetUniformLocation(drawProg3DL, "refl");

	//printf("%d\n", gl)
	///
//	glGenVertexArrays(1, &VertexArrayID);
}

const int buf_szs[5] = { 3, 2, 1, 3, 4 };

void CGEngine::setBuffs(CDrawBuffers& bf)
{
	//glBindVertexArray(VertexArrayID);
	fori(i, GLDB_COUNT)
	{
		if (!bf.bufs[i])
		{
			glDisableVertexAttribArray(i);
			continue;
		}
	//	
		if (i != GLDB_INDEX)
		{
			glEnableVertexAttribArray(i);
			glBindBuffer(GL_ARRAY_BUFFER, bf.bufs[i]);
			glVertexAttribPointer(i, buf_szs[i], GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		else {
			glDisableVertexAttribArray(i);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bf.bufs[i]);
		}
	}
	//glBindVertexArray(0);
	//glBindVertexArray(VertexArrayID);
}

//not necessary
void CGEngine::drawQuad(Point f, Point t, Point ft, Point tt)
{

//	setBuffs(sBufs);

}

void CGEngine::doExit()
{
	isExit = true;
}

void CGEngine::setRasterTrg(Point p)
{
	float x = (p.x - resX / 2) * (2.0f / resX);
	float y = -(p.y - resY / 2) * (2.0f / resY);
	glRasterPos2f(x, y);
	cTex = 0;	//coz relevant operations may reset texture
	//glRasterPos2i((int)p.x, (int)p.y);
}

void CGEngine::selTexture(GLuint tx)
{
	if (cTex == tx) return;

	if (!is3D)
	{
		if (shdMode_2D != shdm_tex)
		{
			shdMode_2D = shdm_tex;
			glUseProgram(drawProg1);
			setColorMod(cColorMod);
		}
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tx);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//const float vv[4] = { 1, 1, 1, 1 };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, vv);
	cTex = tx;
}

void CGEngine::setColorMod(const glm::vec4 &clr)
{
	cColorMod = clr; 
	glUniform4f(is3D ? unv_3Dclr : unv_2Dclr, clr[0], clr[1], clr[2], clr[3]);
	if (is3D) glUniform4f(unv_3DLclr, clr[0], clr[1], clr[2], clr[3]);
}

void CGEngine::selFontColor(const glm::vec4 &clr)
{
	if (shdMode_2D != shdm_fnt)
	{
		shdMode_2D = shdm_fnt;
		glUseProgram(drawProgFnt);
		cTex = 0;
	}	
	glm::mat4 ntrm = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(unv_2DFTRM, 1, GL_FALSE, &ntrm[0][0]);
	glUniform4f(unv_2DF_clr, clr[0], clr[1], clr[2], clr[3]);
}

void CGEngine::renderTrans2D(int ne, Point lt, Point rb)
{
	glm::mat4 ntrm = TRM_2d * glm::translate(glm::vec3(lt.x, lt.y, 0.0f)) * glm::scale(glm::vec3(rb.x - lt.x, rb.y - lt.y, 1.0f));
	glUniformMatrix4fv(unv_2DTRM, 1, GL_FALSE, &ntrm[0][0]);

	glDrawElements(GL_TRIANGLES, ne * 3, GL_UNSIGNED_SHORT, (void*)0);
	///glDrawArrays(GL_TRIANGLES, 0, ne* 3);
}

CSprite* CGEngine::makeSprite(CGLTexture* tex, Point lt, Point rb)
{
	CSprite* ns = new CSprite();
	ns->tex = tex;
	ns->f = lt;
	ns->t = rb;

	float vData[4 * 3];
	float tData[4 * 2];
	const unsigned short iData[6] = {0, 1, 2, 0, 2, 3};

	fori(i, 4) vData[3 * i + 2] = 0.3f; //z
	//x
	vData[3 * 0] = vData[3 * 3] = 0;
	vData[3 * 1] = vData[3 * 2] = 1;
	//y
	vData[3 * 0 + 1] = vData[3 * 1 + 1] = 0;
	vData[3 * 2 + 1] = vData[3 * 3 + 1] = 1;

	const float mrg = 0.5f;
	Point ltf((lt.x + mrg) / tex->sz.x, (lt.y + mrg) / tex->sz.y);
	Point ltt((rb.x + mrg) / tex->sz.x, (rb.y + mrg) / tex->sz.y);

	tData[0] = tData[6] = ltf.x;
	tData[2] = tData[4] = ltt.x;

	tData[1] = tData[3] = ltf.y;
	tData[5] = tData[7] = ltt.y;

	ns->sprBuf.allocBuff(GLDB_VERTEX, 4, vData);
	ns->sprBuf.allocBuff(GLDB_INDEX, 6, iData);
	ns->sprBuf.allocBuff(GLDB_UV, 4, tData);

	return ns;
}

void CGEngine::cycle()
{
	//POINT pp;
	//GetCursorPos(&pp);
	//ScreenToClient()
	//mPos = Point(type(pp.x), type(pp.y));
	__int64 cpTime;
	do
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&cpTime);
		if (cpTime - lpTime < dtTime) Sleep(0);
	} while (cpTime - lpTime < dtTime);
	lpTime = cpTime;

	mState = GetKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	updKeyboard();

	if (gui)
		gui->think(mPos, mState);

	if (isExit)
	{
		glutLeaveMainLoop();
		return;
	}

	if (serverKill)	//signal from thread that terminates
	{
		delete cServer;
		cServer = NULL;
		CloseHandle(hTh_Server);
		hTh_Server = NULL;
		serverKill = false;
		printf("Server was killed\n");
		lPlayer = -1;
		delete cClient;
		cClient = NULL;
	}

	if (cClient)
	{
		if (!cClient->think())
		{
			lPlayer = -1;
			delete cClient;
			cClient = NULL;
		}
		if (!rGame || cClient->gameRestart)
		{
			cClient->gameRestart = false;
			rGame = cClient->getGame_r();
			//okay, we receive no correct game from vovan so let's make it
			if (rGame)
			{

				/*
				rGame->Players_Ammount = 1;
				Player pl;
				pl.Alive = true;
				pl.MyCycle.Current_Point = Point2D<double>(50.0, 50.0);
				pl.MyCycle.Direction = Vector2D<double>(1, 0);
				pl.MyCycle.Speed = 10;//lolwatisit
				pl.Player_Number = 0;
				pl.Team_Number = 0;

				rGame->Walls.resize(1);
				rGame->Walls[0].Segment.A = pl.MyCycle.Current_Point;
				rGame->Walls[0].Segment.B = pl.MyCycle.Current_Point;
				rGame->Walls[0].Player_Number = 0;
				rGame->Walls[0].Wall_Number = 0;

				rGame->Players.push_back(pl);*/
				gui->enterScreen(GSCR_GAME);
				setGame(rGame);
			}
		}
	}

	glutPostRedisplay();
}

void CGEngine::go2D()
{
	glUseProgram(drawProg1);
	is3D = false;

	shdMode_2D = shdm_tex;

	TRM_2d = glm::scale(glm::vec3(1 / (resX * 0.5f),- 1 / (resY * 0.5f), 1.0f)) *
		glm::translate(glm::vec3(-(resX * 0.5f) + 0.5f, -(resY * 0.5f) + 0.5f, 0.0f));
	
	glUniformMatrix4fv(unv_2DTRM, 1, GL_FALSE, &TRM_2d[0][0]);
	glUniform1i(unv_2Dtex, 0);
	setColorMod(glm::vec4(1.0, 1.0, 1.0, 1.0));

	cTex = 0;
}

void CGEngine::go3D()
{
	glUseProgram(drawProg3D);
	is3D = true;
	glUniform1i(unv_3Dtex, 0);
	glUniform1i(unv_3DLtex, 0);

	projMat = glm::perspective(80.0f / 180.0f * 3.14159f, resX / float(resY), 0.1f, 512.0f);
	wrldMat = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	camMat = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	setColorMod(glm::vec4(1.0, 1.0, 1.0, 1.0));
	updMatrices();

	cTex = 0;

}

void CGEngine::draw()
{
//	glShadeModel(GL_SMOOTH);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_DEPTH_TEST);	
//	glDisable(GL_LIGHTING);//not sure if this is still needed
//	glDisable(GL_TEXTURE_2D);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_MULTISAMPLE);
	// glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	go3D();
	if (rGame)
		drawScene(rGame);

	go2D();
	if (gui)
		gui->render();
	//testSpr->render(this, Point(20, 20), false);


	glutSwapBuffers();
}

void CGEngine::updKeyboard()
{
	fori(i, 256)
	{
		if ((GetKeyState(i) & 0x8000) != 0)
		{
			lKeys[i]++;
		}
		else {
			lKeys[i] = 0;
		}
	}
}

bool CGEngine::isKeyPressed(int vkey)
{
	return lKeys[vkey] > 0;
}

bool CGEngine::isKeyJustPressed(int vkey)
{
	return lKeys[vkey] == 1;
}

void CGEngine::start()
{
	isExit = false;
	mPos.x = 0; mPos.y = 0;



	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
//	glutInitContextVersion(3, 3);
//	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
//	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitWindowSize(resX, resY);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Tron");


	printf("Initializing BASS & sound..\n");
	BASS_Init(-1, 44100, 0, GetForegroundWindow(), NULL);

	glutIdleFunc(r_cycle);
	glutPassiveMotionFunc(r_mouseMove);
	glutKeyboardFunc(r_keyb);
	glutDisplayFunc(r_display);
	g_render = this;

	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

//	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}

	if (glewIsSupported("GL_VERSION_3_3"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 not supported. Update ur drivers oify\n");
		getchar();
		return;
	}


	//printf("%s\n", (char const*)glGetString(GL_EXTENSIONS));
	/*
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");*/

	printf("OpenGL vendor string: %s\n", glGetString(GL_VENDOR));
	printf("OpenGL renderer string: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version string: %s\n", glGetString(GL_VERSION));

	//assert(glBindBuffer && glGenBuffers && glBufferData && glDeleteBuffers);

	initRender();
	load();

	gui = new CGUI(this, resX, resY);
	gui->init();
	gui->enterScreen(GSCR_MENU);

	glutMainLoop();
}


DWORD WINAPI hostThreadFunc(LPVOID lpParam)
{
	CGEngine* eng = (CGEngine*)lpParam;
	eng->svth_Entry();
	return 0;
}

void CGEngine::svth_Entry()
{
	while (!isServerExit)
	{
		if (!cServer->think())
		{
			break;
		}
		Sleep(0);
	}
	serverKill = true;
}

void CGEngine::onKey(unsigned char key)
{
	if (gui)
		gui->keyPress(key);
}

void CGEngine::shutdownServer()
{
	isServerExit = true;
}

bool CGEngine::goHosting()
{
	assert(!cServer && !hTh_Server && !cClient);

	Game_Engine* nge = new Game_Engine();
	nge->Constants = ic;

	cServer = new CServer(this, nge);
	isServerExit = false;
	serverKill = false;
	hTh_Server = CreateThread(NULL, 0, hostThreadFunc, this, 0, &hThId_Server);
	assert(hTh_Server);

	Sleep(5);
	if (!goJoining("127.0.0.1"))
	{
		printf("Cannot connect to myself!\n");

		isServerExit = true;
		return false;
	}

	return true;
}

bool CGEngine::goJoining(const char* ip)
{
	assert(!cClient);
	Game_Engine* gge = new Game_Engine();
	gge->Constants = ic;
	cClient = new CClient(this, gge);
	if (!cClient->connect(ip))
	{
		delete cClient;
		cClient = NULL;
		return false;
	}
	else {
		lPlayer = cClient->getPID();
	}
	return true;
}

CGEngine::CGEngine(Init_Constants* aic)
{
	hTh_Server = 0;
	cServer = NULL;
	cClient = NULL;
	wRender = NULL;
	isServerExit = serverKill = false;
	ic = aic;
	resX = ic->resX;
	resY = ic->resY;
	lPlayer = -1;
	g_render = this;
	rGame = NULL;
	fori(i, 256) lKeys[i] = 0;

	lpTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&lpTime);
	QueryPerformanceFrequency((LARGE_INTEGER*)&dtTime);
	dtTime /= 60;
}
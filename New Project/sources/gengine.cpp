#include "stdafx.h"
#include "headers\gengine.h"

/*
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;*/


CGEngine* g_render;

void r_display(void) {
	g_render->draw();
}

void r_cycle()
{
	g_render->cycle();
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

	assert(id >= 0 && id < GLDB_COUNT);
	glGenBuffers(1, bufs + id);
	GLenum trg = id == GLDB_INDEX ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;
	glBindBuffer(trg, bufs[id]);
	if (sz)
		glBufferData(trg, sz * buf_szm[id], data, memType);
}

CDrawBuffers::CDrawBuffers()
{
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
	glGetShaderInfoLog(sh, InfoLogLength, NULL, &errMsg[0]);
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
	printf("%s\n", &errMsg[0]);

	return prog;
}

// ----------------------------------- CGEngine --------------------------------------------

void CGEngine::load()
{
	menuTex = new CGLTexture();
	menuTex->load("menuTex.png");

	testSpr = makeSprite(menuTex, Point(20, 30), Point(20+25, 30+24));
}

void CGEngine::initRender()
{
	printf( "Initializating render\n");

	printf("Loading shaders\n");
	GLuint vShader, fShader, fShaderF;
	vShader = compileShader("shaders\\vertex.sh", GL_VERTEX_SHADER);
	fShader = compileShader("shaders\\fragment.sh", GL_FRAGMENT_SHADER);
	fShaderF = compileShader("shaders\\fragment_font.sh", GL_FRAGMENT_SHADER);

	printf("Linking generic drawing program\n");
	drawProg1 = linkProgram(vShader, fShader);
	drawProgFnt = linkProgram(vShader, fShaderF);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteShader(fShaderF);

	// getting uniform variables handles

	unv_2DTRM = glGetUniformLocation(drawProg1, "TRM");
	unv_2Dtex = glGetUniformLocation(drawProg1, "texSampler");

	unv_2DF_clr = glGetUniformLocation(drawProgFnt, "rclr");
}

const int buf_szs[5] = { 3, 2, 1, 3, 4 };

void CGEngine::setBuffs(CDrawBuffers& bf)
{
	fori(i, GLDB_COUNT)
	{
		if (!bf.bufs[i]) continue;
		glEnableVertexAttribArray(i);
		if (i != GLDB_INDEX)
		{
			glBindBuffer(GL_ARRAY_BUFFER, bf.bufs[i]);
			glVertexAttribPointer(i, buf_szs[i], GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		else {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bf.bufs[i]);
		}
	}
}

//not necessary
void CGEngine::drawQuad(Point f, Point t, Point ft, Point tt)
{

//	setBuffs(sBufs);

}


void CGEngine::setRasterTrg(Point p)
{
	float x = (p.x - resX / 2) * (2.0f / resX);
	float y = -(p.y - resY / 2) * (2.0f / resY);
	glRasterPos2f(x, y);
}

void CGEngine::selTexture(GLuint tx)
{
	if (shdMode_2D != shdm_tex)
	{
		shdMode_2D = shdm_tex;
		glUseProgram(drawProg1);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tx);
}

void CGEngine::selColor(const glm::vec4 &clr)
{
	if (shdMode_2D != shdm_fnt)
	{
		shdMode_2D = shdm_fnt;
		glUseProgram(drawProgFnt);
	}
	glUniform4f(unv_2DF_clr, clr[0], clr[1], clr[2], clr[3]);
}

void CGEngine::renderTrans2D(int ne, Point lt, Point rb)
{
	glm::mat4 ntrm = TRM_2d * glm::translate(glm::vec3(lt.x, lt.y, 0.0f)) * glm::scale(glm::vec3(rb.x - lt.x, rb.y - lt.y, 1.0f));
	glUniformMatrix4fv(unv_2DTRM, 1, GL_FALSE, &ntrm[0][0]);

	glDrawElements(GL_TRIANGLES, ne * 3, GL_UNSIGNED_SHORT, (void*)0);
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

}

void CGEngine::go2D()
{
	glUseProgram(drawProg1);

	shdMode_2D = shdm_tex;

	TRM_2d = glm::scale(glm::vec3(1 / (resX * 0.5f),- 1 / (resY * 0.5f), 1.0f)) *
		glm::translate(glm::vec3(-(resX * 0.5f) + 0.5f, -(resY * 0.5f) + 0.5f, 0.0f));
	
	glUniformMatrix4fv(unv_2DTRM, 1, GL_FALSE, &TRM_2d[0][0]);
	glUniform1i(unv_2Dtex, 0);
}

void CGEngine::draw()
{
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_DEPTH_TEST);	
	glDisable(GL_LIGHTING);//not sure if this is still needed
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_MULTISAMPLE);
	// glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	go2D();
	gui->render();
	//testSpr->render(this, Point(20, 20), false);

	glutSwapBuffers();
}

void CGEngine::start()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(resX, resY);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Tron");
	glutDisplayFunc(r_display);
	glutIdleFunc(r_cycle);
	g_render = this;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}

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

	gui = new CGUI(this);
	gui->init();
	gui->enterScreen(GSCR_MENU);

	glutMainLoop();
}

CGEngine::CGEngine(Init_Constants* aic)
{
	ic = aic;
	resX = ic->resX;
	resY = ic->resY;
	g_render = this;
}
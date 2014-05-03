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

void CGEngine::cycle()
{

}

void CGEngine::go2D()
{

}

void CGEngine::draw()
{
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_MULTISAMPLE);
	// glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)resX, (GLsizei)resY);


	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 4.0f / 3.0f, 0.1f, 400.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	go2D();
	gui->render();

	glutSwapBuffers();
}

void CGEngine::start()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

	gui = new CGUI();
	gui->init();

	glutMainLoop();
}

CGEngine::CGEngine(Init_Constants* aic)
{
	ic = aic;
	resX = ic->resX;
	resY = ic->resY;
	g_render = this;
}
#include "stdafx.h"
#include "headers\gengine.h"

using namespace glm;

struct CDrawEl
{
	CMesh* dMesh;
	mat4 wMat;
};

void CGEngine::drawScene(Game* gm)
{

}

void CGEngine::prepForScene(Game* gm)
{
	assert(lPlayer >= 0 && lPlayer < int(gm->Players.size()));
	Player* lp = &gm->Players[lPlayer];

	cam_Trg = cam_Trg_t = vec3(lp->MyCycle.Current_Point.x, 0.0f, lp->MyCycle.Current_Point.y);
	cam_Pos = vec3(0,0,0);
	cam_Up = vec3(0,1,0);
}
#include "stdafx.h"
#include "headers\gengine.h"

using namespace glm;

struct CDrawEl
{
	CMesh* dMesh;
	mat4 wMat;
};

vec3 pointToVec3(Point p)
{
	return vec3((float ) p.x, 0.0f, (float) p.y);
}
vec3 point2DToVec3(Point2D<double> p)
{
	return vec3((float)p.x, 0.0f, (float)p.y);
}
vec3 vector2DToVec3(Vector2D<double> p)
{
	return vec3((float)p.x, 0.0f, (float)p.y);
}

CMesh* CGEngine::generateGridMesh(int nx, int ny, float sp, float w)
{
	renQuad q;
	q.defaultUV(1.0f, 128.0f/128.0f);
	q.setNormal(vec3(0.0f, 1.0f, 0.0f));
	fori(i, 4) q.v[i].y = 0;

	CMesh* nm = new CMesh();

	fori(i, nx)
	{
		q.v[0].x = i * sp - w;
		q.v[0].z = 0;
		q.v[1].x = i * sp - w;
		q.v[1].z = sp * ny;
		q.v[2].x = i * sp + w;
		q.v[2].z = sp * ny;
		q.v[3].x = i * sp + w;
		q.v[3].z = 0;
		nm->appendQuad(q);
	}
	fori(i, ny)
	{
		q.v[0].x = 0;
		q.v[0].z = i * sp - w;
		q.v[1].x = sp * nx;
		q.v[1].z = i * sp - w;
		q.v[2].x = sp * nx;
		q.v[2].z = i * sp + w;
		q.v[3].x = 0;
		q.v[3].z = i * sp + w;
		nm->appendQuad(q);
	}
	nm->setTexture(gridTex);
	nm->toBuffer();
	return nm;
}

void CGEngine::updMatrices()
{
	pcMat = projMat * camMat;
	pcwMat = pcMat * wrldMat;

	glUniformMatrix4fv(unv_3DTRM, 1, GL_FALSE, &pcwMat[0][0]);
	glUniformMatrix4fv(unv_3DLTRM, 1, GL_FALSE, &pcwMat[0][0]);
}

void CGEngine::updCamera()
{
	camMat = glm::lookAt(cam_Pos, cam_Trg, cam_Up);
}

static float tm = 0.0f;

void CGEngine::drawScene(Game* gm)
{
	cam_Up = vec3(0.0f, 1.0f, 0.0f);
	cam_Trg_t = point2DToVec3(gm->Players[lPlayer].MyCycle.Current_Point);
	vec3 dps = normalize(vector2DToVec3(gm->Players[lPlayer].MyCycle.Direction));

	cam_Trg_t.x = tm;
	cam_Trg_t.z = tm;

	cam_Pos_t = cam_Trg_t - dps * 4.0f + vec3(0.0f, 4.0f, 0.0f);
	tm += 0.001f;

	updCamera();

	wrldMat = translate(vec3(floorf(cam_Pos.x) - 50.0f, 0.0f, floorf(cam_Pos.z) - 50.0f));
	updMatrices();

	glDisable(GL_DEPTH_TEST);
	gridMesh->draw(this);

	float alp = 0.9f;
	cam_Pos = cam_Pos * alp + cam_Pos_t * (1 - alp);
	cam_Trg = cam_Trg * alp + cam_Trg_t * (1 - alp);
}

void CGEngine::prepForScene(Game* gm)
{
	assert(lPlayer >= 0 && lPlayer < int(gm->Players.size()));
	Player* lp = &gm->Players[lPlayer];

	cam_Trg = cam_Trg_t = vec3(lp->MyCycle.Current_Point.x, 0.0f, lp->MyCycle.Current_Point.y);
	cam_Pos = vec3(0.0f,0.0f,0.0f);
	cam_Up = vec3(0.0f,1.0f,0.0f);
}
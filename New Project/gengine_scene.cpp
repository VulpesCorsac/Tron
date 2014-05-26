#include "stdafx.h"
#include "headers\gengine.h"

using namespace glm;

/*
	passes -
		1) direct				-->generic fb
		2) ground reflection	-->generic fb
		3) env. map updates		-->env fb
*/

const int NGROUPS = 3;
// 0 - opaque generic objects (floor, bombs, rockets etc)
// 1 - opaque objects with ligthing / envmapping (bikes)
// 2 - transparent objects (walls)

#define RG_OPAQUE 0
#define RG_OP_LIGHTING 1
#define RG_ALPHA 2

struct CDrawEl
{
	CMesh* dMesh;
	mat4 wMat;
	vec4 cMod = vec4(1.0f);
	bool hasTransform = false;
};

struct CCurScene
{
	vector<CDrawEl> e[NGROUPS];
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

// --------- CWallRender stuff

vec4 indToCol( int i)
{
	if (i == 0) return vec4(0.2f, 0.8f, 1.0f, 1.0f);
	if (i == 1) return vec4(0.9f, 0.6f, 0.6f, 1.0f);
	if (i == 2) return vec4(0.4f, 1.0f, 0.4f, 1.0f);
	if (i == 3) return vec4(1.0f, 0.4f, 0.4f, 1.0f);
	return vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

class CWallRender
{
	struct CWallMesh
	{
		CMesh* m;
		vec4 cMod;
		CWallMesh()
		{
			m = NULL;
			cMod = vec4(1.0f);
		}
	};
	struct CActWall
	{
		int i;
		Wall w;

		bool operator < (const CActWall &oth) const
		{
			if (w.Player_Number < oth.w.Player_Number) return true;
			else if (w.Player_Number > oth.w.Player_Number) return false; 

			if (w.Segment.A.x < oth.w.Segment.A.x) return true;
			else if (w.Segment.A.x > oth.w.Segment.A.x) return false;

			if (w.Segment.A.y < oth.w.Segment.A.y) return true;
			else if (w.Segment.A.y > oth.w.Segment.A.y) return false;

			if (w.Segment.B.x < oth.w.Segment.B.x) return true;
			else if (w.Segment.B.y > oth.w.Segment.B.y) return false;

			if (w.Segment.B.y < oth.w.Segment.B.y) return true;
			else if (w.Segment.B.y > oth.w.Segment.B.y) return false;

			return false;
		}
	};
private:
	vector<CWallMesh> wm;

	set<CActWall> ws_ni;
	vector<CActWall> ws_i;

	vector<CWallMesh> dWalls;
	vector<Wall> dWallsS;

	vector<CWallMesh> statWalls;

	//if t1 is low and t2 is high, U is assumed to be lengthy direction, V - not.
	void makeWall2(CMesh*trg, vec3 sPos, vec3 ePos, vec2 t1, vec2 t2, float w, float h, float h2)
	{
		vec3 dv1 = normalize(ePos - sPos) * w;
		swap(dv1.x, dv1.z);
		dv1.z = -dv1.z;

		vec3 lv[4], hv[4];
		lv[0] = sPos - dv1; lv[1] = ePos - dv1; lv[2] = ePos + dv1; lv[3] = sPos + dv1;
		fori(i, 4)
		{
			hv[i] = lv[i] + vec3(0.0f, ((i == 1) || (i == 2)) ? h2 : h, 0.0f);
		}

		renQuad q;
		q.defaultUV(t1, t2);

		fori(i, 4) q.v[i] = lv[3-i];
	
		q.autoNormal();
		//trg->appendQuad(q);

		fori(i, 4) q.v[i] = hv[i];
		q.autoNormal();
		//trg->appendQuad(q);

		fori(i, 4)
		{
			int j = (i + 1) % 4;
			q.v[0] = hv[i];
			q.v[1] = hv[j];
			q.v[2] = lv[j];
			q.v[3] = lv[i];
			q.autoNormal();
			trg->appendQuad(q);
		}

	}

	void makeWall(CMesh* trg, vec3 sPos, vec3 ePos, float w, bool isLast)
	{
		if (ePos == sPos) return;

		vec3 d = ePos - sPos;
		float r = length(d);

		const float in_r = 1.3f;

		float t_en = r / 3.0f;

		const float whh = 0.6f;
		const float whh2 = whh*0.7f;

		if (!isLast)
		{
			makeWall2(trg, sPos, ePos, vec2(0.0f, 0.0f), vec2(t_en, 1.0f), w, whh, whh);
		}
		else {
			if (r > in_r)
			{
				vec3 mp = sPos + d * ((r - in_r) / r);

				makeWall2(trg, sPos, mp, vec2(0.0f, 0.0f), vec2(t_en - in_r, 1.0f), w, whh, whh);
				makeWall2(trg, mp, ePos, vec2(t_en - in_r, 0.0f), vec2(t_en, 1.0f), w, whh, whh2);
			}
			else {
				makeWall2(trg, sPos, ePos, vec2(0.0f, 0.0f), vec2(t_en, 1.0f), w, whh, whh2);
			}
		}
	}

	void setWall(CWallMesh &tw, const Wall& w, bool isLast)
	{
		if (!tw.m)
		{
			tw.m = new CMesh();
			tw.m->setTexture(wTex);
		}
		tw.cMod = indToCol(w.Player_Number);
		makeWall(tw.m, point2DToVec3(w.Segment.A), point2DToVec3(w.Segment.B), 0.01f, isLast);
		tw.m->toBuffer(true);
	}

public:
	CGLTexture* wTex;
	void addTo(CCurScene& sc)
	{
		forvec(CWallMesh, dWalls, i)
		{
			CDrawEl e;
			e.dMesh = i->m;
			e.wMat = mat4(1.0f);
			e.cMod = i->cMod;
			sc.e[RG_ALPHA].push_back(e);
		}
		forvec(CWallMesh, statWalls, i)
		{
			CDrawEl e;
			e.dMesh = i->m;
			e.wMat = mat4(1.0f);
			e.cMod = i->cMod;
			sc.e[RG_OPAQUE].push_back(e);
		}
	}

	void setDynamicWall(const Wall& w, int ind, bool isLast)
	{
		if (int(dWalls.size()) <= ind)
		{
			dWalls.resize(ind + 1);
			dWallsS.resize(ind + 1);
		}
		if (dWallsS[ind] == w) return;
		dWallsS[ind] = w;
		setWall(dWalls[ind], w, isLast);
	}

	void prepare(Game* g, Init_Constants* ic, CGEngine* gEng)
	{
		forvec(CWallMesh, wm, i) delete i->m;
		forvec(CWallMesh, dWalls, i) delete i->m;
		forvec(CWallMesh, statWalls, i) delete i->m;
		wm.clear();
		ws_ni.clear();
		ws_i.clear();
		dWalls.clear();
		statWalls.clear();

		vec3 vp[4];
		vp[0] = vec3(0, 0, 0);
		vp[1] = vec3(0, 0, ic->Field_Width);
		vp[2] = vec3(ic->Field_Length, 0, ic->Field_Width);
		vp[3] = vec3(ic->Field_Length, 0, 0);

		CWallMesh m;
		m.m = new CMesh();
		m.cMod = vec4(0.0f, 0.8f, 0.8f, 1.0f);
		fori(i, 4)
		{
			int j = (i + 1) % 4;
			makeWall2(m.m, vp[i], vp[j], vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), 0.05f, 2.0f, 2.0f);
		}
		m.m->toBuffer(false);
		m.m->setTexture(gEng->whiteTex);
		statWalls.push_back(m);
	}

	~CWallRender()
	{
		forvec(CWallMesh, wm, i) delete i->m;
		forvec(CWallMesh, dWalls, i) delete i->m;
	}
};

// --------- CGEngine stuff

CMesh* CGEngine::generateGridMesh2(int nx, int ny, float sp)
{
	renQuad q;
	q.defaultUV(1.0f, 1.0f);
	q.setNormal(vec3(0.0f, 1.0f, 0.0f));
	fori(i, 4) q.v[i].y = 0;
	CMesh* nm = new CMesh();
	q.v[0].x = 0;
	q.v[0].z = 0;
	q.v[1].x = 0;
	q.v[1].z = sp * ny;
	q.v[2].x = sp * nx;
	q.v[2].z = sp * ny;
	q.v[3].x = sp * nx;
	q.v[3].z = 0;
	nm->appendQuad(q);
	nm->setTexture(gridTex2);
	nm->toBuffer();
	return nm;
	
}

CMesh* CGEngine::generateGridMesh(int nx, int ny, float sp, float w)
{
	renQuad q;
	q.defaultUV(1.0f, 1.0f);
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
		q.v[0].z = i * sp + w;
		q.v[1].x = sp * nx;
		q.v[1].z = i * sp + w;
		q.v[2].x = sp * nx;
		q.v[2].z = i * sp - w;
		q.v[3].x = 0;
		q.v[3].z = i * sp - w;
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

	glUniformMatrix4fv(unv_3DLTRM, 1, GL_FALSE, &pcwMat[0][0]);
	glUniformMatrix4fv(unv_3DLM, 1, GL_FALSE, &wrldMat[0][0]);
	glUniformMatrix4fv(unv_3DTRM, 1, GL_FALSE, &pcwMat[0][0]);
}

void CGEngine::updCamera()
{
	camMat = glm::lookAt(cam_Pos, cam_Trg, cam_Up);
}

static float tm = 0.0f;


void CGEngine::buildScene(Game* gm, CCurScene& cs)
{

	//temporary - everything is dynamic
	cs.e->clear();

	forvec(Wall, gm->Walls, i)
	{
		wRender->setDynamicWall(*i, i - gm->Walls.begin(), (i - gm->Walls.begin()) < int(gm->Players.size()));
	}
	wRender->addTo(cs);

	forvec(Player, gm->Players, i)
	{
		CDrawEl e;
		e.cMod = 0.9f * indToCol(i->Team_Number);
		e.cMod.a = 1.0f;

		e.dMesh = motoMesh;
		e.hasTransform = true;

		float ang = pAngs[i->Player_Number];

		mat4 rMatrix = rotate(ang, vec3(0.0f, 1.0f, 0.0f));
		mat4 tMatrix = translate(point2DToVec3(i->MyCycle.Current_Point));
		mat4 tMatrix2 = translate(vec3(0.55,0,0));
		e.wMat = tMatrix * rMatrix * tMatrix2 * scale(vec3(0.002f, 0.002f, 0.002f));

		float nang = -atan2f(i->MyCycle.Direction.y, i->MyCycle.Direction.x);

		const float asp = 0.9f;


		if (pAngs[i->Player_Number] - nang >= 3.14159f) pAngs[i->Player_Number] -= 2 * 3.14159f;
		if (nang - pAngs[i->Player_Number] >= 3.14159f) pAngs[i->Player_Number] += 2 * 3.14159f;

		//pAngs[i->Player_Number] = pAngs[i->Player_Number] * asp + nang * (1 - asp);
		if (pAngs[i->Player_Number] - nang >= 0.3f) pAngs[i->Player_Number] -= 0.3f;
		if (nang - pAngs[i->Player_Number] >= 0.3f) pAngs[i->Player_Number] += 0.3f;
		if (fabsf(pAngs[i->Player_Number] - nang) <= 0.3f) pAngs[i->Player_Number] = nang;

	//		pAngs[i->Player_Number] += pAngs[i->Player_Number] * asp + nang * (1 - asp);

		cs.e[RG_OP_LIGHTING].push_back(e);
	}
}

void CGEngine::drawScene(CCurScene& cs, glm::mat4 &tr)
{
	fori(rg, 3)
	{
		if (rg == RG_OPAQUE)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_DEPTH_WRITEMASK);
		}
		else if (rg == 1)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_DEPTH_WRITEMASK);
			glUseProgram(drawProg3DL);

		}
		else if (rg == RG_ALPHA)
		{
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_DEPTH_WRITEMASK);
			glUseProgram(drawProg3D);
		}


		forvec(CDrawEl, cs.e[rg], i)
		{
			if (!i->dMesh) continue;
			if (!i->hasTransform)
			{
				wrldMat = tr;
				updMatrices();
			}
			else {
				wrldMat = tr * i->wMat;
				updMatrices();
			}

			setColorMod(i->cMod);
			i->dMesh->draw(this);
		}
	}
}

void CGEngine::drawScene(Game* gm)
{

	//camera update
	cam_Up = vec3(0.0f, 1.0f, 0.0f);
	cam_Trg_t = point2DToVec3(gm->Players[lPlayer].MyCycle.Current_Point) + vec3(0.0f, 0.5f, 0.0f);
	vec3 dps = normalize(vector2DToVec3(gm->Players[lPlayer].MyCycle.Direction));
	cam_Pos_t = cam_Trg_t - dps * 1.0f /*+ vec3(dps.z, 0, -dps.x) */ + vec3(0.0f, 0.5f, 0.0f);
	//tm += 0.001f;
	updCamera();

	fori(i, (int)gm->Players.size())
		gm->Walls[i].Segment.B = gm->Players[i].MyCycle.Current_Point;	//pffft...

	//scene preparing

	CCurScene csn;
	buildScene(gm, csn);

	//from down to top

	//underworld
	mat4 refl = scale(vec3(1.0f, -1.0f, 1.0f));
	glUniform1f(unv_3DL_refl, -1.0f);
	drawScene(csn, refl);

	//grid rendering
	wrldMat = translate(vec3(floorf(cam_Pos.x) - 50.0f, 0.0f, floorf(cam_Pos.z) - 50.0f));
	updMatrices();
	setColorMod(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	glDisable(GL_DEPTH_WRITEMASK);
	glEnable(GL_DEPTH_TEST);
	gridMesh2->draw(this);
	glDisable(GL_DEPTH_TEST);

	//setColorMod(vec4(1.0f, 1.0f, 0.0f + float(rand() % 100) * 0.00f, 1.0f));
	gridMesh->draw(this);
	//setColorMod(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_WRITEMASK);

	//overworld
	glUniform1f(unv_3DL_refl, 1.0f);
	drawScene(csn, mat4(1.0f));

	float alp = 0.9f;
	cam_Pos = cam_Pos * alp + cam_Pos_t * (1 - alp);
	cam_Trg = cam_Trg * alp + cam_Trg_t * (1 - alp);

	float trg_dist = length(cam_Pos_t - cam_Trg_t);
	cam_Pos = cam_Trg + normalize(cam_Pos - cam_Trg) * trg_dist;
}

void CGEngine::prepForScene(Game* gm)
{
	assert(lPlayer >= 0 && lPlayer < int(gm->Players.size()));
	Player* lp = &gm->Players[lPlayer];

	cam_Trg = cam_Trg_t = vec3(lp->MyCycle.Current_Point.x, 0.0f, lp->MyCycle.Current_Point.y);
	cam_Pos = vec3(0.0f,0.0f,0.0f);
	cam_Up = vec3(0.0f,1.0f,0.0f);

	if (!wRender)
	{
		wRender = new CWallRender();
		wRender->wTex = wallTex;
		wRender->prepare(gm, ic, this);
	}

	pAngs.resize(gm->Players.size(), 0.0f);
}

void CGEngine::setGame(Game* gm)
{
	rGame = gm;
	prepForScene(rGame);
}
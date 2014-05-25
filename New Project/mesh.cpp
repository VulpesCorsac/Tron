#include "stdafx.h"
#include "mesh.h"
#include "headers\gEngine.h"

#include "ObjLoader\objLoader.h"


void renQuad::autoNormal()
{
	glm::vec3 nn = glm::normalize(glm::cross(v[1] - v[0], v[3] - v[0]));	//no idea about the sign yet, totest
	setNormal(nn);
}


void renQuad::defaultUV(glm::vec2 t1, glm::vec2 t2)
{
	uv[0] = t1;
	uv[2] = t2;
	uv[1].y = uv[0].y;
	uv[1].x = uv[2].x;
	uv[3].y = uv[2].y;
	uv[3].x = uv[0].x;
}

void renQuad::defaultUV(float tx, float ty)
{
	uv[0].x = 0; uv[0].y = 0;
	uv[1].x = tx; uv[1].y = 0;
	uv[2].x = tx; uv[2].y = ty;
	uv[3].x = 0; uv[3].y = ty;
}

void renQuad::setNormal(glm::vec3 a)
{
	fori(i, 4) n[i] = a;
}

//--------------------------------------


void CMesh::appendQuad(renQuad& q)
{
	int j = qSize;
	q_i.push_back(4*j);
	q_i.push_back(4 * j + 1);
	q_i.push_back(4 * j + 2);
	q_i.push_back(4 * j);
	q_i.push_back(4 * j + 2);
	q_i.push_back(4 * j + 3);
	fori(i, 4)
	{
		q_v.push_back(q.v[i]);
		q_n.push_back(q.n[i]);
		q_uv.push_back(q.uv[i]);
	}
	qSize++;
}

void CMesh::toBuffer(bool isDyn, bool clrTemp)
{
	if (!q_v.size())
	{
		bf.relBuffers();
		bufI_size = bufQ_size = 0;
		return;
	}
	if (!isDyn || !bf.bufs[0] || bufQ_size != qSize)
	{
		bf.relBuffers();

		bufQ_size = qSize;
		bufI_size = qSize * 6;

		GLuint memType = isDyn ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
	//	if (!isDyn)
	//	{
			bf.allocBuff(GLDB_VERTEX, bufQ_size * 4, &q_v[0], memType);
			bf.allocBuff(GLDB_UV, bufQ_size * 4, &q_uv[0], memType);
			bf.allocBuff(GLDB_NORMALS, bufQ_size * 4, &q_n[0], memType);
			bf.allocBuff(GLDB_INDEX, bufQ_size * 6, &q_i[0], memType);
	//	}
	} else {

		bf.updBuff(GLDB_VERTEX, bufQ_size * 4, &q_v[0]);
		bf.updBuff(GLDB_UV, bufQ_size * 4, &q_uv[0]);
		bf.updBuff(GLDB_NORMALS, bufQ_size * 4, &q_n[0]);
	//	bf.allocBuff(GLDB_INDEX, bufQ_size * 6, &q_i[0]); not necessary, i guess
	}
	if (clrTemp)
	{
		q_v.clear();
		q_n.clear();
		q_i.clear();
		q_uv.clear();
		qSize = 0;
	}
}

void CMesh::draw(CGEngine* gEng)
{
	if (!bf.bufs[0]) return;

	if (bTex)
		gEng->selTexture(bTex->texInd);

	gEng->setBuffs(bf);

	glDrawElements(GL_TRIANGLES, bufI_size, GL_UNSIGNED_SHORT, (void*)0);
}

void CMesh::setTexture(CGLTexture * tex)
{
	bTex = tex;
}

bool CMesh::loadFrom(const char* src)
{
	printf("Loading mesh file : %s ..", src);
	objLoader ld;
	if (ld.load(src))
	{

	} else {
		assert(false);
		return false;
	}

	struct CVertexKey
	{
		int nrI, vrI, txI;

		bool operator <(const CVertexKey& other) const
		{
			if (vrI < other.vrI) return true; else if (vrI > other.vrI) return false;
			if (txI < other.txI) return true; else if (txI > other.txI) return false;
			return nrI < other.nrI;
		}
	};
	struct CVertex
	{
		float x, y, z, tx, ty, nx, ny, nz;
		int col;
	};


	map<CVertexKey, int> vKeys;
	//vector<CVertex> rVecs;
	vector<glm::vec3> v_v, v_n;
	vector<glm::vec2> v_uv;

	fori(i, ld.faceCount)
	{
		fori(j, ld.faceList[i]->vertex_count)
		{
			CVertexKey k;
			k.vrI = ld.faceList[i]->vertex_index[j];
			k.nrI = ld.faceList[i]->normal_index[j];
			k.txI = ld.faceList[i]->texture_index[j];
			map<CVertexKey, int>::iterator kk = vKeys.find(k);
			if (kk == vKeys.end())
			{
				vKeys.insert(pair<CVertexKey, int>(k, v_v.size()));

				if (k.txI >= 0)
					v_uv.push_back(glm::vec2((float)ld.textureList[k.txI]->e[0],
					1 - (float)ld.textureList[k.txI]->e[1]));
				else
					v_uv.push_back(glm::vec2(0.0f, 0.0f));
				v_v.push_back(glm::vec3(ld.vertexList[k.vrI]->e[0], ld.vertexList[k.vrI]->e[1], ld.vertexList[k.vrI]->e[2]));
				v_n.push_back(glm::vec3(ld.normalList[k.nrI]->e[0], ld.normalList[k.nrI]->e[1], ld.normalList[k.nrI]->e[2]));
			}
		}
	}

	int nv = (int)v_v.size();
	if (nv >= 2)
	{
		vector<unsigned short> inds;
		fori(i, ld.faceCount)
		{
			int kc[4];
			fori(j, ld.faceList[i]->vertex_count)
			{
				CVertexKey k;
				k.vrI = ld.faceList[i]->vertex_index[j];
				k.nrI = ld.faceList[i]->normal_index[j];
				k.txI = ld.faceList[i]->texture_index[j];
				map<CVertexKey, int>::iterator kk = vKeys.find(k);
				assert(kk != vKeys.end());
			//	assert(j != 3);
				if (j == 3)
				{
					inds.push_back(kc[0]);
					inds.push_back(kc[2]);
					inds.push_back(kk->second);
				}
				else {
					inds.push_back(kk->second);
					kc[j] = kk->second;
				}
			}
		}

		bf.allocBuff(GLDB_VERTEX, v_v.size(), &v_v[0]);
		bf.allocBuff(GLDB_UV, v_uv.size(), &v_uv[0]);
		bf.allocBuff(GLDB_NORMALS, v_n.size(), &v_n[0]);
		bf.allocBuff(GLDB_INDEX, inds.size(), &inds[0]);
		bufI_size = (int)inds.size();
	}
	else {
		return false;
	}

	printf("done\n");
	return true;
}

CMesh::CMesh()
{
	qSize = 0;
	bufQ_size = 0;
	bufI_size = 0;
	bTex = 0;
}

CMesh::~CMesh()
{

}
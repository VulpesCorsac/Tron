#include "stdafx.h"
#include "mesh.h"

#include "ObjLoader\objLoader.h"

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

	}
	else {
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
	vector<CVertex> rVecs;
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
				vKeys.insert(pair<CVertexKey, int>(k, rVecs.size()));

				v_uv.push_back( glm::vec2( (float)ld.textureList[k.txI]->e[0], 
					 1 - (float)ld.textureList[k.txI]->e[1] ) );
				v_v.push_back(glm::vec3(ld.vertexList[k.vrI]->e[0], ld.vertexList[k.vrI]->e[1], ld.vertexList[k.vrI]->e[2]));
				v_n.push_back(glm::vec3(ld.normalList[k.nrI]->e[0], ld.normalList[k.nrI]->e[1], ld.normalList[k.nrI]->e[2]));
			}
		}
	}

	int nv = (int)rVecs.size();
	if (nv >= 2)
	{
		vector<unsigned short> inds;
		fori(i, ld.faceCount)
		{
			fori(j, ld.faceList[i]->vertex_count)
			{
				CVertexKey k;
				k.vrI = ld.faceList[i]->vertex_index[j];
				k.nrI = ld.faceList[i]->normal_index[j];
				k.txI = ld.faceList[i]->texture_index[j];
				map<CVertexKey, int>::iterator kk = vKeys.find(k);
				assert(kk != vKeys.end());
				assert(j != 3);
				inds.push_back(kk->second);
			}
		}

		bf.allocBuff(GLDB_VERTEX, v_v.size() * sizeof(glm::vec3), &v_v[0]);
		bf.allocBuff(GLDB_UV, v_uv.size() * sizeof(glm::vec2), &v_uv[0]);
		bf.allocBuff(GLDB_NORMALS, v_n.size() * sizeof(glm::vec3), &v_n[0]);
		bf.allocBuff(GLDB_INDEX, inds.size() * sizeof(unsigned short), &inds[0]);
	}
	else {
		return false;
	}

	printf("done\n");
	return true;
}

CMesh::CMesh()
{

}

CMesh::~CMesh()
{

}
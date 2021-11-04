#pragma once
#include "../../Core/glm.h"

#include <vector>

enum MeshSize {
	UBYTE = UCHAR_MAX,
	USHORT = USHRT_MAX,
	UINT = UINT_MAX
};
template <typename VertexType, MeshSize Size,bool KeepInRam>
class Mesh{
	VertexType VERTICIES[Size];
	Mesh();
};


struct VertexLayout {
	std::vector<unsigned short> Strife;
	std::vector<unsigned short> Count;
};
struct Vertex {
	static VertexLayout layout;
};
struct Vertex3D :Vertex{

	Vertex3D(glm::vec3 pos, glm::vec3 nor, glm::vec2 uv) {
		POSITION = pos;
		NORMAL = nor;
		TEXCOORD = uv;
	}
	glm::vec3 POSITION;
	glm::vec3 NORMAL;
	glm::vec2 TEXCOORD;
};
struct Vertex2D :public Vertex{


	glm::vec2 POSITION;
	glm::vec2 TEXCOORD;
};

										//max verticies  - MemSize
typedef Mesh<Vertex2D,  UBYTE,true>LowMesh2D; //256
typedef Mesh<Vertex2D, USHORT,true>Mesh2D_2B; //25,565
typedef Mesh<Vertex2D,   UINT,true>HighMesh2D; //4,294,967,295 - 128MB

typedef Mesh<Vertex3D,  UBYTE,true> Mesh3D_1B;
typedef Mesh<Vertex3D, USHORT,true> Mesh3D_2B;
typedef Mesh<Vertex3D,   UINT,true> Mesh3D_4B;

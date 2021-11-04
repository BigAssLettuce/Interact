
#ifndef MESH3D_C
#define MESH3D_C

//#define NEWMESHTEST


#include <vector>
//#include "../../Core/Resource.h"
#include "../../Core/RenderAPI/RenderAPI.h"
#include "../../Core/glm.h"
#include "../../Core/Debug/Colors.h"
//#include "../../Core/Debug/Debugger.h"
#include <string>

#include "../../Core/RenderAPI/VertexArray/VertexArray.h"
struct Mesh3DAABB {
	glm::vec3 Max;
	glm::vec3 Min;
	glm::vec3 Center;
	glm::vec3 Size;
};
struct OldVertex3D {

	OldVertex3D(glm::vec3 _pos, glm::vec3 _normal, glm::vec2 _uv) {
		POSITION = _pos;
		NORMAL = _normal;
		TEXCOORD = _uv;
	}
	glm::vec3 POSITION;
	glm::vec3 NORMAL;
	glm::vec2 TEXCOORD;
};

#ifndef MESH_ELEMENTTYPE 
#define MESH_ELEMENTTYPE GL_UNSIGNED_SHORT
#endif

#if MESH_ELEMENTTYPE == GL_UNSIGNED_SHORT
	#define ElementDataType  unsigned short
	#define MaxElementData USHRT_MAX
#elif MESH_ELEMENTTYPE == GL_UNSIGNED_INT
	#define ElementDataType  unsigned int
#elif MESH_ELEMENTTYPE == GL_UNSIGNED_BYTE
#define ElementDataType  unsigned char
#endif


class Debugger;
class OldMesh3D
{
	friend Debugger;
	static void ParseOBJ(std::string content, std::vector<OldVertex3D>* vertexVector, std::vector<ElementDataType>* triangleVector, float scale = 1);

	

#ifndef NEWMESHTEST
	GLuint VertexArrayObjectID = -1;
	GLuint MeshTrianglesBufferID = -1;
	GLuint MeshDataBufferID = -1;
#else
	VertexArray VAO;
	VertexBuffer VBO;
	ElementBuffer EBO;

#endif



	static std::vector<OldMesh3D*> MeshRegistry;
	void CalculateAABB();
public:
	OldMesh3D();
	struct ParsedMesh
	{
		ParsedMesh() {
			Triangles = std::vector<ElementDataType>();
			verticies = std::vector<OldVertex3D>();
		}
		std::string Name;
		std::vector<OldVertex3D> verticies;
		std::vector<ElementDataType> Triangles;
		std::string Group;
	};
	static void ParseMultiObj(std::string ObjContent, std::vector<ParsedMesh>* meshes,float Scale);
	bool LoadFromOBJ(std::string file, float scale = 1);

	void DrawAABB(COLORS color);
	std::string Name = "No Name";
	std::vector<ElementDataType>  TRIANGLES;
	std::vector<OldVertex3D>		VERTICIES;



	Mesh3DAABB BOUNDS;

	unsigned int GetTriangleCount() { return TRIANGLES.size(); }
	//VERTEXpos METHODS
	std::vector<OldVertex3D> getVerticies() { return VERTICIES; }
	void SetVerticies(std::vector<OldVertex3D> _verticies) { VERTICIES = _verticies; CalculateAABB(); UpdateVertexBufferData(); }
	void UpdateVertexBufferData();

	std::vector<ElementDataType> GetTriangles() { return TRIANGLES; }
	void SetTriangles(std::vector<ElementDataType> _triangles) { TRIANGLES = _triangles; UpdateElementBufferData();}
	void UpdateElementBufferData();

	
	void Use();
	static void CleanUp();
};

#endif
#pragma once
#include "../Core/include.h"
#include <vector>
#include "../Core/Resource.h"
struct MeshBounds {
	vec3 Max;
	vec3 Min;
	vec3 Center;
	vec3 Size;
};
struct Vertex {
	Vertex(){}
	Vertex(vec3 _pos, vec3 _normal, vec2 _uv) {
		POSITION = _pos;
		NORMAL = _normal;
		TEXCOORD = _uv;
	}
	vec3 POSITION;
	vec3 NORMAL;
	vec2 TEXCOORD;
};


#define GLElementDataType GL_UNSIGNED_SHORT

#if GLElementDataType == GL_UNSIGNED_SHORT
	#define ElementDataType  unsigned short
#elif GLElementDataType == GL_UNSIGNED_INT
	#define ElementDataType  unsigned int
#elif GLElementDataType == GL_UNSIGNED_BYTE
#define ElementDataType  unsigned char
#endif

#define myass yourass

#if myass == yourass
#define myballs yourballs
#endif

class Mesh
{
	
	static void ParseOBJ(string content, vector<Vertex>* vertexVector, vector<ElementDataType>* triangleVector);
	GLuint VertexArrayObjectID = -1;
	GLuint MeshTrianglesBufferID = -1;
	GLuint MeshDataBufferID = -1;

public:
	void LoadFromOBJ(string file);
	vector<ElementDataType>  TRIANGLES;
	vector<Vertex>			VERTICIES;


	MeshBounds BOUNDS;

	unsigned int GetTriangleCount() { return TRIANGLES.size(); }
	//VERTEXpos METHODS
	vector<Vertex> getVerticies() { return VERTICIES; }
	void SetVerticies(vector<Vertex> _verticies) { VERTICIES = _verticies; UpdateVertexBufferData();}
	void UpdateVertexBufferData();

	vector<ElementDataType> GetTriangles() { return TRIANGLES; }
	void SetTriangles(vector<ElementDataType> _triangles) { TRIANGLES = _triangles; UpdateTriangleBufferData();}
	void UpdateTriangleBufferData();

	Mesh();
	void Use();
	static void CleanUp();
};


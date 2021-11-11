#pragma once
#include "../../Core/glm.h"

#include <vector>
#include "../../Core/RenderAPI/RenderAPI.h"
#include "../../Core/RenderAPI/VertexArray/VertexArray.h"
#include <limits>
//#include "../../Core/RenderAPI/Buffers/ElementBuffer/ElementBuffer.h"
//#include "../../Core/RenderAPI/Buffers/VertexBuffer/VertexBuffer.h"
#include "../../Core/Debug/Console.h"

struct VertexAttribute {
	VertexAttribute(unsigned int _index, int _vectorSize, VertexAttributeType _datatype, bool _normalized, int _stride, int _InitialStride) {
		index = _index; vectorSize = _vectorSize; dataType = _datatype;
		Normalized = _normalized; Stride = _stride; InitialStride = _InitialStride;
	}
	unsigned int index;
	int vectorSize;
	VertexAttributeType dataType;
	bool Normalized;
	int Stride;
	int InitialStride;

};

template<class PosType>
struct Vertex {
	PosType POSITION;
	//static VertexAttribute VertexLayouts[]= 0;
};


class BaseMesh {
protected:
	ElementBuffer EBO = ElementBuffer(1 * sizeof(unsigned short), STATIC_DRAW);
	VertexBuffer VBO = VertexBuffer(1 * sizeof(glm::vec3), STATIC_DRAW);
	VertexArray VAO = VertexArray();
	int ElementCount = 0;
public:
	void Use() { VAO.Use(); EBO.Bind(); }
	int GetTriangleCount() { return ElementCount; }
	BaseMesh() {
		//VAO.BindEBO(&EBO);
		VAO.BindVBO(&VBO);

	};
	// virtual ~BaseMesh() {};
};

#define MeshTemplate template <class VertexDef, typename IndexType>
MeshTemplate
class GMesh :public BaseMesh{

protected:
	std::vector<VertexAttribute>VertexAttributes = VertexDef::GetLayout();
	
	static std::vector<GMesh*> MeshRegistry;
	static const IndexType MaxVerticies = ~((IndexType)0 & 0);

public:
	GMesh() {
		EBO.ReInitialize(10 * sizeof(IndexType), STATIC_DRAW);
		VBO.ReInitialize(MaxVerticies * sizeof(VertexDef), STATIC_DRAW);//CHANGE DONT FORGET DICKHEAD
		

		VAO.BindVBO(&VBO);

		for (VertexAttribute attr : VertexAttributes) {
			VAO.EnableVertexAttribute(attr.index);
			VAO.AssignVertexAttribute(attr.index, attr.vectorSize, attr.dataType, attr.Normalized, attr.Stride, (void*)attr.InitialStride);
		}
	}


	
	virtual void SetVerticies(VertexDef vs[],int Size) {
		VBO.InsertData(0, sizeof(vs[0] ) * Size, vs);
	}
	virtual void SetIndicies(IndexType ts[], int Size) {
		if (sizeof(ts[0]) * Size > EBO.GetSize()) EBO.ReInitialize(sizeof(ts[0]) * Size, STATIC_DRAW);
		EBO.InsertData(0, sizeof(ts[0]) * Size, ts);
		ElementCount = Size;
	}
	

};

MeshTemplate
class Mesh :public GMesh<VertexDef, IndexType> {

public:
	Mesh() {
		
	}
	void UpdateVerticies() {
		GMesh<VertexDef,IndexType>::VBO.InsertData(0,sizeof(VERTICIES[0])*VERTICIES.size(),&VERTICIES[0]);}
	void UpdateIndicies() {
		GMesh<VertexDef,IndexType>::EBO.InsertData(0,sizeof(INDICIES[0])*INDICIES.size(),&INDICIES[0]);}
	vector<VertexDef> VERTICIES = vector<VertexDef>();
	//VertexDef VERTICIES[GMesh<VertexDef, ElementType>::MaxVerticies];
	vector<IndexType> INDICIES = vector<IndexType>();

	
	void SetVerticies(VertexDef vs[], int Size) override {
		Console::Error("Dont Use Set functions on Mesh. thats only for GMesh, update vectors directly and use UpdateVerticies / UpdateTriangles functions");
	}
	void SetIndicies(IndexType ts[], int Size) override {
		Console::Error("Dont Use Set functions on Mesh. thats only for GMesh, update vectors directly and use UpdateVerticies / UpdateTriangles functions");
	}
private:
	
};



struct Vertex3D : Vertex<glm::vec3> {
public:
	Vertex3D(){}
	Vertex3D(glm::vec3 pos, glm::vec3 nor, glm::vec2 uv) {
		POSITION = pos;
		NORMAL = nor;
		TEXCOORD = uv;
	}
	glm::vec3 NORMAL;
	glm::vec2 TEXCOORD;

	static std::vector<VertexAttribute> GetLayout() {
		return std::vector<VertexAttribute> {
			VertexAttribute(0, 3, VertexAttributeType::FLOAT, false, sizeof(Vertex3D), 0),
				VertexAttribute(1, 3, VertexAttributeType::FLOAT, true, sizeof(Vertex3D), sizeof(glm::vec3)),
				VertexAttribute(2, 2, VertexAttributeType::FLOAT, false, sizeof(Vertex3D), sizeof(glm::vec3) * 2)
		};
	}
};



struct Vertex2D : Vertex<glm::vec2> {
	Vertex2D(){}
	Vertex2D(glm::vec2 pos, glm::vec2 uv) {
		POSITION = pos;
		TEXCOORD = uv;
	}
	glm::vec2 TEXCOORD;

	static std::vector<VertexAttribute> GetLayout() {
		return std::vector<VertexAttribute> {
			VertexAttribute(0, 2, VertexAttributeType::FLOAT, false, sizeof(Vertex2D), 0),
				VertexAttribute(1, 2, VertexAttributeType::FLOAT, false, sizeof(Vertex2D), sizeof(glm::vec2)),

		};

	}
};


							//ONLY UNSIGNED BYTE,SHORT,INT				
typedef GMesh<Vertex2D,  unsigned char>GMesh2D_LOW;	
typedef GMesh<Vertex2D, unsigned short>GMesh2D;
typedef GMesh<Vertex2D,   unsigned int>GMesh2D_HIGH;

typedef GMesh<Vertex3D,  unsigned char>GMesh3D_LOW;
typedef GMesh<Vertex3D, unsigned short>GMesh3D;
typedef GMesh<Vertex3D,   unsigned int>GMesh3D_HIGH;

typedef Mesh<Vertex2D,   unsigned char>Mesh2D_LOW;
typedef Mesh<Vertex2D,  unsigned short>Mesh2D;
typedef Mesh<Vertex2D,    unsigned int>Mesh2D_HIGH;

typedef Mesh<Vertex3D,   unsigned char>Mesh3D_LOW;
typedef Mesh<Vertex3D,  unsigned short>Mesh3D;
typedef Mesh<Vertex3D,    unsigned int>Mesh3D_HIGH;
 



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

struct Vertex3D {
public:
	Vertex3D(glm::vec3 pos, glm::vec3 nor, glm::vec2 uv) {
		POSITION = pos;
		NORMAL = nor;
		TEXCOORD = uv;
	}
	glm::vec3 POSITION;
	glm::vec3 NORMAL;
	glm::vec2 TEXCOORD;
		
	static std::vector<VertexAttribute> GetLayout() {
		return std::vector<VertexAttribute> {
		VertexAttribute(0, 3, VertexAttributeType::FLOAT, false, sizeof(Vertex3D), 0),
		VertexAttribute(1,3,VertexAttributeType::FLOAT,true,sizeof(Vertex3D),sizeof(glm::vec3)),
		VertexAttribute(2,2,VertexAttributeType::FLOAT,false,sizeof(Vertex3D),sizeof(glm::vec3) * 2)
		};
	}

};

struct Vertex2D {

	Vertex2D(glm::vec2 pos, glm::vec2 uv) {
		POSITION = pos;
		TEXCOORD = uv;
	}
	glm::vec2 POSITION;
	glm::vec2 TEXCOORD;

	static std::vector<VertexAttribute> GetLayout() {
		return std::vector<VertexAttribute> {
		VertexAttribute(0, 2, VertexAttributeType::FLOAT, false, sizeof(Vertex2D), 0),
		VertexAttribute(1,2,VertexAttributeType::FLOAT,false,sizeof(Vertex2D),sizeof(glm::vec2)),
		
		};

	}
};

class BaseMesh {
public:
	ElementBuffer EBO = ElementBuffer(1 * sizeof(unsigned short), STATIC_DRAW);
	VertexBuffer VBO = VertexBuffer(1 * sizeof(glm::vec3), STATIC_DRAW);
	VertexArray VAO = VertexArray();
	int ElementCount = 0;
public:
	void Use() { VAO.Use(); }
	int GetTriangleCount() { return ElementCount; }
	BaseMesh() {
		VAO.BindEBO(&EBO);
		VAO.BindVBO(&VBO);

	};
	// virtual ~BaseMesh() {};
};

#define MeshTemplate template <class VertexDef, typename ElementType>
MeshTemplate
class GMesh :public BaseMesh{
	/*
	struct AABB {
		PosType Max;
		PosType Min;
		PosType Center;
		PosType Size;
	};
	*/

	std::vector<VertexAttribute>VertexAttributes = VertexDef::GetLayout();

	
	

	static std::vector<GMesh*> MeshRegistry;
public:
	GMesh() {
		ElementType maxvalue = ~(maxvalue & 0);
		Console::Log("Max Value " +to_string(maxvalue));
		EBO.ReInitialize(10 * sizeof(ElementType), STATIC_DRAW);
		VBO.ReInitialize(maxvalue * sizeof(VertexDef), STATIC_DRAW);//CHANGE DONT FORGET DICKHEAD
		

		VAO.BindVBO(&VBO);
		Console::Log(to_string(VertexAttributes.size()) + " Attributes");
		for (VertexAttribute attr : VertexAttributes) {
			Console::Log("Attribute at " + to_string(attr.index));
			VAO.EnableVertexAttribute(attr.index);
			Console::Log("Enabled");
			VAO.AssignVertexAttribute(attr.index, attr.vectorSize, attr.dataType, attr.Normalized, attr.Stride, (void*)attr.InitialStride);
		}
	}


	const int VertexArraySize = 999;
	
	void SetVerticies(VertexDef vs[],int Size) {
		Console::Log("Inserting " + to_string(Size));
		VBO.InsertData(0, sizeof(vs[0] ) * Size, vs);
	}
	void SetTriangles(ElementType ts[], int Size) {
		if (sizeof(ts[0]) * Size > EBO.GetSize()) EBO.ReInitialize(sizeof(ts[0]) * Size, STATIC_DRAW);
		EBO.InsertData(0, sizeof(ts[0]) * Size, ts);
		ElementCount = Size;
	}
	

};

/*
MeshTemplate
class Mesh: public GMesh<PosType,VertexDef, ElementType>{

	const int VArraySize = std::numeric_limits<ElementType>::max();
	VertexDef VERTICIES[VArraySize];
	std::vector<ElementType> ELEMENTS = std::vector<ElementType>();
};
*/




							//ONLY UNSIGNED BYTE,SHORT,INT				
typedef GMesh<Vertex2D,  unsigned char>GMesh2D_LOW;	
typedef GMesh<Vertex2D, unsigned short>GMesh2D;
typedef GMesh<Vertex2D,   unsigned int>GMesh2D_HIGH;

typedef GMesh<Vertex3D,  unsigned char>GMesh3D_LOW;
typedef GMesh<Vertex3D, unsigned short>GMesh3D;
typedef GMesh<Vertex3D,   unsigned int>GMesh3D_HIGH;
/*
typedef Mesh<glm::vec2,Vertex2D,   unsigned char>Mesh2D_LOW;
typedef Mesh<glm::vec2,Vertex2D,  unsigned short>Mesh2D;
typedef Mesh<glm::vec2,Vertex2D,    unsigned int>Mesh2D_HIGH;

typedef Mesh<glm::vec3,Vertex3D,   unsigned char>Mesh3D_LOW;
typedef Mesh<glm::vec3,Vertex3D,  unsigned short>Mesh3D;
typedef Mesh<glm::vec3,Vertex3D,    unsigned int>Mesh3D_HIGH;
 */



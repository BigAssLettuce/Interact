#include "Mesh.h"
#include <map>
bool Mesh3D::LoadFromOBJ(string file)
{

	string FileContent;
	if (!Resource::ReadTextFile(file, &FileContent)) return false;
	if (FileContent == "") return false;
	vector<Vertex3D> tempVerticies = vector<Vertex3D>();
	vector<ElementDataType> tempTriangles = vector<ElementDataType>();

	ParseOBJ(FileContent, &tempVerticies, &tempTriangles);
	SetVerticies(tempVerticies);
	SetTriangles(tempTriangles);
	return true;
}
vec3 ParseVec3Line(string line) {
	std::vector<std::string> LineContent = ParseString(line, ' ');
	float x = stof(LineContent[1]);
	float y = stof(LineContent[2]);
	float z = stof(LineContent[3]);
	return vec3(x, y, z);
}

void Mesh3D::ParseOBJ(string content, vector<Vertex3D>* vertexVector, vector<ElementDataType>* triangleVector)
{
	istringstream ss =istringstream( content);
	string line;
	vector<vec3> Positions = vector<vec3>();
	vector<vec3> Normals = vector<vec3>();
	vector<vec2> UVs = vector<vec2>();
	//0:pos 1:nor 2:UV 3:index

	vector<ivec3> VertexRegistry = vector<ivec3>();
	

	while (getline(ss, line)) {
		string first2 = line.substr(0, 2);

		if (first2 == "v ") {
			vec3 pos = ParseVec3Line(line);
			Positions.push_back(pos);
		}
		else if (first2 == "vn") {
			vec3 normal = ParseVec3Line(line);
			Normals.push_back(normal);
		}
		else if (first2 == "vt") {
			vec2 UV = (vec2)ParseVec3Line(line);
			UVs.push_back(UV);
		}
		else if (first2 == "f ") {
			vector<string> linecontent = ParseString(line, ' ');
			linecontent.erase(linecontent.begin());
			for (string desc : linecontent) {
				ivec3 vertexDescriptor;
				vector<string> values = ParseString(desc, '/');
				vertexDescriptor.x = stoi(values[0])-1; //pos
				vertexDescriptor.y = stoi(values[2])-1; //normal
				vertexDescriptor.z = stoi(values[1])-1; //UV

				//uvS THEN NORMALS IN TRIANGLE DESCRIPTIOR

				if (count(VertexRegistry.begin(),VertexRegistry.end(),vertexDescriptor) == 0) {
					//Debug::Log("found");
					triangleVector->push_back(VertexRegistry.size());
					VertexRegistry.push_back(vertexDescriptor);
				}
				else {
					//Debug::Log("registering");
					int indexof = findInVector<ivec3>(VertexRegistry, vertexDescriptor).second;
					triangleVector->push_back(indexof);
				}

			}
			
		}

	}

	for (ivec3 vertDesc : VertexRegistry) {
		//std::cout << to_string(vertDesc) << '\r';
		vertexVector->push_back(Vertex3D(Positions[vertDesc.x], Normals[vertDesc.y], UVs[vertDesc.z]));
		
	}
}

void Mesh3D::UpdateVertexBufferData()
{
	glBindVertexArray(VertexArrayObjectID);

	//meshdata
	glBindBuffer(GL_ARRAY_BUFFER, MeshDataBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * VERTICIES.size(), &VERTICIES[0], GL_STATIC_DRAW);



}

void Mesh3D::UpdateTriangleBufferData()
{
	//element data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshTrianglesBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElementDataType) * TRIANGLES.size(), &TRIANGLES[0], GL_STATIC_DRAW);
}

Mesh3D::Mesh3D()
{
	glGenVertexArrays(1, &VertexArrayObjectID);
	glCreateBuffers(1, &MeshDataBufferID);
	glCreateBuffers(1, &MeshTrianglesBufferID);
	Debug::Log("Mesh Buffers Created " + to_string(MeshDataBufferID) + "V:" + to_string(MeshTrianglesBufferID)+"T");
	glBindVertexArray(VertexArrayObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, MeshDataBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshTrianglesBufferID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);//POS
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex3D) , (void*)sizeof(vec3));//NORMALS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)(sizeof(vec3)*2));//UVS
	glBindVertexArray(0);
}

void Mesh3D::Use()
{
	glBindVertexArray(VertexArrayObjectID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshTrianglesBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, MeshDataBufferID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void Mesh3D::CleanUp()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

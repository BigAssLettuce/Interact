#include "Mesh.h"
#include <map>
#include "../../Core/Resource/Resource.h"
using namespace std;
using namespace glm;
vector<OldMesh3D*> OldMesh3D::MeshRegistry = vector<OldMesh3D*>();



static std::vector<std::string> Mesh3DParseString(std::string input, char separator) {
	std::string Current = "";
	std::vector<std::string> Total = {};
	for (int i = 0; i < input.length(); i++) {
		char CurrentLetter = input[i];
		if (CurrentLetter != separator) {
			Current += CurrentLetter;
		}
		else if (Current.length() > 0) {
			Total.push_back(Current);
			Current = "";

		}
	}

	if (Current.length() > 0) Total.push_back(Current);
	return Total;
}
bool OldMesh3D::LoadFromOBJ(string file, float scale)
{

	string FileContent;
	if (!Resource::ReadTextFile(file, &FileContent)) return false;
	if (FileContent == "") return false;
	vector<OldVertex3D> tempVerticies = vector<OldVertex3D>();
	vector<ElementDataType> tempTriangles = vector<ElementDataType>();

	ParseOBJ(FileContent, &tempVerticies, &tempTriangles);
	SetVerticies(tempVerticies);
	SetTriangles(tempTriangles);
	return true;
}

vec2 ParseVec2Line(string line) {
	std::vector<std::string> LineContent = Mesh3DParseString(line, ' ');
	float x = stof(LineContent[1]);
	float y = stof(LineContent[2]);
	return vec2(x, y);
}
vec3 ParseVec3Line(string line) {
	std::vector<std::string> LineContent = Mesh3DParseString(line, ' ');
	float x = stof(LineContent[1]);
	float y = stof(LineContent[2]);
	float z = stof(LineContent[3]);
	return vec3(x, y, z);
}
template < typename T>
static std::pair<bool, int > MeshfindInVector(const std::vector<T>& vecOfElements, const T& element)
{
	std::pair<bool, int > result;
	// Find given element in vector
	auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
	if (it != vecOfElements.end())
	{
		result.second = std::distance(vecOfElements.begin(), it);
		result.first = true;
	}
	else
	{
		result.first = false;
		result.second = -1;
	}
	return result;
}
void OldMesh3D::ParseOBJ(string content, vector<OldVertex3D>* vertexVector, vector<ElementDataType>* triangleVector, float scale)
{
	istringstream ss = istringstream(content);
	string line;
	vector<vec3> Positions = vector<vec3>();
	vector<vec3> Normals = vector<vec3>();
	vector<vec2> UVs = vector<vec2>();
	//0:pos 1:nor 2:UV 3:index

	vector<ivec3> VertexRegistry = vector<ivec3>();

	while (getline(ss, line)) {
		const string first2 = line.substr(0, 2);


		if (first2 == "v ") {
			vec3 pos = ParseVec3Line(line) * scale;
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
			vector<string> linecontent = Mesh3DParseString(line, ' ');
			linecontent.erase(linecontent.begin());
			for (string desc : linecontent) {
				ivec3 vertexDescriptor;
				vector<string> values = Mesh3DParseString(desc, '/');
				vertexDescriptor.x = stoi(values[0]) - 1; //pos
				vertexDescriptor.y = stoi(values[2]) - 1; //normal
				vertexDescriptor.z = stoi(values[1]) - 1; //UV

				//uvS THEN NORMALS IN TRIANGLE DESCRIPTIOR

				if (count(VertexRegistry.begin(), VertexRegistry.end(), vertexDescriptor) == 0) {
					//Debug::Log("found");
					triangleVector->push_back(VertexRegistry.size());
					VertexRegistry.push_back(vertexDescriptor);
				}
				else {
					//Debug::Log("registering");
					int indexof = MeshfindInVector<ivec3>(VertexRegistry, vertexDescriptor).second;
					triangleVector->push_back(indexof);
				}

			}

		}

	}
	for (ivec3 vertDesc : VertexRegistry) {
		//std::cout << to_string(vertDesc) << '\r';
		vertexVector->push_back(OldVertex3D(Positions[vertDesc.x], Normals[vertDesc.y], UVs[vertDesc.z]));

	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{

	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
void OldMesh3D::ParseMultiObj(string ObjContent, vector<ParsedMesh>* meshes,float Scale)
{

	istringstream ss = istringstream(ObjContent);
	string line;
	istringstream tempss = istringstream(ObjContent);
	int linecount = 0;
	while (getline(tempss, line)) {
		linecount++;
	}

	int currentline = 0;

	vector<vec3> Positions = vector<vec3>();
	vector<vec3> Normals = vector<vec3>();
	vector<vec2> UVs = vector<vec2>();
	vector<ivec3> VertexRegistry = vector<ivec3>();

	bool gotF = false;
	bool gotName = false;
	bool isgettingF = false;

	struct meshtoparse {
		string F;
		string Name;
		string GroupName;
		string Material;
	};
	vector<meshtoparse> meshestoparse = vector<meshtoparse>();
	meshtoparse currentmeshtoparse;
	int lastpercantage = 0;
	int updateiterate = 5;
	while (getline(ss, line)) {//REQUERES COMPLETE REWRITE, OBJ FILES VERTICIES ARE SHARED BETWEEN MESHES
		const string first2 = line.substr(0, 2);

		string linebeginning = "";
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == ' ') break;
			linebeginning += line[i];
		}
		currentline++;
		int percentage = (int)round(((float)currentline / (float)linecount) * 100)/ updateiterate;
		if (lastpercantage != percentage) {
			lastpercantage = percentage;
			std::cout <<" "<< (percentage * updateiterate) << "%" << '\r';
		}
		
		
		if (gotF && gotName&&!isgettingF) {
			meshestoparse.push_back(currentmeshtoparse);
			currentmeshtoparse = meshtoparse();
			gotF = false;
			gotName = false;
		 }

		if (linebeginning != "f") isgettingF = false;
		
		const char* first2c = linebeginning.c_str();
		switch (str2int(first2c))
		{
		case str2int("v"):
			vec3 pos = ParseVec3Line(line) * Scale;
			Positions.push_back(pos);
			break;
		case str2int("vn"):
			vec3 normal = ParseVec3Line(line);
			Normals.push_back(normal);
			break;
		case str2int("vt"):
			vec2 UV = (vec2)ParseVec2Line(line);
			UVs.push_back(UV);
			break;
		case str2int("o"):
			gotName = true; 
			currentmeshtoparse.Name = line.substr(2);
			break;
		case str2int("f"):
			gotF = true;
			isgettingF = true;
			currentmeshtoparse.F += line + "\n";
			break;
		case str2int("g"):
			currentmeshtoparse.GroupName = line.substr(2);
			break;
		}

		/*
		if (first2 == "v ") {
			vec3 pos = ParseVec3Line(line);
			Positions.push_back(pos);
		}
		else if (first2 == "vn") {
			vec3 normal = ParseVec3Line(line);
			Normals.push_back(normal);
		}
		else if (first2 == "vt") {
			vec2 UV = (vec2)ParseVec2Line(line);
			UVs.push_back(UV);
		}
		else if (first2 == "o ") { gotName = true; currentmeshtoparse.Name = line.substr(2); }
		else if (first2 == "f ") {
			gotF = true;
			isgettingF = true;
			currentmeshtoparse.F += line + "\n";
		}*/
	}
	if ((gotF && gotName && !isgettingF) || isgettingF) {
		meshestoparse.push_back(currentmeshtoparse);
		currentmeshtoparse = meshtoparse();
	}

	vector<ParsedMesh> giveback = vector<ParsedMesh>();
	for (meshtoparse parse : meshestoparse) {
		ParsedMesh parsedmesh = ParsedMesh();

		istringstream ss = istringstream(parse.F);
		vector<ivec3>VertexDescRegisry = vector<ivec3>();
		vector<ElementDataType>triangles = vector<ElementDataType>();
		vector<OldVertex3D>verticies = vector<OldVertex3D>();
		while (getline(ss, line)) {
			vector<string> linecontent = Mesh3DParseString(line, ' ');
			linecontent.erase(linecontent.begin());
			for (string desc : linecontent) {
				ivec3 vertexDescriptor;
				vector<string> values = Mesh3DParseString(desc, '/');
				vertexDescriptor.x = stoi(values[0]) - 1; //pos
				vertexDescriptor.y = stoi(values[2]) - 1; //normal
				vertexDescriptor.z = stoi(values[1]) - 1; //UV

				pair<bool, int> result = MeshfindInVector(VertexDescRegisry, vertexDescriptor);
				if (result.first) {
					triangles.push_back(result.second);
				}
				
				else {
					VertexDescRegisry.push_back(vertexDescriptor);
					triangles.push_back(verticies.size());
					verticies.push_back(OldVertex3D(Positions[vertexDescriptor.x], Normals[vertexDescriptor.y], UVs[vertexDescriptor.z]));
					

				}

			}
		}

		parsedmesh.verticies = verticies;
		parsedmesh.Triangles = triangles;
		parsedmesh.Group = parse.GroupName;
		parsedmesh.Name = parse.Name;
		std::cout << "Model Parsed: " << parsedmesh.Name <<  '\r';
		giveback.push_back(parsedmesh);
	}
	Console::Log(to_string(meshestoparse.size()) + "Meshes found");
	
	if (giveback.size() == 0) Console::Error("No meshes");
	else *meshes = giveback;
}

void OldMesh3D::UpdateVertexBufferData()
{

#ifndef NEWMESHTEST
	glBindVertexArray(VertexArrayObjectID);

	//meshdata
	glBindBuffer(GL_ARRAY_BUFFER, MeshDataBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(OldVertex3D) * VERTICIES.size(), &VERTICIES[0], GL_STATIC_DRAW);
	//Console::Log("Mesh vertex Buffer (" + to_string(MeshDataBufferID) + ") : " + ParseBytes(sizeof(Vertex3D) * VERTICIES.size()) );
#endif


}

void OldMesh3D::UpdateElementBufferData()
{
	//element data
#ifndef NEWMESHTEST
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshTrianglesBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElementDataType) * TRIANGLES.size(), &TRIANGLES[0], GL_STATIC_DRAW);
	//Console::Log("Mesh element Buffer (" + to_string(MeshTrianglesBufferID) + ") : " + ParseBytes(sizeof(ElementDataType) * TRIANGLES.size()) );
#endif


}

OldMesh3D::OldMesh3D()
{
	
#ifndef NEWMESHTEST
	glGenVertexArrays(1, &VertexArrayObjectID);
	glCreateBuffers(1, &MeshDataBufferID);
	glCreateBuffers(1, &MeshTrianglesBufferID);
	//Console::Log("Mesh Buffers Created " + to_string(MeshDataBufferID) + "V:" + to_string(MeshTrianglesBufferID) + "T");
	glBindVertexArray(VertexArrayObjectID);
	//glBindBuffer(GL_ARRAY_BUFFER, MeshDataBufferID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshTrianglesBufferID);
	glVertexArrayElementBuffer(VertexArrayObjectID, MeshTrianglesBufferID);
	Console::Log("Bound Element to vA" + to_string(MeshTrianglesBufferID));
	GLint boundElement;
	glGetVertexArrayiv(VertexArrayObjectID, GL_ELEMENT_ARRAY_BUFFER_BINDING,&boundElement);
	Console::Log("Value is " + to_string(boundElement));
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OldVertex3D), (void*)0);//POS
	glVertexArrayVertexAttribOffsetEXT(VertexArrayObjectID, MeshDataBufferID, 0, 3, GL_FLOAT, GL_FALSE, sizeof(OldVertex3D), 0);

	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(OldVertex3D), (void*)sizeof(vec3));//NORMALS
	glVertexArrayVertexAttribOffsetEXT(VertexArrayObjectID, MeshDataBufferID, 1, 3, GL_FLOAT, GL_TRUE, sizeof(OldVertex3D), sizeof(vec3));

	glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OldVertex3D), (void*)(sizeof(vec3) * 2));//UVS
	glVertexArrayVertexAttribOffsetEXT(VertexArrayObjectID, MeshDataBufferID, 2, 2, GL_FLOAT, GL_FALSE, sizeof(OldVertex3D), sizeof(vec3) * 2);

	glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
#else 
	VAO = VertexArray();
	VBO = VertexBuffer(MaxElementData, STATIC_DRAW);
	EBO = ElementBuffer(1, STATIC_DRAW);
#endif



	MeshRegistry.push_back(this);
}


void OldMesh3D::CalculateAABB()
{
	BOUNDS = Mesh3DAABB();
	
	BOUNDS.Max = vec3(-INFINITY);
	BOUNDS.Min = vec3(INFINITY);
	for (OldVertex3D vert : VERTICIES) {

		BOUNDS.Max = glm::max(BOUNDS.Max, vert.POSITION);
		BOUNDS.Min = glm::min(BOUNDS.Min, vert.POSITION);
	}

	BOUNDS.Center = (BOUNDS.Max + BOUNDS.Min) / 2.0f;
	BOUNDS.Size= BOUNDS.Max - BOUNDS.Min;



}


void OldMesh3D::Use()
{

	glBindVertexArray(VertexArrayObjectID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshTrianglesBufferID);
	//glBindBuffer(GL_ARRAY_BUFFER, MeshDataBufferID);

}

void OldMesh3D::CleanUp()
{
	glBindVertexArray(0);

}

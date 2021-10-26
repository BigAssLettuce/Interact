#include "Mesh.h"
#include <map>
vector<Mesh3D*> Mesh3D::MeshRegistry = vector<Mesh3D*>();
void Mesh3D::DrawDebugMenu(bool* open)
{

	if (ImGui::Begin("Mesh3D", open)) {
		for (Mesh3D* mesh : MeshRegistry) {
			string name = 'V' + to_string(mesh->MeshDataBufferID) + " T" + to_string(mesh->MeshTrianglesBufferID);
			if (ImGui::TreeNode(name.c_str())) {
				string vertString = "";
				string triString = "";
				for (Vertex3D vert : mesh->VERTICIES) vertString += to_string(vert.POSITION);
				for (ElementDataType tri : mesh->TRIANGLES) triString += std::to_string(tri);
				ImGui::Text(vertString.c_str());
				ImGui::Separator();
				ImGui::Text(triString.c_str());
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}
}
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
vec2 ParseVec2Line(string line) {
	std::vector<std::string> LineContent = ParseString(line, ' ');
	float x = stof(LineContent[1]);
	float y = stof(LineContent[2]);
	return vec2(x, y);
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

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
void Mesh3D::ParseMultiObj(string ObjContent, vector<ParsedMesh>* meshes,float Scale)
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
		vector<Vertex3D>verticies = vector<Vertex3D>();
		while (getline(ss, line)) {
			vector<string> linecontent = ParseString(line, ' ');
			linecontent.erase(linecontent.begin());
			for (string desc : linecontent) {
				ivec3 vertexDescriptor;
				vector<string> values = ParseString(desc, '/');
				vertexDescriptor.x = stoi(values[0]) - 1; //pos
				vertexDescriptor.y = stoi(values[2]) - 1; //normal
				vertexDescriptor.z = stoi(values[1]) - 1; //UV

				pair<bool, int> result = findInVector(VertexDescRegisry, vertexDescriptor);
				if (result.first) {
					triangles.push_back(result.second);
				}
				
				else {
					VertexDescRegisry.push_back(vertexDescriptor);
					triangles.push_back(verticies.size());
					verticies.push_back(Vertex3D(Positions[vertexDescriptor.x], Normals[vertexDescriptor.y], UVs[vertexDescriptor.z]));
					

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

void Mesh3D::UpdateVertexBufferData()
{
	glBindVertexArray(VertexArrayObjectID);

	//meshdata
	glBindBuffer(GL_ARRAY_BUFFER, MeshDataBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * VERTICIES.size(), &VERTICIES[0], GL_STATIC_DRAW);
	Console::Log("Mesh vertex Buffer (" + to_string(MeshDataBufferID) + ") : " + ParseBytes(sizeof(Vertex3D) * VERTICIES.size()) );



}

void Mesh3D::UpdateElementBufferData()
{
	//element data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshTrianglesBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElementDataType) * TRIANGLES.size(), &TRIANGLES[0], GL_STATIC_DRAW);
	Console::Log("Mesh element Buffer (" + to_string(MeshTrianglesBufferID) + ") : " + ParseBytes(sizeof(ElementDataType) * TRIANGLES.size()) );
}

Mesh3D::Mesh3D()
{
	MeshRegistry.push_back(this);
	glGenVertexArrays(1, &VertexArrayObjectID);
	glCreateBuffers(1, &MeshDataBufferID);
	glCreateBuffers(1, &MeshTrianglesBufferID);
	//Console::Log("Mesh Buffers Created " + to_string(MeshDataBufferID) + "V:" + to_string(MeshTrianglesBufferID) + "T");
	glBindVertexArray(VertexArrayObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, MeshDataBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshTrianglesBufferID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);//POS
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex3D), (void*)sizeof(vec3));//NORMALS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)(sizeof(vec3) * 2));//UVS
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

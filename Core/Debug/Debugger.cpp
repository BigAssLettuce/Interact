#include "Debugger.h"
#include "../Application/MainWindow.h"

Debugger* Debugger::instance;
std::thread Debugger::debugThread;
bool Debugger::ShouldShutdown;
GLFWwindow* Debugger::DebugWindowPointer;

unsigned int Debugger::CurrentSelectionMemmorySize = 0;
unsigned int Debugger::CurrentTypeMemorySize = 1;
Debugger* Debugger::getInstance() {
	if (!instance) 
	{ 
		debugThread = std::thread(Debugger());
		
	} 
	return instance;
}


void Debugger::ShutDown()
{
	ShouldShutdown = true; 
	debugThread.join();
}
#include "../Application/Application.h"
#include"../Texture/Texture2D.h"
void Debugger::TexturesDebug() {
	static float Divisor = 0.5f;
	ImGui::PushItemWidth(ImGui::GetWindowSize().x);
	ImGui::SliderFloat("##r", &Divisor, 0, 1,"");

	ImGui::BeginChild("ChildL", ImVec2(ImGui::GetWindowContentRegionWidth() * Divisor, ImGui::GetContentRegionAvail().y), false);


	static ImGuiTableFlags flags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;

	enum TexturesColumnID
	{
		Name,
		ID,
		TYPE,
		SIZE,
	};
	static int SelectedTexture = -1;
	static int LastSelection = -1;
	if (ImGui::BeginTable("Textures", 4, flags)) {
		ImGuiTableColumnFlags tableflags = ImGuiTableColumnFlags_None;
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthStretch, 0.25f, Name);
		ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthStretch, 0.25f, ID);
		ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthStretch, 0.25f, TYPE);
		ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthStretch, 0.0f, SIZE);
		ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
		ImGui::TableHeadersRow();

		ImGuiSelectableFlags selectflags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;

		for (int i = 0; i < Texture2D::TEXTURES.size(); i++)
		{
			Texture2D* texture = Texture2D::TEXTURES[i];
			ImGui::PushID("Name");
			ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
			ImGui::TableSetColumnIndex(0);
			bool selected = false;
			if (SelectedTexture == i) selected = true;

			if (ImGui::Selectable(to_string(texture->TextureID).c_str(), selected, selectflags)) {
				SelectedTexture = i;
			}
			ImGui::TableNextColumn();

			ImGui::Text(to_string(texture->TextureID).c_str());
			ImGui::TableNextColumn();
			ImGui::Text("2D");
			ImGui::TableNextColumn();
			glm::vec2 texSize = texture->Size;
			stringstream x;
			x << std::fixed << std::setprecision(0) << texSize.x;
			stringstream y;
			y << std::fixed << std::setprecision(0) << texSize.y;
			string sizeline = x.str() + ", " + y.str();
			ImGui::Text(to_string(texture->FileSizeInBytes).c_str());
			//ImGui::Text("Some Size");
			ImGui::PopID();
		}


		ImGui::EndTable();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
	ImGui::BeginChild("Texture View", ImVec2(0, 0), true);

	static GLuint PrevTexture = -1;
	if (PrevTexture==-1) glGenTextures(1, &PrevTexture);

	static Texture2D PreviewTexture = Texture2D();
	if (SelectedTexture >= 0) {
		ImVec2 childsize = ImGui::GetContentRegionAvail();
		Texture2D* tex = Texture2D::TEXTURES[SelectedTexture];

		if (SelectedTexture != LastSelection) {
			PreviewTexture.LoadTexture2D(tex->File);
			//HGLRC debuggercontext = wglGetCurrentContext();
			//wglCopyImageSubDataNV(Application::WGLContext, tex->TextureID, GL_TEXTURE_2D, 0, tex->Size.x, tex->Size.y, 1, debuggercontext, PreviewTexture.TextureID, GL_TEXTURE_2D, 0, tex->Size.x, tex->Size.y, 1, tex->Size.x, tex->Size.y, 1);

			LastSelection = SelectedTexture;
		}


		ImTextureID texID = ImTextureID(PreviewTexture.TextureID);
		ImGui::Text(to_string(tex->TextureID).c_str());
		ImGui::Image(texID, ImVec2(childsize.x, childsize.x));
		string fileline = "File: " + tex->File;
		ImGui::Text(fileline.c_str());
	}

	ImGui::EndChild();
	ImGui::PopStyleVar();
	/*
	ImGui::Begin("Textures");
	int i = 0;
	int texturecount = TEXTURES.size();
	//float size[texturecount];
	for (Texture* tex : TEXTURES) {
		if (ImGui::TreeNode(to_string(tex->TextureID).c_str())) {

			ImVec2 Winsize = ImGui::GetWindowSize();
			int border = 20;
			static float size = 25;
			string name = "Size" + string("##") + to_string(i);
			i++;
			ImGui::SliderFloat(name.c_str(), &size, 1, std::min(Winsize.x, Winsize.y));



			float aspectratio = tex->Size.x / tex->Size.y;

			ImTextureID imtex = ImTextureID(tex->TextureID);
			//ImVec2(size - border, (size - border) * aspectratio)

			ImGui::Image(imtex, ImVec2(std::max(1.0f, size * aspectratio - border), std::max(1.0f, size - border)), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));

			ImGui::TreePop();
		}

	}
	ImGui::End();
	*/
}

#include "../../Modules/Mesh/Mesh.h"

void Debugger::MeshesDebug()
{
	static float Divisor = 0.5f;
	ImGui::PushItemWidth(ImGui::GetWindowSize().x);
	//ImGui::PushStyleVar(ImGuiStyleVar_thic)
	ImGui::SliderFloat("##r", &Divisor, 0, 1,"");

	ImGui::BeginChild("ChildL", ImVec2(ImGui::GetWindowContentRegionWidth() * Divisor, ImGui::GetContentRegionAvail().y), false);


	static ImGuiTableFlags flags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;

	enum TexturesColumnID
	{
		Name,
		VCount,
		ECount,
		VID,
		EID,
		
	};
	static int SelectedMesh = -1;
	static int LastSelection = -1;
	if (ImGui::BeginTable("Meshes", 5, flags)) {
		ImGuiTableColumnFlags tableflags = ImGuiTableColumnFlags_None;
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthStretch, 0.4f, Name);
		ImGui::TableSetupColumn("Verticies", ImGuiTableColumnFlags_WidthStretch, 0.25f, VCount);
		ImGui::TableSetupColumn("Elements (T)", ImGuiTableColumnFlags_WidthStretch, 0.25f, ECount);
		ImGui::TableSetupColumn("V ID", ImGuiTableColumnFlags_WidthStretch, 0.05f, VID);
		ImGui::TableSetupColumn("T ID", ImGuiTableColumnFlags_WidthStretch, 0.05f, EID);
		ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
		ImGui::TableHeadersRow();


		ImGuiSelectableFlags selectflags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;

		for (int i = 0; i < OldMesh3D::MeshRegistry.size(); i++)
		{
			OldMesh3D* mesh = OldMesh3D::MeshRegistry[i];
			ImGui::PushID("Name");
			ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
			ImGui::TableSetColumnIndex(0);
			bool selected = false;
			if (SelectedMesh == i) selected = true;

			if (ImGui::Selectable(mesh->Name.c_str(), selected, selectflags)) {
				SelectedMesh = i;
			}
			ImGui::TableNextColumn();

			ImGui::Text(to_string(mesh->VERTICIES.size()).c_str());
			ImGui::TableNextColumn();
			int TSize = mesh->TRIANGLES.size();
			string ElementColumn = to_string(TSize) + " (" + to_string(TSize / 3) +")";
			ImGui::Text(ElementColumn.c_str());
			ImGui::TableNextColumn();

			ImGui::Text(to_string(mesh->MeshDataBufferID).c_str());
			ImGui::TableNextColumn();
			ImGui::Text(to_string(mesh->MeshTrianglesBufferID).c_str());
			//ImGui::Text("Some Size");
			ImGui::PopID();
		}


		ImGui::EndTable();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
	
	ImGui::BeginChild("Mesh Data", ImVec2(0, 0), true);
	int xSize = ImGui::GetContentRegionAvail().x;
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
	ImGui::BeginChild("Mesh VIew", ImVec2(xSize, xSize), true);

	ImGui::EndChild();
	ImGui::PopStyleVar();
	/*
	static GLuint PrevTexture = -1;
	if (PrevTexture == -1) glGenTextures(1, &PrevTexture);
	static Texture2D PreviewTexture = Texture2D();
	if (SelectedMesh >= 0) {
		ImVec2 childsize = ImGui::GetContentRegionAvail();
		Texture2D* tex = Texture2D::TEXTURES[SelectedMesh];

		if (SelectedMesh != LastSelection) {
			PreviewTexture.LoadTexture2D(tex->File);

			//Once GLX is added use GLX_NV_COPY_IMAGE

			
			//glFinish();
			//glfwMakeContextCurrent(Window::GlWindowPointer);

			//GLint ActiveTexture;
			//glGetIntegerv(GL_ACTIVE_TEXTURE, &ActiveTexture);

			//glBindTexture(GL_TEXTURE_2D,tex->TextureID);

			//int size = tex->Size.x * tex->Size.y * tex->ChannelsInFile;
			//unsigned char* image = nullptr;
			//GLubyte* pixels;
			//pixels = (GLubyte*)malloc(size * sizeof(GLubyte));

			//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(pixels));
			//Console::Log(to_string(IM_ARRAYSIZE(pixels)));
			//Console::Log(to_string(sizeof(*image)));
			//glBindTexture(GL_TEXTURE_2D,ActiveTexture);
			//glFinish();

			//glfwMakeContextCurrent(DebugWindowPointer);
			//glBindTexture(GL_TEXTURE_2D, PreviewTexture.TextureID);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex->Size.x, tex->Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(pixels));
			//glGenerateMipmap(GL_TEXTURE_2D);
			//delete[] pixels;

			//glCopyImageSubDataNV(Window::GlWindowPointer,tex->TextureID,GL_TEXTURE_2D,0,0,0,0,DebugWindowPointer,PrevTexture,GL_TEXTURE_2D,0,0,0,0,tex->Size.x,tex->Size.y,1);
			//glCopyImageSubData
			
			LastSelection = SelectedMesh;
		}


		ImTextureID texID = ImTextureID(PreviewTexture.TextureID);
		ImGui::Text(to_string(tex->TextureID).c_str());
		ImGui::Image(texID, ImVec2(childsize.x, childsize.x));
		string fileline = "File: " + tex->File;
		ImGui::Text(fileline.c_str());
		
	}
	*/

	ImGui::EndChild();
	
}
#include "../../Modules/Light/LightManager.h"

#ifdef MODULE_LIGHT
bool LightTableParser( const char* Type, const char* Color, const char* Intensity,int index,int Selection ) {
	static ImGuiSelectableFlags selectflags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;
	bool returnb = false;
	ImGui::PushID(index);
	ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
	ImGui::TableSetColumnIndex(0);

	bool selected = false;
	if (Selection == index) selected = true;

	if (ImGui::Selectable(Type, selected, selectflags)) {
		Selection = index;
		returnb = true;

	}
	ImGui::TableNextColumn();
	ImGui::Text(Color);
	ImGui::TableNextColumn();
	ImGui::Text(Intensity);
	ImGui::PopID();
	return returnb;
}
void Debugger::LightsDebug()
{
	static int EditorSize = 95;
	ImVec2 RegionAvail = ImGui::GetContentRegionAvail();
	bool DisplayControls = false;
	static int Selection = -1;
	if (Selection != -1) {
		DisplayControls = true; 
		RegionAvail.y -= EditorSize;
	
	}
	ImGui::BeginChild("Table",RegionAvail);
	static ImGuiTableFlags TableFlags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;
	ImGui::BeginTable("Light Table", 3, TableFlags);

	ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthStretch, 0.33f, 0);
	ImGui::TableSetupColumn("Color", ImGuiTableColumnFlags_WidthStretch, 0.33f, 2);
	ImGui::TableSetupColumn("Intensity", ImGuiTableColumnFlags_WidthStretch, 0.33f, 2);
	ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
	ImGui::TableHeadersRow();

	static ImGuiSelectableFlags selectflags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;


	LightManager* lmInstance = LightManager::GetInstance();
	static unsigned short SelectedLightType = -1;
	static PointLight* selectedPointLight;
	int LightCount = 0;
	for (int i = 0; i < lmInstance->PointLightCount; i++) {
		PointLight* pLight = &lmInstance->PointLights[i];
		if (LightTableParser("Point", to_string(pLight->Color).c_str(), to_string(pLight->Intensity).c_str(), LightCount, Selection)) {
			Selection = LightCount;
			SelectedLightType = 0;
			selectedPointLight = pLight;
		}
		LightCount++;
	}

	static DirectionalLight* selectedDLight;

	for (int i = 0; i < lmInstance->DirectionalLightCount; i++) {
		DirectionalLight* DLight = &lmInstance->DirectionalLights[i];


		if (LightTableParser("Directional", to_string(DLight->Color).c_str(), to_string(DLight->Intensity).c_str(), LightCount, Selection)) {
			Selection = LightCount;
			SelectedLightType = 1;
			selectedDLight = DLight;
		}

		LightCount++;
	}
	ImGui::EndTable();


	ImGui::EndChild();
	
	static ImGuiSliderFlags SliderFlags = ImGuiSliderFlags_ClampOnInput;
	if (DisplayControls) {
		ImGui::BeginChild("Controls", ImVec2(0, 0), true);
		switch (SelectedLightType)
		{
		case 0:
			EditorSize = 155;
			ImGui::DragFloat3("Pos", &selectedPointLight->Pos.x, 0.1f, -INFINITY, INFINITY);
			ImGui::SameLine();
			ImGui::Button("Delete");
			ImGui::ColorEdit3("Color", &selectedPointLight->Color.x);
			ImGui::DragFloat("Intensity", &selectedPointLight->Intensity, 0.1f, 0,INFINITY,"%.1f",SliderFlags);
			ImGui::DragFloat("Radius", &selectedPointLight->Radius, 0.1f, 0, INFINITY, "%.1f", SliderFlags);
			ImGui::DragFloat("Range", &selectedPointLight->Range, 0.1f, 0, INFINITY, "%.1f", SliderFlags);
			//selectedPointLight->Range = max(selectedPointLight->Range, selectedPointLight->Radius);
			ImGui::DragFloat("Attentuation", &selectedPointLight->Attentuation, 0.1f, 0, INFINITY, "%.1f", SliderFlags);
			break;
		case 1:
			EditorSize = 70;
			ImGui::ColorEdit3("Color", &selectedDLight->Color.x);
			ImGui::DragFloat("Intensity", &selectedDLight->Intensity, 0.1f, 0);

			if (ImGui::SliderFloat3("Direction", &selectedDLight->Direction.x, -1, 1)) {
				selectedDLight->Direction = glm::normalize(selectedDLight->Direction);
			}
			

			break;
		default:
			break;
		}
		ImGui::EndChild();
	}
	

}
#endif 
void Debugger::RendersDebug()
{

}



#include"../Shader/Shader.h"

static int ShaderInputCallback(ImGuiInputTextCallbackData* data)
{
	if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
	{
		data->InsertChars(data->CursorPos, "..");
	}
	else if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
	{
		if (data->EventKey == ImGuiKey_UpArrow)
		{
			data->DeleteChars(0, data->BufTextLen);
			data->InsertChars(0, "Pressed Up!");
			data->SelectAll();
		}
		else if (data->EventKey == ImGuiKey_DownArrow)
		{
			data->DeleteChars(0, data->BufTextLen);
			data->InsertChars(0, "Pressed Down!");
			data->SelectAll();
		}
	}
	else if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit)
	{
		// Toggle casing of first character
		char c = data->Buf[0];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) data->Buf[0] ^= 32;
		data->BufDirty = true;

		// Increment a counter
		int* p_int = (int*)data->UserData;
		*p_int = *p_int + 1;
		Console::Log("Edit Callback");
	}
	return 0;
}
string ShaderTypeName(ShaderTypes type) {
	switch (type)
	{
	case VERTEX:
		return string("Vertex");
		break;
	case FRAGMENT:
		return string("Fragment");
		break;

	default:
		string("Add Name Conv");
		break;
	}
}

float Clamp(float V, float L, float H) {
	return min(max(L, V), H);
}

void Debugger::ShadersDebug()
{
	
	float sliderWidth = 15;
	ImVec2 contentavail = ImGui::GetContentRegionAvail();
	ImVec2 holdersize = ImVec2(contentavail.x - sliderWidth, contentavail.y);

	static float VDivisor = 0.75;
	ImGui::BeginChild("Holder", holdersize, false,ImGuiWindowFlags_NoScrollbar);

	ImVec2 HolderContentSize = ImGui::GetContentRegionAvail();

	ImGui::BeginChild("ShaderList",ImVec2(0, HolderContentSize.y*(1- Clamp(VDivisor,0.05f,0.95f))),false);
	static float HDisivor = 0.6;
	ImVec2 ListAvailSize = ImGui::GetContentRegionAvail();
	ImGui::PushItemWidth(ListAvailSize.x);
	ImGui::SliderFloat("##r", &HDisivor, 0, 1, "");
	ImGui::PopItemWidth();
#pragma region Table
	ImGui::BeginChild("Table Child", ImVec2(ListAvailSize.x * HDisivor, 0), false);
	//name Parts
	static ImGuiTableFlags TableFlags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;

	ImGui::BeginTable("Shader Programs", 3, TableFlags);

	ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthStretch, 0.33f, 0);
	ImGui::TableSetupColumn("ProgramID", ImGuiTableColumnFlags_WidthStretch, 0.33f, 1);
	ImGui::TableSetupColumn("Parts", ImGuiTableColumnFlags_WidthStretch, 0.33f, 2);
	ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
	ImGui::TableHeadersRow();



	static int SelectedShaderIndex = -1;
	static int LastSelection = -1;
	vector<Shader*> Shaders = Shader::SHADERS;
	static ImGuiSelectableFlags selectflags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;
	for (int i = 0; i < Shaders.size(); i++) {
		Shader* shader = Shaders[i];
		string ID = shader->Name.c_str() + string("##") + to_string(i);
		ImGui::PushID(shader->shaderProgramID);
		ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
		ImGui::TableSetColumnIndex(0);
		bool selected = false;
		if (SelectedShaderIndex == i) selected = true;
		
		if (ImGui::Selectable(shader->Name.c_str(), selected, selectflags)) {
			SelectedShaderIndex = i;
		}

		ImGui::TableNextColumn();
		ImGui::Text(to_string(shader->shaderProgramID).c_str());
		ImGui::TableNextColumn();
		ImGui::Text(to_string(shader->ShaderParts.size()).c_str());
		ImGui::PopID();

	}

	ImGui::EndTable();
	ImGui::EndChild();
#pragma endregion
	ImGui::SameLine();


	
	string currentEdit;
	static vector<ShaderPart> Parts;
	Shader* selectedShader;
	if (LastSelection != SelectedShaderIndex) {
		selectedShader = Shaders[SelectedShaderIndex];
		string content = selectedShader->ShaderParts[0].Content;
		currentEdit = content;
		Parts = selectedShader->ShaderParts;
	}
	 

#pragma region ShaderPreview
	ImGui::BeginChild("Shader Preview", ImVec2(0, 0), true);
	ImGui::EndChild();
#pragma endregion

	ImGui::EndChild();


	
	ImGuiWindowFlags editorFlags = ImGuiWindowFlags_MenuBar;
	ImGui::BeginChild("Shader Editor",ImVec2(0,0),true, editorFlags);
	ImGui::BeginMenuBar();
	ImGui::EndMenuBar();
	static bool AutoCompile = true;
	ImGui::Checkbox("Auto Compile", &AutoCompile);

	ImGui::BeginTabBar("Shader Parts", ImGuiTabBarFlags_Reorderable);
	for (ShaderPart part : Parts) {
		if (ImGui::BeginTabItem(ShaderTypeName(part.Type).c_str())) {
			static ImGuiInputTextFlags tFlags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_AlwaysOverwrite;
			ImGui::InputTextMultiline("##i", &part.Content[0], part.Content.length(), ImGui::GetContentRegionAvail(), tFlags, ShaderInputCallback);

			ImGui::EndTabItem();
		}
	}
	
	ImGui::Text(to_string(SelectedShaderIndex).c_str());
	
	//ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
	ImGui::EndTabBar();

	ImGui::EndChild();

	ImGui::EndChild();
	ImGui::SameLine();
	
	
	ImGui::VSliderFloat("##T", ImVec2(sliderWidth, ImGui::GetContentRegionAvail().y), &VDivisor, 0, 1,"");
}
#include "../RenderAPI/Buffers/Buffer.h"
#include "../RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"


static string BufferTypesParser(BufferTypes bufferType) {
	switch (bufferType)
	{
	case UNIFORM:
		return "Uniform";
	case ARRAY:
		return "Array";
	case ELEMENT:
		return "Element";
	default:
		Console::Log(to_string(bufferType));
		return "Parse not added";
	}
	//bufferPtr->GetType();
}
void Debugger::BuffersDebug()
{
	static ImGuiTableFlags TableFlags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;
	ImGui::BeginTable("Shader Programs", 3, TableFlags);

	ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthStretch, 0.33f, 0);
	ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthStretch, 0.33f, 1);
	ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthStretch, 0.33f, 2);
	ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
	ImGui::TableHeadersRow();

	static ImGuiSelectableFlags selectflags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;

	static int Selection = -1;
	CurrentTypeMemorySize = 0;
	int i = 0;
	for (Buffer* buffer : Buffer::BUFFERS) {
		CurrentTypeMemorySize += buffer->BufferSize;
		ImGui::PushID(buffer->BufferID);
		ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
		ImGui::TableSetColumnIndex(0);
		bool selected = false;
		if (Selection == i) selected = true;

		if (ImGui::Selectable(to_string(buffer->BufferID).c_str(), selected, selectflags)) {
			CurrentSelectionMemmorySize = buffer->BufferSize;
			Selection = i;
		}
		//ImGui::Text(to_string(buffer->BufferID).c_str());
		ImGui::TableNextColumn();
		ImGui::Text(BufferTypesParser(buffer->BufferType).c_str());
		ImGui::TableNextColumn();
		ImGui::Text(DebuggerParseBytes(buffer->BufferSize).c_str());
		ImGui::PopID();
		i++;
	}
	

	static int LastSelection = -1;
	if (LastSelection != Selection) {

	}

	ImGui::EndTable();
}

static GLint ExtensionCount;
static int nthOccurrenceDebugger(const std::string& str, const std::string& findMe, int nth)
{
	size_t  pos = 0;
	int     cnt = 0;

	while (cnt != nth)
	{
		pos += 1;
		pos = str.find(findMe, pos);
		if (pos == std::string::npos)
			return -1;
		cnt++;
	}
	return pos;
}
static bool GotAllExtensions = false;
struct Extension {
	string Name;
	string Type = "Undefined";
};
static vector<Extension> Extensions = vector<Extension>();
static void GetExtensionsDebug() {
	GotAllExtensions = true;

	glGetIntegerv(GL_NUM_EXTENSIONS, &ExtensionCount);
	PFNGLGETSTRINGIPROC glGetStringi = 0;
	

	glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");
	for (GLint i = 0; i < ExtensionCount; i++)
	{
		Extension ext = Extension();
		const char* extensionName =
			(const char*)glGetStringi(GL_EXTENSIONS, i);
		ext.Name = extensionName;
		int from = nthOccurrenceDebugger(extensionName, "_", 1) + 1;
		int count = nthOccurrenceDebugger(extensionName, "_", 2) - from;
		ext.Type = string(extensionName).substr(from,count);
		Extensions.push_back(ext);
	}
}



void Debugger::ExtensionsDebug()
{
	if (!GotAllExtensions)GetExtensionsDebug();

	static ImGuiTableFlags TableFlags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;
	ImGui::BeginTable("Extensions", 2, TableFlags);


	ImGui::TableSetupColumn("Extension", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthStretch, 0.8f, 0);
	ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthStretch, 0.2f, 1);
	ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
	ImGui::TableHeadersRow();
	for (int i = 0; i < ExtensionCount; i++) {
		Extension ext = Extensions[i];

		ImGui::PushID(ext.Name.c_str());
		ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(ext.Name.c_str());
		ImGui::TableNextColumn();
		ImGui::Text(ext.Type.c_str());
		ImGui::PopID();
	}
	
	ImGui::EndTable();
}
#include "../../Modules/ECS/Entity.h"
#include <typeinfo>

void Debugger::ECSDebug()
{
	static ImGuiTableFlags flags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable |ImGuiTableFlags_Hideable| ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;

	if (ImGui::BeginTable("Entities", 1, flags)) {
		ImGui::TableSetupColumn("Entity", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthStretch, 0.8f, 0);
		ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
		ImGui::TableHeadersRow();

		static ImGuiSelectableFlags selectflags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;

		static Entity* Selection = nullptr;

		for (Entity* entity : Entity::ENTITIES) {
			string EntityTypeName = string(typeid(*entity).name());
			EntityTypeName = EntityTypeName.substr(6);
			const char* Name = EntityTypeName.c_str();

			ImGui::PushID(entity);
			ImGui::TableNextRow(ImGuiTableRowFlags_None, 20);
			ImGui::TableSetColumnIndex(0);
			bool selected = false;
			if (Selection == entity) selected = true;

			if (ImGui::Selectable(Name, selected, selectflags)) {
				Selection = entity;
			}
			//ImGui::Text(Name);
			ImGui::PopID();

		}
		ImGui::EndTable();
		//ImGui::BeginChild("Entity Debug", ImVec2(0, 0), true);
		if (Selection) Selection->DebugMenu();
		//ImGui::EndChild();
	}
	

	
}

void Debugger::WindowDebug()
{
}

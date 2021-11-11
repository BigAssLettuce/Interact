#pragma once
#include "../../Dependencies/GL/GLEW/include/GL/glew.h"
#include "../../Dependencies/GL/GLFW/include/GLFW/glfw3.h"

#include "../../Dependencies/glm-master/glm/glm.hpp"
#include "../../Dependencies/glm-master/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm-master/glm/gtc/quaternion.hpp"
#include "../../Dependencies/glm-master/glm/gtx/quaternion.hpp"
#include "../../Dependencies/glm-master/glm/gtx/string_cast.hpp"
#include "../../Dependencies/glm-master/glm/common.hpp"
#include "../../Dependencies/glm-master/glm/gtc/type_ptr.hpp"

#include "../../Dependencies/Imgui/imgui.h"
#include "../../Dependencies/Imgui/imgui_impl_glfw.h"
#include "../../Dependencies/Imgui/imgui_impl_opengl3.h"

#include <thread>
#include <iostream>
#include <sstream>
#include "Console.h"
#include <iomanip>
#include "../Application/MainWindow.h"

#define DEBUGGER_DEBUG
static void DebugThreadWindowResizeCallback(GLFWwindow* window, int width, int height)
{
	//Console::Log("Size:" + to_string(width) + " " + to_string(height));
	glViewport(0, 0, width, height);
}


//#define DEBUGGER_DEBUG
#include "Gizmos/Gizmos.h"
static class Debugger
{
	static void DebuggerdebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar* message, const void* userParam)
	{
		string log = "[OpenGL]: (source: " + std::to_string(source) + string(") ") + message;
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			Console::Critical(log);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			Console::Error(log);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			Console::Warning(log);

			break;
#ifdef OPENGL_DEBUGMODE_SEVERITY_ALL

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			Console::Log(log);
			break; //NOTIFICATIONS ARE ACTUAL NOTIFICATIONS. USUALLY NOT IMPORTANT
#endif

		}


	}
	ImColor AppStuff = ImColor(0, 0, 1, 0);
	ImColor LowAbstraction;
	ImColor HighAbstraction;
	
	static Debugger* instance;

	static std::thread debugThread;
	static GLFWwindow* DebugWindowPointer;
	static bool ShouldShutdown;

	static void TexturesDebug();
	static void ShadersDebug();
	static void BuffersDebug();
	static void ExtensionsDebug();

	static void MeshesDebug();
	static void LightsDebug();
	static void RendersDebug();
	static void ECSDebug();
public:
	static Debugger* getInstance();
	static void ShutDown();
	static unsigned int CurrentSelectionMemmorySize;
	static unsigned int CurrentTypeMemorySize;
	Debugger() {
		
		instance = this;
		ShouldShutdown = false;

	}
	void operator()() const
	{

		#pragma region Init
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


				glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

				glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

					#ifdef DEBUGGER_DEBUG
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
					#endif
				int WinSizeX = 400;
				int WinSizeY =  600;
				DebugWindowPointer = glfwCreateWindow(WinSizeX, WinSizeY, "Interact Debugger", NULL, NULL);

				if (!DebugWindowPointer) assert("Debug Window Failed to open");
				int MonitorCount;
				GLFWmonitor** monitors = glfwGetMonitors(&MonitorCount);

				
				if (MonitorCount>1) {
					GLFWmonitor* secondmonitor = monitors[1];
					int secXpos, secYpos;
					glfwGetMonitorPos(secondmonitor, &secXpos, &secYpos);
					int secXsize, secYsize;
					const GLFWvidmode* secVideoMode = glfwGetVideoMode(secondmonitor);

					glfwSetWindowPos(DebugWindowPointer, secXpos + secVideoMode->width / 2 - WinSizeX / 2, secYpos + secVideoMode->height / 2 - WinSizeY / 2);
				}
				

				if (GL_NV_copy_image)Console::Log("GL_NV_copy_image Supported by GPU. Not that it Helps in anyway given that it cant do what i need it to do. i want GLX_NV_copy_image",COLORS::GREEN);
				//else Console::Log("GL_NV_copy_image Not Supported by GPU", COLORS::RED);


				glfwMakeContextCurrent(DebugWindowPointer);
				#ifdef DEBUGGER_DEBUG
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(DebuggerdebugMessage, NULL);

				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
				#endif
				glfwSetWindowSizeCallback(DebugWindowPointer, &DebugThreadWindowResizeCallback);
				glfwSwapInterval(1);

				IMGUI_CHECKVERSION();
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO();

				ImGui_ImplGlfw_InitForOpenGL(DebugWindowPointer, true);
				ImGui_ImplOpenGL3_Init();
		#pragma endregion


		
		while (!ShouldShutdown)
		{
			#pragma region PrepareFrame
						glClear(GL_COLOR_BUFFER_BIT);
						ImGui_ImplOpenGL3_NewFrame();
						ImGui_ImplGlfw_NewFrame();
						ImGui::NewFrame();

			#pragma endregion

			
			static bool ConsoleOpen = true;
			static bool TexturesOpen = false;
			static bool MeshesOpen = false;
			static bool ShadersOpen = false;
			static bool BuffersOpen = false;
			static bool LightsOpen = false;
			static bool ExtensionsOpen = false;
			static bool RendersOpen = true;
			static bool ECSOpen = true;

			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("Actions")) {
					ImGui::Separator();

					if (ImGui::MenuItem("Terminate")) MainWindow::SetShouldClose(true);

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Debug")) {
					ImGui::MenuItem("Console", NULL, &ConsoleOpen);
					ImGui::MenuItem("Textures", NULL, & TexturesOpen);
					
					ImGui::MenuItem("Shaders", NULL, &ShadersOpen);
					ImGui::MenuItem("Buffers", NULL, &BuffersOpen);
					ImGui::MenuItem("Extentions", NULL, &ExtensionsOpen);
					ImGui::Separator();
					#ifdef MODULE_LIGHT
					ImGui::MenuItem("Lights", NULL, &LightsOpen);
					#endif
					ImGui::MenuItem("Meshes", NULL, &MeshesOpen);
					ImGui::MenuItem("Renders", NULL, &RendersOpen);
					ImGui::MenuItem("ECS", NULL, &ECSOpen);
					ImGui::EndMenu();
				}

				
				static const char* UpdIntNames[] = {"1","2","3","4"};
				static int currentUpdateIntervalSelection = 0;
				if (ImGui::BeginMenu("Options")) {
					//if (ImGui::MenuItem())
					
					if (ImGui::BeginMenu("Update rate")) {
						ImGui::Text("RefreshRate / (value)");
						ImGui::Separator();
						for (int i = 0; i < 4; i++) {
							bool selected = false;
							if (currentUpdateIntervalSelection == i) selected = true;
							if (ImGui::Selectable(UpdIntNames[i],selected)) {
								currentUpdateIntervalSelection= i;
								glfwSwapInterval(currentUpdateIntervalSelection+1);
							}
							
						}
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				
				ImGui::EndMainMenuBar();
			}

			
			static bool ShowGPUProfiler = false;
			//if (TexturesOpen || MeshesOpen || ShadersOpen || BuffersOpen) ShowGPUProfiler = true;
			#pragma region WorkAreaBegin
						static bool use_work_area = true;
						static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

						const ImGuiViewport* viewport = ImGui::GetMainViewport();
						ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
						ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
						static bool open = true;
						ImGui::Begin("Work Area", nullptr, flags);
			#pragma endregion

			int GPUProfilerSize = 120;
			ImVec2 InspectorSize = ImVec2(0, 0);
			if (ShowGPUProfiler)InspectorSize = ImVec2(0, ImGui::GetContentRegionAvail().y - GPUProfilerSize);
			ImGui::BeginChild("Work Inspector", InspectorSize, false);

			

			ImGui::BeginChild("General Options", ImVec2(0,60),true);
			ImGui::Checkbox("Gizmos", &Gizmos::GizmosEnabled);

			ImGui::EndChild();

			ImGuiTabBarFlags tabflags = ImGuiTabBarFlags_Reorderable;
			ImGui::BeginTabBar("Work Units", tabflags);
			
			if (ImGui::BeginTabItem("Console",&ConsoleOpen)) {
				Console::DrawImguiConsole();
				ShowGPUProfiler = false;
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Textures", &TexturesOpen)) {
				TexturesDebug();
				ShowGPUProfiler = true;
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Shaders",&ShadersOpen)) {
				ShadersDebug();
				ShowGPUProfiler = true;
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Buffers", &BuffersOpen)) {
				BuffersDebug();
				ShowGPUProfiler = true;
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Meshes", &MeshesOpen)) {
				MeshesDebug();
				ShowGPUProfiler = true;
				ImGui::EndTabItem();
			}
			#ifdef MODULE_LIGHT
			if (ImGui::BeginTabItem("Lights", &LightsOpen)) {
				LightsDebug();
				ImGui::EndTabItem();
			}
			#endif
			if (ImGui::BeginTabItem("Extensions", &ExtensionsOpen)) {
				ExtensionsDebug();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Renders", &RendersOpen)) {
				RendersDebug();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("ECS", &ECSOpen)) {
				ECSDebug();
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
			ImGui::EndChild();


			if (ShowGPUProfiler) {
				ImGui::Separator();
				ImGui::BeginChild("GPU Profiler", ImVec2(0, 0), false);

				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				
				
				const ImVec2 p = ImGui::GetCursorScreenPos();
				static float size = 1;
				ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);

				float MemoryPercentage = (float)CurrentSelectionMemmorySize / (float)CurrentTypeMemorySize;
				
				string Label = DebuggerParseBytes(CurrentSelectionMemmorySize) + "/" + DebuggerParseBytes(CurrentTypeMemorySize);
				ImGui::ProgressBar(MemoryPercentage,ImVec2(0,0), Label.c_str());
				ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
				ImGui::SliderFloat("Size", &size, 0, 1);
	
				draw_list->AddRectFilled(ImGui::GetCursorScreenPos(), ImGui::GetContentRegionAvail(), ImColor(1, 0, 0, 1),0,10);
				//draw_list->AddBezierQuadratic()
				
				glfwMakeContextCurrent(MainWindow::GlWindowPointer);
				static int mult = 1024;
				
				ImGui::Text("Total Available: "); ImGui::SameLine();
				GLint GPUTotalMemmory;
				glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &GPUTotalMemmory);
				ImGui::Text(DebuggerParseBytes(GPUTotalMemmory* mult).c_str());
				ImGui::SameLine();

				ImGui::Text("Dedicated: "); ImGui::SameLine();
				GLint GPUDedicadedMemory;
				glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &GPUDedicadedMemory);
				ImGui::Text(DebuggerParseBytes(GPUDedicadedMemory* mult).c_str());

				//Console::Log(to_string(glGetError()));

				

				//Console::Log(to_string(glGetError()));

				ImGui::Text("Current Available: "); ImGui::SameLine();
				GLint GPUMemoryAmount;
				glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &GPUMemoryAmount);
				ImGui::Text(DebuggerParseBytes(GPUMemoryAmount* mult).c_str());
				//ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0.2f, 1));
				ImGui::Text("I know. GPU_MEMORY_INFO_NVX is being a cunt >:/");
				//ImGui::PopStyleColor();
				//Console::Log(to_string(glGetError()));
				

				glfwMakeContextCurrent(DebugWindowPointer);
				
				
				ImGui::EndChild();
			}
			


			ImGui::End();


			



			ImGui::ShowDemoWindow();
			//Console::DrawImguiConsole();


			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			

			glfwSwapBuffers(DebugWindowPointer);
			glfwPollEvents();

		}


	}

	static string DebuggerParseBytes(int Bytes) {
		int Levels = 0;
		bool isBiggerThanNext = true;
		while (isBiggerThanNext) {
			if (Bytes >= 1024) {
				Levels++;
				Bytes /= 1024;
			}
			else isBiggerThanNext = false;
		}
		string Unit;
		switch (Levels)
		{
		case 0:
			Unit = "B";
			break;
		case 1:
			Unit = "KB";
			break;
		case 2:
			Unit = "MB";
			break;
		case 3:
			Unit = "GB";
			break;
		default:
			break;
		}
		return to_string(Bytes) + Unit;
	}
	
};


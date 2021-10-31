#include "Console.h"
#include "../../Dependencies/Imgui/imgui.h"
vector<Console::Line> Console::NewConsoleLog = vector<Console::Line>();
string Console::ConsoleLog = "";
bool Console::ConsoleOpen = true;
bool Console::AutoScroll = true;


void Console::AddToConsoleLog(string log,ConsoleColors color)
{
	ConsoleLog += log + "\n";
	Line line;
	line.lineContent = log;
	line.color = color;
	NewConsoleLog.push_back(line);
}

void Console::Log(string log, ConsoleColors color) {
	std::cout << " \033[0m" << log << std::endl;
	AddToConsoleLog(log,color);

}

void Console::Error(string error) {
	std::cout << " \033[0;31m[ERROR]" << "\033[0m " << error << std::endl;
	AddToConsoleLog(error,ConsoleColors::ROSE);
}

void Console::Warning(string warning) {
	std::cout << " \033[0;33m[WARNING]" << "\033[0m " << warning << std::endl;
	AddToConsoleLog(warning,ConsoleColors::YELLOW);
}

void Console::Critical(string critical) {
	std::cout << " \033[41m[CRITICAL]" << "\033[0m " << critical << std::endl;
	AddToConsoleLog(critical,ConsoleColors::RED);
}
ImVec4 ConsoleColorParse(ConsoleColors cColor) {

	switch (cColor)
	{
	case RED:
		return ImVec4(1, 0, 0, 1);
		break;
	case ROSE:
		return ImVec4(1, 0.25f, 0, 1);
		break;
	case BLUE:
		break;
	case CYAN:
		break;
	case GREEN:
		return ImVec4(0, 1, 0, 1);
		break;
	case WHITE:
		return ImVec4(1, 1, 1, 1);
		break;
	case YELLOW:
		break;
	case ORANGE:
		break;
	default:
		break;
	}
}
void Console::DrawImguiConsole() {



	
	
	ImGui::TextWrapped(
		"This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
		"implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
	ImGui::TextWrapped("Enter 'HELP' for help.");

	if (ImGui::SmallButton("Clear")) { ConsoleLog = ""; }
	ImGui::SameLine();
	bool copy_to_clipboard = ImGui::SmallButton("Copy");

	ImGui::Separator();

	if (ImGui::Button("Options"))
		ImGui::OpenPopup("Options");

	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-scroll", &AutoScroll);
		ImGui::EndPopup();
	}

	
	ImGui::SameLine();
	ImGui::Button("Filter wip :/");
	ImGui::Separator();

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	static float scale = 1;
	if (ImGui::SliderFloat("Scale", &scale, 0.25f,4)) {
		scale = round(scale * 4) / 4;
	}
	
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
	ImGui::BeginChild("ScrollingRegion",ImVec2(0,0),false,window_flags);
	ImGui::SetWindowFontScale(scale);
	/*
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
	ImGui::TextUnformatted(ConsoleLog.c_str());
	ImGui::PopStyleVar();
	*/
	
	//static int lines = 0;
	
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGuiListClipper clipper;
	clipper.Begin(NewConsoleLog.size());

	while (clipper.Step())
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
			Line line = NewConsoleLog[i];
			ImGui::PushStyleColor(ImGuiCol_Text, ConsoleColorParse(line.color));
			ImGui::Text(line.lineContent.c_str(), i);
			ImGui::PopStyleColor();
		}
	ImGui::PopStyleVar();
	if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);

	ImGui::EndChild();

}

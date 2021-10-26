#include "Console.h"
#include "../Dependencies/Imgui/imgui.h"
string Console::ConsoleLog = "";
bool Console::ConsoleOpen = true;
bool Console::AutoScroll = true;
void Console::AddToConsoleLog(string log)
{
	ConsoleLog += log + "\n";
}

void Console::Log(string log) {
	std::cout << " \033[0m" << log << std::endl;
	AddToConsoleLog(log);

}

void Console::Error(string error) {
	std::cout << " \033[0;31m[ERROR]" << "\033[0m " << error << std::endl;
	AddToConsoleLog(error);
}

void Console::Warning(string warning) {
	std::cout << " \033[0;33m[WARNING]" << "\033[0m " << warning << std::endl;
	AddToConsoleLog(warning);
}

void Console::Critical(string critical) {
	std::cout << " \033[41m[CRITICAL]" << "\033[0m " << critical << std::endl;
	AddToConsoleLog(critical);
}

void Console::DrawImguiConsole() {
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Console", &ConsoleOpen)) {
		ImGui::End();
		return;
	}

	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Close Console"))
			ConsoleOpen = false;
		ImGui::EndPopup();
	}

	ImGui::TextWrapped(
		"This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
		"implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
	ImGui::TextWrapped("Enter 'HELP' for help.");

	if (ImGui::SmallButton("Clear")) { ConsoleLog = ""; }
	ImGui::SameLine();
	bool copy_to_clipboard = ImGui::SmallButton("Copy");

	ImGui::Separator();

	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-scroll", &AutoScroll);
		ImGui::EndPopup();
	}

	if (ImGui::Button("Options"))
		ImGui::OpenPopup("Options");
	ImGui::SameLine();
	ImGui::Button("Filter wip :/");
	ImGui::Separator();

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);


	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
	ImGui::TextUnformatted(ConsoleLog.c_str());
	ImGui::PopStyleVar();
	if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);
	ImGui::EndChild();
	ImGui::End();
}
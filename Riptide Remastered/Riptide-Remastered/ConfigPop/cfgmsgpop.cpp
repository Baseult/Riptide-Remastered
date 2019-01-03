#include "cfgmsgpop.h"
#include <chrono>

long getMils() {
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

namespace Anime {
	bool reverse = false;
	//bool done = false;
	int offset = 0;
	bool show_popup = false;

	void Popup(const char* text, int onScreenMils, bool* done)
	{
		if (!done)
			show_popup = true;

		ImGuiIO &io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		int Wd = io.DisplaySize.x;
		static long oldTime = -1;
		ImGui::SetNextWindowPos(ImVec2(Wd - offset, 100));
		style.WindowMinSize = ImVec2(100.f, 20.f);
		ImGui::Begin("##PopUpWindow", &show_popup, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		long currentTime_ms = getMils();

		ImVec2 txtSz = ImGui::CalcTextSize(text);
		ImGui::SetCursorPosY(ImGui::GetWindowHeight() / 2 - txtSz.y / 2);
		ImGui::Text(text);


		if (!reverse)
		{
			if (offset < ImGui::GetWindowWidth())
				offset += (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);

			if (offset >= ImGui::GetWindowWidth() && oldTime == -1)
			{

				oldTime = currentTime_ms;
			}
		}


		if (currentTime_ms - oldTime >= onScreenMils && oldTime != -1) // close after x mils
			reverse = true;

		if (reverse)
		{
			if (offset > 0)
				offset -= (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);
			if (offset <= 0)
			{
				offset = 0;
				reverse = false;
				*done = true;
				oldTime = -1;
				show_popup = false;

			}
		}

		ImGui::End();
	}
}



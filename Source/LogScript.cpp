#include <string>
#include "Signatures.hpp"
#include "LogScript.hpp"
#include "UI/Interface.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "D3DRenderer.hpp"
#include "ImGui/imgui_internal.h"

namespace Saint
{
	bool LogScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType LogScript::GetType()
	{
		return ScriptType::D3D;
	}

	void LogScript::Initialize()
	{
		m_Initialized = true;
	}

	void LogScript::Destroy()
	{
	}

	namespace
	{
		std::size_t s_LastLogCount = 0;
	}
	ImU32 ConvertRectColor(Color p1) {
		float p2 = 1.0f;
		__int32 p3 = 255;
		float p4 = (p2 / p3) * p1.r;
		float p5 = (p2 / p3) * p1.g;
		float p6 = (p2 / p3) * p1.b;
		float p7 = (p2 / p3) * p1.a;
		return ImU32(ImColor(p4, p5, p6, p7));
	}
	void LogScript::Tick()
	{

			if (g_Render->m_Opened && g_Render->m_HeaderText)
			{
				auto m_Hello = ImGui::CalcTextSize("Hello").y;
				auto m_XPosition = ((g_Render->m_PosX - (g_Render->m_Width / g_Render->m_FooterTextPadding)) * ImGui::GetIO().DisplaySize.x);
				auto m_YPosition = (g_Render->m_PosY + (g_Render->m_HeaderHeight / 100.f) + ((ImGui::CalcTextSize(g_Render->m_CurrentSubMenuName).y / 1920) / 4.f)) * ImGui::GetIO().DisplaySize.y;
				if (ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)) {
					ImGui::SetWindowSize(ImGui::GetIO().DisplaySize);
					ImGui::PushFont(g_D3DRenderer->m_HeaderFont);
					auto DrawList = ImGui::GetWindowDrawList();
					DrawList->AddText(ImVec2(m_XPosition, m_YPosition), ImColor(g_Render->m_HeaderTextColor.r, g_Render->m_HeaderTextColor.g, g_Render->m_HeaderTextColor.b, g_Render->m_HeaderTextColor.a), g_Render->m_CurrentSubMenuName);
					ImGui::PopFont();
				}
			}  ImGui::End();
		if (g_Render->m_Opened && g_Settings.m_LogWindow)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Logger"))
			{
				std::lock_guard lock(g_Logger->GetMutex());
				auto msgs = g_Logger->GetMessages();

				for (std::size_t i = 0; i < msgs.second; ++i)
				{
					ImGui::TextUnformatted(msgs.first[i].get());
				}

				if (s_LastLogCount != msgs.second)
				{
					s_LastLogCount = msgs.second;
					ImGui::SetScrollHereY(1.f);
				}
			}  ImGui::End();
		}
	}
}

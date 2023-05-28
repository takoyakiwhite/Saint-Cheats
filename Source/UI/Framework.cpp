#include "Framework.hpp"
#include "../Timer.hpp"
#include "../FiberHelper.hpp"
#include "UnclickOption.hpp"
#include "../Enums.h"
#include "../Features.h"
#include "../ImGui/imgui.h"
#include "../D3DRenderer.hpp"
#include "../ImGui/imgui_internal.h"
#include "../Translation.hpp"
#define VERSION 4
//#define DEV_MODE
//#define TESTER_MODE
#define RELEASE_MODE


#ifdef DEV_MODE
#undef RELEASE_MODE
#undef TESTER_MODE
#define VERSION_TYPE "DEV"
#endif
#define VERSION_TYPE "RELEASE"
namespace Saint::UserInterface
{
	bool FileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}
	void LoadYTD()
	{
		std::string MenuFolderPath = "C:\\Saint\\";
		std::string name = "Textures.ytd";
		const std::string fullPath = MenuFolderPath + name;
		uint32_t textureID;
		if (FileExists(fullPath))
			g_GameFunctions->m_RegisterFile(&textureID, fullPath.c_str(), true, name.c_str(), false);
	}
	void MenuOpeningAnimation()
	{
		g_Render->m_Opened = true;
	}
	void MenuClosingAnimation()
	{
		g_Render->m_Opened = false;
	}
	bool g_HasSetToolTip = false;
	int g_ToolTip = 0;
	int random(int min, int max)
	{
		static bool first = true;
		if (first)
		{
			srand(time(NULL));
			first = false;
		}
		return min + rand() % ((max + 1) - min);
	}
	void Framework::RenderToolTip()
	{

		if (fileExists("C:\\Saint\\tooltips.txt")) {
			std::ifstream file("C:\\Saint\\tooltips.txt");
			std::vector<std::string> lines;

			if (file.is_open()) {
				std::string line;
				while (std::getline(file, line)) {
					lines.push_back(line);
				}

				file.close();
			}
			else {
				getLogger()->Push("Coulden't open file 'tooltips.txt'", LogFlag::Error, "");
			}
			if (!g_HasSetToolTip)
			{
				g_ToolTip = random(0, lines.size());
				g_HasSetToolTip = true;
			}
			char text[200];
			if (tooltips_enabled && !lines.empty()) {
				if (g_ToolTip < 0 || g_ToolTip >= lines.size()) {
					g_ToolTip = 0;
				}
				if (PAD::IS_USING_KEYBOARD_AND_MOUSE(2)) {
					sprintf_s(text, "%s\n~u~%s", lines[g_ToolTip].c_str(), "~b~F4");
					DrawingFunctions()->Text(text, 0.5f, 0.09f, Font::ChaletLondon, 0.4f, m_ToolTipColor, true, false, false);
				}
				else {
					sprintf_s(text, "%s\n~b~RB + RIGHT", lines[g_ToolTip].c_str());
					DrawingFunctions()->Text(text, 0.5f, 0.09f, Font::ChaletLondon, 0.4f, m_ToolTipColor, true, false, false);
				}
			}
			else {
				if (PAD::IS_USING_KEYBOARD_AND_MOUSE(2)) {
					sprintf_s(text, "%s\n~u~%s", "No tooltip found.", "~b~F4");
					DrawingFunctions()->Text(text, 0.5f, 0.09f, Font::ChaletLondon, 0.4f, m_ToolTipColor, true, false, false);
				}
				else {
					sprintf_s(text, "%s\n~b~RB + RIGHT", "No tooltip found.");
					DrawingFunctions()->Text(text, 0.5f, 0.09f, Font::ChaletLondon, 0.4f, m_ToolTipColor, true, false, false);
				}
			}
		}
	}
	float convert_360(float base, float min, float max) {
		float fVar0;
		if (min == max) return min;
		fVar0 = max - min;
		base -= SYSTEM::ROUND(base - min / fVar0) * fVar0;
		if (base < min) base += fVar0;
		return base;
	}
	void Framework::drawstring(char* text, float X, float Y)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT2(X, Y);
	}
	void Framework::setupdraw(bool outline)
	{
		HUD::SET_TEXT_FONT(1);
		HUD::SET_TEXT_SCALE(0.4f, 0.4f);
		HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
		HUD::SET_TEXT_WRAP(0.0f, 1.0f);
		HUD::SET_TEXT_CENTRE(0);
		HUD::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		HUD::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		if (outline)
		{
			HUD::SET_TEXT_OUTLINE();
		}
	}
	void Framework::draw_glare() {
		if (m_render_glare) {
			m_glare_handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
			NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
			float dir = convert_360(rot.z, 0, 360);
			if (m_glare_direction != dir) {
				m_glare_direction = dir;
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_glare_handle, "SET_DATA_SLOT");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(m_glare_direction);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			}
			GRAPHICS::DRAW_SCALEFORM_MOVIE(m_glare_handle, (m_PosX + 0.3456f - glare_x_offset), (m_DrawBaseY + (m_HeaderHeight / 2.f) + 0.38f), (m_Width + 0.82700f), (m_HeaderHeight + 0.852f) + glare.height_offset, 255, 255, 255, 255, 0);
		}
	}
	void Framework::OnTick()
	{
		std::lock_guard lock(m_Mutex);
		if (IsMouseLocked())
		{
			if (g_Render->controlsEnabled) {
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				ShowCursor(true);
				SetCursor(LoadCursorA(NULL, IDC_ARROW));
			}
		}
		if (g_Render->m_Opened && g_Settings.m_LockMouse)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}
		if (!g_Render->m_Opened)
		{
			RenderToolTip();
		}
		CheckForInput();
		HandleInput();
		LoadYTD();
		if (m_Opened)
		{
			HUD::DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME();
			GRAPHICS::FORCE_RENDER_IN_GAME_UI(true);
			GRAPHICS::SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(true);
			PAD::DISABLE_CONTROL_ACTION(0, 27, true);
			m_DrawBaseY = m_PosY;
			DrawHeader();
			if (!m_SubmenuStack.empty())
			{
				auto sub = m_SubmenuStack.top();
				sub->Reset();
				sub->Execute();
				DrawSubmenuBar(sub);
				g_Render->m_CurrentSubMenuName = dynamic_text ? sub->GetName() : header_name.c_str();
				if (sub->GetNumOptions() != 0)
				{
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->GetNumOptions() > m_OptionsPerPage ? m_OptionsPerPage : sub->GetNumOptions();
					if (sub->GetNumOptions() > m_OptionsPerPage && sub->GetSelectedOption() >= m_OptionsPerPage)
					{
						startPoint = sub->GetSelectedOption() - m_OptionsPerPage + 1;
						endPoint = sub->GetSelectedOption() + 1;
					}
					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						DrawOption(sub->GetOption(i), i == sub->GetSelectedOption());
					}
				}
			}
			DrawFooter();
			DrawDescription();
		}
	}
	void Framework::CheckForInput()
	{
		ResetInput();
		m_OpenKeyPressed = IsKeyPressed(open_key);
		m_OpenKeyPressed2 = IsKeyPressed(VK_INSERT);
		m_BackKeyPressed = IsKeyPressed(VK_BACK) || IsKeyPressed(VK_NUMPAD0);
		m_EnterKeyPressed = IsKeyPressed(VK_RETURN) || IsKeyPressed(VK_NUMPAD5);
		m_UpKeyPressed = IsKeyPressed(VK_UP) || IsKeyPressed(VK_NUMPAD8);
		m_DownKeyPressed = IsKeyPressed(VK_DOWN) || IsKeyPressed(VK_NUMPAD2);
		m_LeftKeyPressed = IsKeyPressed(VK_LEFT) || IsKeyPressed(VK_NUMPAD4);
		m_RightKeyPressed = IsKeyPressed(VK_RIGHT) || IsKeyPressed(VK_NUMPAD6);
	}
	void Framework::HandleInput()
	{
		if (controlsEnabled && !g_Settings.command_window) {
			static Timer openTimer(0ms);
			openTimer.SetDelay(std::chrono::milliseconds(m_OpenDelay));
			if (m_OpenKeyPressed && openTimer.Update())
			{
				g_HasSetToolTip = false;
				if (!m_Opened) {
					MenuOpeningAnimation();
				}
				else {
					MenuClosingAnimation();

				}

				if (m_Sounds)
					Game->PlaySound2(m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET");
			}
			if (!PAD::IS_USING_KEYBOARD_AND_MOUSE(2)) {
				if (Game->DisabledControlPressed(227) && Game->DisabledControlPressed(INPUT_CELLPHONE_RIGHT) && openTimer.Update())
				{
					g_HasSetToolTip = false;
					if (!m_Opened) {
						MenuOpeningAnimation();
					}
					else {
						MenuClosingAnimation();
					}

					if (m_Sounds)
						Game->PlaySound2(m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET");
				}
			}
			if (m_OpenKeyPressed2 && openTimer.Update())
			{
				g_HasSetToolTip = false;
				if (!m_Opened) {
					MenuOpeningAnimation();
				}
				else {
					MenuClosingAnimation();
				}

				if (m_Sounds)
					Game->PlaySound2(m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET");
			}
			static Timer backTimer(0ms);
			backTimer.SetDelay(std::chrono::milliseconds(m_BackDelay));
			if (m_Opened && m_BackKeyPressed && backTimer.Update())
			{
				if (m_Sounds)
					Game->PlaySound2("BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET");

				if (m_SubmenuStack.size() <= 1)
				{
					MenuClosingAnimation();
					m_Opened = false;
				}
				else
				{
					m_SubmenuStack.pop();
				}
			}
			if (m_Opened && Game->DisabledControlPressed(194) && backTimer.Update())
			{
				if (m_Sounds)
					Game->PlaySound2("BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET");

				if (m_SubmenuStack.size() <= 1)
				{
					MenuClosingAnimation();
					m_Opened = false;
				}
				else
				{
					m_SubmenuStack.pop();
				}
			}
			if (m_Opened && !m_SubmenuStack.empty())
			{

				Game->DisableControl(0, true);
				Game->DisableControl(19, true);
				Game->DisableControl(140, true);
				Game->DisableControl(20, true);
				Game->DisableControl(27, true);
				Game->DisableControl(80, true);
				Game->DisableControl(337, true);
				Game->DisableControl(27, true);
				Game->DisableControl(85, true);
				Game->DisableControl(74, true);
				Game->DisableControl(58, true);
				Game->DisableControl(70, true);
				auto sub = m_SubmenuStack.top();
				static Timer enterTimer(0ms);
				enterTimer.SetDelay(std::chrono::milliseconds(m_EnterDelay));
				if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update())
				{
					if (g_Settings.m_LockMouse) {
						g_Settings.m_LockMouse = false;
					}
					if (m_Sounds)
						Game->PlaySound2("SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET");

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::Enter);
					}
				}
				if (Game->KeyPress(0x56)) {
					if (g_Settings.m_LockMouse) {
						g_Settings.m_LockMouse = false;
					}
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::Hotkey);
					}
				}
				if (Game->DisabledControlPressed(191) && sub->GetNumOptions() != 0 && enterTimer.Update())
				{
					if (g_Settings.m_LockMouse) {
						g_Settings.m_LockMouse = false;
					}
					if (m_Sounds)
						Game->PlaySound2("SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET");

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::Enter);
					}
				}
				static Timer upTimer(0ms);
				upTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
				if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update())
				{
					if (g_Settings.m_LockMouse) {
						g_Settings.m_LockMouse = false;
					}
					if (m_Sounds)
						Game->PlaySound2("NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET");

					sub->Scroll(ScrollDirection::BACKWARD);
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (opt->GetFlag("break", "none"))
						{
							sub->Scroll(ScrollDirection::BACKWARD);
						}
					}
				}
				if (Game->DisabledControlPressed(172) && sub->GetNumOptions() != 0 && upTimer.Update())
				{
					if (g_Settings.m_LockMouse) {
						g_Settings.m_LockMouse = false;
					}
					if (m_Sounds)
						Game->PlaySound2("NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET");

					sub->Scroll(ScrollDirection::BACKWARD);
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (opt->GetFlag("break", "none"))
						{
							sub->Scroll(ScrollDirection::BACKWARD);
						}
					}
				}
				static Timer downTimer(0ms);
				downTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
				if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update())
				{
					if (g_Settings.m_LockMouse) {
						g_Settings.m_LockMouse = false;
					}
					if (m_Sounds)
						Game->PlaySound2("NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET");

					sub->Scroll(ScrollDirection::FORWARD);
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (opt->GetFlag("break", "none"))
						{
							sub->Scroll(ScrollDirection::FORWARD);
						}
					}

				}
				if (Game->DisabledControlPressed(173) && sub->GetNumOptions() != 0 && downTimer.Update())
				{
					if (g_Settings.m_LockMouse) {
						g_Settings.m_LockMouse = false;
					}
					if (m_Sounds)
						Game->PlaySound2("NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET");

					sub->Scroll(ScrollDirection::FORWARD);
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (opt->GetFlag("break", "none"))
						{
							sub->Scroll(ScrollDirection::FORWARD);
						}
					}

				}
				static Timer leftTimer(0ms);
				leftTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
				if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update())
				{

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (g_Settings.m_LockMouse) {
							g_Settings.m_LockMouse = false;
						}
						if (m_Sounds && !opt->GetFlag("none", "bool"))
							Game->PlaySound2("NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET");
						opt->HandleAction(OptionAction::Left);
					}
				}
				if (Game->DisabledControlPressed(174) && sub->GetNumOptions() != 0 && leftTimer.Update())
				{


					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (g_Settings.m_LockMouse) {
							g_Settings.m_LockMouse = false;
						}
						if (m_Sounds && !opt->GetFlag("none", "bool"))
							Game->PlaySound2("NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET");
						opt->HandleAction(OptionAction::Left);
					}
				}
				static Timer rightTimer(0ms);
				rightTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
				if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update())
				{


					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (g_Settings.m_LockMouse) {
							g_Settings.m_LockMouse = false;
						}
						if (m_Sounds && !opt->GetFlag("none", "bool"))
							Game->PlaySound2("NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET");
						opt->HandleAction(OptionAction::Right);
					}
				}

				if (Game->DisabledControlPressed(175) && !Game->ControlPressed(227) && sub->GetNumOptions() != 0 && rightTimer.Update())
				{
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (g_Settings.m_LockMouse) {
							g_Settings.m_LockMouse = false;
						}
						if (m_Sounds && !opt->GetFlag("none", "bool"))
							Game->PlaySound2("NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET");
						opt->HandleAction(OptionAction::Right);
					}
				}
			}
		}
	}

	void Framework::ResetInput()
	{
		m_OpenKeyPressed = false;
		m_BackKeyPressed = false;
		m_EnterKeyPressed = false;
		m_UpKeyPressed = false;
		m_DownKeyPressed = false;
		m_LeftKeyPressed = false;
		m_RightKeyPressed = false;
	}

	void Framework::DrawHeader()
	{
		float MousePosX = (1.f / ImGui::GetIO().DisplaySize.x) * GetMousePos().x;
		float MousePosY = (1.f / ImGui::GetIO().DisplaySize.y) * GetMousePos().y;
		float Top = m_DrawBaseY;
		float Bottom = m_DrawBaseY + m_HeaderHeight;
		float Left = m_PosX - (m_Width / 2.f);
		float Right = m_PosX + (m_Width / 2.f);
		if (MousePosX > Left && MousePosX < Right && MousePosY > Top && MousePosY < Bottom && g_Settings.m_LockMouse && GetAsyncKeyState(VK_LBUTTON)) {
			m_PosX = MousePosX;
			m_PosY = MousePosY - (m_HeaderHeight / 2.f);
		}

		switch (m_HeaderType)
		{
		case HeaderType::Static:
			DrawingFunctions()->Rectangle(
				m_PosX,
				m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width,
				m_HeaderHeight,
				m_HeaderBackgroundColor);

			break;
		case HeaderType::YTD:
			for (std::size_t i = 0; i < (m_HeaderGradientTransparent ? 1 : 20); ++i)
			{
				DrawingFunctions()->Sprite(
					"Textures",
					"Header",
					m_PosX,
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width,
					m_HeaderHeight,
					{ 255, 255, 255, 255 },
					0.f);

			}
			break;
		}
		if (m_HeaderNativeText)
		{
			if (center_head) {
				DrawingFunctions()->Text(TextPosition::Center,
					m_CurrentSubMenuName,
					m_PosX - (m_Width / 2.1f) - header_x_offset - 0.005f,
					m_DrawBaseY + (m_HeaderHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
					m_HeaderTextSize,
					m_HeaderFont,
					m_HeaderTextColor,
					false, true, false);
			}
			else {
				DrawingFunctions()->Text(TextPosition::Left,
					m_CurrentSubMenuName,
					m_PosX - (m_Width / 2.1f) - header_x_offset,
					m_DrawBaseY + (m_HeaderHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
					m_HeaderTextSize,
					m_HeaderFont,
					m_HeaderTextColor,
					false, true, false);
			}
		}
		draw_glare();
		m_DrawBaseY += m_HeaderHeight;
	}
	void Framework::DrawSubmenuBar(SubmenuBase* sub)
	{
		if (submenu_enabled) {
			char leftText[64] = {};
			std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
			std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>(toupper(c)); });
			DrawingFunctions()->Rectangle(m_PosX, m_DrawBaseY + (m_SubheaderHeight / 2.f), m_Width, m_SubheaderHeight, m_SubheaderBackground);
			DrawingFunctions()->Text(TextPosition::Left,
				&leftText[0],
				m_PosX - (m_Width / m_OptionPadding) - 0.002f,
				m_DrawBaseY + (m_SubheaderHeight / 2.f) - (DrawingFunctions()->GetTextHeight(Font::ChaletLondon, 0.25f) / 1.5f),
				0.25f, Font::ChaletLondon,
				m_SubheaderText,
				false, true, false);
			DrawingFunctions()->Text(TextPosition::Right,
				GetAmountOfOptions(sub),
				m_PosX + (m_Width / 2.1f),
				m_DrawBaseY + (m_SubheaderHeight / 2.f) - (DrawingFunctions()->GetTextHeight(Font::ChaletLondon, 0.25f) / 1.5f),
				0.25f, Font::ChaletLondon,
				m_SubheaderTextRight,
				false, true, false);
			if (lines_enabled) {
				DrawingFunctions()->Rectangle(m_PosX, m_DrawBaseY + (0.0005f / 2.0f) + 0.031, m_Width, 0.0018f, m_HeaderBackgroundColor);
			}
			m_DrawBaseY += m_SubheaderHeight;
		}
	}
	void Framework::DrawOption(OptionBase* opt, bool selected)
	{
		if (selected) {
			m_OptionSelected = m_OptionSelectedTextColor;
		}
		else {
			m_OptionSelected = m_OptionUnselectedTextColor;
		}
		std::string s1 = Translations::GetTranslation(opt->GetLeftText());
		std::string s2 = Translations::GetTranslation(opt->GetRightText());
		const char* lefttext = s1.c_str();
		const char* righttext = s2.c_str();
		DrawingFunctions()->SetDrawOrder(1);
		DrawingFunctions()->Rectangle(
			m_PosX,
			m_DrawBaseY + (m_OptionHeight / 2.f),
			m_Width,
			m_OptionHeight,
			m_OptionUnselectedBackgroundColor);
		if (selected)
		{
			m_CurrentCoord = lerp(m_CurrentCoord, m_DrawBaseY + (m_OptionHeight / 2.f), smooth_scroll_speed);
			DrawingFunctions()->SetDrawOrder(2);
			DrawingFunctions()->Rectangle(
				m_PosX,
				m_CurrentCoord,
				m_Width,
				m_OptionHeight,
				m_OptionSelectedBackgroundColor);
			if (scrollbar) {
				DrawingFunctions()->Rectangle(
					m_PosX,
					m_CurrentCoord - 0.016,
					m_Width,
					0.0020f,
					m_HeaderBackgroundColor);
				DrawingFunctions()->Rectangle(
					m_PosX,
					m_CurrentCoord + 0.016,
					m_Width,
					0.0020f,
					m_HeaderBackgroundColor);
			}
			if (ScrollerInt == 1) {
				m_CurrentCoord2 = lerp(m_CurrentCoord2, m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f), smooth_scroll_speed);
				DrawingFunctions()->Text(TextPosition::Left,
					lefttext,
					m_PosX - (m_Width / m_OptionPadding) - 0.002f,
					m_CurrentCoord2,
					m_OptionTextSize,
					m_OptionFont,
					getSelectedColor(),
					false, false
				);
			}
		}
		DrawingFunctions()->SetDrawOrder(3);
		if (!selected || ScrollerInt == 0) {
			DrawingFunctions()->Text(TextPosition::Left,
				lefttext,
				m_PosX - (m_Width / m_OptionPadding) - 0.002f,
				m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
				m_OptionTextSize,
				m_OptionFont,
				getSelectedColor(),
				false, false
			);
		}
		if (opt->GetFlag("number", "bool")) {
			DrawingFunctions()->Arrows(selected, 0.016f);
			DrawingFunctions()->Text(TextPosition::Right,
				righttext,
				selected ? m_PosX + (m_Width / m_OptionPadding) - 0.022 : m_PosX + (m_Width / m_OptionPadding) - 0.01,
				m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
				m_OptionTextSize,
				m_OptionFont,
				getSelectedColor(),
				false, false
			);
		}
		else if (opt->GetFlag("number", "none")) {
			DrawingFunctions()->Arrows(selected, 0.005f);
			DrawingFunctions()->Text(TextPosition::Right,
				righttext,
				selected ? m_PosX + (m_Width / m_OptionPadding) - 0.012 : m_PosX + (m_Width / m_OptionPadding),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
				m_OptionTextSize,
				m_OptionFont,
				getSelectedColor(),
				false, false);
		}
		else if (opt->GetFlag("choose", "bool")) {
			DrawingFunctions()->Arrows(selected, 0.015);
			DrawingFunctions()->Text(TextPosition::Right,
				righttext,
				selected ? show_positions ? m_PosX + (m_Width / m_OptionPadding) - 0.020 : m_PosX + (m_Width / m_OptionPadding) - 0.021 : m_PosX + (m_Width / m_OptionPadding) - 0.01,
				m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
				m_OptionTextSize,
				m_OptionFont,
				getSelectedColor(),
				false, false);
		}
		else if (opt->GetFlag("choose", "none")) {
			DrawingFunctions()->Arrows(selected, 0.005f);
			DrawingFunctions()->Text(
				TextPosition::Right, righttext,
				selected ? m_PosX + (m_Width / m_OptionPadding) - 0.012 : m_PosX + (m_Width / m_OptionPadding),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
				m_OptionTextSize, m_OptionFont, getSelectedColor(), false, false);
		}
		else if (opt->GetFlag("keyboard", "none") || opt->GetFlag("keyboard", "no_pen")) {
			auto res = DrawingFunctions()->GetSpriteScale(0.0185);
			auto res2 = DrawingFunctions()->GetSpriteScale(0.0185);
			DrawingFunctions()->Text(TextPosition::Right,
				righttext,
				opt->GetFlag("keyboard", "none") ? m_PosX + (m_Width / m_OptionPadding - 0.01f) : m_PosX + (m_Width / m_OptionPadding),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
				m_OptionTextSize,
				m_OptionFont,
				getSelectedColor(),
				false, false);
			if (opt->GetFlag("keyboard", "none")) {
				DrawingFunctions()->Sprite(TextureManager()->Get("pen"), m_PosX + (m_Width / m_OptionPadding - 0.004f), m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, 0.0);
			}
		}
		else {
			DrawingFunctions()->Text(TextPosition::Right,
				righttext,
				m_PosX + (m_Width / m_OptionPadding),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
				m_OptionTextSize,
				m_OptionFont,
				getSelectedColor(),
				false, false);
		}
		DrawingFunctions()->Text(TextPosition::Center,
			opt->GetCenteredText(),
			m_PosX,
			m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_SeperatorFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize + 0.02f,
			m_SeperatorFont,
			getSelectedColor(),
			false, false);
		if (opt->GetFlag("number", "bool") || opt->GetFlag("choose", "bool") || opt->GetFlag("none", "bool"))
		{
			auto res = DrawingFunctions()->GetSpriteScale(0.025f);
			auto res2 = DrawingFunctions()->GetSpriteScale(0.032f);
			switch (ToggleIterator) {
			case 0:
				DrawingFunctions()->Sprite(TextureManager()->Get("mainToggles"), g_Render->m_PosX + (g_Render->m_Width / g_Render->m_OptionPadding - 0.005f), g_Render->m_DrawBaseY + (g_Render->m_OptionHeight / 2.5f) - (DrawingFunctions()->GetTextHeight(g_Render->m_OptionFont, g_Render->m_OptionTextSize) / 1.5f) + 0.014f - 0.001, res.x, res.y, ToggledOn ? m_ToggleOnColor : m_ToggleOffColor, 0.0);
				break;
			case 1:
				DrawingFunctions()->Sprite(TextureManager()->Get("mainToggles").dictionary, ToggledOn ? "shop_box_tick" : "shop_box_blank", g_Render->m_PosX + (g_Render->m_Width / g_Render->m_OptionPadding - 0.005f), g_Render->m_DrawBaseY + (g_Render->m_OptionHeight / 2.5f) - (DrawingFunctions()->GetTextHeight(g_Render->m_OptionFont, g_Render->m_OptionTextSize) / 1.5f) + 0.014f, res2.x, res2.y, m_OptionSelected, 0.0f);
				break;
			case 3:
				DrawingFunctions()->Sprite(ToggledOn ? TextureManager()->Get("mainToggles").dictionary : "shared", ToggledOn ? "shop_tick_icon" : "menuplus_32", (m_PosX + (m_Width / m_OptionPadding - 0.004f)), m_DrawBaseY + (m_OptionHeight / 2.0f), ToggledOn ? toggle_width : toggle_width_off, ToggledOn ? toggle_height : toggle_height_off, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, ToggledOn ? toggle_on_rotation : toggle_off_rotation);
				break;
			case 4:
				DrawingFunctions()->Sprite(ToggledOn ? custom_toggle_dict_on.c_str() : custom_toggle_dict_off.c_str(), ToggledOn ? custom_toggle_asset_on.c_str() : custom_toggle_asset_off.c_str(), (m_PosX + (m_Width / m_OptionPadding - 0.004f)), m_DrawBaseY + (m_OptionHeight / 2.0f), ToggledOn ? toggle_width : toggle_width_off, ToggledOn ? toggle_height : toggle_height_off, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, ToggledOn ? toggle_on_rotation : toggle_off_rotation);
				break;
			}
		}
		if (opt->GetFlag("submenu", "none") || opt->GetFlag("submenu", "player"))
		{
			switch (enterable.position) {
			case 0:
				DrawingFunctions()->Text(TextPosition::Right, ">", m_PosX + (m_Width / m_OptionPadding), m_DrawBaseY + (m_OptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(Font::Monospace, 0.35) / 1.725f) - 0.001, 0.35, Font::Monospace, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, false, false);
				break;
			case 1:
				DrawingFunctions()->Rectangle(m_PosX + (m_Width / m_OptionPadding) + 0.00355f + enterable.x_offset, m_DrawBaseY + ((m_OptionHeight) / 2.f), 0.0035f + enterable.width_offset, m_OptionHeight, { m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, sub_alpha });
				break;
			}
		}
		if (opt->GetFlag("submenu", "color"))
		{
			auto res = DrawingFunctions()->GetSpriteScale(0.0140);
			auto res2 = DrawingFunctions()->GetSpriteScale(0.0140);
			DrawingFunctions()->Sprite("commonmenu", "", m_PosX + (m_Width / m_OptionPadding - 0.004f), m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, opt->GetColor(), 0.0);
		}

		m_DrawBaseY += m_OptionHeight;
	}
	void Framework::DrawFooter()
	{
		float size = m_FooterSpriteSize;
		float rotation = 0.f;
		const char* texture = TextureManager()->Get("arrows").asset;
		auto sub = m_SubmenuStack.top();

		if (!m_SubmenuStack.empty())
		{
			if (!freeze_icon) {
				if (sub->GetSelectedOption() == 0 || sub->GetSelectedOption() + 1 == sub->GetNumOptions()) {
					texture = "arrowright";
					size *= 0.8f;
				}
				if (sub->GetSelectedOption() == 0)
				{
					rotation = FooterPosition::DOWN;
				}
				else if (sub->GetSelectedOption() + 1 == sub->GetNumOptions())
				{
					rotation = FooterPosition::UP;

				}
			}
		}
		if (sub->GetNumOptions() <= m_OptionsPerPage && m_dynamic_footer || !footer_enabled) {
			return;
		}
		auto sizee = DrawingFunctions()->GetSpriteScale(size);
		DrawingFunctions()->Rectangle(
			m_PosX,
			m_DrawBaseY + (m_FooterHeight / 2.f),
			m_Width,
			m_FooterHeight,
			m_FooterBackgroundColor);
		DrawingFunctions()->Sprite(
			TextureManager()->Get("arrows").dictionary,
			texture,
			m_PosX,
			m_DrawBaseY + (m_FooterHeight / 2.f),
			sizee.x,
			sizee.y,
			m_FooterSpriteColor,
			rotation);
		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu ~s~&#8226; %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());
		if (LeftFooterText) {
			DrawingFunctions()->Text(TextPosition::Left,
				"Saint Paid",
				m_PosX - (m_Width / m_FooterTextPadding),
				m_DrawBaseY + (m_FooterHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_FooterTextFont, m_FooterTextSize) / 1.5f),
				m_FooterTextSize, m_FooterTextFont,
				m_FooterTextColor,
				false, true, false);
		}
		if (RightFooterText) {
			DrawingFunctions()->Text(TextPosition::Right,
				Flags->isDev() ? "Developer" : g_GameVariables->m_version,
				m_PosX + (m_Width / m_FooterTextPadding),
				m_DrawBaseY + (m_FooterHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_FooterTextFont, m_FooterTextSize) / 1.5f),
				m_FooterTextSize, m_FooterTextFont,
				m_FooterTextColor,
				false, true
			);
		}
		if (lines_enabled) {
			DrawingFunctions()->Rectangle(m_PosX, m_DrawBaseY + (0.001f / 2.0f), m_Width, 0.0018f, m_HeaderBackgroundColor);
		}
		m_DrawBaseY += m_FooterHeight;
	}
	void Framework::DrawDescription()
	{
		const char* description{};

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetNumOptions())
			{
				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					description = opt->GetDescription();
				}
			}
		}
		if (!description || !*description)
			return;
		if (connect_description)
			m_DrawBaseY += m_DescriptionHeightPadding;
		if (connect_description) {
			DrawingFunctions()->Rectangle(m_PosX, m_DrawBaseY + (m_DescriptionHeight / 2.f), m_Width, m_DescriptionHeight, m_OptionUnselectedBackgroundColor);
			DrawingFunctions()->Rectangle(m_PosX, m_DrawBaseY + (m_DescriptionHeight / 2.f) - 0.029, m_Width, 0.003f, m_HeaderBackgroundColor);
		}
		else {
			DrawingFunctions()->Rectangle(m_PosX + description_x, m_PosY + description_y + (m_DescriptionHeight / 2.f), m_Width, m_DescriptionHeight, m_OptionUnselectedBackgroundColor);
			DrawingFunctions()->Rectangle(m_PosX + description_x, m_PosY + description_y + (m_DescriptionHeight / 2.f) - 0.029, m_Width, 0.003f, m_HeaderBackgroundColor);
		}
		if (connect_description) {
			DrawingFunctions()->Wrap(m_PosX, m_PosX + m_Width / 2);
		}
		else {
			DrawingFunctions()->Wrap(m_PosX + description_x2, m_PosX + description_x2 + m_Width / 2);
		}
		if (connect_description) {
			DrawingFunctions()->Text(TextPosition::Left,
				description,
				m_PosX - (m_Width / m_DescriptionPadding),
				m_DrawBaseY + (m_DescriptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f) - 0.015,
				m_DescriptionTextSize,
				m_DescriptionFont,
				m_DescriptionTextColor,
				false, false, false);
		}
		else {
			DrawingFunctions()->Text(TextPosition::Left,
				description,
				m_PosX + description_x2 - (m_Width / m_DescriptionPadding),
				m_PosY + description_y2 + (m_DescriptionHeight / 2.f) - (DrawingFunctions()->GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f) - 0.015,
				m_DescriptionTextSize,
				m_DescriptionFont,
				m_DescriptionTextColor,
				false, false, false);
		}
		if (connect_description) {
			m_DrawBaseY += m_DescriptionHeight;
		}
	}
	bool Framework::IsMouseLocked()
	{
		return m_Opened && m_MouseLocked;
	}
	Vector2 Framework::GetMousePos() //incorrect
	{
		POINT point;
		GetCursorPos(&point);
		return Vector2{ static_cast<float>(point.x), static_cast<float>(point.y) };
	}
	void Framework::SetMousePos(int x, int y)
	{
		SetCursorPos(x, y);
	}
}
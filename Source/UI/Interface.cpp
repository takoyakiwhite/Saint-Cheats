#include "Interface.hpp"
#include "../Timer.hpp"
#include "../Natives.hpp"
#include "../FiberHelper.hpp"
#include "UnclickOption.hpp"
#include "../Enums.h"
#include "../Features.h"
#include "../ImGui/imgui.h"
#include "../D3DRenderer.hpp"
#include "../ImGui/imgui_internal.h"

#define VERSION 4
#define DEV_MODE
//#define TESTER_MODE
//#define RELEASE_MODE


#ifdef DEV_MODE
#undef RELEASE_MODE
#undef TESTER_MODE
#define VERSION_TYPE "DEV"
#endif

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
	void UIManager::RenderToolTip()
	{
		static const char* names[] = {
			"Get Good Get Saint",
			"Sexy Saint Cheats",
			"what am i doing wrong??? - patek",
			"Kiddions VIP On Top",
			"Become you're inner vali."
		};

		if (!g_HasSetToolTip)
		{
			g_ToolTip = MISC::GET_RANDOM_INT_IN_RANGE(0, 4);
			g_HasSetToolTip = true;
		}

		char text[200];

		if (PAD::IS_USING_KEYBOARD_AND_MOUSE(2)) {
			sprintf_s(text, "%s\n~u~%s", names[g_ToolTip], "~c~F4");
			RenderText(text, 0.5f, 0.09f, Font::ChaletLondon, 0.4f, m_ToolTipColor, true, false, false);
		}
		else {
			sprintf_s(text, "%s\n~c~RB + RIGHT", names[g_ToolTip]);
			RenderText(text, 0.5f, 0.09f, Font::ChaletLondon, 0.4f, m_ToolTipColor, true, false, false);
		}
	}

	void UIManager::RenderText(std::string text, std::float_t x, std::float_t y, Font font, std::float_t scale, RGBA color, bool centered, bool right_justified, bool outlined)
	{
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_SCALE(0.f, scale);
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (right_justified)
			HUD::SET_TEXT_WRAP(0.f, x);
		else HUD::SET_TEXT_WRAP(0.f, 1.f);
		HUD::SET_TEXT_CENTRE(centered);
		if (outlined)
			HUD::SET_TEXT_OUTLINE();
		HUD::SET_TEXT_RIGHT_JUSTIFY(right_justified);
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(text.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, NULL);
	}

	float convert_360(float base, float min, float max) {
		float fVar0;
		if (min == max) return min;
		fVar0 = max - min;
		base -= SYSTEM::ROUND(base - min / fVar0) * fVar0;
		if (base < min) base += fVar0;
		return base;
	}

	void UIManager::drawstring(char* text, float X, float Y)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT2(X, Y);
	}

	void UIManager::setupdraw(bool outline)
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

	void UIManager::draw_glare() {
		if (m_render_glare) {
			m_glare_handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
			NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
			float dir = convert_360(rot.z, 0, 360);
			if ((m_glare_direction == 0 || m_glare_direction - dir > 0.5) || m_glare_direction - dir < -0.5)
			{
				m_glare_direction = dir;
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_glare_handle, "SET_DATA_SLOT");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(m_glare_direction);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			}
			GRAPHICS::DRAW_SCALEFORM_MOVIE(m_glare_handle, (m_PosX + 0.3456f - glare_x_offset), (m_DrawBaseY + (m_HeaderHeight / 2.f) + 0.38f), (m_Width + 0.82700f), (m_HeaderHeight + 0.852f), 255, 255, 255, 255, 0);
		}
	}

	void UIManager::OnTick()
	{
		std::lock_guard lock(m_Mutex);
		if (IsMouseLocked())
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			ShowCursor(true);
			SetCursor(LoadCursorA(NULL, IDC_ARROW));
			

		}
		if (g_Settings.command_window)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			if (!g_Render->m_Opened) {
				ShowCursor(true);
				SetCursor(LoadCursorA(NULL, IDC_ARROW));
			}
			


		}

		if (g_Render->m_Opened && g_Settings.m_LockMouse)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}

		//RenderToolTip
		if (!g_Render->m_Opened)
		{
			RenderToolTip();
		}




		CheckForInput();

		HandleInput();
		LoadYTD();

		if (m_Opened)
		{
			// Drawing order
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
				g_Render->m_CurrentSubMenuName = submenu_enabled ? header_name.c_str() : sub->GetName();
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

	void UIManager::CheckForInput()
	{
		ResetInput();
		m_OpenKeyPressed = IsKeyPressed(open_key);
		m_OpenKeyPressed2 = IsKeyPressed(VK_INSERT);
		m_BackKeyPressed = IsKeyPressed(VK_BACK);
		m_EnterKeyPressed = IsKeyPressed(VK_RETURN);
		m_UpKeyPressed = IsKeyPressed(VK_UP);
		m_DownKeyPressed = IsKeyPressed(VK_DOWN);
		m_LeftKeyPressed = IsKeyPressed(VK_LEFT);
		m_RightKeyPressed = IsKeyPressed(VK_RIGHT);
	}

	void UIManager::HandleInput()
	{
		if (controlsEnabled && !g_Settings.command_window) {
			static Timer openTimer(0ms);
			openTimer.SetDelay(std::chrono::milliseconds(m_OpenDelay));
			if (m_OpenKeyPressed && openTimer.Update())
			{
				if (!m_Opened) {
					MenuOpeningAnimation();
				}
				else {
					MenuClosingAnimation();

				}

				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
			}
			if (!PAD::IS_USING_KEYBOARD_AND_MOUSE(2)) {
				if (PAD::IS_CONTROL_PRESSED(2, 227) && PAD::IS_CONTROL_PRESSED(2, INPUT_CELLPHONE_RIGHT) && openTimer.Update())
				{
					if (!m_Opened) {
						MenuOpeningAnimation();
					}
					else {
						MenuClosingAnimation();
					}

					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
				}
			}
			if (m_OpenKeyPressed2 && openTimer.Update())
			{
				if (!m_Opened) {
					MenuOpeningAnimation();
				}
				else {
					MenuClosingAnimation();
				}

				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
			}
			static Timer backTimer(0ms);
			backTimer.SetDelay(std::chrono::milliseconds(m_BackDelay));
			if (m_Opened && m_BackKeyPressed && backTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

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
			if (m_Opened && PAD::IS_CONTROL_PRESSED(2, 194) && backTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

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
				
				PAD::DISABLE_CONTROL_ACTION(2, 0, true);
				PAD::DISABLE_CONTROL_ACTION(2, 19, true);
				PAD::DISABLE_CONTROL_ACTION(2, 140, true);
				PAD::DISABLE_CONTROL_ACTION(2, 20, true);
				PAD::DISABLE_CONTROL_ACTION(2, 27, true);
				PAD::DISABLE_CONTROL_ACTION(2, 80, true);
				PAD::DISABLE_CONTROL_ACTION(2, 337, true);
				PAD::DISABLE_CONTROL_ACTION(2, 27, true);
				PAD::DISABLE_CONTROL_ACTION(2, 85, true);
				PAD::DISABLE_CONTROL_ACTION(2, 74, true);
				PAD::DISABLE_CONTROL_ACTION(2, 58, true);
				PAD::DISABLE_CONTROL_ACTION(2, 70, true);
				auto sub = m_SubmenuStack.top();
				
				static Timer enterTimer(0ms);
				enterTimer.SetDelay(std::chrono::milliseconds(m_EnterDelay));
				if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::EnterPress);
					}
				}
				if (PAD::IS_CONTROL_PRESSED(2, 191) && sub->GetNumOptions() != 0 && enterTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::EnterPress);
					}
				}
				static Timer upTimer(0ms);
				upTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
				if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					sub->ScrollBackward();
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (opt->GetFlag(OptionFlag::UnclickOption))
						{
							sub->ScrollBackward();
						}
					}
				}
				if (PAD::IS_CONTROL_PRESSED(2, 172) && sub->GetNumOptions() != 0 && upTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					sub->ScrollBackward();
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (opt->GetFlag(OptionFlag::UnclickOption))
						{
							sub->ScrollBackward();
						}
					}
				}
				static Timer downTimer(0ms);
				downTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
				if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					sub->ScrollForward();
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (opt->GetFlag(OptionFlag::UnclickOption))
						{
							sub->ScrollForward();
						}
					}

				}
				if (PAD::IS_CONTROL_PRESSED(2, 173) && sub->GetNumOptions() != 0 && downTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					sub->ScrollForward();
					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						if (opt->GetFlag(OptionFlag::UnclickOption))
						{
							sub->ScrollForward();
						}
					}

				}
				static Timer leftTimer(0ms);
				leftTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
				if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::LeftPress);
					}
				}
				if (PAD::IS_CONTROL_PRESSED(2, 174) && sub->GetNumOptions() != 0 && leftTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::LeftPress);
					}
				}
				static Timer rightTimer(0ms);
				rightTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
				if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::RightPress);
					}
				}
				if (PAD::IS_CONTROL_PRESSED(2, 175) && !PAD::IS_CONTROL_PRESSED(2, 227) && sub->GetNumOptions() != 0 && rightTimer.Update())
				{
					if (m_Sounds)
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

					if (auto opt = sub->GetOption(sub->GetSelectedOption()))
					{
						opt->HandleAction(OptionAction::RightPress);
					}
				}
			}
		}
	}

	void UIManager::ResetInput()
	{
		m_OpenKeyPressed = false;
		m_BackKeyPressed = false;
		m_EnterKeyPressed = false;
		m_UpKeyPressed = false;
		m_DownKeyPressed = false;
		m_LeftKeyPressed = false;
		m_RightKeyPressed = false;
	}
	
	void UIManager::DrawHeader()
	{
		switch (m_HeaderType)
		{
		case HeaderType::Static:
			DrawRect(
				m_PosX,
				m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width,
				m_HeaderHeight,
				m_HeaderBackgroundColor);

			break;
		case HeaderType::YTD:
			for (std::size_t i = 0; i < (m_HeaderGradientTransparent ? 1 : 20); ++i)
			{
				DrawSprite(
					"Textures",
					"Header",
					m_PosX,
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width,
					m_HeaderHeight,
					m_HeaderBackgroundColor,
					0.f);
				
			}
			break;

			break;
		}
		if (m_HeaderNativeText)
		{
			DrawLeftText(
				m_CurrentSubMenuName,
				m_PosX - (m_Width / 2.1f) - header_x_offset,
				m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
				m_HeaderTextSize,
				m_HeaderFont,
				m_HeaderTextColor,
				false, true);
		}
		draw_glare();
		m_DrawBaseY += m_HeaderHeight;
	}
	void UIManager::DrawSubmenuBar(AbstractSubmenu* sub)
	{
		if (submenu_enabled) {
			char leftText[64] = {};
			std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
			std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>(toupper(c)); });

			char rightText[32] = {};
			std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());

			

			DrawRect(
				m_PosX,
				m_DrawBaseY + (m_SubheaderHeight / 2.f),
				m_Width, m_SubheaderHeight,
				m_SubheaderBackground);


			DrawLeftText(
				&leftText[0],
				m_PosX - (m_Width / m_OptionPadding) - 0.002f,
				m_DrawBaseY + (0.03f / 2.f) - (GetTextHeight(Font::ChaletLondon, 0.25f) / 1.5f),
				0.25f, Font::ChaletLondon,
				m_SubheaderText,
				false, true);
			DrawRightText(
				&rightText[0],
				m_PosX + (m_Width / 2.1f),
				m_DrawBaseY + (0.03f / 2.f) - (GetTextHeight(Font::ChaletLondon, 0.25f) / 1.5f),
				0.25f, Font::ChaletLondon,
				m_SubheaderTextRight,
				false, true);

			if (lines_enabled) {
				GRAPHICS::DRAW_RECT(m_PosX, m_DrawBaseY + (0.0005f / 2.0f) + 0.031, m_Width, 0.0018f, m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, m_HeaderBackgroundColor.a, 0);
			}



			m_DrawBaseY += 0.03f;
		}




	}
	void drawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
		{
			GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0, -1);
		}
		else
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
		}
	}
	void UIManager::DrawOption(AbstractOption* opt, bool selected)
	{
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(1);
		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_OptionHeight / 2.f),
			m_Width,
			m_OptionHeight,
			m_OptionUnselectedBackgroundColor);
		if (selected)
		{
			m_CurrentCoord = lerp(m_CurrentCoord, m_DrawBaseY + (m_OptionHeight / 2.f), smooth_scroll_speed); m_OptionSelectedTextColor;
				GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(2);
				DrawRect(
					m_PosX,
					m_CurrentCoord,
					m_Width,
					m_OptionHeight,
					m_OptionSelectedBackgroundColor);
			
		}

		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(3);
		if (opt->GetFlag(OptionFlag::PlayerSub)) {
			
			DrawLeftText(
				opt->GetLeftText(),
				m_PosX - (m_Width / m_OptionPadding) - 0.002f,
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
				m_OptionTextSize,
				m_OptionFont,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false
			);
		}
		else {
			DrawLeftText(
				opt->GetLeftText(),
				m_PosX - (m_Width / m_OptionPadding) - 0.002f,
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
				m_OptionTextSize,
				m_OptionFont,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false);
		}
		
		if (opt->GetFlag(OptionFlag::BoolWithNumber)) {
			if (selected) {

				auto res = GetSpriteScale(0.030);
				auto res2 = GetSpriteScale(0.033);
				DrawSprite("commonmenu", "shop_arrows_upanddown", m_PosX + (m_Width / m_OptionPadding) - 0.016f, m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, 90.0);

				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.022,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else {
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.01,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
		}
		else if (opt->GetFlag(OptionFlag::Horizontal)) {
			if (selected) {

				auto res = GetSpriteScale(0.030);
				auto res2 = GetSpriteScale(0.033);
				DrawSprite("commonmenu", "shop_arrows_upanddown", m_PosX + (m_Width / m_OptionPadding) - 0.005f, m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, 90.0);

				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.012,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else {
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
		}
		else if (opt->GetFlag(OptionFlag::ChooseBool)) {
			if (selected) {

				auto res = GetSpriteScale(0.030);
				auto res2 = GetSpriteScale(0.033);
				DrawSprite("commonmenu", "shop_arrows_upanddown", m_PosX + (m_Width / m_OptionPadding) - 0.015, m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, 90.0);

				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.020,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else {
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.01,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f) - 0.001,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
		}
		else if (opt->GetFlag(OptionFlag::Choose)) {
			if (selected) {
				auto res = GetSpriteScale(0.030);
				auto res2 = GetSpriteScale(0.033);
				DrawSprite("commonmenu", "shop_arrows_upanddown", m_PosX + (m_Width / m_OptionPadding - 0.005f), m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, 90.0);

				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding) - 0.012,
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else {
				DrawRightText(
					opt->GetRightText(),
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
					m_OptionTextSize,
					m_OptionFont,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
		}
		else if (opt->GetFlag(OptionFlag::Keyboard)) {
			auto res = GetSpriteScale(0.0185);
			auto res2 = GetSpriteScale(0.0185);
			DrawRightText(
				opt->GetRightText(),
				m_PosX + (m_Width / m_OptionPadding - 0.01f),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 2) - 0.003,
				m_OptionTextSize,
				m_OptionFont,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false);
			DrawSprite("Textures", "Pen", m_PosX + (m_Width / m_OptionPadding - 0.004f), m_DrawBaseY + (m_OptionHeight / 2.f), res2.x, res.y, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, 0.0);
		}
		
		else {
			DrawRightText(
				opt->GetRightText(),
				m_PosX + (m_Width / m_OptionPadding),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
				m_OptionTextSize,
				m_OptionFont,
				selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
				false, false);
		}
		DrawCenteredText(
			opt->GetCenteredText(),
			m_PosX,
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_SeperatorFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize + 0.02f,
			m_SeperatorFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);
		
		if (opt->GetFlag(OptionFlag::BoolWithNumber) || opt->GetFlag(OptionFlag::ChooseBool) || opt->GetFlag(OptionFlag::BoolOption))
		{
			auto res = GetSpriteScale(0.025f);
			auto res2 = GetSpriteScale(0.032f);
			if (ToggleIterator == 0)
			{
				if (ToggledOn)
				{
					GRAPHICS::DRAW_SPRITE("CommonMenu", "common_medal",
						g_Render->m_PosX + (g_Render->m_Width / g_Render->m_OptionPadding - 0.005f)
						, g_Render->m_DrawBaseY + (g_Render->m_OptionHeight / 2.5f) - (g_Render->GetTextHeight(g_Render->m_OptionFont
							, g_Render->m_OptionTextSize) / 1.5f) + 0.014f
						, res.x, res.y, 0.0, m_ToggleOnColor.r, m_ToggleOnColor.g, m_ToggleOnColor.b, m_ToggleOnColor.a, false, false);
				}
				else if (!ToggledOn)
				{
					GRAPHICS::DRAW_SPRITE("CommonMenu", "common_medal",
						g_Render->m_PosX + (g_Render->m_Width / g_Render->m_OptionPadding - 0.005f)
						, g_Render->m_DrawBaseY + (g_Render->m_OptionHeight / 2.5f) - (g_Render->GetTextHeight(g_Render->m_OptionFont
							, g_Render->m_OptionTextSize) / 1.5f) + 0.014f
						, res.x, res.y, 0.0, m_ToggleOffColor.r, m_ToggleOffColor.g, m_ToggleOffColor.b, m_ToggleOffColor.a, false, false);
				}
			}
			else if (ToggleIterator == 1)
			{
				if (ToggledOn)
				{
					GRAPHICS::DRAW_SPRITE("CommonMenu", "shop_box_tick",
						g_Render->m_PosX + (g_Render->m_Width / g_Render->m_OptionPadding - 0.005f)
						, g_Render->m_DrawBaseY + (g_Render->m_OptionHeight / 2.5f) - (g_Render->GetTextHeight(g_Render->m_OptionFont
							, g_Render->m_OptionTextSize) / 1.5f) + 0.014f
						, res2.x, res2.y, 0.0, m_ToggleCheckColor.r, m_ToggleCheckColor.g, m_ToggleCheckColor.b, m_ToggleCheckColor.a, false, false);

				}
				else if (!ToggledOn)
				{
					GRAPHICS::DRAW_SPRITE("CommonMenu", "shop_box_blank",
						g_Render->m_PosX + (g_Render->m_Width / g_Render->m_OptionPadding - 0.005f)
						, g_Render->m_DrawBaseY + (g_Render->m_OptionHeight / 2.5f) - (g_Render->GetTextHeight(g_Render->m_OptionFont
							, g_Render->m_OptionTextSize) / 1.5f) + 0.014f
						, res2.x, res2.y, 0.0, m_ToggleCheckColor.r, m_ToggleCheckColor.g, m_ToggleCheckColor.b, m_ToggleCheckColor.a, false, false);
				}
			}
			else if (ToggleIterator == 3) {
				if (ToggledOn)
				{
					drawSprite("commonmenu", "shop_tick_icon", (m_PosX + (m_Width / m_OptionPadding - 0.004f)), m_DrawBaseY + (m_OptionHeight / 2.0f), toggle_width, toggle_height, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, toggle_on_rotation);

				}
				else if (!ToggledOn)
				{


					drawSprite("shared", "menuplus_32", (m_PosX + (m_Width / m_OptionPadding - 0.004f)), m_DrawBaseY + (m_OptionHeight / 2.0f), toggle_width_off, toggle_height_off, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, toggle_off_rotation);


				}

			}
			else if (ToggleIterator == 4) {
				if (ToggledOn)
				{
					drawSprite(custom_toggle_dict_on.c_str(), custom_toggle_asset_on.c_str(), (m_PosX + (m_Width / m_OptionPadding - 0.004f)), m_DrawBaseY + (m_OptionHeight / 2.0f), toggle_width, toggle_height, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, toggle_on_rotation);

				}
				else if (!ToggledOn)
				{


					drawSprite(custom_toggle_dict_off.c_str(), custom_toggle_asset_off.c_str(), (m_PosX + (m_Width / m_OptionPadding - 0.004f)), m_DrawBaseY + (m_OptionHeight / 2.0f), toggle_width_off, toggle_height_off, selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor, toggle_off_rotation);


				}

			}
		}
		if (opt->GetFlag(OptionFlag::Enterable))
		{
			if (IndicatorIterator == 0)
			{


				DrawRightText(
					">",
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, 0.35) / 1.725f) - 0.001,
					0.35,
					Font::Monospace,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else if (IndicatorIterator == 1)
			{
				DrawRect(m_PosX + (m_Width / m_OptionPadding) + 0.003f, m_DrawBaseY + ((m_OptionHeight) / 2.f), 0.0035f, m_OptionHeight, { m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, sub_alpha });
			}
		}
		if (opt->GetFlag(OptionFlag::PlayerSub))
		{
			if (IndicatorIterator == 0)
			{


				DrawRightText(
					">",
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, 0.35) / 1.725f) - 0.001,
					0.35,
					Font::Monospace,
					selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
					false, false);
			}
			else if (IndicatorIterator == 1)
			{
				DrawRect(m_PosX + (m_Width / m_OptionPadding) + 0.003f, m_DrawBaseY + ((m_OptionHeight) / 2.f), 0.0035f, m_OptionHeight, { m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, sub_alpha });
			}
		}

		m_DrawBaseY += m_OptionHeight;
	}

	void UIManager::DrawSprite1(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(textureDict))
		{
			GRAPHICS::DRAW_SPRITE1(textureDict, textureName, screenX, screenY, width, height, heading, red, green, blue, alpha, 0);
		}
		else
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(textureDict, false);
		}
	}

	void UIManager::DrawFooter()
	{
		if (footer_enabled) {
			float size = m_FooterSpriteSize;
			float rotation = 0.f;
			const char* texture = "shop_arrows_upanddown";
			auto sub = m_SubmenuStack.top();

			if (!m_SubmenuStack.empty())
			{
				if (!freeze_icon) {
					if (sub->GetSelectedOption() == 0)
					{
						rotation = 90.f;
						texture = "arrowright";
						size *= 0.8f;
					}
					else if (sub->GetSelectedOption() + 1 == sub->GetNumOptions())
					{
						rotation = 270.f;
						texture = "arrowright";
						size *= 0.8f;
					}
				}
			}

			if (sub->GetNumOptions() >= m_OptionsPerPage && m_dynamic_footer) {

				auto sizee = GetSpriteScale(size);

				DrawRect(
					m_PosX,
					m_DrawBaseY + (m_FooterHeight / 2.f),
					m_Width,
					m_FooterHeight,
					m_FooterBackgroundColor);

				DrawSprite(
					"commonmenu",
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
					DrawLeftText(
						VERSION_TYPE,
						m_PosX - (m_Width / m_FooterTextPadding),
						m_DrawBaseY + (m_FooterHeight / 2.f) - (GetTextHeight(m_FooterTextFont, m_FooterTextSize) / 1.5f),
						m_FooterTextSize, m_FooterTextFont,
						m_FooterTextColor,
						false, true);
				}
				if (RightFooterText) {
					DrawRightText(
						g_GameVariables->m_version,
						m_PosX + (m_Width / m_FooterTextPadding),
						m_DrawBaseY + (m_FooterHeight / 2.f) - (GetTextHeight(m_FooterTextFont, m_FooterTextSize) / 1.5f),
						m_FooterTextSize, m_FooterTextFont,
						m_FooterTextColor,
						false, true);
				}

				m_DrawBaseY += m_FooterHeight;
			}
			else if (!m_dynamic_footer) {
				auto sizee = GetSpriteScale(size);

				DrawRect(
					m_PosX,
					m_DrawBaseY + (m_FooterHeight / 2.f),
					m_Width,
					m_FooterHeight,
					m_FooterBackgroundColor);

				DrawSprite(
					"commonmenu",
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
					DrawLeftText(
						"Saint Paid",
						m_PosX - (m_Width / m_FooterTextPadding),
						m_DrawBaseY + (m_FooterHeight / 2.f) - (GetTextHeight(m_FooterTextFont, m_FooterTextSize) / 1.5f),
						m_FooterTextSize, m_FooterTextFont,
						m_FooterTextColor,
						false, true);
				}
				if (RightFooterText) {
					DrawRightText(
						g_GameVariables->m_version,
						m_PosX + (m_Width / m_FooterTextPadding),
						m_DrawBaseY + (m_FooterHeight / 2.f) - (GetTextHeight(m_FooterTextFont, m_FooterTextSize) / 1.5f),
						m_FooterTextSize, m_FooterTextFont,
						m_FooterTextColor,
						false, true);
				}
				if (lines_enabled) {
					GRAPHICS::DRAW_RECT(m_PosX, m_DrawBaseY + (0.001f / 2.0f), m_Width, 0.0018f, m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, m_HeaderBackgroundColor.a, 0);
				}
				m_DrawBaseY += m_FooterHeight;
			}
		}
	}

	void UIManager::DrawDescription()
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

		m_DrawBaseY += m_DescriptionHeightPadding;


		GRAPHICS::DRAW_RECT(m_PosX, m_DrawBaseY + (m_DescriptionHeight / 2.f), m_Width, m_DescriptionHeight, m_OptionUnselectedBackgroundColor.r, m_OptionUnselectedBackgroundColor.g, m_OptionUnselectedBackgroundColor.b, m_OptionUnselectedBackgroundColor.a, 0);
		GRAPHICS::DRAW_RECT(m_PosX, m_DrawBaseY + (m_DescriptionHeight / 2.f) - 0.029, m_Width, 0.003f, m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, m_HeaderBackgroundColor.a, 0);
		HUD::SET_TEXT_WRAP(m_PosX, m_PosX + m_Width / 2);
		DrawLeftText(
			description,
			m_PosX - (m_Width / m_DescriptionPadding),
			m_DrawBaseY + (m_DescriptionHeight / 2.f) - (GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f) - 0.015,
			m_DescriptionTextSize,
			m_DescriptionFont,
			m_DescriptionTextColor,
			false, false, false
		);

		m_DrawBaseY += m_DescriptionHeight;
	}

	void UIManager::DrawRect(float x, float y, float width, float height, Color color)
	{
		if (m_MenuOpeningAnimation) {
			GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, 255, 0);
		}
		else {
			GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
		}
	}

	void UIManager::DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
		{
			if (m_MenuOpeningAnimation) {
				GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, 255, NULL, NULL);
			}
			else {
				GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, NULL, NULL);
			}
		}
		else
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
		}
	}

	void UIManager::DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow, bool wrap)
	{
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		if (m_MenuOpeningAnimation) {
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
		}
		else {
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
		}
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();
		if (wrap) {

		}
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
	}

	void UIManager::DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_CENTRE(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void UIManager::DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_WRAP(0.f, x);
		HUD::SET_TEXT_RIGHT_JUSTIFY(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	float UIManager::GetTextHeight(Font font, float size)
	{
		return HUD::GET_RENDERED_CHARACTER_HEIGHT(size, static_cast<int>(font));
	}

	Vector2 UIManager::GetSpriteScale(float size)
	{
		int x;
		int y;
		GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&x, &y);

		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}

	bool UIManager::IsMouseLocked()
	{
		return m_Opened && m_MouseLocked;
	}

	Rectangle UIManager::GetMenuRect()
	{
		float height = m_HeaderHeight;

		if (!m_SubmenuStack.empty())
		{
			height += m_OptionHeight * std::min(m_SubmenuStack.top()->GetNumOptions(), m_OptionsPerPage);
		}

		height += m_FooterHeight;

		return
		{
			{ m_PosX + (m_Width / 2.f), m_PosY + (height / 2.f) },
			{ m_Width, height }
		};
	}

	Vector2 UIManager::GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);

		return Vector2{ static_cast<float>(point.x), static_cast<float>(point.y) };
	}
	void UIManager::SetMousePos(int x, int y)
	{
		SetCursorPos(x, y);
	}
}
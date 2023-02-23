#include "Interface.hpp"
#include "../Timer.hpp"
#include "../Natives.hpp"
#include "../FiberHelper.hpp"
#include "UnclickOption.hpp"

#define VERSION 4
#define DEV_MODE
//#define TESTER_MODE
//#define RELEASE_MODE


#ifdef DEV_MODE
#undef RELEASE_MODE
#undef TESTER_MODE
#define VERSION_TYPE "DEV"
#endif

namespace Arctic::UserInterface
{
	void MenuOpeningAnimation()
	{
		g_FiberPool.queue([]
			{
		g_Render->m_MenuOpeningAnimation = true;
		g_Render->m_Opened = true;
		g_Render->g_MenuAlpha = 0;
		g_Render->m_HeaderTextColor.a = 0;
		fbr::cur()->wait(10ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha + 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha + 5;
		g_Render->m_MenuOpeningAnimation = false;
			});
	}
	void MenuClosingAnimation()
	{
		g_FiberPool.queue([]
			{
		g_Render->m_MenuOpeningAnimation = true;
		g_Render->m_Opened = true;
		//g_Render->g_MenuAlpha = 255;
		g_Render->m_HeaderTextColor.a = 255;
		fbr::cur()->wait(10ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		fbr::cur()->wait(1ms);
		g_Render->m_HeaderTextColor.a = g_Render->g_MenuAlpha - 5;
		g_Render->g_MenuAlpha = g_Render->g_MenuAlpha - 5;
		g_Render->m_Opened = false;
		g_Render->m_MenuOpeningAnimation = false;
		});
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
			"Get Good Get Arctic Cheats",
			"Sexy Arctic Cheats",
		};

		if (!g_HasSetToolTip)
		{
			g_ToolTip = random(0, 2);
			g_HasSetToolTip = true;
		}

		char text[200];

		if (PAD::IS_USING_KEYBOARD_AND_MOUSE(2)) {
			sprintf_s(text, "%s\n~u~%s", names[g_ToolTip], "~c~F4");
			RenderText(text, 0.5f, 0.09f, Font::ChaletLondon, 0.4f, m_ToolTipColor, true, false, false);
		}
		else {
			sprintf_s(text, "%s\n~c~RB + RIGHT", names[g_ToolTip]);
			RenderText(text, 0.5f, 0.09f, Font::ChaletLondon, 0.2f, m_ToolTipColor, true, false, false);
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

	void UIManager::Welcome() {

		if (m_Welcome)
		{
			char WelcomeText[60];
			snprintf(WelcomeText, sizeof(WelcomeText), "Welcome ~w~%s", PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()));
			setupdraw(true);
			HUD::SET_TEXT_FONT(6);
			HUD::SET_TEXT_SCALE(0.5f, 0.5f);
			HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
			HUD::SET_TEXT_CENTRE(0);
			drawstring(WelcomeText, 0.020f, 0.010f);
		}
	}

	void UIManager::MenuVersion() {

		if (m_MenuVersion)
		{
			char MenuVersionText[60];
			snprintf(MenuVersionText, sizeof(MenuVersionText), "Arctic Version: V2.5");
			setupdraw(true);
			HUD::SET_TEXT_FONT(6);
			HUD::SET_TEXT_SCALE(0.5f, 0.5f);
			HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
			HUD::SET_TEXT_CENTRE(0);
			drawstring(MenuVersionText, 0.020f, 0.040f);
		}
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
			GRAPHICS::DRAW_SCALEFORM_MOVIE(m_glare_handle, (m_PosX + 0.345f), (m_DrawBaseY + (m_HeaderHeight / 2.f) + 0.38f), (m_Width + 0.82700f), (m_HeaderHeight + 0.852f), 255, 255, 255, 255, 0);
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

		if (g_Render->m_Opened && g_Settings.m_LockMouse)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}

		//RenderToolTip
		if (!g_Render->m_Opened)
		{
			RenderToolTip();
		}

		if (ThemeIterator == 0)
		{
			//Header
			g_Render->m_HeaderBackgroundColor = { 138, 43, 226, 255 };

			//Footer
			g_Render->m_FooterBackgroundColor = { 138, 43, 226, 255 };

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 138, 43, 226, 255 };

			//Description
			g_Render->m_DescriptionBackgroundColor = { 138, 43, 226, 255 };

			//Background
			g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

			//Logger
			//g_Logger->Theme("Default Theme");
		}

		if (ThemeIterator == 1)
		{
			//Header
			g_Render->m_HeaderBackgroundColor = { 255, 108, 116, 255 };

			//Footer
			g_Render->m_FooterBackgroundColor = { 255, 108, 116, 255 };

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 255, 108, 116, 255 };

			//Description
			g_Render->m_DescriptionBackgroundColor = { 255, 108, 116, 255 };

			//Background
			g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

			//Logger
			//g_Logger->Theme("Salmon Red Theme");
		}

		if (ThemeIterator == 2)
		{
			//Header
			g_Render->m_HeaderBackgroundColor = { 15, 82, 186, 255 };

			//Footer
			g_Render->m_FooterBackgroundColor = { 15, 82, 186, 255 };

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 15, 82, 186, 255 };

			//Description
			g_Render->m_DescriptionBackgroundColor = { 15, 82, 186, 255 };

			//Background
			g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

			//Logger
			//g_Logger->Theme("Sapphire Blue Theme");
		}

		if (ThemeIterator == 3)
		{
			//Header
			g_Render->m_HeaderBackgroundColor = { 24, 26, 24, 255 };

			//Footer
			g_Render->m_FooterBackgroundColor = { 24, 26, 24, 255 };

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 24, 26, 24, 255 };

			//Description
			g_Render->m_DescriptionBackgroundColor = { 24, 26, 24, 255 };

			//Background
			g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

			//Logger
			//g_Logger->Theme("Soft Black Theme");
		}

		if (ThemeIterator == 4)
		{
			//Header
			g_Render->m_HeaderBackgroundColor = { 0, 155, 119, 255 };

			//Footer
			g_Render->m_FooterBackgroundColor = { 0, 155, 119, 255 };

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 0, 155, 119, 255 };

			//Description
			g_Render->m_DescriptionBackgroundColor = { 0, 155, 119, 255 };

			//Background
			g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

			//Logger
			//g_Logger->Theme("Emerald Green Theme");
		}

		if (ThemeIterator == 5)
		{
			//Header
			g_Render->m_HeaderBackgroundColor = { 70, 38, 180, 255 };

			//Footer
			g_Render->m_FooterBackgroundColor = { 70, 38, 180, 255 };

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 70, 38, 180, 255 };

			//Description
			g_Render->m_DescriptionBackgroundColor = { 70, 38, 180, 255 };

			//Background
			g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

			//Logger
			//g_Logger->Theme("Violet Purple Theme");
		}

		if (ThemeIterator == 6)
		{
			//Header
			g_Render->m_HeaderBackgroundColor = { 255, 145, 164, 255 };

			//Footer
			g_Render->m_FooterBackgroundColor = { 255, 145, 164, 255 };

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 255, 145, 164, 255 };

			//Description
			g_Render->m_DescriptionBackgroundColor = { 255, 145, 164, 255 };

			//Background
			g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

			//Logger
			//g_Logger->Theme("Salmon Pink Theme");
		}

		if (ThemeIterator == 7)
		{
			//Header
			g_Render->m_HeaderBackgroundColor = { 17, 17, 17, 255 };

			//Footer
			g_Render->m_FooterBackgroundColor = { 17, 17, 17, 255 };
			g_Render->m_FooterSpriteColor = { 181,181,181, 255 };
			g_Render->m_FooterHeight = 0.030f;
			g_Render->m_FooterSpriteSize = 0.030f;

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 65, 60, 60, 255 };

			//Description
			g_Render->m_DescriptionBackgroundColor = { 0, 0, 0, 120 };

			//Background
			g_Render->m_OptionUnselectedBackgroundColor = { 30,35,36, 230 };

			//Option Height
			g_Render->m_OptionHeight = 0.033f;
			
			//Option Text Size
			g_Render->m_OptionTextSize = 0.29f;

			//Option Text Color
			g_Render->m_OptionUnselectedTextColor = { 181,181,181, 255 };
			g_Render->m_OptionSelectedTextColor = { 181,181,181, 255 };

			//Logger
			//g_Logger->Theme("Salmon Pink Theme");
		}

		MenuVersion();
		
		Welcome();

		CheckForInput();

		HandleInput();

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
				g_Render->m_CurrentSubMenuName = sub->GetName();
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
		m_OpenKeyPressed = IsKeyPressed(VK_F4);
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
		
		if (m_Opened && !m_SubmenuStack.empty())
		{
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
		case HeaderType::Gradient:
			for (std::size_t i = 0; i < (m_HeaderGradientTransparent ? 1 : 20); ++i)
			{
				DrawSprite(
					"aircraft_dials",
					"aircraft_dials_g0",
					m_PosX - (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					m_HeaderGradientColorRight,
					m_HeaderGradientFlip ? 0.f : 180.f);
				DrawSprite(
					"aircraft_dials",
					"aircraft_dials_g0",
					m_PosX + (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					m_HeaderGradientColorLeft,
					m_HeaderGradientFlip ? 180.f : 0.f);
			}
			break;

			break;
		}
		if (m_HeaderNativeText)
		{
			DrawCenteredText(
				m_CurrentSubMenuName,
				m_PosX,
				m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
				m_HeaderTextSize,
				m_HeaderFont,
				m_HeaderTextColor,
				false, true);
		}
		draw_glare();
		m_DrawBaseY += m_HeaderHeight;
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
			m_CurrentCoord = lerp(m_CurrentCoord, m_DrawBaseY + (m_OptionHeight / 2.f), 0.15f);
			GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(2);
			DrawRect(
				m_PosX,
				m_CurrentCoord,
				m_Width,
				m_OptionHeight,
				m_OptionSelectedBackgroundColor);
		}

		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(3);
		DrawLeftText(
			opt->GetLeftText(),
			m_PosX - (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);
		DrawRightText(
			opt->GetRightText(),
			m_PosX + (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);
		DrawCenteredText(
			opt->GetCenteredText(),
			m_PosX,
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_SeperatorFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize + 0.02f,
			m_SeperatorFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);
		if (opt->GetFlag(OptionFlag::BoolOption))
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
						, res.x, res.y, 0.0, m_ToggleOnColor.r, m_ToggleOnColor.g, m_ToggleOnColor.b, m_ToggleOnColor.a,false,false);
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
		}

		if (opt->GetFlag(OptionFlag::Enterable))
		{
			if (IndicatorIterator == 0)
			{
				DrawRightText(
					">",
					m_PosX + (m_Width / m_OptionPadding),
					m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f),
					m_OptionTextSize,Font::Monospace,selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,false, false);
			}
			else if (IndicatorIterator == 1)
			{
				DrawRect(m_PosX + (m_Width / m_OptionPadding) + 0.003f,m_DrawBaseY + ((m_OptionHeight) / 2.f), 0.0035f,m_OptionHeight,{ m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, 190 });
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
		float size = m_FooterSpriteSize;
		float rotation = 0.f;
		const char* texture = "shop_arrows_upanddown";
		auto sub = m_SubmenuStack.top();

		if (!m_SubmenuStack.empty())
		{
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
					&rightText[0],
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
			std::snprintf(rightText, sizeof(rightText) - 1,  "%zu ~s~&#8226; %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());

			if (LeftFooterText) {
				DrawLeftText(
					"Arctic Private",
					m_PosX - (m_Width / m_FooterTextPadding),
					m_DrawBaseY + (m_FooterHeight / 2.f) - (GetTextHeight(m_FooterTextFont, m_FooterTextSize) / 1.5f),
					m_FooterTextSize, m_FooterTextFont,
					m_FooterTextColor,
					false, true);
			}
			if (RightFooterText) {
				DrawRightText(
					&rightText[0],
					m_PosX + (m_Width / m_FooterTextPadding),
					m_DrawBaseY + (m_FooterHeight / 2.f) - (GetTextHeight(m_FooterTextFont, m_FooterTextSize) / 1.5f),
					m_FooterTextSize, m_FooterTextFont,
					m_FooterTextColor,
					false, true);
			}

			m_DrawBaseY += m_FooterHeight;
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

		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_DescriptionHeight / 2.f),
			m_Width,
			m_DescriptionHeight,
			m_DescriptionBackgroundColor);

		DrawLeftText(
			description,
			m_PosX - (m_Width / m_DescriptionPadding),
			m_DrawBaseY + (m_DescriptionHeight / 2.f) - (GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f),
			m_DescriptionTextSize,
			m_DescriptionFont,
			m_DescriptionTextColor,
			false, false
		);

		m_DrawBaseY += m_DescriptionHeight;
	}

	void UIManager::DrawRect(float x, float y, float width, float height, Color color)
	{
		if (m_MenuOpeningAnimation) {
			GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, g_MenuAlpha, 0);
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
				GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, g_MenuAlpha, NULL, NULL);
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

	void UIManager::DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		if (m_MenuOpeningAnimation) {
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, g_MenuAlpha);
		}
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();

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
}
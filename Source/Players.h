#pragma once
#include "Natives.hpp" 
#include "UI/Interface.hpp"
#include "Selected.h"
namespace Arctic {
	class PlayersData {
	public:
		GetSelected get_selected;
		void get_theme(Color col) {
			switch (g_Render->ThemeIterator) {
			case 0:
				col = { 138, 43, 226, 255 };
				break;
			case 1:
				col = { 255, 108, 116, 255 };
				break;
			case 2:
				col = { 15, 82, 186, 255 };
				break;
			case 3:
				col = { 24, 26, 24, 255 };
				break;
			case 4:
				col = { 0, 155, 119, 255 };
				break;
			case 5:
				col = { 70, 38, 180, 255 };
			case 6:
				col = { 255, 145, 164, 255 };
				break;
			case 7:
				col = { 17, 17, 17, 255 };
				break;
			case 8:
				col = { 234, 90, 81, 255 };
				break;

			}
		}
		void drawText(const char* text, float x, float y, float size, int font, bool center, Color color, bool right) {
			HUD::SET_TEXT_SCALE(size, size);
			HUD::SET_TEXT_FONT(font);
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
			HUD::SET_TEXT_CENTRE(center);
			if (right) {
				HUD::SET_TEXT_WRAP(0.0f, x);
				HUD::SET_TEXT_RIGHT_JUSTIFY(true);
			}
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
		}
		float x_offset = 0.505;
		float y_offset = 0.105f;
		float width = 0.183f;
		float height = 0.178;
		void draw_info_text(const char* text, const char* text2, int pos, float x_offset, bool first = false) {
			Color col2 = { 255, 255, 255, 190 };
			if (first) {
				drawText(text, 0.505, 0.105f, 0.25f, 0, false, col2, false);
				drawText(text2, 0.630 - x_offset, 0.105f, 0.25f, 0, false, col2, false);
			}
			else {
				drawText(text, 0.505, 0.105f + 0.015f * pos, 0.25f, 0, false, col2, false);
				drawText(text2, 0.630 - x_offset, 0.105f + 0.015f * pos, 0.25f, 0, false, col2, false);
			}
		}
		void draw_info(std::uint32_t player) {
			float x = g_Render->m_PosX;
			float y = g_Render->m_PosY;
			Color col;
			GRAPHICS::DRAW_RECT(x - 0.210, y + -0.090 + 0.178, 0.183f, 0.178, g_Render->m_OptionUnselectedBackgroundColor.r, g_Render->m_OptionUnselectedBackgroundColor.g, g_Render->m_OptionUnselectedBackgroundColor.b, 160, false);
			Color col2 = { 255, 255, 255, 190 };
			char name[64];
			char name2[64];
			int netHandle[13];
			char run_speed[64];
			int infos = 2;
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, netHandle, 13);
			sprintf(name, "RID: %s", NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]));
			draw_info_text("Coords", "ALL TALK", 1, 0, true);
			draw_info_text("RID", NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]), 1, 0);
			
			switch (g_Render->ThemeIterator) {
			case 0:
				col = { 138, 43, 226, 255 };
				break;
			case 1:
				col = { 255, 108, 116, 255 };
				break;
			case 2:
				col = { 15, 82, 186, 255 };
				break;
			case 3:
				col = { 24, 26, 24, 255 };
				break;
			case 4:
				col = { 0, 155, 119, 255 };
				break;
			case 5:
				col = { 70, 38, 180, 255 };
			case 6:
				col = { 255, 145, 164, 255 };
				break;
			case 7:
				col = { 17, 17, 17, 255 };
				break;
			case 8:
				col = { 234, 90, 81, 255 };
				break;

			}
			GRAPHICS::DRAW_RECT(x - 0.210, y + -0.000, 0.183, -0.002, col.r, col.g, col.b, col.a, false);
			
		}
	};
	inline PlayersData g_players;
}
#pragma once
#include "Natives.hpp" 
#include "UI/Interface.hpp"
#include "Selected.h"
#include "Images.h"
#include "Caller.h"
namespace Saint {
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
				drawText(text2, 0.678 - x_offset, 0.105f, 0.25f, 0, false, col2, true);
			}
			else {
				drawText(text, 0.505, 0.105f + 0.015f * pos, 0.25f, 0, false, col2, false);
				drawText(text2, 0.678 - x_offset, 0.105f + 0.015f * pos, 0.25f, 0, false, col2, true);
			}
		}
		void drawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
		{
			if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
			{
				GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0, false);
			}
			else
			{
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
			}
		}
		
		void draw_info2(Hash hash) {
			
			float x = g_Render->m_PosX;
			float y = g_Render->m_PosY;
			Color col;
			GRAPHICS::DRAW_RECT(x - 0.210, y + -0.090 + 0.178, 0.183f, 0.178, g_Render->m_OptionUnselectedBackgroundColor.r, g_Render->m_OptionUnselectedBackgroundColor.g, g_Render->m_OptionUnselectedBackgroundColor.b, 160, false);
			Color col2 = { 255, 255, 255, 190 };

			char timesince[128];
			char max_speed[128];
			char seats[64];
			char price[128];
			char make[128];
			sprintf(timesince, "%.1f", VEHICLE::GET_VEHICLE_MODEL_ACCELERATION(hash));
			sprintf(max_speed, "%.0f MPH", (VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(hash)) * 2.23694);
			sprintf(seats, "%i", VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(hash));
			sprintf(price, "$%i", VEHICLE::GET_VEHICLE_MODEL_VALUE(hash));
			sprintf(make, "%s", VEHICLE::GET_MAKE_NAME_FROM_VEHICLE_MODEL(hash));
			//drawSprite(preview.dict, preview.texture, x + 0.3545595, y + -0.139, 0.1493f, 0.10f, { 255, 255, 255, 255 }, 0.0f);
			draw_info_text("Acceleration", timesince, 1, 0, true);
			draw_info_text("Max Speed (MPH)", max_speed, 1, 0);
			draw_info_text("Seats", seats, 2, 0);
			draw_info_text("Price", price, 3, 0);
			draw_info_text("Make", make, 4, 0);

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
		float pedx = 0.95f;
		float pedy = 0.196;
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
			char wanted_level[64];
			int infos = 2;
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, netHandle, 13);
			Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			int ms2 = PLAYER::GET_TIME_SINCE_LAST_DEATH(playerPed);

			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

			int sec = ms2 / 1000;

			ms2 = ms2 % 1000;

			int min = sec / 60;
			sec = sec % 60;

			int hour = min / 60;
			min = min % 60;

			if (ms2 == -1)
			{
				hour = 0;
				min = 0;
				sec = 0;
			}
			char timesince[128];
			NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
			sprintf(run_speed, "%i, %i, %i", (int)c.x, (int)c.y, (int)c.z);
			sprintf(wanted_level, "%i", PLAYER::GET_PLAYER_WANTED_LEVEL(player));
			sprintf(timesince, "%ih %im %is", hour, min, sec);
			std::string rockstar = NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(ped) ? "Yes" : "No";
			
			
			draw_info_text("Coords", run_speed, 1, 0, true);
			draw_info_text("RID", NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]), 1, 0);
			draw_info_text("Vehicle", (PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false) == 0) ? "N/A" : HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false)))), 2, 0);
			draw_info_text("Wanted Level", wanted_level, 3, 0);
			draw_info_text("Time Since Last Death", timesince, 4, 0);
			draw_info_text("Rockstar Dev", rockstar.c_str(), 5, 0);
			
			//draw_info_text("Clan Name", g_GameVariables->m_net_game_player(player)->m_clan_data.m_clan_name, 2, 0);

			//CNetGamePlayer* g_player = g_GameVariables->m_net_game_player(player);
			rage::joaat_t scene_hash = 0x390DCCF5;//0xAD197067, 0x390DCCF5, 0x3D8F5C29, 0x5ADFAFD0
			rage::joaat_t element = 0;
			CPed* local_ped = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_ped;
			uintptr_t ui_3d_draw_manager = *(uint64_t*)(g_GameVariables->ui_3d_draw_manager);

			Vector3 pos = { x - pedx, y * 0.8f, 0.65f };

			if (ui_3d_draw_manager) {

				DWORD* preset2 = call<DWORD*>(g_GameVariables->get_scene_preset, ui_3d_draw_manager, &scene_hash);
				DWORD* preset = preset2 + (0x2A0 * element);

				if (preset) {

					*(float*)(preset + 0x12) = 0;
					*(float*)(preset + 0x9) = -3.8f;//size
				}
				if (call<bool>(g_GameVariables->push_scene_preset_manager, ui_3d_draw_manager, &scene_hash)) {
					if (call<bool>(g_GameVariables->add_element_to_scene, ui_3d_draw_manager, &scene_hash, element, local_ped, pos, 1.0f)) {
						call<bool>(g_GameVariables->set_scene_element_lighting, ui_3d_draw_manager, &scene_hash, element, 1.6f);
					}
				}
			}

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

			//3dped 
			GRAPHICS::DRAW_RECT(x - 0.210, y + -0.090 + 0.485, 0.183f, 0.400, g_Render->m_OptionUnselectedBackgroundColor.r, g_Render->m_OptionUnselectedBackgroundColor.g, g_Render->m_OptionUnselectedBackgroundColor.b, 160, false);
			GRAPHICS::DRAW_RECT(x - 0.210, y + pedy, 0.183, -0.002, col.r, col.g, col.b, col.a, false);
		}
	};
	inline PlayersData g_players;
}
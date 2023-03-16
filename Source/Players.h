#pragma once
#include "Natives.hpp" 
#include "UI/Interface.hpp"
#include "Selected.h"
#include "Images.h"
#include "Caller.h"
#include <GTAV-Classes/script/globals/GlobalPlayerBD.hpp>
#include <GTAV-Classes/script/globals/GPBD_FM.hpp>
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
			float x = g_Render->m_PosX;
			Color col2 = { 255, 255, 255, 190 };
			float offset = 0.02;
			float xfr = x + 0.205f + offset;
			if (first) {
				drawText(text, xfr - 0.110f, 0.105f, 0.25f, 0, false, col2, false);
				drawText(text2, xfr + 0.066f -x_offset, 0.105f, 0.25f, 0, false, col2, true);
			}
			else {
				drawText(text, xfr - 0.110f, 0.105f + 0.015f * pos, 0.25f, 0, false, col2, false);
				drawText(text2, xfr + 0.066f - x_offset, 0.105f + 0.015f * pos, 0.25f, 0, false, col2, true);
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

		void draw_friend_info(int selected) {

			float x = g_Render->m_PosX;
			float y = g_Render->m_PosY;
			Color col;

			float offset = 0.023f;
			float xfr = x + 0.205f + offset - 0.025f;
			GRAPHICS::DRAW_RECT(xfr, y + -0.090 + 0.178, 0.183f, 0.178, g_Render->m_OptionUnselectedBackgroundColor.r, g_Render->m_OptionUnselectedBackgroundColor.g, g_Render->m_OptionUnselectedBackgroundColor.b, 160, false);
			Color col2 = { 255, 255, 255, 190 };

			char timesince[128];
			char max_speed[128];
			char seats[64];
			char price[128];
			char make[128];
			sprintf(timesince, "%s", g_GameVariables->m_friendRegistry->m_friends[selected]->m_is_joinable ? "Yes" : "No");
			sprintf(max_speed, "%i", (int)g_GameVariables->m_friendRegistry->m_friends[selected]->m_rockstar_id);
			//drawSprite(preview.dict, preview.texture, x + 0.3545595, y + -0.139, 0.1493f, 0.10f, { 255, 255, 255, 255 }, 0.0f);
			draw_info_text("Joinable", timesince, 1, 0, true);
			draw_info_text("RID", max_speed, 1, 0);

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
			GRAPHICS::DRAW_RECT(x - 0.510, y + -0.000, 0.183, -0.002, g_Render->m_HeaderBackgroundColor.r, g_Render->m_HeaderBackgroundColor.g, g_Render->m_HeaderBackgroundColor.b, 255, false);
			GRAPHICS::DRAW_RECT(xfr, y + -0.000, 0.183f, -0.002, g_Render->m_HeaderBackgroundColor.r, g_Render->m_HeaderBackgroundColor.g, g_Render->m_HeaderBackgroundColor.b, 255, false);
		}
		void draw_info2(Hash hash) {
			
			float x = g_Render->m_PosX;
			float y = g_Render->m_PosY;
			Color col;

			float offset = 0.023f;
			float xfr = x + 0.205f + offset - 0.025f;
			GRAPHICS::DRAW_RECT(xfr, y + -0.090 + 0.178, 0.183f, 0.178, g_Render->m_OptionUnselectedBackgroundColor.r, g_Render->m_OptionUnselectedBackgroundColor.g, g_Render->m_OptionUnselectedBackgroundColor.b, 160, false);
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
			GRAPHICS::DRAW_RECT(x - 0.510, y + -0.000, 0.183, -0.002, g_Render->m_HeaderBackgroundColor.r, g_Render->m_HeaderBackgroundColor.g, g_Render->m_HeaderBackgroundColor.b, 255, false);
			GRAPHICS::DRAW_RECT(xfr, y + -0.000, 0.183f, -0.002, g_Render->m_HeaderBackgroundColor.r, g_Render->m_HeaderBackgroundColor.g, g_Render->m_HeaderBackgroundColor.b, 255, false);
		}
		float pedx = 0.540f;
		float pedyy = 1.680f;
		float pedy = 0.196;
		int GetSpeed(Ped ped) {

			int speed = (int)round(ENTITY::GET_ENTITY_SPEED(ped) * 2.24);
			return speed;
		}
		char* GetWanted(Player p)
		{
			char buffer[20];
			int Stars = (int)PLAYER::GET_PLAYER_WANTED_LEVEL(p);
			sprintf_s(buffer, "%i/5", Stars);
			return buffer;
		}
		void Text(const char* text, Color color, Vector2 position, Vector2 size, bool center)
		{
			HUD::SET_TEXT_CENTRE(center);
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
			HUD::SET_TEXT_FONT(0);
			HUD::SET_TEXT_SCALE(size.x, size.y);
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
		}
		bool is_player_stand_user(std::int32_t player) {
			const char* name = PLAYER::GET_PLAYER_NAME(player);
			if (name != nullptr)
				if ((((std::uint64_t)(name - 0x24) >> 32) & 0xFFFFFFFF) == NULL)
					return true;
			return false;
		}
		CNetGamePlayer* get_net_player(std::uint32_t player) {
			return g_GameVariables->m_net_game_player(player) == nullptr ? nullptr : g_GameVariables->m_net_game_player(player);
		}
		rage::rlGamerInfo* get_net_data(std::uint32_t player) const
		{
			return g_GameVariables->m_net_game_player(player) == nullptr ? nullptr : g_GameVariables->m_net_game_player(player)->get_net_data();
		}
		Network* get_network()
		{
			return *g_GameFunctions->m_network;
		}
		rage::snPlayer* get_session_player(std::uint32_t player)
		{
			for (std::uint32_t i = 0; i < get_network()->m_game_session_ptr->m_player_count; i++)
			{
				if (get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == get_net_data(player)->m_host_token)
				{
					return get_network()->m_game_session_ptr->m_players[i];
				}
			}

			if (get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == get_net_data(player)->m_host_token)
				return &get_network()->m_game_session_ptr->m_local_player;

			return nullptr;
		}
		
		netAddress get_ip_address(std::uint32_t player)
		{
			
			if (player == PLAYER::PLAYER_ID())
				return (*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_net_player_data.m_external_ip;

			if (auto session_player = get_session_player(player))
				if (auto peer = g_GameFunctions->m_get_connection_peer(get_network()->m_game_session_ptr->m_net_connection_mgr, (int)get_session_player(player)->m_player_data.m_peer_id_2))
					return netAddress{ 
						((netConnectionPeer*)peer)->m_external_ip 
					};

			return { 0 };
		}
		void draw_info(std::uint32_t player) {
			Color m_InfoBG{ 0, 0, 0, 190 };
			float x = g_Render->m_PosX;
			float y = g_Render->m_PosY;
			float offset = 0.012;
			Color m_white{ 255, 255, 255, 255 };
			float PosX = x + 0.225f + offset;
			float PosY = y + 0.168f;
			float LTextX = PosX - 0.1225;
			float RTextX = PosX + 0.009f;
			float TextY = y - 0.055;
			float SeperatorX = PosX + 0.05;

			float RTextX2 = PosX + 0.1215f;

			float rightresult = 0.49f;
			float righttext = SeperatorX - 0.048f;

			float LeftOffset = SeperatorX - 0.0523f;

			g_Render->DrawRect(PosX, PosY + 0.0202f, 0.25f, 0.375f, m_InfoBG);//draw main info rect
			g_Render->DrawRect(PosX, PosY - 0.0220f * 7.652f, 0.25f, 0.002f, g_Render->m_HeaderBackgroundColor);//draw main info top bar 


			g_Render->DrawRect(PosX + 0.195, PosY + 0.0202f, 0.135f, 0.375f, m_InfoBG);//draw ped preview rect
			g_Render->DrawRect(PosX + 0.195, PosY - 0.0220f * 7.652f, 0.135f, 0.002f, g_Render->m_HeaderBackgroundColor);//draw ped preview top bar 


			//geo info

			g_Render->DrawRect(PosX, PosY + 0.28, 0.25f, 0.125, m_InfoBG);//draw geo info rect
			g_Render->DrawRect(PosX, PosY + 0.31 - 0.09375, 0.25f, 0.002f, g_Render->m_HeaderBackgroundColor);//draw geo info top bar 

			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			//std::string Health = ("%s", std::to_string(GetHealth(ped)));
			//std::string Armor = ("%s", std::to_string(GetArmor(ped, player)));

			NativeVector3 get_coords = ENTITY::GET_ENTITY_COORDS(ped, 0);
			std::string wantedlvl = GetWanted(player);
			std::string ammo = std::format("{}", WEAPON::GET_AMMO_IN_PED_WEAPON(ped, WEAPON::GET_SELECTED_PED_WEAPON(ped)));
			std::string coords = std::format("[{0},{1},{2}]", std::roundl(get_coords.x), std::roundl(get_coords.y), std::roundl(get_coords.z));



			Hash street[2]{};
			PATHFIND::GET_STREET_NAME_AT_COORD(get_coords.x, get_coords.y, get_coords.z, &street[0], &street[1]);
			std::string Street = HUD::GET_STREET_NAME_FROM_HASH_KEY(street[0]);
			std::string Zone = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ZONE::GET_NAME_OF_ZONE(get_coords.x, get_coords.y, get_coords.z));
			std::string heading = std::format("{}", roundf(ENTITY::GET_ENTITY_HEADING(ped)));

			NativeVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(ped, false);
			NativeVector3 selfCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(selfCoords.x, selfCoords.y, selfCoords.z, playerCoords.x, playerCoords.y, playerCoords.z, true);
			std::string Distance = std::format("{}m", roundf(distance));
			std::string Speed = std::to_string(GetSpeed(ped));
			std::string passive = PLAYER::IS_PLAYER_BATTLE_AWARE(ped) ? "Yes" : "No";
			std::string rockstar = NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(ped) ? "Yes" : "No";

			const char* playerstate2 = "None / If you see this, buy a lottery ticket!";
			const char* parachutestate2 = "None";
			Ped playerPed = ped;
			if (PED::GET_PED_PARACHUTE_STATE(playerPed) == 0)
			{
				parachutestate2 = "Wearing";

			}
			if (PED::GET_PED_PARACHUTE_STATE(playerPed) == 1)
			{
				parachutestate2 = "Opening";
			}
			if (PED::GET_PED_PARACHUTE_STATE(playerPed) == 2)
			{
				parachutestate2 = "Open";
			}
			if (PED::GET_PED_PARACHUTE_STATE(playerPed) == 3)
			{
				parachutestate2 = "Falling To Death";
			}


			if (PED::IS_PED_RAGDOLL(playerPed))
			{
				playerstate2 = "Ragdolling";
			}
			if (PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
			{
				playerstate2 = "Respawning";
			}
			if (!PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_STILL(playerPed) && !PED::IS_PED_RAGDOLL(playerPed) && !PED::IS_PED_RELOADING(playerPed) && !TASK::IS_PED_GETTING_UP(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1));
			{
				playerstate2 = "Standing Still";
			}
			if (TASK::IS_PED_GETTING_UP(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
			{
				playerstate2 = "Getting Up From Ragdoll";
			}
			if (PED::IS_PED_RELOADING(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
			{
				playerstate2 = "Reloading";
			}
			if (PED::IS_PED_SHOOTING(playerPed) && !PED::IS_PED_DOING_DRIVEBY(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
			{
				playerstate2 = "Shooting";
			}
			if (PED::IS_PED_DOING_DRIVEBY(playerPed))
			{
				playerstate2 = "Doing Drive-by";
			}
			if (PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_SPRINTING(playerPed) || PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_RUNNING(playerPed) && !PED::IS_PED_RELOADING(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
			{
				playerstate2 = "Sprinting & Shooting";
			}
			if (!PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_SPRINTING(playerPed) || !PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_RUNNING(playerPed) && !PED::IS_PED_RELOADING(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
			{
				playerstate2 = "Sprinting";
			}
			if (PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_WALKING(playerPed) && !PED::IS_PED_RELOADING(playerPed))
			{
				playerstate2 = "Shooting & Walking";
			}
			if (!PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_WALKING(playerPed) && !PED::IS_PED_RELOADING(playerPed))
			{
				playerstate2 = "Walking";
			}
			if (PED::IS_PED_JUMPING(playerPed) && !TASK::IS_PED_GETTING_UP(playerPed))
			{
				playerstate2 = "Jumping";
			}
			char wantedLevel[128];
			//info
			//g_Render->DrawRect(SeperatorX - 0.05, TextY + 0.135f, 0.001f, 0.015f, m_white);
			if (!PLAYER::ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(playerPed))
			{
				sprintf(wantedLevel, "%i/5", PLAYER::GET_PLAYER_WANTED_LEVEL(player));
			}
			if (PLAYER::ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(playerPed))
			{
				sprintf(wantedLevel, "%i/5 (Flashing/About To Drop)", PLAYER::GET_PLAYER_WANTED_LEVEL(player));
			}
			float placey = 0.057f;
			Text("Vehicle", { m_white }, { LTextX, TextY + placey }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText((PED::GET_VEHICLE_PED_IS_IN(ped, false) == 0) ? "N/A" : HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(playerPed, false)))), RTextX2, TextY + placey, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			float placey2 = 0.077f;
			Text("State", { m_white }, { LTextX, TextY + placey2 }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(playerstate2, RTextX2, TextY + placey2, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			Text("Wanted Level", { m_white }, { LTextX, TextY + placey2 + 0.020f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(wantedLevel, RTextX2, TextY + placey2 + 0.020f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			Text("ID", { m_white }, { LTextX, TextY + placey2 + 0.040f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(std::to_string(player).c_str(), RTextX2, TextY + placey2 + 0.040f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			Text("Parachute State", { m_white }, { LTextX, TextY + 0.135f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(parachutestate2, LeftOffset, TextY + 0.135f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			g_Render->DrawRect(SeperatorX - 0.05, TextY + 0.145f, 0.001f, 0.015f, m_white);
			Text("Ammo", { m_white }, { SeperatorX - 0.048f, TextY + 0.135f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(ammo.c_str(), RTextX2, TextY + 0.135f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			Text("Stand User", { m_white }, { LTextX, TextY + 0.16f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(is_player_stand_user(player) ? "Yes" : "No", RTextX2, TextY + 0.16f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			Text("Zone", { m_white }, { LTextX, TextY + 0.185f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(Zone.c_str(), RTextX2, TextY + 0.185, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			Text("Street", { m_white }, { LTextX, TextY + 0.21f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(Street.c_str(), RTextX2, TextY + 0.21, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			Text("Coords", { m_white }, { LTextX, TextY + 0.235f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(coords.c_str(), SeperatorX - 0.0523f, TextY + 0.235f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
			g_Render->DrawRect(SeperatorX - 0.05, TextY + 0.245f, 0.001f, 0.015f, m_white);
			Text("Heading", { m_white }, { SeperatorX - 0.048f, TextY + 0.235f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(heading.c_str(), RTextX2, TextY + 0.235f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

			Text("Distance", { m_white }, { LTextX, TextY + 0.26f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(Distance.c_str(), SeperatorX - 0.0523f, TextY + 0.26f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
			g_Render->DrawRect(SeperatorX - 0.05, TextY + 0.27f, 0.001f, 0.015f, m_white);
			Text("Speed", { m_white }, { SeperatorX - 0.048f, TextY + 0.26f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(Speed.c_str(), RTextX2, TextY + 0.26f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);


			Text("Passive", { m_white }, { LTextX, TextY + 0.44f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(passive.c_str(), SeperatorX - 0.0523f, TextY + 0.44f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
			g_Render->DrawRect(SeperatorX - 0.05, TextY + 0.45f, 0.001f, 0.015f, m_white);
			Text("Rockstar", { m_white }, { SeperatorX - 0.048f, TextY + 0.44f }, { 0.23f, 0.23f }, false);
			g_Render->DrawRightText(rockstar.c_str(), RTextX2, TextY + 0.44f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);



			//draw_info_text("Clan Name", g_GameVariables->m_net_game_player(player)->m_clan_data.m_clan_name, 2, 0);

			//CNetGamePlayer* g_player = g_GameVariables->m_net_game_player(player);
			rage::joaat_t scene_hash = 0x390DCCF5;//0xAD197067, 0x390DCCF5, 0x3D8F5C29, 0x5ADFAFD0
			rage::joaat_t element = 0;
			CPed* local_ped = NETWORK::NETWORK_IS_SESSION_STARTED() ? all_players.get_ped(player) : (*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_ped;
			uintptr_t ui_3d_draw_manager = *(uint64_t*)(g_GameVariables->ui_3d_draw_manager);

			Vector3 pos = { x - pedx, y * 0.8f, pedyy };

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




		}
	};
	inline PlayersData g_players;
}
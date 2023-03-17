#pragma once
#include "Render.h"
namespace Saint {
	
	class Crash {
	public:
		bool vehicle = true;
		bool loading_screen = true;
	};
	class GameEvents {
	public:
		bool remove_sticky_bomb = false;
		bool request_map_pickup = true;
		bool give_pickup_rewards = true;
		bool ragdoll_request = true;
		bool remove_weapon = true;
		bool remove_all_weapons = true;
		bool particle_spam = true;
		bool freeze = true;
		bool give_weapons = true;
		bool fire_event = true;
		bool explosion = true;
		bool alter_wanted_level = true;
		bool play_sound = true;
		bool request_control = true;
		bool request_pickup = true;
		bool clear_area = true;
		bool weapon_damage = false;
		bool vehicle_component_control = false;
		bool chnage_radio_station = false;
		bool car_horn = true;
		bool vote_kick = true;
		bool blow_up_vehicle = true;
		
	};
	class ScriptEvents {
	public:
		bool bounty = false;
		bool globals = true;
		bool vehicle_kick = true;
		bool text_messages = true;
		bool notifications = true;
		bool destroy_personal_vehicle = true;
		bool ceo_events = true;
		bool rotate_cam = true;
		bool transaction_error = true;
		bool tutorial = true;
	};
	class Entites {
	public:
		bool cage = false;
		bool invalid_pickups = true;
		void init() {
			
		}
	};
	class eventHandler {
	public:
		eventHandler(int64_t m_hash, std::string m_name, bool* m_toggle) {
			hash = m_hash;
			name = m_name;
			toggled = m_toggle;
		}
	public:
		std::string name;
		int64_t hash;
		bool* toggled;
	};
	class Reactions {
	public:
		const char* type[3] = { "None", "Cage", "Kick"};
		int type_2 = 0;
	};
	class Protections {
	public:
		Reactions reaction;
		Crash Crashes;
		GameEvents GameEvents;
		ScriptEvents ScriptEvents;
		Entites Entities;
		
		bool crash_blocked = false;
		void push_notification(const char* body) {


			Noti::InsertNotification({ ImGuiToastType_None, 4000, body });
		}
		void push_notification2(const char* body) {

			if (!crash_blocked) {
				Noti::InsertNotification({ ImGuiToastType_None, 4000, body });
				crash_blocked = true;
			}
		}
		bool send_to_location = false;
		bool mc_teleport = true;
		bool sound_spam = false;
		bool block_reports = false;
		//teleports
		bool teleport = true;
		bool Interior = true;
		bool cayo_perico = true;
		bool warehouse = true;
		bool sms_with_attachment = true;
		bool mission = true;
		//ceo
		bool ceo_kick = true;
		bool ceo_ban = true;
		bool ceo_money = true;
		bool ceo_raid = true;
		//kick
		bool kick = true;
		//Activity
		bool activity = true;
		
	};
	inline Protections protections;
	inline std::vector<eventHandler> m_scriptEvents = {
			{ -1603050746, "Vehicle Kick", &protections.ScriptEvents.vehicle_kick },
			{ 448051697, "Rotate Camera", &protections.ScriptEvents.rotate_cam },
			{ -1428749433, "Rotate Camera", &protections.ScriptEvents.rotate_cam },
			//Teleport
			{ 330622597, "Send To Location", &protections.send_to_location },
			{ 891653640, "MC Teleport", &protections.mc_teleport },
			{ -702866045, "Teleport", &protections.teleport },
			{ 1727896103, "Send To Interior", &protections.Interior },
			{ -369672308, "Send To Cayo Perico", &protections.cayo_perico },
			{ -1796714618, "Send To Warehouse", &protections.warehouse },
			{ -2138393348, "Send To Mission", &protections.mission },
			//Text
			{ 1075676399, "Text Message (Attachment)", &protections.sms_with_attachment },
			{ 53975141, "Text Message", &protections.ScriptEvents.text_messages },
			//Crash
			{ -992162568, "Crash", &protections.Crashes.loading_screen },
			{ 1131623211, "Crash", &protections.Crashes.loading_screen },
			{ 1556360603, "Crash", &protections.Crashes.loading_screen },
			//Globals
			{ 1141648445, "Off Radar", &protections.ScriptEvents.globals },
			//Other
			{ 54323524, "Transaction Error", &protections.ScriptEvents.transaction_error },
			//Kyro
			{ -95341040, "Start Script", &protections.ScriptEvents.tutorial },
			{ 1742713914, "Start Script", &protections.ScriptEvents.tutorial },
			//CEO
			{ 1421455565, "Ceo Kick", &protections.ceo_kick },
			{ 1517094008, "Ceo Ban", &protections.ceo_ban },
			{ 75579707, "Ceo Money", &protections.ceo_money },
			{-1388385133, "CEO Raid", &protections.ceo_raid},
			//Kicks
			{ 1017995959, "Kick", &protections.kick},
			//Msc
			{ 1104117595, "Activity", &protections.activity},
	};
}
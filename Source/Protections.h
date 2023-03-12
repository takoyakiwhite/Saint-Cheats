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
		eventHandler(int64_t hash, std::string name, bool* toggle) {
			eventHash = hash;
			eventName = name;
			eventBlockToggle = toggle;
		}
	public:
		std::string eventName;
		int64_t eventHash;
		bool* eventBlockToggle;
	};
	class Protections {
	public:
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
		bool sound_spam = false;
		bool block_reports = false;
		
	};
	inline Protections protections;
	inline std::vector<eventHandler> m_scriptEvents = {
			{ -1603050746, "Vehicle Kick", &protections.ScriptEvents.vehicle_kick },
	};
}
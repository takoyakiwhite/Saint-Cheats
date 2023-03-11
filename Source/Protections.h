#pragma once
#include "Render.h"
namespace Saint {
	
	class Crash {
	public:
		bool vehicle = true;
	};
	class GameEvents {
	public:
		bool request_control = true;
		bool request_pickup = true;
		bool give_weapons = true;
		bool clear_ped_tasks = true;
		bool remove_weapons = true;
		bool play_sound = true;
		bool remove_sound = true;
		bool explosion = true;
		bool fire = true;
		bool give_pickup_rewards = false;
		bool votekick = true;
		
	};
	class Entites {
	public:
		bool cage = false;
		bool invalid_pickups = true;
		void init() {
			
		}
	};
	class Protections {
	public:
		Crash crash;
		GameEvents m_game_events;
		Entites m_entities;
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
}
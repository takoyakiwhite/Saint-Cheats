#pragma once
#include "Render.h"
namespace Saint {
	class Crash {
	public:
		bool vehicle = true;
	};
	class Protections {
	public:
		Crash crash;
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
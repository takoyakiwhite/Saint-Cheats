#pragma once
#include "Render.h"
namespace Saint {
	
	class Protections {
	public:
		void push_notification(const char* body) {

			
			Noti::InsertNotification({ ImGuiToastType_None, 4000, body });




		}
		bool send_to_location = false;
		bool sound_spam = false;
		bool block_reports = false;
	};
	inline Protections protections;
}
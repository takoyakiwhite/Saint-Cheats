#pragma once
#include "Render.h"

namespace Saint {
	class Notifcations {
	public:
		void add(const char* text) {
			Noti::InsertNotification({ ImGuiToastType_None, 2000, text });
		}
	};
	inline Notifcations* g_Notifcations;
}

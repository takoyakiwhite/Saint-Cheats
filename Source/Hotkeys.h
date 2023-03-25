#pragma once
#include "Features.h"
namespace Saint {
	class hotkeyHandler {
	public:
		hotkeyHandler(std::string m_name, int m_key, bool* m_toggle) {
			name = m_name;
			key = m_key;
			toggle = m_toggle;
		}
	public:
		std::string name;
		int key;
		bool* toggle;
	};
	inline std::vector<hotkeyHandler> m_Hotkeys = {
		{"No-Clip", 0x45, &no_clip.enabled}
	};
	inline void hotkey_tick() {
		for (auto& hotkey : m_Hotkeys) {
			if (GetAsyncKeyState(hotkey.key) & 1) {
				*hotkey.toggle = !*hotkey.toggle;
				Noti::InsertNotification({ ImGuiToastType_None, 2000, "'%s' hotkey was used.", hotkey.name });
				
			}
		}
	}
}

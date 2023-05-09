#pragma once
#include "Features.h"
namespace Saint {
	class hotkeyHandler {
	public:
		hotkeyHandler(std::string m_name, int m_key, bool* m_toggle, std::string m_key_name) {
			name = m_name;
			key = m_key;
			toggle = m_toggle;
			key_name = m_key_name;
		}
	public:
		std::string name;
		int key;
		bool* toggle;
		std::string key_name;
	};
	inline std::vector<hotkeyHandler> m_Hotkeys = {
		
	};
	inline void hotkey_tick() {
		for (auto& hotkey : m_Hotkeys) {
			if (Game->KeyPress(hotkey.key) & 1) {
				*hotkey.toggle = !*hotkey.toggle;
				Noti::InsertNotification({ ImGuiToastType_None, 2000, "'%s' hotkey was used.", hotkey.name });
				
			}
		}
	}
}

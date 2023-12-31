#pragma once
#include "optionGetters.hpp"
#include "Framework.hpp"
#include "../Hotkeys.h"
namespace Saint::UserInterface
{
	enum class BoolDisplay
	{
		OnOff,
		YesNo
	};

	class toggle : public OptionGetters<toggle>
	{
	public:
		explicit toggle(const char* text, const char* description, bool* b00l, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l)
		{
			Base::SetLeftText(text);
			if (description == "NO DESCRIPTION") {
				Base::SetDescription("");
			}
			if (description != "" || description != nullptr && description != "NO DESCRIPTION") {
				Base::SetDescription(description);
			}
			if (description == "" || description == nullptr) {
				Base::SetDescription("Hold V and any key to set a hotkey.");
			}
			Base::SetAction(std::move(action));
			Base::SetBool(b00l);
		}
		explicit toggle(const char* text, bool* b00l, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l)
		{
			Base::SetLeftText(text);
			Base::SetDescription("Hold V and any key to set a hotkey.");
			Base::SetAction(std::move(action));
		}

		~toggle() noexcept = default;
		toggle(toggle const&) = default;
		toggle& operator=(toggle const&) = default;
		toggle(toggle&&) = default;
		toggle& operator=(toggle&&) = default;


		
		const char* GetRightText() override
		{
			
			
			return Base::GetRightText();
		}

		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "none" && secondary == "bool") {
				g_Render->ToggledOn = *m_Bool;
				return true;
			}
			return Base::GetFlag(flag, secondary);
		}
		const char* get_name(int vk) {
			TCHAR keyName[32];
			GetKeyNameText(vk << 16, keyName, 32);
			return keyName;
		}
		void HandleAction(OptionAction action) override
		{
			for (int i = 0; i < 256; i++) {
				if (action == OptionAction::Hotkey) {
					if (g_Render->m_Opened) {
						if (Game->KeyPress(0xA0, true)) {
							for (auto& keys : m_Hotkeys) {
								//Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s, key: %s", keys.name, get_name(keys.key) });
							}
						}
						if (Game->KeyPress(i, true)) {
							PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
							UINT vk = MapVirtualKey(i, MAPVK_VSC_TO_VK);
							if (vk == 56) {
								Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %i hotkeys cleared.", m_Hotkeys.size() });
								m_Hotkeys.clear();
							}
							if (vk != 86 && vk != 0 && vk != 87 && vk != 68 && vk != 122 && vk != 56 && vk != 121 && vk != 118 && vk != 46) {
								TCHAR keyName[32];
								GetKeyNameText(vk << 16, keyName, 32);
								g_Render->controlsEnabled = false;
								if (vk == 35) {
									m_Hotkeys.push_back({ m_Text, 0x4F, (bool*)m_Bool, "o", Base::m_Action});
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'o'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 33) {
									m_Hotkeys.push_back({ m_Text, 0x49, (bool*)m_Bool, "i", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'i'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 12) {
									m_Hotkeys.push_back({ m_Text, 0x59, (bool*)m_Bool, "y", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'y'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 144) {
									m_Hotkeys.push_back({ m_Text, 0x45, (bool*)m_Bool, "e", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'e'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 145) {
									m_Hotkeys.push_back({ m_Text, 0x46, (bool*)m_Bool, "f", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'f'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 119) {
									m_Hotkeys.push_back({ m_Text, 0x42, (bool*)m_Bool, "b", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'b'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 107) {
									m_Hotkeys.push_back({ m_Text, 0x4E, (bool*)m_Bool, "n", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'n'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 39) {
									m_Hotkeys.push_back({ m_Text, 0x4D, (bool*)m_Bool, "m", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'm'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 109) {
									m_Hotkeys.push_back({ m_Text, 0x4A, (bool*)m_Bool, "j", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'j'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 38) {
									m_Hotkeys.push_back({ m_Text, 0x48, (bool*)m_Bool, "h", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'h'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 36) {
									m_Hotkeys.push_back({ m_Text, 0x47, (bool*)m_Bool, "g", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'g'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else if (vk == 37) {
									m_Hotkeys.push_back({ m_Text, 0x4B, (bool*)m_Bool, "k", Base::m_Action });
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to 'k'", m_Text, keyName, vk });
									g_Render->controlsEnabled = true;
								}
								else {
									//Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %i was pressed", vk });
									g_Render->controlsEnabled = true;
								}

							}

						}
					}

				}
				
			}
			if (action == OptionAction::Enter)
			{
				*m_Bool = !*m_Bool;
			}

			Base::HandleAction(action);
		}
	private:
		bool* m_Bool;
		const char* m_Text;

		using Base = OptionGetters<toggle>;
	};
}

#pragma once
#include "UI/OptionGetters.hpp"
#include "UI/Framework.hpp"

namespace Saint::UserInterface {
	class ToggleWithScroller : public OptionGetters<ToggleWithScroller>
	{
	public:
		explicit ToggleWithScroller() = default;

		template <std::size_t N>
		explicit ToggleWithScroller(const char* text, const char* description, bool* b00l, const char*(*array)[N], std::size_t* position, bool actionOnHorizontal = false, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l),
			m_Data(&(*array)[0]),
			m_DataSize(N),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal)
		{
			Base::SetLeftText(text);
			if (description != "" || description != nullptr)
				Base::SetDescription(description);
			if (description == "" || description == nullptr) {
				Base::SetDescription("Hold V and any key to set a hotkey.");
			}
			Base::SetAction(std::move(action));
		}

		template <typename VectorType>
		explicit ToggleWithScroller(const char* text, const char* description, bool* b00l, const VectorType* v, std::size_t* position, bool actionOnHorizontal = true, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l),
			m_Data(v->data()),
			m_DataSize(v->size()),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal)
		{
			Base::SetLeftText(text);
			if (description != "" || description != nullptr)
				Base::SetDescription(description);
			if (description == "" || description == nullptr) {
				Base::SetDescription("Hold V and any key to set a hotkey.");
			}
			Base::SetAction(std::move(action));
		}

		enum class BoolDisplay
		{
			OnOff,
			YesNo
		};
		template <typename BoolType = bool>
		explicit ToggleWithScroller(const char* text, const char* description, bool* b00l, std::size_t* position, BoolDisplay displayType, bool displayInverted = true, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l),
			m_DisplayInverted(displayInverted),
			m_DisplayType(displayType)
		{
			Base::SetLeftText(text);
			if (description != "" || description != nullptr)
				Base::SetDescription(description);
			if (description == "" || description == nullptr) {
				Base::SetDescription("Hold V and any key to set a hotkey.");
			}
			Base::SetAction(std::move(action));
		}

		const char* GetRightText() override
		{
			MemoryStringStream stream(Base::m_RightText);

			if (m_Data)
			{
				if (g_Render->show_positions) {
					stream << m_Data[*m_Position];
					stream << " ~c~[" << *m_Position + 1 << "/" << m_DataSize << "]";
				}
				else {
					stream << m_Data[*m_Position];
					stream << " ";
				}

			}
			else
			{
				stream << "N/A";
			}

			return OptionGetters::GetRightText();
		}

		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "choose" && secondary == "bool") {
				g_Render->ToggledOn = *m_Bool;
				return true;
			}
			return Base::GetFlag(flag, secondary);
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
									m_Hotkeys.push_back({ m_Text, 0x4F, (bool*)m_Bool, "o", Base::m_Action });
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
			if (action == OptionAction::Left)
			{
				if (m_Data)
				{
					if (*m_Position > 0)
						--(*m_Position);
					else
						*m_Position = static_cast<std::size_t>(m_DataSize - 1);

					if (m_ActionOnHorizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}
			else if (action == OptionAction::Right)
			{
				if (m_Data)
				{
					if (*m_Position < m_DataSize - 1)
						++(*m_Position);
					else
						*m_Position = 0;

					if (m_ActionOnHorizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}

			if (m_Data)
				Base::HandleAction(action);
		}

		~ToggleWithScroller() noexcept = default;
		ToggleWithScroller(ToggleWithScroller const&) = default;
		ToggleWithScroller& operator=(ToggleWithScroller const&) = default;
		ToggleWithScroller(ToggleWithScroller&&) = default;
		ToggleWithScroller& operator=(ToggleWithScroller&&) = default;
	private:
		const char* m_Text;
		const const char** m_Data{};
		std::size_t m_DataSize{};
		std::size_t* m_Position{};
		bool m_ActionOnHorizontal{};

		bool* m_Bool;
		BoolDisplay m_DisplayType;
		bool m_DisplayInverted = false;

		using Base = OptionGetters<ToggleWithScroller>;
	};
}
#pragma once
#include "UI/BaseOption.hpp"
#include "UI/Interface.hpp"
#include "FiberHelper.hpp"
namespace Saint::UserInterface
{
	class color_submenu : public BaseOption<color_submenu>
	{
	public:
		explicit color_submenu() = default;
		explicit color_submenu(const char* text, const char* description, Color color, std::uint32_t subId, std::function<void()> action = [] {}) :
			m_SubId(subId)
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
			SetColor(color);
		}

		~color_submenu() noexcept = default;
		color_submenu(color_submenu const&) = default;
		color_submenu& operator=(color_submenu const&) = default;
		color_submenu(color_submenu&&) = default;
		color_submenu& operator=(color_submenu&&) = default;

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::EnterPress)
			{
				g_Render->SwitchToSubmenu(m_SubId);
			}

			BaseOption::HandleAction(action);
		}

		

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::ColorSub)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}
	private:
		std::uint32_t m_SubId{};
	};
}

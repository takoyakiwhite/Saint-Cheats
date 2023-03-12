#pragma once
#include "Ui/BaseOption.hpp"
#include "Ui/Interface.hpp"
#include "FiberHelper.hpp"
namespace Saint::UserInterface
{
	class playersubmenu : public BaseOption<playersubmenu>
	{
	public:
		explicit playersubmenu() = default;
		explicit playersubmenu(const char* text, const char* description, std::uint32_t subId, std::function<void()> action = [] {}) :
			m_SubId(subId)
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		~playersubmenu() noexcept = default;
		playersubmenu(playersubmenu const&) = default;
		playersubmenu& operator=(playersubmenu const&) = default;
		playersubmenu(playersubmenu&&) = default;
		playersubmenu& operator=(playersubmenu&&) = default;

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
			if (flag == OptionFlag::PlayerSub)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}
	private:
		std::uint32_t m_SubId{};
	};
}

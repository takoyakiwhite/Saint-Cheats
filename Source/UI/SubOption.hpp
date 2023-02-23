#pragma once
#include "BaseOption.hpp"
#include "Interface.hpp"
#include "../FiberHelper.hpp"
namespace Arctic::UserInterface
{
	class SubOption : public BaseOption<SubOption>
	{
	public:
		explicit SubOption() = default;
		explicit SubOption(const char* text, const char* description, std::uint32_t subId, std::function<void()> action = [] {}) :
			m_SubId(subId)
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		~SubOption() noexcept = default;
		SubOption(SubOption const&) = default;
		SubOption& operator=(SubOption const&) = default;
		SubOption(SubOption&&) = default;
		SubOption& operator=(SubOption&&) = default;

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::EnterPress)
			{
				if (g_Render->m_AnimationCheck)
				{
					g_FiberPool.queue([]
						{
							g_Render->m_AnimationCheck = false;
					g_Render->m_OptionUnselectedTextColor.a = 0;
					g_Render->m_OptionSelectedTextColor.a = 0;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					fbr::cur()->wait(1ms);
					g_Render->m_OptionUnselectedTextColor.a = g_Render->m_OptionUnselectedTextColor.a + 5;
					g_Render->m_OptionSelectedTextColor.a = g_Render->m_OptionSelectedTextColor.a + 5;
					g_Render->m_AnimationCheck = true;
						});
				}
				g_Render->SwitchToSubmenu(m_SubId);
			}

			BaseOption::HandleAction(action);
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Enterable)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}
	private:
		std::uint32_t m_SubId{};
	};
}

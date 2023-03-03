#pragma once
#include "BaseOption.hpp"
#include "Interface.hpp"

namespace Arctic::UserInterface
{
	enum class BoolDisplay
	{
		OnOff,
		YesNo
	};

	template <typename BoolType = bool>
	class toggle : public BaseOption<toggle<BoolType>>
	{
	public:
		explicit toggle(const char* text, const char* description, BoolType* b00l, BoolDisplay displayType, bool displayInverted = false, std::function<void()> action = [] {}) :
			m_Bool(b00l),
			m_DisplayInverted(displayInverted),
			m_DisplayType(displayType)
		{
			Base::SetLeftText(text);
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}

		~toggle() noexcept = default;
		toggle(toggle const&) = default;
		toggle& operator=(toggle const&) = default;
		toggle(toggle&&) = default;
		toggle& operator=(toggle&&) = default;

		
		const char* GetRightText() override
		{
			switch (m_DisplayType)
			{
			case BoolDisplay::OnOff:
				//Base::SetRightText((*m_Bool ^ m_DisplayInverted) ? "~g~ON" : "~r~OFF");
				break;
			case BoolDisplay::YesNo:
				Base::SetRightText((*m_Bool ^ m_DisplayInverted) ? "~g~YES" : "~r~NO");
				break;
			}
			
			return Base::GetRightText();
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::BoolOption)
			{
				g_Render->ToggledOn = *m_Bool ^ m_DisplayInverted;
				return true;
			}

			return Base::GetFlag(flag);
		}

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::EnterPress)
			{
				*m_Bool = !*m_Bool;
			}

			Base::HandleAction(action);
		}
	private:
		BoolType* m_Bool;
		BoolDisplay m_DisplayType;
		BoolType m_DisplayInverted = false;

		using Base = BaseOption<toggle<BoolType>>;
	};
}

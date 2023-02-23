#pragma once
#include "BaseOption.hpp"
#include "Interface.hpp"

namespace Arctic::UserInterface
{
	class UnclickOption : public BaseOption<UnclickOption>
	{
	public:
		explicit UnclickOption() = default;
		explicit UnclickOption(const char* text, const char* description = nullptr, std::function<void()> action = [] {})
		{
			std::string text2 = std::string(text);
			const char* textfinal = text2.c_str();
			SetCenteredText(textfinal);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::UnclickOption)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}

		~UnclickOption() noexcept = default;
		UnclickOption(UnclickOption const&) = default;
		UnclickOption& operator=(UnclickOption const&) = default;
		UnclickOption(UnclickOption&&) = default;
		UnclickOption& operator=(UnclickOption&&) = default;
	};
}

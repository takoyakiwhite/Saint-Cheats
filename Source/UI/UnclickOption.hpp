#pragma once
#include "BaseOption.hpp"
#include "Interface.hpp"

namespace Saint::UserInterface
{
	class Break : public BaseOption<Break>
	{
	public:
		explicit Break() = default;
		explicit Break(const char* text)
		{
			std::string text2 = std::string(text);
			const char* textfinal = text2.c_str();
			SetCenteredText(textfinal);
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::UnclickOption)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}

		~Break() noexcept = default;
		Break(Break const&) = default;
		Break& operator=(Break const&) = default;
		Break(Break&&) = default;
		Break& operator=(Break&&) = default;
	};
}

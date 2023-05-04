#pragma once
#include "UI/BaseOption.hpp"

namespace Saint::UserInterface
{
	class KeyboardOption : public BaseOption<KeyboardOption>
	{
	public:
		explicit KeyboardOption() = default;
		explicit KeyboardOption(const char* text, const char* description = nullptr, std::string right = "", std::function<void()> action = [] {})
		{
			SetLeftText(text);
			if (right == "") {
				SetRightText("None");
			}
			else {
				SetRightText(right.c_str());
			}
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Keyboard)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}

		~KeyboardOption() noexcept = default;
		KeyboardOption(KeyboardOption const&) = default;
		KeyboardOption& operator=(KeyboardOption const&) = default;
		KeyboardOption(KeyboardOption&&) = default;
		KeyboardOption& operator=(KeyboardOption&&) = default;
	};
	class KeyboardOption2 : public BaseOption<KeyboardOption2>
	{
	public:
		explicit KeyboardOption2() = default;
		explicit KeyboardOption2(const char* text, const char* description = nullptr, const char* right = "", std::function<void()> action = [] {})
		{
			SetLeftText(text);
			if (right == "") {
				SetRightText("None");
			}
			else {
				SetRightText(right);
			}
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Keyboard)
			{
				return true;
			}

			return BaseOption::GetFlag(flag);
		}

		~KeyboardOption2() noexcept = default;
		KeyboardOption2(KeyboardOption2 const&) = default;
		KeyboardOption2& operator=(KeyboardOption2 const&) = default;
		KeyboardOption2(KeyboardOption2&&) = default;
		KeyboardOption2& operator=(KeyboardOption2&&) = default;
	};
}

#pragma once
#include "UI/BaseOption.hpp"

namespace Arctic::UserInterface
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



		~KeyboardOption() noexcept = default;
		KeyboardOption(KeyboardOption const&) = default;
		KeyboardOption& operator=(KeyboardOption const&) = default;
		KeyboardOption(KeyboardOption&&) = default;
		KeyboardOption& operator=(KeyboardOption&&) = default;
	};
}

#pragma once
#include "optionGetters.hpp"

namespace Saint::UserInterface
{
	class Button : public OptionGetters<Button>
	{
	public:
		explicit Button() = default;
		explicit Button(const char* text, const char* description = nullptr, std::function<void()> action = [] {})
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		~Button() noexcept = default;
		Button(Button const&) = default;
		Button& operator=(Button const&) = default;
		Button(Button&&) = default;
		Button& operator=(Button&&) = default;
	};
}

#pragma once
#include "optionGetters.hpp"

namespace Saint::UserInterface
{
	class Scroll : public OptionGetters<Scroll>
	{
	public:
		explicit Scroll() = default;

		template <std::size_t N>
		explicit Scroll(const char* text, const char* description, const char*(*array)[N], std::size_t* position, bool actionOnHorizontal = false, std::uint32_t subId2 = -1, std::function<void()> action = [] {}):
			m_Data(&(*array)[0]),
			m_DataSize(N),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal),
			m_SubId2(subId2)
		{
			Base::SetLeftText(text);
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}

		template <typename VectorType>
		explicit Scroll(const char* text, const char* description, const VectorType* v, std::size_t* position, bool actionOnHorizontal = false, std::uint32_t subId2 = -1, std::function<void()> action = [] {}) :
			m_Data(v->data()),
			m_DataSize(v->size()),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal),
			m_SubId2(subId2)
		{
			Base::SetLeftText(text);
			if (description)
				Base::SetDescription(description);
			Base::SetAction(std::move(action));
		}
		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "choose" && secondary == "none") {
				return true;
			}
			return Base::GetFlag(flag, secondary);
		}
		const char* GetRightText() override
		{
			MemoryStringStream stream(OptionGetters::m_RightText);

			if (m_Data)
			{
				if (g_Render->show_positions) {
					stream << m_Data[*m_Position];
					stream << " ~c~[" << *m_Position + 1 << "/" << m_DataSize << "]";
				}
				else {
					stream << m_Data[*m_Position];
				}
				
			}
			else
			{
				stream << "N/A";
			}

			return Base::GetRightText();
		}

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::Enter) {
				if (m_SubId2 == -1) {

				}
				else {
					g_Render->SwitchToSubmenu(m_SubId2);
				}
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

		~Scroll() noexcept = default;
		Scroll(Scroll const&) = default;
		Scroll& operator=(Scroll const&) = default;
		Scroll(Scroll&&) = default;
		Scroll& operator=(Scroll&&) = default;
	private:
		const const char** m_Data{};
		std::size_t m_DataSize{};
		std::size_t* m_Position{};
		bool m_ActionOnHorizontal{};
		std::uint32_t m_SubId2{};

		using Base = OptionGetters<Scroll>;
	};
}

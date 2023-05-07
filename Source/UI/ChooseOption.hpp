#pragma once
#include "BaseOption.hpp"

namespace Saint::UserInterface
{
	template <typename DataType, typename PositionType>
	class Scroll : public BaseOption<Scroll<DataType, PositionType>>
	{
	public:
		explicit Scroll() = default;

		template <PositionType N>
		explicit Scroll(const char* text, const char* description, DataType(*array)[N], PositionType* position, bool actionOnHorizontal = false, std::uint32_t subId2 = -1, std::function<void()> action = [] {}):
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
		explicit Scroll(const char* text, const char* description, const VectorType* v, PositionType* position, bool actionOnHorizontal = false, std::uint32_t subId2 = -1, std::function<void()> action = [] {}) :
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
		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::Choose)
			{
				return true;
			}

			return Base::GetFlag(flag);
		}
		const char* GetRightText() override
		{
			MemoryStringStream stream(Base::m_RightText);

			if (m_Data)
			{
				stream << m_Data[*m_Position];
				stream << " ~c~[" << *m_Position + 1 << "/" << m_DataSize << "]";
			}
			else
			{
				stream << "Unknown ~c~[0 / 0]";
			}

			return Base::GetRightText();
		}

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::EnterPress) {
				if (m_SubId2 == -1) {

				}
				else {
					g_Render->SwitchToSubmenu(m_SubId2);
				}
			}
			if (action == OptionAction::LeftPress)
			{
				if (m_Data)
				{
					if (*m_Position > 0)
						--(*m_Position);
					else
						*m_Position = static_cast<PositionType>(m_DataSize - 1);

					if (m_ActionOnHorizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}
			else if (action == OptionAction::RightPress)
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
		const DataType* m_Data{};
		PositionType m_DataSize{};
		PositionType* m_Position{};
		bool m_ActionOnHorizontal{};
		std::uint32_t m_SubId2{};

		using Base = BaseOption<Scroll<DataType, PositionType>>;
	};
}

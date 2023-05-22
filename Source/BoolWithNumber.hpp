#pragma once
#include "UI/OptionGetters.hpp"
#include "UI/Framework.hpp"

namespace Saint::UserInterface {
    template <typename NumberType>
    class ToggleWithNumber : public OptionGetters<ToggleWithNumber<NumberType>>
    {
    public:
        explicit ToggleWithNumber() = default;
        explicit ToggleWithNumber(const char* text, const char* description, bool* b00l, NumberType* number, NumberType min, NumberType max, NumberType step = 1, std::size_t precision = 3, bool actionOnHorizontal = true, const char* prefix = "", const char* suffix = "", std::function<void()> action = [] {}) :
            m_ActionOnHorizontal(actionOnHorizontal),
            m_Bool(b00l),
            m_Number(number),
            m_Min(min),
            m_Max(max),
            m_Step(step),
            m_Precision(precision)
        {
            Base::SetLeftText(text);
            if (description)
                Base::SetDescription(description);
            Base::SetAction(std::move(action));
            Base::HandleAction(*m_Bool ? OptionAction::Enter : OptionAction::Enter);
            std::strncpy(&m_Prefix[0], prefix, sizeof(m_Prefix) - 1);
            std::strncpy(&m_Suffix[0], suffix, sizeof(m_Suffix) - 1);
        }

        ~ToggleWithNumber() noexcept = default;
        ToggleWithNumber(ToggleWithNumber const&) = default;
        ToggleWithNumber& operator=(ToggleWithNumber const&) = default;
        ToggleWithNumber(ToggleWithNumber&&) = default;
        ToggleWithNumber& operator=(ToggleWithNumber&&) = default;

        bool GetFlag(const char* flag, const char* secondary) override
        {
            if (flag == "number" && secondary == "bool") {
                g_Render->ToggledOn = *m_Bool;
                return true;
            }
            return Base::GetFlag(flag, secondary);
        }
        const char* GetRightText() override
        {
            
            if (g_Render->show_max) {
                MemoryStringStream stream(Base::m_RightText);
                stream
                    << std::setprecision(m_Precision)
                    << std::fixed
                    << m_Prefix
                    << static_cast<DisplayType>(*m_Number)
                    << "/"
                    << static_cast<DisplayType>(m_Max)
                    << m_Suffix;
            }
            else {
                MemoryStringStream stream(Base::m_RightText);
                stream
                    << std::setprecision(m_Precision)
                    << std::fixed
                    << m_Prefix
                    << static_cast<DisplayType>(*m_Number)
                    << m_Suffix;
            }
            return Base::GetRightText();
        }

        void HandleAction(OptionAction action) override
        {
            if (action == OptionAction::Enter)
            {
                *m_Bool = !*m_Bool;
            }
            if (action == OptionAction::Left)
            {
                if (*m_Number - m_Step < m_Min)
                    *m_Number = m_Max;
                else
                    *m_Number -= m_Step;

                if (m_ActionOnHorizontal && Base::m_Action)
                    std::invoke(Base::m_Action);
            }
            else if (action == OptionAction::Right)
            {
                if (*m_Number + m_Step > m_Max)
                    *m_Number = m_Min;
                else
                    *m_Number += m_Step;

                if (m_ActionOnHorizontal && Base::m_Action)
                    std::invoke(Base::m_Action);
                Base::HandleAction(action);
            }


        }
    private:
        char m_Prefix[32] = {};
        char m_Suffix[32] = {};
        bool m_ActionOnHorizontal{};
        bool* m_Bool;
        NumberType* m_Number{};
        NumberType m_Min{};
        NumberType m_Max{};
        NumberType m_Step{};
        std::size_t m_Precision{};


        using Base = OptionGetters<ToggleWithNumber<NumberType>>;
        using DisplayType = std::conditional_t<sizeof(NumberType) == 1, std::uint32_t, NumberType>;
    };
}
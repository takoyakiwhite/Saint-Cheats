#pragma once
#include "UI/SubmenuBase.hpp"
#include "UI/BoolOption.hpp"
namespace Saint {
	template <typename ...TArgs>
	void addToggle(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::toggle>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addBreak(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Break>(std::forward<TArgs>(args)...));
	}
	template <typename NumberType, typename ...TArgs>
	void addToggleWithNumber(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::ToggleWithNumber<NumberType>>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addToggleWithScroll(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::ToggleWithScroller>(std::forward<TArgs>(args)...));
	}
	template <typename NumberType, typename ...TArgs>
	void addNumber(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::number<NumberType>>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addScroll(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Scroll>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addSubmenu(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::submenu>(std::forward<TArgs>(args)...));
	}
}
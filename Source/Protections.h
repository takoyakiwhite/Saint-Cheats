#pragma once
namespace Arctic {
	
	class Protections {
	public:
		void push_notification(const char* body) {

			
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");

			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(body);
			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(FALSE, TRUE);




		}
		bool send_to_location = false;
		bool sound_spam = false;
		bool block_reports;
	};
	inline Protections protections;
}
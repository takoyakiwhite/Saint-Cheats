#include "Natives.hpp"
#include "UI/Interface.hpp"
namespace Saint::UserInterface
{
	enum TextPosition {
		Left = 0,
		Right = 1,
		Center = 2,
	};
	struct MenuTextures {
		const char* dictionary;
		const char* asset;
	};
	inline MenuTextures getTexture(const char* name) {
		if (name == "arrows") {
			return { "commonmenu", "shop_arrows_upanddown" };
		}
		else if (name == "mainToggles") {
			return { "commonmenu", "common_medal" };
		}
		else if (name == "pen") {
			return { "Textures", "pen" };
		}
	}
	inline MenuTextures getTexture(const char* name, const char* name2) {
		return { name, name2 };
	}
	inline bool isInBounds(float first, float second, float top, float bottom, float left, float right) {
		if (first > left && first < right && second > top && second < bottom) {
			return true;
		}
	}
	inline Vector2 getMousePos() {
		POINT point;
		GetCursorPos(&point);

		Vector2 GetMousePos = { static_cast<float>(point.x), static_cast<float>(point.y) };
		return { (1.f / ImGui::GetIO().DisplaySize.x) * GetMousePos.x, (1.f / ImGui::GetIO().DisplaySize.x) * GetMousePos.y };
	}
	
	class DrawingFunctions2 {
	public:
		void RadiusSphere(int pos, float radiusHandle, bool always_show, SubmenuBase* sub) {
			if (sub->GetSelectedOption() == pos || always_show) {
				GRAPHICS::DRAW_MARKER(28, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).z, 0, 0, 0, 0, 0, 0, radiusHandle, radiusHandle, radiusHandle, g_Render->m_RadiusSphere.r, g_Render->m_RadiusSphere.g, g_Render->m_RadiusSphere.b, g_Render->m_RadiusSphere.a, false, false, 0, false, NULL, NULL, false);
			}
		}
		void RadiusSphere(int pos, float radiusHandle, SubmenuBase* sub) {
			if (sub->GetSelectedOption() == pos) {
				GRAPHICS::DRAW_MARKER(28, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).z, 0, 0, 0, 0, 0, 0, radiusHandle, radiusHandle, radiusHandle, g_Render->m_RadiusSphere.r, g_Render->m_RadiusSphere.g, g_Render->m_RadiusSphere.b, g_Render->m_RadiusSphere.a, false, false, 0, false, NULL, NULL, false);
			}
		}
		void RadiusSphere(float radiusHandle, SubmenuBase* sub) {
			if (sub->GetSelectedOption() == sub->GetNumOptions()) {
				GRAPHICS::DRAW_MARKER(28, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0).z, 0, 0, 0, 0, 0, 0, radiusHandle, radiusHandle, radiusHandle, g_Render->m_RadiusSphere.r, g_Render->m_RadiusSphere.g, g_Render->m_RadiusSphere.b, g_Render->m_RadiusSphere.a, false, false, 0, false, NULL, NULL, false);
			}
		}
		void SetDrawOrder(int order) {
			GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(order);
		}
		float GetTextHeight(Font font, float size)
		{
			return HUD::GET_RENDERED_CHARACTER_HEIGHT(size, static_cast<int>(font));
		}

		Vector2 GetSpriteScale(float size)
		{
			int x;
			int y;
			GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&x, &y);
			return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
		}
		void Wrap(float x, float y) {
			HUD::SET_TEXT_WRAP(x, y);
		}
		void Rectangle(float x, float y, float width, float height, Color color)
		{
			GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
		}
		void Sprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
		{
			if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
			{
				GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0, -1);
			}
			else
			{
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
			}
		}
		void Sprite(MenuTextures texture, float x, float y, float width, float height, Color color, float rotation)
		{
			if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture.dictionary))
			{
				GRAPHICS::DRAW_SPRITE(texture.dictionary, texture.asset, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0, -1);
			}
			else
			{
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(texture.dictionary, false);
			}
		}
		void Arrows(bool selected, float offset)
		{
			if (selected) {
				if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(getTexture("arrows").dictionary))
				{
					Sprite(getTexture("arrows"), g_Render->m_PosX + (g_Render->m_Width / g_Render->m_OptionPadding) - offset, g_Render->m_DrawBaseY + (g_Render->m_OptionHeight / 2.f), GetSpriteScale(0.033).x, GetSpriteScale(0.030).y, selected ? g_Render->m_OptionSelectedTextColor : g_Render->m_OptionUnselectedTextColor, 90.0);
				}
				else
				{
					Sprite(getTexture("arrows"), g_Render->m_PosX + (g_Render->m_Width / g_Render->m_OptionPadding) - offset, g_Render->m_DrawBaseY + (g_Render->m_OptionHeight / 2.f), GetSpriteScale(0.033).x, GetSpriteScale(0.030).y, selected ? g_Render->m_OptionSelectedTextColor : g_Render->m_OptionUnselectedTextColor, 90.0);
				}
			}
		}
		void Text(TextPosition position, const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow, bool wrap = false)
		{
			switch (position) {
			case TextPosition::Left:
			{
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap) {

				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
				break;
			}
			case TextPosition::Right:
			{


				HUD::SET_TEXT_WRAP(0.f, x);
				HUD::SET_TEXT_RIGHT_JUSTIFY(true);
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap) {

				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
				break;
			}
			case TextPosition::Center:
			{
				HUD::SET_TEXT_CENTRE(true);
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap) {

				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
				break;
			}

			}

		}
		void Text(std::string text, std::float_t x, std::float_t y, Font font, std::float_t scale, RGBA color, bool centered, bool right_justified, bool outlined)
		{
			HUD::SET_TEXT_FONT(static_cast<int>(font));
			HUD::SET_TEXT_SCALE(0.f, scale);
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
			if (right_justified)
				HUD::SET_TEXT_WRAP(0.f, x);
			else HUD::SET_TEXT_WRAP(0.f, 1.f);
			HUD::SET_TEXT_CENTRE(centered);
			if (outlined)
				HUD::SET_TEXT_OUTLINE();
			HUD::SET_TEXT_RIGHT_JUSTIFY(right_justified);
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(text.c_str());
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, NULL);
		}
	};

	inline DrawingFunctions2* DrawingFunctions22;
	inline DrawingFunctions2* DrawingFunctions() {
		return DrawingFunctions22;
	}

}


#pragma once
#include "../Common.hpp"
#include "../Types.hpp"
#include "TextBox.hpp"
#include "AbstractSubmenu.hpp"

namespace Arctic::UserInterface
{
	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};
	enum class Outfits : std::int32_t
	{
		Face = 0,
		Head = 1,
		Hair = 2,
		Torso = 3,
		Torso2 = 4,
		Legs = 5,
		Hands = 6,
		Feet = 7,
		Eyes = 8,
		Accessories = 9,
		Vests = 10,
		Decals = 11,
		HeadProps = 12,
	};
	enum class HeaderType : std::int32_t
	{
		Static = 0,
		Gradient = 1
	};

	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;

		bool IsInBounds(Vector2 point)
		{
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);
			
			if (point.x > right || point.x < left)
				return false;
			if (point.y > top || point.y < bottom)
				return false;

			return true;
		}
	};

	struct RGBA
	{
		std::int32_t r;
		std::int32_t g;
		std::int32_t b;
		std::int32_t a;
		RGBA(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a)
			: r(r), g(g), b(b), a(a) {}
	};

	class UIManager
	{
	public:
		explicit UIManager() = default;
		~UIManager() noexcept = default;
		UIManager(UIManager const&) = delete;
		UIManager(UIManager&&) = delete;
		UIManager& operator=(UIManager const&) = delete;
		UIManager& operator=(UIManager&&) = delete;
	
		template <typename SubmenuType, typename ...TArgs>
		void draw_submenu(TArgs&&... args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}

		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto&& sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}

		void OnTick();
	public:
		std::mutex m_Mutex;

		bool m_Opened = false;
		bool m_MouseLocked = false;
		float m_PosX = 0.8f;
		float m_PosY = 0.1f;
		float m_Width = 0.22f;
		std::size_t m_OptionsPerPage = 13;
		bool m_Sounds = true;
		bool welcomemessage = false;
		
		// Glare
		bool m_render_glare = { true };
		int m_glare_handle;
		float m_glare_direction;
		void draw_glare();

		// Input
		std::int32_t m_OpenDelay = 200;
		std::int32_t m_BackDelay = 300;
		std::int32_t m_EnterDelay = 300;
		std::int32_t m_VerticalDelay = 120;
		std::int32_t m_HorizontalDelay = 120;

		

		//ToolTip
		void RenderToolTip();
		RGBA m_ToolTipColor = RGBA{ 255, 255, 255, 255 };
		Font m_ToolTipFont = Font::ChaletLondon;
		float m_ToolTipTextSize = 0.4f;

		// Header
		float m_HeaderHeight = { 0.083f };
		bool m_HeaderText = true;
		bool m_HeaderNativeText = false;
		float m_HeaderTextSize = 1.f;
		Font m_HeaderFont = Font::HouseScript;
		Color m_HeaderBackgroundColor{ 138, 43, 226, 255 };
		Color m_HeaderTextColor{ 255, 255, 255, 255 };
		HeaderType m_HeaderType = HeaderType::Static;

		bool m_HeaderGradientTransparent = false;
		bool m_HeaderGradientFlip = false;
		float m_HeaderGradientStretch = 0.f;
		float m_HeaderGradientFiller = 0.f;
		Color m_HeaderGradientColorLeft{ 0, 0, 0, 255 };
		Color m_HeaderGradientColorRight{ 255, 255, 255, 255 };

		// Footer Text
		bool LeftFooterText = false;
		bool RightFooterText = true;
		float m_FooterTextSize = 0.27f;
		Font m_FooterTextFont = Font::ChaletLondon;
		float m_FooterTextPadding = 2.1f;
		Color m_FooterTextColor{ 255,255,255, 255 };

		// Smooth Scrolling
		float lerp(float a, float b, float t)
		{
			return a + t * (b - a);
		}

		float m_CurrentCoord = m_PosY;

		//Themes
		const char* ThemeList[8]
		{
			"Light Purple",
			"Red Salmon",
			"Sapphire Blue",
			"Soft Black",
			"Emerald Green",
			"Violet Purple",
			"Salmon Pink",
			"Stash Skid Menu"
		};
		std::size_t ThemeIterator = 1;

		const char* HeaderFont[6]
		{
			"Chalet London",
			"House Script",
			"Monospace",
			"Wingdings",
			"Chalet Comprime Cologne",
			"Pricedown"
		};
		std::size_t HeaderFontIterator = 3;
		Outfits outfits = Outfits::Face;
		

		// Options
		float m_OptionHeight = 0.0315f;
		float m_OptionTextSize = 0.29f;
		Font m_OptionFont = Font::ChaletLondon;
		Font m_SeperatorFont = Font::HouseScript;
		float m_OptionPadding = 2.1f;
		Color m_OptionSelectedTextColor{ 255,255,255, 255 };
		Color m_OptionUnselectedTextColor{ 255,255,255, 255 };
		Color m_OptionSelectedBackgroundColor{ 138, 43, 226, 255 };
		Color m_OptionUnselectedBackgroundColor{ 0, 0, 0, 160 };

		// Footer
		bool m_dynamic_footer = { false };
		int m_option_count;
		int m_current_option;
		int m_previous_option;

		float m_FooterHeight = 0.030f;
		float m_FooterSpriteSize = 0.025f;
		Color m_FooterBackgroundColor{ 138, 43, 226, 255 };
		Color m_FooterSpriteColor{ 255,255,255, 255 };

		//Enterable
		const char* IndicatorList[3]
		{
			"Arrows",
			"Lines",
			"None"
		};
		std::size_t IndicatorIterator = 1;

		// Bool Toogles
		bool ToggledOn = false;
		bool ToggledOff = false;
		float m_ToggleSize = { 0.028f };
		Color m_ToggleOnColor{ 130, 214, 157, 255 };
		Color m_ToggleOffColor{ 200, 55, 80, 255 };
		Color m_ToggleCheckColor{ 255,255,255, 255 };
		const char* ToggleList[3]
		{
			"Buttons",
			"Checkmarks",
			"None"
		};
		std::size_t ToggleIterator = 0;

		// Description
		float m_DescriptionHeightPadding = 0.01f;
		float m_DescriptionHeight = 0.033f;
		float m_DescriptionTextSize = 0.28f;
		Font m_DescriptionFont = Font::ChaletLondon;
		Color m_DescriptionBackgroundColor{ 0, 0, 0, 160 };
		Color m_DescriptionTextColor{ 255,255,255, 255 };
		float m_DescriptionSpriteSize = 0.025f;
		float m_DescriptionPadding = 2.1f;
		Color m_DescriptionSpriteColor{ 255,255,255, 255 };

		bool m_MenuOpeningAnimation = false;
		int g_MenuAlpha = 0;
		const char* m_CurrentSubMenuName = "Hello";
		bool m_AnimationCheck;
		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> m_SubmenuStack;
	private:
		bool m_OpenKeyPressed = false;
		bool m_OpenKeyPressed2 = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
		void CheckForInput();
		void HandleInput();
		void ResetInput();

		float m_DrawBaseY{};
		void DrawHeader();
		void drawstring(char* text, float X, float Y);
		void setupdraw(bool outline);
		
		void RenderText(std::string text, std::float_t x, std::float_t y, Font font, std::float_t scale, RGBA color, bool centered, bool right_justified, bool outlined);
		void DrawOption(AbstractOption* opt, bool selected);
		void DrawFooter();
		void DrawDescription();
		void DrawSprite1(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha);
		void DrawRect(float x, float y, float width, float height, Color color);
		void DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation);
		void DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		float GetTextHeight(Font font, float size);
		Vector2 GetSpriteScale(float size);

		bool IsMouseLocked();
		Rectangle GetMenuRect();
		Vector2 GetMousePos();

		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
		
	};
}

namespace Arctic
{
	inline std::unique_ptr<UserInterface::UIManager> g_Render;
}

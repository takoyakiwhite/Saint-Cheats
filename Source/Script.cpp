#include "Script.h"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "Translation.hpp"
#include "CustomText.hpp"
#include "UI/Interface.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/UnclickOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "FiberHelper.hpp"
#include "Features.h"
namespace Arctic
{
	enum Submenu : std::uint32_t
	{
		//HOME
		SubmenuHome,

		//SELF
		SubmenuSelf,
		SubmenuNoClip,
		//SESSION
		SubmenuNetwork,
		SubmenuPlayerList,
		SubmenuSelectedPlayer,

		//SETTINGS
		SubmenuSettings,
		SubmenuSettingsHeader,
		SubmenuSettingsHeaderStaticBackground,
		SubmenuSettingsHeaderGradientBackground,
		SubmenuSettingsHeaderText,
		SubmenuSettingsSubmenuBar,
		SubmenuSettingsOption,
		SubmenuSettingsFooter,
		SubmenuSettingsDescription,
		SubmenuSettingsInput,
		SubmenuThemes,
		SubmenuDemo,
		SubmenuTest
		
	};

	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}

	void MainScript::Initialize()
	{
		m_Initialized = true;
		using namespace UserInterface;
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "Loading GTA Online with " BIGBASE_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_QUITTING"), "Leaving with " BIGBASE_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_QUIT_MP"), "Exiting GTA Online with " BIGBASE_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_ENTER_MP"), "Play GTA Online with  " BIGBASE_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_EXIT_GAME"), "Quit GTA with" BIGBASE_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_GO"), "Online with " BIGBASE_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_MPREENTER"), "Joining a new session with " BIGBASE_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_FRIEND_FM"), "Closed Friend Session with " BIGBASE_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_GOTO_STORE"), "Purchase Shark Cards with " BIGBASE_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_EXIT"), "Quit to desktop with " BIGBASE_NAME "?");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_CRESES"), "Joining A Crew Only Session with " BIGBASE_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_PGOB"), "Cut to the chase and	 head straight into the world of GTA Online with " BIGBASE_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_PGOT"), "Online w/ " BIGBASE_NAME "!");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INVO_FM"), "Join A Invite Only Session with " BIGBASE_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("LOADING_SPLAYER_L"), "Loading Story Mode with " BIGBASE_NAME "...");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_NCREW_FM"), "Join A Crew Session with " BIGBASE_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_CREW_FM"), "Join A Closed Crew Session with " BIGBASE_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_SOLO_FM"), "Join A Solo Session with " BIGBASE_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("PM_FRESES"), "Join A Friends Only Session with " BIGBASE_NAME ".");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_MAINTIT"), BIGBASE_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("MP_CHAT_ALL"), BIGBASE_NAME);
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_TRANSP"), "Isn't " BIGBASE_NAME " the fucking best?");

		g_Render->AddSubmenu<RegularSubmenu>("Arctic", SubmenuHome, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Player", nullptr, SubmenuSelf);
			sub->AddOption<SubOption>("Network", nullptr, SubmenuNetwork);
			sub->AddOption<SubOption>("Protections", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Teleport", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Weapon", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Vehicle", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Spawner", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Miscellaneous", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
		});
		g_Render->AddSubmenu<RegularSubmenu>(("Self"), SubmenuSelf, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("No-Clip", nullptr, SubmenuNoClip);
				sub->AddOption<BoolOption<bool>>(("Godmode"), nullptr, &godmode, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Never Wanted"), nullptr, &neverWantedBool, BoolDisplay::OnOff);
			
			});
		g_Render->AddSubmenu<RegularSubmenu>(("No-Clip"), SubmenuNoClip, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &no_clip.enabled, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Set Rotation"), nullptr, &no_clip.enabled, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Include Vehicles"), nullptr, &no_clip.WorkForVehicles, BoolDisplay::OnOff);
				if (no_clip.WorkForVehicles) {
					sub->AddOption<BoolOption<bool>>(("Stop After No Input"), nullptr, &no_clip.StopAfterNoInput, BoolDisplay::OnOff);
				}
				sub->AddOption<BoolOption<bool>>(("Disable Collision"), nullptr, &no_clip.DisableCollision, BoolDisplay::OnOff);
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Movement Type", nullptr, &no_clip.FlyType, &no_clip.FlyInt);
				}
				sub->AddOption<NumberOption<float>>("Speed", nullptr, &no_clip.speed, 0.1f, 50.f, 0.01f, 2);
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Network"), SubmenuNetwork, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Players", nullptr, SubmenuPlayerList);
			});

		g_Render->AddSubmenu<RegularSubmenu>("Players List", SubmenuPlayerList, [](RegularSubmenu* sub)
			{
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{

						std::string name = PLAYER::GET_PLAYER_NAME(i);
						if (i == PLAYER::PLAYER_ID())
							name.append(" ~p~[Self]");

						sub->AddOption<SubOption>(name.c_str(), nullptr, SubmenuSelectedPlayer, [=]
							{
								g_SelectedPlayer = i;
							});
					}
				}
			});

		g_Render->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
			{
				sub;
	
			});

		g_Render->AddSubmenu<RegularSubmenu>(("Demo"), SubmenuTest, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Submenu Option", nullptr, SubmenuDemo);

			sub->AddOption<RegularOption>(("Regular Option"), nullptr, []
			{
				g_Logger->Info("You pressed the test option");
			});

			static bool testBool1{};
			sub->AddOption<BoolOption<bool>>(("Bool Option"), nullptr, &testBool1, BoolDisplay::OnOff);

			sub->AddOption<UnclickOption>(("Unclickable Option"), nullptr, [] {});

			static std::int32_t int32Test{ 1337 };
			sub->AddOption<NumberOption<std::int32_t>>("Int32", nullptr, &int32Test, 0, 1337);

			static std::int64_t int64Test{ 1337 };
			sub->AddOption<NumberOption<std::int64_t>>("Int64", nullptr, &int64Test, 0, 1337, 10);

			static float floatTest{ 1337.f };
			sub->AddOption<NumberOption<float>>("Float", nullptr, &floatTest, 0.f, 1337.f, 0.1f, 1);

			static std::vector<std::uint64_t> vector{ 1, 2, 3 };
			static std::size_t vectorPos{};

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Array", nullptr, &Lists::DemoList, &Lists::DemoListPos);
			sub->AddOption<ChooseOption<std::uint64_t, std::size_t>>("Vector", nullptr, &vector, &vectorPos);
		});

		g_Render->AddSubmenu<RegularSubmenu>("Settings", SubmenuSettings, [](RegularSubmenu* sub)
		{
		sub->AddOption<SubOption>("Header", nullptr, SubmenuSettingsHeader);
		sub->AddOption<SubOption>("Footer Text", nullptr, SubmenuSettingsSubmenuBar);
		sub->AddOption<SubOption>("Options", nullptr, SubmenuSettingsOption);
		sub->AddOption<SubOption>("Footer", nullptr, SubmenuSettingsFooter);
		sub->AddOption<SubOption>("Description", nullptr, SubmenuSettingsDescription);
		sub->AddOption<SubOption>("Input", nullptr, SubmenuSettingsInput);
		sub->AddOption<SubOption>("Themes", nullptr, SubmenuThemes);
		sub->AddOption<SubOption>("Demo", nullptr, SubmenuTest);
		sub->AddOption<NumberOption<float>>("X Position", nullptr, &g_Render->m_PosX, 0.f, 1.f, 0.01f, 2);
		sub->AddOption<NumberOption<float>>("Y Position", nullptr, &g_Render->m_PosY, 0.f, 1.f, 0.01f, 2);
		sub->AddOption<NumberOption<float>>("Width", nullptr, &g_Render->m_Width, 0.01f, 1.f, 0.01f, 2);
		sub->AddOption<BoolOption<bool>>("Sounds", nullptr, &g_Render->m_Sounds, BoolDisplay::OnOff);
		sub->AddOption<ChooseOption<const char*, std::size_t>>(("Toggles"), nullptr, &g_Render->ToggleList, &g_Render->ToggleIterator);
		sub->AddOption<ChooseOption<const char*, std::size_t>>(("Submenu Indicators"), nullptr, &g_Render->IndicatorList, &g_Render->IndicatorIterator);
		sub->AddOption<BoolOption<bool>>("Glare", nullptr, &g_Render->m_render_glare, BoolDisplay::OnOff);
		sub->AddOption<BoolOption<bool>>("Log Script Events", nullptr, &g_LogScriptEvents, BoolDisplay::OnOff);
		sub->AddOption<RegularOption>("Unload", nullptr, []
			{
				g_Running = false;
			});
		});

		g_Render->AddSubmenu<RegularSubmenu>(("Themes"), SubmenuThemes, [](RegularSubmenu* sub)
		{
				sub->AddOption<ChooseOption<const char*, std::size_t>>(("Themes"), nullptr, &g_Render->ThemeList, &g_Render->ThemeIterator);
		});

		g_Render->AddSubmenu<RegularSubmenu>("Footer Text", SubmenuSettingsSubmenuBar, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_Render->m_FooterTextSize, 0.01f, 1.f, 0.01f, 2);
			sub->AddOption<BoolOption<bool>>("Left Text", nullptr, &g_Render->LeftFooterText, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Right Text", nullptr, &g_Render->RightFooterText, BoolDisplay::OnOff);
			sub->AddOption<UnclickOption>(("Colors"), nullptr, [] {});
			sub->AddOption<NumberOption<std::uint8_t>>("Text R", nullptr, &g_Render->m_FooterTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text G", nullptr, &g_Render->m_FooterTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text B", nullptr, &g_Render->m_FooterTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text A", nullptr, &g_Render->m_FooterTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_Render->AddSubmenu<RegularSubmenu>("Options", SubmenuSettingsOption, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_Render->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_Render->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);
			sub->AddOption<UnclickOption>(("Colors"), nullptr, [] {});
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background R", nullptr, &g_Render->m_OptionSelectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background G", nullptr, &g_Render->m_OptionSelectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background B", nullptr, &g_Render->m_OptionSelectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background A", nullptr, &g_Render->m_OptionSelectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background R", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background G", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background B", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background A", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));

			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text R", nullptr, &g_Render->m_OptionSelectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text G", nullptr, &g_Render->m_OptionSelectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text B", nullptr, &g_Render->m_OptionSelectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text A", nullptr, &g_Render->m_OptionSelectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text R", nullptr, &g_Render->m_OptionUnselectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text G", nullptr, &g_Render->m_OptionUnselectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text B", nullptr, &g_Render->m_OptionUnselectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text A", nullptr, &g_Render->m_OptionUnselectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_Render->AddSubmenu<RegularSubmenu>("Footer", SubmenuSettingsFooter, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_Render->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_Render->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);
			sub->AddOption<BoolOption<bool>>("Dynamic Footer", nullptr, &g_Render->m_dynamic_footer, BoolDisplay::OnOff);
			sub->AddOption<UnclickOption>(("Colors"), nullptr, [] {});
			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_Render->m_FooterBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_Render->m_FooterBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_Render->m_FooterBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_Render->m_FooterBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite R", nullptr, &g_Render->m_FooterSpriteColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite G", nullptr, &g_Render->m_FooterSpriteColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite B", nullptr, &g_Render->m_FooterSpriteColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite A", nullptr, &g_Render->m_FooterSpriteColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_Render->AddSubmenu<RegularSubmenu>("Header", SubmenuSettingsHeader, [](RegularSubmenu* sub)
		{
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, []
			{
				g_Render->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
			});

			switch (g_Render->m_HeaderType)
			{
			case HeaderType::Static:
				sub->AddOption<SubOption>("Background", nullptr, SubmenuSettingsHeaderStaticBackground);
				break;
			case HeaderType::Gradient:
				sub->AddOption<SubOption>("Gradient", nullptr, SubmenuSettingsHeaderGradientBackground);
				break;
			}

			sub->AddOption<SubOption>("Text", nullptr, SubmenuSettingsHeaderText);
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_Render->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
		});

		g_Render->AddSubmenu<RegularSubmenu>("Header Background", SubmenuSettingsHeaderStaticBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_Render->m_HeaderBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_Render->m_HeaderBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_Render->m_HeaderBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_Render->m_HeaderBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_Render->AddSubmenu<RegularSubmenu>("Header Gradient", SubmenuSettingsHeaderGradientBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Transparent", nullptr, &g_Render->m_HeaderGradientTransparent, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Flip", nullptr, &g_Render->m_HeaderGradientFlip, BoolDisplay::YesNo);
			sub->AddOption<UnclickOption>(("Colors"), nullptr, [] {});
			sub->AddOption<NumberOption<std::uint8_t>>("R1", nullptr, &g_Render->m_HeaderGradientColorLeft.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G1", nullptr, &g_Render->m_HeaderGradientColorLeft.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B1", nullptr, &g_Render->m_HeaderGradientColorLeft.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A1", nullptr, &g_Render->m_HeaderGradientColorLeft.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("R2", nullptr, &g_Render->m_HeaderGradientColorRight.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G2", nullptr, &g_Render->m_HeaderGradientColorRight.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B2", nullptr, &g_Render->m_HeaderGradientColorRight.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A2", nullptr, &g_Render->m_HeaderGradientColorRight.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_Render->AddSubmenu<RegularSubmenu>("Header Text", SubmenuSettingsHeaderText, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("DX Header Text", "Disable native text if going to use dx", &g_Render->m_HeaderText, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Native Header Text", "Disable dx text if going to use native ", &g_Render->m_HeaderNativeText, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<float>>("Size", nullptr, &g_Render->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
			sub->AddOption<UnclickOption>(("Colors"), nullptr, [] {});
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_Render->m_HeaderTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_Render->m_HeaderTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_Render->m_HeaderTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_Render->m_HeaderTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_Render->AddSubmenu<RegularSubmenu>("Description", SubmenuSettingsDescription, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Padding", "Padding before the description rect.", &g_Render->m_DescriptionHeightPadding, 0.01f, 1.f, 0.001f,
 3);
			sub->AddOption<NumberOption<float>>("Height", "Size of the description rect.", &g_Render->m_DescriptionHeight, 0.01f, 1.f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", "Size of the description text.", &g_Render->m_DescriptionTextSize, 0.1f, 2.f, 0.01f, 2);
		});

		g_Render->AddSubmenu<RegularSubmenu>("Input", SubmenuSettingsInput, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::int32_t>>("Open Delay", nullptr, &g_Render->m_OpenDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Back Delay", nullptr, &g_Render->m_BackDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Enter Delay", nullptr, &g_Render->m_EnterDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Vertical Delay", nullptr, &g_Render->m_VerticalDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Horizontal Delay", nullptr, &g_Render->m_HorizontalDelay, 10, 1000, 10, 0);
		});
	}

	void MainScript::Destroy()
	{
		g_Render.reset();
	}

	void MainScript::Tick()
	{
		Initialize();
		while (true) {
			g_Render->OnTick();
			FeatureInitalize();
			fbr::cur()->wait();
		}
	}
}

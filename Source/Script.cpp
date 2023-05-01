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
#include "BoolWithNumber.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "BoolWithChoose.h"
#include "UI/PlayerSubmenu.hpp"
#include "PlayerSub.hpp"
#include "FiberHelper.hpp"
#include "Features.h"
#include "Enums.h"
#include "All Players.h"
#include "Players.h"
#include "Hooking.hpp"
#include "Protections.h"
#include "Queue.h"
#include "Spoofing.h"
#include "KeyboardOption.h"
#include "Render.h"
#include "Notifications.h"
#include "Discord/DiscordHandler.hpp"
#include "hex_memory.h"
#include "ScriptLocal.h"
#include "Hotkeys.h"
namespace Saint
{

	enum Submenu : std::uint32_t
	{
		SubmenuCustomFlags,
		//HOME
		SubmenuHome,
		SubmenuSpammer,
		SubmenuSpoofSpammer,

		//SELF
		SubmenuSelf,

		SubmenuNoClip,
		SubmenuInvisible,
		SubmenuSuperjump,
		SubmenuMultipliers,
		//SESSION
		SubmenuSendToInt,
		SubmenuApartments,
		SubmenuNetwork,
		SubmenuPlayerList,
		SubmenuSelectedPlayer,
		SubmenuAntiCheat,
		SubmenuRegion,

		//SELECTEDPLAYER
		SubmenuBodyguards,
		SubmenuDrops,
		SubmenuPlayerTeleport,
		//SELECTED_TROLLING
		SubmenuTrolling,
		SubmenuFakeDrops,

		//spoofing
		SubmenuCrew,

		//VEHICLE
		SubmenuVehicle,
		SubmenuVehicleMultipliers,
		SubmenuHornBoost,
		SubmenuEngineSound,
		SubmenuNegitiveTorque,
		SubmenuCustomize,
		SubmenuPresets,
		SubmenuSpeedo,
		SubmenuAcrobatics,
		SubmenuAutoPilot,
		//WEAPON
		SubmenuWeapon,
		SubmenuExplosiveAmmo,
		SubmenuRapidFire,
		SubmenuWeaponAnimation,
		SubmenuGunLocker,
		SubmenuGunLockerGive,
		SubmenuGunLockerAmmo,
		SubmenuWeaponMultipliers,
		SubmenuDamageTest,

		SubmenuMaxThatFucker,

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
		SubMenuTranslations,
		SubmenuTest,
		SubmenuToggles,
		SubmenuTogglesColor,
		SubmenuColors,
		Customization,
		CustomizationSubheader,
		CustomizationToggles,
		CustomizationBase,
		CustomizationHeader,
		Positions,
		PositionsMenu,
		PositionsGlobe,
		//COLORS
		SubmenuHeaderColor,
		SubmenuHeaderText,
		SubmenuOptionSelectedBackground,
		SubmenuOptionUnselectedBackground,
		OptionTextSelected,
		OptionTextUnselected,
		FooterBackground,
		FooterSprite,
		SubheaderBackground,
		SubheaderTextLeft,
		SubheaderTextRight,
		//WORLD
		SubmenuWorld,
		SubmeuWeather,
		SpawnerSelectedSettings,
		SubmenuSelectedVehicleSearch,

		//LSC
		LosSantosArmor,
		LosSantosBrakes,
		LosSantosRightFender,
		LosSantosFender,
		LosSantosBumpers,
		LosSantosEngine,
		LosSantosExhaust,
		LosSantosLivery,
		LosSantosGrille,
		LosSantosHood,
		LosSantosHorn,
		LosSantosLights,
		LosSantosPlate,
		LosSantosFront,
		LosSantosRear,
		LosSantosRespray,
		LosSantosRoof,
		LosSantosSkirts,
		LosSantosChassis,
		LosSantosSpoiler,
		LosSantosSuspension,
		LosSantosTransmission,
		LosSantosTurbo,
		LosSantosWheels,
		LosSantosWindows,

		SubmenuAirstrike,
		SubmenuTargetingMode,
		SubmenuTargetMode,
		SubmenuTriggerbot,
		SubmenuSpamText,
		SubmenuUpgrades,
		SubmenuUpgradeLoop,
		SubmenuOutfitEditor,
		SubmenuExplode,
		SubmenuExplodeBlame,
		SubmenuAttackers,
		SubmenuAllPlayers,

		//SessionNotifcations
		SubmenuNotifcations,
		SubmenuPlayerJoining,

		SubmenuVehicleSpawner,
		SubmenuVehicleSearch,
		SubmenuGetClass,
		SpawnerSettings,
		SpawnerSettingsColor,
		SpawnerSettingsSpawnInAir,
		SpawnerSettingsSetForwardSpeed,
		SubmenuVehicleAll,

		SubmenuAllSettings,
		SubmenuAllJets,
		SubmenuJetExcludes,

		SubmenuAllExplode,
		SubmenuAllExplodeBlame,
		SubmenuAllExplodeExcludes,
		PLATEHOLDER25,
		VANITY_PLATES26,
		TRIM27,
		ORNAMENTS28,
		DASHBOARD29,
		DIAL30,
		DOOR_SPEAKER31,
		SEATS32,
		STEERINGWHEEL33,
		SubmenuRaimbow,
		SHIFTER_LEAVERS34,
		PLAQUES35,
		SPEAKERS36,
		SubmenuTeam,
		TRUNK37,
		HYDRAULICS38,
		ENGINE_BLOCK39,
		AIR_FILTER,
		STRUTS,
		ARCH_COVER,
		AERIALS,
		TRIM_2,
		TANK,
		WINDOWS,
		UNK47,
		SubmenuMisc,
		SubmenuReplaceText,
		HandTrails,
		SubmenuFOV,
		SubmenuRemoval,
		SubmenuCrashes,
		SubmenuKicks,
		SubmenuRequests,
		SubmenuSesStart,
		SubmenuFriendly,
		SubmenuGiveWeapons,
		SubmenuOffRadar,
		SubmenuFlagCreator,
		SubmenuTeleport,
		SubmenuRIDJoiner,
		SubmenuProtections,
		SubmenuScriptEvents,
		SubmenuWater,
		SubmenuAimbot,
		SubmenuAimbotExcludes,
		SubmenuChangeVehicleColor,
		SubmenuChat,
		SubmenuPeds,
		SubmenuAnimations,
		SubmenuScenarios,
		SubmenuCage,
		SubmenuIncrement,
		SubmenuSpoofing,
		SubmenuGame,
		SubmenuInformation,
		SubmenuIP,
		SubmenuSelectedWeapon,
		SubmenuSelectedExplosiveAmmo,
		SubmenuBlameExplosiveAmmo,
		SubmenuPersonalVehicles,
		SubmenuVehicleRamps,
		SubmenuSavedVehicles,
		SubmenuScripts,
		SubmenuRecovery,
		SubmenuRP,
		SubmenuUnlocks,

		SubmenuDLC,

		SubmenuRMisc,

		SubmenuMoney,


		SubmenuDEmeth,

		SubmenuSelectedSpawner,
		SubmenuSelectedGet,
		SubmenuOutfitLoader,
		SubmenuVehicleInvis,
		SubmenuSelectedVehicle,
		SubmenuProtCrash,
		EntityShooter,
		EntityShooterVehicle,
		EntityShooterSelectedClass,

		//Heist Editing
		HeistControl,
		DiamondCasino,
		CayoPerico,

		//Disables
		Disables,
		//world
		NearbyPeds,
		NearbyVehicles,
		NearbyManager,
		SubmenuVehParticles,
		SubmenuUnlocks2,
		SubmenuSelectedVehicleColor,

		//Handling
		HandlingMisc,
		CentreOfMass,
		InertiaMultiplier,
		DriveBias,
		Shift,
		HandlingBrakes,
		SteeringLock,
		Traction,
		Curve,
		Suspension,
		AntiRollbar,
		RollCentreHeight,
		HandlingDamage,
		HandlingGas,
		//Discord RPC
		DiscordRPC,
		SubmenuParachute,

		//Protections
		SubmenuEntities,

		//More Player Stuff
		SubmenuSavedPlayers,
		SubmenuSelectedDetections,

		SubmenuStreamerMode,

		SubmenuWalkStyles,

		SubmenuGameEvents,

		SubmenuFriends,
		SubmenuSelectedFriend,

		SubmenuSocialClub,

		SubmenuPersonalVehicle,

		SubmenuModelChanger,
		SubmenuSelectedModelChanger,

		SubmenuSelectedChat,
		SubmenuSelectedChatPresets,
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
		if (!std::filesystem::exists("C:\\Saint\\Translations"))
			std::filesystem::create_directory("C:\\Saint\\Translations");

		if (std::filesystem::exists("C:\\Saint\\Translations\\chinese.json"))
			std::filesystem::remove("C:\\Saint\\Translations\\chinese.json");

		URLDownloadToFileA(0, "https://saintcheats.xyz/chinese.json", "C:\\Saint\\Translations\\chinese.json", 0, 0);

		if (std::filesystem::exists("C:\\Saint\\Translations\\english.json"))
			std::filesystem::remove("C:\\Saint\\Translations\\english.json");

		URLDownloadToFileA(0, "https://saintcheats.xyz/english.json", "C:\\Saint\\Translations\\english.json", 0, 0);

		if (LOCALIZATION::GET_CURRENT_LANGUAGE() == 9 || LOCALIZATION::GET_CURRENT_LANGUAGE() == 12)
			Translations::LoadTranslation("C:\\Saint\\Translations\\chinese.json");
		else
			Translations::LoadTranslation("C:\\Saint\\Translations\\english.json");

		g_Render->draw_submenu<sub>("Main Menu", SubmenuHome, [](sub* sub)
			{

				sub->draw_option<submenu>("Player", nullptr, SubmenuSelf);
				sub->draw_option<submenu>("Network", nullptr, SubmenuNetwork);
				sub->draw_option<submenu>("Protections", nullptr, SubmenuProtections);
				sub->draw_option<submenu>("Teleport", nullptr, SubmenuTeleport);
				sub->draw_option<submenu>("Weapon", nullptr, SubmenuWeapon);
				sub->draw_option<submenu>("Vehicle", nullptr, SubmenuVehicle);
				sub->draw_option<submenu>("Misc", nullptr, SubmenuMisc);
				sub->draw_option<submenu>("World", nullptr, SubmenuWorld);
				sub->draw_option<submenu>("Settings", nullptr, SubmenuSettings);

			});
		g_Render->draw_submenu<sub>(("Self"), SubmenuSelf, [](sub* sub)
			{
				sub->draw_option<submenu>("No-Clip", nullptr, SubmenuNoClip);
				sub->draw_option<submenu>("Invisible", nullptr, SubmenuInvisible);
				sub->draw_option<submenu>("Super Jump", nullptr, SubmenuSuperjump);
				sub->draw_option<submenu>("Multipliers", nullptr, SubmenuMultipliers);
				sub->draw_option<submenu>("Model Changer", nullptr, SubmenuModelChanger);
				sub->draw_option<submenu>("Outfit Editor", nullptr, SubmenuOutfitEditor);
				sub->draw_option<submenu>("Animations", nullptr, SubmenuAnimations);
				sub->draw_option<submenu>("Hand Trails", nullptr, HandTrails);
				sub->draw_option<submenu>("Walk Styles", nullptr, SubmenuWalkStyles);
				sub->draw_option<submenu>("Parachute", nullptr, rage::joaat("ParachuteSelf"));
				sub->draw_option<submenu>("Ragdoll", nullptr, rage::joaat("RagdollFort"));
				sub->draw_option<toggle<bool>>(("Godmode"), nullptr, &godmode, BoolDisplay::OnOff, false, [] {
					if (!godmode)
					{
						(*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits = 0;

					}
					});
				sub->draw_option<toggle<bool>>(("Never Wanted"), "Disables the wanted level system.", &neverWantedBool, BoolDisplay::OnOff, false, [] {
					if (!neverWantedBool) {
						PLAYER::SET_MAX_WANTED_LEVEL(5);
					}
					});
				sub->draw_option<toggle<bool>>(("Slide Run"), "Slides you around the map.", &features.slide_run, BoolDisplay::OnOff);

				sub->draw_option<toggle<bool>>(("Seatbelt"), "Click you're seatbelt so you don't fly out of the vehicle.", &features.seatbelt, BoolDisplay::OnOff, false, [] {
					if (!features.seatbelt) {
						PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), false);
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, true);
					}
					});
				sub->draw_option<toggle<bool>>(("Explosive Melee"), "Allows you have the ability from director mode.", &m_frame_flags.m_explosive_melee, BoolDisplay::OnOff);
				
				sub->draw_option<toggle<bool>>(("Pickup Entities"), "Allows you to pickup & throw entities and players.", &features.pickup_mode, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Auto Clean"), "Automaticly cleans you're ped from visual damage.", &features.autoclean, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Forcefield"), "Automaticly cleans you're ped from visual damage.", &features.force_field, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Swim Anywhere"), nullptr, &features.swim_anywhere, BoolDisplay::OnOff, false, [] {
					if (!features.swim_anywhere)
					{
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 65, false);
					}
					});
				sub->draw_option<toggle<bool>>(("Tiny Ped"), "Shrinks you're ped.", &features.tiny_ped, BoolDisplay::OnOff, false, [] {
					if (!features.tiny_ped)
					{
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, false);
					}
					});
				sub->draw_option<toggle<bool>>(("Take Less Damage"), "Headshots won't kill you instantly.", &features.take_less_damage, BoolDisplay::OnOff, false, [] {
					if (!features.take_less_damage)
					{
						PED::SET_PED_SUFFERS_CRITICAL_HITS(PLAYER::PLAYER_PED_ID(), TRUE);
					}
					});
				sub->draw_option<toggle<bool>>(("Crouched"), "", &features.crouched, BoolDisplay::OnOff, false, [] {
					if (!features.crouched)
					{
						PED::RESET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), 1.0f);
					}
					});
				sub->draw_option<toggle<bool>>(("Unlimited Special Ability"), "Automaticly refills your special ability bar.", &features.unlim, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Attack Friendly"), "Allows you to shoot teammates.", &features.attack_friendly, BoolDisplay::OnOff, false, [] {
					if (!features.attack_friendly)
					{
						PED::SET_CAN_ATTACK_FRIENDLY(PLAYER::PLAYER_PED_ID(), false, true);
					}
					});
				sub->draw_option<toggle<bool>>(("Reduced Collision"), "Allows you to walk through walls and such.", &features.reduced, BoolDisplay::OnOff, false, [] {
					if (!features.reduced)
					{
						PED::SET_PED_CAPSULE(PLAYER::PLAYER_PED_ID(), false);
					}
					});
				sub->draw_option<toggle<bool>>(("Bound Ankles"), "Makes it so when you ragdoll, You cannot get up.", &features.bound_ankles, BoolDisplay::OnOff, false, [] {
					if (!features.bound_ankles)
					{
						PED::SET_ENABLE_BOUND_ANKLES(PLAYER::PLAYER_PED_ID(), false);
					}
					});
				sub->draw_option<toggle<bool>>(("Ignored By Peds"), "Makes pedestrains around you ignore your actions.", &features.ignored, BoolDisplay::OnOff, false, [] {
					if (!features.ignored)
					{
						PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
						PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
						PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(PLAYER::PLAYER_ID(), true);
						PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(PLAYER::PLAYER_ID(), false);

					}
					});
				sub->draw_option<toggle<bool>>(("Drugs"), "Recreates the micheal strangers & things mission.", &features.drugs, BoolDisplay::OnOff, false, [] {
					if (!features.drugs)
					{
						GRAPHICS::ENABLE_ALIEN_BLOOD_VFX(false);
						GRAPHICS::ANIMPOSTFX_STOP("DrugsMichaelAliensFight");


					}
					});

				sub->draw_option<toggle<bool>>(("Blink"), "Like a freecam but you teleport to the end, And you can control you're ped.", &blink.enabled, BoolDisplay::OnOff, false, [] {
					if (!blink.enabled)
					{
						NativeVector3 c = CAM::GET_CAM_COORD(blink.freecamCamera);
						NativeVector3 rot = CAM::GET_CAM_ROT(blink.freecamCamera, 2);
						ENTITY::SET_ENTITY_ROTATION(PLAYER::PLAYER_PED_ID(), rot.x, rot.y, rot.z, 2, 1);
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z, true, true, true);
						CAM::RENDER_SCRIPT_CAMS(false, true, 700, true, true, true);
						CAM::SET_CAM_ACTIVE(blink.freecamCamera, false);
						CAM::DESTROY_CAM(blink.freecamCamera, true);
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), true);

					}
					});
				sub->draw_option<toggle<bool>>(("Wet"), "", &features.wet, BoolDisplay::OnOff, false, [] {
					if (!features.wet)
					{
						PED::SET_PED_WETNESS_HEIGHT(PLAYER::PLAYER_PED_ID(), 0);

					}
					});
				sub->draw_option<toggle<bool>>(("Walk Underwater"), "Disables the swimming animation.", &features.walk_underwater, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Push Water Away"), "Pushes water away from you.", &features.push_water_away, BoolDisplay::OnOff);
				
				sub->draw_option<number<std::int32_t>>("Wanted Level", nullptr, &i_hate_niggers, 0, 5, 1, 3, true, "", "", [] {
					(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_wanted_level = i_hate_niggers;
					});
				sub->draw_option<number<float>>("Move Rate", nullptr, &move_rate, 0, 10.0, 1.0, 3, true, "", "", [] {
					PED::SET_PED_MOVE_RATE_OVERRIDE(PLAYER::PLAYER_PED_ID(), move_rate);
					});

			});
			g_Render->draw_submenu<sub>(("Ragdoll"), rage::joaat("RagdollFort"), [](sub* sub)
				{
					sub->draw_option<toggle<bool>>(("Disable"), "", &features.no_ragdoll, BoolDisplay::OnOff, false, [] {
						if (!features.no_ragdoll)
						{
							PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), true);
							PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
							PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), true);
						}
						});
					if (features.no_ragdoll) {
						sub->draw_option<UnclickOption>(("Ragdoll is disabled."), nullptr, [] {});
					}
					if (!features.no_ragdoll) {
						sub->draw_option<toggle<bool>>(("On Q"), "", &features.ragdoll_on_q, BoolDisplay::OnOff);
						sub->draw_option<toggle<bool>>(("On Jump"), "", &ragdoll.on_jump, BoolDisplay::OnOff);
						sub->draw_option<toggle<bool>>(("On Collison"), "", &ragdoll.on_collison, BoolDisplay::OnOff, false, [] {
							if (!ragdoll.on_collison)
							{
								PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
							}
							});
						sub->draw_option<RegularOption>(("Start"), nullptr, []
							{
								NativeVector3 v = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::PLAYER_PED_ID());
								PED::SET_PED_TO_RAGDOLL_WITH_FALL(PLAYER::PLAYER_PED_ID(), 1500, 2000, 1, -v.x, -v.y, -v.z, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
							});
					}
				});
		g_Render->draw_submenu<sub>(("Smoke Trail Color"), rage::joaat("SmokeTrail"), [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("R", nullptr, &changeVehicleColor.r, 0, 255, 1, 3, true, "", "", [] {
					parachutes.set_color(parachutes.r, parachutes.g, parachutes.b);
					});
				sub->draw_option<number<std::int32_t>>("G", nullptr, &changeVehicleColor.g, 0, 255, 1, 3, true, "", "", [] {
					parachutes.set_color(parachutes.r, parachutes.g, parachutes.b);
					});
				sub->draw_option<number<std::int32_t>>("B", nullptr, &changeVehicleColor.b, 0, 255, 1, 3, true, "", "", [] {
					parachutes.set_color(parachutes.r, parachutes.g, parachutes.b);
					});
			});
		g_Render->draw_submenu<sub>(("Parachute"), rage::joaat("ParachuteSelf"), [](sub* sub)
			{
				sub->draw_option<submenu>("Smoke Trail Color", nullptr, rage::joaat("SmokeTrail"));
				sub->draw_option<toggle<bool>>(("Give When In Plane"), "", &parachutes.give_when_in_plane, BoolDisplay::OnOff, false, [] {
					if (!parachutes.give_when_in_plane)
					{
						PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(PLAYER::PLAYER_PED_ID(), false);


					}
					});
				sub->draw_option<toggle<bool>>(("Use Reserved"), "", &parachutes.use_reservered, BoolDisplay::OnOff, false, [] {
					if (!parachutes.use_reservered)
					{
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 363, false);


					}
					});
				sub->draw_option<toggle<bool>>(("Auto Deploy"), "Automaticly pulls you're parachute.", &features.auto_parachute, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Tint"), nullptr, [] {});
				for (std::uint32_t i = 0; i < 14; ++i) {
					sub->draw_option<RegularOption>((parachutes.types[i]), nullptr, [=]
						{

							parachutes.set_tint(i - 1);


						});
				}
			});
		g_Render->draw_submenu<sub>(("Walk Styles"), SubmenuWalkStyles, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Reset"), nullptr, []
					{
						PED::RESET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), 1.0f);

					});
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				sub->draw_option<RegularOption>("Sexy", nullptr, [=]
					{

						walk_style->change("move_f@sexy@a");

					});
				sub->draw_option<RegularOption>("Injured", nullptr, [=]
					{

						walk_style->change("move_injured_generic");

					});
				sub->draw_option<RegularOption>("Gangster", nullptr, [=]
					{

						walk_style->change("move_m@gangster@var_f");

					});
				sub->draw_option<RegularOption>("Drunk (Slightly)", nullptr, [=]
					{

						walk_style->change("MOVE_M@DRUNK@SLIGHTLYDRUNK");

					});
				sub->draw_option<RegularOption>("Drunk (Very)", nullptr, [=]
					{

						walk_style->change("MOVE_M@DRUNK@VERYDRUNK");

					});
				sub->draw_option<RegularOption>("Scared", nullptr, [=]
					{

						walk_style->change("move_f@scared");

					});
				sub->draw_option<RegularOption>("Flee", nullptr, [=]
					{

						walk_style->change("move_f@flee@a");

					});
				sub->draw_option<RegularOption>("Crouched", nullptr, [=]
					{

						walk_style->change("move_ped_crouched");

					});



			});
		g_Render->draw_submenu<sub>(("Model Changer"), SubmenuModelChanger, [](sub* sub)
			{
				for (std::int32_t i = 0; i < m_ModelChanger.size; i++) {
					sub->draw_option<submenu>(m_ModelChanger.get_class_name[i], nullptr, SubmenuSelectedModelChanger, [=]
						{
							m_ModelChanger.selected_class = i;
						});

				}
			});
		g_Render->draw_submenu<sub>((m_ModelChanger.get_class_name[m_ModelChanger.selected_class]), SubmenuSelectedModelChanger, [](sub* sub)
			{
				for (auto& model : m_ModelChanger.m_GetModels) {
					if (m_ModelChanger.selected_class == model.m_class) {
						sub->draw_option<RegularOption>(model.m_name.c_str(), nullptr, [=]
							{

								m_ModelChanger.change(rage::joaat(model.m_model.c_str()));

							});
					}
				}


			});
		g_Render->draw_submenu<sub>(("Hand Trails"), HandTrails, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &g_HandTrails.enabled, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &g_HandTrails.type, &g_HandTrails.size);
				sub->draw_option<UnclickOption>(("Color"), nullptr, [] {});
				sub->draw_option<toggle<bool>>(("Rainbow"), nullptr, &g_HandTrails.rainbow, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Red", nullptr, &g_HandTrails.r, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Green", nullptr, &g_HandTrails.g, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Blue", nullptr, &g_HandTrails.b, 0, 255, 1, 3, true, "", "", [] {

					});
			});
		g_Render->draw_submenu<sub>(("Outfit Editor"), SubmenuOutfitEditor, [](sub* sub)
			{
				sub->draw_option<submenu>("Load", nullptr, SubmenuOutfitLoader);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Component", nullptr, &Lists::HeaderTypesFrontend2, &Lists::HeaderTypesPosition2, true, -1, [] {
					g_Render->outfits = Lists::HeaderTypesBackend2[Lists::HeaderTypesPosition2];
					});
				switch (g_Render->outfits) {
				case Outfits::Face:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets face variation.", &testa, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, testa, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets face texture variation.", &facetexture, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0, testa), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, testa, facetexture, 0); }); break;
				case Outfits::Head:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets head variation.", &testb, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, testb, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets head texture variation.", &facetexture1, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1, testb), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, testb, facetexture1, 0); }); break;
				case Outfits::Hair:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets hair variation.", &testc, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, testc, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets hair texture variation.", &facetexture2, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2, testc), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, testc, facetexture2, 0); }); break;
				case Outfits::Torso:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets torso variation.", &testd, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 3), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, testd, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets torso texture variation.", &facetexture3, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 3, testd), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, testd, facetexture3, 0); }); break;
				case Outfits::Torso2:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets torso 2 variation.", &testl, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 11), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, testl, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets torso 2 texture variation.", &facetexture4, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 11, testl), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, testl, facetexture4, 0); }); break;
				case Outfits::Legs:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets leg variation.", &teste, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 4), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, teste, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets leg texture variation.", &facetexture5, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 4, teste), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, teste, facetexture5, 0); }); break;
				case Outfits::Hands:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets hand variation.", &testf, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 5), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, testf, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets hand texture variation.", &facetexture6, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 5, testf), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, testf, facetexture6, 0); }); break;
				case Outfits::Feet:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets feet variation.", &testg, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, testg, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets feet texture variation.", &facetexture7, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6, testg), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, testg, facetexture7, 0); }); break;
				case Outfits::Eyes:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets eye variation.", &testh, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, testh, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets eyes texture variation.", &facetexture8, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7, testh), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, testh, facetexture8, 0); }); break;
				case Outfits::Accessories:

					sub->draw_option<number<std::int32_t>>("Drawable", "Sets accessories variation.", &testi, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 8), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, testi, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets accessories texture variation.", &facetexture9, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 8, testi), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, testi, facetexture9, 0); }); break;
				case Outfits::Vests:

					sub->draw_option<number<std::int32_t>>("Drawable", "Sets vest variation.", &testj, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 9), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, testj, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets vests texture variation.", &facetexture10, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 9, testj), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, testj, facetexture10, 0); }); break;
				case Outfits::Decals:

					sub->draw_option<number<std::int32_t>>("Drawable", "Sets texture variation.", &testk, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 10), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, testk, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets decals texture variation.", &facetexture11, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 10, testk), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, testk, facetexture11, 0); }); break;
				}
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Props", nullptr, &Lists::HeaderTypesFrontend3, &Lists::HeaderTypesPosition3, true, -1, [] {
					g_Render->props = Lists::HeaderTypesBackend3[Lists::HeaderTypesPosition3];
					});
				switch (g_Render->props) {
				case Props::Hats:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &hatDrawable, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, hatDrawable, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &hatTexture, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0, hatDrawable), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, hatDrawable, hatTexture, 0); }); break;
					break;
				case Props::Glasses:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &glassesDrawable, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, glassesDrawable, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &glassesTexture, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1, glassesDrawable), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, glassesDrawable, glassesTexture, 0); }); break;
					break;
				case Props::Ears:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &earsDrawable, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, earsDrawable, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &earsTexture, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2, earsDrawable), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, earsDrawable, earsTexture, 0); }); break;
					break;
				case Props::Watches:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &watchesDrawable, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 6, watchesDrawable, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &watchesTexture, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6, watchesDrawable), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 6, watchesDrawable, watchesTexture, 0); }); break;
					break;
				case Props::Bracelets:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &braceDrawable, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 7, braceDrawable, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &braceTexture, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7, braceDrawable), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 7, braceDrawable, braceTexture, 0); }); break;
					break;
				}

			});
		g_Render->draw_submenu<sub>(("Animations"), SubmenuAnimations, [](sub* sub)
			{
				//sub->draw_option<submenu>("Scenarions", "", Submenu::SubmenuScenarios);
				sub->draw_option<toggle<bool>>(("Controllable"), nullptr, &animation.controllable, BoolDisplay::OnOff);
				sub->draw_option<RegularOption>(("Stop"), nullptr, [=]
					{
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());

					});
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				sub->draw_option<RegularOption>(("Pole Dance"), nullptr, [=]
					{
						animation.start("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");

					});
				sub->draw_option<RegularOption>(("Sit Ups"), nullptr, [=]
					{
						animation.start("amb@world_human_sit_ups@male@base", "base");

					});
				sub->draw_option<RegularOption>(("Push Ups"), nullptr, [=]
					{
						animation.start("amb@world_human_push_ups@male@base", "base");

					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Suicide", nullptr, &animation.suc, &animation.suc_data, false, -1, [] {
					switch (animation.suc_data) {
					case 0:
						animation.start("mp_suicide", "pistol");
						break;
					case 1:
						animation.start("mp_suicide", "pill");
						break;
					}
					});
				sub->draw_option<RegularOption>(("Meditate"), nullptr, [=]
					{
						animation.start("rcmcollect_paperleadinout@", "meditiate_idle");

					});
				sub->draw_option<RegularOption>(("Cower"), nullptr, [=]
					{
						animation.start("amb@code_human_cower@female@idle_a", "idle_c");

					});
				sub->draw_option<RegularOption>(("Plant"), nullptr, [=]
					{
						animation.start("amb@world_human_gardener_plant@female@idle_a", "idle_a_female");


					});
				sub->draw_option<RegularOption>(("Dance"), nullptr, [=]
					{
						animation.start("oddjobs@assassinate@multi@yachttarget@lapdanc", "yacht_ld_f");


					});
				
				for (std::int32_t i = 0; i < animation.scenarios.size; i++) {
					sub->draw_option<RegularOption>(animation.scenarios.name[i], nullptr, [=]
						{

							animation.start(animation.scenarios.dict[i], animation.scenarios.id[i]);
						});

				}

			});
		g_Render->draw_submenu<sub>(("Load"), SubmenuOutfitLoader, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Save"), nullptr, [=]
					{
						showKeyboard("Enter Something", "", 25, &g_Outfits.buffer, [] {
							g_Outfits.save(g_Outfits.buffer);
							});


					});
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				if (std::filesystem::exists("C:\\Saint\\Outfits\\") && std::filesystem::is_directory("C:\\Saint\\Outfits\\")) {

					namespace fs = std::filesystem;
					fs::directory_iterator dirIt{ "C:\\Saint\\Outfits\\" };
					for (auto&& dirEntry : dirIt)
					{
						if (dirEntry.is_regular_file())
						{
							auto path = dirEntry.path();
							if (path.has_filename())
							{
								if (path.extension() == ".ini")
								{

									char nigger[64];
									sprintf(nigger, "%s", path.stem().u8string().c_str());
									sub->draw_option<RegularOption>(nigger, nullptr, [=]
										{
											g_Outfits.load(nigger);
										});

								}

							}
						}
					}
				}
				else {
					std::filesystem::create_directory("C:\\Saint\\Outfits\\");
				}


			});

		g_Render->draw_submenu<sub>(("Invisible"), SubmenuInvisible, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &invisible.enabled, BoolDisplay::OnOff, false, [] {
					if (!invisible.enabled) {
						ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, false);

					}
					});
				sub->draw_option<toggle<bool>>(("Locally Visible"), nullptr, &invisible.local_visible, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("No-Clip"), SubmenuNoClip, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &no_clip.enabled, BoolDisplay::OnOff, false, [] {
					if (!no_clip.enabled) {
						no_clip.onDisable();
						ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), 255, false);
					}
					});
				sub->draw_option<toggle<bool>>(("Set Rotation"), nullptr, &no_clip.SetRotation, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Spin"), nullptr, &no_clip.spin, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Transparent"), "", &no_clip.transparent, BoolDisplay::OnOff, false, [] {
					if (!no_clip.transparent)
					{
						ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), 255, true);


					}
					});
				sub->draw_option<toggle<bool>>(("Include Vehicles"), nullptr, &no_clip.WorkForVehicles, BoolDisplay::OnOff);
				if (no_clip.WorkForVehicles) {
					sub->draw_option<toggle<bool>>(("Stop After No Input"), nullptr, &no_clip.StopAfterNoInput, BoolDisplay::OnOff);
					sub->draw_option<toggle<bool>>(("Disable Collision"), nullptr, &no_clip.DisableCollision, BoolDisplay::OnOff);
				}

				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
					sub->draw_option<ChooseOption<const char*, std::size_t>>("Animation", nullptr, &no_clip.FlyType, &no_clip.FlyInt);
				}
				sub->draw_option<number<float>>("Speed", nullptr, &no_clip.speed, 0.1f, 50.f, 0.01f, 2);
			});
		g_Render->draw_submenu<sub>(("Multipliers"), SubmenuMultipliers, [](sub* sub)
			{

				sub->draw_option<toggle_number_option<float, bool>>("Run Speed", nullptr, &multipliers.run, &multipliers.run_speed, 0.1f, 10.f, 0.01f, 2, false, "", "", [] {
					if (!multipliers.run) {
						(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_run_speed = 1.0f;
					}
					});
				sub->draw_option<toggle_number_option<float, bool>>("Swim Speed", nullptr, &multipliers.swim_run, &multipliers.swim_speed, 0.1f, 10.f, 0.01f, 2, false, "", "", [] {

					if (!multipliers.run) {
						(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_swim_speed = 1.0f;
					}
					});
				sub->draw_option<toggle_number_option<float, bool>>("Width", nullptr, &get_model_info.width, &get_model_info.widthm, 0.1f, 10.f, 0.01f, 2, true, "", "", [] {


					if (!get_model_info.width) {
						Memory::set_value<float>({ 0x08, 0x0064 }, 1.0f);
					}
					});
				sub->draw_option<toggle_number_option<float, bool>>("Height", nullptr, &get_model_info.height, &get_model_info.heightm, 0.1f, 10.f, 0.01f, 2, true, "", "", [] {

					if (!get_model_info.height) {
						Memory::set_value<float>({ 0x08, 0x88 }, 1.0f);
					}
					});


			});
		g_Render->draw_submenu<sub>(("Super Jump"), SubmenuSuperjump, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &superjump.enabled, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Add Force"), nullptr, &superjump.add_force, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Animation", nullptr, &superjump.Jump_Type, &superjump.Jump_Int);
			});
		g_Render->draw_submenu<sub>(("Vehicle"), SubmenuVehicle, [](sub* sub)
			{
				sub->draw_option<submenu>("Spawner", nullptr, Submenu::SubmenuVehicleSpawner);
				sub->draw_option<submenu>("Handling", "", Submenu::SubmenuVehicleMultipliers);
				sub->draw_option<submenu>("Horn Boost", nullptr, Submenu::SubmenuHornBoost);
				sub->draw_option<submenu>("Acrobatics", nullptr, Submenu::SubmenuAcrobatics);
				sub->draw_option<submenu>("Auto-Pilot", nullptr, Submenu::SubmenuAutoPilot);
				sub->draw_option<submenu>("Speedometer", nullptr, Submenu::SubmenuSpeedo);
				sub->draw_option<submenu>("Engine Sound", nullptr, Submenu::SubmenuEngineSound);
				sub->draw_option<submenu>("Negitive Torque", nullptr, Submenu::SubmenuNegitiveTorque);
				//sub->draw_option<submenu>("Parachute", nullptr, Submenu::SubmenuParachute);
				sub->draw_option<submenu>("Particles", nullptr, Submenu::SubmenuVehParticles);
				sub->draw_option<submenu>("Invisible", nullptr, Submenu::SubmenuVehicleInvis);
				sub->draw_option<submenu>("Ramps", nullptr, Submenu::SubmenuVehicleRamps);
				sub->draw_option<submenu>("Randomization", nullptr, Submenu::SubmenuUpgrades);
				sub->draw_option<submenu>("LSC", nullptr, Submenu::SubmenuCustomize);
				sub->draw_option<submenu>("Color", nullptr, Submenu::SubmenuChangeVehicleColor);
				sub->draw_option<submenu>("Personal", nullptr, Submenu::SubmenuPersonalVehicle);
				sub->draw_option<submenu>("Forge Model", nullptr, rage::joaat("ForgeModel"));
				sub->draw_option<submenu>("Rocket Boost", nullptr, rage::joaat("ROCKET_BOOST"));
				sub->draw_option<submenu>("Jump Force", nullptr, rage::joaat("JUNPFORCE"));
				sub->draw_option<submenu>("Bike Lean", nullptr, rage::joaat("BIKE_LEAN"));
				sub->draw_option<submenu>("Doors", nullptr, rage::joaat("DOORS"));
				//sub->draw_option<submenu>("Cargobob", nullptr, rage::joaat("CARGO_BOB"));
				sub->draw_option<toggle<bool>>(("Godmode"), "Prevents your vehicle from taking damage.", &features.vehicle_godmode, BoolDisplay::OnOff, false, [] {
					if (!features.vehicle_godmode) {
						if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
						{
							Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
							ENTITY::SET_ENTITY_INVINCIBLE(playerVehicle, false);
							ENTITY::SET_ENTITY_PROOFS(playerVehicle, false, false, false, false, false, false, false, false);
							VEHICLE::SET_VEHICLE_DAMAGE(playerVehicle, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, false);
							//VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(playerVehicle);
							//VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVehicle, 0.0f);
							VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(playerVehicle, false);
							VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(playerVehicle, false);
							VEHICLE::SET_VEHICLE_BODY_HEALTH(playerVehicle, 1000.0f);
							VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(playerVehicle, !false);
							VEHICLE::SET_VEHICLE_CAN_BREAK(playerVehicle, !false);
							VEHICLE::SET_VEHICLE_ENGINE_HEALTH(playerVehicle, 1000.0f);
							VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(playerVehicle, !false);
							VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(playerVehicle, !false);
							VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(playerVehicle, 1000.0f);
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVehicle, !false);
							VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(playerVehicle, !false);

							//cool
						}
					}
					});
				sub->draw_option<toggle<bool>>(("Keep Engine On"), "Prevents your vehicle's engine from being turned off when exiting.", &features.keep_engine_on, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Infinite Countermeasures"), "", &features.inf_c, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("No Plane Turbulence"), "Removes your plane's turbulance. When turning off, it can make turbulance levels a little messed up.", &NoPlaneTurbulance, BoolDisplay::OnOff);
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>(auto_repair.name, "Automaticly repairs you're vehicle.", &features.auto_repair, &features.auto_repair_type, &features.get_repair_type);
				sub->draw_option<toggle<bool>>(("Can Be Used By Fleeing Peds"), nullptr, &features.can_be_used_by_peds, BoolDisplay::OnOff, false, [] {
					if (!features.can_be_used_by_peds) {
						VEHICLE::SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
					}
					});
				sub->draw_option<toggle<bool>>(("Remove Deformation"), "Removes deformation from you're vehicle.", &features.remove_def, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Stick To Ground"), "Creates a weird wheel effect, and makes it so you're vehicle stays on the ground.", &features.stick_to_ground, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Burned"), "Displays you're vehicle as destroyed like you blew it up.", &features.burned, BoolDisplay::OnOff, false, [] {
					if (!features.burned) {
						ENTITY::SET_ENTITY_RENDER_SCORCHED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
					}
					});

				sub->draw_option<toggle<bool>>(("Bypass Max Speed"), "Allows you to exceed the maximum speed limit your current vehicle.", &m_vehicle.bypass_max_speed.enabled, BoolDisplay::OnOff, false, [] {
					if (!m_vehicle.bypass_max_speed.enabled) {
						m_vehicle.bypass_max_speed.disable(); //trying something new
					}
					});
				sub->draw_option<toggle<bool>>(("Disable Lock-On"), "Disables other players & entities from locking on to you're vehicle.", &features.disable_lock_on, BoolDisplay::OnOff, false, [] {
					if (!features.disable_lock_on) {
						auto g_local_player = (*g_GameFunctions->m_pedFactory)->m_local_ped;
						if (g_local_player && g_local_player->m_vehicle)
							g_local_player->m_vehicle->m_is_targetable = true;
					}
					});
				sub->draw_option<toggle<bool>>(("Disable Camber"), nullptr, &features.disable_camber, BoolDisplay::OnOff, false, [] {
					if (!features.disable_camber) {
						VEHICLE::SET_CAN_USE_HYDRAULICS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
					}
					});
				sub->draw_option<toggle<bool>>(("Force Skidmarks"), nullptr, &features.show_skidmarks, BoolDisplay::OnOff, false, [] {
					if (!features.show_skidmarks) {
						GRAPHICS::USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(false);
					}
					});
				sub->draw_option<toggle<bool>>(("No Gravity"), nullptr, &features.no_grav_veh, BoolDisplay::OnOff, false, [] {
					if (!features.no_grav_veh) {
						VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
					}
					});
				sub->draw_option<toggle<bool>>(("Auto Clean"), "", &features.clean_veh, BoolDisplay::OnOff);
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
					sub->draw_option<KeyboardOption>(("Liscene Plate"), nullptr, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true)), []
						{

							showKeyboard("Enter Something", "", 8, &Bufferfrrrr, [=] {
								VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), Bufferfrrrr.c_str());
								});
						});
				}
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Upgrades", nullptr, &m_upgrades.types, &m_upgrades.data, false, SubmenuMaxThatFucker, [] {

					m_upgrades.apply(m_upgrades.data);
					});
				sub->draw_option<number<float>>("Forklift Height", nullptr, &features.forklight_height, 0.0f, 1.f, 0.1f, 2, true, "", "", [=] {
					VEHICLE::SET_FORKLIFT_FORK_HEIGHT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), features.forklight_height);
					});

			});
		g_Render->draw_submenu<sub>(("Jump Force"), rage::joaat("JUNPFORCE"), [](sub* sub)
			{
				sub->draw_option<submenu>("Compatible Vehicles", nullptr, rage::joaat("COMPVEHICLES2"));
				sub->draw_option<toggle<bool>>(("Increase"), "", &jump_force.increase, BoolDisplay::OnOff, false, [] {
					if (!jump_force.increase) {
						VEHICLE::SET_USE_HIGHER_CAR_JUMP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
					}
					});
			});
		g_Render->draw_submenu<sub>(("Compatible Vehicles"), rage::joaat("COMPVEHICLES2"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Action", nullptr, &jump_force.action, &jump_force.pos);
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});

				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("ruiner2")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("ruiner2"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("scramjet")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("scramjet"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("scarab")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("scarab"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("monster3")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("monster3"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("slamvan4")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("slamvan4"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("issi4")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("issi4"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("imperator")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("imperator"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("dominator4")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("dominator4"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("deathbike")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("deathbike"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("cerberus")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("cerberus"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("brutus")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("brutus"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("bruiser")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("bruiser"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("zr380")))), nullptr, [=]
					{
						if (jump_force.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("zr380"), &veh);
						}

					});
			});
		g_Render->draw_submenu<sub>(("Cargobob"), rage::joaat("CARGO_BOB"), [](sub* sub)
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				sub->draw_option<toggle<bool>>(("Magnet"), nullptr, &cargobob.magnet, BoolDisplay::OnOff, false, [=] {
					if (!cargobob.magnet) {
						VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(veh, false);

					}
					});
				sub->draw_option<number<float>>("Strength", nullptr, &cargobob.strength, 0.0f, 1000.f, 1.f, 0, true, "", "", [=] {
					VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(veh, cargobob.strength);
					});
				sub->draw_option<number<float>>("Effect Radius", nullptr, &cargobob.eraidus, 0.0f, 1000.f, 1.f, 0, true, "", "", [=] {
					VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_FALLOFF(veh, cargobob.eraidus);
					});
				sub->draw_option<number<float>>("Falloff", nullptr, &cargobob.falloff, 0.0f, 1000.f, 1.f, 0, true, "", "", [=] {
					VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_PULL_ROPE_LENGTH(veh, cargobob.falloff);
					});
				sub->draw_option<RegularOption>("Detach Current Vehicle From Magnet", nullptr, [=]
					{
						Vehicle get = VEHICLE::GET_VEHICLE_ATTACHED_TO_CARGOBOB(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
						VEHICLE::DETACH_VEHICLE_FROM_CARGOBOB(get, PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));

					});
			});
		g_Render->draw_submenu<sub>(("Bike Lean"), rage::joaat("BIKE_LEAN"), [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("X", nullptr, &bike_lean, -1, 1, 1, 3, true, "", "", [] {
					VEHICLE::SET_BIKE_ON_STAND(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), bike_lean, bike_lean2);
					});
				sub->draw_option<number<std::int32_t>>("Y", nullptr, &bike_lean2, -1, 1, 1, 3, true, "", "", [] {
					VEHICLE::SET_BIKE_ON_STAND(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), bike_lean, bike_lean2);
					});
			});
		g_Render->draw_submenu<sub>(("Doors"), rage::joaat("DOORS"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Action", nullptr, &doors.action, &doors.pos);
				sub->draw_option<RegularOption>("Driver Side (Front)", nullptr, [=]
					{
						if (doors.pos == 0) {
							VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0, true, false);
						}
						if (doors.pos == 1) {
							VEHICLE::SET_VEHICLE_DOOR_SHUT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0, false);
						}
						if (doors.pos == 2) {
							VEHICLE::SET_VEHICLE_DOOR_BROKEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0, true);
						}

					});
				if (VEHICLE::GET_IS_DOOR_VALID(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1)) {
					sub->draw_option<RegularOption>("Driver Side (Rear)", nullptr, [=]
						{
							if (doors.pos == 0) {
								VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, false, false);
							}
							if (doors.pos == 1) {
								VEHICLE::SET_VEHICLE_DOOR_SHUT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, false);
							}
							if (doors.pos == 2) {
								VEHICLE::SET_VEHICLE_DOOR_BROKEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, true);
							}

						});
				}
				if (VEHICLE::GET_IS_DOOR_VALID(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2)) {
					sub->draw_option<RegularOption>("Passenger Side (Front)", nullptr, [=]
						{
							if (doors.pos == 0) {
								VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2, false, false);
							}
							if (doors.pos == 1) {
								VEHICLE::SET_VEHICLE_DOOR_SHUT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2, false);
							}
							if (doors.pos == 2) {
								VEHICLE::SET_VEHICLE_DOOR_BROKEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2, true);
							}

						});
				}
				if (VEHICLE::GET_IS_DOOR_VALID(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 3)) {
					sub->draw_option<RegularOption>("Passenger Side (Rear)", nullptr, [=]
						{
							if (doors.pos == 0) {
								VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 3, false, false);
							}
							if (doors.pos == 1) {
								VEHICLE::SET_VEHICLE_DOOR_SHUT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 3, false);
							}
							if (doors.pos == 2) {
								VEHICLE::SET_VEHICLE_DOOR_BROKEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 3, true);
							}

						});
				}
				if (VEHICLE::GET_IS_DOOR_VALID(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 4)) {
					sub->draw_option<RegularOption>("Hood", nullptr, [=]
						{
							if (doors.pos == 0) {
								VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 4, false, false);
							}
							if (doors.pos == 1) {
								VEHICLE::SET_VEHICLE_DOOR_SHUT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 4, false);
							}
							if (doors.pos == 2) {
								VEHICLE::SET_VEHICLE_DOOR_BROKEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 4, true);
							}

						});
				}
				sub->draw_option<UnclickOption>(("Bomb Bay"), nullptr, [] {});
				sub->draw_option<RegularOption>("Open", nullptr, [=]
					{
						VEHICLE::OPEN_BOMB_BAY_DOORS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));

					});
				sub->draw_option<RegularOption>("Close", nullptr, [=]
					{
						VEHICLE::CLOSE_BOMB_BAY_DOORS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));

					});
			});
		g_Render->draw_submenu<sub>(("Rocket Boost"), rage::joaat("ROCKET_BOOST"), [](sub* sub)
			{
				sub->draw_option<submenu>("Compatible Vehicles", nullptr, rage::joaat("COMP_VEHICLES"));
				sub->draw_option<toggle<bool>>(("Infinite"), "Instantly refills your vehicle's rocket boost.", &features.infiniter, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Always Active"), "", &rocket_boost.always_active, BoolDisplay::OnOff);
				sub->draw_option<number<float>>("Percentage", nullptr, &rocket_boost.percentage, 0.0f, 100.f, 1.f, 0, true, "", "", [] {
					VEHICLE::SET_ROCKET_BOOST_FILL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), rocket_boost.percentage);
					});
				sub->draw_option<number<float>>("Refill Time", nullptr, &rocket_boost.refill_time, 0.0f, 1000.f, 1.f, 0, true, "", "", [] {
					VEHICLE::SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), rocket_boost.refill_time);
					});
			});
		g_Render->draw_submenu<sub>(("Compatible Vehicles"), rage::joaat("COMP_VEHICLES"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Action", nullptr, &rocket_boost.action, &rocket_boost.pos);
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});

				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("voltic2")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("voltic2"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("vigilante")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("vigilante"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("oppressor")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("oppressor"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("oppressor2")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("oppressor2"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("toreador")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("toreador"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("scramjet")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("scramjet"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("scarab")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("scarab"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("monster3")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("monster3"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("slamvan4")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("slamvan4"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("issi4")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("issi4"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("imperator")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("imperator"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("dominator4")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("dominator4"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("deathbike")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("deathbike"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("cerberus")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("cerberus"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("brutus")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("brutus"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("bruiser")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("bruiser"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("zr380")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("zr380"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("starling")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("starling"), &veh);
						}

					});
				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("thruster")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("thruster"), &veh);
						}

					});

				sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY("tula")))), nullptr, [=]
					{
						if (rocket_boost.pos == 1) {
							Vehicle veh;
							veh_spawner.spawn(MISC::GET_HASH_KEY("tula"), &veh);
						}

					});
			});
		g_Render->draw_submenu<sub>(("Forge Model"), rage::joaat("ForgeModel"), [](sub* sub)
			{
				for (std::int32_t i = 0; i < 23; i++) {
					sub->draw_option<submenu>(get_vehicle_class_name(i), nullptr, rage::joaat("GetClass"), [=]
						{
							forge_model.selected_class = i;
						});

				}
			});
		g_Render->draw_submenu<sub>((get_vehicle_class_name(forge_model.selected_class)), rage::joaat("GetClass"), [](sub* sub)
			{
				if (g_GameFunctions->m_vehicle_hash_pool != nullptr) {
					for (std::int32_t i = 0; i < g_GameFunctions->m_vehicle_hash_pool->capacity; i++) {
						std::uint64_t info = g_GameFunctions->m_vehicle_hash_pool->get(i);
						if (info != NULL) {
							if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
								std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
								std::string model_ptr = (char*)((uintptr_t)info + 0x298);
								if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(MISC::GET_HASH_KEY(model_ptr.c_str())) == forge_model.selected_class) {
									std::stringstream ss;
									std::string make(make_ptr);
									std::string model(model_ptr);
									if (make[0] || model[0]) {
										make = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(make.c_str());
										model = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model.c_str());
										if (make != "NULL" && model != "NULL") {
											ss << make << " " << model;
										}
										else if (model != "NULL") {
											ss << model;
										}
										else {
											ss << "Unknown";
										}
									}
									if (sub->GetSelectedOption() == sub->GetNumOptions()) {
										g_players.draw_info2(*(std::uint32_t*)(info + 0x18));
									}

									sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(*(std::uint32_t*)(info + 0x18)))), nullptr, [=]
										{
											if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
												forge_model.change(*(std::uint32_t*)(info + 0x18));
												Noti::InsertNotification({ ImGuiToastType_None, 4000, ICON_FA_CHECK"  Done!" });
											}

										});
								}
							}
						}
					}
				}
			});
		g_Render->draw_submenu<sub>(("Personal"), SubmenuPersonalVehicle, [](sub* sub)
			{
				sub->draw_option<submenu>("Garage", nullptr, Submenu::SubmenuPersonalVehicles);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Teleport To You", nullptr, &personal_vehicle.type, &personal_vehicle.size, false, -1, [] {

					if (personal_vehicle.size == 0) {
						Vehicle veh = personal_vehicle.get();
						NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(veh, coords.x, coords.y, coords.z, false, false, false);

					}
					if (personal_vehicle.size == 1) {
						Vehicle veh = personal_vehicle.get();
						NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(veh, coords.x, coords.y, coords.z, false, false, false);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
					}

					});
				sub->draw_option<RegularOption>(("Despawn"), nullptr, [=]
					{
						int get_current_personal_vehicle = *script_global(2359296).at(0, 5568).at(681).at(2).as<int*>();

						m_GetBits.clear_bits(vehicle_global.at(get_current_personal_vehicle, 142).at(103).as<int*>(), eVehicleFlags::TRIGGER_SPAWN_TOGGLE);

					});

			});
		g_Render->draw_submenu<sub>(("Garage"), SubmenuPersonalVehicles, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Fix All"), nullptr, [=]
					{
						personal_vehicle.fix_all();

					});
			});
		g_Render->draw_submenu<sub>(("Invisible"), SubmenuVehicleInvis, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &features.invisible_car, BoolDisplay::OnOff, false, [] {
					if (!features.invisible_car) {
						ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true, false);

					}
					});
				sub->draw_option<toggle<bool>>(("Locally Visible"), nullptr, &features.invisible_carlocal_visible, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Parachute"), SubmenuParachute, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &features.invisible_carlocal_visible, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Particles"), SubmenuVehParticles, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Particle", nullptr, &m_fx.type, &m_fx.size);
				sub->draw_option<number<float>>("Scale", nullptr, &m_fx.vscale, 0.01f, 1000.f, 0.05f, 2);
				sub->draw_option<UnclickOption>(("Bones"), nullptr, [] {});
				sub->draw_option<toggle<bool>>(("Front Left Wheel"), nullptr, &m_fx.lf, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Back Left Wheel"), nullptr, &m_fx.bl5, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Front Right Wheel"), nullptr, &m_fx.fr5, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Back Right Wheel"), nullptr, &m_fx.br, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Exaust"), nullptr, &m_fx.exaust2, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Spoiler"), nullptr, &m_fx.spoilerr, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Brakelight Left"), nullptr, &m_fx.brakele, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Brakelight Right"), nullptr, &m_fx.brakerig, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Tail Light Left"), nullptr, &m_fx.taill, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Tail Light Right"), nullptr, &m_fx.tailr, BoolDisplay::OnOff);
				//sub->draw_option<toggle<bool>>(("Gas Cap"), nullptr, &m_fx.gas_cap, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Ramps"), SubmenuVehicleRamps, [](sub* sub)
			{
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Transparent", nullptr, &m_vehicle_ramps.m_is_trasparent, &m_vehicle_ramps.m_ramp_trasparency, &m_vehicle_ramps.m_ramp_transparency_data, false, [] {
					if (!m_vehicle_ramps.m_is_trasparent) {
						if (ENTITY::DOES_ENTITY_EXIST(m_vehicle_ramps.m_ramp_location.back)) {
							ENTITY::SET_ENTITY_ALPHA(m_vehicle_ramps.m_ramp_location.back, 255, false);

						}
						if (ENTITY::DOES_ENTITY_EXIST(m_vehicle_ramps.m_ramp_location.front)) {
							ENTITY::SET_ENTITY_ALPHA(m_vehicle_ramps.m_ramp_location.front, 255, false);

						}
						if (ENTITY::DOES_ENTITY_EXIST(m_vehicle_ramps.m_ramp_location.left)) {
							ENTITY::SET_ENTITY_ALPHA(m_vehicle_ramps.m_ramp_location.left, 255, false);

						}
						if (ENTITY::DOES_ENTITY_EXIST(m_vehicle_ramps.m_ramp_location.right)) {
							ENTITY::SET_ENTITY_ALPHA(m_vehicle_ramps.m_ramp_location.right, 255, false);

						}
					}
					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Model", nullptr, &m_vehicle_ramps.m_ramp_type, &m_vehicle_ramps.m_ramp_type_data);
				sub->draw_option<toggle<bool>>(("Front"), nullptr, &m_vehicle_ramps.m_ramp_location.m_front, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Back"), nullptr, &m_vehicle_ramps.m_ramp_location.m_back, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Left"), nullptr, &m_vehicle_ramps.m_ramp_location.m_left, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Right"), nullptr, &m_vehicle_ramps.m_ramp_location.m_right, BoolDisplay::OnOff);
				sub->draw_option<RegularOption>(("Build"), nullptr, [=]
					{
						m_vehicle_ramps.m_add_ramp();

					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Remove", nullptr, &m_vehicle_ramps.m_remove_type, &m_vehicle_ramps.m_remove_data, false, -1, [] {
					switch (m_vehicle_ramps.m_remove_data) {
					case 0:
						m_vehicle_ramps.m_remove();
						break;
					case 1:
						Hash ramp = MISC::GET_HASH_KEY("prop_mp_ramp_01");
						Hash ramp2 = MISC::GET_HASH_KEY("lts_prop_lts_ramp_02");
						Hash ramp3 = MISC::GET_HASH_KEY("lts_prop_lts_ramp_03");


						NativeVector3 pedpos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
						Object ObjToDelete = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pedpos.x, pedpos.y, pedpos.z, 10.f, ramp, 0, 1, 1);
						OBJECT::DELETE_OBJECT(&ObjToDelete);
						Object ObjToDelete2 = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pedpos.x, pedpos.y, pedpos.z, 10.f, ramp2, 0, 1, 1);
						OBJECT::DELETE_OBJECT(&ObjToDelete2);
						Object ObjToDelete3 = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pedpos.x, pedpos.y, pedpos.z, 10.f, ramp3, 0, 1, 1);
						OBJECT::DELETE_OBJECT(&ObjToDelete3);

					}
					});
			});
		g_Render->draw_submenu<sub>(("Color"), SubmenuChangeVehicleColor, [](sub* sub)
			{
				sub->draw_option<submenu>("Rainbow", nullptr, Submenu::SubmenuRaimbow);
				sub->draw_option<number<std::int32_t>>("R", nullptr, &changeVehicleColor.r, 0, 255, 1, 3, true, "", "", [] {
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), changeVehicleColor.r, changeVehicleColor.g, changeVehicleColor.b);
					});
				sub->draw_option<number<std::int32_t>>("G", nullptr, &changeVehicleColor.g, 0, 255, 1, 3, true, "", "", [] {
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), changeVehicleColor.r, changeVehicleColor.g, changeVehicleColor.b);
					});
				sub->draw_option<number<std::int32_t>>("B", nullptr, &changeVehicleColor.b, 0, 255, 1, 3, true, "", "", [] {
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), changeVehicleColor.r, changeVehicleColor.g, changeVehicleColor.b);
					});





			});
		g_Render->draw_submenu<sub>(("Rainbow"), SubmenuRaimbow, [](sub* sub)
			{

				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &changeVehicleColor.rainbow.enabled, BoolDisplay::OnOff, false, [] {
					changeVehicleColor.r = 255;

					});
				sub->draw_option<toggle<bool>>(("Secondary"), nullptr, &changeVehicleColor.rainbow.change_secondary, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Underglow"), nullptr, &changeVehicleColor.rainbow.underglow, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Tyre Smoke"), nullptr, &changeVehicleColor.rainbow.tyre_smoke, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &changeVehicleColor.rainbow.delay, rainbow_delay.min, rainbow_delay.max, rainbow_delay.step);



			});
		g_Render->draw_submenu<sub>(("Spawner"), SubmenuVehicleSpawner, [](sub* sub)
			{

				sub->draw_option<submenu>("Settings", nullptr, Submenu::SpawnerSettings);
				sub->draw_option<submenu>("Search", nullptr, Submenu::SubmenuVehicleSearch);
				sub->draw_option<submenu>("Saved", nullptr, Submenu::SubmenuSavedVehicles);
				sub->draw_option<submenu>("Spawned", nullptr, rage::joaat("Spawned"));
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				sub->draw_option<submenu>("All", nullptr, SubmenuVehicleAll);
				for (std::int32_t i = 0; i < 23; i++) {
					sub->draw_option<submenu>(get_vehicle_class_name(i), nullptr, SubmenuGetClass, [=]
						{
							m_selected_vehicle_class = i;
						});

				}


			});
		g_Render->draw_submenu<sub>(("Spawned"), rage::joaat("Spawned"), [](sub* sub)
			{
				for (auto& model : spawned_veh.spawned) {
					sub->draw_option<submenu>(model.m_name.c_str(), nullptr, rage::joaat("Fortniteeee"), [=]
						{
							spawned_veh.selectedveh = model.m_id;
							spawned_veh.seletedname = model.m_name.c_str();
						});

				}
			});
		g_Render->draw_submenu<sub>("Spawned", rage::joaat("Fortniteeee"), [](sub* sub)
			{
				for (auto& model : spawned_veh.spawned) {
					if (spawned_veh.selectedveh == model.m_id) {
						sub->draw_option<RegularOption>("Teleport To You", nullptr, [=]
							{

								NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
								ENTITY::SET_ENTITY_COORDS(model.m_id, coords.x, coords.y, coords.z, 0, 0, 0, 0);

							});
					}
				}


			});
		g_Render->draw_submenu<sub>(("Saved"), SubmenuSavedVehicles, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Save"), nullptr, []
					{
						if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
							showKeyboard("Enter Something", "", 25, &VehNameBuffer, [] {
								m_VehicleLoad.save(VehNameBuffer);
								});
						}
					});
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				if (std::filesystem::exists("C:\\Saint\\Vehicles\\") && std::filesystem::is_directory("C:\\Saint\\Vehicles\\")) {
					namespace fs = std::filesystem;
					fs::directory_iterator dirIt{ "C:\\Saint\\Vehicles\\" };
					for (auto&& dirEntry : dirIt)
					{
						if (dirEntry.is_regular_file())
						{
							auto path = dirEntry.path();
							if (path.has_filename())
							{
								if (path.extension() == ".ini")
								{
									OutfitList();
									char nigger[64];
									sprintf(nigger, "%s", path.stem().u8string().c_str());
									sub->draw_option<RegularOption>(nigger, nullptr, [=]
										{
											m_VehicleLoad.load(nigger);
										});

								}

							}
						}
					}
				}
				else {
					if (std::filesystem::create_directory("C:\\Saint\\Vehicles\\")) {

					}
					else {
						std::filesystem::create_directory("C:\\Saint\\Vehicles\\");
					}
				}


			});
		g_Render->draw_submenu<sub>(("All"), SubmenuVehicleAll, [](sub* sub)
			{
				if (g_GameFunctions->m_vehicle_hash_pool != nullptr) {
					for (std::int32_t i = 0; i < g_GameFunctions->m_vehicle_hash_pool->capacity; i++) {
						std::uint64_t info = g_GameFunctions->m_vehicle_hash_pool->get(i);
						if (info != NULL) {
							if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
								std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
								std::string model_ptr = (char*)((uintptr_t)info + 0x298);
								std::stringstream ss;
								std::string make(make_ptr);
								std::string model(model_ptr);
								if (make[0] || model[0]) {
									make = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(make.c_str());
									model = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model.c_str());
									if (make != "NULL" && model != "NULL") {
										ss << make << " " << model;
									}
									else if (model != "NULL") {
										ss << model;
									}
									else {
										ss << "Unknown";
									}
								}

								sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(*(std::uint32_t*)(info + 0x18)))), nullptr, [=]
									{
										Vehicle veh;
										veh_spawner.spawn(*(std::uint32_t*)(info + 0x18), &veh);

									});

							}
						}
					}
				}

			});
		g_Render->draw_submenu<sub>(("Settings"), SpawnerSettings, [](sub* sub)
			{
				sub->draw_option<submenu>("Color", nullptr, Submenu::SpawnerSettingsColor);
				sub->draw_option<submenu>("Forward Speed", nullptr, Submenu::SpawnerSettingsSetForwardSpeed);
				sub->draw_option<submenu>("Spawn In Air", nullptr, Submenu::SpawnerSettingsSpawnInAir);
				sub->draw_option<toggle<bool>>(("Set Engine On"), nullptr, &veh_spawner.setengineon, BoolDisplay::OnOff);
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Fade", nullptr, &veh_spawner.fade_in, &veh_spawner.fade_speed, &veh_spawner.fade_speed_i);
				sub->draw_option<toggle<bool>>(("Spawn Into"), nullptr, &veh_spawner.spawn_in, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Delete Last"), nullptr, &veh_spawner.dellast, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Max"), nullptr, &veh_spawner.max, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Color"), SpawnerSettingsColor, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &veh_spawner.spawnwithcolor, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("R (Primary)", nullptr, &veh_spawner.spawnr, 0, 255);
				sub->draw_option<number<std::int32_t>>("G (Primary) ", nullptr, &veh_spawner.spawng, 0, 255);
				sub->draw_option<number<std::int32_t>>("B (Primary)", nullptr, &veh_spawner.spawnb, 0, 255);
				sub->draw_option<number<std::int32_t>>("R (Secondary)", nullptr, &veh_spawner.spawnr2, 0, 255);
				sub->draw_option<number<std::int32_t>>("G (Secondary)", nullptr, &veh_spawner.spawng2, 0, 255);
				sub->draw_option<number<std::int32_t>>("B (Secondary)", nullptr, &veh_spawner.spawnb2, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Forward Speed"), SpawnerSettingsSetForwardSpeed, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &veh_spawner.forward_speed, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Speed", nullptr, &veh_spawner.forwardspeedmutli, 0, 1000);

			});
		g_Render->draw_submenu<sub>(("Spawn In Air"), SpawnerSettingsSpawnInAir, [](sub* sub)
			{

				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &veh_spawner.spawninair, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Height", nullptr, &veh_spawner.heightmulti, 0, 1000);

			});
		g_Render->draw_submenu<sub>((get_vehicle_class_name(m_selected_vehicle_class)), SubmenuGetClass, [](sub* sub)
			{
				if (g_GameFunctions->m_vehicle_hash_pool != nullptr) {
					for (std::int32_t i = 0; i < g_GameFunctions->m_vehicle_hash_pool->capacity; i++) {
						std::uint64_t info = g_GameFunctions->m_vehicle_hash_pool->get(i);
						if (info != NULL) {
							if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
								std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
								std::string model_ptr = (char*)((uintptr_t)info + 0x298);
								if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(MISC::GET_HASH_KEY(model_ptr.c_str())) == m_selected_vehicle_class) {
									std::stringstream ss;
									std::string make(make_ptr);
									std::string model(model_ptr);
									if (make[0] || model[0]) {
										make = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(make.c_str());
										model = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model.c_str());
										if (make != "NULL" && model != "NULL") {
											ss << make << " " << model;
										}
										else if (model != "NULL") {
											ss << model;
										}
										else {
											ss << "Unknown";
										}
									}
									if (sub->GetSelectedOption() == sub->GetNumOptions()) {
										g_players.draw_info2(*(std::uint32_t*)(info + 0x18));
									}

									sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(*(std::uint32_t*)(info + 0x18)))), nullptr, [=]
										{
											Vehicle veh;
											veh_spawner.spawn(*(std::uint32_t*)(info + 0x18), &veh);

										});
								}
							}
						}
					}
				}
			});
		g_Render->draw_submenu<sub>(("Search"), SubmenuVehicleSearch, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Click Here"), nullptr, []
					{

						showKeyboard("Enter Something", "", 25, &ModelInput, [] {
							search_completed = true;
							});
					});
				if (search_completed) {
					Hash vehicleHash2 = MISC::GET_HASH_KEY(ModelInput.c_str());
					if (STREAMING::IS_MODEL_VALID(vehicleHash2)) {
						sub->draw_option<UnclickOption>(("Found ~r~1 ~w~Result."), nullptr, [] {});
					}
					else {
						sub->draw_option<UnclickOption>(("Found ~r~0 ~w~Results."), nullptr, [] {});
					}

					if (STREAMING::IS_MODEL_VALID(vehicleHash2)) {

						STREAMING::REQUEST_MODEL(vehicleHash2);
						if (!STREAMING::HAS_MODEL_LOADED(vehicleHash2)) {


						}
						else {



							sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehicleHash2))), nullptr, [=]
								{
									NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
									*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
									Vehicle vehicle = VEHICLE::CREATE_VEHICLE(vehicleHash2, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(g_SelectedPlayer), true, false, false);
									*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
									DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
									auto networkId = NETWORK::VEH_TO_NET(vehicle);
									if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
										NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
									VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
									PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);

								});


						}
					}
				}

			});
		g_Render->draw_submenu<sub>(("Max (Once)"), SubmenuMaxThatFucker, [](sub* sub)
			{

				for (std::uint32_t i = 0; i < 3; ++i) {
					sub->draw_option<RegularOption>((m_upgrades.types[i]), nullptr, [=]
						{

							m_upgrades.apply(i);


						});
				}




			});
		g_Render->draw_submenu<sub>(("Randomization"), SubmenuUpgrades, [](sub* sub)
			{
				sub->draw_option<submenu>("Upgrades", nullptr, Submenu::SubmenuUpgradeLoop);
				sub->draw_option<submenu>("Acrobatics", nullptr, rage::joaat("acrobaticsr"));
				

			});
		g_Render->draw_submenu<sub>(("Acrobatics"), rage::joaat("acrobaticsr"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &randomization.acrobatics, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &randomization.delay, 0, 5000, 50);
			});
		g_Render->draw_submenu<sub>(("Upgrades"), SubmenuUpgradeLoop, [](sub* sub)
			{
				sub->draw_option<submenu>("Color", nullptr, Submenu::SubmenuSelectedVehicleColor);
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &max_loop.enabled, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &max_loop.delay, 0, 5000, 50);
			});
		g_Render->draw_submenu<sub>(("Upgrades"), SubmenuUpgradeLoop, [](sub* sub)
			{
				sub->draw_option<submenu>("Color", nullptr, Submenu::SubmenuSelectedVehicleColor);
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &max_loop.enabled, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &max_loop.delay, 0, 5000, 50);
			});
		g_Render->draw_submenu<sub>(("Color"), SubmenuSelectedVehicleColor, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Primary"), nullptr, &max_loop.randomizeprimary, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Secondary"), nullptr, &max_loop.randomizesecondary, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Auto-Pilot"), SubmenuAutoPilot, [](sub* sub)
			{
				sub->draw_option<submenu>("Flag Creator", nullptr, SubmenuFlagCreator);
				sub->draw_option<toggle<bool>>(("Reckless"), nullptr, &autopilot.wreckless, BoolDisplay::OnOff);
				if (autopilot.wreckless) {
					sub->draw_option<toggle<bool>>((autopilot.avoid_roads_name.c_str()), nullptr, &autopilot.avoid_roads, BoolDisplay::OnOff);
				}
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Destination", nullptr, &autopilot.destination, &autopilot.destination_i);
				sub->draw_option<number<float>>("Speed", nullptr, &autopilot.speed, 1.0f, 200.f, 1.0f, 2);
				sub->draw_option<number<float>>("Stop Range", nullptr, &autopilot.stop_range, 0.f, 1000.f, 0.50f, 2);
				sub->draw_option<RegularOption>(("Start"), nullptr, []
					{

						int WaypointHandle = HUD::GET_FIRST_BLIP_INFO_ID(8);
						NativeVector3 destination = HUD::GET_BLIP_INFO_ID_COORD(HUD::GET_FIRST_BLIP_INFO_ID(8));
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						if (autopilot.destination_i == 0) {
							PED::SET_DRIVER_ABILITY(PLAYER::PLAYER_PED_ID(), 100.f);
							TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(PLAYER::PLAYER_PED_ID(), veh, destination.x, destination.y, destination.z, autopilot.speed, autopilot.wreckless ? autopilot.wreckless_flag : autopilot.nonwreckless_flag, autopilot.stop_range);

						}
						if (autopilot.destination_i == 1) {
							NativeVector3 location;

							get_objective_location(location);
							if (autopilot.wreckless) {
								PED::SET_DRIVER_ABILITY(PLAYER::PLAYER_PED_ID(), 100.f);
								TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(PLAYER::PLAYER_PED_ID(), veh, location.x, location.y, location.z, autopilot.speed, autopilot.avoid_roads ? autopilot.avoid_roads_flag : autopilot.wreckless_flag, autopilot.stop_range);

							}
							else {
								TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(PLAYER::PLAYER_PED_ID(), veh, location.x, location.y, location.z, autopilot.speed, autopilot.nonwreckless_flag, autopilot.stop_range);
							}
						}
						if (autopilot.destination_i == 2) {

							if (autopilot.wreckless) {

								PED::SET_DRIVER_ABILITY(PLAYER::PLAYER_PED_ID(), 100.f);
								TASK::TASK_VEHICLE_DRIVE_WANDER(PLAYER::PLAYER_PED_ID(), veh, autopilot.speed, autopilot.avoid_roads ? autopilot.avoid_roads_flag : autopilot.wreckless_flag);

							}
							else {
								TASK::TASK_VEHICLE_DRIVE_WANDER(PLAYER::PLAYER_PED_ID(), veh, autopilot.speed, autopilot.nonwreckless_flag);

							}
						}
					});
				sub->draw_option<RegularOption>(("Stop"), nullptr, []
					{
						Vehicle oldveh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), oldveh, -1);

					});
				sub->draw_option<UnclickOption>(("Current Flags"), nullptr, [] {});
				char wreckless[64];
				sprintf(wreckless, "%i", autopilot.wreckless_flag);
				sub->draw_option<KeyboardOption>(("Reckless"), nullptr, wreckless, []
					{
						showKeyboard("Enter Something", "", 25, &autopilot.wreckless_buffer, [] {
							autopilot.wreckless_flag = atoi(autopilot.wreckless_buffer.c_str());
							});



					});
				char nonwreckless[64];
				sprintf(nonwreckless, "%i", autopilot.nonwreckless_flag);
				sub->draw_option<KeyboardOption>(("Non-Reckless"), nullptr, nonwreckless, []
					{
						showKeyboard("Enter Something", "", 25, &autopilot.nonwreckless_flag_buffer, [] {
							autopilot.nonwreckless_flag = atoi(autopilot.nonwreckless_flag_buffer.c_str());
							});



					});
				char nonwreckless2[64];
				sprintf(nonwreckless2, "%i", autopilot.avoid_roads_flag);
				sub->draw_option<KeyboardOption>((autopilot.avoid_roads_name.c_str()), nullptr, nonwreckless2, []
					{
						showKeyboard("Enter Something", "", 25, &autopilot.avoid_roads_buffer, [] {
							autopilot.avoid_roads_flag = atoi(autopilot.avoid_roads_buffer.c_str());
							});



					});

			});

		g_Render->draw_submenu<sub>(("Flag Creator"), SubmenuFlagCreator, [](sub* sub)
			{
				sub->draw_option<submenu>("Flags", nullptr, SubmenuCustomFlags);



				sub->draw_option<toggle<bool>>(("Automaticly Save"), nullptr, &flag_creator.auto_save, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Save", nullptr, &flag_creator.direction, &flag_creator.data, false, -1, []
					{
						m_queue.add(2s, "Saving...", [] {
							switch (flag_creator.data) {
							case 0:
								autopilot.wreckless_flag = flag_creator.current;
								break;
							case 1:
								autopilot.nonwreckless_flag = flag_creator.current;
								break;
							case 2:
								autopilot.avoid_roads_flag = flag_creator.current;
								break;
							}
							});


					});
				sub->draw_option<UnclickOption>(("Current"), nullptr, [] {});
				char current[64];
				sprintf(current, "%i", flag_creator.current);
				sub->draw_option<RegularOption>((current), "", []
					{


					});
				sub->draw_option<UnclickOption>(("Names"), nullptr, [] {});

				sub->draw_option<KeyboardOption>(("Slot 3"), nullptr, autopilot.avoid_roads_name.c_str(), []
					{
						showKeyboard("Enter Something", "", 25, &autopilot.avoid_roads_name, [] {});



					});



			});
		g_Render->draw_submenu<sub>(("Flags"), SubmenuCustomFlags, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Stop Before Vehicles"), nullptr, &flag_creator.stop_before_vehicles, BoolDisplay::OnOff, false, [] {
					if (flag_creator.stop_before_vehicles) {
						flag_creator.current += 1;
					}
					if (!flag_creator.stop_before_vehicles) {
						flag_creator.current -= 1;
					}
					});
				sub->draw_option<toggle<bool>>(("Stop Before Peds"), nullptr, &flag_creator.stop_before_peds, BoolDisplay::OnOff, false, [] {
					if (flag_creator.stop_before_peds) {
						flag_creator.current += 2;
					}
					if (!flag_creator.stop_before_peds) {
						flag_creator.current -= 2;
					}
					});
				sub->draw_option<toggle<bool>>(("Avoid Vehicles"), nullptr, &flag_creator.avoid_vehicles, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.avoid_vehicles;
					if (buffer) {
						flag_creator.current += 4;
					}
					if (!buffer) {
						flag_creator.current -= 4;
					}
					});
				sub->draw_option<toggle<bool>>(("Avoid Empty Vehicles"), nullptr, &flag_creator.avoid_empty_vehicles, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.avoid_empty_vehicles;
					if (buffer) {
						flag_creator.current += 8;
					}
					if (!buffer) {
						flag_creator.current -= 8;
					}

					});
				sub->draw_option<toggle<bool>>(("Avoid Peds"), nullptr, &flag_creator.avoid_peds, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.avoid_peds;
					if (buffer) {
						flag_creator.current += 16;
					}
					if (!buffer) {
						flag_creator.current -= 16;
					}

					});
				sub->draw_option<toggle<bool>>(("Avoid Objects"), nullptr, &flag_creator.avoid_objects, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.avoid_objects;
					if (buffer) {
						flag_creator.current += 16 * 2;
					}
					if (!buffer) {
						flag_creator.current -= 16 * 2;
					}

					});
				sub->draw_option<toggle<bool>>(("Stop At Traffic Lights"), nullptr, &flag_creator.stop_at_traffic_lights, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.stop_at_traffic_lights;
					if (buffer) {
						flag_creator.current += 128;
					}
					if (!buffer) {
						flag_creator.current -= 128;
					}

					});
				sub->draw_option<toggle<bool>>(("Use Blinkers"), nullptr, &flag_creator.use_blinkers, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.use_blinkers;
					if (buffer) {
						flag_creator.current += 256;
					}
					if (!buffer) {
						flag_creator.current -= 256;
					}

					});
				sub->draw_option<toggle<bool>>(("Allow Going Wrong Way"), nullptr, &flag_creator.allow_going_wrong_way, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.allow_going_wrong_way;
					if (buffer) {
						flag_creator.current += 512;
					}
					if (!buffer) {
						flag_creator.current -= 512;
					}

					});
				sub->draw_option<toggle<bool>>(("Drive In Reverse"), nullptr, &flag_creator.drive_in_reverse, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.drive_in_reverse;
					if (buffer) {
						flag_creator.current += 1024;
					}
					if (!buffer) {
						flag_creator.current -= 1024;
					}

					});
				sub->draw_option<toggle<bool>>(("Take Shortest Path"), nullptr, &flag_creator.take_shortest_path, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.take_shortest_path;
					if (buffer) {
						flag_creator.current += 262144;
					}
					if (!buffer) {
						flag_creator.current -= 262144;
					}

					});
				sub->draw_option<toggle<bool>>(("Reckless"), nullptr, &flag_creator.wreckless, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.wreckless;
					if (buffer) {
						flag_creator.current += 524288;
					}
					if (!buffer) {
						flag_creator.current -= 524288;
					}

					});
				sub->draw_option<toggle<bool>>(("Ignore Roads"), nullptr, &flag_creator.ignore_roads, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.ignore_roads;
					if (buffer) {
						flag_creator.current += 4194304;
					}
					if (!buffer) {
						flag_creator.current -= 4194304;
					}

					});
				sub->draw_option<toggle<bool>>(("Ignore All Pathing"), nullptr, &flag_creator.ignore_all_pathing, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.ignore_all_pathing;
					if (buffer) {
						flag_creator.current += 16777216;
					}
					if (!buffer) {
						flag_creator.current -= 16777216;
					}

					});
				sub->draw_option<toggle<bool>>(("Avoid Highways"), nullptr, &flag_creator.avoid_highways, BoolDisplay::OnOff, false, [] {
					bool buffer = flag_creator.avoid_highways;
					if (buffer) {
						flag_creator.current += 536870912;
					}
					if (!buffer) {
						flag_creator.current -= 536870912;
					}

					});
			});
		g_Render->draw_submenu<sub>(("Acrobatics"), SubmenuAcrobatics, [](sub* sub)
			{

				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &acrobatic_type, &acrobatic_int);
				sub->draw_option<RegularOption>(("Start"), nullptr, []
					{
						if (acrobatic_int == 0) {

							Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);

						}
						if (acrobatic_int == 1) {

							Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 9.0f, 0, -2.0f, 0, true, true, true, true, false, true);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 9.0f, 0, -2.0f, 0, true, true, true, true, false, true);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 9.0f, 0, -2.0f, 0, true, true, true, true, false, true);

						}
						if (acrobatic_int == 2) {

							Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 10.0f, 20.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);

						}
						if (acrobatic_int == 3) {

							Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 7.0f, 0, 0, 0, true, true, true, true, false, true);



						}
					});



			});
		g_Render->draw_submenu<sub>(("Speedometer"), SubmenuSpeedo, [](sub* sub)
			{
				sub->draw_option<submenu>("Custom", "", rage::joaat("CustomSpeedo"));
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Enabled", nullptr, &speedo.enabled, &speedo.type, &speedo.type_i);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Font", nullptr, &g_Render->HeaderFont, &speedo.font2);
				sub->draw_option<number<float>>("X Offset", nullptr, &speedo.x_offset, -100.f, 100.f, 0.01f, 2);
				sub->draw_option<number<float>>("Y Offset", nullptr, &speedo.y_offset, -100.f, 100.f, 0.01f, 2);
				sub->draw_option<number<float>>("Scale", nullptr, &speedo.scale, 0.f, 100.f, 0.01f, 2);
				sub->draw_option<UnclickOption>(("Color"), nullptr, [] {});
				sub->draw_option<number<std::int32_t>>("R", nullptr, &speedo.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &speedo.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &speedo.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &speedo.b, 0, 255);


			});
		g_Render->draw_submenu<sub>(("Custom"), rage::joaat("CustomSpeedo"), [](sub* sub)
			{
				sub->draw_option<KeyboardOption>(("Name"), nullptr, speedo.custom_name, []
					{
						showKeyboard("Enter Something", "", 25, &speedo.custom_name, [] {});


					});

				sub->draw_option<number<float>>("Value", nullptr, &speedo.custom_times, -10000.f, 10000.f, 0.01f);
			});
		g_Render->draw_submenu<sub>(("Settings"), rage::joaat("SetitngsForLsc"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Hide HSW"), nullptr, &features.hide_hsw_mods, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("LSC"), SubmenuCustomize, [](sub* sub)
			{
				sub->draw_option<submenu>("Settings", "", rage::joaat("SetitngsForLsc"));
				sub->draw_option<UnclickOption>(("Modifications"), nullptr, [] {});
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					Vehicle veh; veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
					VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) > 0)
					{
						sub->draw_option<submenu>("Armor", "", LosSantosArmor);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_BRAKES) > 0)
					{
						sub->draw_option<submenu>("Brakes", "", LosSantosBrakes);
					}
					sub->draw_option<submenu>("Lights", "", LosSantosLights);
					
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTBUMPER) > 0)
					{
						sub->draw_option<submenu>("Front Bumper", "", LosSantosFront);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_REARBUMPER) > 0)
					{
						sub->draw_option<submenu>("Rear Bumper", "", LosSantosRear);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) > 0)
					{
						sub->draw_option<submenu>("Plates", "", LosSantosPlate);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_PLATEHOLDER) > 0)
					{
						sub->draw_option<submenu>("Plateholder", "", Submenu::PLATEHOLDER25);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_VANITY_PLATES) > 0)
					{
						sub->draw_option<submenu>("Vanity Plates", "", VANITY_PLATES26);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE) > 0)
					{
						sub->draw_option<submenu>("Engine", "", LosSantosEngine);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST) > 0)
					{
						sub->draw_option<submenu>("Exhaust", "", LosSantosExhaust);
					}

					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRIM) > 0)
					{
						sub->draw_option<submenu>("Trim", "", TRIM27);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ORNAMENTS) > 0)
					{
						sub->draw_option<submenu>("Ornaments", "", ORNAMENTS28);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_DASHBOARD) > 0)
					{
						sub->draw_option<submenu>("Dashboard", "", Submenu::DASHBOARD29);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_DIAL) > 0)
					{
						sub->draw_option<submenu>("Dial", "", Submenu::DIAL30);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_DOOR_SPEAKER) > 0)
					{
						sub->draw_option<submenu>("Door Seaker", "", Submenu::DOOR_SPEAKER31);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SEATS) > 0)
					{
						sub->draw_option<submenu>("Seats", "", Submenu::SEATS32);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_STEERINGWHEEL) > 0)
					{
						sub->draw_option<submenu>("Steering Wheel", "", Submenu::STEERINGWHEEL33);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SHIFTER_LEAVERS) > 0)
					{
						sub->draw_option<submenu>("Shifter Leavers", "", Submenu::SHIFTER_LEAVERS34);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_PLAQUES) > 0)
					{
						sub->draw_option<submenu>("Plaques", "", Submenu::PLAQUES35);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPEAKERS) > 0)
					{
						sub->draw_option<submenu>("Speakers", "", Submenu::SPEAKERS36);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRUNK) > 0)
					{
						sub->draw_option<submenu>("Trunk", "", Submenu::TRUNK37);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HYDRAULICS) > 0)
					{
						sub->draw_option<submenu>("Hydraulics", "", Submenu::HYDRAULICS38);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE_BLOCK) > 0)
					{
						sub->draw_option<submenu>("Engine Block", "", Submenu::ENGINE_BLOCK39);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_AIR_FILTER) > 0)
					{
						sub->draw_option<submenu>("Air Filter", "", Submenu::AIR_FILTER);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_STRUTS) > 0)
					{
						sub->draw_option<submenu>("Struts", "", Submenu::STRUTS);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARCH_COVER) > 0)
					{
						sub->draw_option<submenu>("Arch Cover", "", Submenu::ARCH_COVER);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_AERIALS) > 0)
					{
						sub->draw_option<submenu>("Aerials", "", Submenu::AERIALS);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRIM_2) > 0)
					{
						sub->draw_option<submenu>("Trim 2", "", Submenu::TRIM_2);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TANK) > 0)
					{
						sub->draw_option<submenu>("Tank", "", Submenu::TANK);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_WINDOWS) > 0)
					{
						sub->draw_option<submenu>("Windows", "", Submenu::WINDOWS);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FENDER) > 0)
					{
						sub->draw_option<submenu>("Fender", "", LosSantosFender);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_RIGHTFENDER) > 0)
					{
						sub->draw_option<submenu>("Right Fender", "", LosSantosRightFender);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_GRILLE) > 0)
					{
						sub->draw_option<submenu>("Grille", "", LosSantosGrille);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HOOD) > 0)
					{
						sub->draw_option<submenu>("Hood", "", LosSantosHood);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HORNS) > 0)
					{
						sub->draw_option<submenu>("Horn", "", LosSantosHorn);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_LIVERY) > 0)
					{
						sub->draw_option<submenu>("Livery", "", LosSantosLivery);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ROOF) > 0)
					{
						sub->draw_option<submenu>("Roof", "", LosSantosRoof);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SIDESKIRT) > 0)
					{
						sub->draw_option<submenu>("Skirts", "", LosSantosSkirts);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_CHASSIS) > 0)
					{
						sub->draw_option<submenu>("Chassis", "", LosSantosChassis);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPOILER) > 0)
					{
						sub->draw_option<submenu>("Spoiler", "", LosSantosSpoiler);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SUSPENSION) > 0)
					{
						sub->draw_option<submenu>("Suspension", "", LosSantosSuspension);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRANSMISSION) > 0)
					{
						sub->draw_option<submenu>("Transmission", "", LosSantosTransmission);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) > 0)
					{
						//	sub->draw_option<submenu>("Wheels", "", LosSantosWheels);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_WINDOWS) > 0)
					{
						sub->draw_option<submenu>("Windows", "", LosSantosWindows);
					}
					sub->draw_option<submenu>("Wheels", "", rage::joaat("Wheels"));
					
					sub->draw_option<toggle<bool>>(("Turbo"), nullptr, &lsc.turbo, BoolDisplay::OnOff, false, [] {
						if (!lsc.turbo)
						{
							VEHICLE::TOGGLE_VEHICLE_MOD(get_veh(), 18, false);

						}
						});



				}


			});
			g_Render->draw_submenu<sub>("Lights", LosSantosLights, [](sub* sub)
				{
					sub->draw_option<submenu>("Neon", "", rage::joaat("NeonLights"));
					sub->draw_option<toggle<bool>>(("Xenon"), nullptr, &lsc.xenon, BoolDisplay::OnOff, false, [] {
						if (!lsc.xenon)
						{
							VEHICLE::TOGGLE_VEHICLE_MOD(get_veh(), 22, false);

						}
						});
				});
			g_Render->draw_submenu<sub>("Wheels", rage::joaat("NeonLights"), [](sub* sub)
				{
					sub->draw_option<toggle<bool>>(("Front"), nullptr, &lsc.neon.front, BoolDisplay::OnOff, false, [] {
						if (!lsc.neon.front)
						{
							VEHICLE::TOGGLE_VEHICLE_MOD(get_veh(), 2, false);

						}
						});
					sub->draw_option<toggle<bool>>(("Back"), nullptr, &lsc.neon.back, BoolDisplay::OnOff, false, [] {
						if (!lsc.neon.back)
						{
							VEHICLE::SET_VEHICLE_NEON_ENABLED(get_veh(), 3, false);

						}
						});
					sub->draw_option<toggle<bool>>(("Left"), nullptr, &lsc.neon.left, BoolDisplay::OnOff, false, [] {
						if (!lsc.neon.left)
						{
							VEHICLE::SET_VEHICLE_NEON_ENABLED(get_veh(), 0, false);

						}
						});
					sub->draw_option<toggle<bool>>(("Right"), nullptr, &lsc.neon.right, BoolDisplay::OnOff, false, [] {
						if (!lsc.neon.right)
						{
							VEHICLE::SET_VEHICLE_NEON_ENABLED(get_veh(), 1, false);

						}
						});
				});
		g_Render->draw_submenu<sub>("Wheels", rage::joaat("Wheels"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &lsc.TypeName, &lsc.pos, true, -1, [] {
					lsc.set_wheel_type(lsc.pos);
					});
				sub->draw_option<number<std::int32_t>>("Index", nullptr, &lsc.wheel_type, 0, VEHICLE::GET_NUM_VEHICLE_MODS(get_veh(), 23), 1, 3, true, "", "", [] {
					lsc.set_wheel(lsc.wheel_type);
					});
				//crash the gate doing 98 (american song v98 and tim wouldent understand)
			});
		g_Render->draw_submenu<sub>("Windows", LosSantosWindows, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_WINDOWS, -1);
					});
				sub->draw_option<RegularOption>("Light Smoke", "", []
					{
						VehicleModifier(MOD_WINDOWS, 1);
					});
				sub->draw_option<RegularOption>("Dark Smoke", "", []
					{
						VehicleModifier(MOD_WINDOWS, 2);
					});
				sub->draw_option<RegularOption>("Limo", "", []
					{
						VehicleModifier(MOD_WINDOWS, 3);
					});
			});
		g_Render->draw_submenu<sub>("Armor", LosSantosArmor, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_ARMOR, -1);
					});
				sub->draw_option<RegularOption>("Armor Upgrade 20%", "", []
					{
						VehicleModifier(MOD_ARMOR, 0);
					});
				sub->draw_option<RegularOption>("Armor Upgrade 40%", "", []
					{
						VehicleModifier(MOD_ARMOR, 1);
					});
				sub->draw_option<RegularOption>("Armor Upgrade 60%", "", []
					{
						VehicleModifier(MOD_ARMOR, 2);
					});
				sub->draw_option<RegularOption>("Armor Upgrade 80%", "", []
					{
						VehicleModifier(MOD_ARMOR, 3);
					});
				sub->draw_option<RegularOption>("Armor Upgrade 100%", "", []
					{
						VehicleModifier(MOD_ARMOR, 4);
					});
			});
		g_Render->draw_submenu<sub>("Horns", LosSantosHorn, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_HORNS, -1);
					});
				sub->draw_option<RegularOption>("1", "", []
					{
						VehicleModifier(MOD_HORNS, 0);
					});
				sub->draw_option<RegularOption>("2", "", []
					{
						VehicleModifier(MOD_HORNS, 1);
					});
				sub->draw_option<RegularOption>("3", "", []
					{
						VehicleModifier(MOD_HORNS, 2);
					});
				sub->draw_option<RegularOption>("4", "", []
					{
						VehicleModifier(MOD_HORNS, 3);
					});
				sub->draw_option<RegularOption>("5", "", []
					{
						VehicleModifier(MOD_HORNS, 4);
					});
				sub->draw_option<RegularOption>("6", "", []
					{
						VehicleModifier(MOD_HORNS, 5);
					});
				sub->draw_option<RegularOption>("7", "", []
					{
						VehicleModifier(MOD_HORNS, 6);
					});
				sub->draw_option<RegularOption>("8", "", []
					{
						VehicleModifier(MOD_HORNS, 7);
					});
				sub->draw_option<RegularOption>("9", "", []
					{
						VehicleModifier(MOD_HORNS, 8);
					});
				sub->draw_option<RegularOption>("10", "", []
					{
						VehicleModifier(MOD_HORNS, 9);
					});
				sub->draw_option<RegularOption>("11", "", []
					{
						VehicleModifier(MOD_HORNS, 10);
					});
				sub->draw_option<RegularOption>("12", "", []
					{
						VehicleModifier(MOD_HORNS, 11);
					});
				sub->draw_option<RegularOption>("13", "", []
					{
						VehicleModifier(MOD_HORNS, 12);
					});
				sub->draw_option<RegularOption>("14", "", []
					{
						VehicleModifier(MOD_HORNS, 13);
					});
				sub->draw_option<RegularOption>("15", "", []
					{
						VehicleModifier(MOD_HORNS, 14);
					});
				sub->draw_option<RegularOption>("16", "", []
					{
						VehicleModifier(MOD_HORNS, 15);
					});
				sub->draw_option<RegularOption>("17", "", []
					{
						VehicleModifier(MOD_HORNS, 16);
					});
				sub->draw_option<RegularOption>("18", "", []
					{
						VehicleModifier(MOD_HORNS, 17);
					});
				sub->draw_option<RegularOption>("19", "", []
					{
						VehicleModifier(MOD_HORNS, 18);
					});
				sub->draw_option<RegularOption>("20", "", []
					{
						VehicleModifier(MOD_HORNS, 19);
					});
				sub->draw_option<RegularOption>("21", "", []
					{
						VehicleModifier(MOD_HORNS, 20);
					});
				sub->draw_option<RegularOption>("22", "", []
					{
						VehicleModifier(MOD_HORNS, 21);
					});
				sub->draw_option<RegularOption>("23", "", []
					{
						VehicleModifier(MOD_HORNS, 22);
					});
				sub->draw_option<RegularOption>("24", "", []
					{
						VehicleModifier(MOD_HORNS, 23);
					});
				sub->draw_option<RegularOption>("25", "", []
					{
						VehicleModifier(MOD_HORNS, 24);
					});
				sub->draw_option<RegularOption>("26", "", []
					{
						VehicleModifier(MOD_HORNS, 25);
					});
				sub->draw_option<RegularOption>("27", "", []
					{
						VehicleModifier(MOD_HORNS, 26);
					});
				sub->draw_option<RegularOption>("28", "", []
					{
						VehicleModifier(MOD_HORNS, 27);
					});
				sub->draw_option<RegularOption>("29", "", []
					{
						VehicleModifier(MOD_HORNS, 28);
					});
				sub->draw_option<RegularOption>("30", "", []
					{
						VehicleModifier(MOD_HORNS, 29);
					});
				sub->draw_option<RegularOption>("31", "", []
					{
						VehicleModifier(MOD_HORNS, 30);
					});
				sub->draw_option<RegularOption>("32", "", []
					{
						VehicleModifier(MOD_HORNS, 31);
					});
				sub->draw_option<RegularOption>("33", "", []
					{
						VehicleModifier(MOD_HORNS, 32);
					});
				sub->draw_option<RegularOption>("34", "", []
					{
						VehicleModifier(MOD_HORNS, 33);
					});
				sub->draw_option<RegularOption>("35", "", []
					{
						VehicleModifier(MOD_HORNS, 34);
					});
				sub->draw_option<RegularOption>("36", "", []
					{
						VehicleModifier(MOD_HORNS, 35);
					});
				sub->draw_option<RegularOption>("37", "", []
					{
						VehicleModifier(MOD_HORNS, 36);
					});
				sub->draw_option<RegularOption>("38", "", []
					{
						VehicleModifier(MOD_HORNS, 37);
					});
				sub->draw_option<RegularOption>("39", "", []
					{
						VehicleModifier(MOD_HORNS, 38);
					});
				sub->draw_option<RegularOption>("40", "", []
					{
						VehicleModifier(MOD_HORNS, 39);
					});
			});
		g_Render->draw_submenu<sub>("Brakes", LosSantosBrakes, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_BRAKES, -1);
					});
				sub->draw_option<RegularOption>("Street Brakes", "", []
					{
						VehicleModifier(MOD_BRAKES, 0);
					});
				sub->draw_option<RegularOption>("Street Brakes", "", []
					{
						VehicleModifier(MOD_BRAKES, 1);
					});
				sub->draw_option<RegularOption>("Race Brakes", "", []
					{
						VehicleModifier(MOD_BRAKES, 2);
					});
			});
		g_Render->draw_submenu<sub>("Engine", LosSantosEngine, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_ENGINE, -1);
					});
				sub->draw_option<RegularOption>("1", "", []
					{
						VehicleModifier(MOD_ENGINE, 0);
					});
				sub->draw_option<RegularOption>("2", "", []
					{
						VehicleModifier(MOD_ENGINE, 1);
					});
				sub->draw_option<RegularOption>("3", "", []
					{
						VehicleModifier(MOD_ENGINE, 2);
					});
				sub->draw_option<RegularOption>("4", "", []
					{
						VehicleModifier(MOD_ENGINE, 3);
					});
			});
		g_Render->draw_submenu<sub>("Exhaust", LosSantosExhaust, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_EXHAUST, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST); i++)
				{
					sub->draw_option<RegularOption>(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_EXHAUST, i)), "", [i]
						{
							VehicleModifier(MOD_EXHAUST, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Front Bumper", LosSantosFront, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_FRONTBUMPER, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTBUMPER); i++)
				{
					sub->draw_option<RegularOption>(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_FRONTBUMPER, i)), "", [i]
						{
							VehicleModifier(MOD_FRONTBUMPER, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Rear Bumper", LosSantosRear, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_REARBUMPER, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_REARBUMPER); i++)
				{
					sub->draw_option<RegularOption>(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_REARBUMPER, i)), "", [i]
						{
							VehicleModifier(MOD_REARBUMPER, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Livery", LosSantosLivery, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_LIVERY, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_LIVERY); i++)
				{
					sub->draw_option<RegularOption>(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_LIVERY, i)), "", [i]
						{
							VehicleModifier(MOD_LIVERY, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Fender", LosSantosFender, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_FENDER, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FENDER);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* GrilleTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_FENDER, i);
					const char* GrilleName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(GrilleTextLabel);
					sub->draw_option<RegularOption>(GrilleName, "", [i]
						{
							VehicleModifier(MOD_FENDER, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Right Fender", LosSantosRightFender, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_RIGHTFENDER, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_RIGHTFENDER);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* GrilleTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_RIGHTFENDER, i);
					const char* GrilleName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(GrilleTextLabel);
					sub->draw_option<RegularOption>(GrilleName, "", [i]
						{
							VehicleModifier(MOD_RIGHTFENDER, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Grille", LosSantosGrille, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_GRILLE, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_GRILLE);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* GrilleTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_GRILLE, i);
					const char* GrilleName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(GrilleTextLabel);
					sub->draw_option<RegularOption>(GrilleName, "", [i]
						{
							VehicleModifier(MOD_GRILLE, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Hood", LosSantosHood, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_HOOD, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HOOD);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* HoodTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_HOOD, i);
					const char* HoodName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(HoodTextLabel);
					sub->draw_option<RegularOption>(HoodName, "", [i]
						{
							VehicleModifier(MOD_HOOD, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Spoiler", LosSantosSpoiler, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(0, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 0);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* RoofTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, 0, i);
					const char* RoofName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(RoofTextLabel);
					sub->draw_option<RegularOption>(RoofName, "", [i]
						{
							VehicleModifier(0, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Roof", LosSantosRoof, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_ROOF, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ROOF);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* RoofTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_ROOF, i);
					const char* RoofName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(RoofTextLabel);
					sub->draw_option<RegularOption>(RoofName, "", [i]
						{
							VehicleModifier(MOD_ROOF, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Chassis", LosSantosChassis, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_CHASSIS, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_CHASSIS);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SkirtsTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_CHASSIS, i);
					const char* SkirtsName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SkirtsTextLabel);
					sub->draw_option<RegularOption>(SkirtsName, "", [i]
						{
							VehicleModifier(MOD_CHASSIS, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Skirts", LosSantosSkirts, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_SIDESKIRT, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SIDESKIRT);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SkirtsTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_SIDESKIRT, i);
					const char* SkirtsName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SkirtsTextLabel);
					sub->draw_option<RegularOption>(SkirtsName, "", [i]
						{
							VehicleModifier(MOD_SIDESKIRT, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Suspension", LosSantosSuspension, [](sub* sub)
			{
				sub->draw_option<RegularOption>("Stock Suspension", "", []
					{
						VehicleModifier(MOD_SUSPENSION, -1);
					});
				sub->draw_option<RegularOption>("Lowered Suspension", "", []
					{
						VehicleModifier(MOD_SUSPENSION, 0);
					});
				sub->draw_option<RegularOption>("Street Suspension", "", []
					{
						VehicleModifier(MOD_SUSPENSION, 1);
					});
				sub->draw_option<RegularOption>("Sport Suspension", "", []
					{
						VehicleModifier(MOD_SUSPENSION, 2);
					});
				sub->draw_option<RegularOption>("Competition Suspension", "", []
					{
						VehicleModifier(MOD_SUSPENSION, 3);
					});
			});
		g_Render->draw_submenu<sub>("Transmission", LosSantosTransmission, [](sub* sub)
			{
				sub->draw_option<RegularOption>("Stock Transmission", "", []
					{
						VehicleModifier(MOD_TRANSMISSION, -1);
					});
				sub->draw_option<RegularOption>("Street Transmission", "", []
					{
						VehicleModifier(MOD_TRANSMISSION, 0);
					});
				sub->draw_option<RegularOption>("Sports Transmission", "", []
					{
						VehicleModifier(MOD_TRANSMISSION, 1);
					});
				sub->draw_option<RegularOption>("Race Transmission", "", []
					{
						VehicleModifier(MOD_TRANSMISSION, 2);
					});
			});
		g_Render->draw_submenu<sub>("Plate Holder", PLATEHOLDER25, [](sub* sub)
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_PLATEHOLDER);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_PLATEHOLDER, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [i]
						{
							VehicleModifier(MOD_PLATEHOLDER, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Vanity Plates", VANITY_PLATES26, [](sub* sub)
			{
				int buffer = MOD_VANITY_PLATES;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Trim", TRIM27, [](sub* sub)
			{
				int buffer = MOD_TRIM;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Ornaments", ORNAMENTS28, [](sub* sub)
			{
				int buffer = MOD_ORNAMENTS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Dashboard", DASHBOARD29, [](sub* sub)
			{
				int buffer = MOD_DASHBOARD;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Dial", DIAL30, [](sub* sub)
			{
				int buffer = MOD_DIAL;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Door Speaker", DOOR_SPEAKER31, [](sub* sub)
			{
				int buffer = MOD_DASHBOARD;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Seats", SEATS32, [](sub* sub)
			{
				int buffer = MOD_SEATS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Steering Wheel", STEERINGWHEEL33, [](sub* sub)
			{
				int buffer = MOD_STEERINGWHEEL;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Shifter Leavers", SHIFTER_LEAVERS34, [](sub* sub)
			{
				int buffer = MOD_SHIFTER_LEAVERS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Plaques", PLAQUES35, [](sub* sub)
			{
				int buffer = MOD_PLAQUES;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Speakers", SPEAKERS36, [](sub* sub)
			{
				int buffer = MOD_SPEAKERS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Trunk", TRUNK37, [](sub* sub)
			{
				int buffer = MOD_TRUNK;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Hydrualics", HYDRAULICS38, [](sub* sub)
			{
				int buffer = MOD_HYDRAULICS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Hydrualics", HYDRAULICS38, [](sub* sub)
			{
				int buffer = MOD_HYDRAULICS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Engine Block", ENGINE_BLOCK39, [](sub* sub)
			{
				int buffer = MOD_ENGINE_BLOCK;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Air Filter", AIR_FILTER, [](sub* sub)
			{
				int buffer = MOD_AIR_FILTER;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Struts", STRUTS, [](sub* sub)
			{
				int buffer = MOD_STRUTS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Arch Cover", ARCH_COVER, [](sub* sub)
			{
				int buffer = MOD_ARCH_COVER;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Arials", AERIALS, [](sub* sub)
			{
				int buffer = MOD_AERIALS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Trim 2", TRIM_2, [](sub* sub)
			{
				int buffer = MOD_TRIM_2;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Tank", TANK, [](sub* sub)
			{
				int buffer = MOD_TANK;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Windows", WINDOWS, [](sub* sub)
			{
				int buffer = MOD_WINDOWS;
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, buffer);
				for (int i = 0; i < AmountOfVehicleMods; i++)
				{
					const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, buffer, i);
					const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
					sub->draw_option<RegularOption>(SpoilerName, "", [=]
						{
							VehicleModifier(buffer, i);
						});
				}
			});
		g_Render->draw_submenu<sub>("Exhaust", LosSantosExhaust, [](sub* sub)
			{
				sub->draw_option<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_EXHAUST, -1);
					});
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST); i++)
				{
					sub->draw_option<RegularOption>(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_EXHAUST, i)), "", [i]
						{
							VehicleModifier(MOD_EXHAUST, i);
						});
				}
			});
		g_Render->draw_submenu<sub>(("Negitive Torque"), SubmenuNegitiveTorque, [](sub* sub)
			{


				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &negitiveTorque.enabled, BoolDisplay::OnOff, false, [] {
					if (!negitiveTorque.enabled) {
						VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1.0);
					}
					});
				sub->draw_option<number<float>>("Multiplier", nullptr, &negitiveTorque.multiplier, 0.1f, 100.f, 0.10f, 2);


			});
		g_Render->draw_submenu<sub>(("Engine Sound"), SubmenuEngineSound, [](sub* sub)
			{

				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &sound_type, &sound_int);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						AUDIO::FORCE_USE_AUDIO_GAME_OBJECT(veh, sound_data[sound_int]);
					});


			});
		g_Render->draw_submenu<sub>(("Handling"), SubmenuVehicleMultipliers, [](sub* sub)
			{
				sub->draw_option<submenu>("Presets", nullptr, SubmenuPresets);
				sub->draw_option<UnclickOption>(("Edit"), nullptr, [] {});
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
					sub->draw_option<submenu>("Miscellaneous", nullptr, HandlingMisc);
					sub->draw_option<submenu>("Centre Of Mass", nullptr, CentreOfMass);
					sub->draw_option<submenu>("Inertia Multiplier", nullptr, InertiaMultiplier);
					sub->draw_option<submenu>("Drive Bias", nullptr, DriveBias);
					sub->draw_option<submenu>("Shift", nullptr, Shift);
					sub->draw_option<submenu>("Brakes", nullptr, HandlingBrakes);
					sub->draw_option<submenu>("Steering Lock", nullptr, SteeringLock);
					sub->draw_option<submenu>("Traction", nullptr, Traction);
					sub->draw_option<submenu>("Curve", nullptr, Curve);
					sub->draw_option<submenu>("Suspension", nullptr, Suspension);
					sub->draw_option<submenu>("Anti Rollbar", nullptr, RollCentreHeight);
					sub->draw_option<submenu>("Damage", nullptr, HandlingDamage);
					sub->draw_option<submenu>("Gas", nullptr, HandlingGas);
				}


			});
		g_Render->draw_submenu<sub>(("Miscellaneous"), HandlingMisc, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Mass", nullptr, &handling->m_mass, 0.f, 10000.f, 50.0f, 1);
				sub->draw_option<number<float>>("Initial Drag Coeff", nullptr, &handling->m_initial_drag_coeff, 0.f, 10000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Downforce Multiplier", nullptr, &handling->m_downforce_multiplier, 0.f, 10000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Popup Light Rotation", nullptr, &handling->m_popup_light_rotation, 0.f, 10000.f, 0.1f, 1);


				sub->draw_option<number<float>>("Buoyancy", nullptr, &handling->m_buoyancy, 0.0f, 1000.f, 1.0f, 1);

				sub->draw_option<number<float>>("Acceleration", nullptr, &handling->m_acceleration, 0.0f, 1000.f, 0.1f, 1);

				sub->draw_option<number<float>>("Initial Drive Force", nullptr, &handling->m_initial_drive_force, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Drive Max Flat Velocity", nullptr, &handling->m_drive_max_flat_velocity, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Initial Drive Max Flat Velocity", nullptr, &handling->m_initial_drive_max_flat_vel, 0.0f, 1000.f, 0.1f, 1);

				sub->draw_option<number<float>>("Handbrake Force", nullptr, &handling->m_handbrake_force, 0.0f, 1000.f, 0.1f, 1);





				sub->draw_option<number<float>>("Camber Stiffness", nullptr, &handling->m_camber_stiffness, 0.0f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Damage"), HandlingDamage, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Collision Multiplier", nullptr, &handling->m_collision_damage_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Weapon Multiplier", nullptr, &handling->m_weapon_damamge_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Deformation Multiplier", nullptr, &handling->m_deformation_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Engine Multiplier", nullptr, &handling->m_engine_damage_mult, -1000.f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Gas"), HandlingGas, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Petrol Tank Volume", nullptr, &handling->m_petrol_tank_volume, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Oil Volume", nullptr, &handling->m_oil_volume, 1000.f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Anti Rollbar"), RollCentreHeight, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Force", nullptr, &handling->m_anti_rollbar_force, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Bias Front", nullptr, &handling->m_anti_rollbar_bias_front, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Bias Rear", nullptr, &handling->m_anti_rollbar_bias_rear, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Centre Height Front", nullptr, &handling->m_roll_centre_height_front, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Centre Height Rear", nullptr, &handling->m_roll_centre_height_rear, -1000.f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Shift"), Shift, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Up", nullptr, &handling->m_upshift, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Down", nullptr, &handling->m_downshift, 0.0f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Brakes"), HandlingBrakes, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Force", nullptr, &handling->m_brake_force, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Bias Front", nullptr, &handling->m_brake_bias_front, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Bias Rear", nullptr, &handling->m_brake_bias_rear, 0.0f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Steering Lock"), SteeringLock, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Multiplier", nullptr, &handling->m_steering_lock, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Ratio", nullptr, &handling->m_steering_lock_ratio, 0.0f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Curve"), Curve, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Lateral", nullptr, &handling->m_curve_lateral, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Lateral Ratio", nullptr, &handling->m_curve_lateral_ratio, 0.0f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Suspension"), Suspension, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Force", nullptr, &handling->m_suspension_force, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Comp Damp", nullptr, &handling->m_suspension_comp_damp, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Rebound Damp", nullptr, &handling->m_suspension_rebound_damp, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Upper Limit", nullptr, &handling->m_suspension_upper_limit, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Lower Limit", nullptr, &handling->m_suspension_lower_limit, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Raise", nullptr, &handling->m_suspension_raise, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Bias Front", nullptr, &handling->m_suspension_bias_front, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Bias Rear", nullptr, &handling->m_suspension_bias_rear, -1000.f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Traction"), Traction, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Max", nullptr, &handling->m_traction_curve_max, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Min", nullptr, &handling->m_traction_curve_min, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Lateral", nullptr, &handling->m_traction_curve_lateral, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Ratio", nullptr, &handling->m_traction_curve_ratio, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Spring Delta Max", nullptr, &handling->m_traction_spring_delta_max, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Spring Delta Max Ratio", nullptr, &handling->m_traction_spring_delta_max_ratio, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Bias Front", nullptr, &handling->m_traction_bias_front, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Bias Rear", nullptr, &handling->m_traction_bias_rear, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Loss Multiplier", nullptr, &handling->m_traction_loss_mult, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Low Speed Loss Multiplier", nullptr, &handling->m_low_speed_traction_loss_mult, 0.0f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Drive Bias"), DriveBias, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("Rear", nullptr, &handling->m_drive_bias_rear, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Front", nullptr, &handling->m_drive_bias_front, 0.0f, 1000.f, 0.1f, 1);


			});

		g_Render->draw_submenu<sub>(("Inertia Multiplier"), InertiaMultiplier, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("X", nullptr, &handling->m_inertia_mult.x, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Y", nullptr, &handling->m_inertia_mult.y, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Z", nullptr, &handling->m_inertia_mult.z, 0.0f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Centre Of Mass"), CentreOfMass, [](sub* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->draw_option<number<float>>("X", nullptr, &handling->m_centre_of_mass.x, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Y", nullptr, &handling->m_centre_of_mass.y, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Z", nullptr, &handling->m_centre_of_mass.z, 0.0f, 1000.f, 0.1f, 1);


			});
		g_Render->draw_submenu<sub>(("Presets"), SubmenuPresets, [](sub* sub)
			{

				sub->draw_option<RegularOption>(("Save"), nullptr, []
					{

						showKeyboard("Enter Something", "", 25, &handlingBuffer, [] {
							m_handling.save(handlingBuffer);
							});
					});
				sub->draw_option<UnclickOption>(("Lists"), nullptr, [] {});
				if (std::filesystem::exists("C:\\Saint\\Handling\\") && std::filesystem::is_directory("C:\\Saint\\Handling\\")) {
					namespace fs = std::filesystem;
					fs::directory_iterator dirIt{ "C:\\Saint\\Handling\\" };
					for (auto&& dirEntry : dirIt)
					{
						if (dirEntry.is_regular_file())
						{
							auto path = dirEntry.path();
							if (path.has_filename())
							{
								if (path.extension() == ".ini")
								{
									OutfitList();
									char nigger[64];
									sprintf(nigger, "%s", path.stem().u8string().c_str());
									sub->draw_option<RegularOption>(nigger, nullptr, [=]
										{
											m_handling.load(nigger);
										});

								}

							}
						}
					}

				}
				else {
					std::filesystem::create_directory("C:\\Saint\\Handling\\");
				}




			});
		g_Render->draw_submenu<sub>(("Horn Boost"), SubmenuHornBoost, [](sub* sub)
			{
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Enabled", nullptr, &hornboost.enabled, &hornboost.Boost_Type, &hornboost.Boost_Int);

				sub->draw_option<toggle<bool>>(("Smooth"), nullptr, &hornboost.smooth, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Only On Ground"), nullptr, &hornboost.onlyOnGround, BoolDisplay::OnOff);

				sub->draw_option<number<std::int32_t>>("Speed", nullptr, &hornboost.speed, 0, 1000);
				if (hornboost.smooth) {
					sub->draw_option<number<float>>("Boost Power", nullptr, &hornboost.boost_power, 0.1f, 50.f, 0.05f, 2);
				}


			});
		g_Render->draw_submenu<sub>(("Weapon"), SubmenuWeapon, [](sub* sub)
			{
				sub->draw_option<submenu>("Explosive Ammo", nullptr, SubmenuExplosiveAmmo);
				sub->draw_option<submenu>("Rapid Fire", nullptr, SubmenuRapidFire);
				sub->draw_option<submenu>("Triggerbot", nullptr, SubmenuTriggerbot);
				sub->draw_option<submenu>("Aimbot", nullptr, SubmenuAimbot);
				sub->draw_option<submenu>("Airstrike", nullptr, SubmenuAirstrike);
				sub->draw_option<submenu>("Targeting Mode", nullptr, SubmenuTargetingMode);
				sub->draw_option<submenu>("Multipliers", nullptr, SubmenuWeaponMultipliers);
				sub->draw_option<submenu>("Animation", nullptr, SubmenuWeaponAnimation);
				sub->draw_option<submenu>("Gun Locker", nullptr, SubmenuGunLocker);
				sub->draw_option<submenu>("Entity Shooter", nullptr, EntityShooter);
				sub->draw_option<submenu>("Light", nullptr, rage::joaat("Paint"));
				sub->draw_option<submenu>("Bullet Changer", nullptr, rage::joaat("BULLET_CHANGER"));
				sub->draw_option<toggle<bool>>(("Infinite Ammo"), nullptr, &features.infinite_ammo, BoolDisplay::OnOff, false, [] {
					if (!features.infinite_ammo) {
						WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), false);
					}
					});
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Teleport", nullptr, &features.teleport_gun, &features.teleport_gun_type, &features.teleport_gun_int);
				sub->draw_option<toggle<bool>>(("Delete"), nullptr, &features.delete_gun, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Bypass C4 Limit"), nullptr, &features.bypass_c4_limit, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Gravity"), nullptr, &gravity.enabled, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Incendiary"), nullptr, &m_frame_flags.m_fire, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Aim Tracer"), nullptr, &features.aim_tracer, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Rope"), nullptr, &rope_gun.enabled, BoolDisplay::OnOff);
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Money", nullptr, &wdrop.money, &wdrop.money_model, &wdrop.money_model_data);
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("RP", nullptr, &wdrop.rp, &wdrop.rp_model, &wdrop.rp_model_data);
				sub->draw_option<toggle<bool>>(("Shotgun"), nullptr, &m_shotgun.enabled, BoolDisplay::OnOff, false, [] {
					if (!m_shotgun.enabled) {
						m_shotgun.onDisable();
					}
					});
				sub->draw_option<toggle_number_option<std::int32_t, bool>>("Force", nullptr, &features.force_gun, &features.force_gun_mult, 0, 300, 10);
				sub->draw_option<toggle_number_option<float, bool>>("Grapple Hook", nullptr, &ghook.enabled, &ghook.speed, 0.1f, 50.f, 0.1f);

			});
		g_Render->draw_submenu<sub>(("Bullet Changer"), rage::joaat("BULLET_CHANGER"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &bullet_changer.enabled, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &all_weapons.name, &bullet_changer.weapon_pos);
				sub->draw_option<UnclickOption>("Attributes", nullptr, [] {});
				sub->draw_option<toggle<bool>>(("Audible"), nullptr, &bullet_changer.Audible, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Invisible"), nullptr, &bullet_changer.Invisible, BoolDisplay::OnOff);
				sub->draw_option<number<float>>("Velocity", nullptr, &bullet_changer.velocity, 0.1f, 1000.f, 1.f);
			});
		g_Render->draw_submenu<sub>(("Light"), rage::joaat("Paint"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &paint.enabled, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>("Attributes", nullptr, [] {});
				sub->draw_option<toggle<bool>>(("Rainbow"), nullptr, &paint.rainbow, BoolDisplay::OnOff);
				sub->draw_option<toggle_number_option<float, bool>>("Shadow", nullptr, &paint.shadow, &paint.shadow_value, 0.1f, 50.f, 0.1f);
				sub->draw_option<number<std::int32_t>>("Red", nullptr, &paint.r, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Green", nullptr, &paint.g, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Blue", nullptr, &paint.b, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<float>>("Brightness", nullptr, &paint.brightness, 0.1f, 1000.f, 1.f);
				sub->draw_option<number<float>>("Range", nullptr, &paint.range, 0.1f, 1000.f, 0.1f);
			});
		g_Render->draw_submenu<sub>(("Entity Shooter"), EntityShooter, [](sub* sub)
			{

				sub->draw_option<submenu>("Entity", nullptr, EntityShooterVehicle);
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &m_entity_shooter.enabled, BoolDisplay::OnOff);


			});
		g_Render->draw_submenu<sub>(("Entity"), EntityShooterVehicle, [](sub* sub)
			{
				sub->draw_option<KeyboardOption>(("Selected"), nullptr, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m_entity_shooter.selected_hash)), []
					{



					});
				sub->draw_option<UnclickOption>("List", nullptr, [] {});
				for (std::int32_t i = 0; i < 23; i++) {
					sub->draw_option<submenu>(get_vehicle_class_name(i), nullptr, EntityShooterSelectedClass, [=]
						{
							m_entity_shooter.selected_class = i;

						});

				}


			});
		g_Render->draw_submenu<sub>((get_vehicle_class_name(m_entity_shooter.selected_class)), EntityShooterSelectedClass, [](sub* sub)
			{
				if (g_GameFunctions->m_vehicle_hash_pool != nullptr) {
					for (std::int32_t i = 0; i < g_GameFunctions->m_vehicle_hash_pool->capacity; i++) {
						std::uint64_t info = g_GameFunctions->m_vehicle_hash_pool->get(i);
						if (info != NULL) {
							if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
								std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
								std::string model_ptr = (char*)((uintptr_t)info + 0x298);
								if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(MISC::GET_HASH_KEY(model_ptr.c_str())) == m_entity_shooter.selected_class) {
									std::stringstream ss;
									std::string make(make_ptr);
									std::string model(model_ptr);
									if (make[0] || model[0]) {
										make = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(make.c_str());
										model = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model.c_str());
										if (make != "NULL" && model != "NULL") {
											ss << make << " " << model;
										}
										else if (model != "NULL") {
											ss << model;
										}
										else {
											ss << "Unknown";
										}
									}

									sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(*(std::uint32_t*)(info + 0x18)))), nullptr, [=]
										{
											m_entity_shooter.selected_hash = (*(std::uint32_t*)(info + 0x18));

										});
								}
							}
						}
					}
				}
			});
		g_Render->draw_submenu<sub>(("Aimbot"), SubmenuAimbot, [](sub* sub)
			{
				//sub->draw_option<submenu>("Excludes", nullptr, SubmenuAimbotExcludes);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Bone", nullptr, &aimbot.bone, &aimbot.data);
				//sub->draw_option<toggle<bool>>(("FOV Circle"), nullptr, &g_Render->fov_circle, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &aimbot.enabled, BoolDisplay::OnOff, false, [] {
					if (!aimbot.enabled) {
						CAM::RENDER_SCRIPT_CAMS(false, true, 700, true, true, true);
						CAM::SET_CAM_ACTIVE(aimbot.aimcam, false);
						CAM::DESTROY_CAM(aimbot.aimcam, true);
					}
					});



			});
		g_Render->draw_submenu<sub>("Exclude", SubmenuAimbotExcludes, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Friends"), nullptr, &aimbot.excludes.friends, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Players"), nullptr, &aimbot.excludes.players, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Peds"), nullptr, &aimbot.excludes.peds, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Teammates"), nullptr, &aimbot.excludes.team, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Triggerbot"), SubmenuTriggerbot, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &triggerbot.enabled, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Disable When Ragdolling"), nullptr, &triggerbot.d1, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Disable When Reloading"), nullptr, &triggerbot.d2, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Exclude Friends"), nullptr, &triggerbot.exclude_friends, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Filter", nullptr, &triggerbot.filter, &triggerbot.filter_i);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Redirect To Bone", nullptr, &triggerbot.shoot_coords, &triggerbot.scoords_i);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &triggerbot.delay, 0, 5000, 50);


			});
		g_Render->draw_submenu<sub>(("Type"), SubmenuTargetMode, [](sub* sub)
			{

				for (std::uint32_t i = 0; i < 4; ++i) {
					sub->draw_option<RegularOption>((t_mode.data[i]), nullptr, [=]
						{

							target_c.change(i);


						});
				}




			});

		g_Render->draw_submenu<sub>(("Targeting Mode"), SubmenuTargetingMode, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &t_mode.data, &t_mode.init, false, SubmenuTargetMode);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						PLAYER::SET_PLAYER_TARGETING_MODE(t_mode.init);
					});



			});
		g_Render->draw_submenu<sub>(("Airstrike"), SubmenuAirstrike, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &airstrike.enabled, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Damage", nullptr, &airstrike.damage, 0, 1000);
				sub->draw_option<number<float>>("Height", nullptr, &airstrike.height, 0.15f, 250.f, 0.05f, 2);




			});
		g_Render->draw_submenu<sub>(("Damage Type"), SubmenuDamageTest, [](sub* sub)
			{

				for (std::uint32_t i = 0; i < 16; ++i) {
					sub->draw_option<RegularOption>((Lists::DamageList[i]), nullptr, [=]
						{

							damage_type.change(i);


						});
				}




			});
		g_Render->draw_submenu<sub>(("Multipliers"), SubmenuWeaponMultipliers, [](sub* sub)
			{
				auto weapon = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info;

				sub->draw_option<toggle<bool>>(("No Recoil"), nullptr, &features.no_recoil, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Damage Type", nullptr, &Lists::DamageList, &Lists::DamagePos, true, SubmenuDamageTest, []
					{
						eDamageType type;
						switch (Lists::DamagePos) {
						case 0:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Unknown;
							break;
						case 1:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::None;
							break;
						case 2:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Melee;
							break;
						case 3:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Bullet;
							break;
						case 4:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::BulletRubber;
							break;
						case 5:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Explosive;
							break;
						case 6:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Fire;
							break;
						case 7:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Collision;
							break;
						case 8:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Fall;
							break;
						case 9:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Drown;
							break;
						case 10:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Electric;
							break;
						case 11:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::BarbedWire;
							break;
						case 12:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::FireExtinguisher;
							break;
						case 13:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Smoke;
							break;
						case 14:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::WaterCannon;
							break;
						case 15:
							(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Tranquilizer;
							break;


						}



					});
				sub->draw_option<number<float>>("Accuracy Spread", nullptr, &weapon->m_accuracy_spread, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Accurate Mode Accuracy Modifier", nullptr, &weapon->m_accurate_mode_accuracy_modifier, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("RNG Accuracy", nullptr, &weapon->m_run_and_gun_accuracy, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("RNG Min Accuracy", nullptr, &weapon->m_run_and_gun_min_accuracy, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Recoil Accuracy Max", nullptr, &weapon->m_recoil_accuracy_max, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Recoil Error Time", nullptr, &weapon->m_recoil_error_time, -1000.f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Recoil Recovery Rate", nullptr, &weapon->m_recoil_recovery_rate, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Recoil Accuracy To Allow Headshot AI", nullptr, &weapon->m_recoil_accuracy_to_allow_headshot_ai, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Min Headshot Distance AI", nullptr, &weapon->m_min_headshot_distance_ai, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Max Headshot Range AI", nullptr, &weapon->m_max_headshot_distance_ai, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Headshot Damage Modifie AIr", nullptr, &weapon->m_headshot_damage_modifier_ai, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Recoil Accuracy To Allow Headshot Player ", nullptr, &weapon->m_recoil_accuracy_to_allow_headshot_player, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Min Headshot Distance Player", nullptr, &weapon->m_min_headshot_distance_player, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Max Headshot Distance Player", nullptr, &weapon->m_max_headshot_distance_player, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Headshot Damage Modifier Player", nullptr, &weapon->m_headshot_damage_modifier_player, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Damage", nullptr, &weapon->m_damage, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Damage Time", nullptr, &weapon->m_damage_time, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Damage Time In Vehicle", nullptr, &weapon->m_damage_time_in_vehicle, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Damage Time In Vehicle Headshot", nullptr, &weapon->m_damage_time_in_vehicle_headshot, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Hit Limbs Damage Modifier", nullptr, &weapon->m_hit_limbs_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Network Hit Limbs Damage Modifier", nullptr, &weapon->m_network_hit_limbs_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Lightly Armoured Damage Modifier", nullptr, &weapon->m_lightly_armoured_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Vehicle Damage Modifier", nullptr, &weapon->m_vehicle_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Force", nullptr, &weapon->m_force, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Force On Ped", nullptr, &weapon->m_force_on_ped, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Force On Vehicle", nullptr, &weapon->m_force_on_vehicle, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Force On Heli", nullptr, &weapon->m_force_on_heli, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Force Max Strength Multiplier", nullptr, &weapon->m_force_max_strength_mult, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Force Falloff Range Start", nullptr, &weapon->m_force_falloff_range_start, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Force Falloff Range End", nullptr, &weapon->m_force_falloff_range_end, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Force Falloff Range Min", nullptr, &weapon->m_force_falloff_range_min, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Project Force", nullptr, &weapon->m_project_force, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Frag Impulse", nullptr, &weapon->m_frag_impulse, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Penetration", nullptr, &weapon->m_penetration, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Vertical Launch Ajustment", nullptr, &weapon->m_vertical_launch_adjustment, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Speed", nullptr, &weapon->m_speed, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Batch Spread", nullptr, &weapon->m_batch_spread, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<std::uint32_t>>("Bullets In Batch", nullptr, &weapon->m_bullets_in_batch, 0, 1000);
				sub->draw_option<number<float>>("Reload Time MP", nullptr, &weapon->m_reload_time_mp, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Reload Time SP", nullptr, &weapon->m_reload_time_sp, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Vehicle Reload Time", nullptr, &weapon->m_vehicle_reload_time, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Animation Reload Time", nullptr, &weapon->m_anim_reload_time, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Time Betweeen Shots", nullptr, &weapon->m_time_between_shots, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Time Left Between Shots", nullptr, &weapon->m_time_left_between_shots_where_should_fire_is_cached, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Spinup Time", nullptr, &weapon->m_spinup_time, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Spin Time", nullptr, &weapon->m_spin_time, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Spin Down Time", nullptr, &weapon->m_spindown_time, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Alternate Wait Time", nullptr, &weapon->m_alternate_wait_time, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Network Player Damage Modifier", nullptr, &weapon->m_network_player_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Network Ped Damage Modifier", nullptr, &weapon->m_network_ped_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Network Headshot Modifier", nullptr, &weapon->m_network_headshot_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Lock On Range", nullptr, &weapon->m_lock_on_range, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Weapon Range", nullptr, &weapon->m_weapon_range, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("AI Sound Range", nullptr, &weapon->m_ai_sound_range, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("AI Potential Blast Event Range", nullptr, &weapon->m_ai_potential_blast_event_range, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Damage Fall Off Range Min", nullptr, &weapon->m_damage_fall_off_range_min, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Damage Fall Off Range Max", nullptr, &weapon->m_damage_fall_off_range_max, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Damage Fall Off Modifier", nullptr, &weapon->m_damage_fall_off_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Min Time Between Recoil Shakes", nullptr, &weapon->m_min_time_between_recoil_shakes, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Recoil Shake Amplitude", nullptr, &weapon->m_recoil_shake_amplitude, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Explosion Shake Amplitude (Actual Recoil)", nullptr, &weapon->m_explosion_shake_amplitude, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Camera FOV", nullptr, &weapon->m_camera_fov, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("First Person Aim Fov Min", nullptr, &weapon->m_first_person_aim_fov_min, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("First Person Aim Fov Max", nullptr, &weapon->m_first_person_aim_fov_max, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("First Person Scope FOV", nullptr, &weapon->m_first_person_scope_fov, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("First Person Scope Attachment FOV", nullptr, &weapon->m_first_person_scope_attachment_fov, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Reticule Hud Position X", nullptr, &weapon->m_reticule_hud_position.x, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Reticule Hud Position Y", nullptr, &weapon->m_reticule_hud_position.y, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Reticule Hud Position POV Turret X", nullptr, &weapon->m_reticule_hud_position_pov_turret.x, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Reticule Hud Position POV Turret Y", nullptr, &weapon->m_reticule_hud_position_pov_turret.y, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Reticule Min Size Standing", nullptr, &weapon->m_reticule_min_size_standing, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Reticule Min Size Crouched", nullptr, &weapon->m_reticule_min_size_crouched, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Reticule Size", nullptr, &weapon->m_reticule_scale, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("HUD Range", nullptr, &weapon->m_hud_range, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Aiming Breathing Additive Weight", nullptr, &weapon->m_aiming_breathing_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Firing Breathing Additive Weight", nullptr, &weapon->m_firing_breathing_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Stealth Aiming Breathing Additive Weight", nullptr, &weapon->m_stealth_aiming_breathing_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Stealth Firing Breathing Additive Weight", nullptr, &weapon->m_stealth_firing_breathing_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Aiming Lean Additive Weight", nullptr, &weapon->m_aiming_lean_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Firing Lean Additive Weight", nullptr, &weapon->m_firing_lean_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Stealth Aiming Lean Additive Weight", nullptr, &weapon->m_stealth_aiming_lean_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->draw_option<number<float>>("Stealth Firing Lean Additive Weight", nullptr, &weapon->m_stealth_firing_lean_additive_weight, 0.0f, 1000.f, 0.1f, 1);



			});
		g_Render->draw_submenu<sub>(("Gun Locker"), SubmenuGunLocker, [](sub* sub)
			{
				sub->draw_option<submenu>("Ammo", nullptr, SubmenuGunLockerAmmo);
				sub->draw_option<submenu>("Give", nullptr, SubmenuGunLockerGive);



			});
		g_Render->draw_submenu<sub>(("Give"), SubmenuGunLockerGive, [](sub* sub)
			{
				int Maxammo = 0;

				if (give_weapon.type_int != 0) {
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), all_weapons.hash_all[give_weapon.type_int], &Maxammo);
				}
				if (give_weapon.type_int == 0) {
					Maxammo = 9999;
				}

				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &all_weapons.name_all, &give_weapon.type_int);
				sub->draw_option<number<std::int32_t>>("Ammo", nullptr, &give_weapon.amount, 1, Maxammo);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						if (give_weapon.type_int != 0) {
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), all_weapons.hash_all[give_weapon.type_int], 9999, false);
						}
						if (give_weapon.type_int == 0) {
							for (int x = 0; x < 106; x++) {
								WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), all_weapons.hash[x], give_weapon.amount, false);
							}
						}
					});

			});
		g_Render->draw_submenu<sub>(("Ammo"), SubmenuGunLockerAmmo, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &give_ammo.type, &give_ammo.type_int);
				if (give_ammo.type_int == 1) {
					Hash weaponhash;
					int Maxammo = 0;
					WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), weaponhash, &Maxammo);
					sub->draw_option<number<std::int32_t>>("Amount", nullptr, &give_ammo.amount, 1, Maxammo);
				}
				else {
					sub->draw_option<number<std::int32_t>>("Amount", nullptr, &give_ammo.amount, 1, 9999);

				}
				sub->draw_option<RegularOption>(("Give"), nullptr, []
					{
						if (give_ammo.type_int == 0) {
							std::uint32_t wephashes[89]
							{ 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
							0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
							0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
							0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
							0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A };
							for (int x = 0; x < 89; x++) {
								WEAPON::ADD_AMMO_TO_PED(PLAYER::PLAYER_PED_ID(), wephashes[x], give_ammo.amount);
							}
						}
						if (give_ammo.type_int == 1) {
							Hash weaponhash;
							WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
							WEAPON::ADD_AMMO_TO_PED(PLAYER::PLAYER_PED_ID(), weaponhash, give_ammo.amount);
						}
					});

			});
		g_Render->draw_submenu<sub>(("Animation"), SubmenuWeaponAnimation, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &animation_type, &animation_int);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						WEAPON::SET_WEAPON_ANIMATION_OVERRIDE(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY(animation_data[animation_int]));
					});

			});
		g_Render->draw_submenu<sub>(("Rapid Fire"), SubmenuRapidFire, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &rapid_fire.enabled, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Disable When Reloading"), nullptr, &rapid_fire.disable_when_reloading, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Disable Shooting"), nullptr, &rapid_fire.disable_shooting, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Only When Aiming"), nullptr, &rapid_fire.only_when_aiming, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &rapid_fire.delay, 0, 5000, 50);

			});
		g_Render->draw_submenu<sub>(("Explosive Ammo"), SubmenuExplosiveAmmo, [](sub* sub)
			{
				sub->draw_option<submenu>("Blame", nullptr, Submenu::SubmenuBlameExplosiveAmmo);
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &explosiveAmmo.enabled, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Sound"), nullptr, &explosiveAmmo.sound, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Invisible"), nullptr, &explosiveAmmo.invisible, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &explosiveAmmo.explode_type, &explosiveAmmo.explode_int);
				sub->draw_option<number<float>>("Damage", nullptr, &explosiveAmmo.damage, 0.0f, 150.f, 0.10f, 2);
				sub->draw_option<number<float>>("Camera Shake", nullptr, &explosiveAmmo.camera_shake, 0.0f, 150.f, 0.10f, 2);

			});
		g_Render->draw_submenu<sub>("Blame", SubmenuBlameExplosiveAmmo, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &explosiveAmmo.blame, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Player List"), nullptr, [] {});

				if (!explosiveAmmo.blame) {
					return;
				}
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{

						std::string name = PLAYER::GET_PLAYER_NAME(i);
						if (i == PLAYER::PLAYER_ID())
							name.append(" ~p~[Self]");

						if (i == explosiveAmmo.blamed_person)
							name.append(" ~b~[Selected]");
						if (INTERIOR::GET_INTERIOR_FROM_ENTITY(ped) == 0) {
							sub->draw_option<RegularOption>((name.c_str()), nullptr, [=]
								{
									explosiveAmmo.blamed_person = i;
								});
						}
					}
				}
			});
		g_Render->draw_submenu<sub>(("Network"), SubmenuNetwork, [](sub* sub)
			{
				sub->draw_option<submenu>("Player List", nullptr, SubmenuPlayerList);
				sub->draw_option<submenu>("Modder Detection", nullptr, SubmenuAntiCheat);
				sub->draw_option<submenu>("Spoofing", nullptr, SubmenuSpoofing);
				//sub->draw_option<submenu>("Friends", nullptr, SubmenuFriends);
				sub->draw_option<submenu>("Recovery", nullptr, SubmenuRecovery);
				sub->draw_option<submenu>("Requests", nullptr, SubmenuRequests);
				sub->draw_option<submenu>("Session Starter", nullptr, SubmenuSesStart);
				//sub->draw_option<submenu>("RID Joiner", nullptr, SubmenuRIDJoiner); need to be fixed
				sub->draw_option<submenu>("Notifications", nullptr, SubmenuNotifcations);
				sub->draw_option<submenu>("Chat", nullptr, SubmenuChat);
				sub->draw_option<submenu>("Team", nullptr, SubmenuTeam);
				sub->draw_option<submenu>("Off The Radar", nullptr, SubmenuOffRadar);
				sub->draw_option<submenu>("Freemode Events", nullptr, rage::joaat("FreemodeEvent"));
				sub->draw_option<submenu>("Heist Control", nullptr, HeistControl);
				sub->draw_option<submenu>("Matchmaking", nullptr, rage::joaat("Matchmaking"));
				sub->draw_option<toggle<bool>>(("No Idle Kick"), nullptr, &features.no_idle_kick, BoolDisplay::OnOff);
				sub->draw_option<RegularOption>(("Force Script Host"), nullptr, [=]
					{

						g_FiberPool.queue([=] {
							force_host(rage::joaat("freemode"));

							force_host(rage::joaat("fmmc_launcher"));

							});
					});
			});
		g_Render->draw_submenu<sub>("Matchmaking", rage::joaat("Matchmaking"), [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("Max Players", nullptr, &max_players, 0, 32, 1, 3, true, "", "", [] {
					NETWORK::NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX(0, max_players);
					});
				sub->draw_option<number<std::int32_t>>("Max Spectators", nullptr, &max_spectators, 0, 32, 1, 3, true, "", "", [] {
					NETWORK::NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX(4, max_spectators);
					});
			});
		g_Render->draw_submenu<sub>("Freemode Events", rage::joaat("FreemodeEvent"), [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Max Criminal Damage"), nullptr, [=]
					{

						if (auto criminal_damage = find_script_thread(rage::joaat("am_criminal_damage")))
							*script_local(criminal_damage->m_stack, am_criminal_damage::score_idx).as<int*>() = 999'999'999;
					});
			});
		g_Render->draw_submenu<sub>("Friends", SubmenuFriends, [](sub* sub)
			{
				static auto friendReg = g_GameVariables->m_friendRegistry;



				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});

				for (int32_t i = 0; i < friendReg->m_friend_count; i++)
				{
					if (sub->GetSelectedOption() == sub->GetNumOptions()) {
						g_players.draw_friend_info(i);
					}
					if (friendReg->m_friends[i]->m_name != " ") {
						char make[128];
						sprintf(make, "%s %s", friendReg->m_friends[i]->m_name, getFriendStateStr(friendReg->m_friends[i]->m_friend_state, friendReg->m_friends[i]->m_is_joinable).c_str());
						sub->draw_option<submenu>(make, nullptr, SubmenuSelectedFriend, [=]
							{
								SelectedFriend = i;
							});

					}

				}

			});
		g_Render->draw_submenu<sub>(g_GameVariables->m_friendRegistry->m_friends[SelectedFriend]->m_name, SubmenuSelectedFriend, [](sub* sub)
			{
				sub->draw_option<RegularOption>("Join", "", [] {
					rid_toolkit.join(g_GameVariables->m_friendRegistry->m_friends[SelectedFriend]->m_rockstar_id);
					});


			});
		g_Render->draw_submenu<sub>("Heist Control", HeistControl, [](sub* sub)
			{
				sub->draw_option<submenu>("Diamond Casino", nullptr, DiamondCasino);
				sub->draw_option<submenu>("Cayo Perico", nullptr, rage::joaat("CayoPerico"));


			});
		g_Render->draw_submenu<sub>("Cayo Perico", rage::joaat("CayoPerico"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Target", nullptr, &Aproach3, &Opreracogh223, false, -1, [=] {
					switch (Opreracogh223) {
					case 0:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_TARGET"), 0, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_TARGET"), 0, true);
						break;
					case 1:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_TARGET"), 1, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_TARGET"), 1, true);
						break;
					case 2:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_TARGET"), 2, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_TARGET"), 2, true);
						break;
					case 3:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_TARGET"), 3, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_TARGET"), 3, true);
						break;
					case 4:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_TARGET"), 5, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_TARGET"), 5, true);
						break;
					}
					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Approach Vehicle", nullptr, &AproachVeh, &Opreracogh2232, false, -1, [=] {
					switch (Opreracogh223) {
					case 0:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_MISSIONS"), 65283, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_MISSIONS"), 65283, true);
						break;
					case 1:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_MISSIONS"), 65413, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_MISSIONS"), 65413, true);
						break;
					case 2:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_MISSIONS"), 65289, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_MISSIONS"), 65289, true);
						break;
					case 3:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_MISSIONS"), 65425, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_MISSIONS"), 65425, true);
						break;
					case 4:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_MISSIONS"), 65313, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_MISSIONS"), 65313, true);
						break;
					case 5:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_MISSIONS"), 65345, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_MISSIONS"), 65345, true);
						break;
					}
					});
				sub->draw_option<RegularOption>("Remove Cooldown", "", [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_TARGET_POSIX"), 1659643454, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_COOLDOWN"), 0, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_COOLDOWN_HARD"), 0, true);

					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_TARGET_POSIX"), 1659643454, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_COOLDOWN"), 0, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_COOLDOWN_HARD"), 0, true);
					});
				sub->draw_option<RegularOption>("Scope POIS", "", [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_BS_GEN"), -1, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_BS_ENTR"), 63, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_APPROAC"), -1, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_BS_GEN"), -1, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_BS_ENTR"), 63, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_APPROAC"), -1, true);
					});
				sub->draw_option<RegularOption>("Hard Mode", "Puts heist on hard mode.", [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_PROGRESS"), 131055, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_PROGRESS"), 131055, true);
					});
				sub->draw_option<UnclickOption>(("Teleports"), nullptr, [] {});
				sub->draw_option<RegularOption>("Main Dock", "", [] {
					PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 4947.496094, -5168.458008, 1.234270);
					});
				sub->draw_option<RegularOption>("Vault", "", [] {
					PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 4999.764160, -5747.863770, 14.840000);
					});
				sub->draw_option<RegularOption>("Communication Tower", "", [] {
					PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 5266.018555, -5427.736328, 64.297134);
					});
				sub->draw_option<RegularOption>("Power Station", "", [] {
					PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 4477.102539, -4597.295898, 4.283014);
					});
				sub->draw_option<RegularOption>("Exit", "", [] {
					PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 4990.778809, -5716.004395, 18.580210);
					});
			});
		g_Render->draw_submenu<sub>("Diamond Casino", DiamondCasino, [](sub* sub)
			{

				sub->draw_option<ChooseOption<const char*, std::size_t>>("Driver", nullptr, &Aproach2, &Opreracogh22, false, -1, [=] {
					switch (Opreracogh22) {
					case 0:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWDRIVER"), 5, true);
						break;
					case 1:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWDRIVER"), 3, true);
						break;
					case 2:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWDRIVER"), 2, true);
						break;
					case 3:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWDRIVER"), 4, true);
						break;
					case 4:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWDRIVER"), 1, true);
						break;
					}
					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Target", nullptr, &Aproach, &Opreracogh2, true, -1, [=] {
					switch (Opreracogh2) {
					case 0:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_TARGET"), 3, true);
						break;
					case 1:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_TARGET"), 1, true);
						break;
					case 2:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_TARGET"), 2, true);
						break;
					case 3:
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_TARGET"), 4, true);
						break;
					}
					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Teleport", nullptr, &casino_teleport, &casino_tp, false, -1, [=] {
					switch (casino_tp) {
					case 0:
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 2465.4746, -279.2276, -70.694145);
						break;
					case 1:
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 2515.1252, -238.91661, -70.73713);
						break;
					case 2:
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 917.24634, 48.989567, 80.89892);
						break;

					case 3:
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 2711.773, -369.458, -54.781);
						break;


					}


					});
				sub->draw_option<RegularOption>("Hard Mode", "Puts heist on hard mode.", [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3_HARD_APPROACH"), 3, true);
					});
				sub->draw_option<RegularOption>("Scope POIS", "", [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_POI"), 268435455, true);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_ACCESSPOINTS"), 2047, true);
					});


			});
		g_Render->draw_submenu<sub>("Recovery", SubmenuRecovery, [](sub* sub)
			{

				sub->draw_option<ChooseOption<const char*, std::size_t>>("Character", nullptr, &g_RecoveryManager.get_char_name, &g_RecoveryManager.selected, false, -1, [] {});
				sub->draw_option<submenu>("Level", nullptr, SubmenuRP);
				sub->draw_option<submenu>("Unlocks", nullptr, SubmenuUnlocks);

				sub->draw_option<submenu>("DLC", nullptr, SubmenuDLC);


				sub->draw_option<submenu>("Misc", nullptr, SubmenuRMisc);


				//sub->draw_option<submenu>("Money", nullptr, SubmenuMoney); not finished


				sub->draw_option<submenu>("Nightclub", nullptr, rage::joaat("Nightclub"));
				sub->draw_option<submenu>("ATM", nullptr, rage::joaat("ATM"));


				sub->draw_option<submenu>("Detected Methods", nullptr, SubmenuDEmeth);




				sub->draw_option<RegularOption>("Max Stats", "", []
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STAM"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STRN"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_LUNG"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_DRIV"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_FLY"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_SHO"), 100, 1);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STL"), 100, 1);
					});







			});




		g_Render->draw_submenu<sub>("ATM", rage::joaat("atm"), [](sub* sub)
			{
				script_global globalplayer_bd(2657589);
				script_global gpbd_fm_3(1894573);
				script_global gpbd_fm_1(1853910);
				auto& stats = gpbd_fm_1.as<GPBD_FM*>()->Entries[PLAYER::PLAYER_ID()].PlayerStats;
				static int max_bank = stats.Money - stats.WalletBalance;
				static int max_wallet = stats.WalletBalance;
				sub->draw_option<number<std::int32_t>>("Transfer To Wallet", nullptr, &features.transfer_to_wallet, 0, max_bank, 1, 3, false, "", "", [] {
					NETSHOPPING::NET_GAMESERVER_TRANSFER_BANK_TO_WALLET(g_RecoveryManager.selected, features.transfer_to_wallet);
				});
				sub->draw_option<number<std::int32_t>>("Transfer To Bank", nullptr, &features.transfer_to_bank, 0, max_wallet, 1, 3, false, "", "", [] {
					NETSHOPPING::NET_GAMESERVER_TRANSFER_WALLET_TO_BANK(g_RecoveryManager.selected, features.transfer_to_bank);
				});
				sub->draw_option<RegularOption>("Refresh", "Might take a few tries.", [=]
					{
						script_global gpbd_fm_12(1853910);
						auto& stats2 = gpbd_fm_12.as<GPBD_FM*>()->Entries[PLAYER::PLAYER_ID()].PlayerStats;
						features.transfer_to_wallet = 0;
						features.transfer_to_bank = 0;
						max_bank = stats2.Money - stats2.WalletBalance;
						max_wallet = stats2.WalletBalance;
					});
			});
		g_Render->draw_submenu<sub>("Money", SubmenuMoney, [](sub* sub)
			{



				sub->draw_option<RegularOption>("In testing atm", "", []
					{



					});

				//sub->draw_option<toggle<bool>>(("500k (Loop)"), nullptr, &features.Yes500k, BoolDisplay::OnOff);

			});



		g_Render->draw_submenu<sub>("Nightclub", rage::joaat("Nightclub"), [](sub* sub)
			{
				g_players.draw_info3();
				sub->draw_option<toggle<bool>>(("300k (Loop)"), nullptr, &features.nigthclub300k, BoolDisplay::OnOff);
				sub->draw_option<RegularOption>("300k", "", []
					{
						*script_global(262145 + 24045).as<int*>() = 300000;
						*script_global(262145 + 24041).as<int*>() = 300000;
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_POPULARITY"), 10000, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_PAY_TIME_LEFT"), -1, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_POPULARITY"), 100000, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLUB_POPULARITY"), 10000, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLUB_PAY_TIME_LEFT"), -1, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLUB_POPULARITY"), 100000, true);
					});
			});


		g_Render->draw_submenu<sub>("Misc", SubmenuRMisc, [](sub* sub)
			{


				sub->draw_option<RegularOption>("Allow Gender Change", "", [] {
					statSetInt("ALLOW_GENDER_CHANGE", -1);
					});

				sub->draw_option<RegularOption>("Increase Throwable Cap", "", [] {
					statSetBool("SR_INCREASE_THROW_CAP", true);
					});



				sub->draw_option<RegularOption>("Fast Run & Reload", "", [] {
					statSetInt("MP0_CHAR_ABILITY_1_UNLCK", -1);
					statSetInt("MP0_CHAR_ABILITY_2_UNLCK", -1);
					statSetInt("MP0_CHAR_ABILITY_3_UNLCK", -1);
					statSetInt("MP0_CHAR_FM_ABILITY_1_UNLCK", -1);
					statSetInt("MP0_CHAR_FM_ABILITY_2_UNLCK", -1);
					statSetInt("MP0_CHAR_FM_ABILITY_3_UNLCK", -1);

					//
					statSetInt("MP1_CHAR_ABILITY_1_UNLCK", -1);
					statSetInt("MP1_CHAR_ABILITY_2_UNLCK", -1);
					statSetInt("MP1_CHAR_ABILITY_3_UNLCK", -1);
					statSetInt("MP1_CHAR_FM_ABILITY_1_UNLCK", -1);
					statSetInt("MP1_CHAR_FM_ABILITY_2_UNLCK", -1);
					statSetInt("MP1_CHAR_FM_ABILITY_3_UNLCK", -1);


					});



				sub->draw_option<RegularOption>("Refill Snacks/Armour", "", [] {
					statSetInt("MP0_NO_BOUGHT_YUM_SNACKS", 30);
					statSetInt("MP0_NO_BOUGHT_HEALTH_SNACKS", 15);
					statSetInt("MP0_NO_BOUGHT_EPIC_SNACKS", 5);
					statSetInt("MP0_NUMBER_OF_CHAMP_BOUGHT", 5);
					statSetInt("MP0_NUMBER_OF_ORANGE_BOUGHT", 11);
					statSetInt("MP0_NUMBER_OF_BOURGE_BOUGHT", 10);
					statSetInt("MP0_NUMBER_OF_SPRUNK_BOUGHT", 10);
					statSetInt("MP0_CIGARETTES_BOUGHT", 20);

					statSetInt("MP0_MP_CHAR_ARMOUR_1_COUNT", 10);

					statSetInt("MP0_MP_CHAR_ARMOUR_2_COUNT", 10);
					statSetInt("MP0_MP_CHAR_ARMOUR_3_COUNT", 10);
					statSetInt("MP0_MP_CHAR_ARMOUR_4_COUNT", 10);
					statSetInt("MP0_MP_CHAR_ARMOUR_5_COUNT", 10);

					statSetInt("MP0_BREATHING_APPAR_BOUGHT", 20);

					//-----------
					statSetInt("MP1_NO_BOUGHT_YUM_SNACKS", 30);
					statSetInt("MP1_NO_BOUGHT_HEALTH_SNACKS", 15);
					statSetInt("MP1_NO_BOUGHT_EPIC_SNACKS", 5);
					statSetInt("MP1_NUMBER_OF_CHAMP_BOUGHT", 5);
					statSetInt("MP1_NUMBER_OF_ORANGE_BOUGHT", 11);
					statSetInt("MP1_NUMBER_OF_BOURGE_BOUGHT", 10);
					statSetInt("MP1_NUMBER_OF_SPRUNK_BOUGHT", 10);
					statSetInt("MP1_CIGARETTES_BOUGHT", 20);

					statSetInt("MP1_MP_CHAR_ARMOUR_1_COUNT", 10);

					statSetInt("MP1_MP_CHAR_ARMOUR_2_COUNT", 10);
					statSetInt("MP1_MP_CHAR_ARMOUR_3_COUNT", 10);
					statSetInt("MP1_MP_CHAR_ARMOUR_4_COUNT", 10);
					statSetInt("MP1_MP_CHAR_ARMOUR_5_COUNT", 10);

					statSetInt("MP1_BREATHING_APPAR_BOUGHT", 20);




					});


				// turn to masked
				sub->draw_option<RegularOption>("Stone Hatchet & Double", "", [] {
					statSetInt("MP0_GANGOPSPSTAT_INT102", 24, 8, 3);
					statSetInt("MP1_GANGOPSPSTAT_INT102", 24, 8, 3);

					statSetInt("MP1_GANGOPSPSTAT_INT102", 24, 8, 3);
					statSetInt("MP0_GANGOPSPSTAT_INT102", 24, 8, 3);


					statSetInt("MP0_GANGOPSPSTAT_INT102", 24, 8, 3);
					statSetInt("MP1_GANGOPSPSTAT_INT102", 0, 24, 8);

					statSetInt("MP1_GANGOPSPSTAT_INT102", 24, 8, 3);
					statSetInt("MP0_GANGOPSPSTAT_INT102", 0, 24, 8);

					// ----------------------

					statSetInt("MP0_MP_NGDLCPSTAT_INT0", 16, 8, 5);
					statSetInt("MP1_MP_NGDLCPSTAT_INT0", 16, 8, 5);

					statSetInt("MP0_MP_NGDLCPSTAT_INT0", 5, 16, 8);
					statSetInt("MP1_MP_NGDLCPSTAT_INT0", 5, 16, 8);


					});


				sub->draw_option<RegularOption>("Casino", "", [] {
					statSetBool("AWD_LEADER", true);
					statSetBool("AWD_SURVIVALIST", true);
					statSetBool("AWD_SUPPORTING_ROLE", true);
					});






				sub->draw_option<RegularOption>("Max Shooting Range", "", [] {
					statSetInt("SR_HIGHSCORE_1", 690);
					statSetInt("SR_HIGHSCORE_2", 1860);
					statSetInt("SR_HIGHSCORE_3", 2690);
					statSetInt("SR_HIGHSCORE_4", 2660);
					statSetInt("SR_HIGHSCORE_5", 2650);
					statSetInt("SR_HIGHSCORE_6", 450);
					statSetInt("SR_TARGETS_HIT", 269);
					statSetInt("SR_WEAPON_BIT_SET", -1);
					statSetBool("SR_TIER_1_REWARD", true);
					statSetBool("SR_TIER_3_REWARD", true);
					statSetBool("SR_INCREASE_THROW_CAP", true);
					});







				sub->draw_option<RegularOption>("Remove Badsport", "", []
					{
						Any date[12];
						STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MPPLY_CHAR_IS_BADSPORT "), false, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), false, true);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), false, true);
						STATS::STAT_SET_DATE(MISC::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_DT"), &date[0], 7, true);
					});











			});





		g_Render->draw_submenu<sub>("Detected Methods", SubmenuDEmeth, [](sub* sub)
			{


				sub->draw_option<RegularOption>("1bil Hangar Sell ", "", []
					{
						switch (g_RecoveryManager.selected) {
						case 0:
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PROP_HANGAR_VALUE"), 1999000000, true);
							break;
						case 1:
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PROP_HANGAR_VALUE"), 1999000000, true);
							break;
						}
						*script_global(262145 + 1574918).as<int*>() = 1999000000;
					});


				sub->draw_option<RegularOption>("1bil Nightclub Sell ", "", []
					{
						switch (g_RecoveryManager.selected) {
						case 0:
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PROP_NIGHTCLUB_VALUE"), 1999000000, true);
							break;
						case 1:
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PROP_NIGHTCLUB_VALUE"), 1999000000, true);
							break;
						}
						*script_global(262145 + 1574918).as<int*>() = 1999000000;
					});


				sub->draw_option<RegularOption>("1bil Arcade Sell ", "", []
					{
						switch (g_RecoveryManager.selected) {
						case 0:
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PROP_ARCADE_VALUE"), 1999000000, true);
							break;
						case 1:
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PROP_ARCADE_VALUE"), 1999000000, true);
							break;
						}
						*script_global(262145 + 1574918).as<int*>() = 1999000000;
					});



			});



		g_Render->draw_submenu<sub>("DLC", SubmenuDLC, [](sub* sub)
			{




				sub->draw_option<RegularOption>("Valentine", "", []
					{
						*script_global(262145 + 6856).as<int64_t*>() = 1; //TURN_ON_VALENTINES_EVENT
						*script_global(262145 + 11819).as<int64_t*>() = 1; //TURN_ON_VALENTINE_WEAPON"
						*script_global(262145 + 11820).as<int64_t*>() = 1;//TURN_ON_VALENTINE_VEHICLE
						*script_global(262145 + 11821).as<int64_t*>() = 1; //TURN_ON_VALENTINE_MASKS
						*script_global(262145 + 11822).as<int64_t*>() = 1; //TURN_ON_VALENTINE_HAIR"
						*script_global(262145 + 11823).as<int64_t*>() = 1; //TURN_ON_VALENTINE_CLOTHING"
						*script_global(262145 + 13185).as<int64_t*>() = 1; //TURN_ON_VALENTINE_2016_CLOTHING"
						*script_global(262145 + 13186).as<int64_t*>() = 1; //TURN_ON_VALENTINE_2016_VEHICLE"
					});


				sub->draw_option<RegularOption>("Halloween", "Will able you buy facepaints & others", []
					{
						*script_global(262145 + 11785).as<int64_t*>() = 1; //turn_on_halloween_event"
						*script_global(262145 + 11825).as<int64_t*>() = 1; //enable_heist_masks_halloween"
						*script_global(262145 + 11830).as<int64_t*>() = 1; //turn_on_halloween_vehicles"
						*script_global(262145 + 11831).as<int64_t*>() = 1; //turn_on_halloween_masks"
						*script_global(262145 + 11832).as<int64_t*>() = 1; //turn_on_halloween_facepaint"
						*script_global(262145 + 11834).as<int64_t*>() = 1; //turn_on_halloween_bobbleheads"
						*script_global(262145 + 11840).as<int64_t*>() = 1; //turn_on_halloween_clothing"
						*script_global(262145 + 11841).as<int64_t*>() = 1; //turn_on_halloween_weapons"
						*script_global(262145 + 11842).as<int64_t*>() = 1; //turn_on_halloween_horns"
						*script_global(262145 + 11848).as<int64_t*>() = 1; //TURN_ON_HALLOWEEN_ANIMS"
						*script_global(262145 + 12491).as<int64_t*>() = 1; //TURN_ON_HALLOWEEN_SOUNDS"
						*script_global(262145 + 17287).as<int64_t*>() = 1; //enable_biker_sanctus"
					});




				sub->draw_option<RegularOption>("Independance Day", "", []
					{
						*script_global(262145 + 8051).as<int64_t*>() = 1; //toggle_activate_independence_pack"
						*script_global(262145 + 8056).as<int64_t*>() = 1; //INDEPENDENCE_DAY_FIREWORKS_TYPE_1"
						*script_global(262145 + 8057).as<int64_t*>() = 1; //INDEPENDENCE_DAY_FIREWORKS_TYPE_2"
						*script_global(262145 + 8058).as<int64_t*>() = 1; //INDEPENDENCE_DAY_FIREWORKS_TYPE_3"
						*script_global(262145 + 8059).as<int64_t*>() = 1; //INDEPENDENCE_DAY_FIREWORKS_TYPE_4"
						*script_global(262145 + 8060).as<int64_t*>() = 1; //independence_day_deactivate_fireworks_launcher"
						*script_global(262145 + 8061).as<int64_t*>() = 1; //independence_day_deactivate_placed_fireworks"
						*script_global(262145 + 8064).as<int64_t*>() = 1; //DISABLEFIREWORKS"
						*script_global(262145 + 8065).as<int64_t*>() = 1; //Toggle_activate_Western_sovereign"
						*script_global(262145 + 8066).as<int64_t*>() = 1; //Toggle_activate_Monster_truck"
						*script_global(262145 + 8067).as<int64_t*>() = 1; //CLOTHING_INDEPENDENCEDAY_GROUP"
						*script_global(262145 + 8068).as<int64_t*>() = 1; //HAIR_MAKEUP_INDEPENDENCEDAY_GROUP"
						*script_global(262145 + 8069).as<int64_t*>() = 1; //MASKS_INDEPENDENCEDAY_MASKS_GROUP"
						*script_global(262145 + 8070).as<int64_t*>() = 1; //vehicle_independenceday_monster"
						*script_global(262145 + 8071).as<int64_t*>() = 1; //vehicle_independenceday_sovereign"
						*script_global(262145 + 8072).as<int64_t*>() = 1; //vehiclekit_independenceday_patriot_tire_smoke"
						*script_global(262145 + 8073).as<int64_t*>() = 1; //vehiclekit_independenceday_horn_1"
						*script_global(262145 + 8074).as<int64_t*>() = 1; //vehiclekit_independenceday_horn_2"
						*script_global(262145 + 8075).as<int64_t*>() = 1; //vehiclekit_independenceday_horn_3"
						*script_global(262145 + 8076).as<int64_t*>() = 1; //vehiclekit_independenceday_horn_4"
						*script_global(262145 + 8077).as<int64_t*>() = 1; //weapons_independenceday_musket"
						*script_global(262145 + 8078).as<int64_t*>() = 1; //weapons_independenceday_musket_ammo"
						*script_global(262145 + 8079).as<int64_t*>() = 1; //weapons_independenceday_fireworklauncher"
						*script_global(262145 + 8080).as<int64_t*>() = 1; //weapons_independenceday_fireworklauncher_ammo"
						*script_global(262145 + 8081).as<int64_t*>() = 1; //weapons_independenceday_patriot_parachute_smoke"

						*script_global(262145 + 8089).as<int64_t*>() = 1; //Pisswasser" Beer Hat"			
						*script_global(262145 + 8090).as<int64_t*>() = 1; //Benedict" Beer Hat
						*script_global(262145 + 8091).as<int64_t*>() = 1; //J Lager" Beer Hat
						*script_global(262145 + 8092).as<int64_t*>() = 1; //Patriot" Beer Hat
						*script_global(262145 + 8093).as<int64_t*>() = 1; //Blarneys" Beer Hat
						*script_global(262145 + 8094).as<int64_t*>() = 1; //Supa Wet" Beer Hat
						*script_global(262145 + 8095).as<int64_t*>() = 1; //Statue of Happiness T-shirt"
					});




				sub->draw_option<RegularOption>("Christmas 2014-2022", "", []
					{
						//*script_global(262145 + 4723).as<int64_t*>() = 1; //Turn On Snow
						*script_global(262145 + 4734).as<int64_t*>() = 1; //Toggle xmas content
						*script_global(262145 + 9184).as<int64_t*>() = 1; //disable_snowballs"
						*script_global(262145 + 9185).as<int64_t*>() = 1; //DISABLE_CHRISTMAS_TREE_PERISHING_SQUARE_SNOW"
						*script_global(262145 + 9186).as<int64_t*>() = 1; // "DISABLE_CHRISTMAS_TREE_PERISHING_SQUARE"
						*script_global(262145 + 9187).as<int64_t*>() = 1; // "DISABLE_CHRISTMAS_TREE_APARTMENT"
						*script_global(262145 + 9188).as<int64_t*>() = 1; // "disable_christmas_clothing"
						*script_global(262145 + 9189).as<int64_t*>() = 1; // "disable_christmas_masks"
						*script_global(262145 + 9190).as<int64_t*>() = 1; // "disable_christmas_vehicles"
						*script_global(262145 + 9192).as<int64_t*>() = 1; // "max_number_of_snowballs
						*script_global(262145 + 9193).as<int64_t*>() = 1; // "pick_up_number_of_snowballs"

						*script_global(262145 + 9194).as<int64_t*>() = 1; // "VEHICLE_XMAS14_DINKA_JESTER_RACECAR 	
						*script_global(262145 + 9195).as<int64_t*>() = 1; // "VEHICLE_XMAS14_DEWBAUCHEE_MASSACRO_RACECAR
						*script_global(262145 + 9196).as<int64_t*>() = 1; // "VEHICLE_XMAS14_RAT_TRUCK
						*script_global(262145 + 9197).as<int64_t*>() = 1; // "VEHICLE_XMAS14_SLAMVAN
						*script_global(262145 + 9198).as<int64_t*>() = 1; // "VEHICLE_XMAS14_BRAVADO_SPRUNK_BUFFALO
						*script_global(262145 + 9199).as<int64_t*>() = 1; // "VEHICLE_XMAS14_VAPID_PISSWASSER_DOMINATOR
						*script_global(262145 + 9200).as<int64_t*>() = 1; // "VEHICLE_XMAS14_BRAVADO_REDWOOD_GAUNTLET
						*script_global(262145 + 9201).as<int64_t*>() = 1; // "VEHICLE_XMAS14_DECLASSE_BURGER_SHOT_STALLION

						*script_global(262145 + 9202).as<int64_t*>() = 1; // "WEAPONS_XMAS14_HOMING_LAUNCHER	
						*script_global(262145 + 9203).as<int64_t*>() = 1; // "WEAPONS_XMAS14_HOMING_LAUNCHER_AMMO
						*script_global(262145 + 9204).as<int64_t*>() = 1; // "WEAPONS_XMAS14_PROXIMITY_MINE
						*script_global(262145 + 9205).as<int64_t*>() = 1; // "WEAPONS_XMAS14_BLACK_COMBAT_CHUTE_BAG
						*script_global(262145 + 9206).as<int64_t*>() = 1; // "WEAPONS_XMAS14_GRAY_COMBAT_CHUTE_BAG
						*script_global(262145 + 9207).as<int64_t*>() = 1; // "WEAPONS_XMAS14_CHARCOAL_COMBAT_CHUTE_BAG
						*script_global(262145 + 9208).as<int64_t*>() = 1; // "WEAPONS_XMAS14_TAN_COMBAT_CHUTE_BAG
						*script_global(262145 + 9209).as<int64_t*>() = 1; // "WEAPONS_XMAS14_FOREST_COMBAT_CHUTE_BAG

						*script_global(262145 + 9210).as<int64_t*>() = 1; // "TATTOOS_XMAS14_SKULL_RIDER		
						*script_global(262145 + 9211).as<int64_t*>() = 1; // "TATTOOS_XMAS14_SPIDER_OUTLINE
						*script_global(262145 + 9212).as<int64_t*>() = 1; // "TATTOOS_XMAS14_SPIDER_COLOR
						*script_global(262145 + 9213).as<int64_t*>() = 1; // "TATTOOS_XMAS14_SNAKE_OUTLINE 
						*script_global(262145 + 9214).as<int64_t*>() = 1; // "TATTOOS_XMAS14_SNAKE_SHADED
						*script_global(262145 + 9215).as<int64_t*>() = 1; // "TATTOOS_XMAS14_CARP_OUTLINE
						*script_global(262145 + 9216).as<int64_t*>() = 1; // "TATTOOS_XMAS14_CARP_SHADED
						*script_global(262145 + 9217).as<int64_t*>() = 1; // "TATTOOS_XMAS14_LOS_MUERTOS
						*script_global(262145 + 9218).as<int64_t*>() = 1; // "TATTOOS_XMAS14_DEATH_BEFORE_DISHONOR
						*script_global(262145 + 9219).as<int64_t*>() = 1; // "TATTOOS_XMAS14_TIME_TO_DIE
						*script_global(262145 + 9220).as<int64_t*>() = 1; // "TATTOOS_XMAS14_ELECTRIC_SNAKE
						*script_global(262145 + 9221).as<int64_t*>() = 1; // "TATTOOS_XMAS14_ROARING_TIGER
						*script_global(262145 + 9222).as<int64_t*>() = 1; // "TATTOOS_XMAS14_8_BALL_SKULL
						*script_global(262145 + 9223).as<int64_t*>() = 1; // "TATTOOS_XMAS14_LIZARD
						*script_global(262145 + 9224).as<int64_t*>() = 1; // "TATTOOS_XMAS14_FLORAL_DAGGER
						*script_global(262145 + 9225).as<int64_t*>() = 1; // "TATTOOS_XMAS14_JAPANESE_WARRIOR
						*script_global(262145 + 9226).as<int64_t*>() = 1; // "TATTOOS_XMAS14_LOOSE_LIPS_OUTLINE
						*script_global(262145 + 9227).as<int64_t*>() = 1; // "TATTOOS_XMAS14_LOOSE_LIPS_COLOR
						*script_global(262145 + 9228).as<int64_t*>() = 1; // "TATTOOS_XMAS14_ROYAL_DAGGER_OUTLINE
						*script_global(262145 + 9229).as<int64_t*>() = 1; // "TATTOOS_XMAS14_ROYAL_DAGGER_COLOR
						*script_global(262145 + 9230).as<int64_t*>() = 1; // "TATTOOS_XMAS14_TIMES_UP_OUTLINE
						*script_global(262145 + 9231).as<int64_t*>() = 1; // "TATTOOS_XMAS14_TIMES_UP_COLOR
						*script_global(262145 + 9232).as<int64_t*>() = 1; // "TATTOOS_XMAS14_YOURE_NEXT_OUTLINE
						*script_global(262145 + 9233).as<int64_t*>() = 1; // "TATTOOS_XMAS14_YOURE_NEXT_COLOR
						*script_global(262145 + 9234).as<int64_t*>() = 1; // "TATTOOS_XMAS14_SNAKE_HEAD_OUTLINE
						*script_global(262145 + 9235).as<int64_t*>() = 1; // "TATTOOS_XMAS14_SNAKE_HEAD_COLOR
						*script_global(262145 + 9236).as<int64_t*>() = 1; // "TATTOOS_XMAS14_FUCK_LUCK_OUTLINE
						*script_global(262145 + 9237).as<int64_t*>() = 1; // "TATTOOS_XMAS14_FUCK_LUCK_COLOR
						*script_global(262145 + 9238).as<int64_t*>() = 1; // "TATTOOS_XMAS14_EXECUTIONER
						*script_global(262145 + 9239).as<int64_t*>() = 1; // "TATTOOS_XMAS14_BEAUTIFUL_DEATH

						//Bodysuits:
						*script_global(262145 + 23175).as<int64_t*>() = 1; //Bodysuit Green
						*script_global(262145 + 23176).as<int64_t*>() = 1; //Bodysuit Orange
						*script_global(262145 + 23177).as<int64_t*>() = 1; //Bodysuit Blue
						*script_global(262145 + 23178).as<int64_t*>() = 1; //Bodysuit Pink
						*script_global(262145 + 23179).as<int64_t*>() = 1; //Bodysuit Yellow

						//Free items :
						*script_global(262145 + 25482).as<int64_t*>() = 1; //Free Vapid Clique with Merry Cliquemas
						*script_global(262145 + 25483).as<int64_t*>() = 1; //Free Nagasaki Buzzard Attack Chopper
						*script_global(262145 + 25484).as<int64_t*>() = 1; //Free HVY Insurgent Pick - Up

						//Other gifts, items:
						*script_global(262145 + 8977).as<int64_t*>() = 1; // 2014_christmas_day_gift: exclusive stocking mask, firework launcher, etc.
						*script_global(262145 + 9240).as<int64_t*>() = 1; // 2014_christmas_eve_gift: firework launcher + 5 fireworks
						*script_global(262145 + 9241).as<int64_t*>() = 1; // 2014_new_years_eve_gift: firework launcher + 5 fireworks
						*script_global(262145 + 9242).as<int64_t*>() = 1; // 2014_new_years_day_gift: firework launcher + 5 fireworks
						*script_global(262145 + 12499).as<int64_t*>() = 1; // "XMAS2015_VEHICLE"
						*script_global(262145 + 23180).as<int64_t*>() = 1; //full armor(holiday)
						*script_global(262145 + 23181).as<int64_t*>() = 1; //full sticky bombs(holiday)
						*script_global(262145 + 23182).as<int64_t*>() = 1; //full snacks(holiday)
						*script_global(262145 + 23183).as<int64_t*>() = 1; //full ammo(holiday)
						*script_global(262145 + 23971).as<int64_t*>() = 1; //Free RC Tank or idk what is this (-1029230616 hash from tuneables processing.c)

						//Christmas clothing :
						*script_global(262145 + 12500).as<int64_t*>() = 1; //Festive masks(2015)
						*script_global(262145 + 12502).as<int64_t*>() = 1; //Festive Pajamas(2015)
						*script_global(262145 + 19050).as<int64_t*>() = 1; // "christmas2016_clothing"
						*script_global(262145 + 22824).as<int64_t*>() = 1; // "christmas2017_clothing"

						//2015:
						*script_global(262145 + 12605).as<int64_t*>() = 1; // 2015_christmas_eve_gift: fireworks launcher, fireworks
						*script_global(262145 + 12606).as<int64_t*>() = 1; // 2015_new_years_eve_gift: fireworks launcher, fireworks
						*script_global(262145 + 12607).as<int64_t*>() = 1; // 2015_new_years_day_gift: fireworks launcher, fireworks
						*script_global(262145 + 12608).as<int64_t*>() = 1; // 2015_christmas_day_gift: abominable snowman mask, set of pajamas, naughty cap, etc.

						//2016 :
						*script_global(262145 + 18909).as<int64_t*>() = 1; // 2016_christmas_eve_gift
						*script_global(262145 + 18910).as<int64_t*>() = 1; // 2016_new_years_eve_gift
						*script_global(262145 + 18911).as<int64_t*>() = 1; // 2016_new_years_day_gift
						*script_global(262145 + 18912).as<int64_t*>() = 1; // 2016_christmas_day_gift

						//2017:
						*script_global(262145 + 23202).as<int64_t*>() = 1; // 2017 christmas eve gift : odious krampus mask, black ammu - nation hoodie, etc.
						*script_global(262145 + 23203).as<int64_t*>() = 1; // 2017_new_years_eve_gift: hideous krampus mask, vivisection t - shirt, etc.
						*script_global(262145 + 23204).as<int64_t*>() = 1; // 2017_new_years_day_gift: fearsome krampus mask, fake dix white t - shirt, etc.
						*script_global(262145 + 23205).as<int64_t*>() = 1; // 2017_christmas_day_gift: heinous krampus mask, one free albany hermes, etc.

						//2018:
						*script_global(262145 + 25486).as<int64_t*>() = 1; // 2018_christmas_eve_gift: black & white bones festive sweater, firework launcher, etc.
						*script_global(262145 + 25487).as<int64_t*>() = 1; // 2018_new_years_eve_gift: black & red bones festive sweater, one free hvy insurgent pick - up, etc.
						*script_global(262145 + 25488).as<int64_t*>() = 1; // 2018_new_years_day_gift: red bones festive sweater, firework launcher, etc.
						*script_global(262145 + 25489).as<int64_t*>() = 1; // 2018_christmas_day_gift: slasher festive sweater, one free vapid clique, up - n - atomizer, etc.

						//2019:
						*script_global(262145 + 28338).as<int64_t*>() = 1; // 2019_christmas_eve_gift: green reindeer lights bodysuit, firework launcher, etc.
						*script_global(262145 + 28339).as<int64_t*>() = 1; // 2019_new_years_eve_gift: yellow reindeer lights bodysuit, firework launcher, etc.
						*script_global(262145 + 28340).as<int64_t*>() = 1; // 2019_new_years_day_gift: neon festive lights bodysuit, firework launcher, etc.
						*script_global(262145 + 28341).as<int64_t*>() = 1; // 2019_christmas_day_gift: minigun sweater, festive lights bodysuit, firework launcher, etc.

						//2020:

						*script_global(262145 + 30536).as<int64_t*>() = 1; // 2020_christmas_eve_gift: vibrant stitch emissive mask, firework launcher, etc.

						//2021:
						*script_global(262145 + 31382).as<int64_t*>() = 1; // 2021_chrtismas_day_gift
						*script_global(262145 + 31383).as<int64_t*>() = 1; // 2021_new_years_gift





						//Crashes for some reason

						//2022:


						//*script_global(262145 + 33794).as<int64_t*>() = 1;

						//*script_global(262145 + 34044).as<int64_t*>() = 1;


						//*script_global(262145 + 34043).as<int64_t*>() = 1;


						//*script_global(262145 + 34045).as<int64_t*>() = 1;



					});




			});



		g_Render->draw_submenu<sub>("Unlocks", SubmenuUnlocks, [](sub* sub)
			{


				sub->draw_option<RegularOption>("All", "", [] {

					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 1);



					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONNAV"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 25, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);



					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONNAV"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 25, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);





					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_ENEMYDRIVEBYKILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_USJS_FOUND"), 50, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMWINALLRACEMODES"), 1, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMWINEVERYGAMEMODE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_DB_PLAYER_KILLS"), 1000, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_KILLS_PLAYERS"), 1000, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMHORDWAVESSURVIVE"), 21, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_TDM_MVP"), 60, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_HOLD_UP_SHOPS"), 20, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_RACES_WON"), 101, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_NO_ARMWRESTLING_WINS"), 21, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMATTGANGHQ"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMBBETWIN"), 50000, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 51, 1);
					STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMFULLYMODDEDCAR"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_DM_TOTALKILLS"), 500, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_DM_TOTAL_DEATHS"), 412, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PLAYER_HEADSHOTS"), 623, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 63, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_TDM_WINS"), 13, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_GTA_RACES_WON"), 12, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_GOLF_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_TENNIS_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TENNIS_MATCHES_WON"), 2, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_WON"), 101, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_LOST"), 36, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_25_KILLS_STICKYBOMBS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_50_KILLS_GRENADES"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_20_KILLS_MELEE"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PISTOL50_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_APPISTOL_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MICROSMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CMBTMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTMG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PUMP_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SAWNOFF_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_BULLPUP_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_HVYSNIPER_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_RPG_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MINIGUNS_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SMKGRENADE_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_STKYBMB_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TORSO"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_DECL"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TORSO"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_DECL"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TEETH"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_REV_DA_IN_POSSESSION"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MPPLY_VEHICLE_ID_ADMIN_WEB"), 117401876, 1);



					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);

					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SHOOTING_ABILITY"), 150, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SHOOTING_ABILITY"), 15000, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SHOOTING_ABILITY"), 1000, 0);


					});




				sub->draw_option<RegularOption>("LSC/Vehicle", "", [] {

					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONNAV"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 25, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);

					/// ----------------


					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMRALLYWONDRIVE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMRALLYWONNAV"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMWINSEARACE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMWINAIRRACE"), 1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_WIN_CAPTURES"), 25, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FINISH_HEISTS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);

					});



				sub->draw_option<RegularOption>("Tattoos", "", [] {

					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_8"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_9"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_10"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_11"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_tattoo_fm_unlocks_12"), -1, 1);

					//----------------------------

					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_7"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_8"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_9"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_10"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_11"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_tattoo_fm_unlocks_12"), -1, 1);
					});


				sub->draw_option<RegularOption>("Haircuts", "", [] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);


					// --------------


					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 1);



					});


				sub->draw_option<RegularOption>("Weapons", "", [] {

					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MOLOTOV _ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);





					// -------------------

					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MOLOTOV _ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PISTOL50_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_APPISTOL_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MICROSMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CMBTMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTMG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PUMP_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SAWNOFF_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_BULLPUP_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_HVYSNIPER_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_RPG_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MINIGUNS_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SMKGRENADE_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_STKYBMB_ENEMY_KILLS"), 600, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 0);
					});




				sub->draw_option<RegularOption>("Trophies", "", [] {
					STATS::STAT_SET_INT(0x53c59a8e, -1, 1);
					STATS::STAT_SET_INT(0x796d2d6a, 25, 1);
					STATS::STAT_SET_INT(0xd5d5279d, 25, 1);
					STATS::STAT_SET_INT(0xe00c1321, 100, 1);
					STATS::STAT_SET_INT(0x723f39d6, 4, 1);
					STATS::STAT_SET_INT(0x653a8f83, 4, 1);
					STATS::STAT_SET_INT(0x45e1432a, 5, 1);
					STATS::STAT_SET_INT(0xe9e500bc, 5, 1);
					STATS::STAT_SET_INT(0x833d3192, 10, 1);
					STATS::STAT_SET_INT(0x12f3b311, 20, 1);
					STATS::STAT_SET_INT(0x25ed089e, 255, 1);
					STATS::STAT_SET_INT(0x7bd82f11, 1000, 1);
					STATS::STAT_SET_FLOAT(0xb14148de, 1000, 1);
					STATS::STAT_SET_INT(0x69a50e0d, 2147483647, 1);
					STATS::STAT_SET_INT(0xa24ba69a, 4, 1);
					STATS::STAT_SET_INT(0x1fa36d2, 4, 1);
					STATS::STAT_SET_INT(0xeecca992, 5, 1);
					STATS::STAT_SET_INT(0x34c1f2c1, 5, 1);
					STATS::STAT_SET_INT(0x18f27d05, 10, 1);
					STATS::STAT_SET_INT(0x36177f20, 20, 1);
					STATS::STAT_SET_INT(0x5eaa0099, 255, 1);
					STATS::STAT_SET_INT(0xf21f4859, 1000, 1);
					STATS::STAT_SET_FLOAT(0x361609bc, 1000, 1);
					STATS::STAT_SET_INT(0x5873796d, 2147483647, 1);
					});




				sub->draw_option<RegularOption>("All Achievements", "", [] {
					PLAYER::GIVE_ACHIEVEMENT_TO_PLAYER;
					STATS::STAT_SET_INT(0x53c59a8e, -1, 1); // MPPLY_HEIST_ACH_TRACKER
					STATS::STAT_SET_INT(0x796d2d6a, 25, 1); // MPPLY_AWD_FM_CR_DM_MADE
					STATS::STAT_SET_INT(0xd5d5279d, 25, 1); // MPPLY_AWD_FM_CR_RACES_MADE
					STATS::STAT_SET_INT(0xe00c1321, 100, 1); // MPPLY_AWD_FM_CR_PLAYED_BY_PEEP
					Hash StatsBools[] =
					{
						// MP0_AWD_FM_GOLF_HOLE_IN_1 MP0_AWD_FM_SHOOTRANG_GRAN_WON MP0_AWD_FM_TENNIS_STASETWIN MP0_AWD_FM6DARTCHKOUT MP0_AWD_FMATTGANGHQ
						0x22d9626f, 0x2bfe2b98, 0xcca40e6,  0xb6c51652, 0x49e3d35b,
						// MP0_AWD_BUY_EVERY_GUN MP0_AWD_FMWINEVERYGAMEMODE MP0_AWD_FM25DIFFERENTDM MP0_AWD_FM_TENNIS_5_SET_WINS MP0_AWD_FM25DIFFERENTRACES
						0x21f81ca1, 0xbdda53b4, 0x59de4ddc, 0x69e7c068, 0xb4f06c2f,
						// MP0_AWD_FM25DIFITEMSCLOTHES MP0_AWD_FMFULLYMODDEDCAR MP0_AWD_FMKILL3ANDWINGTARACE MP0_AWD_FMKILLSTREAKSDM MP0_AWD_FMMOSTKILLSGANGHIDE
						0x9ba12d14, 0xe9472bb4, 0x43d56fad, 0x3099c3fe, 0x5941fbad,
						// MP0_AWD_FMMOSTKILLSSURVIVE MP0_AWD_FMRACEWORLDRECHOLDER MP0_AWD_FMPICKUPDLCCRATE1ST MP0_AWD_FMWINCUSTOMRACE MP0_MP0_AWD_FMWINALLRACEMODES
						0xc41b8767, 0x655e0bad, 0x2ae837e4, 0x71212ddf, 0xda28ebe4,
						// MP0_AWD_FMTATTOOALLBODYPARTS
						0xe3520842
					};
					for (Hash h : StatsBools)
						STATS::STAT_SET_BOOL(h, 1, 1);
					STATS::STAT_SET_INT(0x723f39d6, 4, 1); // MP0_AWD_PASSENGERTIME
					STATS::STAT_SET_INT(0x653a8f83, 4, 1); // MP0_AWD_TIME_IN_HELICOPTER
					STATS::STAT_SET_INT(0x45e1432a, 5, 1); // MP0_MOST_FLIPS_IN_ONE_JUMP
					STATS::STAT_SET_INT(0xe9e500bc, 5, 1); // MP0_MOST_SPINS_IN_ONE_JUMP
					STATS::STAT_SET_INT(0x833d3192, 10, 1); // MP0_AWD_FMHORDWAVESSURVIVE
					STATS::STAT_SET_INT(0x12f3b311, 20, 1); // MP0_AWD_HOLD_UP_SHOPS
					Hash Stats25[] =
					{
						// MP0_AWD_CAR_BOMBS_ENEMY_KILLS MP0_AWD_FM_GOLF_WON MP0_AWD_FM_SHOOTRANG_CT_WON MP0_AWD_FM_SHOOTRANG_RT_WON MP0_AWD_FM_SHOOTRANG_TG_WON
						0xaae88a2f, 0xe847156c, 0x741f0838, 0xeac04cce, 0x898dab76, 0x1AF2DE9E, 0xA1787290, 0x5F76739A, 0x2C177BAD,
						// MP0_AWD_FM_TENNIS_WON MP0_AWD_SECURITY_CARS_ROBBED MP0_AWD_LAPDANCES MP0_MOST_ARM_WRESTLING_WINS MP0_AWD_NO_HAIRCUTS
						0xe51a03e4, 0x5413e4e9, 0x4314583e, 0xd9da214e, 0xa43c7aac, 0xEC234AE2, 0x46533E0C, 0xF29D01D9, 0x3EDE081C, 0xC55AAFAA,
						// MP0_AWD_WIN_AT_DARTS MP0_AWD_FM_GOLF_BIRDIES MP0_AWD_FM_TENNIS_ACE MP0_AWD_PARACHUTE_JUMPS_20M MP0_AWD_PARACHUTE_JUMPS_50M
						0x279625d2, 0x978c6413, 0x7036f468, 0x1e3139c0, 0xd95051b7, 0x61F5DB39, 0x786E5B58, 0xAE352AA3, 0xAFBB09A3, 0x2F6C1441,
						// MP0_AIR_LAUNCHES_OVER_40M MP0_AWD_FMCRATEDROPS MP0_AWD_FMKILLBOUNTY MP0_AWD_FMSHOOTDOWNCOPHELI MP0_AWD_FMRALLYWONDRIVE
						0x8a8786e7, 0x2671fd3,  0xfb6b31f1, 0xee270322, 0xbb5b1a96, 0xE7939C0B, 0x144E7D9F, 0x4F6CDED8, 0xF5EDCABA, 0xB43E0E1A,
						// MP0_AWD_FMRALLYWONNAV MP0_AWD_FMWINAIRRACE MP0_AWD_FMWINRACETOPOINTS MP0_AWD_FMWINSEARACE MP0_AWD_FMBASEJMP
						0x6ae2181d, 0x40bf1a36, 0xa11bb5b6, 0xc5c0f286, 0xe54057bd, 0xB1590553, 0x16F2FD31, 0x5A1942E7, 0x58857E4, 0xFA2E93FF,
						// MP0_AWD_FM_RACE_LAST_FIRST MP0_AWD_FM_RACES_FASTEST_LAP
						0x25609da9, 0xc13d4f3a, 0x3A2621D6, 0xE751F17 };




					});

				sub->draw_option<RegularOption>("Hidden Liverys", "", [] {
					statSetInt("XMASLIVERIES0", -1);
					statSetInt("XMASLIVERIES1", -1);
					statSetInt("XMASLIVERIES2", -1);
					statSetInt("XMASLIVERIES3", -1);
					statSetInt("XMASLIVERIES4", -1);
					statSetInt("XMASLIVERIES5", -1);
					statSetInt("XMASLIVERIES6", -1);
					statSetInt("XMASLIVERIES7", -1);
					statSetInt("XMASLIVERIES8", -1);
					statSetInt("XMASLIVERIES9", -1);
					statSetInt("XMASLIVERIES10", -1);
					statSetInt("XMASLIVERIES11", -1);
					statSetInt("XMASLIVERIES12", -1);
					statSetInt("XMASLIVERIES13", -1);
					statSetInt("XMASLIVERIES14", -1);
					statSetInt("XMASLIVERIES15", -1);
					statSetInt("XMASLIVERIES16", -1);
					statSetInt("XMASLIVERIES17", -1);
					statSetInt("XMASLIVERIES18", -1);
					statSetInt("XMASLIVERIES19", -1);
					statSetInt("XMASLIVERIES20", -1);
					});

				sub->draw_option<RegularOption>("Speical T-Shirts", "", [] {
					*script_global(262145 + 20904).as<int64_t*>() = 1; // "BLACK_AMMUNATION_TEE"
					*script_global(262145 + 20906).as<int64_t*>() = 1; // "BLACK_COIL_TEE"
					*script_global(262145 + 20908).as<int64_t*>() = 1; // "BLACK_HAWK_AND_LITTLE_LOGO_TEE"
					*script_global(262145 + 20909).as<int64_t*>() = 1; // "BLACK_HAWK_AND_LITTLE_TEE"
					*script_global(262145 + 20913).as<int64_t*>() = 1; // "GREEN_VOM_FEUER_TEE"
					*script_global(262145 + 20916).as<int64_t*>() = 1; // "WHITE_AMMUNATION_TEE"
					*script_global(262145 + 20918).as<int64_t*>() = 1; // "WHITE_COIL_TEE"
					*script_global(262145 + 20920).as<int64_t*>() = 1; // "WHITE_HAWK_AND_LITTLE_TEE"
					*script_global(262145 + 20921).as<int64_t*>() = 1; // "WHITE_SHREWSBURY_TEE"
					*script_global(262145 + 20924).as<int64_t*>() = 1; // "WHITE_SHREWSBURY_LOGO_TEE"
					*script_global(262145 + 20928).as<int64_t*>() = 1; // "YELLOW_VOM_FEUER_LOGO_TEE"
					*script_global(262145 + 20929).as<int64_t*>() = 1; // "YELLOW_VOM_FEUER_TEE"
					*script_global(262145 + 20930).as<int64_t*>() = 1; // "YELLOW_WARSTOCK_TEE"
					*script_global(262145 + 20931).as<int64_t*>() = 1; // "BLUE_R*_CLASS_OF_98"
					*script_global(262145 + 20932).as<int64_t*>() = 1; // "RED_R*_CLASS_OF_98"
					*script_global(262145 + 20933).as<int64_t*>() = 1; // "NOISE_ROCKSTAR_LOGO_TEE"
					*script_global(262145 + 20934).as<int64_t*>() = 1; // "NOISE_TEE"
					*script_global(262145 + 20935).as<int64_t*>() = 1; // "RAZOR_TEE"
					*script_global(262145 + 20936).as<int64_t*>() = 1; // "BLACK_ROCKSTAR_CAMO"
					*script_global(262145 + 20937).as<int64_t*>() = 1; // "WHITE_ROCKSTAR_CAMO"
					*script_global(262145 + 20938).as<int64_t*>() = 1; // "KNUCKLEDUSTER_POCKET_TEE"
					*script_global(262145 + 20939).as<int64_t*>() = 1; // "ROCKSTAR_LOGO_BLACKED_OUT_TEE"
					*script_global(262145 + 20940).as<int64_t*>() = 1; // "ROCKSTAR_LOGO_WHITE_OUT_TEE"
					*script_global(262145 + 25377).as<int64_t*>() = 1; // "Kifflom Tee"
					*script_global(262145 + 25490).as<int64_t*>() = 1; // "Albany Tee"
					*script_global(262145 + 25491).as<int64_t*>() = 1; // "Albany Vintage Tee"
					*script_global(262145 + 25492).as<int64_t*>() = 1; // "Annis Tee"
					*script_global(262145 + 25493).as<int64_t*>() = 1; // "Benefector Tee"
					*script_global(262145 + 25494).as<int64_t*>() = 1; // "BF Tee"
					*script_global(262145 + 25495).as<int64_t*>() = 1; // "Bollokan Tee"
					*script_global(262145 + 25496).as<int64_t*>() = 1; // "Bravado Tee"
					*script_global(262145 + 25497).as<int64_t*>() = 1; // "Brute Tee"
					*script_global(262145 + 25498).as<int64_t*>() = 1; // "Buckingham Tee"
					*script_global(262145 + 25499).as<int64_t*>() = 1; // "Canis Tee"
					*script_global(262145 + 25500).as<int64_t*>() = 1; // "Chariot Tee"
					*script_global(262145 + 25501).as<int64_t*>() = 1; // "Cheval Tee"
					*script_global(262145 + 25502).as<int64_t*>() = 1; // "Classigue Tee"
					*script_global(262145 + 25503).as<int64_t*>() = 1; // "Coil Tee"
					*script_global(262145 + 25504).as<int64_t*>() = 1; // "Declasse Tee"
					*script_global(262145 + 25505).as<int64_t*>() = 1; // "Dewbauchee Tee"
					*script_global(262145 + 25506).as<int64_t*>() = 1; // "Dilettante Tee"
					*script_global(262145 + 25507).as<int64_t*>() = 1; // "Dinka Tee"
					*script_global(262145 + 25508).as<int64_t*>() = 1; // "Dundreary Tee"
					*script_global(262145 + 25509).as<int64_t*>() = 1; // "Emperor Tee"
					*script_global(262145 + 25510).as<int64_t*>() = 1; // "Enus Tee"
					*script_global(262145 + 25511).as<int64_t*>() = 1; // "Fathom Tee"
					*script_global(262145 + 25512).as<int64_t*>() = 1; // "Gallivanter Tee"
					*script_global(262145 + 25513).as<int64_t*>() = 1; // "Grotti Tee"
					*script_global(262145 + 25514).as<int64_t*>() = 1; // "Hijak Tee"
					*script_global(262145 + 25515).as<int64_t*>() = 1; // "HVT Tee"
					*script_global(262145 + 25516).as<int64_t*>() = 1; // "Imponte Tee"
					*script_global(262145 + 25517).as<int64_t*>() = 1; // "Invetero Tee"
					*script_global(262145 + 25518).as<int64_t*>() = 1; // "Jobuilt Tee"
					*script_global(262145 + 25519).as<int64_t*>() = 1; // "Karin Tee"
					*script_global(262145 + 25520).as<int64_t*>() = 1; // "Lampadati Tee"
					*script_global(262145 + 25521).as<int64_t*>() = 1; // "Maibatsu Tee"
					*script_global(262145 + 25522).as<int64_t*>() = 1; // "Mamba Tee"
					*script_global(262145 + 25523).as<int64_t*>() = 1; // "Mammoth Tee"
					*script_global(262145 + 25524).as<int64_t*>() = 1; // "MTL Tee"
					*script_global(262145 + 25525).as<int64_t*>() = 1; // "Obey Tee"
					*script_global(262145 + 25526).as<int64_t*>() = 1; // "Ocelot Tee"
					*script_global(262145 + 25527).as<int64_t*>() = 1; // "Overflod Tee"
					*script_global(262145 + 25528).as<int64_t*>() = 1; // "Pegassi Tee"
					*script_global(262145 + 25529).as<int64_t*>() = 1; // "Pfister Tee"
					*script_global(262145 + 25530).as<int64_t*>() = 1; // "Progen Tee"
					*script_global(262145 + 25531).as<int64_t*>() = 1; // "Rune Tee"
					*script_global(262145 + 25532).as<int64_t*>() = 1; // "Schyster Tee"
					*script_global(262145 + 25533).as<int64_t*>() = 1; // "Shitzu Tee"
					*script_global(262145 + 25534).as<int64_t*>() = 1; // "Truffade Tee"
					*script_global(262145 + 25535).as<int64_t*>() = 1; // "Ubermacht Tee"
					*script_global(262145 + 25536).as<int64_t*>() = 1; // "Vapid Tee"
					*script_global(262145 + 25537).as<int64_t*>() = 1; // "Vulcar Tee"
					*script_global(262145 + 25538).as<int64_t*>() = 1; // "Weeny Tee"
					*script_global(262145 + 25539).as<int64_t*>() = 1; // "Willard Tee"
					*script_global(262145 + 25540).as<int64_t*>() = 1; // "Albany Nostalgia Tee"
					*script_global(262145 + 25541).as<int64_t*>() = 1; // "Albany USA Tee"
					*script_global(262145 + 25542).as<int64_t*>() = 1; // "Albany Dealership Tee"
					*script_global(262145 + 25543).as<int64_t*>() = 1; // "Annis JPN Tee"
					*script_global(262145 + 25544).as<int64_t*>() = 1; // "BF Surfer Tee"
					*script_global(262145 + 25545).as<int64_t*>() = 1; // "Bollokan Prairie Tee"
					*script_global(262145 + 25546).as<int64_t*>() = 1; // "Bravado Stylized Tee"
					*script_global(262145 + 25547).as<int64_t*>() = 1; // "Brute Impregnable Tee"
					*script_global(262145 + 25548).as<int64_t*>() = 1; // "Brute Heavy Duty Tee"
					*script_global(262145 + 25549).as<int64_t*>() = 1; // "Buckingham Luxe Tee"
					*script_global(262145 + 25550).as<int64_t*>() = 1; // "Canis USA Tee"
					*script_global(262145 + 25551).as<int64_t*>() = 1; // "Canis American Legend Tee"
					*script_global(262145 + 25552).as<int64_t*>() = 1; // "Canis Wolf Tee"
					*script_global(262145 + 25553).as<int64_t*>() = 1; // "Cheval Marshall Tee"
					*script_global(262145 + 25554).as<int64_t*>() = 1; // "Coil USA Tee"
					*script_global(262145 + 25555).as<int64_t*>() = 1; // "Coil Raiden Tee"
					*script_global(262145 + 25556).as<int64_t*>() = 1; // "Declasse Logo Tee"
					*script_global(262145 + 25557).as<int64_t*>() = 1; // "Declasse Girl Tee"

					//Festive Sweaters :
					*script_global(262145 + 25558).as<int64_t*>() = 1; // "Burger Shot Festive Sweater"
					*script_global(262145 + 25559).as<int64_t*>() = 1; // "Red Bleeder Festive Sweater"
					*script_global(262145 + 25560).as<int64_t*>() = 1; // "Blue Bleeder Festive Sweater"
					*script_global(262145 + 25561).as<int64_t*>() = 1; // "Blue Cluckin' Festive Sweater"
					*script_global(262145 + 25562).as<int64_t*>() = 1; // "Green Cluckin' Festive Sweater"
					*script_global(262145 + 25563).as<int64_t*>() = 1; // "Blue Slaying Festive Sweater"
					*script_global(262145 + 25564).as<int64_t*>() = 1; // "Green Slaying Festive Sweater"
					*script_global(262145 + 25565).as<int64_t*>() = 1; // "Hail Santa Festive Sweater"
					*script_global(262145 + 25566).as<int64_t*>() = 1; // "Merrry Sprunkmas Festive Sweater"
					*script_global(262145 + 25567).as<int64_t*>() = 1; // "Ice Cold Sprunk Festive Sweater"



					*script_global(262145 + 7980).as<int64_t*>() = 1; //UNLOCKBITCHNDOGFOODTSHIRTEVENT
					*script_global(262145 + 7981).as<int64_t*>() = 1; //UNLOCKVINYLCOUNTDOWNTSHIRTEVENT
					*script_global(262145 + 7982).as<int64_t*>() = 1; //UNLOCKHOMIESSHARPTSHIRTEVENT




					});


				sub->draw_option<RegularOption>("More Special T-Shirts", "", [] {
					//Brands Shirts :
					*script_global(262145 + 14971).as<int64_t*>() = 1; // "Accountant Shirt"
					*script_global(262145 + 14972).as<int64_t*>() = 1; // "Bahamamamas Shirt"
					*script_global(262145 + 14973).as<int64_t*>() = 1; // "Drone Shirt"
					*script_global(262145 + 14975).as<int64_t*>() = 1; // "Golf Shirt"
					*script_global(262145 + 14976).as<int64_t*>() = 1; // "Maisonette Shirt"
					*script_global(262145 + 14977).as<int64_t*>() = 1; // "Manopause Shirt"
					*script_global(262145 + 14979).as<int64_t*>() = 1; // "Pacific Bluffs Shirt"
					*script_global(262145 + 14980).as<int64_t*>() = 1; // "Prolaps Shirt"
					*script_global(262145 + 14981).as<int64_t*>() = 1; // "Tennis Shirt"
					*script_global(262145 + 14982).as<int64_t*>() = 1; // "Toe Shirt"
					*script_global(262145 + 14983).as<int64_t*>() = 1; // "Vanilla Unicorn Shirt"
					*script_global(262145 + 14984).as<int64_t*>() = 1; // "Marlowe Shirt"
					*script_global(262145 + 14985).as<int64_t*>() = 1; // "Crest Shirt"
					*script_global(262145 + 23973).as<int64_t*>() = 1; // "Crocs Bar T-Shirt"
					*script_global(262145 + 23974).as<int64_t*>() = 1; // "Base5 T-Shirt"
					*script_global(262145 + 23975).as<int64_t*>() = 1; // "BOBO T-Shirt"
					*script_global(262145 + 23976).as<int64_t*>() = 1; // "Bitch'n'Dog T-Shirt"
					*script_global(262145 + 23978).as<int64_t*>() = 1; // "Vivisection T-Shirt"
					*script_global(262145 + 23981).as<int64_t*>() = 1; // "Vinyl Countdown T-Shirt"
					*script_global(262145 + 23983).as<int64_t*>() = 1; // "Victory Fist T-Shirt"
					*script_global(262145 + 23986).as<int64_t*>() = 1; // "Homie Sharp T-Shirt"
					*script_global(262145 + 8095).as<int64_t*>() = 1; // "Statue of Happiness T-shirt"

					//Knock Offs T - shirts:
					*script_global(262145 + 23989).as<int64_t*>() = 1; // "Fake Perseus T-Shirt"
					*script_global(262145 + 23990).as<int64_t*>() = 1; // "Fake Santo Capra T-Shirt"
					*script_global(262145 + 23991).as<int64_t*>() = 1; // "Fake Dix White T-Shirt"
					*script_global(262145 + 23992).as<int64_t*>() = 1; // "Fake Le Chien Crew T-Shirt"
					*script_global(262145 + 23993).as<int64_t*>() = 1; // "Fake Enema T-Shirt"
					*script_global(262145 + 23994).as<int64_t*>() = 1; // "Fake Dix Gold T-Shirt"
					*script_global(262145 + 23995).as<int64_t*>() = 1; // "Fake Le Chien No2 T-Shirt"
					*script_global(262145 + 23996).as<int64_t*>() = 1; // "Fake Seesanta Nove T-Shirt"
					*script_global(262145 + 23997).as<int64_t*>() = 1; // "Fake Didier Sachs T-Shirt"
					*script_global(262145 + 23998).as<int64_t*>() = 1; // "Fake Vapid T-Shirt"

					//Manufactures:
					*script_global(262145 + 14975).as<int64_t*>() = 1; // "Grotti Shirt"
					*script_global(262145 + 17331).as<int64_t*>() = 1; // "Western Brand White Tee"
					*script_global(262145 + 17332).as<int64_t*>() = 1; // "Western Brand Black Tee"
					*script_global(262145 + 17333).as<int64_t*>() = 1; // "Western Logo White Tee"
					*script_global(262145 + 17334).as<int64_t*>() = 1; // "Western Logo Black Tee"
					*script_global(262145 + 17335).as<int64_t*>() = 1; // "Steel Horse Solid Logo Tee"
					*script_global(262145 + 17336).as<int64_t*>() = 1; // "Steel Horse Logo Tee"
					*script_global(262145 + 17337).as<int64_t*>() = 1; // "Steel Horse Brand White Tee"
					*script_global(262145 + 17338).as<int64_t*>() = 1; // "Steel Horse Brand Black Tee"
					*script_global(262145 + 17339).as<int64_t*>() = 1; // "Nagasaki White Tee"
					*script_global(262145 + 17340).as<int64_t*>() = 1; // "Nagasaki White And Red Tee"
					*script_global(262145 + 17341).as<int64_t*>() = 1; // "Nagasaki Black Tee"
					*script_global(262145 + 17342).as<int64_t*>() = 1; // "Purple Helmets Black Tee"
					*script_global(262145 + 17343).as<int64_t*>() = 1; // "Principe Black Tee"
					*script_global(262145 + 17344).as<int64_t*>() = 1; // "Steel Horse Black Hoodie"
					*script_global(262145 + 17345).as<int64_t*>() = 1; // "Steel Horse White Hoodie"
					*script_global(262145 + 17346).as<int64_t*>() = 1; // "Western Black Hoodie"
					*script_global(262145 + 17347).as<int64_t*>() = 1; // "Western White Hoodie"
					*script_global(262145 + 17348).as<int64_t*>() = 1; // "Nagasaki White Hoodie"
					*script_global(262145 + 17349).as<int64_t*>() = 1; // "Nagasaki White And Red Hoodie"
					*script_global(262145 + 17350).as<int64_t*>() = 1; // "Nagasaki Black Hoodie"
					*script_global(262145 + 17351).as<int64_t*>() = 1; // "Purple Helmets Black Hoodie"
					*script_global(262145 + 17352).as<int64_t*>() = 1; // "Principe Hoodie Black"

					//Movie shirts :
					*script_global(262145 + 11744).as<int64_t*>() = 1; // "MELTDOWN"
					*script_global(262145 + 11745).as<int64_t*>() = 1; // "VINEWOOD_ZOMBIE"
					*script_global(262145 + 11746).as<int64_t*>() = 1; // "I_MARRIED_MY_DAD"
					*script_global(262145 + 11747).as<int64_t*>() = 1; // "DIE_ALREADY_4"
					*script_global(262145 + 11748).as<int64_t*>() = 1; // "THE_SHOULDER_OF_ORION_II"
					*script_global(262145 + 11749).as<int64_t*>() = 1; // "NELSON_IN_NAPLES"
					*script_global(262145 + 11750).as<int64_t*>() = 1; // "THE_MANY_WIVES_OF_ALFREDO_SMITH"
					*script_global(262145 + 11751).as<int64_t*>() = 1; // "AN_AMERICAN_DIVORCE"
					*script_global(262145 + 11752).as<int64_t*>() = 1; // "THE_LONELIEST_ROBOT"
					*script_global(262145 + 11753).as<int64_t*>() = 1; // "CAPOLAVORO"
					*script_global(262145 + 12390).as<int64_t*>() = 1; // "Vinewood Zombie Shirt"
					*script_global(262145 + 12391).as<int64_t*>() = 1; // "Knife After Dark Shirt"
					*script_global(262145 + 12392).as<int64_t*>() = 1; // "The Simian Shirt"
					*script_global(262145 + 12393).as<int64_t*>() = 1; // "Zombie Liberals In The Midwest Shirt"
					*script_global(262145 + 12394).as<int64_t*>() = 1; // "Twilight Knife Shirt"
					*script_global(262145 + 12395).as<int64_t*>() = 1; // "Butchery and Other Hobbies Shirt"
					*script_global(262145 + 12396).as<int64_t*>() = 1; // "Cheerleader Massacre 3 Shirt"
					*script_global(262145 + 12397).as<int64_t*>() = 1; // "Cannibal Clown Shirt"
					*script_global(262145 + 12398).as<int64_t*>() = 1; // "Hot Serial Killer Stepmom Shirt"
					*script_global(262145 + 12399).as<int64_t*>() = 1; // "Splatter And Shot Shirt"
					*script_global(262145 + 12400).as<int64_t*>() = 1; // "Meathook For Mommy Shirt"
					*script_global(262145 + 12401).as<int64_t*>() = 1; // "Psycho Swingers Shirt"
					*script_global(262145 + 12402).as<int64_t*>() = 1; // "Vampires On The Beach Shirt"
					*script_global(262145 + 14978).as<int64_t*>() = 1; // "Meltdown Shirt

					//Radio Station T - shirts:
					*script_global(262145 + 23972).as<int64_t*>() = 1; // "Emotion 98.3 Radio T-Shirt"
					*script_global(262145 + 23977).as<int64_t*>() = 1; // "KJAH Radio T-Shirt"
					*script_global(262145 + 23979).as<int64_t*>() = 1; // "K-ROSE Radio T-Shirt"
					*script_global(262145 + 23980).as<int64_t*>() = 1; // "FLASH Radio T-Shirt"
					*script_global(262145 + 23982).as<int64_t*>() = 1; // "Fever 105 Radio T-Shirt"
					*script_global(262145 + 23984).as<int64_t*>() = 1; // "K-DST Radio T-Shirt"
					*script_global(262145 + 23985).as<int64_t*>() = 1; // "Bounce FM Radio T-Shirt"
					*script_global(262145 + 24497).as<int64_t*>() = 1; // "LS UR T-Shirt"
					*script_global(262145 + 24498).as<int64_t*>() = 1; // "Non-Stop-Pop FM T-Shirt"
					*script_global(262145 + 24499).as<int64_t*>() = 1; // "Radio Los Santos T-Shirt"
					*script_global(262145 + 24500).as<int64_t*>() = 1; // "Los Santos Rock Radio T-Shirt"
					*script_global(262145 + 24501).as<int64_t*>() = 1; // "Blonded Los Santos 97.8 FM T-Shirt"
					*script_global(262145 + 24502).as<int64_t*>() = 1; // "West Coast Talk Radio T-Shirt"
					*script_global(262145 + 24503).as<int64_t*>() = 1; // "Radio Mirror Park T-Shirt"
					*script_global(262145 + 24504).as<int64_t*>() = 1; // "Rebel Radio T-Shirt"
					*script_global(262145 + 24505).as<int64_t*>() = 1; // "Channel X T-Shirt"
					*script_global(262145 + 24506).as<int64_t*>() = 1; // "Vinewood Boulevard Radio T-Shirt"
					*script_global(262145 + 24507).as<int64_t*>() = 1; // "FlyLo FM T-Shirt"
					*script_global(262145 + 24508).as<int64_t*>() = 1; // "Space 103.2 T-Shirt"
					*script_global(262145 + 24509).as<int64_t*>() = 1; // "West Coast Classics T-Shirt"
					*script_global(262145 + 24510).as<int64_t*>() = 1; // "East Los FM T-Shirt"
					*script_global(262145 + 24511).as<int64_t*>() = 1; // "The Lab T-Shirt"
					*script_global(262145 + 24512).as<int64_t*>() = 1; // "The Lowdown 91.1 T-Shirt"
					*script_global(262145 + 24513).as<int64_t*>() = 1; // "WorldWide FM T-Shirt"
					*script_global(262145 + 24514).as<int64_t*>() = 1; // "Soulwax FM T-Shirt"
					*script_global(262145 + 24515).as<int64_t*>() = 1; // "Blue Ark T-Shirt"
					*script_global(262145 + 24516).as<int64_t*>() = 1; // "Blaine County Radio T-Shirt"

					//Clubs T - shirts:'
					*script_global(262145 + 24457).as<int64_t*>() = 1; // "Maisonette Los Santos T-Shirt"
					*script_global(262145 + 24458).as<int64_t*>() = 1; // "Studio Los Santos T-Shirt"
					*script_global(262145 + 24459).as<int64_t*>() = 1; // "Galaxy T-Shirt"
					*script_global(262145 + 24460).as<int64_t*>() = 1; // "Gefängnis T-Shirt"
					*script_global(262145 + 24461).as<int64_t*>() = 1; // "Omega T-Shirt"
					*script_global(262145 + 24462).as<int64_t*>() = 1; // "Technologie T-Shirt"
					*script_global(262145 + 24463).as<int64_t*>() = 1; // "Paradise T-Shirt"
					*script_global(262145 + 24464).as<int64_t*>() = 1; // "The Palace T-Shirt"
					*script_global(262145 + 24465).as<int64_t*>() = 1; // "Tony's Fun House T-Shirt"

					//DJ T - shirts:
					*script_global(262145 + 24672).as<int64_t*>() = 1; // "White Solomun Logo Tee"
					*script_global(262145 + 24673).as<int64_t*>() = 1; // "White Solomun Pocket Logo Tee"
					*script_global(262145 + 24674).as<int64_t*>() = 1; // "Black And Yellow Solomun Tee"
					*script_global(262145 + 24675).as<int64_t*>() = 1; // "Black Solomun White Logo Tee"
					*script_global(262145 + 24676).as<int64_t*>() = 1; // "Black And White Solomun Tee"
					*script_global(262145 + 24677).as<int64_t*>() = 1; // "Black Solomun Pocket Logo Tee"
					*script_global(262145 + 24678).as<int64_t*>() = 1; // "Dixon Box logo Tee"
					*script_global(262145 + 24679).as<int64_t*>() = 1; // "Dixon Pocket logo Tee"
					*script_global(262145 + 24680).as<int64_t*>() = 1; // "White Dixon Wilderness Tee"
					*script_global(262145 + 24681).as<int64_t*>() = 1; // "Dixon Green Logo Tee"
					*script_global(262145 + 24682).as<int64_t*>() = 1; // "Dixon Glitch Logo Tee"
					*script_global(262145 + 24683).as<int64_t*>() = 1; // "Black Dixon Repeated Logo Tee"
					*script_global(262145 + 24684).as<int64_t*>() = 1; // "Tale Of Us Box Logo Tee"
					*script_global(262145 + 24685).as<int64_t*>() = 1; // "White Tale Of Us Logo Tee"
					*script_global(262145 + 24686).as<int64_t*>() = 1; // "White Tale Of Us Emb. Tee"
					*script_global(262145 + 24687).as<int64_t*>() = 1; // "Black Tale Of Us 0Logo Tee"
					*script_global(262145 + 24688).as<int64_t*>() = 1; // "Tale Of Us Stacked Logo Tee"
					*script_global(262145 + 24689).as<int64_t*>() = 1; // "Tale Of Us Afterlight Tee"
					*script_global(262145 + 24690).as<int64_t*>() = 1; // "White The Black Madonna Tee"
					*script_global(262145 + 24691).as<int64_t*>() = 1; // "Black The Black Madonna Tee"
					*script_global(262145 + 24692).as<int64_t*>() = 1; // "White The Black Madonna Emb. Tee"
					*script_global(262145 + 24693).as<int64_t*>() = 1; // "White The Black Madonna Init. Tee"
					*script_global(262145 + 24694).as<int64_t*>() = 1; // "Black The Black Madonna Init. Tee"
					*script_global(262145 + 24695).as<int64_t*>() = 1; // "The Black Madonna We Believe Tee"



					*script_global(262145 + 20904).as<int64_t*>() = 1; // "BLACK_AMMUNATION_TEE"
					*script_global(262145 + 20906).as<int64_t*>() = 1; // "BLACK_COIL_TEE"
					*script_global(262145 + 20908).as<int64_t*>() = 1; // "BLACK_HAWK_AND_LITTLE_LOGO_TEE"
					*script_global(262145 + 20909).as<int64_t*>() = 1; // "BLACK_HAWK_AND_LITTLE_TEE"
					*script_global(262145 + 20913).as<int64_t*>() = 1; // "GREEN_VOM_FEUER_TEE"
					*script_global(262145 + 20916).as<int64_t*>() = 1; // "WHITE_AMMUNATION_TEE"
					*script_global(262145 + 20918).as<int64_t*>() = 1; // "WHITE_COIL_TEE"
					*script_global(262145 + 20920).as<int64_t*>() = 1; // "WHITE_HAWK_AND_LITTLE_TEE"
					*script_global(262145 + 20921).as<int64_t*>() = 1; // "WHITE_SHREWSBURY_TEE"
					*script_global(262145 + 20924).as<int64_t*>() = 1; // "WHITE_SHREWSBURY_LOGO_TEE"
					*script_global(262145 + 20928).as<int64_t*>() = 1; // "YELLOW_VOM_FEUER_LOGO_TEE"
					*script_global(262145 + 20929).as<int64_t*>() = 1; // "YELLOW_VOM_FEUER_TEE"
					*script_global(262145 + 20930).as<int64_t*>() = 1; // "YELLOW_WARSTOCK_TEE"
					*script_global(262145 + 20931).as<int64_t*>() = 1; // "BLUE_R*_CLASS_OF_98"
					*script_global(262145 + 20932).as<int64_t*>() = 1; // "RED_R*_CLASS_OF_98"
					*script_global(262145 + 20933).as<int64_t*>() = 1; // "NOISE_ROCKSTAR_LOGO_TEE"
					*script_global(262145 + 20934).as<int64_t*>() = 1; // "NOISE_TEE"
					*script_global(262145 + 20935).as<int64_t*>() = 1; // "RAZOR_TEE"
					*script_global(262145 + 20936).as<int64_t*>() = 1; // "BLACK_ROCKSTAR_CAMO"
					*script_global(262145 + 20937).as<int64_t*>() = 1; // "WHITE_ROCKSTAR_CAMO"
					*script_global(262145 + 20938).as<int64_t*>() = 1; // "KNUCKLEDUSTER_POCKET_TEE"
					*script_global(262145 + 20939).as<int64_t*>() = 1; // "ROCKSTAR_LOGO_BLACKED_OUT_TEE"
					*script_global(262145 + 20940).as<int64_t*>() = 1; // "ROCKSTAR_LOGO_WHITE_OUT_TEE"
					*script_global(262145 + 25377).as<int64_t*>() = 1; // "Kifflom Tee"


					});

				sub->draw_option<RegularOption>("Special Hoodies", "", [] {
					*script_global(262145 + 20903).as<int64_t*>() = 1; // "BLACK_AMMUNATION_HOODIE"
					*script_global(262145 + 20907).as<int64_t*>() = 1; // "BLACK_HAWK_AND_LITTLE_HODDIE"
					*script_global(262145 + 20910).as<int64_t*>() = 1; // "BLACK_SHREWSBURY_HOODIE"
					*script_global(262145 + 20912).as<int64_t*>() = 1; // "BLACK_WARSTOCK_HOODIE"
					*script_global(262145 + 20917).as<int64_t*>() = 1; // "WHITE_COIL_HOODIE"
					*script_global(262145 + 20919).as<int64_t*>() = 1; // "WHITE_HAWK_AND_LITTLE_HOODIE"
					*script_global(262145 + 20923).as<int64_t*>() = 1; // "WHITE_SHREWSBURY_HOODIE"
					*script_global(262145 + 20926).as<int64_t*>() = 1; // "WHITE_VOM_FEUER_HOODIE

					});




				sub->draw_option<RegularOption>("Special Hats", "", [] {
					*script_global(262145 + 20902).as<int64_t*>() = 1; //BLACK_AMMUNATION_CAP
					*script_global(262145 + 20905).as<int64_t*>() = 1; //BLACK_COIL_CAP
					*script_global(262145 + 20911).as<int64_t*>() = 1; //BLACK_VOM_FEUER_CAP
					*script_global(262145 + 20914).as<int64_t*>() = 1; //RED_HAWK_AND_LITTLE_CAP
					*script_global(262145 + 20915).as<int64_t*>() = 1; //WARSTOCK_CAP
					*script_global(262145 + 20922).as<int64_t*>() = 1; //WHITE_SHREWSBURY_CAP
					*script_global(262145 + 20925).as<int64_t*>() = 1; //WHITE_VOM_FEUER_CAP
					*script_global(262145 + 20927).as<int64_t*>() = 1; //WINE_COIL_CAP


					*script_global(262145 + 12380).as<int64_t*>() = 1; // "Magnetics Script Hat"
					*script_global(262145 + 12381).as<int64_t*>() = 1; // "Magnetics Block Hat"
					*script_global(262145 + 12382).as<int64_t*>() = 1; // "Los Santos Hat"
					*script_global(262145 + 12383).as<int64_t*>() = 1; // "Boars Hat"
					*script_global(262145 + 12384).as<int64_t*>() = 1; // "Benny's Hat"
					*script_global(262145 + 12385).as<int64_t*>() = 1; // "Westside Hat"
					*script_global(262145 + 12386).as<int64_t*>() = 1; // "Eastside Hat"
					*script_global(262145 + 12387).as<int64_t*>() = 1; // "Strawberry Hat"
					*script_global(262145 + 12388).as<int64_t*>() = 1; // "S.A. Hat"
					*script_global(262145 + 12389).as<int64_t*>() = 1; // "Davis Hat"



					});



				sub->draw_option<RegularOption>("Misc Outfits", "", [] {
					STATS::STAT_SET_BOOL(0x9cf3d019, 1, 1);
					STATS::STAT_SET_BOOL(0x45b6712, 1, 1);
					STATS::STAT_SET_INT(0x2ae837e4, 1, 1);
					STATS::STAT_SET_INT(0x833d3192, 10, 1);
					STATS::STAT_SET_INT(0x30418014, 100, 1);
					STATS::STAT_SET_INT(0xe2a9b0c4, 100, 1);
					STATS::STAT_SET_BOOL(0x59d644b9, 1, 1);
					STATS::STAT_SET_BOOL(0xa5f06324, 1, 1);
					STATS::STAT_SET_INT(0x3804231b, 1, 1);
					STATS::STAT_SET_INT(0x18f27d05, 10, 1);
					STATS::STAT_SET_INT(0x87b6d2d, 100, 1);
					STATS::STAT_SET_INT(0xe5e29eea, 100, 1);

					*script_global(262145 + 25490).as<int64_t*>() = 1; // "Albany Tee"
					*script_global(262145 + 25491).as<int64_t*>() = 1; // "Albany Vintage Tee"
					*script_global(262145 + 25492).as<int64_t*>() = 1; // "Annis Tee"
					*script_global(262145 + 25493).as<int64_t*>() = 1; // "Benefector Tee"
					*script_global(262145 + 25494).as<int64_t*>() = 1; // "BF Tee"
					*script_global(262145 + 25495).as<int64_t*>() = 1; // "Bollokan Tee"
					*script_global(262145 + 25496).as<int64_t*>() = 1; // "Bravado Tee"
					*script_global(262145 + 25497).as<int64_t*>() = 1; // "Brute Tee"
					*script_global(262145 + 25498).as<int64_t*>() = 1; // "Buckingham Tee"
					*script_global(262145 + 25499).as<int64_t*>() = 1; // "Canis Tee"
					*script_global(262145 + 25500).as<int64_t*>() = 1; // "Chariot Tee"
					*script_global(262145 + 25501).as<int64_t*>() = 1; // "Cheval Tee"
					*script_global(262145 + 25502).as<int64_t*>() = 1; // "Classigue Tee"
					*script_global(262145 + 25503).as<int64_t*>() = 1; // "Coil Tee"
					*script_global(262145 + 25504).as<int64_t*>() = 1; // "Declasse Tee"
					*script_global(262145 + 25505).as<int64_t*>() = 1; // "Dewbauchee Tee"
					*script_global(262145 + 25506).as<int64_t*>() = 1; // "Dilettante Tee"
					*script_global(262145 + 25507).as<int64_t*>() = 1; // "Dinka Tee"
					*script_global(262145 + 25508).as<int64_t*>() = 1; // "Dundreary Tee"
					*script_global(262145 + 25509).as<int64_t*>() = 1; // "Emperor Tee"
					*script_global(262145 + 25510).as<int64_t*>() = 1; // "Enus Tee"
					*script_global(262145 + 25511).as<int64_t*>() = 1; // "Fathom Tee"
					*script_global(262145 + 25512).as<int64_t*>() = 1; // "Gallivanter Tee"
					*script_global(262145 + 25513).as<int64_t*>() = 1; // "Grotti Tee"
					*script_global(262145 + 25514).as<int64_t*>() = 1; // "Hijak Tee"
					*script_global(262145 + 25515).as<int64_t*>() = 1; // "HVT Tee"
					*script_global(262145 + 25516).as<int64_t*>() = 1; // "Imponte Tee"
					*script_global(262145 + 25517).as<int64_t*>() = 1; // "Invetero Tee"
					*script_global(262145 + 25518).as<int64_t*>() = 1; // "Jobuilt Tee"
					*script_global(262145 + 25519).as<int64_t*>() = 1; // "Karin Tee"
					*script_global(262145 + 25520).as<int64_t*>() = 1; // "Lampadati Tee"
					*script_global(262145 + 25521).as<int64_t*>() = 1; // "Maibatsu Tee"
					*script_global(262145 + 25522).as<int64_t*>() = 1; // "Mamba Tee"
					*script_global(262145 + 25523).as<int64_t*>() = 1; // "Mammoth Tee"
					*script_global(262145 + 25524).as<int64_t*>() = 1; // "MTL Tee"
					*script_global(262145 + 25525).as<int64_t*>() = 1; // "Obey Tee"
					*script_global(262145 + 25526).as<int64_t*>() = 1; // "Ocelot Tee"
					*script_global(262145 + 25527).as<int64_t*>() = 1; // "Overflod Tee"
					*script_global(262145 + 25528).as<int64_t*>() = 1; // "Pegassi Tee"
					*script_global(262145 + 25529).as<int64_t*>() = 1; // "Pfister Tee"
					*script_global(262145 + 25530).as<int64_t*>() = 1; // "Progen Tee"
					*script_global(262145 + 25531).as<int64_t*>() = 1; // "Rune Tee"
					*script_global(262145 + 25532).as<int64_t*>() = 1; // "Schyster Tee"
					*script_global(262145 + 25533).as<int64_t*>() = 1; // "Shitzu Tee"
					*script_global(262145 + 25534).as<int64_t*>() = 1; // "Truffade Tee"
					*script_global(262145 + 25535).as<int64_t*>() = 1; // "Ubermacht Tee"
					*script_global(262145 + 25536).as<int64_t*>() = 1; // "Vapid Tee"
					*script_global(262145 + 25537).as<int64_t*>() = 1; // "Vulcar Tee"
					*script_global(262145 + 25538).as<int64_t*>() = 1; // "Weeny Tee"
					*script_global(262145 + 25539).as<int64_t*>() = 1; // "Willard Tee"
					*script_global(262145 + 25540).as<int64_t*>() = 1; // "Albany Nostalgia Tee"
					*script_global(262145 + 25541).as<int64_t*>() = 1; // "Albany USA Tee"
					*script_global(262145 + 25542).as<int64_t*>() = 1; // "Albany Dealership Tee"
					*script_global(262145 + 25543).as<int64_t*>() = 1; // "Annis JPN Tee"
					*script_global(262145 + 25544).as<int64_t*>() = 1; // "BF Surfer Tee"
					*script_global(262145 + 25545).as<int64_t*>() = 1; // "Bollokan Prairie Tee"
					*script_global(262145 + 25546).as<int64_t*>() = 1; // "Bravado Stylized Tee"
					*script_global(262145 + 25547).as<int64_t*>() = 1; // "Brute Impregnable Tee"
					*script_global(262145 + 25548).as<int64_t*>() = 1; // "Brute Heavy Duty Tee"
					*script_global(262145 + 25549).as<int64_t*>() = 1; // "Buckingham Luxe Tee"
					*script_global(262145 + 25550).as<int64_t*>() = 1; // "Canis USA Tee"
					*script_global(262145 + 25551).as<int64_t*>() = 1; // "Canis American Legend Tee"
					*script_global(262145 + 25552).as<int64_t*>() = 1; // "Canis Wolf Tee"
					*script_global(262145 + 25553).as<int64_t*>() = 1; // "Cheval Marshall Tee"
					*script_global(262145 + 25554).as<int64_t*>() = 1; // "Coil USA Tee"
					*script_global(262145 + 25555).as<int64_t*>() = 1; // "Coil Raiden Tee"
					*script_global(262145 + 25556).as<int64_t*>() = 1; // "Declasse Logo Tee"
					*script_global(262145 + 25557).as<int64_t*>() = 1; // "Declasse Girl Tee"


					*script_global(262145 + 25558).as<int64_t*>() = 1; // "Burger Shot Festive Sweater"
					*script_global(262145 + 25559).as<int64_t*>() = 1; // "Red Bleeder Festive Sweater"
					*script_global(262145 + 25560).as<int64_t*>() = 1; // "Blue Bleeder Festive Sweater"
					*script_global(262145 + 25561).as<int64_t*>() = 1; // "Blue Cluckin' Festive Sweater"
					*script_global(262145 + 25562).as<int64_t*>() = 1; // "Green Cluckin' Festive Sweater"
					*script_global(262145 + 25563).as<int64_t*>() = 1; // "Blue Slaying Festive Sweater"
					*script_global(262145 + 25564).as<int64_t*>() = 1; // "Green Slaying Festive Sweater"
					*script_global(262145 + 25565).as<int64_t*>() = 1; // "Hail Santa Festive Sweater"
					*script_global(262145 + 25566).as<int64_t*>() = 1; // "Merrry Sprunkmas Festive Sweater"
					*script_global(262145 + 25567).as<int64_t*>() = 1; // "Ice Cold Sprunk Festive Sweater"


					*script_global(262145 + 23175).as<int64_t*>() = 1; // "Green Wireframe Bodysuit"
					*script_global(262145 + 23176).as<int64_t*>() = 1; // "Orange Wireframe Bodysuit"
					*script_global(262145 + 23177).as<int64_t*>() = 1; // "Blue Wireframe Bodysuit"
					*script_global(262145 + 23178).as<int64_t*>() = 1; // "Pink Wireframe Bodysuit"
					*script_global(262145 + 23179).as<int64_t*>() = 1; // "Yellow Wireframe Bodysuit"

					//Stunt Suits :
					*script_global(262145 + 16590).as<int64_t*>() = 1; // "White Jock Cranley Suit"
					*script_global(262145 + 16591).as<int64_t*>() = 1; // "Blue Jock Cranley Suit"
					*script_global(262145 + 16592).as<int64_t*>() = 1; // "Red Jock Cranley Suit"
					*script_global(262145 + 16593).as<int64_t*>() = 1; // "Gold Jock Cranley Suit"
					*script_global(262145 + 16594).as<int64_t*>() = 1; // "Black Jock Cranley Suit"
					*script_global(262145 + 16595).as<int64_t*>() = 1; // "Pink Jock Cranley Suit"
					*script_global(262145 + 16596).as<int64_t*>() = 1; // "Silver Jock Cranley Suit"

					});


			});
		g_Render->draw_submenu<sub>("Level", SubmenuRP, [](sub* sub)
			{
				if (m_recovery.m_level.m_level > 8000) {
					m_recovery.m_level.m_level = 8000;
				}
				if (m_recovery.m_level.m_level < 1) {
					m_recovery.m_level.m_level = 1;
				}
				sub->draw_option<KeyboardOption>(("Value"), nullptr, std::to_string(m_recovery.m_level.m_level), []
					{
						showKeyboard("Enter Something", "", 4, &m_recovery.m_level.m_level_buffer, [] {


							m_recovery.m_level.m_level = atoi(m_recovery.m_level.m_level_buffer.c_str());

							});


					});
				sub->draw_option<RegularOption>("Apply", nullptr, []
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_SET_RP_GIFT_ADMIN"), m_recovery.m_level.Levels[m_recovery.m_level.m_level], true);
						Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_CHECK"  Change session for the level to apply." });
					});


			});
		g_Render->draw_submenu<sub>("Notifications", SubmenuNotifcations, [](sub* sub)
			{
				sub->draw_option<submenu>("Joining & Leaving", nullptr, SubmenuPlayerJoining);



			});
		g_Render->draw_submenu<sub>("Joining & Leaving", SubmenuPlayerJoining, [](sub* sub)
			{

				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &all_players.notifications.leaving_and_joining, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Log"), nullptr, &all_players.notifications.log, BoolDisplay::OnOff);



			});
		g_Render->draw_submenu<sub>("Modder Detection", SubmenuAntiCheat, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &antiCheat.enabled, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Checks"), nullptr, [] {});
				sub->draw_option<toggle<bool>>(("Godmode"), nullptr, &antiCheat.godmode, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Infinite Ammo"), nullptr, &antiCheat.infinite_ammo, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Infinite Clip"), nullptr, &antiCheat.infinite_ammo2, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Speed"), nullptr, &antiCheat.speed, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Fly"), nullptr, &antiCheat.fly, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Unobtainable Vehicle"), nullptr, &antiCheat.UnobtainableVehicle, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Scenarios"), nullptr, &antiCheat.scenarios, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Tiny Ped"), nullptr, &antiCheat.tiny_ped, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("No Ragdoll"), nullptr, &antiCheat.no_ragdoll, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Invalid Model"), nullptr, &antiCheat.invalidmodel, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Spoofing"), SubmenuSpoofing, [](sub* sub)
			{
				//sub->draw_option<submenu>("Information", nullptr, SubmenuInformation);
				sub->draw_option<submenu>("Game", nullptr, SubmenuGame);
				sub->draw_option<submenu>("Crew", nullptr, SubmenuCrew);
				sub->draw_option<toggle<bool>>(("QA Tester"), nullptr, &spoofing.qa_tester, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Information"), SubmenuInformation, [](sub* sub)
			{
				sub->draw_option<submenu>("IP", nullptr, SubmenuIP);

			});
		g_Render->draw_submenu<sub>(("Crew"), SubmenuCrew, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &spoofing.m_crew.enabled, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Members", nullptr, &spoofing.m_crew.member_count, 0, 5000);
				sub->draw_option<UnclickOption>(("Values"), nullptr, [] {});

				sub->draw_option<KeyboardOption>(("Name"), nullptr, spoofing.m_crew.name, []
					{
						showKeyboard("Enter Something", "", 10, &spoofing.m_crew.nameBuffer, [] {
							spoofing.m_crew.name = spoofing.m_crew.nameBuffer.c_str();
							});


					});
				sub->draw_option<KeyboardOption>(("Tag"), nullptr, spoofing.m_crew.tag.c_str(), []
					{
						showKeyboard("Enter Something", "", 4, &spoofing.m_crew.tag, [] {});


					});

			});
		g_Render->draw_submenu<sub>(("Game"), SubmenuGame, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Godmode"), nullptr, &spoofing.m_godmode, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Super Jump"), nullptr, &spoofing.m_superjump, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Spectating"), nullptr, &spoofing.spectating, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Respawning"), nullptr, &spoofing.respawning, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Seatbelt"), nullptr, &spoofing.seatbelt, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Team"), SubmenuTeam, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Override Restrictions"), nullptr, &team.override_restrictions, BoolDisplay::OnOff, false, [] {
					if (!team.override_restrictions) {
						NETWORK::NETWORK_OVERRIDE_TEAM_RESTRICTIONS(PLAYER::GET_PLAYER_TEAM(PLAYER::PLAYER_PED_ID()), false);
					}
					});
				sub->draw_option<toggle<bool>>(("Use Freemode Colour Instead Of Team"), nullptr, &team.use_player_colour_instead_of_team, BoolDisplay::OnOff, false, [] {
					if (!team.use_player_colour_instead_of_team) {
						NETWORK::USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(false);
					}
					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Team", nullptr, &team.type, &team.data, true, -1, [] {
					PLAYER::SET_PLAYER_TEAM(PLAYER::PLAYER_PED_ID(), team.data);
					});
				sub->draw_option<UnclickOption>(("Players"), nullptr, [] {});
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{
						if (PLAYER::GET_PLAYER_TEAM(ped) == 0) {
							std::string name = PLAYER::GET_PLAYER_NAME(i);
							name = "~r~" + name;
							if (i == PLAYER::PLAYER_ID())
								name.append(" ~p~[Self]");


							sub->draw_option<RegularOption>((name.c_str()), nullptr, [=]
								{

								});
						}
						if (PLAYER::GET_PLAYER_TEAM(ped) == 1) {
							std::string name = PLAYER::GET_PLAYER_NAME(i);
							name = "~b~" + name;
							if (i == PLAYER::PLAYER_ID())
								name.append(" ~p~[Self]");


							sub->draw_option<RegularOption>((name.c_str()), nullptr, [=]
								{

								});
						}
					}
				}


			});
		g_Render->draw_submenu<sub>(("Chat"), SubmenuChat, [](sub* sub)
			{
				sub->draw_option<submenu>("Spammer", nullptr, SubmenuSpammer);
				sub->draw_option<toggle<bool>>(("Team Only"), nullptr, &chat.team_only, BoolDisplay::OnOff, false, [] {
					if (!chat.team_only) {
						NETWORK::NETWORK_SET_TEAM_ONLY_CHAT(false);
					}
					});


			});
		g_Render->draw_submenu<sub>(("Spammer"), SubmenuSpammer, [](sub* sub)
			{
				//sub->draw_option<submenu>("Spoof Sender", nullptr, SubmenuSpoofSpammer);
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &chat.spammer, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &chat.delay, 0, 5000, 50);
				sub->draw_option<KeyboardOption>(("Text"), nullptr, chat.text.c_str(), []
					{
						showKeyboard("Enter Something", "", 35, &chat.text, [] {});



					});
				sub->draw_option<RegularOption>(("Send Once"), nullptr, []
					{
						chat.send_once();
					});


			});
		g_Render->draw_submenu<sub>(("Spoof Sender"), SubmenuSpoofSpammer, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &chat.spoof_sender, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Player List"), nullptr, [] {});

				if (!chat.spoof_sender) {
					return;
				}
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{

						std::string name = PLAYER::GET_PLAYER_NAME(i);
						if (i == PLAYER::PLAYER_ID())
							name.append(" ~p~[Self]");

						if (i == chat.spoofed_sender)
							name.append(" ~b~[Selected]");
						sub->draw_option<RegularOption>((name.c_str()), nullptr, [=]
							{
								chat.spoofed_sender = i;
							});

					}
				}



			});
		g_Render->draw_submenu<sub>(("Off The Radar"), SubmenuOffRadar, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &m_radar.enabled, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Time", nullptr, &m_radar.time, &m_radar.data);

			});
		g_Render->draw_submenu<sub>(("RID Joiner"), SubmenuRIDJoiner, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Join"), nullptr, []
					{
						rid_toolkit.join(selected_rid);

					});

				sub->draw_option<UnclickOption>(("RID"), nullptr, [] {});
				if (ridBuffer.c_str() != "") {

					sub->draw_option<KeyboardOption>(("RID"), nullptr, ridBuffer.c_str(), []
						{
							showKeyboard("Enter Something", "", 25, &ridBuffer, [] {
								selected_rid = atoi(ridBuffer.c_str());
								});



						});
				}


			});
		g_Render->draw_submenu<sub>(("Requests"), SubmenuRequests, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &requests.data, &requests.data_i);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						switch (requests.data_i) {
						case 0:
							requests.add(888);
							break;
						case 1:
							requests.add(887);
							break;
						case 2:
							requests.add(4484);
							break;
						case 3:
							requests.add(4485);
							break;
						case 4:
							requests.add(886);
							break;
						case 5:
							*script_global(2672505).at(3689).as<bool*>() = true;
							break;
						case 6:
							requests.add(896);
							break;
						}
					});
				sub->draw_option<UnclickOption>(("Other"), nullptr, [] {});
				sub->draw_option<RegularOption>(("RC"), "", [] {

					*script_global(2793046).at(6874).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("Mini Tank"), "", [] {

					*script_global(2793046).at(6875).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("MOC"), "", [] {

					*script_global(2793046).at(925).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("Avenger"), "", [] {

					*script_global(2793046).at(933).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("Terrobyte"), "", [] {

					*script_global(2793046).at(937).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("Kosatka"), "", [] {

					*script_global(2793046).at(954).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("Kosatka"), "", [] {

					*script_global(2793046).at(954).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("Acid Lab"), "", [] {

					*script_global(2793046).at(938).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("Delivery Bike"), "", [] {

					*script_global(2793046).at(988).as<bool*>() = true;

					});
				sub->draw_option<RegularOption>(("Remove Loop"), "", [] {
					*script_global(2793046).at(6874).as<bool*>() = false;
					*script_global(2793046).at(6875).as<bool*>() = false;
					});


			});
		g_Render->draw_submenu<sub>(("Session Starter"), SubmenuSesStart, [](sub* sub)
			{
				sub->draw_option<toggle_number_option<std::int32_t, bool>>("Start Once Below Count", nullptr, &autostart.enabled, &autostart.max, 0, 32);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &session.name, &session.data);
				sub->draw_option<RegularOption>(("Join"), nullptr, []
					{
						switch (session.data) {
						case 0:
							session.join(eSessionType::JOIN_PUBLIC);
							break;
						case 1:
							session.join(eSessionType::NEW_PUBLIC);
							break;
						case 2:
							session.join(eSessionType::CLOSED_CREW);
							break;
						case 3:
							session.join(eSessionType::CREW);
							break;
						case 4:
							session.join(eSessionType::CLOSED_FRIENDS);
							break;
						case 5:
							session.join(eSessionType::FIND_FRIEND);
							break;
						case 6:
							session.join(eSessionType::SOLO);
							break;
						case 7:
							session.join(eSessionType::INVITE_ONLY);
							break;
						case 8:
							session.join(eSessionType::JOIN_CREW);
							break;
						case 9:
							session.join(eSessionType::SC_TV);
							break;
						case 10:
							session.join(eSessionType::LEAVE_ONLINE);
							break;

						}
					});

			});
		g_Render->draw_submenu<sub>("Hide Information", rage::joaat("HideINFO"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("IP"), nullptr, &hide_information.ip, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Port"), nullptr, &hide_information.port, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Vehicle"), nullptr, &hide_information.vehicle, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("State"), nullptr, &hide_information.state, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Wanted Level"), nullptr, &hide_information.wanted_level, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("ID"), nullptr, &hide_information.id, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Parachute State"), nullptr, &hide_information.parachute_state, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Ammo"), nullptr, &hide_information.ammo, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Stand User"), nullptr, &hide_information.standuser, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Zone"), nullptr, &hide_information.zone, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Street"), nullptr, &hide_information.street, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Coords"), nullptr, &hide_information.coords, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Distance"), nullptr, &hide_information.distance, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Wallet & Bank"), nullptr, &hide_information.walletandbank, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Total Money"), nullptr, &hide_information.totalmoney, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Heading"), nullptr, &hide_information.heading, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Speed"), nullptr, &hide_information.speed, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Rank"), nullptr, &hide_information.rank, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Favorite Vehicle"), nullptr, &hide_information.favvehicle, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("RP"), nullptr, &hide_information.rp, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Yacht Name"), nullptr, &hide_information.yachtname, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Ceo Name"), nullptr, &hide_information.ceoname, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("MC Name"), nullptr, &hide_information.mcname, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Off The Radar"), nullptr, &hide_information.offtheradar, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("KD"), nullptr, &hide_information.kd, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Kills"), nullptr, &hide_information.kills, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Deaths"), nullptr, &hide_information.deaths, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>("Settings", rage::joaat("PlayerInfoSettings"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Player Information"), nullptr, &hide_information.all, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Ped Preview"), nullptr, &hide_information.ped, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Tags"), nullptr, [] {});
				sub->draw_option<toggle<bool>>(("Self"), nullptr, &tags.self, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Saint"), nullptr, &tags.saint_user, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Interior"), nullptr, &tags.interior, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Modder"), nullptr, &tags.modder, BoolDisplay::OnOff);


			});
		g_Render->draw_submenu<sub>("Player List", SubmenuPlayerList, [](sub* sub)
			{
				sub->draw_option<submenu>("All", nullptr, SubmenuAllPlayers);
				sub->draw_option<submenu>("Saved", nullptr, SubmenuSavedPlayers);
				sub->draw_option<submenu>("Hide Information", nullptr, rage::joaat("HideINFO"));
				sub->draw_option<submenu>("Settings", nullptr, rage::joaat("PlayerInfoSettings"));
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Spectate", nullptr, &spectateo.type, &spectateo.pos, false, -1, []
					{
						if (spectateo.pos == 0) {
							spectateo.stop();
						}
						if (spectateo.pos == 1) {
							spectateo.random();
						}

					});


				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});

				for (std::uint32_t i = 0; i < 32; ++i)
				{


					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{
						if (sub->GetSelectedOption() == sub->GetNumOptions()) {
							if (hide_information.all) {
								g_players.draw_info(i);
							}
						}
						std::string name = PLAYER::GET_PLAYER_NAME(i);
						if (i == PLAYER::PLAYER_ID() && tags.self)
							name.append(" ~p~[Self]");
						if (PED::GET_PED_CONFIG_FLAG(ped, 109, true) && tags.saint_user) {
							name.append(" ~b~[Saint]");
						}
						if (INTERIOR::GET_INTERIOR_FROM_ENTITY(ped) != 0 && tags.interior) {
							name.append(" ~b~[Interior]");
						}
						if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
							if (antiCheat.cheater[g_GameVariables->m_net_game_player(i)->m_player_id] == true && tags.modder) {
								name.append(" ~r~[Modder]");
							}
						}



						sub->draw_option<playersubmenu>(name.c_str(), nullptr, SubmenuSelectedPlayer, [=]
							{
								g_SelectedPlayer = i;
							});


					}


				}

			});

		g_Render->draw_submenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
			{
				sub->draw_option<submenu>("Trolling", nullptr, SubmenuTrolling);
				sub->draw_option<submenu>("Bodyguards", nullptr, SubmenuBodyguards);
				sub->draw_option<submenu>("Increment", nullptr, SubmenuIncrement);
				sub->draw_option<submenu>("Friendly", nullptr, SubmenuFriendly);
				sub->draw_option<submenu>("Vehicle", nullptr, SubmenuSelectedVehicle);
				sub->draw_option<submenu>("Weapon", nullptr, SubmenuSelectedWeapon);
				sub->draw_option<submenu>("Teleport", nullptr, SubmenuPlayerTeleport);
				sub->draw_option<submenu>("Spawner", nullptr, SubmenuSelectedSpawner);
				sub->draw_option<submenu>("Removals", nullptr, SubmenuRemoval);
				sub->draw_option<submenu>("Chat", nullptr, SubmenuSelectedChat);
				sub->draw_option<submenu>("Social Club", nullptr, SubmenuSocialClub);
				//sub->draw_option<submenu>("Block Actions", nullptr, rage::joaat("BlockActions"));
				sub->draw_option<submenu>("More Information", nullptr, rage::joaat("MoreInformation"));
				sub->draw_option<submenu>("Detections", nullptr, SubmenuSelectedDetections);
				if (g_SelectedPlayer != PLAYER::PLAYER_ID()) {
					sub->draw_option<toggle<bool>>(("Spectate"), nullptr, &features.spectate, BoolDisplay::OnOff, false, [] {
						if (!features.spectate) {



							NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, -1);
							HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);

							ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
							ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false);

							STREAMING::SET_FOCUS_ENTITY(PLAYER::PLAYER_PED_ID());

						}
						});
				}
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Copy To Clipboard", nullptr, &c_clipboard.to_copy, &c_clipboard.data, false, -1, []
					{
						switch (c_clipboard.data) {
						case 0:
							int netHandle[13];
							NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), netHandle, 13);
							copytoclipboard(NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]));
							break;
						case 1:
							if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
								copytoclipboard(all_players.get_player_info(g_SelectedPlayer)->m_net_player_data.m_name);
							}
							else {
								g_NotificationManager->add("Please start a session.");

							}
							break;
						case 2:
							if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
								const auto* net_player_data = g_GameVariables->m_net_game_player(g_SelectedPlayer)->get_net_data();


								auto data = g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_clan_data;
								char input2[64];
								sprintf(input2, "Name: %s\nTag: %s\nMember Count: %i\nMotto: %s", data.m_clan_name, data.m_clan_tag, data.m_clan_member_count, data.m_clan_motto);
								copytoclipboard(input2);

							}
							else {
								g_NotificationManager->add("Please start a session.");
							}
							break;
						}
					});
				sub->draw_option<RegularOption>("Save", nullptr, [=]
					{
						m_saved_players.add(g_SelectedPlayer);

					});


			});
		g_Render->draw_submenu<sub>("More Information", rage::joaat("MoreInformation"), [](sub* sub)
			{
				if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer))
				{
					script_global globalplayer_bd(2657589);
					script_global gpbd_fm_3(1894573);
					script_global gpbd_fm_1(1853910);
					auto& stats = gpbd_fm_1.as<GPBD_FM*>()->Entries[all_players.get_id(g_SelectedPlayer)].PlayerStats;
					auto& stats1 = gpbd_fm_1.as<GPBD_FM*>()->Entries[all_players.get_id(g_SelectedPlayer)];
					auto& stats2 = gpbd_fm_3.as<GPBD_FM_3*>()->Entries[all_players.get_id(g_SelectedPlayer)];
					auto& stats3 = globalplayer_bd.as<GlobalPlayerBD*>()->Entries[all_players.get_id(g_SelectedPlayer)];
					sub->draw_option<KeyboardOption>(("Races Won"), nullptr, std::to_string(stats.TotalRacesWon), [] {});
					sub->draw_option<KeyboardOption>(("Races Lost"), nullptr, std::to_string(stats.TotalRacesLost), [] {});
					sub->draw_option<KeyboardOption>(("Killstreak"), nullptr, std::to_string(stats1.KillStreak), [] {});
					sub->draw_option<KeyboardOption>(("Arcade Safe Cash"), nullptr, std::to_string(stats1.PropertyData.ArcadeData.SafeCashValue), [] {});
					sub->draw_option<KeyboardOption>(("Time Trial Active"), nullptr, stats3.TimeTrialActive ? "Yes" : "No", [] {});
					sub->draw_option<KeyboardOption>(("Badsport"), nullptr, stats3.IsBadsport ? "Yes" : "No", [] {});
					sub->draw_option<KeyboardOption>(("Invisible"), nullptr, stats3.IsInvisible ? "Yes" : "No", [] {});
					sub->draw_option<KeyboardOption>(("Off Radar"), nullptr, stats3.OffRadarActive ? "Yes" : "No", [] {});
					sub->draw_option<KeyboardOption>(("Yacht Name"), nullptr, stats3.YachtData.Appearance.Name.Data, [] {});
					sub->draw_option<KeyboardOption>(("Nightclub Safe Cash"), nullptr, separateByCommas2(stats1.PropertyData.NightclubData.SafeCashValue), [] {});
					sub->draw_option<KeyboardOption>(("Nightclub Entry Cost"), nullptr, std::to_string(stats1.PropertyData.NightclubData.EntryCost), [] {});
					sub->draw_option<KeyboardOption>(("Nightclub Popularity"), nullptr, std::to_string((int)stats1.PropertyData.NightclubData.Popularity), [] {});
					sub->draw_option<KeyboardOption>(("Bunker Research"), nullptr, std::to_string(stats1.PropertyData.TotalBunkerResearch), [] {});
					sub->draw_option<KeyboardOption>(("Current Research Progress"), nullptr, std::to_string(stats1.PropertyData.CurrentBunkerResearchProgress), [] {});
				}
			});
		g_Render->draw_submenu<sub>("Block Actions", rage::joaat("BlockActions"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Shooting"), nullptr, &g_players.get_selected.block_actions.shooting, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>("Chat", SubmenuSelectedChat, [](sub* sub)
			{
				sub->draw_option<submenu>("Presets", nullptr, SubmenuSelectedChatPresets);
				sub->draw_option<KeyboardOption>(("Text"), nullptr, p_chat.text.c_str(), []
					{
						showKeyboard("Enter Something", "", 35, &p_chat.text, [] {});



					});
				sub->draw_option<RegularOption>(("Send Once"), "~y~Notice: ~w~Local only.", []
					{
						p_chat.send_once();
					});
			});
		g_Render->draw_submenu<sub>("Presets", SubmenuSelectedChatPresets, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Hello, My IP is {ip}"), nullptr, []
					{
						std::string get_ip_text = std::format("Hello, My IP is {0}.{1}.{2}.{3}", g_players.get_ip_address(g_SelectedPlayer).m_field1, g_players.get_ip_address(g_SelectedPlayer).m_field2, g_players.get_ip_address(g_SelectedPlayer).m_field3, g_players.get_ip_address(g_SelectedPlayer).m_field4);
						p_chat.text = get_ip_text;
					});

			});
		g_Render->draw_submenu<sub>("Social Club", SubmenuSocialClub, [](sub* sub)
			{
				sub->draw_option<KeyboardOption>(("Send Friend Request"), nullptr, messageFriendInput, []
					{

						showKeyboard("Enter Something", "", 25, &messageFriendInput, [] {
							int handle[76];
							NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
							NETWORK::NETWORK_ADD_FRIEND(&handle[0], messageFriendInput.c_str());
							});
					});
				sub->draw_option<RegularOption>("Show Profile", nullptr, [=]
					{
						int handle[76];
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
						NETWORK::NETWORK_SHOW_PROFILE_UI(&handle[0]);

					});
			});
		g_Render->draw_submenu<sub>("Detections", SubmenuSelectedDetections, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Exclude"), nullptr, &antiCheat.excludethatuck, BoolDisplay::OnOff, false, [] {
					if (antiCheat.excludethatuck) {
						antiCheat.exclude_player(all_players.get_id(g_SelectedPlayer));
					}
					if (!antiCheat.excludethatuck) {
						antiCheat.remove_exclude(all_players.get_id(g_SelectedPlayer));
					}
					});
				if (antiCheat.excludethatuck) {
					sub->draw_option<UnclickOption>(("This player is excluded."), nullptr, [] {});
				}
				if (!antiCheat.excludethatuck) {
					sub->draw_option<RegularOption>("Mark As Cheater", nullptr, [=]
						{
							if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
								antiCheat.flag_as_modder(all_players.get_id(g_SelectedPlayer), g_SelectedPlayer, true);
							}


						});
					sub->draw_option<RegularOption>("Unmark As Cheater", nullptr, [=]
						{
							if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
								antiCheat.remove_as_modder(all_players.get_id(g_SelectedPlayer));
							}

						});
				}
			});
		g_Render->draw_submenu<sub>("Vehicle", SubmenuSelectedVehicle, [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("Boost", nullptr, &features.boost_speed, 0, 300, 10, 3, false, "", "", [] {
					if (g_players.get_selected.request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false))) {

						Vehicle get_veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(get_veh, features.boost_speed);
					}
					});
				sub->draw_option<RegularOption>("Stop", nullptr, [=]
					{
						if (g_players.get_selected.request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false))) {

							Vehicle get_veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(get_veh, 0);
						}

					});
				sub->draw_option<RegularOption>("Launch", nullptr, [=]
					{
						if (g_players.get_selected.request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false))) {

							ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false), 1, 0, 0, 300, 0, 0, 0, 1, false, true, true, true, true);
						}

					});
				sub->draw_option<RegularOption>("Downgrade", nullptr, [=]
					{
						if (g_players.get_selected.request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false))) {

							for (int i = 0; i < 50; i++)
							{

								Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
								VEHICLE::REMOVE_VEHICLE_MOD(vehicle, i);
							}
						}

					});
				sub->draw_option<RegularOption>("Gift Current", "", [] {
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, TRUE, TRUE);
					DECORATOR::DECOR_REGISTER("PV_Slot", 3);
					DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
					DECORATOR::DECOR_SET_BOOL(vehicle, "IgnoredByQuickSave", FALSE);
					DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(g_SelectedPlayer));
					VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
					});
				sub->draw_option<RegularOption>("Clone", nullptr, [=]
					{
						Vehicle pedVeh = NULL;
						Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
						if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
						{
							pedVeh = PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE);
							if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
							{

								Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);
								*script_global(4540726).as<bool*>() = true;
								g_CallbackScript->AddCallback<ModelCallback>(vehicleModelHash, [=]
									{



										Vehicle playerVeh;
										NativeVector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(PLAYER::PLAYER_PED_ID(), { 0.f, 0.f, (VEHICLE::IS_THIS_MODEL_A_PLANE(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_HELI(vehicleModelHash)) ? 1.0f + 50.f : 1.0f });
										*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
										Vehicle vehicle = VEHICLE::CREATE_VEHICLE(vehicleModelHash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, false, false);
										spawned_veh.spawned.push_back({ HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(vehicle))), vehicle });
										playerVeh = vehicle;
										*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
										DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
										auto networkId = NETWORK::VEH_TO_NET(vehicle);
										if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
											NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
										VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
										PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);

										int primaryColor, secondaryColor;
										VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
										VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
										if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh))
										{
											int r, g, b;
											VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
										}
										if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh))
										{
											int r, g, b;
											VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
										}
										if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
										{
											VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
											VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
											for (int i = 0; i <= 24; i++)
											{
												if (i > 16 && i < 23)
													VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
												else
													VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
											}
											int tireSmokeColor[3], pearlescentColor, wheelColor;
											VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
											VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
											VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
											if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
											{
												int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
												if (convertableState == 0 || convertableState == 3 || convertableState == 5)
													VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
												else
													VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
											}
											for (int i = 0; i <= 3; i++)
											{
												VEHICLE::SET_VEHICLE_NEON_ENABLED(playerVeh, i, VEHICLE::GET_VEHICLE_NEON_ENABLED(pedVeh, i));
											}
											for (int i = 0; i <= 11; i++)
											{
												if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
													VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
											}
											if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
											{
												VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
											}
											int neonColor[3];
											VEHICLE::GET_VEHICLE_NEON_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
											VEHICLE::SET_VEHICLE_NEON_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
											VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
										}

									});





							}
						}

					});




			});
		g_Render->draw_submenu<sub>("Spawner", SubmenuSelectedSpawner, [](sub* sub)
			{
				sub->draw_option<submenu>("Settings", nullptr, Submenu::SpawnerSelectedSettings);
				sub->draw_option<submenu>("Search", nullptr, Submenu::SubmenuSelectedVehicleSearch);
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				for (std::int32_t i = 0; i < 23; i++) {
					sub->draw_option<submenu>(get_vehicle_class_name(i), nullptr, SubmenuSelectedGet, [=]
						{
							m_selected_player_vehicle_class = i;

						});

				}

			});
		g_Render->draw_submenu<sub>(("Search"), SubmenuSelectedVehicleSearch, [](sub* sub)
			{

				sub->draw_option<KeyboardOption>(("Input"), nullptr, ModelInput, []
					{

						showKeyboard("Enter Something", "", 25, &ModelInput, [] {
							search_completed = true;
							});
					});
				if (search_completed) {
					Hash vehicleHash2 = MISC::GET_HASH_KEY(ModelInput.c_str());
					if (STREAMING::IS_MODEL_VALID(vehicleHash2)) {
						sub->draw_option<UnclickOption>(("Found ~r~1 ~w~Result."), nullptr, [] {});
					}
					else {
						sub->draw_option<UnclickOption>(("Found ~r~0 ~w~Results."), nullptr, [] {});
					}

					if (STREAMING::IS_MODEL_VALID(vehicleHash2)) {

						STREAMING::REQUEST_MODEL(vehicleHash2);
						if (!STREAMING::HAS_MODEL_LOADED(vehicleHash2)) {


						}
						else {



							sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehicleHash2))), nullptr, [=]
								{
									Vehicle veh;
									veh_spawner.spawn_for_ped(vehicleHash2, &veh);

								});


						}
					}
				}

			});
		g_Render->draw_submenu<sub>("Settings", SpawnerSelectedSettings, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Fade"), nullptr, &veh_spawner.selected_fade, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>((get_vehicle_class_name(m_selected_player_vehicle_class)), SubmenuSelectedGet, [](sub* sub)
			{
				if (g_GameFunctions->m_vehicle_hash_pool != nullptr) {
					for (std::int32_t i = 0; i < g_GameFunctions->m_vehicle_hash_pool->capacity; i++) {
						std::uint64_t info = g_GameFunctions->m_vehicle_hash_pool->get(i);
						if (info != NULL) {
							if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
								std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
								std::string model_ptr = (char*)((uintptr_t)info + 0x298);
								if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(MISC::GET_HASH_KEY(model_ptr.c_str())) == m_selected_player_vehicle_class) {
									std::stringstream ss;
									std::string make(make_ptr);
									std::string model(model_ptr);
									if (make[0] || model[0]) {
										make = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(make.c_str());
										model = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model.c_str());
										if (make != "NULL" && model != "NULL") {
											ss << make << " " << model;
										}
										else if (model != "NULL") {
											ss << model;
										}
										else {
											ss << "Unknown";
										}
									}

									sub->draw_option<RegularOption>((HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(*(std::uint32_t*)(info + 0x18)))), nullptr, [=]
										{
											Vehicle veh;
											veh_spawner.spawn_for_ped(*(std::uint32_t*)(info + 0x18), &veh);

										});
								}
							}
						}
					}
				}
			});
		g_Render->draw_submenu<sub>("Weapon", SubmenuSelectedWeapon, [](sub* sub)
			{
				sub->draw_option<submenu>("Explosive Ammo", nullptr, SubmenuSelectedExplosiveAmmo);
				sub->draw_option<toggle<bool>>(("Teleport You"), nullptr, &m_impacts.teleport, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>("Explosive Ammo", SubmenuSelectedExplosiveAmmo, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &g_players.get_selected.explosiveAmmo.enabled, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Sound"), nullptr, &g_players.get_selected.explosiveAmmo.sound, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Invisible"), nullptr, &g_players.get_selected.explosiveAmmo.invisible, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &g_players.get_selected.explosiveAmmo.explode_type, &g_players.get_selected.explosiveAmmo.explode_int);
				sub->draw_option<number<float>>("Damage", nullptr, &g_players.get_selected.explosiveAmmo.damage, 0.0f, 150.f, 0.10f, 2);
				sub->draw_option<number<float>>("Camera Shake", nullptr, &g_players.get_selected.explosiveAmmo.camera_shake, 0.0f, 150.f, 0.10f, 2);

			});
		g_Render->draw_submenu<sub>("Increment", SubmenuIncrement, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &incr.type, &incr.data);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						incr.add();
					});

			});
		g_Render->draw_submenu<sub>("Friendly", SubmenuFriendly, [](sub* sub)
			{
				sub->draw_option<submenu>("Drops", nullptr, SubmenuDrops);
				sub->draw_option<submenu>("Give Weapons", nullptr, SubmenuGiveWeapons);
				sub->draw_option<toggle<bool>>(("Flash Blip"), nullptr, &g_players.get_selected.flash_blip.enabled, BoolDisplay::OnOff, false, [] {
					if (!g_players.get_selected.flash_blip.enabled) {
						Blip b = HUD::GET_BLIP_FROM_ENTITY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
						HUD::SET_BLIP_FLASHES(b, false);
					}
					});

				sub->draw_option<toggle<bool>>(("Off The Radar"), nullptr, &g_players.get_selected.otr.enabled, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Give Weapons"), SubmenuGiveWeapons, [](sub* sub)
			{
				int Maxammo = 0;

				if (give_weapon.type_int != 0) {
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), all_weapons.hash[give_weapon.type_int], &Maxammo);
				}
				if (give_weapon.type_int == 0) {
					Maxammo = 9999;
				}
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &all_weapons.name_all, &give_weapon.type_int);
				sub->draw_option<number<std::int32_t>>("Ammo", nullptr, &give_weapon.amount, 1, Maxammo);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						if (give_weapon.type_int != 0) {
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), all_weapons.hash[give_weapon.type_int], 9999, false);
						}
						if (give_weapon.type_int == 0) {

							for (int x = 0; x < 106; x++) {
								WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), all_weapons.hash[x], give_weapon.amount, false);
							}
						}
					});

			});
		g_Render->draw_submenu<sub>("Removals", SubmenuRemoval, [](sub* sub)
			{
				sub->draw_option<submenu>("Kick", nullptr, SubmenuKicks);
				sub->draw_option<submenu>("Crash", nullptr, SubmenuCrashes);

			});
		g_Render->draw_submenu<sub>("Kick", SubmenuKicks, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Menu", nullptr, &g_players.get_selected.events.Menu, &g_players.get_selected.events.Menu_Data);
				sub->draw_option<RegularOption>(("Start"), nullptr, []
					{

						g_players.get_selected.events.remove();
					});


			});
		g_Render->draw_submenu<sub>("Crash", SubmenuCrashes, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &g_players.get_selected.events.CrashMenu, &g_players.get_selected.events.Menu_DataCrash);
				sub->draw_option<RegularOption>(("Start"), nullptr, []
					{

						g_players.get_selected.events.crash();
					});

			});
		g_Render->draw_submenu<sub>(("Saved"), SubmenuSavedPlayers, [](sub* sub)
			{

				sub->draw_option<RegularOption>(("Clear"), nullptr, []
					{
						std::string path = "C:\\Saint\\Players\\";
						for (const auto& entry : std::filesystem::directory_iterator(path)) {
							std::filesystem::remove(entry.path());
						}
						//thank you chat gpt!

					});
				sub->draw_option<UnclickOption>(("Lists"), nullptr, [] {});
				if (std::filesystem::exists("C:\\Saint\\Players\\") && std::filesystem::is_directory("C:\\Saint\\Players\\")) {

					namespace fs = std::filesystem;
					fs::directory_iterator dirIt{ "C:\\Saint\\Players\\" };
					for (auto&& dirEntry : dirIt)
					{
						if (dirEntry.is_regular_file())
						{
							auto path = dirEntry.path();
							if (path.has_filename())
							{
								if (path.extension() == ".ini")
								{
									OutfitList();
									char nigger[64];
									sprintf(nigger, "%s", path.stem().u8string().c_str());
									sub->draw_option<RegularOption>(nigger, nullptr, [=]
										{

										});

								}

							}
						}
					}
				}
				else {
					std::filesystem::create_directory("C:\\Saint\\Players\\");
				}



			});
		g_Render->draw_submenu<sub>("All", SubmenuAllPlayers, [](sub* sub)
			{
				sub->draw_option<submenu>("Settings", nullptr, SubmenuAllSettings);
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				sub->draw_option<submenu>("Jets", nullptr, SubmenuAllJets);
				sub->draw_option<submenu>("Explode", nullptr, SubmenuAllExplode);
				sub->draw_option<submenu>("ESP", nullptr, rage::joaat("ESP"));

				sub->draw_option<toggle<bool>>(("Off The Radar"), "Can cause crashes.", &all_players.off_the_radar, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Reveal"), nullptr, &features.reveal_all_players, BoolDisplay::OnOff, false, [] {
					if (!features.reveal_all_players) {



						*script_global(2657589).at(PLAYER::PLAYER_ID(), 466).at(213).as<std::int32_t*>() = 0;
						*script_global(2672505).at(58).as<std::int32_t*>() = 0;

					}
					});
				sub->draw_option<RegularOption>(("Teleport To You"), nullptr, [=]
					{
						for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
							if (g_players.get_selected.request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false))) {
								Entity ent = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
								ENTITY::SET_ENTITY_COORDS(ent, coords.x, coords.y, coords.z, 0, 0, 0, 0);
							}
						}



					});
				sub->draw_option<RegularOption>("Save", nullptr, [=]
					{
						bool saved = true;
						int number_saved = 0;
						int number_failed = 0;
						for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
							std::string name = PLAYER::GET_PLAYER_NAME(i);
							int netHandle[13];
							NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, netHandle, 13);
							std::string MenuFolderPath = "C:\\Saint\\Players\\";
							if (m_saved_players.DoesIniExists((MenuFolderPath + name + ".ini").c_str())) {

								if (number_failed < 2) {
									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_TIMES"  %s is already saved!", name });
								}
								if (number_failed > 2 && saved) {

									Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_TIMES"  2 or more players are already saved." });
									saved = false;
								}
								number_failed++;
							}
							else {
								Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
								ColorIni->WriteString(name, "Info", "Name");
								ColorIni->WriteString(NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]), "Info", "RID");
								number_saved++;
							}
						}
						Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_CHECK"  Saved a total of %i, and %i already existed.", number_saved, number_failed });
						saved = true;

					});


			});
		g_Render->draw_submenu<sub>("ESP", rage::joaat("ESP"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Tracers"), nullptr, &all_players.esp2.tracer, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Name"), nullptr, &all_players.esp2.name, BoolDisplay::OnOff);
				//sub->draw_option<toggle<bool>>(("Box"), nullptr, &all_players.esp2.box, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>("Explode", SubmenuAllExplode, [](sub* sub)
			{
				sub->draw_option<submenu>("Exclude", nullptr, SubmenuAllExplodeExcludes);
				sub->draw_option<submenu>("Blame", nullptr, SubmenuAllExplodeBlame);
				sub->draw_option<toggle<bool>>(("Sound"), nullptr, &all_players.m_explode.settings.sound, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Invisible"), nullptr, &all_players.m_explode.settings.invisible, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &all_players.m_explode.settings.explosions, &all_players.m_explode.settings.data);
				sub->draw_option<number<float>>("Damage", nullptr, &all_players.m_explode.settings.damage_scale, 0.0f, 150.f, 0.10f, 2);
				sub->draw_option<number<float>>("Camera Shake", nullptr, &all_players.m_explode.settings.camera_shake, 0.0f, 150.f, 0.10f, 2);
				sub->draw_option<toggle<bool>>(("Looped"), nullptr, &all_players.m_explode.settings.looped, BoolDisplay::OnOff);
				sub->draw_option<RegularOption>(("Once"), nullptr, []
					{
						all_players.m_explode.once();
					});
			});
		g_Render->draw_submenu<sub>("Exclude", SubmenuAllExplodeExcludes, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Friends"), nullptr, &all_players.m_explode.excludes.friends, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Self"), nullptr, &all_players.m_explode.excludes.self, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>("Blame", SubmenuAllExplodeBlame, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &all_players.m_explode.settings.blame, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Player List"), nullptr, [] {});

				if (!all_players.m_explode.settings.blame) {
					return;
				}
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{

						std::string name = PLAYER::GET_PLAYER_NAME(i);
						if (i == PLAYER::PLAYER_ID())
							name.append(" ~p~[Self]");

						if (i == all_players.m_explode.settings.blamed_person)
							name.append(" ~b~[Selected]");
						if (INTERIOR::GET_INTERIOR_FROM_ENTITY(ped) == 0) {
							sub->draw_option<RegularOption>((name.c_str()), nullptr, [=]
								{
									all_players.m_explode.settings.blamed_person = i;
								});
						}
					}
				}
			});
		g_Render->draw_submenu<sub>("Jets", SubmenuAllJets, [](sub* sub)
			{
				sub->draw_option<submenu>("Exclude", nullptr, SubmenuJetExcludes);
				sub->draw_option<RegularOption>(("Send"), nullptr, []
					{
						all_players.jet.spawn();
					});
			});
		g_Render->draw_submenu<sub>("Exclude", SubmenuJetExcludes, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Friends"), nullptr, &all_players.jet.excludes.friends, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Self"), nullptr, &all_players.jet.excludes.self, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>("Trolling", SubmenuTrolling, [](sub* sub)
			{
				sub->draw_option<submenu>("Send To Interior", nullptr, SubmenuSendToInt);
				sub->draw_option<submenu>("Fake Drops", nullptr, SubmenuFakeDrops);
				sub->draw_option<submenu>("Text Spam", nullptr, SubmenuSpamText);
				sub->draw_option<submenu>("Explode", nullptr, SubmenuExplode);
				sub->draw_option<submenu>("Attackers", nullptr, SubmenuAttackers);
				sub->draw_option<submenu>("Cage", nullptr, SubmenuCage);
				sub->draw_option<submenu>("Shoot Single Bullet", nullptr, rage::joaat("SHOOT_BULLET"));
				sub->draw_option<toggle<bool>>(("Water"), nullptr, &g_players.get_selected.water_loop, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Fire"), nullptr, &g_players.get_selected.fire_loop, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Always Wanted"), nullptr, &wanted_lev.always, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Freeze"), nullptr, &g_players.get_selected.freeze, BoolDisplay::OnOff);
				static int boost_power = 10000;
				sub->draw_option<number<std::int32_t>>("Bounty", nullptr, &boost_power, 0, 10000, 1, 3, false, "", "", [] {
					g_players.get_selected.bounty(boost_power);
					});
				sub->draw_option<RegularOption>(("Taze"), nullptr, [=]
					{
						g_players.get_selected.taze();


					});
				sub->draw_option<RegularOption>(("Kick From Vehicle"), nullptr, [=]
					{

						g_players.get_selected.kick_from_vehicle();



					});
				sub->draw_option<RegularOption>(("Blame"), nullptr, [=]
					{

						for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
							*(unsigned short*)g_GameFunctions->m_owned_explosion = 0xE990;
							FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), c.x, c.y, c.z, 0, 500, true, false, 0);
							*(unsigned short*)g_GameFunctions->m_owned_explosion = 0x850F;
						}



					});
				sub->draw_option<RegularOption>(("Send To Island"), nullptr, [=]
					{

						const size_t arg_count = 2;
						int64_t args[arg_count] = {
							(int64_t)eRemoteEvent::SendToCayoPerico,
							(int64_t)PLAYER::PLAYER_ID(),
						};

						g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << g_players.get_selected.get_id());



					});
				sub->draw_option<number<std::int32_t>>("Wanted Level", nullptr, &g_players.get_selected.wanted_level, 0, 5, 1, 3, true, "", "", [] {
					g_players.get_selected.set_wanted_level(g_players.get_selected.wanted_level);
					});
				//sub->draw_option<number<std::int32_t>>("Delay", nullptr, &Fake_drops.delay, 0, 5000, 50);


			});
		g_Render->draw_submenu<sub>(("Shoot Single Bullet"), rage::joaat("SHOOT_BULLET"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Weapon", nullptr, &all_weapons.name, &features.bullet_int);
				sub->draw_option<RegularOption>(("Shoot"), nullptr, [=]
					{
						std::int32_t hash = all_weapons.hash[features.bullet_int];
						WEAPON::REQUEST_WEAPON_ASSET(hash, 31, 0);
						g_FiberPool.queue([=] {
							while (!WEAPON::HAS_WEAPON_ASSET_LOADED(hash))
								fbr::cur()->wait();
							});
						NativeVector3 destination = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), SKEL_ROOT, 0.0f, 0.0f, 0.0f);
						NativeVector3 origin = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), SKEL_R_Hand, 0.0f, 0.0f, 0.2f);
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, hash, PLAYER::PLAYER_PED_ID(), false, false, 100.f);
					});
			});
		g_Render->draw_submenu<sub>(("Send To Interior"), SubmenuSendToInt, [](sub* sub) {
			sub->draw_option<RegularOption>(("Casino"), nullptr, [=]
				{
					g_players.get_selected.send_to_int({ 123 });
				});
			sub->draw_option<UnclickOption>(("Custom"), nullptr, [] {});
			sub->draw_option<KeyboardOption>(("ID"), nullptr, std::to_string(g_players.get_selected.int_id), []
				{
					showKeyboard("Enter Message", "", 50, &g_players.get_selected.buffer, [] {
						g_players.get_selected.int_id = atoi(g_players.get_selected.buffer.c_str());
						});
				});
			sub->draw_option<RegularOption>(("Send"), nullptr, [=]
				{
					g_players.get_selected.send_to_int({ g_players.get_selected.int_id });
				});
			});
		g_Render->draw_submenu<sub>(("Cage"), SubmenuCage, [](sub* sub) {
			sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &cage.type, &cage.data);
			sub->draw_option<toggle<bool>>(("Invisible"), nullptr, &cage.is_invisible, BoolDisplay::OnOff);
			sub->draw_option<RegularOption>(("Spawn"), nullptr, []
				{
					cage.add();
				});
			sub->draw_option<RegularOption>(("Delete"), nullptr, []
				{
					Player ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
					NativeVector3 pedpos = ENTITY::GET_ENTITY_COORDS(ped, 0);
					Hash ramp3 = MISC::GET_HASH_KEY("stt_prop_stunt_tube_l");
					Object ObjToDelete3 = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pedpos.x, pedpos.y, pedpos.z, 10.f, ramp3, 0, 1, 1);
					OBJECT::DELETE_OBJECT(&ObjToDelete3);
					Hash ramp = MISC::GET_HASH_KEY("prop_gold_cont_01");
					Object ObjToDelete = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pedpos.x, pedpos.y, pedpos.z, 10.f, ramp, 0, 1, 1);
					OBJECT::DELETE_OBJECT(&ObjToDelete);
				});
			});
		g_Render->draw_submenu<sub>(("Attackers"), SubmenuAttackers, [](sub* sub) {
			sub->draw_option<ChooseOption<const char*, std::size_t>>("Mode", nullptr, &attackers.mode, &attackers.mode_i);
			if (attackers.mode_i == 1) {
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Model", nullptr, &attackers.cop_models, &attackers.cop_int);
			}
			if (attackers.mode_i != 2) {
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Weapon", nullptr, &attackers.data, &attackers.data_i);
			}
			if (attackers.mode_i == 2) {
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Vehicle", nullptr, &attackers.veh, &attackers.veh_int);
				sub->draw_option<number<std::int32_t>>("Amount", nullptr, &attackers.how_many_planes, 0, 100);
			}

			sub->draw_option<RegularOption>(("Spawn"), nullptr, []
				{
					attackers.add();
				});
			sub->draw_option<RegularOption>(("Delete"), nullptr, []
				{
					attackers.remove();
				});
			});
		g_Render->draw_submenu<sub>(("Explode"), SubmenuExplode, [](sub* sub) {
			sub->draw_option<submenu>("Blame", nullptr, SubmenuExplodeBlame);
			sub->draw_option<toggle<bool>>(("Sound"), nullptr, &owned_explosion.sound, BoolDisplay::OnOff);
			sub->draw_option<toggle<bool>>(("Invisible"), nullptr, &owned_explosion.invisible, BoolDisplay::OnOff);
			sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &owned_explosion.data, &owned_explosion.data_i);
			sub->draw_option<number<float>>("Damage", nullptr, &owned_explosion.damage_scale, 0.0f, 150.f, 0.10f, 2);
			sub->draw_option<number<float>>("Camera Shake", nullptr, &owned_explosion.cameraShake, 0.0f, 150.f, 0.10f, 2);
			sub->draw_option<toggle<bool>>(("Looped"), nullptr, &owned_explosion.looped, BoolDisplay::OnOff);
			sub->draw_option<RegularOption>(("Once"), nullptr, []
				{
					if (owned_explosion.blame) {
						NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
						owned_explosion.add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(owned_explosion.blamed_person), c, owned_explosion.data_i, owned_explosion.damage_scale, owned_explosion.sound, owned_explosion.invisible, owned_explosion.cameraShake);
					}
					else {
						NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, owned_explosion.data_i, owned_explosion.damage_scale, owned_explosion.sound, owned_explosion.invisible, owned_explosion.cameraShake, false);
					}
				});
			});
		g_Render->draw_submenu<sub>("Blame", SubmenuExplodeBlame, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &owned_explosion.blame, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Player List"), nullptr, [] {});

				if (!owned_explosion.blame) {
					return;
				}
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{

						std::string name = PLAYER::GET_PLAYER_NAME(i);
						if (i == PLAYER::PLAYER_ID())
							name.append(" ~p~[Self]");
						if (i == g_SelectedPlayer)
							name.append(" ~r~[Them]");
						if (i == owned_explosion.blamed_person)
							name.append(" ~b~[Selected]");
						if (INTERIOR::GET_INTERIOR_FROM_ENTITY(ped) == 0) {
							sub->draw_option<RegularOption>((name.c_str()), nullptr, [=]
								{
									owned_explosion.blamed_person = i;
								});
						}
					}
				}
			});
		g_Render->draw_submenu<sub>(("Fake Drops"), SubmenuFakeDrops, [](sub* sub) {
			sub->draw_option<toggle<bool>>(("Money"), nullptr, &Fake_drops.money, BoolDisplay::OnOff);
			sub->draw_option<toggle<bool>>(("RP"), nullptr, &Fake_drops.rp, BoolDisplay::OnOff);
			sub->draw_option<number<std::int32_t>>("Height", nullptr, &Fake_drops.height, 0, 100);
			sub->draw_option<number<std::int32_t>>("Delay", nullptr, &Fake_drops.delay, 0, 5000, 50);
			});
		g_Render->draw_submenu<sub>("Text Spam", SubmenuSpamText, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &text_spam.enabled, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &text_spam.delay, 0, 5000, 50);

				sub->draw_option<KeyboardOption>(("Text"), nullptr, text_spam.text.c_str(), []
					{
						showKeyboard("Enter Message", "", 50, &text_spam.text, [] {});
					});
			});
		g_Render->draw_submenu<sub>("Teleport", SubmenuPlayerTeleport, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("To Player"), nullptr, []
					{
						if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false)) {
							for (int i = -1; i < 16; i++)
							{
								if (VEHICLE::IS_VEHICLE_SEAT_FREE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false), i, i))
								{
									PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false), i);
								}
							}
						}
						else {
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
							PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z);
						}
					});
				sub->draw_option<RegularOption>(("Their Vehicle To Me"), nullptr, [=]
					{

						if (g_players.get_selected.request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false))) {
							Entity ent = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
							NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
							ENTITY::SET_ENTITY_COORDS(ent, coords.x, coords.y, coords.z, 0, 0, 0, 0);

						}




					});

			});
		g_Render->draw_submenu<sub>(("Bodyguards"), SubmenuBodyguards, [](sub* sub)
			{
				sub->draw_option<submenu>("Model", nullptr, rage::joaat("CustomModelB"));
				sub->draw_option<toggle<bool>>(("Godmode"), nullptr, &bodygaurd.godmode, BoolDisplay::OnOff);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Weapon", nullptr, &all_weapons.name, &bodygaurd.WeaponInt);
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Custom Firing Pattern", nullptr, &bodygaurd.FiringPatternEnabled, &bodygaurd.FiringPattern, &bodygaurd.FiringPatternInt);
				sub->draw_option<number<std::int32_t>>("Accuracy", nullptr, &bodygaurd.accuary, 0, 100);
				sub->draw_option<number<float>>("Damage Multiplier", nullptr, &bodygaurd.damagemultiplier, 0.0f, 150.f, 0.10f, 2);
				sub->draw_option<KeyboardOption>(("Selected"), nullptr, bodygaurd.selected_name, []
					{

					});
				g_FiberPool.queue([=] {
					for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY(bodygaurd.selected_model.c_str())) && i < 100; i++)
					{
						STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY(bodygaurd.selected_model.c_str()));
						fbr::cur()->wait();
					}
					});
				if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY(bodygaurd.selected_model.c_str())))
				{
					sub->draw_option<RegularOption>(("Loading..."), "If the selected is a bunch of giberish, reselect the model", []
						{
						});
				}
				if (STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY(bodygaurd.selected_model.c_str()))) {
					sub->draw_option<RegularOption>(("Spawn"), nullptr, []
						{
							
							g_CallbackScript->AddCallback<ModelCallback>(MISC::GET_HASH_KEY(bodygaurd.selected_model.c_str()), [=] {
								NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
								Ped ped = PED::CREATE_PED(26, MISC::GET_HASH_KEY(bodygaurd.selected_model.c_str()), c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(g_SelectedPlayer), true, true);
								
								NETWORK::NETWORK_FADE_IN_ENTITY(ped, true, false);
								PED::SET_PED_AS_GROUP_LEADER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), PLAYER::GET_PLAYER_GROUP(g_SelectedPlayer));
								PED::SET_PED_AS_GROUP_MEMBER(ped, PLAYER::GET_PLAYER_GROUP(g_SelectedPlayer));
								PED::SET_PED_NEVER_LEAVES_GROUP(ped, PLAYER::GET_PLAYER_GROUP(g_SelectedPlayer));
								PED::SET_PED_COMBAT_ABILITY(ped, 100);
								WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, all_weapons.hash[bodygaurd.WeaponInt], 9998, true);
								PED::SET_PED_CAN_SWITCH_WEAPON(ped, true);
								PED::SET_GROUP_FORMATION(PLAYER::GET_PLAYER_GROUP(g_SelectedPlayer), 3);
								PED::SET_PED_MAX_HEALTH(ped, 5000);
								PED::SET_PED_ACCURACY(ped, bodygaurd.accuary);
								PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(ped, bodygaurd.damagemultiplier);
								if (bodygaurd.FiringPatternEnabled) {
									PED::SET_PED_FIRING_PATTERN(ped, bodygaurd.FiringPatternHashes[bodygaurd.FiringPatternInt]);
								}
								if (bodygaurd.godmode)
								{
									ENTITY::SET_ENTITY_INVINCIBLE(ped, bodygaurd.godmode);
								}
								bodygaurd.spawned.push_back({ ped, bodygaurd.selected_name, g_SelectedPlayer });
							});

						});
				}
				sub->draw_option<UnclickOption>(("Spawned"), nullptr, [] {});
				sub->draw_option<submenu>("All", nullptr, rage::joaat("BodyAll"));
				
				for (auto& guard : bodygaurd.spawned) {
					if (guard.m_owner == g_SelectedPlayer) {
						if (sub->GetSelectedOption() == sub->GetNumOptions()) {
							g_players.draw_info4(guard.m_id);
							NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(guard.m_id, false);
							GRAPHICS::DRAW_MARKER(20, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, 255, 0, 0, 200, 1, 1, 1, 0, 0, 0, 0);

						}
						sub->draw_option<submenu>(guard.m_name.c_str(), nullptr, rage::joaat("SelectedBodyGuard"), [=]
							{
								bodygaurd.selected_gaurd = guard.m_id;
							});
					}
					
				}
			});
		g_Render->draw_submenu<sub>(("All"), rage::joaat("BodyAll"), [](sub* sub)
			{
				
				sub->draw_option<RegularOption>(("Teleport To Me"), nullptr, [=]
					{
						for (auto& guard : bodygaurd.spawned) {
							if (guard.m_owner == g_SelectedPlayer) {
								NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
								ENTITY::SET_ENTITY_COORDS(guard.m_id, coords.x, coords.y, coords.z, 0, 0, 0, 0);
							}
						}
					});
				sub->draw_option<RegularOption>(("Teleport Into Current Vehicle"), nullptr, [=]
					{
						if (VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(get_veh())) {
							for (auto& guard : bodygaurd.spawned) {
								if (guard.m_owner == g_SelectedPlayer) {
									if (!PED::IS_PED_IN_ANY_VEHICLE(guard.m_id, false)) {
										if (VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(get_veh())) {
											for (int i = 0; i < 6; i++)
											{
												if (VEHICLE::IS_VEHICLE_SEAT_FREE(get_veh(), i, i))
												{
													PED::SET_PED_INTO_VEHICLE(guard.m_id, get_veh(), i);
												}
											}

										}

									}
								}
							}
						}
						else {
							Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_TIMES"  No seats are free." });
						}
					});
				sub->draw_option<RegularOption>(("Kill"), nullptr, [=]
					{

						for (auto& guard : bodygaurd.spawned) {
							if (guard.m_owner == g_SelectedPlayer) {
								PED::APPLY_DAMAGE_TO_PED(guard.m_id, PED::GET_PED_MAX_HEALTH(guard.m_id) * 2, false, 0);
							}
						}
					});
				sub->draw_option<RegularOption>(("Delete"), nullptr, []
					{
						for (auto& guard : bodygaurd.spawned) {
							if (guard.m_owner == g_SelectedPlayer) {
								PED::DELETE_PED(&guard.m_id);
								bodygaurd.spawned.clear();
							}
						}
						
					});

			});
		g_Render->draw_submenu<sub>(("Seleced"), rage::joaat("SelectedBodyGuard"), [](sub* sub)
			{
				Ped ped = bodygaurd.selected_gaurd;
				sub->draw_option<submenu>("Outfit Editor", nullptr, rage::joaat("OutfitEditorSelected"));
				sub->draw_option<RegularOption>(("Teleport To Me"), nullptr, [=]
					{
						NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
						ENTITY::SET_ENTITY_COORDS(ped, coords.x, coords.y, coords.z, 0, 0, 0, 0);
					});
				sub->draw_option<RegularOption>(("Teleport Into Current Vehicle"), nullptr, [=]
					{
						if (!PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
							if (VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(get_veh())) {
								for (int i = 0; i < 6; i++)
								{
									if (VEHICLE::IS_VEHICLE_SEAT_FREE(get_veh(), i, i))
									{
										PED::SET_PED_INTO_VEHICLE(ped, get_veh(), i);
									}
								}

							}
							else {
								Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_TIMES"  No seats are free." });
							}
						}
					});
				sub->draw_option<RegularOption>(("Kill"), nullptr, [=]
					{
						PED::APPLY_DAMAGE_TO_PED(ped, PED::GET_PED_MAX_HEALTH(ped) * 2, false, 0);
					});
				
			});
		g_Render->draw_submenu<sub>(("Outfit Editor"), rage::joaat("OutfitEditorSelected"), [](sub* sub)
			{
				Ped ped = bodygaurd.selected_gaurd;
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Component", nullptr, &Lists::HeaderTypesFrontend2, &Lists::HeaderTypesPosition22, true, -1, [] {
					g_Render->outfits = Lists::HeaderTypesBackend2[Lists::HeaderTypesPosition22];
					});
				switch (g_Render->outfits) {
				case Outfits::Face:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets face variation.", &testa2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 0), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 0, testa2, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets face texture variation.", &facetexture22222, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 0, testa2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 0, testa2, facetexture22222, 0); }); break;
				case Outfits::Head:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets head variation.", &testb2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 1), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 1, testb2, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets head texture variation.", &facetexture125, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 1, testb2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 1, testb2, facetexture125, 0); }); break;
				case Outfits::Hair:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets hair variation.", &testc2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 2, testc, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets hair texture variation.", &facetexture22, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 2, testc2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 2, testc2, facetexture22, 0); }); break;
				case Outfits::Torso:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets torso variation.", &testd2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 3), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 3, testd, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets torso texture variation.", &facetexture32, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 3, testd2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 3, testd2, facetexture32, 0); }); break;
				case Outfits::Torso2:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets torso 2 variation.", &testl2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 11), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 11, testl, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets torso 2 texture variation.", &facetexture42, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 11, testl2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 11, testl2, facetexture42, 0); }); break;
				case Outfits::Legs:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets leg variation.", &teste2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 4), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 4, teste, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets leg texture variation.", &facetexture52, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 4, teste2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 4, teste2, facetexture52, 0); }); break;
				case Outfits::Hands:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets hand variation.", &testf2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 5), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 5, testf, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets hand texture variation.", &facetexture62, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 5, testf2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 5, testf2, facetexture62, 0); }); break;
				case Outfits::Feet:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets feet variation.", &testg2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 6), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 6, testg, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets feet texture variation.", &facetexture72, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 6, testg2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 6, testg2, facetexture72, 0); }); break;
				case Outfits::Eyes:
					sub->draw_option<number<std::int32_t>>("Drawable", "Sets eye variation.", &testh2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 7), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 7, testh, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets eyes texture variation.", &facetexture82, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 7, testh2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 7, testh2, facetexture82, 0); }); break;
				case Outfits::Accessories:

					sub->draw_option<number<std::int32_t>>("Drawable", "Sets accessories variation.", &testi2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 8), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 8, testi, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets accessories texture variation.", &facetexture92, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 8, testi2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 8, testi2, facetexture92, 0); }); break;
				case Outfits::Vests:

					sub->draw_option<number<std::int32_t>>("Drawable", "Sets vest variation.", &testj2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 9), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 9, testj, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets vests texture variation.", &facetexture102, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 9, testj2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 9, testj2, facetexture102, 0); }); break;
				case Outfits::Decals:

					sub->draw_option<number<std::int32_t>>("Drawable", "Sets texture variation.", &testk2, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, 10), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 10, testk, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "Sets decals texture variation.", &facetexture112, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, 10, testk2), 1, 3, true, "", "", [=] { PED::SET_PED_COMPONENT_VARIATION(ped, 10, testk2, facetexture112, 0); }); break;
				}
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Props", nullptr, &Lists::HeaderTypesFrontend3, &Lists::HeaderTypesPosition32, true, -1, [] {
					g_Render->props = Lists::HeaderTypesBackend3[Lists::HeaderTypesPosition32];
					});
				switch (g_Render->props) {
				case Props::Hats:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &hatDrawable2, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, 0), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 0, hatDrawable2, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &hatTexture2, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, 0, hatDrawable2), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 0, hatDrawable2, hatTexture2, 0); }); break;
					break;
				case Props::Glasses:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &glassesDrawable2, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, 1), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 1, glassesDrawable2, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &glassesTexture2, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, 1, glassesDrawable2), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 1, glassesDrawable2, glassesTexture2, 0); }); break;
					break;
				case Props::Ears:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &earsDrawable2, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, 2), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 2, earsDrawable2, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &earsTexture2, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, 2, earsDrawable2), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 2, earsDrawable2, earsTexture2, 0); }); break;
					break;
				case Props::Watches:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &watchesDrawable2, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, 6), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 6, watchesDrawable2, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &watchesTexture2, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, 6, watchesDrawable2), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 6, watchesDrawable2, watchesTexture2, 0); }); break;
					break;
				case Props::Bracelets:
					sub->draw_option<number<std::int32_t>>("Drawable", "", &braceDrawable2, 0, PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, 7), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 7, braceDrawable2, 0, 0); });
					sub->draw_option<number<std::int32_t>>("Texture", "", &braceTexture2, 0, PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, 7, braceDrawable2), 1, 3, true, "", "", [=] { PED::SET_PED_PROP_INDEX(ped, 7, braceDrawable2, braceTexture2, 0); }); break;
					break;
				}
			});
		g_Render->draw_submenu<sub>(("Model"), rage::joaat("CustomModelB"), [](sub* sub)
			{
				for (std::int32_t i = 0; i < m_ModelChanger.size; i++) {
					sub->draw_option<submenu>(m_ModelChanger.get_class_name[i], nullptr, rage::joaat("FORTNITEISGOOD9992"), [=]
						{
							bodygaurd.selected_class = i;
						});

				}
			});
		g_Render->draw_submenu<sub>((m_ModelChanger.get_class_name[bodygaurd.selected_class]), rage::joaat("FORTNITEISGOOD9992"), [](sub* sub)
			{
				for (auto& model : m_ModelChanger.m_GetModels) {
					if (bodygaurd.selected_class == model.m_class) {
						sub->draw_option<RegularOption>(model.m_name.c_str(), nullptr, [=]
							{
								bodygaurd.selected_model = model.m_model;
								bodygaurd.selected_name = model.m_name;

							});
					}
				}


			});
		g_Render->draw_submenu<sub>(("Drops"), SubmenuDrops, [](sub* sub) {
			sub->draw_option<submenu>("Custom Location", nullptr, rage::joaat("CLocation"));
			sub->draw_option<toggle<bool>>(("Money"), nullptr, &drops.money, BoolDisplay::OnOff);
			sub->draw_option<toggle<bool>>(("RP"), nullptr, &drops.rp, BoolDisplay::OnOff);
			sub->draw_option<UnclickOption>(("Settings"), nullptr, [] {});
			sub->draw_option<toggle_number_option<std::int32_t, bool>>("Randomize RP Model", nullptr, &drops.random_rp_model, &drops.model_delay, 0, 5000, 50);
			sub->draw_option<toggle_number_option<std::int32_t, bool>>("Randomize Money Model", nullptr, &drops.random_money_model, &drops.model_delay2, 0, 5000, 50);
			sub->draw_option<ChooseOption<const char*, std::size_t>>("Location", nullptr, &drops.location, &drops.data);
			sub->draw_option<ChooseOption<const char*, std::size_t>>("RP Model", nullptr, &drops.rp_model, &drops.rp_model_data);
			sub->draw_option<ChooseOption<const char*, std::size_t>>("Money Model", nullptr, &drops.money_model, &drops.money_model_data);
			sub->draw_option<number<std::int32_t>>("Height", nullptr, &drops.height, 0, 100);
			sub->draw_option<number<std::int32_t>>("Delay", nullptr, &drops.delay, 0, 5000, 50);
			});
		g_Render->draw_submenu<sub>(("Custom Location"), rage::joaat("CLocation"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Money"), nullptr, &drops.custom.money, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("RP"), nullptr, &drops.custom.rp, BoolDisplay::OnOff);
				sub->draw_option<toggle_number_option<std::int32_t, bool>>("Randomize RP Model", nullptr, &drops.custom.random_rp_model, &drops.custom.model_delay, 0, 5000, 50);
				sub->draw_option<toggle_number_option<std::int32_t, bool>>("Randomize Money Model", nullptr, &drops.custom.random_money_model, &drops.custom.model_delay2, 0, 5000, 50);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Location", nullptr, &drops.custom.location, &drops.custom.data);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("RP Model", nullptr, &drops.custom.rp_model, &drops.custom.rp_model_data);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Money Model", nullptr, &drops.custom.money_model, &drops.custom.money_model_data);
				sub->draw_option<number<std::int32_t>>("Height", nullptr, &drops.custom.height, 0, 100);
				sub->draw_option<number<std::int32_t>>("Delay", nullptr, &drops.custom.delay, 0, 5000, 50);
				sub->draw_option<RegularOption>(("Add"), nullptr, []
					{
						NativeVector3 b2 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
						drops.custom.a.push_back(b2);
					});
				sub->draw_option<RegularOption>(("Remove All"), nullptr, []
					{
						drops.custom.a.clear();
					});
				sub->draw_option<UnclickOption>(("Current"), nullptr, [] {});
				for (auto& drop : drops.custom.a) {
					sub->draw_option<RegularOption>(std::format("{}, {}, {}", drop.x, drop.y, drop.z).c_str(), nullptr, [=]
						{



						});

				}

			});
		g_Render->draw_submenu<sub>(("Protection"), SubmenuProtections, [](sub* sub)
			{
				sub->draw_option<submenu>("Excludes", nullptr, rage::joaat("ExcludesFromScripts"));
				sub->draw_option<submenu>("Script Events", nullptr, SubmenuScriptEvents);
				sub->draw_option<submenu>("Game Events", nullptr, SubmenuGameEvents);
				sub->draw_option<submenu>("Entities", nullptr, SubmenuEntities);
				sub->draw_option<submenu>("Crash", nullptr, SubmenuProtCrash);
				sub->draw_option<toggle<bool>>(("Reports"), nullptr, &protections.block_reports, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Excludes"), rage::joaat("ExcludesFromScripts"), [](sub* sub)
			{

				sub->draw_option<toggle<bool>>(("Friends"), nullptr, &protections.exclude_friends, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Self"), nullptr, &protections.exclude_self, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Game Events"), SubmenuGameEvents, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Freeze"), nullptr, &protections.GameEvents.freeze, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Remove Weapon"), nullptr, &protections.GameEvents.remove_weapon, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Remove All Weapons"), nullptr, &protections.GameEvents.remove_all_weapons, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("PTFX"), nullptr, &protections.GameEvents.particle_spam, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Give Weapons"), nullptr, &protections.GameEvents.give_weapons, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Fire"), nullptr, &protections.GameEvents.fire_event, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Explosion"), nullptr, &protections.GameEvents.explosion, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Alter Wanted Level"), nullptr, &protections.GameEvents.alter_wanted_level, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Play Sound"), nullptr, &protections.GameEvents.play_sound, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Request Control"), nullptr, &protections.GameEvents.request_control, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Remove Sticky Bomb"), nullptr, &protections.GameEvents.remove_sticky_bomb, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Request Map Pickup"), nullptr, &protections.GameEvents.request_map_pickup, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Give Pickup Rewards"), nullptr, &protections.GameEvents.give_pickup_rewards, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Request Pickup"), nullptr, &protections.GameEvents.request_pickup, BoolDisplay::OnOff);
				//sub->draw_option<toggle<bool>>(("Clear Area"), nullptr, &protections.GameEvents.clear_area, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Weapon Damage"), nullptr, &protections.GameEvents.weapon_damage, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Vehicle Component Control"), nullptr, &protections.GameEvents.vehicle_component_control, BoolDisplay::OnOff);
				//sub->draw_option<toggle<bool>>(("Vehicle Horn"), nullptr, &protections.GameEvents.car_horn, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Vote Kick"), nullptr, &protections.GameEvents.vote_kick, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Blow Up Vehicle"), nullptr, &protections.GameEvents.blow_up_vehicle, BoolDisplay::OnOff);


			});
		g_Render->draw_submenu<sub>(("Entities"), SubmenuEntities, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Cage"), nullptr, &protections.Entities.cage, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Crash"), SubmenuProtCrash, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Rope"), nullptr, &protections.Crashes.rope, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Group Override"), nullptr, &protections.Crashes.groupoverride, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Invalid World State"), nullptr, &protections.Crashes.invalidworldstate, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Invalid Script Entity"), nullptr, &protections.Crashes.invalid_script_entity, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Task"), nullptr, &protections.Crashes.task, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Weapon"), nullptr, &protections.Crashes.weapon, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Fragment"), nullptr, &protections.Crashes.fragment, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Train"), nullptr, &protections.Crashes.train, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Entity"), nullptr, &protections.Crashes.entity, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Vehicle"), nullptr, &protections.Crashes.vehicle, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Ped"), nullptr, &protections.Crashes.ped, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Player"), nullptr, &protections.Crashes.player, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Object"), nullptr, &protections.Crashes.object, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Script Events"), SubmenuScriptEvents, [](sub* sub)
			{
				sub->draw_option<submenu>("Teleport", nullptr, rage::joaat("ProtectionsTeleport"));
				sub->draw_option<submenu>("CEO", nullptr, rage::joaat("ProtectionsCEO"));
				sub->draw_option<submenu>("Text Message", nullptr, rage::joaat("ProtectionsSMS"));
				sub->draw_option<submenu>("Notifications", nullptr, rage::joaat("ProtectionsNOTI"));
				sub->draw_option<toggle<bool>>(("Vehicle Kick"), nullptr, &protections.ScriptEvents.vehicle_kick, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Rotate Camera"), nullptr, &protections.ScriptEvents.rotate_cam, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Tutorial"), nullptr, &protections.ScriptEvents.tutorial, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Sound Spam"), nullptr, &protections.sound_spam, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Bounty"), nullptr, &protections.ScriptEvents.bounty, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Notifications"), rage::joaat("ProtectionsNOTI"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Money Stolen"), nullptr, &protections.moneystolen, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Money Removed"), nullptr, &protections.moneyremoved, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Money Banked"), nullptr, &protections.moneybanked, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Text Message"), rage::joaat("ProtectionsSMS"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Regular"), nullptr, &protections.ScriptEvents.text_messages, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Attachments"), nullptr, &protections.sms_with_attachment, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("CEO"), rage::joaat("ProtectionsCEO"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Kick"), nullptr, &protections.ceo_kick, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Ban"), nullptr, &protections.ceo_ban, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Money"), nullptr, &protections.ceo_money, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Raid"), nullptr, &protections.ceo_raid, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Teleport"), rage::joaat("ProtectionsTeleport"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Send To Location"), nullptr, &protections.send_to_location, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Motorcycle Club"), nullptr, &protections.mc_teleport, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Regular"), nullptr, &protections.teleport, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Interior"), nullptr, &protections.Interior, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Cayo Perico"), nullptr, &protections.cayo_perico, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Warehouse"), nullptr, &protections.warehouse, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Mission"), nullptr, &protections.mission, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Teleport"), SubmenuTeleport, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Automaticly Teleport To Waypoint"), nullptr, &m_teleport.automatic, BoolDisplay::OnOff);
				sub->draw_option<RegularOption>(("Waypoint"), nullptr, []
					{
						m_teleport.waypoint();
					});
				sub->draw_option<RegularOption>(("Objective"), nullptr, []
					{
						m_teleport.objective();
					});
				sub->draw_option<UnclickOption>(("Locations"), nullptr, [] {});
				sub->draw_option<submenu>("Popular", nullptr, rage::joaat("populartps"));
				sub->draw_option<submenu>("Airfields", nullptr, rage::joaat("airfield"));
				sub->draw_option<submenu>("Clubhouse & Warehouses", nullptr, rage::joaat("warhouse"));
				sub->draw_option<submenu>("Indoors", nullptr, rage::joaat("indoors"));


			});
		g_Render->draw_submenu<sub>(("Airfields"), rage::joaat("airfield"), [](sub* sub)
			{
				sub->draw_option<RegularOption>("LSIA", "", []
					{
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), -1336.0f, -3044.0f, 13.9f);
					});
				sub->draw_option<RegularOption>("Sandy Shores", "", []
					{
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 1747.0f, 3273.7f, 41.1f);
					});
				sub->draw_option<RegularOption>("McKenzie", "", []
					{
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 2121.7f, 4796.3f, 41.1f);
					});

			});
		g_Render->draw_submenu<sub>(("Popular"), rage::joaat("populartps"), [](sub* sub)
			{
				sub->draw_option<RegularOption>("Maze Bank Roof", "", []
					{
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), -75.015, -818.215, 326.176);
					});
				sub->draw_option<RegularOption>("Main LS Customs", "", []
					{
						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), -373.01, -124.91, 38.31);
					});

			});
		g_Render->draw_submenu<sub>(("Indoors"), rage::joaat("indoors"), [](sub* sub)
			{
				sub->draw_option<RegularOption>("Franklin's House", "", []
					{
						NativeVector3 Coords;
						Coords.x = -6, 54853; Coords.y = 520, 445007; Coords.z = 174, 627792;
						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});
				sub->draw_option<RegularOption>("Franklin's First House", "", []
					{
						NativeVector3 Coords;
						Coords.x = -14, 577254; Coords.y = -1427, 414917; Coords.z = 31, 101492;

						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});
				sub->draw_option<RegularOption>("Trevor's Truck", "", []
					{
						NativeVector3 Coords;
						Coords.x = 1973, 865845; Coords.y = 3819, 97168; Coords.z = 33, 436317;
						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});

				sub->draw_option<RegularOption>("Michael's House", "", []
					{
						NativeVector3 Coords;
						Coords.x = -812, 573303; Coords.y = 180, 043457; Coords.z = 72, 159172;
						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});

				sub->draw_option<RegularOption>("Lester's House", "", []
					{
						NativeVector3 Coords;
						Coords.x = 1269, 541504; Coords.y = -1710, 447876; Coords.z = 54, 771492;
						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});



				sub->draw_option<RegularOption>("Prison", "", []
					{
						NativeVector3 Coords;
						Coords.x = 1739.5726; Coords.y = 2576.4565; Coords.z = 45.0334;

						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});
				sub->draw_option<RegularOption>("Humane Labs", "", []
					{
						NativeVector3 Coords;
						Coords.x = 3614, 394775; Coords.y = 3744, 803467; Coords.z = 28, 690090;
						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});
				sub->draw_option<RegularOption>("FIB Building", "", []
					{
						NativeVector3 Coords;
						Coords.x = 128, 572662; Coords.y = -727, 923401; Coords.z = 254, 152115;
						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});

				sub->draw_option<RegularOption>("Floyd's Appartement", "", []
					{
						NativeVector3 Coords;
						Coords.x = -1155, 725952; Coords.y = -1518, 761719; Coords.z = 10, 632728;
						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});
				sub->draw_option<RegularOption>("Strip Club", "", []
					{
						NativeVector3 Coords;
						Coords.x = 126.135;
						Coords.y = -1278.583;
						Coords.z = 29.270;
						ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Coords, false, false, false, false);
					});
			});
		g_Render->draw_submenu<sub>(("Clubhouse & Warehouses"), rage::joaat("warhouse"), [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Clubhouse 1"), nullptr, []
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1107.04, -3157.399, -37.51859, false, false, false, false);
					});
				sub->draw_option<RegularOption>(("Clubhouse 2"), nullptr, []
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 998.4809, -3164.711, -38.90733, false, false, false, false);
					});
				sub->draw_option<RegularOption>(("Methlab"), nullptr, []
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1009.5, -3196.6, -38.99682, false, false, false, false);
					});
				sub->draw_option<RegularOption>(("Weed Farm"), nullptr, []
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1051.491, -3196.536, -39.14842, false, false, false, false);
					});
				sub->draw_option<RegularOption>(("Cocaine Lockup"), nullptr, []
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1093.6, -3196.6, -38.99841, false, false, false, false);
					});
			});

		g_Render->draw_submenu<sub>(("World"), SubmenuWorld, [](sub* sub)
			{
				//sub->draw_option<submenu>("Peds", nullptr, SubmenuPeds);
				sub->draw_option<submenu>("Weather", nullptr, SubmeuWeather);
				sub->draw_option<submenu>("Nearby Manager", nullptr, NearbyManager);
				sub->draw_option<submenu>("Creator", nullptr, rage::joaat("Creator"));
				sub->draw_option<submenu>("Time", nullptr, rage::joaat("TimeWORLD"));
				sub->draw_option<submenu>("Sky", nullptr, rage::joaat("Sky"));
				sub->draw_option<submenu>("Clouds", nullptr, rage::joaat("Clouds"));
				sub->draw_option<submenu>("Ocean", nullptr, rage::joaat("Ocean"));
				sub->draw_option<submenu>("Black Hole", nullptr, rage::joaat("BlackHole"));
				sub->draw_option<submenu>("Spawner", nullptr, rage::joaat("SpawnerW"));
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Vehicle Density", nullptr, &features.veh_density, &features.vden_pos, true, -1, [] {
					switch (features.vden_pos) {
					case 0:
						VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						break;
					case 1:
						VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(1.0f);
						break;
					}
					});


			});
		g_Render->draw_submenu<sub>(("Spawner"), rage::joaat("SpawnerW"), [](sub* sub)
			{
				sub->draw_option<submenu>("Ped", nullptr, rage::joaat("SpawnerWPed"));
			});
		g_Render->draw_submenu<sub>(("Ped"), rage::joaat("SpawnerWPed"), [](sub* sub)
			{
				for (std::int32_t i = 0; i < m_ModelChanger.size; i++) {
					sub->draw_option<submenu>(m_ModelChanger.get_class_name[i], nullptr, rage::joaat("FORTNITEISGOOD999"), [=]
						{
							ped_spawner.selected = i;
						});

				}
			});
		g_Render->draw_submenu<sub>((m_ModelChanger.get_class_name[ped_spawner.selected]), rage::joaat("FORTNITEISGOOD999"), [](sub* sub)
			{
				for (auto& model : m_ModelChanger.m_GetModels) {
					if (ped_spawner.selected == model.m_class) {
						sub->draw_option<RegularOption>(model.m_name.c_str(), nullptr, [=]
							{
								ped_spawner.change(MISC::GET_HASH_KEY(model.m_model.c_str()));

							});
					}
				}


			});
		g_Render->draw_submenu<sub>(("Black Hole"), rage::joaat("BlackHole"), [](sub* sub)
			{
				sub->draw_option<submenu>("Color", nullptr, rage::joaat("BHoleColor"));
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &black_hole.enabled, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Peds"), nullptr, &black_hole.peds2, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Vehicles"), nullptr, &black_hole.vehicles, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Preview", nullptr, &black_hole.preview, 0, 43, 1, 3);
				sub->draw_option<number<float>>("Force", nullptr, &black_hole.force, 0, 1000.0, 1.0, 3);
				sub->draw_option<number<float>>("Size", nullptr, &black_hole.size, 0, 1000.0, 1.0, 3);

				sub->draw_option<UnclickOption>(("Location"), nullptr, [] {});
				sub->draw_option<number<float>>("X", nullptr, &black_hole.c.x, -10000.f, 10000.f);
				sub->draw_option<number<float>>("Y", nullptr, &black_hole.c.y, -10000.f, 10000.f);
				sub->draw_option<number<float>>("Z", nullptr, &black_hole.c.z, -10000.f, 10000.f);
				sub->draw_option<RegularOption>("Teleport To Me", "", []
					{
						black_hole.c = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
					});
			});
		g_Render->draw_submenu<sub>(("Color"), rage::joaat("BHoleColor"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Rainbow"), nullptr, &black_hole.rainbow, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Red", nullptr, &black_hole.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("Green", nullptr, &black_hole.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("Blue", nullptr, &black_hole.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("Alpha", nullptr, &black_hole.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Ocean"), rage::joaat("Ocean"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Visual Effect", "put this as smooth and wave intensity at 0 for a cool effect", &ocean.type, &ocean.pos, true, -1, [] {

					switch (ocean.pos) {
					case 0:
						MISC::WATER_OVERRIDE_SET_STRENGTH(0.0f);
						break;
					case 1:
						MISC::WATER_OVERRIDE_SET_STRENGTH(1.0f);
						break;
					case 2:
						MISC::WATER_OVERRIDE_SET_STRENGTH(3.0f);
						break;
					}
					});
				sub->draw_option<number<float>>("Wave Intensity", nullptr, &ocean.intensity, 0, 1000.0, 1.0, 3, true, "", "", [] {
					WATER::SET_DEEP_OCEAN_SCALER(ocean.intensity);
					});

			});
		g_Render->draw_submenu<sub>(("Color"), rage::joaat("ColorClouds"), [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("Red", nullptr, &sky_data.cloud.r, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Green", nullptr, &sky_data.cloud.g, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Blue", nullptr, &sky_data.cloud.b, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<float>>("Brightness", nullptr, &sky_data.cloud.brightness, 1.0f, 1000.0f, 1.0f);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						sky_data.cloud.changed = true;
						std::fill_n(g_GameFunctions->m_cloud_mid_patch, 7, '\x90');
						uintptr_t west_red = scan_address(g_base_address + 0x26CFE10, {});
						uintptr_t west_green = scan_address(g_base_address + 0x26CFE14, {});
						uintptr_t west_blue = scan_address(g_base_address + 0x26CFE18, {});

						*(float*)west_red = (sky_data.cloud.r / 255.f) * sky_data.cloud.brightness;
						*(float*)west_green = (sky_data.cloud.g / 255.f) * sky_data.cloud.brightness;
						*(float*)west_blue = (sky_data.cloud.b / 255.f) * sky_data.cloud.brightness;


					});
			});
		g_Render->draw_submenu<sub>(("Clouds"), rage::joaat("Clouds"), [](sub* sub)
			{
				sub->draw_option<submenu>("Color", nullptr, rage::joaat("ColorClouds"));
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				sub->draw_option<RegularOption>("None", nullptr, [] { MISC::UNLOAD_ALL_CLOUD_HATS(); });
				sub->draw_option<RegularOption>("Cloudy", nullptr, [] { MISC::LOAD_CLOUD_HAT("Cloudy 01", 0.5f); });
				sub->draw_option<RegularOption>("Rain", nullptr, [] { MISC::LOAD_CLOUD_HAT("RAIN", 0.5f); });
				sub->draw_option<RegularOption>("Horizon", nullptr, [] { MISC::LOAD_CLOUD_HAT("Horizon", 0.5f); });
				sub->draw_option<RegularOption>("Horizon Band 1", nullptr, [] { MISC::LOAD_CLOUD_HAT("horizonband1", 0.5f); });
				sub->draw_option<RegularOption>("Horizon Band 2", nullptr, [] { MISC::LOAD_CLOUD_HAT("horizonband2", 0.5f); });
				sub->draw_option<RegularOption>("Horizon Band 3", nullptr, [] { MISC::LOAD_CLOUD_HAT("horizonband3", 0.5f); });
				sub->draw_option<RegularOption>("Puffs", nullptr, [] { MISC::LOAD_CLOUD_HAT("Puffs", 0.5f); });
				sub->draw_option<RegularOption>("Wispy", nullptr, [] { MISC::LOAD_CLOUD_HAT("Wispy", 0.5f); });
				sub->draw_option<RegularOption>("Stormy", nullptr, [] { MISC::LOAD_CLOUD_HAT("Stormy 01", 0.5f); });
				sub->draw_option<RegularOption>("Clear", nullptr, [] { MISC::LOAD_CLOUD_HAT("Clear 01", 0.5f); });
				sub->draw_option<RegularOption>("Snowy", nullptr, [] { MISC::LOAD_CLOUD_HAT("Snowy 01", 0.5f); });
				sub->draw_option<RegularOption>("Contrails", nullptr, [] { MISC::LOAD_CLOUD_HAT("Contrails", 0.5f); });
				sub->draw_option<RegularOption>("Altostratus", nullptr, [] { MISC::LOAD_CLOUD_HAT("altostratus", 0.5f); });
				sub->draw_option<RegularOption>("Nimbus", nullptr, [] { MISC::LOAD_CLOUD_HAT("Nimbus", 0.5f); });
				sub->draw_option<RegularOption>("Cirrus", nullptr, [] { MISC::LOAD_CLOUD_HAT("Cirrus", 0.5f); });
				sub->draw_option<RegularOption>("Cirrocumulus", nullptr, [] { MISC::LOAD_CLOUD_HAT("cirrocumulus", 0.5f); });
				sub->draw_option<RegularOption>("Stratocumulus", nullptr, [] { MISC::LOAD_CLOUD_HAT("stratocumulus", 0.5f); });
				sub->draw_option<RegularOption>("Stripey", nullptr, [] { MISC::LOAD_CLOUD_HAT("Stripey", 0.5f); });
				sub->draw_option<RegularOption>("Horsey", nullptr, [] { MISC::LOAD_CLOUD_HAT("horsey", 0.5f); });
				sub->draw_option<RegularOption>("Shower", nullptr, [] { MISC::LOAD_CLOUD_HAT("shower", 0.5f); });
			});
		g_Render->draw_submenu<sub>(("Sky"), rage::joaat("Sky"), [](sub* sub)
			{
				sub->draw_option<submenu>("East", nullptr, rage::joaat("East"));
				sub->draw_option<submenu>("West", nullptr, rage::joaat("West"));
				sub->draw_option<submenu>("South & North", nullptr, rage::joaat("SouthNorth"));
				//sub->draw_option<submenu>("Zenith", nullptr, rage::joaat("Zenith"));
			});
		g_Render->draw_submenu<sub>(("East"), rage::joaat("East"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Rainbow"), nullptr, &sky_data.east.rainbow, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Red", nullptr, &sky_data.east.r, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Green", nullptr, &sky_data.east.g, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Blue", nullptr, &sky_data.east.b, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<float>>("Brightness", nullptr, &sky_data.east.brightness, 1.0f, 1000.0f, 1.0f);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						sky_data.east.changed = true;
						std::fill_n(g_GameFunctions->m_east_azimuth_patch, 4, '\x90');
						uintptr_t east_red = scan_address(g_base_address + 0x26CFAB0, {});
						uintptr_t east_green = scan_address(g_base_address + 0x26CFAB4, {});
						uintptr_t east_blue = scan_address(g_base_address + 0x26CFAB8, {});

						*(float*)east_red = (sky_data.east.r / 255.f) * sky_data.east.brightness;
						*(float*)east_green = (sky_data.east.g / 255.f) * sky_data.east.brightness;
						*(float*)east_blue = (sky_data.east.b / 255.f) * sky_data.east.brightness;
					});

			});
		g_Render->draw_submenu<sub>(("West"), rage::joaat("West"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Rainbow"), nullptr, &sky_data.west.rainbow, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Red", nullptr, &sky_data.west.r, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Green", nullptr, &sky_data.west.g, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Blue", nullptr, &sky_data.west.b, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<float>>("Brightness", nullptr, &sky_data.west.brightness, 1.0f, 1000.0f, 1.0f);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						sky_data.west.changed = true;
						std::fill_n(g_GameFunctions->m_west_azimuth_patch, 4, '\x90');
						uintptr_t west_red = scan_address(g_base_address + 0x26CFAE0, {});
						uintptr_t west_green = scan_address(g_base_address + 0x26CFAE4, {});
						uintptr_t west_blue = scan_address(g_base_address + 0x26CFAE8, {});

						*(float*)west_red = (sky_data.west.r / 255.f) * sky_data.west.brightness;
						*(float*)west_green = (sky_data.west.g / 255.f) * sky_data.west.brightness;
						*(float*)west_blue = (sky_data.west.b / 255.f) * sky_data.west.brightness;
					});

			});
		g_Render->draw_submenu<sub>(("South & North"), rage::joaat("SouthNorth"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Rainbow"), nullptr, &sky_data.southnorth.rainbow, BoolDisplay::OnOff);
				sub->draw_option<number<std::int32_t>>("Red", nullptr, &sky_data.southnorth.r, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Green", nullptr, &sky_data.southnorth.g, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<std::int32_t>>("Blue", nullptr, &sky_data.southnorth.b, 0, 255, 1, 3, true, "", "", [] {

					});
				sub->draw_option<number<float>>("Brightness", nullptr, &sky_data.southnorth.brightness, 1.0f, 1000.0f, 1.0f);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						sky_data.southnorth.changed = true;
						std::fill_n(g_GameFunctions->m_azimuth_transition_patch, 7, '\x90');
						uintptr_t west_red = scan_address(g_base_address + 0x26CFB10, {});
						uintptr_t west_green = scan_address(g_base_address + 0x26CFB14, {});
						uintptr_t west_blue = scan_address(g_base_address + 0x26CFB18, {});

						*(float*)west_red = (sky_data.southnorth.r / 255.f) * sky_data.southnorth.brightness;
						*(float*)west_green = (sky_data.southnorth.g / 255.f) * sky_data.southnorth.brightness;
						*(float*)west_blue = (sky_data.southnorth.b / 255.f) * sky_data.southnorth.brightness;
					});

			});
		g_Render->draw_submenu<sub>(("Time"), rage::joaat("TimeWORLD"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Freeze"), "", &freeze_time, BoolDisplay::OnOff, false, [] {});
				sub->draw_option<toggle<bool>>(("Sync"), "", &time_gta.sync, BoolDisplay::OnOff, false, [] {});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Unit", nullptr, &time_gta.type, &time_gta.pos);
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});

				if (time_gta.pos == 0) {
					sub->draw_option<number<std::int32_t>>("Value", nullptr, &time_gta.second, 0, 60, 1, 3, true, "", "", [] {
						NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(time_gta.hour, time_gta.min, time_gta.second);
						CLOCK::SET_CLOCK_TIME(time_gta.hour, time_gta.min, time_gta.second);
						});
				}
				if (time_gta.pos == 1) {
					sub->draw_option<number<std::int32_t>>("Value", nullptr, &time_gta.min, 0, 60, 1, 3, true, "", "", [] {
						NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(time_gta.hour, time_gta.min, time_gta.second);
						CLOCK::SET_CLOCK_TIME(time_gta.hour, time_gta.min, time_gta.second);
						});
				}
				if (time_gta.pos == 2) {
					sub->draw_option<number<std::int32_t>>("Value", nullptr, &time_gta.hour, 0, 24, 1, 3, true, "", "", [] {
						NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(time_gta.hour, time_gta.min, time_gta.second);
						CLOCK::SET_CLOCK_TIME(time_gta.hour, time_gta.min, time_gta.second);
						});
				}
			});
		g_Render->draw_submenu<sub>(("Creator"), rage::joaat("Creator"), [](sub* sub)
			{
				sub->draw_option<submenu>("Object", nullptr, rage::joaat("Objects"));
				sub->draw_option<toggle<bool>>(("Enabled"), "", &m_creator.enabled, BoolDisplay::OnOff, false, [] {
					if (!m_creator.enabled)
					{
						NativeVector3 c = CAM::GET_CAM_COORD(m_creator.creator_cam);
						NativeVector3 rot = CAM::GET_CAM_ROT(m_creator.creator_cam, 2);
						CAM::RENDER_SCRIPT_CAMS(false, true, 700, true, true, true);
						CAM::SET_CAM_ACTIVE(m_creator.creator_cam, false);
						CAM::DESTROY_CAM(m_creator.creator_cam, true);
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), true);
						ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);



					}
					});
				sub->draw_option<toggle<bool>>(("Frozen"), "", &m_creator.frozen, BoolDisplay::OnOff, false, [] {});
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				for (auto& object : m_creator.m_Objects) {
					sub->draw_option<RegularOption>(object.m_model.c_str(), nullptr, [=]
						{

							m_creator.m_selected = object.m_model;


						});

				}




			});
		g_Render->draw_submenu<sub>(("Object"), rage::joaat("Objects"), [](sub* sub)
			{

				sub->draw_option<KeyboardOption>(("Add To List"), nullptr, m_creator.selected_object_name, []
					{
						showKeyboard("Enter Something", "", 25, &m_creator.selected_buffer, [] {
							Hash hash = MISC::GET_HASH_KEY(m_creator.selected_buffer.c_str());
							if (STREAMING::IS_MODEL_VALID(hash) && !STREAMING::IS_MODEL_A_PED(hash) && !STREAMING::IS_MODEL_A_VEHICLE(hash)) {
								m_creator.m_Objects.push_back({ m_creator.selected_buffer });

								m_creator.selected_object_name = "~g~" + m_creator.selected_buffer;

							}
							else {

								m_creator.selected_object_name = "~r~" + m_creator.selected_buffer;
							}
							});
					});
				sub->draw_option<UnclickOption>(("Delete"), nullptr, [] {});
				sub->draw_option<RegularOption>("Clear", nullptr, [=]
					{
						m_creator.m_Objects.clear();
					});



			});
		g_Render->draw_submenu<sub>(("Nearby Manager"), NearbyManager, [](sub* sub)
			{
				sub->draw_option<submenu>("Traffic", nullptr, NearbyVehicles);
				sub->draw_option<submenu>("Pedestrians", nullptr, NearbyPeds);

			});
		g_Render->draw_submenu<sub>(("Pedestrians"), NearbyPeds, [](sub* sub)
			{
				sub->draw_option<submenu>("ESP", nullptr, rage::joaat("PedESP"));
				sub->draw_option<toggle<bool>>(("Grapple Hook"), nullptr, &m_nearby.m_peds.enabled, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Riot"), nullptr, &m_nearby.m_peds.riot, BoolDisplay::OnOff, false, [] {
					if (!m_nearby.m_peds.riot) {
						MISC::SET_RIOT_MODE_ENABLED(false);
					}
					});
				sub->draw_option<RegularOption>(("Explode"), nullptr, []
					{
						Ped* peds = new Ped[(10 * 2 + 2)];
						peds[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, 0); i++)
						{
							Ped ped = peds[(i * 2 + 2)];
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(ped, false);
							FIRE::ADD_EXPLOSION(c.x, c.y, c.z, 0, 100000.f, true, false, 0.0f, false);

						}
						delete peds;
					});
				sub->draw_option<RegularOption>(("Kill"), nullptr, []
					{
						Ped* peds = new Ped[(10 * 2 + 2)];
						peds[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, 0); i++)
						{
							Ped ped = peds[(i * 2 + 2)];
							PED::APPLY_DAMAGE_TO_PED(ped, PED::GET_PED_MAX_HEALTH(ped) * 2, false, 0);

						}
						delete peds;
					});
				sub->draw_option<RegularOption>(("Delete"), nullptr, []
					{
						Ped* peds = new Ped[(10 * 2 + 2)];
						peds[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, 0); i++)
						{
							Ped ped = peds[(i * 2 + 2)];
							ENTITY::DELETE_ENTITY(&ped);

						}
						delete peds;
					});
				sub->draw_option<RegularOption>(("Hands Up"), nullptr, []
					{
						Ped* peds = new Ped[(10 * 2 + 2)];
						peds[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, 0); i++)
						{
							Ped ped = peds[(i * 2 + 2)];
							TASK::TASK_HANDS_UP(ped, 5000, PLAYER::PLAYER_PED_ID(), 0, 0);

						}
						delete peds;
					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Jump", nullptr, &jump_type, &jump_int, false, -1, [] {
					Ped* peds = new Ped[(10 * 2 + 2)];
					peds[0] = 10;
					for (int i = 0; i < PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, 0); i++)
					{
						Ped ped = peds[(i * 2 + 2)];
						switch (jump_int) {
						case 0:
							TASK::TASK_JUMP(ped, false, false, false);
							break;
						case 1:
							TASK::TASK_JUMP(ped, true, true, true);
							break;
						}

					}
					delete peds;
					});

			});
		g_Render->draw_submenu<sub>(("ESP"), rage::joaat("PedESP"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Name"), nullptr, &m_nearby.m_peds.name_esp, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Rectangle"), nullptr, &m_nearby.m_peds.rectangle, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Traffic"), NearbyVehicles, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Horn"), nullptr, &m_nearby.m_traffic.horn, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Max Loop"), nullptr, &m_nearby.m_traffic.max_loop, BoolDisplay::OnOff);
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Rainbow", nullptr, &m_nearby.m_traffic.rainbow, &m_nearby.m_traffic.rainbow_type, &m_nearby.m_traffic.rainbow_int);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Acrobatics", nullptr, &acrobatic_type, &m_nearby.m_traffic.acrobatic, false, -1, [] {
					if (m_nearby.m_traffic.acrobatic == 0) {
						Vehicle* vehicles = new Vehicle[(10 * 2 + 2)];
						vehicles[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehicles); i++)
						{
							Vehicle playerVehicle = vehicles[(i * 2 + 2)];
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);

						}
						delete vehicles;


					}
					if (m_nearby.m_traffic.acrobatic == 1) {
						Vehicle* vehicles = new Vehicle[(10 * 2 + 2)];
						vehicles[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehicles); i++)
						{
							Vehicle playerVehicle = vehicles[(i * 2 + 2)];
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 9.0f, 0, -2.0f, 0, true, true, true, true, false, true);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 9.0f, 0, -2.0f, 0, true, true, true, true, false, true);
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 9.0f, 0, -2.0f, 0, true, true, true, true, false, true);

						}
						delete vehicles;

					}
					if (m_nearby.m_traffic.acrobatic == 2) {
						Vehicle* vehicles = new Vehicle[(10 * 2 + 2)];
						vehicles[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehicles); i++)
						{
							Vehicle playerVehicle = vehicles[(i * 2 + 2)];
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 10.0f, 20.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);

						}
						delete vehicles;

					}
					if (m_nearby.m_traffic.acrobatic == 3) {
						Vehicle* vehicles = new Vehicle[(10 * 2 + 2)];
						vehicles[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehicles); i++)
						{
							Vehicle playerVehicle = vehicles[(i * 2 + 2)];
							ENTITY::APPLY_FORCE_TO_ENTITY(playerVehicle, true, 0, 0, 7.0f, 0, 0, 0, true, true, true, true, false, true);

						}
						delete vehicles;




					}
					});

				sub->draw_option<RegularOption>(("Teleport To Me"), nullptr, []
					{
						Vehicle* vehicles = new Vehicle[(10 * 2 + 2)];
						vehicles[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehicles); i++)
						{
							Vehicle playerVehicle = vehicles[(i * 2 + 2)];
							NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
							ENTITY::SET_ENTITY_COORDS2(playerVehicle, self_coords, false, false, false, false);

						}
						delete vehicles;
					});
				sub->draw_option<RegularOption>(("Max"), nullptr, []
					{
						Vehicle* vehicles = new Vehicle[(10 * 2 + 2)];
						vehicles[0] = 10;
						for (int i = 0; i < PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehicles); i++)
						{
							Vehicle playerVehicle = vehicles[(i * 2 + 2)];
							VEHICLE::SET_VEHICLE_MOD_KIT(playerVehicle, 0);
							for (int i = 0; i < 50; i++)
							{
								VEHICLE::SET_VEHICLE_MOD(playerVehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(playerVehicle, i) - 1), false);

							}
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));

						}
						delete vehicles;
					});

			});
		g_Render->draw_submenu<sub>(("Weather"), SubmeuWeather, [](sub* sub)
			{
				sub->draw_option<toggle_number_option<std::int32_t, bool>>("Randomize", nullptr, &weather.randomize, &weather.randomize_delay, 0, 5000, 50);
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &weather.data, &weather.init);
				sub->draw_option<RegularOption>(("Apply"), nullptr, []
					{
						if (weather.init == 0) {
							weather.override("ExtraSunny");
						}
						if (weather.init == 1) {
							weather.override("Clouds");
						}
						if (weather.init == 2) {
							weather.override("Smog");
						}
						if (weather.init == 3) {
							weather.override("Foggy");
						}
						if (weather.init == 4) {
							weather.override("Overcast");
						}
						if (weather.init == 5) {
							weather.override("Rain");
						}
						if (weather.init == 6) {
							weather.override("Clearing");
						}
						if (weather.init == 7) {
							weather.override("Neutral");
						}
						if (weather.init == 8) {
							weather.override("Snow");
						}
						if (weather.init == 9) {
							weather.override("Blizzard");
						}
						if (weather.init == 10) {
							weather.override("SnowLight");
						}
						if (weather.init == 11) {
							weather.override("XMAS");
						}
						if (weather.init == 12) {
							weather.override("Halloween");
						}
						if (weather.init == 13) {
							weather.override("Clear");
						}
					});

			});
		g_Render->draw_submenu<sub>("Misc", SubmenuMisc, [](sub* sub)
			{

				sub->draw_option<submenu>("Replace Text", nullptr, SubmenuReplaceText);
				sub->draw_option<submenu>("FOV", nullptr, SubmenuFOV);
				sub->draw_option<submenu>("Disables", nullptr, Disables);
				sub->draw_option<submenu>("HUD", nullptr, rage::joaat("HUDFORT"));
				sub->draw_option<submenu>("Phone", nullptr, rage::joaat("Phone"));
				sub->draw_option<submenu>("Cutscene", nullptr, rage::joaat("Cutscene"));
				//sub->draw_option<toggle<bool>>(("Use Stunt Jump Camera"), nullptr, &features.use_stunt_jump_camera, BoolDisplay::OnOff); dont work sadly

			});
		g_Render->draw_submenu<sub>("Cutscene", rage::joaat("Cutscene"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Stop (Loop)"), nullptr, &features.stop_cut, BoolDisplay::OnOff);
				sub->draw_option<RegularOption>(("Stop"), nullptr, []
					{
						CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();

					});
				sub->draw_option<RegularOption>(("Set Skippable"), nullptr, []
					{
						CUTSCENE::SET_CUTSCENE_CAN_BE_SKIPPED(0);

					});
			});
		g_Render->draw_submenu<sub>("Phone", rage::joaat("Phone"), [](sub* sub)
			{
				PAD::DISABLE_CONTROL_ACTION(2, 172, true);
				PAD::DISABLE_CONTROL_ACTION(2, 173, true);
				PAD::DISABLE_CONTROL_ACTION(2, 174, true);
				PAD::DISABLE_CONTROL_ACTION(2, 175, true);
				PAD::DISABLE_CONTROL_ACTION(2, 176, true);
				PAD::DISABLE_CONTROL_ACTION(2, 177, true);
				NativeVector3 coords;
				MOBILE::GET_MOBILE_PHONE_POSITION(&coords);
				sub->draw_option<toggle<bool>>(("Disable"), nullptr, &phone.disable, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Attributes"), nullptr, [] {});
				sub->draw_option<toggle_number_option<float, bool>>("Scale", nullptr, &phone.scaler, &phone.scale, 1.f, 10000.f, 1.0f, 2, false, "", "", [] {
					if (!phone.scaler) {
						MOBILE::SET_MOBILE_PHONE_SCALE(500.0f);
					}
					});
				sub->draw_option<number<std::int32_t>>("X", nullptr, &phone.x, -1000, 1000, 1, 3, true, "", "", [=] {
					MOBILE::SET_MOBILE_PHONE_POSITION(phone.x, coords.y, coords.z);
					});
				sub->draw_option<number<std::int32_t>>("Y", nullptr, &phone.y, -1000, 1000, 1, 3, true, "", "", [=] {
					MOBILE::SET_MOBILE_PHONE_POSITION(coords.x, phone.y, coords.z);
					});
				sub->draw_option<number<std::int32_t>>("Z", nullptr, &phone.z, -1000, 1000, 1, 3, true, "", "", [=] {
					MOBILE::SET_MOBILE_PHONE_POSITION(coords.x, coords.y, phone.z);
					});
				sub->draw_option<number<std::int32_t>>("Pitch", nullptr, &phone.rotx, -1000, 1000, 1, 3, true, "", "", [=] {
					MOBILE::SET_MOBILE_PHONE_ROTATION(phone.rotx, phone.roty, phone.rotz, 0);
					});
				sub->draw_option<number<std::int32_t>>("Roll", nullptr, &phone.roty, -1000, 1000, 1, 3, true, "", "", [=] {
					MOBILE::SET_MOBILE_PHONE_ROTATION(phone.rotx, phone.roty, phone.rotz, 0);
					});
				sub->draw_option<number<std::int32_t>>("Yaw", nullptr, &phone.rotz, -1000, 1000, 1, 3, true, "", "", [=] {
					MOBILE::SET_MOBILE_PHONE_ROTATION(phone.rotx, phone.roty, phone.rotz, 0);
					});
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Get Older Versions", nullptr, &phone.type, &phone.pos, false, -1, [=] {
					switch (phone.pos) {
					case 0:
						MOBILE::CREATE_MOBILE_PHONE(0);
						break;
					case 1:
						MOBILE::CREATE_MOBILE_PHONE(1);
						break;
					case 2:
						MOBILE::CREATE_MOBILE_PHONE(2);
						break;
					case 3:
						MOBILE::CREATE_MOBILE_PHONE(4);
						break;
					}
					});
			});
		g_Render->draw_submenu<sub>("HUD", rage::joaat("HUDFORT"), [](sub* sub)
			{
				sub->draw_option<submenu>("Wanted Level", nullptr, rage::joaat("WantedLevelHUD"));
				sub->draw_option<submenu>("Minimap", nullptr, rage::joaat("Minimap"));
			});
		g_Render->draw_submenu<sub>("Minimap", rage::joaat("Minimap"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Hide"), nullptr, &features.hide_map, BoolDisplay::OnOff, false, [] {
					if (!features.hide_map) {
						HUD::DISPLAY_RADAR(true);
					}
					});
				sub->draw_option<toggle<bool>>(("Reveal"), nullptr, &minimap.hide_fow, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Force Exterior"), nullptr, &minimap.force_exterior, BoolDisplay::OnOff);
				if (!features.hide_map) {
					sub->draw_option<number<std::int32_t>>("Zoom", nullptr, &minimap.zoom, 0, 200, 1, 3, true, "", "", [] {
						HUD::SET_RADAR_ZOOM(minimap.zoom);
						});
				}
			});
		g_Render->draw_submenu<sub>("Wanted Level", rage::joaat("WantedLevelHUD"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Disable Wanted Stars"), nullptr, &features.disable_wanted_stars, BoolDisplay::OnOff);
				if (!features.disable_wanted_stars) {
					sub->draw_option<number<std::int32_t>>("Fake", nullptr, &features.fake_wanted_levels, 0, 6, 1, 0, true, "", "", [] {
						MISC::SET_FAKE_WANTED_LEVEL(features.fake_wanted_levels);
						});
				}
			});
		g_Render->draw_submenu<sub>("Disables", Disables, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Recording"), nullptr, &m_disables.recording, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Cinematics"), nullptr, &m_disables.cin, BoolDisplay::OnOff, false, [] {
					if (!m_disables.cin) {
						CAM::SET_CINEMATIC_BUTTON_ACTIVE(true);
					}
					});
				sub->draw_option<toggle<bool>>(("Stunt Jumps"), nullptr, &m_disables.stuntjumps, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Idle Camera"), nullptr, &m_disables.idle_cam, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>(("Wanted Music"), "", &features.disable_wanted_music, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>("FOV", SubmenuFOV, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &m_fov.enabled, BoolDisplay::OnOff, false, [] {
					if (!m_fov.enabled) {
						CAM::RENDER_SCRIPT_CAMS(false, true, 700, true, true, true);
						CAM::SET_CAM_ACTIVE(m_fov.freecamCamera, false);
						CAM::DESTROY_CAM(m_fov.freecamCamera, true);
					}
					});
				sub->draw_option<number<float>>("Value", nullptr, &m_fov.value, 1.0f, 130.0f, 1.0f, 2);
			});
		g_Render->draw_submenu<sub>("Replace Text", SubmenuReplaceText, [](sub* sub)
			{

				sub->draw_option<RegularOption>(("Enter Text"), nullptr, []
					{

						showKeyboard("Enter Something", "", 25, &replaceTextBuffer, [] {
							replaced = true;
							});
					});
				sub->draw_option<RegularOption>(("Enter Second Text"), nullptr, []
					{

						showKeyboard("Enter Something", "", 25, &replaceTextBuffer2, [] {
							replaced2 = true;
							});
					});
				sub->draw_option<RegularOption>(("Replace"), nullptr, []
					{
						if (replaced || replaced2) {
							g_CustomText->AddText(MISC::GET_HASH_KEY(replaceTextBuffer.c_str()), replaceTextBuffer2.c_str());
						}

					});
				if (replaced || replaced2) {
					sub->draw_option<UnclickOption>(("Input"), nullptr, [] {});
					char inputfr[64];
					sprintf(inputfr, "%s>%s", replaceTextBuffer.c_str(), replaceTextBuffer2.c_str());
					sub->draw_option<RegularOption>(inputfr, "");
				}
			});
		g_Render->draw_submenu<sub>(("Demo"), SubmenuTest, [](sub* sub)
			{
				sub->draw_option<submenu>("Submenu Option", nullptr, SubmenuDemo);

				sub->draw_option<RegularOption>(("Regular Option"), nullptr, []
					{
						g_Logger->Info("You pressed the test option");
					});

				static bool testBool1{};
				sub->draw_option<toggle<bool>>(("Bool Option"), nullptr, &testBool1, BoolDisplay::OnOff);

				sub->draw_option<UnclickOption>(("Unclickable Option"), nullptr, [] {});

				static std::int32_t int32Test{ 1337 };
				static std::int32_t in32Test22{ 1337 };
				static bool in32Test2 = false;
				sub->draw_option<toggle_number_option<std::int32_t, bool>>("Hey", nullptr, &in32Test2, &int32Test, 0, 1337);
				sub->draw_option<number<std::int32_t>>("Int32", nullptr, &int32Test, 0, 1337);

				static std::int64_t int64Test{ 1337 };
				sub->draw_option<number<std::int64_t>>("Int64", nullptr, &int64Test, 0, 1337, 10);

				static float floatTest{ 1337.f };
				sub->draw_option<number<float>>("Float", nullptr, &floatTest, 0.f, 1337.f, 0.1f, 1);

				static std::vector<std::uint64_t> vector{ 1, 2, 3 };
				static std::size_t vectorPos{};
				static bool arraytest = false;
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Array", nullptr, &Lists::DemoList, &Lists::DemoListPos);
				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Array", nullptr, &arraytest, &Lists::DemoList, &Lists::DemoListPos);
				sub->draw_option<ChooseOption<std::uint64_t, std::size_t>>("Vector", nullptr, &vector, &vectorPos);
			});
		g_Render->draw_submenu<sub>("Translations", SubMenuTranslations, [](sub* sub)
			{
				namespace fs = std::filesystem;
				fs::directory_iterator dirIt{ "C:\\Saint\\Translations" };
				for (auto&& dirEntry : dirIt) {
					if (dirEntry.is_regular_file()) {
						auto path = dirEntry.path();
						if (path.has_filename()) {

							sub->draw_option<RegularOption>((reinterpret_cast<const char*>(path.stem().u8string().data())), nullptr, [=]
								{
									if (Translations::LoadTranslation(reinterpret_cast<const char*>(path.u8string().data())))
										g_Logger->Info("Successfully Loaded translation");
									else
										g_Logger->Error("Error loading translation");
								});
						}
					}
				}
			});
		g_Render->draw_submenu<sub>("Settings", SubmenuSettings, [](sub* sub)
			{
				sub->draw_option<submenu>("Customization", nullptr, Customization);
				sub->draw_option<submenu>("Positions", nullptr, Positions);
				sub->draw_option<submenu>("Colors", nullptr, SubmenuColors);
				sub->draw_option<submenu>("Themes", nullptr, SubmenuThemes);
				sub->draw_option<submenu>("Hotkeys", nullptr, rage::joaat("Hotkeys"));
				sub->draw_option<submenu>("Translations", nullptr, SubMenuTranslations);










				sub->draw_option<RegularOption>("Unload", nullptr, []
					{
						g_Running = false;
					});
			});
		g_Render->draw_submenu<sub>(("Hotkeys"), rage::joaat("Hotkeys"), [](sub* sub)
			{
				sub->draw_option<RegularOption>("Clear", nullptr, []
					{
						m_Hotkeys.clear();
					});
				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				for (auto& hotkey : m_Hotkeys) {
					sub->draw_option<KeyboardOption>((hotkey.name.c_str()), nullptr, std::to_string(hotkey.key), []
						{

						});
				}
			});
		g_Render->draw_submenu<sub>(("Themes"), SubmenuThemes, [](sub* sub)
			{

				sub->draw_option<RegularOption>(("Save"), nullptr, [=]
					{
						showKeyboard("Enter Something", "", 25, &g_ThemeLoading.buffer, [] {
							g_ThemeLoading.save(g_ThemeLoading.buffer);
							});


					});

				sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
				if (std::filesystem::exists("C:\\Saint\\Themes\\") && std::filesystem::is_directory("C:\\Saint\\Themes\\")) {

					namespace fs = std::filesystem;
					fs::directory_iterator dirIt{ "C:\\Saint\\Themes\\" };
					for (auto&& dirEntry : dirIt)
					{
						if (dirEntry.is_regular_file())
						{
							auto path = dirEntry.path();
							if (path.has_filename())
							{
								if (path.extension() == ".ini")
								{

									char nigger[64];
									sprintf(nigger, "%s", path.stem().u8string().c_str());
									sub->draw_option<RegularOption>(nigger, nullptr, [=]
										{
											g_ThemeLoading.load(nigger);
										});

								}

							}
						}
					}
				}
				else {
					std::filesystem::create_directory("C:\\Saint\\Themes\\");
				}



			});
		g_Render->draw_submenu<sub>(("Positions"), Positions, [](sub* sub)
			{

				sub->draw_option<submenu>("Base", nullptr, PositionsMenu);
				sub->draw_option<submenu>("Globe", nullptr, PositionsGlobe);


			});
		g_Render->draw_submenu<sub>(("Base"), PositionsMenu, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("Move With Mouse", "Works best in fullscreen.", &features.move_with_mouse, BoolDisplay::OnOff, false, [] {
					g_Settings.m_LockMouse = false;
					});
				sub->draw_option<number<float>>("X", nullptr, &g_Render->m_PosX, 0.f, 1.f, 0.01f, 2);
				sub->draw_option<number<float>>("Y", nullptr, &g_Render->m_PosY, 0.f, 1.f, 0.01f, 2);
				sub->draw_option<RegularOption>("Reset", nullptr, [=]
					{
						g_Render->m_PosX = 0.18f;
						g_Render->m_PosY = 0.1f;
					});


			});
		g_Render->draw_submenu<sub>(("Globe"), PositionsGlobe, [](sub* sub)
			{

				sub->draw_option<number<float>>("X Offset", nullptr, &g_Render->glare_x_offset, -1000.f, 1000.f, 0.002f, 3);


			});
		g_Render->draw_submenu<sub>(("Customization"), Customization, [](sub* sub)
			{
				sub->draw_option<submenu>("Base", nullptr, CustomizationBase);
				sub->draw_option<submenu>("Header", nullptr, CustomizationHeader);
				sub->draw_option<submenu>("Subheader", nullptr, CustomizationSubheader);
				sub->draw_option<submenu>("Option Selected", nullptr, rage::joaat("OptionSele"));
				sub->draw_option<submenu>("Toggles", nullptr, CustomizationToggles);
				sub->draw_option<submenu>("Footer", nullptr, SubmenuSettingsFooter);
				sub->draw_option<submenu>("Break", nullptr, rage::joaat("Break"));
				sub->draw_option<submenu>("Submenu", nullptr, rage::joaat("SubmenuIndc"));
				sub->draw_option<submenu>("Rainbow", nullptr, rage::joaat("RainbowGay"));
				sub->draw_option<toggle<bool>>("Lines", nullptr, &g_Render->lines_enabled, BoolDisplay::OnOff);
				sub->draw_option<number<float>>("Text Size", nullptr, &g_Render->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);
				//sub->draw_option<ChooseOption<const char*, std::size_t>>("Resolution", nullptr, &g_Render->Resolution, &g_Render->reso);


			});
		g_Render->draw_submenu<sub>(("Rainbow"), rage::joaat("RainbowGay"), [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("Header Background", nullptr, &rainbow_ui.main, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Option Selected"), rage::joaat("OptionSele"), [](sub* sub)
			{
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
			});
		g_Render->draw_submenu<sub>(("Submenu"), rage::joaat("SubmenuIndc"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>(("Indicators"), nullptr, &g_Render->IndicatorList, &g_Render->IndicatorIterator);
				if (g_Render->IndicatorIterator == 1) {
					sub->draw_option<number<std::int32_t>>("Alpha", nullptr, &g_Render->sub_alpha, 0, 255);
				}
			});
		g_Render->draw_submenu<sub>(("Break"), rage::joaat("Break"), [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Font", nullptr, &g_Render->HeaderFont, &g_Render->HeaderFontIterator2, true, -1, []
					{
						if (g_Render->HeaderFontIterator2 == 0) {
							g_Render->m_SeperatorFont = Font::ChaletLondon;
						}
						if (g_Render->HeaderFontIterator2 == 1) {
							g_Render->m_SeperatorFont = Font::HouseScript;
						}
						if (g_Render->HeaderFontIterator2 == 2) {
							g_Render->m_SeperatorFont = Font::Monospace;
						}
						if (g_Render->HeaderFontIterator2 == 3) {
							g_Render->m_SeperatorFont = Font::Wingdings;
						}
						if (g_Render->HeaderFontIterator2 == 4) {
							g_Render->m_SeperatorFont = Font::ChaletComprimeCologne;
						}
						if (g_Render->HeaderFontIterator2 == 5) {
							g_Render->m_SeperatorFont = Font::Pricedown;
						}
					});
				sub->draw_option<UnclickOption>(("Preview"), nullptr, [] {});
			});
		g_Render->draw_submenu<sub>(("Toggles"), CustomizationToggles, [](sub* sub)
			{
				g_Render->toggle_show_on = true;
				g_Render->toggle_show_off = false;
				sub->draw_option<ChooseOption<const char*, std::size_t>>(("Icon"), nullptr, &g_Render->ToggleList, &g_Render->ToggleIterator);
				sub->draw_option<UnclickOption>(("On"), nullptr, [] {});
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->toggle_height, -1000.f, 1000.f, 0.001f);
				sub->draw_option<number<float>>("Width", nullptr, &g_Render->toggle_width, -1000.f, 1000.f, 0.001f);
				sub->draw_option<UnclickOption>(("Off"), nullptr, [] {});
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->toggle_height_off, -1000.f, 1000.f, 0.001f);
				sub->draw_option<number<float>>("Width", nullptr, &g_Render->toggle_width_off, -1000.f, 1000.f, 0.001f);
				sub->draw_option<UnclickOption>(("Rotation"), nullptr, [] {});
				sub->draw_option<number<float>>("On", nullptr, &g_Render->toggle_on_rotation, 0.0f, 360.f, 1, 1);
				sub->draw_option<number<float>>("Off", nullptr, &g_Render->toggle_off_rotation, 0.0f, 360.f, 1, 1);
				sub->draw_option<UnclickOption>(("Preview"), nullptr, [] {});
				sub->draw_option<toggle<bool>>("On", nullptr, &g_Render->toggle_show_on, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>("Off", nullptr, &g_Render->toggle_show_off, BoolDisplay::OnOff);
				if (g_Render->ToggleIterator == 4) {
					sub->draw_option<UnclickOption>(("Custom"), nullptr, [] {});
					sub->draw_option<KeyboardOption>(("Directory"), nullptr, g_Render->custom_toggle_dict_on, []
						{
							showKeyboard("Enter Something", "", 25, &g_Render->custom_toggle_dict_on, [] {});
						});
					sub->draw_option<KeyboardOption>(("Asset"), nullptr, g_Render->custom_toggle_asset_on, []
						{
							showKeyboard("Enter Something", "", 25, &g_Render->custom_toggle_asset_on, [] {});
						});
					sub->draw_option<KeyboardOption>(("Directory Off"), nullptr, g_Render->custom_toggle_dict_off, []
						{
							showKeyboard("Enter Something", "", 25, &g_Render->custom_toggle_dict_off, [] {});
						});
					sub->draw_option<KeyboardOption>(("Asset Off"), nullptr, g_Render->custom_toggle_asset_off, []
						{
							showKeyboard("Enter Something", "", 25, &g_Render->custom_toggle_asset_off, [] {});
						});
				}


			});
		g_Render->draw_submenu<sub>(("Subheader"), CustomizationSubheader, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("Enabled", nullptr, &g_Render->submenu_enabled, BoolDisplay::OnOff);
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->m_SubheaderHeight, 0.01f, 0.2f, 0.001f, 3);


			});
		g_Render->draw_submenu<sub>(("Base"), CustomizationBase, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("Glare", nullptr, &g_Render->m_render_glare, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>("Sounds", nullptr, &g_Render->m_Sounds, BoolDisplay::OnOff);
				sub->draw_option<number<float>>("Width", nullptr, &g_Render->m_Width, 0.01f, 1.f, 0.01f, 2);
				sub->draw_option<number<float>>("Smooth Scroll Speed", nullptr, &g_Render->smooth_scroll_speed, 0.01f, 1.00f, 0.01f, 2);


			});
		g_Render->draw_submenu<sub>(("Header"), CustomizationHeader, [](sub* sub)
			{
				sub->draw_option<KeyboardOption>(("Text"), nullptr, g_Render->header_name, []
					{
						showKeyboard("Enter Something", "", 25, &g_Render->header_name, [] {});
					});
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
				sub->draw_option<number<float>>("Text X Offset", nullptr, &g_Render->header_x_offset, -1000.f, 1000.f, 0.001f);


			});
		g_Render->draw_submenu<sub>(("Colors"), SubmenuColors, [](sub* sub)
			{

				//sub->draw_option<submenu>("Header", nullptr, SubmenuSettingsHeader);
				//sub->draw_option<submenu>("Footer Text", nullptr, SubmenuSettingsSubmenuBar);
				//sub->draw_option<submenu>("Options", nullptr, SubmenuSettingsOption);
				//sub->draw_option<submenu>("Footer", nullptr, SubmenuSettingsFooter);
				//sub->draw_option<submenu>("Toggles", nullptr, SubmenuToggles);
				//sub->draw_option<submenu>("Description", nullptr, SubmenuSettingsDescription);
				sub->draw_option<submenu>("Header Background", nullptr, SubmenuHeaderColor);
				sub->draw_option<submenu>("Header Text", nullptr, SubmenuHeaderText);
				sub->draw_option<submenu>("Background Selected", nullptr, SubmenuOptionSelectedBackground);
				sub->draw_option<submenu>("Background Unselected", nullptr, SubmenuOptionUnselectedBackground);
				sub->draw_option<submenu>("Text Selected", nullptr, OptionTextSelected);
				sub->draw_option<submenu>("Text Unselected", nullptr, OptionTextUnselected);
				sub->draw_option<submenu>("Footer Background", nullptr, FooterBackground);
				sub->draw_option<submenu>("Footer Sprite", nullptr, FooterSprite);
				sub->draw_option<submenu>("Subheader Background", nullptr, SubheaderBackground);
				sub->draw_option<submenu>("Subheader Text Left", nullptr, SubheaderTextLeft);
				sub->draw_option<submenu>("Subheader Text Right", nullptr, SubheaderTextRight);


			});
		g_Render->draw_submenu<sub>(("Subheader Background"), SubheaderBackground, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_SubheaderBackground.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_SubheaderBackground.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_SubheaderBackground.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_SubheaderBackground.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Subheader Text Left"), SubheaderTextLeft, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_SubheaderText.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_SubheaderText.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_SubheaderText.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_SubheaderText.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Subheader Text Right"), SubheaderTextRight, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_SubheaderTextRight.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_SubheaderTextRight.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_SubheaderTextRight.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_SubheaderTextRight.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Header Background"), SubmenuHeaderColor, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_HeaderBackgroundColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_HeaderBackgroundColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_HeaderBackgroundColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_HeaderBackgroundColor.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Header Text"), SubmenuHeaderText, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_HeaderTextColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_HeaderTextColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_HeaderTextColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_HeaderTextColor.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Background Selected"), SubmenuOptionSelectedBackground, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_OptionSelectedBackgroundColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_OptionSelectedBackgroundColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_OptionSelectedBackgroundColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_OptionSelectedBackgroundColor.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Background Unselected"), SubmenuOptionUnselectedBackground, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Text Selected"), OptionTextSelected, [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_OptionSelectedTextColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_OptionSelectedTextColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_OptionSelectedTextColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_OptionSelectedTextColor.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Text Unselected"), OptionTextUnselected, [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_OptionUnselectedTextColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_OptionUnselectedTextColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_OptionUnselectedTextColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_OptionUnselectedTextColor.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Footer Background"), FooterBackground, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_FooterBackgroundColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_FooterBackgroundColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_FooterBackgroundColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_FooterBackgroundColor.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Footer Sprite"), FooterSprite, [](sub* sub)
			{

				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_FooterSpriteColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_FooterSpriteColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_FooterSpriteColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_FooterSpriteColor.a, 0, 255);

			});
		g_Render->draw_submenu<sub>(("Toggles"), SubmenuToggles, [](sub* sub)
			{
				sub->draw_option<submenu>("Color", nullptr, SubmenuTogglesColor);
				sub->draw_option<ChooseOption<const char*, std::size_t>>(("Icon"), nullptr, &g_Render->ToggleList, &g_Render->ToggleIterator);

			});
		g_Render->draw_submenu<sub>(("Color"), SubmenuTogglesColor, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("Automaticly Match", nullptr, &features.match, BoolDisplay::OnOff);

				sub->draw_option<ChooseOption<const char*, std::size_t>>("Toggled (Match)", nullptr, &g_Render->ThemeList, &Lists::MatchPos, true, -1, []
					{
						switch (Lists::MatchPos) {
						case 0:
							g_Render->m_ToggleOnColor = { 108, 60, 175, 255 };
							break;
						case 1:
							g_Render->m_ToggleOnColor = { 255, 108, 116, 255 };
							break;
						case 2:
							g_Render->m_ToggleOnColor = { 15, 82, 186, 255 };
							break;
						case 3:
							g_Render->m_ToggleOnColor = { 24, 26, 24, 255 };
							break;
						case 4:
							g_Render->m_ToggleOnColor = { 0, 155, 119, 255 };
							break;
						case 5:
							g_Render->m_ToggleOnColor = { 70, 38, 180, 255 };
							break;
						case 6:
							g_Render->m_ToggleOnColor = { 255, 145, 164, 255 };
							break;
						case 7:
							g_Render->m_ToggleOnColor = { 17, 17, 17, 255 };
							break;
						}

					});

				sub->draw_option<number<std::int32_t>>("Toggled (R)", nullptr, &g_Render->m_ToggleOnColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("Toggled (G)", nullptr, &g_Render->m_ToggleOnColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("Toggled (B)", nullptr, &g_Render->m_ToggleOnColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("Toggled (A)", nullptr, &g_Render->m_ToggleOnColor.a, 0, 255);
				sub->draw_option<RegularOption>("Reset", "", []
					{
						features.match = false;
						g_Render->m_ToggleOnColor = { 130, 214, 157, 255 };
					});

			});


		g_Render->draw_submenu<sub>(("Themes"), SubmenuThemes, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>(("Themes"), nullptr, &g_Render->ThemeList, &g_Render->ThemeIterator, false, -1, [] {
					if (g_Render->ThemeIterator == 0)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 108, 60, 175, 255 };

						//Footer
						g_Render->m_FooterBackgroundColor = { 108, 60, 175, 255 };

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 108, 60, 175, 255 };

						//Description
						g_Render->m_DescriptionBackgroundColor = { 108, 60, 175, 255 };

						//Background
						g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

						//Logger
						//g_Logger->Theme("Default Theme");
					}

					if (g_Render->ThemeIterator == 1)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 255, 108, 116, 255 };

						//Footer
						g_Render->m_FooterBackgroundColor = { 255, 108, 116, 255 };

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 255, 108, 116, 255 };

						//Description
						g_Render->m_DescriptionBackgroundColor = { 255, 108, 116, 255 };

						//Background
						g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

						//Logger
						//g_Logger->Theme("Salmon Red Theme");
					}

					if (g_Render->ThemeIterator == 2)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 15, 82, 186, 255 };

						//Footer
						g_Render->m_FooterBackgroundColor = { 15, 82, 186, 255 };

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 15, 82, 186, 255 };

						//Description
						g_Render->m_DescriptionBackgroundColor = { 15, 82, 186, 255 };

						//Background
						g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

						//Logger
						//g_Logger->Theme("Sapphire Blue Theme");
					}

					if (g_Render->ThemeIterator == 3)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 24, 26, 24, 255 };

						//Footer
						g_Render->m_FooterBackgroundColor = { 24, 26, 24, 255 };

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 24, 26, 24, 255 };

						//Description
						g_Render->m_DescriptionBackgroundColor = { 24, 26, 24, 255 };

						//Background
						g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

						//Logger
						//g_Logger->Theme("Soft Black Theme");
					}

					if (g_Render->ThemeIterator == 4)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 0, 155, 119, 255 };

						//Footer
						g_Render->m_FooterBackgroundColor = { 0, 155, 119, 255 };

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 0, 155, 119, 255 };

						//Description
						g_Render->m_DescriptionBackgroundColor = { 0, 155, 119, 255 };

						//Background
						g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

						//Logger
						//g_Logger->Theme("Emerald Green Theme");
					}

					if (g_Render->ThemeIterator == 5)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 70, 38, 180, 255 };

						//Footer
						g_Render->m_FooterBackgroundColor = { 70, 38, 180, 255 };

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 70, 38, 180, 255 };

						//Description
						g_Render->m_DescriptionBackgroundColor = { 70, 38, 180, 255 };

						//Background
						g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

						//Logger
						//g_Logger->Theme("Violet Purple Theme");
					}

					if (g_Render->ThemeIterator == 6)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 255, 145, 164, 255 };

						//Footer
						g_Render->m_FooterBackgroundColor = { 255, 145, 164, 255 };

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 255, 145, 164, 255 };

						//Description
						g_Render->m_DescriptionBackgroundColor = { 255, 145, 164, 255 };

						//Background
						g_Render->m_OptionUnselectedBackgroundColor = { 0, 0, 0, 160 };

						//Logger
						//g_Logger->Theme("Salmon Pink Theme");
					}

					if (g_Render->ThemeIterator == 7)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 17, 17, 17, 255 };

						//Footer
						g_Render->m_FooterBackgroundColor = { 17, 17, 17, 255 };
						g_Render->m_FooterSpriteColor = { 181,181,181, 255 };
						g_Render->m_FooterHeight = 0.030f;
						g_Render->m_FooterSpriteSize = 0.030f;

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 65, 60, 60, 255 };

						//Description
						g_Render->m_DescriptionBackgroundColor = { 0, 0, 0, 120 };

						//Background
						g_Render->m_OptionUnselectedBackgroundColor = { 30,35,36, 230 };

						//Option Height
						g_Render->m_OptionHeight = 0.033f;

						//Option Text Size
						g_Render->m_OptionTextSize = 0.29f;

						//Option Text Color
						g_Render->m_OptionUnselectedTextColor = { 181,181,181, 255 };
						g_Render->m_OptionSelectedTextColor = { 181,181,181, 255 };

						//Logger
						//g_Logger->Theme("Salmon Pink Theme");
					}
					if (g_Render->ThemeIterator == 8)
					{
						//Header
						g_Render->m_HeaderBackgroundColor = { 108, 60, 175, 255 };

						//Footer

						//Footer
						g_Render->m_FooterBackgroundColor = { 0, 0, 0, 255 };

						//Option
						g_Render->m_OptionSelectedBackgroundColor = { 255, 255, 255, 255 };

						//Description
						//g_Render->m_DescriptionBackgroundColor = { 234, 90, 81, 255 };

						//Background
						g_Render->m_OptionSelectedTextColor = { 0, 0, 0, 255 };

						g_Render->header_name = "Saint";

						g_Render->m_HeaderText = false;
						g_Render->m_HeaderNativeText = true;

						g_Render->submenu_enabled = true;

						g_Render->IndicatorIterator = 0;



						//Logger
						//g_Logger->Theme("North");
					}
					});
				sub->draw_option<RegularOption>("Random", "", []
					{
						g_Render->ThemeIterator = MISC::GET_RANDOM_INT_IN_RANGE(0, 8);
					});
			});

		g_Render->draw_submenu<sub>("Footer Text", SubmenuSettingsSubmenuBar, [](sub* sub)
			{
				sub->draw_option<number<float>>("Text Size", nullptr, &g_Render->m_FooterTextSize, 0.01f, 1.f, 0.01f, 2);
				sub->draw_option<toggle<bool>>("Left Text", nullptr, &g_Render->LeftFooterText, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>("Right Text", nullptr, &g_Render->RightFooterText, BoolDisplay::OnOff);
				sub->draw_option<UnclickOption>(("Colors"), nullptr, [] {});
				sub->draw_option<number<std::int32_t>>("Text R", nullptr, &g_Render->m_FooterTextColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("Text G", nullptr, &g_Render->m_FooterTextColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("Text B", nullptr, &g_Render->m_FooterTextColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("Text A", nullptr, &g_Render->m_FooterTextColor.a, 0, 255);
			});

		g_Render->draw_submenu<sub>("Options", SubmenuSettingsOption, [](sub* sub)
			{
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
				sub->draw_option<number<float>>("Text Size", nullptr, &g_Render->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);
				sub->draw_option<UnclickOption>(("Colors"), nullptr, [] {});
				sub->draw_option<number<std::int32_t>>("Selected Background R", nullptr, &g_Render->m_OptionSelectedBackgroundColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("Selected Background G", nullptr, &g_Render->m_OptionSelectedBackgroundColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("Selected Background B", nullptr, &g_Render->m_OptionSelectedBackgroundColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("Selected Background A", nullptr, &g_Render->m_OptionSelectedBackgroundColor.a, 0, 255);
				sub->draw_option<number<std::int32_t>>("Unselected Background R", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("Unselected Background G", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("Unselected Background B", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("Unselected Background A", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.a, 0, 255);

				sub->draw_option<number<std::int32_t>>("Selected Text R", nullptr, &g_Render->m_OptionSelectedTextColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("Selected Text G", nullptr, &g_Render->m_OptionSelectedTextColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("Selected Text B", nullptr, &g_Render->m_OptionSelectedTextColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("Selected Text A", nullptr, &g_Render->m_OptionSelectedTextColor.a, 0, 255);
				sub->draw_option<number<std::int32_t>>("Unselected Text R", nullptr, &g_Render->m_OptionUnselectedTextColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("Unselected Text G", nullptr, &g_Render->m_OptionUnselectedTextColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("Unselected Text B", nullptr, &g_Render->m_OptionUnselectedTextColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("Unselected Text A", nullptr, &g_Render->m_OptionUnselectedTextColor.a, 0, 255);
			});

		g_Render->draw_submenu<sub>("Footer", SubmenuSettingsFooter, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("Enabled", nullptr, &g_Render->footer_enabled, BoolDisplay::OnOff);
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
				sub->draw_option<number<float>>("Sprite Size", nullptr, &g_Render->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);
				sub->draw_option<toggle<bool>>("Dynamic", nullptr, &g_Render->m_dynamic_footer, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>("Freeze Icon", nullptr, &g_Render->freeze_icon, BoolDisplay::OnOff);
			});

		g_Render->draw_submenu<sub>("Header", SubmenuSettingsHeader, [](sub* sub)
			{
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, -1, []
					{
						g_Render->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
					});

				switch (g_Render->m_HeaderType)
				{
				case HeaderType::Static:
					sub->draw_option<submenu>("Background", nullptr, SubmenuSettingsHeaderStaticBackground);
					break;
				case HeaderType::YTD:
					sub->draw_option<submenu>("Gradient", nullptr, SubmenuSettingsHeaderGradientBackground);
					break;
				}

				sub->draw_option<submenu>("Text", nullptr, SubmenuSettingsHeaderText);
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
				sub->draw_option<KeyboardOption>(("Name"), nullptr, g_Render->header_name, []
					{
						showKeyboard("Enter Something", "", 25, &g_Render->header_name, [] {});



					});
			});

		g_Render->draw_submenu<sub>("Header Background", SubmenuSettingsHeaderStaticBackground, [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_HeaderBackgroundColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_HeaderBackgroundColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_HeaderBackgroundColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_HeaderBackgroundColor.a, 0, 255);
			});

		g_Render->draw_submenu<sub>("Header Gradient", SubmenuSettingsHeaderGradientBackground, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("Transparent", nullptr, &g_Render->m_HeaderGradientTransparent, BoolDisplay::YesNo);
				sub->draw_option<toggle<bool>>("Flip", nullptr, &g_Render->m_HeaderGradientFlip, BoolDisplay::YesNo);
				sub->draw_option<UnclickOption>(("Colors"), nullptr, [] {});
				sub->draw_option<number<std::int32_t>>("R1", nullptr, &g_Render->m_HeaderGradientColorLeft.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G1", nullptr, &g_Render->m_HeaderGradientColorLeft.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B1", nullptr, &g_Render->m_HeaderGradientColorLeft.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A1", nullptr, &g_Render->m_HeaderGradientColorLeft.a, 0, 255);
				sub->draw_option<number<std::int32_t>>("R2", nullptr, &g_Render->m_HeaderGradientColorRight.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G2", nullptr, &g_Render->m_HeaderGradientColorRight.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B2", nullptr, &g_Render->m_HeaderGradientColorRight.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A2", nullptr, &g_Render->m_HeaderGradientColorRight.a, 0, 255);
			});

		g_Render->draw_submenu<sub>("Header Text", SubmenuSettingsHeaderText, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("DX Header Text", "Disable native text if going to use dx", &g_Render->m_HeaderText, BoolDisplay::OnOff);
				sub->draw_option<toggle<bool>>("Native Header Text", "Disable dx text if going to use native ", &g_Render->m_HeaderNativeText, BoolDisplay::OnOff);
				if (g_Render->m_HeaderNativeText) {
					sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &g_Render->HeaderFont, &g_Render->HeaderFontIterator, true, -1, []
						{
							if (g_Render->HeaderFontIterator == 0) {
								g_Render->m_HeaderFont = Font::ChaletLondon;
							}
							if (g_Render->HeaderFontIterator == 1) {
								g_Render->m_HeaderFont = Font::HouseScript;
							}
							if (g_Render->HeaderFontIterator == 2) {
								g_Render->m_HeaderFont = Font::Monospace;
							}
							if (g_Render->HeaderFontIterator == 3) {
								g_Render->m_HeaderFont = Font::Wingdings;
							}
							if (g_Render->HeaderFontIterator == 4) {
								g_Render->m_HeaderFont = Font::ChaletComprimeCologne;
							}
							if (g_Render->HeaderFontIterator == 5) {
								g_Render->m_HeaderFont = Font::Pricedown;
							}
						});
				}
				sub->draw_option<number<float>>("Size", nullptr, &g_Render->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
				sub->draw_option<UnclickOption>(("Colors"), nullptr, [] {});
				sub->draw_option<number<std::int32_t>>("R", nullptr, &g_Render->m_HeaderTextColor.r, 0, 255);
				sub->draw_option<number<std::int32_t>>("G", nullptr, &g_Render->m_HeaderTextColor.g, 0, 255);
				sub->draw_option<number<std::int32_t>>("B", nullptr, &g_Render->m_HeaderTextColor.b, 0, 255);
				sub->draw_option<number<std::int32_t>>("A", nullptr, &g_Render->m_HeaderTextColor.a, 0, 255);
			});

		g_Render->draw_submenu<sub>("Description", SubmenuSettingsDescription, [](sub* sub)
			{
				sub->draw_option<number<float>>("Padding", "Padding before the description rect.", &g_Render->m_DescriptionHeightPadding, 0.01f, 1.f, 0.001f,
				3);
		sub->draw_option<number<float>>("Height", "Size of the description rect.", &g_Render->m_DescriptionHeight, 0.01f, 1.f, 0.001f, 3);
		sub->draw_option<number<float>>("Text Size", "Size of the description text.", &g_Render->m_DescriptionTextSize, 0.1f, 2.f, 0.01f, 2);
			});

		g_Render->draw_submenu<sub>("Input", SubmenuSettingsInput, [](sub* sub)
			{
				sub->draw_option<number<std::int32_t>>("Open Delay", nullptr, &g_Render->m_OpenDelay, 10, 1000, 10, 0);
				sub->draw_option<number<std::int32_t>>("Back Delay", nullptr, &g_Render->m_BackDelay, 10, 1000, 10, 0);
				sub->draw_option<number<std::int32_t>>("Enter Delay", nullptr, &g_Render->m_EnterDelay, 10, 1000, 10, 0);
				sub->draw_option<number<std::int32_t>>("Vertical Delay", nullptr, &g_Render->m_VerticalDelay, 10, 1000, 10, 0);
				sub->draw_option<number<std::int32_t>>("Horizontal Delay", nullptr, &g_Render->m_HorizontalDelay, 10, 1000, 10, 0);
			});
	}

	void MainScript::Destroy()
	{
		g_Render.reset();
	}

	void MainScript::Tick()
	{
		g_Discord->Tick();
		Initialize();
		while (true) {
			g_Render->OnTick();
			FeatureInitalize();
			hotkey_tick();
			fbr::cur()->wait();
		}
	}
}

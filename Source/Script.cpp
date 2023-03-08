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
		SubmenuTest,
		SubmenuToggles,
		SubmenuTogglesColor,
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


		g_Render->draw_submenu<sub>("Saint", SubmenuHome, [](sub* sub)
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
		sub->draw_option<submenu>("Outfit Editor", nullptr, SubmenuOutfitEditor);
		sub->draw_option<submenu>("Animations", nullptr, SubmenuAnimations);
		sub->draw_option<toggle<bool>>(("Godmode"), nullptr, &godmode, BoolDisplay::OnOff, false, [] {
			if (!godmode)
			{
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits = 0;

			}
			});
		sub->draw_option<toggle<bool>>(("Never Wanted"), nullptr, &neverWantedBool, BoolDisplay::OnOff, false, [] {
			if (!neverWantedBool) {
				PLAYER::SET_MAX_WANTED_LEVEL(5);
			}
			});
		sub->draw_option<toggle<bool>>(("Auto Parachute"), "Automaticly pulls you're parachite", &features.auto_parachute, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Seatbelt"), nullptr, &features.seatbelt, BoolDisplay::OnOff, false, [] {
			if (!features.seatbelt) {
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), false);
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, true);
			}
			});
		sub->draw_option<toggle<bool>>(("Explosive Melee"), nullptr, &m_frame_flags.m_explosive_melee, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("No Ragdoll"), nullptr, &features.no_ragdoll, BoolDisplay::OnOff, false, [] {
			if (!features.no_ragdoll)
			{
				PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), true);
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), true);
			}
			});
		sub->draw_option<toggle<bool>>(("Pickup Entities"), nullptr, &features.pickup_mode, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Auto Clean"), nullptr, &features.autoclean, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Swim Anywhere"), nullptr, &features.swim_anywhere, BoolDisplay::OnOff, false, [] {
			if (!features.swim_anywhere)
			{
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 65, false);
			}
			});
		sub->draw_option<toggle<bool>>(("Tiny Ped"), "We can turn into ron height", &features.tiny_ped, BoolDisplay::OnOff, false, [] {
			if (!features.tiny_ped)
			{
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, false);
			}
			});
		sub->draw_option<toggle<bool>>(("Unlimited Special Ability"), nullptr, &features.unlim, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Attack Friendly"), nullptr, &features.attack_friendly, BoolDisplay::OnOff, false, [] {
			if (!features.attack_friendly)
			{
				PED::SET_CAN_ATTACK_FRIENDLY(PLAYER::PLAYER_PED_ID(), false, true);
			}
			});
		sub->draw_option<toggle<bool>>(("Reduced Collision"), nullptr, &features.reduced, BoolDisplay::OnOff, false, [] {
			if (!features.reduced)
			{
				PED::SET_PED_CAPSULE(PLAYER::PLAYER_PED_ID(), false);
			}
			});
		sub->draw_option<toggle<bool>>(("Bound Ankles"), nullptr, &features.bound_ankles, BoolDisplay::OnOff, false, [] {
			if (!features.bound_ankles)
			{
				PED::SET_ENABLE_BOUND_ANKLES(PLAYER::PLAYER_PED_ID(), false);
			}
			});
		sub->draw_option<toggle<bool>>(("Ignored By Peds"), nullptr, &features.ignored, BoolDisplay::OnOff, false, [] {
			if (!features.ignored)
			{
				PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(PLAYER::PLAYER_ID(), true);
				PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(PLAYER::PLAYER_ID(), false);

			}
			});
		sub->draw_option<toggle<bool>>(("Drugs"), nullptr, &features.drugs, BoolDisplay::OnOff, false, [] {
			if (!features.drugs)
			{
				GRAPHICS::ENABLE_ALIEN_BLOOD_VFX(false);
				GRAPHICS::ANIMPOSTFX_STOP("DrugsMichaelAliensFight");


			}
			});

		sub->draw_option<toggle<bool>>(("Blink"), nullptr, &blink.enabled, BoolDisplay::OnOff, false, [] {
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

		sub->draw_option<number<std::int32_t>>("Wanted Level", nullptr, &i_hate_niggers, 0, 5, 1, 3, true, "", "", [] {
			(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_wanted_level = i_hate_niggers;
			});

			});
		g_Render->draw_submenu<sub>(("Outfit Editor"), SubmenuOutfitEditor, [](sub* sub)
			{
				sub->draw_option<submenu>("Load", nullptr, SubmenuOutfitLoader);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend2, &Lists::HeaderTypesPosition2, true, -1, [] {
			g_Render->outfits = Lists::HeaderTypesBackend2[Lists::HeaderTypesPosition2];
			});
		switch (g_Render->outfits) {
		case Outfits::Face:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets face variation.", &testa, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, testa, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets face texture variation.", &facetexture, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0, testa), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, testa, facetexture, 0); }); break;
		case Outfits::Head:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets head variation.", &testb, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, testb, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets head texture variation.", &facetexture1, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1, testb), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, testb, facetexture1, 0); }); break;
		case Outfits::Hair:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets hair variation.", &testc, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, testc, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets hair texture variation.", &facetexture2, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2, testc), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, testc, facetexture2, 0); }); break;
		case Outfits::Torso:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets torso variation.", &testd, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 3), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, testd, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets torso texture variation.", &facetexture3, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 3, testd), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, testd, facetexture3, 0); }); break;
		case Outfits::Torso2:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets torso 2 variation.", &testl, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 11), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, testl, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets torso 2 texture variation.", &facetexture4, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 11, testl), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, testl, facetexture4, 0); }); break;
		case Outfits::Legs:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets leg variation.", &teste, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 4), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, teste, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets leg texture variation.", &facetexture5, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 4, teste), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, teste, facetexture5, 0); }); break;
		case Outfits::Hands:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets hand variation.", &testf, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 5), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, testf, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets hand texture variation.", &facetexture6, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 5, testf), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, testf, facetexture6, 0); }); break;
		case Outfits::Feet:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets feet variation.", &testg, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, testg, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets feet texture variation.", &facetexture7, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6, testg), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, testg, facetexture7, 0); }); break;
		case Outfits::Eyes:
			sub->draw_option<number<std::int32_t>>("Prop", "Sets eye variation.", &testh, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, testh, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets eyes texture variation.", &facetexture8, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7, testh), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, testh, facetexture8, 0); }); break;
		case Outfits::Accessories:

			sub->draw_option<number<std::int32_t>>("Prop", "Sets accessories variation.", &testi, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 8), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, testi, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets accessories texture variation.", &facetexture9, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 8, testi), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, testi, facetexture9, 0); }); break;
		case Outfits::Vests:

			sub->draw_option<number<std::int32_t>>("Prop", "Sets vest variation.", &testj, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 9), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, testj, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets vests texture variation.", &facetexture10, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 9, testj), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, testj, facetexture10, 0); }); break;
		case Outfits::Decals:

			sub->draw_option<number<std::int32_t>>("Prop", "Sets texture variation.", &testk, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 10), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, testk, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets decals texture variation.", &facetexture11, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 10, testk), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, testk, facetexture11, 0); }); break;
		case Outfits::HeadProps:

			sub->draw_option<number<std::int32_t>>("Prop", "Sets head props", &testm, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, testm, 0, 0); });
			sub->draw_option<number<std::int32_t>>("Texture", "Sets head props texture variation.", &facetexture12, 0, PED::GET_PED_PROP_TEXTURE_INDEX(PLAYER::PLAYER_PED_ID(), 1), 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, testm, facetexture12, 0); }); break;
		}
			});
		g_Render->draw_submenu<sub>(("Animations"), SubmenuAnimations, [](sub* sub)
			{
				sub->draw_option<submenu>("Scenarions", "", Submenu::SubmenuScenarios);
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
						showKeyboard("Enter Something", "", 25, &g_Outfits->nameBuffer2, [] {});


					});
		sub->draw_option<RegularOption>(("Save"), nullptr, [=]
			{


				g_Outfits->save(g_Outfits->nameBuffer2);



			});
		sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
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
						OutfitList();
						char nigger[64];
						sprintf(nigger, "%s", path.stem().u8string().c_str());
						sub->draw_option<RegularOption>(nigger, nullptr, [=]
							{
								g_Outfits->load(nigger);
							});

					}

				}
			}
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
				}
					});
		sub->draw_option<toggle<bool>>(("Set Rotation"), nullptr, &no_clip.SetRotation, BoolDisplay::OnOff);
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


			});
		g_Render->draw_submenu<sub>(("Super Jump"), SubmenuSuperjump, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &superjump.enabled, BoolDisplay::OnOff);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &superjump.Jump_Type, &superjump.Jump_Int);
			});
		g_Render->draw_submenu<sub>(("Vehicle"), SubmenuVehicle, [](sub* sub)
			{
				sub->draw_option<submenu>("Handling", "", Submenu::SubmenuVehicleMultipliers);
		sub->draw_option<submenu>("Horn Boost", nullptr, Submenu::SubmenuHornBoost);
		sub->draw_option<submenu>("Acrobatics", nullptr, Submenu::SubmenuAcrobatics);
		sub->draw_option<submenu>("Auto-Pilot", nullptr, Submenu::SubmenuAutoPilot);
		sub->draw_option<submenu>("Speedometer", nullptr, Submenu::SubmenuSpeedo);
		sub->draw_option<submenu>("Engine Sound", nullptr, Submenu::SubmenuEngineSound);
		sub->draw_option<submenu>("Negitive Torque", nullptr, Submenu::SubmenuNegitiveTorque);
		sub->draw_option<submenu>("Particles", nullptr, Submenu::SubmenuVehParticles);
		sub->draw_option<submenu>("Invisible", nullptr, Submenu::SubmenuVehicleInvis);
		sub->draw_option<submenu>("Ramps", nullptr, Submenu::SubmenuVehicleRamps);
		sub->draw_option<submenu>("Spawner", nullptr, Submenu::SubmenuVehicleSpawner);
		sub->draw_option<submenu>("Upgrades", nullptr, Submenu::SubmenuUpgrades);
		sub->draw_option<submenu>("LSC", nullptr, Submenu::SubmenuCustomize);
		sub->draw_option<submenu>("Color", nullptr, Submenu::SubmenuChangeVehicleColor);
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
				}
			}
			});
		sub->draw_option<toggle<bool>>(("Keep Engine On"), "Prevents your vehicle's engine from being turned off when exiting.", &features.keep_engine_on, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("No Plane Turbulence"), "Removes your plane's turbulance. When turning off, it can make turbulance levels a little messed up.", &NoPlaneTurbulance, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Auto-Repair"), nullptr, &features.auto_repair, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Remove Deformation"), nullptr, &features.remove_def, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Stick To Ground"), nullptr, &features.stick_to_ground, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Burned"), nullptr, &features.burned, BoolDisplay::OnOff, false, [] {
			if (!features.burned) {
				ENTITY::SET_ENTITY_RENDER_SCORCHED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
			}
			});
		sub->draw_option<toggle<bool>>(("Infinite Rocket Boost"), "Instantly refills your vehicle's rocket boost.", &features.infiniter, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Bypass Max Speed"), "Allows you to exceed the maximum speed limit your current vehicle.", &m_vehicle.bypass_max_speed.enabled, BoolDisplay::OnOff, false, [] {
			if (!m_vehicle.bypass_max_speed.enabled) {
				m_vehicle.bypass_max_speed.disable(); //trying something new
			}
			});
		sub->draw_option<toggle<bool>>(("Disable Lock-On"), "Allows you to exceed the maximum speed limit your current vehicle.", &features.disable_lock_on, BoolDisplay::OnOff, false, [] {
			if (!features.disable_lock_on) {
				auto g_local_player = (*g_GameFunctions->m_pedFactory)->m_local_ped;
				if (g_local_player && g_local_player->m_vehicle)
					g_local_player->m_vehicle->m_is_targetable = true;
			}
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
		sub->draw_option<toggle<bool>>(("Include Secondary"), nullptr, &changeVehicleColor.rainbow.change_secondary, BoolDisplay::OnOff);
		sub->draw_option<number<std::int32_t>>("Delay", nullptr, &changeVehicleColor.rainbow.delay, 0, 5000, 50);



			});
		g_Render->draw_submenu<sub>(("Spawner"), SubmenuVehicleSpawner, [](sub* sub)
			{
				
				sub->draw_option<submenu>("Settings", nullptr, Submenu::SpawnerSettings);
		sub->draw_option<submenu>("Search", nullptr, Submenu::SubmenuVehicleSearch);
		sub->draw_option<submenu>("Saved", nullptr, Submenu::SubmenuSavedVehicles);
		
		sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
		sub->draw_option<submenu>("All", nullptr, SubmenuVehicleAll);
		for (std::int32_t i = 0; i < 23; i++) {
			sub->draw_option<submenu>(get_vehicle_class_name(i), nullptr, SubmenuGetClass, [=]
				{
					m_selected_vehicle_class = i;
				});

		}


			});
		g_Render->draw_submenu<sub>(("Saved"), SubmenuSavedVehicles, [](sub* sub)
			{
				sub->draw_option<RegularOption>(("Save"), nullptr, [=]
					{
						g_VehicleLoading->save();

					});
		sub->draw_option<UnclickOption>(("Saved"), nullptr, [] {});
		sub->draw_option<RegularOption>(("Load"), nullptr, [=]
			{
				g_VehicleLoading->load();

			});
		namespace fs = std::filesystem;
		fs::directory_iterator dirIt{ g_TranslationManager->GetTranslationDirectory() };
		for (auto&& dirEntry : dirIt)
		{
			if (dirEntry.is_regular_file())
			{
				auto path = dirEntry.path();
				if (path.has_filename())
				{
					const char* lmao = "hey";
					sub->draw_option<RegularOption>(lmao, nullptr, [=]
						{
							//g_TranslationManager->LoadTranslations(path.stem().u8string().c_str());
						});
				}
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
										veh_spawner.spawn(*(std::uint32_t*)(info + 0x18));

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
											veh_spawner.spawn(*(std::uint32_t*)(info + 0x18));

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
		g_Render->draw_submenu<sub>(("Upgrades"), SubmenuUpgrades, [](sub* sub)
			{
				sub->draw_option<submenu>("Max (Loop)", nullptr, Submenu::SubmenuUpgradeLoop);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Max (Once)", nullptr, &m_upgrades.types, &m_upgrades.data, false, SubmenuMaxThatFucker, [] {

			m_upgrades.apply(m_upgrades.data);
			});

			});
		g_Render->draw_submenu<sub>(("Max (Loop)"), SubmenuUpgradeLoop, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &max_loop.enabled, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Randomize Primary"), nullptr, &max_loop.randomizeprimary, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Randomize Secondary"), nullptr, &max_loop.randomizesecondary, BoolDisplay::OnOff);
		sub->draw_option<number<std::int32_t>>("Delay", nullptr, &max_loop.delay, 0, 5000, 50);
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

				sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Enabled", nullptr, &speedo.enabled, &speedo.type, &speedo.type_i);
		sub->draw_option<number<float>>("X Offset", nullptr, &speedo.x_offset, -100.f, 100.f, 0.01f, 2);
		sub->draw_option<number<float>>("Y Offset", nullptr, &speedo.y_offset, -100.f, 100.f, 0.01f, 2);
		sub->draw_option<number<float>>("Scale", nullptr, &speedo.scale, 0.f, 100.f, 0.01f, 2);



			});
		g_Render->draw_submenu<sub>(("LSC"), SubmenuCustomize, [](sub* sub)
			{


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
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_XENONLIGHTS) > 0)
					{
						sub->draw_option<submenu>("Lights", "", LosSantosLights);
					}
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


				}
				else
				{
					sub->draw_option<RegularOption>("Vehicle Not Found", "");
				}


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
			sub->draw_option<number<float>>("Mass", nullptr, &handling->m_mass, 0.f, 10000.f, 50.0f, 1);
			sub->draw_option<number<float>>("Initial Drag Coeff", nullptr, &handling->m_initial_drag_coeff, 0.f, 10000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Downforce Multiplier", nullptr, &handling->m_downforce_multiplier, 0.f, 10000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Popup Light Rotation", nullptr, &handling->m_popup_light_rotation, 0.f, 10000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Centre Of Mass X", nullptr, &handling->m_centre_of_mass.x, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Centre Of Mass Y", nullptr, &handling->m_centre_of_mass.y, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Centre Of Mass Z", nullptr, &handling->m_centre_of_mass.z, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Inertia Multiplier X", nullptr, &handling->m_inertia_mult.x, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Inertia Multiplier Y", nullptr, &handling->m_inertia_mult.y, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Inertia Multiplier Z", nullptr, &handling->m_inertia_mult.z, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Buoyancy", nullptr, &handling->m_buoyancy, 0.0f, 1000.f, 1.0f, 1);
			sub->draw_option<number<float>>("Drive Bias Rear", nullptr, &handling->m_drive_bias_rear, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Drive Bias Front", nullptr, &handling->m_drive_bias_front, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Acceleration", nullptr, &handling->m_acceleration, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Upshift", nullptr, &handling->m_upshift, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Downshift", nullptr, &handling->m_downshift, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Initial Drive Force", nullptr, &handling->m_initial_drive_force, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Drive Maxx Flat Velocity", nullptr, &handling->m_drive_max_flat_velocity, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Initial Drive Max Flat Velocity", nullptr, &handling->m_initial_drive_max_flat_vel, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Brake Force", nullptr, &handling->m_brake_force, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Brake Bias Front", nullptr, &handling->m_brake_bias_front, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Brake Bias Rear", nullptr, &handling->m_brake_bias_rear, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Handbrake Force", nullptr, &handling->m_handbrake_force, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Steering Lock", nullptr, &handling->m_steering_lock, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Steering Lock Ratio", nullptr, &handling->m_steering_lock_ratio, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Curve Max", nullptr, &handling->m_traction_curve_max, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Curve Min", nullptr, &handling->m_traction_curve_min, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Curve Lateral", nullptr, &handling->m_traction_curve_lateral, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Curve Ratio", nullptr, &handling->m_traction_curve_ratio, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Curve Lateral", nullptr, &handling->m_curve_lateral, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Curve Lateral Ratio", nullptr, &handling->m_curve_lateral_ratio, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Spring Delta Max", nullptr, &handling->m_traction_spring_delta_max, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Spring Delta Max Ratio", nullptr, &handling->m_traction_spring_delta_max_ratio, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Low Speed Traction Loss Multiplier", nullptr, &handling->m_low_speed_traction_loss_mult, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Camber Stiffness", nullptr, &handling->m_camber_stiffness, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Bias Front", nullptr, &handling->m_traction_bias_front, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Bias Rear", nullptr, &handling->m_traction_bias_rear, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Traction Loss Multiplier", nullptr, &handling->m_traction_loss_mult, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Suspension Force", nullptr, &handling->m_suspension_force, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Suspension Comp Damp", nullptr, &handling->m_suspension_comp_damp, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Suspension Rebound Damp", nullptr, &handling->m_suspension_rebound_damp, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Suspsension Upper Limit", nullptr, &handling->m_suspension_upper_limit, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Suspension Lower Limit", nullptr, &handling->m_suspension_lower_limit, 0.0f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Suspension Raise", nullptr, &handling->m_suspension_raise, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Suspension Bias Front", nullptr, &handling->m_suspension_bias_front, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Suspension Bias Rear", nullptr, &handling->m_suspension_bias_rear, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Anti Rollbar Force", nullptr, &handling->m_anti_rollbar_force, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Anti Rollbar Bias Front", nullptr, &handling->m_anti_rollbar_bias_front, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Anti Rollbar Bias Rear", nullptr, &handling->m_anti_rollbar_bias_rear, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Roll Centre Height Front", nullptr, &handling->m_roll_centre_height_front, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Roll Centre Height Rear", nullptr, &handling->m_roll_centre_height_rear, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Collision Damage Multiplier", nullptr, &handling->m_collision_damage_mult, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Weapon Damage Multiplier", nullptr, &handling->m_weapon_damamge_mult, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Deformation Multiplier", nullptr, &handling->m_deformation_mult, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Engine Damage Multiplier", nullptr, &handling->m_engine_damage_mult, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Petrol Tank Volume", nullptr, &handling->m_petrol_tank_volume, -1000.f, 1000.f, 0.1f, 1);
			sub->draw_option<number<float>>("Oil Volume", nullptr, &handling->m_oil_volume, 1000.f, 1000.f, 0.1f, 1);
		}


			});
		g_Render->draw_submenu<sub>(("Presets"), SubmenuPresets, [](sub* sub)
			{

				sub->draw_option<RegularOption>(("Save"), nullptr, []
					{

						showKeyboard("Enter Something", "", 25, &handlingBuffer, [] {

							});
					});
		sub->draw_option<UnclickOption>(("Lists"), nullptr, [] {});
		if (handlingBuffer.c_str() != "") {
			sub->draw_option<RegularOption>(handlingBuffer.c_str(), "");
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
		sub->draw_option<toggle<bool>>(("Infinite Ammo"), nullptr, &features.infinite_ammo, BoolDisplay::OnOff, false, [] {
			if (!features.infinite_ammo) {
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), false);
			}
			});
		sub->draw_option<BoolChoose<const char*, std::size_t, bool>>("Teleport", nullptr, &features.teleport_gun, &features.teleport_gun_type, &features.teleport_gun_int);
		sub->draw_option<toggle<bool>>(("Delete"), nullptr, &features.delete_gun, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Bypass C4 Limit"), nullptr, &features.bypass_c4_limit, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Magnet"), nullptr, &gravity.enabled, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Incendiary"), nullptr, &m_frame_flags.m_fire, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Aim Tracer"), nullptr, &features.aim_tracer, BoolDisplay::OnOff);

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
				sub->draw_option<submenu>("Excludes", nullptr, SubmenuAimbotExcludes);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Bone", nullptr, &aimbot.bone, &aimbot.data);
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
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Bone", nullptr, &triggerbot.shoot_coords, &triggerbot.scoords_i);
		sub->draw_option<number<std::int32_t>>("Delay", nullptr, &triggerbot.delay, 0, 5000);


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
		sub->draw_option<number<float>>("Accurate Mode Acuracy Modifier", nullptr, &weapon->m_accurate_mode_accuracy_modifier, -1000.f, 1000.f, 0.1f, 1);
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
		sub->draw_option<number<float>>("Vehilce Damage Modifier", nullptr, &weapon->m_vehicle_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
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
			WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), give_weapon.data[give_weapon.type_int], &Maxammo);
		}
		if (give_weapon.type_int == 0) {
			Maxammo = 9999;
		}
		
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &give_weapon.type, &give_weapon.type_int);
		sub->draw_option<number<std::int32_t>>("Ammo", nullptr, &give_weapon.amount, 1, Maxammo);
		sub->draw_option<RegularOption>(("Apply"), nullptr, []
			{
				if (give_weapon.type_int != 0) {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), give_weapon.data[give_weapon.type_int], 9999, false);
				}
		if (give_weapon.type_int == 0) {
			std::uint32_t wephashes[89]
			{ 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
			0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
			0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
			0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
			0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A };
			for (int x = 0; x < 89; x++) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), wephashes[x], give_weapon.amount, false);
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
		sub->draw_option<submenu>("Recovery", nullptr, SubmenuRecovery);
		sub->draw_option<submenu>("Requests", nullptr, SubmenuRequests);
		sub->draw_option<submenu>("Session Starter", nullptr, SubmenuSesStart);
		sub->draw_option<submenu>("RID Joiner", nullptr, SubmenuRIDJoiner);
		sub->draw_option<submenu>("Notifications", nullptr, SubmenuNotifcations);
		sub->draw_option<submenu>("Chat", nullptr, SubmenuChat);
		sub->draw_option<submenu>("Team", nullptr, SubmenuTeam);
		sub->draw_option<submenu>("Off The Radar", nullptr, SubmenuOffRadar);
		sub->draw_option<submenu>("Heist Control", nullptr, HeistControl);
			});
		g_Render->draw_submenu<sub>("Heist Control", HeistControl, [](sub* sub)
			{
				sub->draw_option<submenu>("Diamond Casino", nullptr, DiamondCasino);


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
				sub->draw_option<submenu>("Level", nullptr, SubmenuRP);


			});
		g_Render->draw_submenu<sub>("Level", SubmenuRP, [](sub* sub)
			{
				if (m_recovery.m_level.m_level > 8000) {
					m_recovery.m_level.m_level = 8000;
				}
		if (m_recovery.m_level.m_level < 1) {
			m_recovery.m_level.m_level = 1;
		}
		sub->draw_option<KeyboardOption>(("Level"), nullptr, std::to_string(m_recovery.m_level.m_level), []
			{
				showKeyboard("Enter Something", "", 4, &m_recovery.m_level.m_level_buffer, [] {


				m_recovery.m_level.m_level = atoi(m_recovery.m_level.m_level_buffer.c_str());

					});


			});
		sub->draw_option<RegularOption>("Apply", nullptr, []
			{
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_SET_RP_GIFT_ADMIN"), m_recovery.m_level.Levels[m_recovery.m_level.m_level], true);
		Noti::InsertNotification({ ImGuiToastType_None, 2000, "Change session for the level to apply." });
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
				sub->draw_option<submenu>("Information", nullptr, SubmenuInformation);
		sub->draw_option<submenu>("Game", nullptr, SubmenuGame);
		sub->draw_option<submenu>("Crew", nullptr, SubmenuCrew);
		sub->draw_option<toggle<bool>>(("QA Tester"), nullptr, &spoofing.qa_tester, BoolDisplay::OnOff);
			});
		g_Render->draw_submenu<sub>(("Information"), SubmenuInformation, [](sub* sub)
			{
				sub->draw_option<submenu>("IP", nullptr, SubmenuIP);

			});
		g_Render->draw_submenu<sub>(("IP"), SubmenuIP, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Enabled"), nullptr, &spoofing.ip.enabled, BoolDisplay::OnOff);
		sub->draw_option<KeyboardOption>(("Field 1"), nullptr, spoofing.ip.f1, []
			{
				


			});
		sub->draw_option<KeyboardOption>(("Field 2"), nullptr, spoofing.ip.f2.c_str(), []
			{
				showKeyboard("Enter Something", "", 3, &spoofing.ip.f2, [] {
				spoofing.ip.field2 = atoi(spoofing.ip.f2.c_str());
					});


			});
		sub->draw_option<KeyboardOption>(("Field 3"), nullptr, spoofing.ip.f3.c_str(), []
			{
				showKeyboard("Enter Something", "", 3, &spoofing.ip.f3, [] {
				spoofing.ip.field3 = atoi(spoofing.ip.f3.c_str());
					});


			});
		sub->draw_option<KeyboardOption>(("Field 4"), nullptr, spoofing.ip.f4.c_str(), []
			{
				showKeyboard("Enter Something", "", 3, &spoofing.ip.f4, [] {
				spoofing.ip.field4 = atoi(spoofing.ip.f4.c_str());
					});


			});


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
						std::uint32_t g_RIDHash{ 0xDA4858C1 };
		m_EnableSCIDJoiner = true;
		HUD::ACTIVATE_FRONTEND_MENU(0XD528C7E2, 0, 2);
		fbr::cur()->wait(250ms);
		if (m_PlayerListPointer)
		{
			g_GameFunctions->m_PlayerGUIOptions(m_PlayerListPointer, &g_RIDHash);
			m_PlayerListPointer = 0;
			fbr::cur()->wait(300ms);
		}
		m_EnableSCIDJoiner = false;

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
					*script_global(2672505).at(3689).as<int*>() = 1;
					break;
				case 6:
					requests.add(896);
					break;
				}
			});

			});
		g_Render->draw_submenu<sub>(("Session Starter"), SubmenuSesStart, [](sub* sub)
			{
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
		g_Render->draw_submenu<sub>("Player List", SubmenuPlayerList, [](sub* sub)
			{
				sub->draw_option<submenu>("All", nullptr, SubmenuAllPlayers);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Filter", nullptr, &p_filter.data, &p_filter.data_i);
		
		
		sub->draw_option<UnclickOption>(("List"), nullptr, [] {});

		for (std::uint32_t i = 0; i < 32; ++i)
		{
			if (sub->GetSelectedOption() == sub->GetNumOptions()) {
				g_players.draw_info(i);
			}

			if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
			{

				std::string name = PLAYER::GET_PLAYER_NAME(i);
				if (i == PLAYER::PLAYER_ID())
					name.append(" ~p~[Self]");
				if (PED::GET_PED_CONFIG_FLAG(ped, 109, true)) {
					name.append(" ~b~[Saint]");
				}
				if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
					if (antiCheat.cheater[g_GameVariables->m_net_game_player(i)->m_player_id] == true) {
						name.append(" ~r~[Modder]");
					}
				}




				if (p_filter.data_i == 0) {
					sub->draw_option<submenu>(name.c_str(), nullptr, SubmenuSelectedPlayer, [=]
						{
							g_SelectedPlayer = i;
						});

				}
				if (p_filter.data_i == 1) {
					if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
						sub->draw_option<submenu>(name.c_str(), nullptr, SubmenuSelectedPlayer, [=]
							{
								g_SelectedPlayer = i;
							});
					}
				}
				if (p_filter.data_i == 2) {
					if (INTERIOR::GET_INTERIOR_FROM_ENTITY(ped) != 0) {
						sub->draw_option<submenu>(name.c_str(), nullptr, SubmenuSelectedPlayer, [=]
							{
								g_SelectedPlayer = i;
							});
					}
				}
				if (p_filter.data_i == 3) {
					if (!PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
						sub->draw_option<submenu>(name.c_str(), nullptr, SubmenuSelectedPlayer, [=]
							{
								g_SelectedPlayer = i;
							});
					}
				}

			}
		}
			});

		g_Render->draw_submenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
			{
				sub->draw_option<submenu>("Trolling", nullptr, SubmenuTrolling);
		sub->draw_option<submenu>("Bodygaurds", nullptr, SubmenuBodyguards);
		sub->draw_option<submenu>("Increment", nullptr, SubmenuIncrement);
		sub->draw_option<submenu>("Friendly", nullptr, SubmenuFriendly);
		sub->draw_option<submenu>("Vehicle", nullptr, SubmenuSelectedVehicle);
		sub->draw_option<submenu>("Weapon", nullptr, SubmenuSelectedWeapon);
		sub->draw_option<submenu>("Teleport", nullptr, SubmenuPlayerTeleport);
		sub->draw_option<submenu>("Spawner", nullptr, SubmenuSelectedSpawner);
		sub->draw_option<submenu>("Removals", nullptr, SubmenuRemoval);
		if (g_SelectedPlayer != PLAYER::PLAYER_ID()) {
			sub->draw_option<toggle<bool>>(("Spectate"), nullptr, &features.spectate, BoolDisplay::OnOff, false, [] {
				if (!features.spectate) {



					NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
					HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
					STREAMING::SET_FOCUS_ENTITY(PLAYER::PLAYER_PED_ID());
					ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);

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
						g_Notifcations->add("Please start a session.");

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
						g_Notifcations->add("Please start a session.");
					}
					break;
				}
			});


			});
		g_Render->draw_submenu<sub>("Vehicle", SubmenuSelectedVehicle, [](sub* sub)
			{
				static int boost_power = 150;
				sub->draw_option<number<std::int32_t>>("Boost", nullptr, &boost_power, 0, 300, 10, 3, false, "", "", [] {
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
			WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), give_weapon.data[give_weapon.type_int], &Maxammo);
		}
		if (give_weapon.type_int == 0) {
			Maxammo = 9999;
		}
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Type", nullptr, &give_weapon.type, &give_weapon.type_int);
		sub->draw_option<number<std::int32_t>>("Ammo", nullptr, &give_weapon.amount, 1, Maxammo);
		sub->draw_option<RegularOption>(("Apply"), nullptr, []
			{
				if (give_weapon.type_int != 0) {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), give_weapon.data[give_weapon.type_int], 9999, false);
				}
		if (give_weapon.type_int == 0) {
			std::uint32_t wephashes[89]
			{ 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
			0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
			0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
			0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
			0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A };
			for (int x = 0; x < 89; x++) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), wephashes[x], give_weapon.amount, false);
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
				sub->draw_option<ChooseOption<const char*, std::size_t>>("Menu", nullptr, &g_players.get_selected.events.CrashMenu, &g_players.get_selected.events.Menu_DataCrash);
		sub->draw_option<RegularOption>(("Start"), nullptr, []
			{

				g_players.get_selected.events.crash();
			});

			});
		g_Render->draw_submenu<sub>("All", SubmenuAllPlayers, [](sub* sub)
			{
				sub->draw_option<submenu>("Settings", nullptr, SubmenuAllSettings);
		sub->draw_option<UnclickOption>(("List"), nullptr, [] {});
		sub->draw_option<submenu>("Jets", nullptr, SubmenuAllJets);
		sub->draw_option<submenu>("Explode", nullptr, SubmenuAllExplode);
		sub->draw_option<toggle<bool>>(("Off The Radar"), "Can cause crashes.", &all_players.off_the_radar, BoolDisplay::OnOff);
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
		sub->draw_option<toggle<bool>>(("Always Wanted"), nullptr, &wanted_lev.always, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("Freeze"), nullptr, &g_players.get_selected.freeze, BoolDisplay::OnOff);
		static int boost_power = 10000;
		sub->draw_option<number<std::int32_t>>("Bounty", nullptr, &boost_power, 0, 10000, 1, 3, false, "", "", [] {
			g_players.get_selected.bounty(boost_power);
		});
		//sub->draw_option<toggle<bool>>(("Freeze"), nullptr, &g_players.get_selected.freeze, BoolDisplay::OnOff);
		sub->draw_option<RegularOption>(("Taze"), nullptr, [=]
			{
				g_players.get_selected.taze();


			});
		sub->draw_option<RegularOption>(("Kick From Vehicle"), nullptr, [=]
			{

				g_players.get_selected.kick_from_vehicle();



			});

		sub->draw_option<number<std::int32_t>>("Wanted Level", nullptr, &g_players.get_selected.wanted_level, 0, 5, 1, 3, true, "", "", [] {
			g_players.get_selected.set_wanted_level(g_players.get_selected.wanted_level);
			});
		//sub->draw_option<number<std::int32_t>>("Delay", nullptr, &Fake_drops.delay, 0, 5000, 50);


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
		sub->draw_option<RegularOption>(("Their Vehicle To You"), nullptr, [=]
			{
				if (g_players.get_selected.request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false))) {
					Entity ent = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
					NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
					ENTITY::SET_ENTITY_COORDS(ent, coords.x, coords.y, coords.z, 0, 0, 0, 0);
				}



			});

			});
		g_Render->draw_submenu<sub>(("Bodygaurds"), SubmenuBodyguards, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Godmode"), nullptr, &bodygaurd.godmode, BoolDisplay::OnOff);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Weapon", nullptr, &bodygaurd.Weapon, &bodygaurd.WeaponInt);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Model", nullptr, &bodygaurd.Models, &bodygaurd.ModelInt);
		sub->draw_option<toggle<bool>>(("Custom Firing Pattern"), nullptr, &bodygaurd.FiringPatternEnabled, BoolDisplay::OnOff);
		if (bodygaurd.FiringPatternEnabled) {
			sub->draw_option<ChooseOption<const char*, std::size_t>>("Firing Pattern", nullptr, &bodygaurd.FiringPattern, &bodygaurd.FiringPatternInt);
		}
		sub->draw_option<number<std::int32_t>>("Accuary", nullptr, &bodygaurd.accuary, 0, 100);
		sub->draw_option<number<float>>("Damage Multiplier", nullptr, &bodygaurd.damagemultiplier, 0.0f, 150.f, 0.10f, 2);
		sub->draw_option<RegularOption>(("Spawn"), nullptr, []
			{
				g_CallbackScript->AddCallback<ModelCallback>(MISC::GET_HASH_KEY(bodygaurd.ModelHashes[bodygaurd.ModelInt]), [=] {
				Ped ped;
		NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
		ped = PED::CREATE_PED(26, MISC::GET_HASH_KEY(bodygaurd.ModelHashes[bodygaurd.ModelInt]), c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(g_SelectedPlayer), true, true);
		NETWORK::NETWORK_FADE_IN_ENTITY(ped, true, false);
		PED::SET_PED_AS_GROUP_LEADER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), PLAYER::GET_PLAYER_GROUP(g_SelectedPlayer));
		PED::SET_PED_AS_GROUP_MEMBER(ped, PLAYER::GET_PLAYER_GROUP(g_SelectedPlayer));
		PED::SET_PED_NEVER_LEAVES_GROUP(ped, PLAYER::GET_PLAYER_GROUP(g_SelectedPlayer));
		PED::SET_PED_COMBAT_ABILITY(ped, 100);
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, bodygaurd.WeaponHashes[bodygaurd.WeaponInt], 9998, true);
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
					});
			});
			});
		g_Render->draw_submenu<sub>(("Drops"), SubmenuDrops, [](sub* sub) {
			sub->draw_option<toggle<bool>>(("Money"), nullptr, &drops.money, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>(("RP"), nullptr, &drops.rp, BoolDisplay::OnOff);
		sub->draw_option<UnclickOption>(("Settings"), nullptr, [] {});
		sub->draw_option<toggle_number_option<std::int32_t, bool>>("Randomize RP Model", nullptr, &drops.random_rp_model, &drops.model_delay, 0, 5000, 50);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Location", nullptr, &drops.location, &drops.data);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("RP Model", nullptr, &drops.rp_model, &drops.rp_model_data);
		sub->draw_option<ChooseOption<const char*, std::size_t>>("Model Model", nullptr, &drops.money_model, &drops.money_model_data);
		sub->draw_option<number<std::int32_t>>("Height", nullptr, &drops.height, 0, 100);
		sub->draw_option<number<std::int32_t>>("Delay", nullptr, &drops.delay, 0, 5000, 50);
			});
		g_Render->draw_submenu<sub>(("Protection"), SubmenuProtections, [](sub* sub)
			{
				sub->draw_option<submenu>("Script Events", nullptr, SubmenuScriptEvents);
		sub->draw_option<submenu>("Crash", nullptr, SubmenuProtCrash);
		sub->draw_option<toggle<bool>>(("Reports"), nullptr, &protections.block_reports, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Crash"), SubmenuProtCrash, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Vehicle"), nullptr, &protections.crash.vehicle, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Script Events"), SubmenuScriptEvents, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Send To Location"), nullptr, &protections.send_to_location, BoolDisplay::OnOff);

			});
		g_Render->draw_submenu<sub>(("Teleport"), SubmenuTeleport, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Automatic"), nullptr, &m_teleport.automatic, BoolDisplay::OnOff);
				sub->draw_option<RegularOption>(("Waypoint"), nullptr, []
					{



						m_teleport.waypoint();

					});
				
			});

		g_Render->draw_submenu<sub>(("World"), SubmenuWorld, [](sub* sub)
			{
				//sub->draw_option<submenu>("Peds", nullptr, SubmenuPeds);
				sub->draw_option<submenu>("Weather", nullptr, SubmeuWeather);
				sub->draw_option<submenu>("Neraby Manager", nullptr, NearbyManager);
		

			});
		g_Render->draw_submenu<sub>(("Neraby Manager"), NearbyManager, [](sub* sub)
			{
				sub->draw_option<submenu>("Traffic", nullptr, NearbyVehicles);
				sub->draw_option<submenu>("Pedestrians", nullptr, NearbyPeds);

			});
		g_Render->draw_submenu<sub>(("Traffic"), NearbyVehicles, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>(("Horn"), nullptr, &m_nearby.m_traffic.horn, BoolDisplay::OnOff);
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

			});
		g_Render->draw_submenu<sub>(("Weather"), SubmeuWeather, [](sub* sub)
			{
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

		g_Render->draw_submenu<sub>("Settings", SubmenuSettings, [](sub* sub)
			{
				sub->draw_option<submenu>("Header", nullptr, SubmenuSettingsHeader);
		sub->draw_option<submenu>("Footer Text", nullptr, SubmenuSettingsSubmenuBar);
		sub->draw_option<submenu>("Options", nullptr, SubmenuSettingsOption);
		sub->draw_option<submenu>("Footer", nullptr, SubmenuSettingsFooter);
		sub->draw_option<submenu>("Toggles", nullptr, SubmenuToggles);
		sub->draw_option<submenu>("Description", nullptr, SubmenuSettingsDescription);
		sub->draw_option<submenu>("Input", nullptr, SubmenuSettingsInput);
		sub->draw_option<submenu>("Themes", nullptr, SubmenuThemes);
		//sub->draw_option<submenu>("Scripts", nullptr, SubmenuScripts);
		//sub->draw_option<submenu>("Demo", nullptr, SubmenuTest);
		
		sub->draw_option<number<float>>("X Position", nullptr, &g_Render->m_PosX, 0.f, 1.f, 0.01f, 2);
		sub->draw_option<number<float>>("Y Position", nullptr, &g_Render->m_PosY, 0.f, 1.f, 0.01f, 2);
		sub->draw_option<number<float>>("Width", nullptr, &g_Render->m_Width, 0.01f, 1.f, 0.01f, 2);
		sub->draw_option<toggle<bool>>("Sounds", nullptr, &g_Render->m_Sounds, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>("Submenu Bar", nullptr, &g_Render->submenu_enabled, BoolDisplay::OnOff);
		sub->draw_option<ChooseOption<const char*, std::size_t>>(("Submenu Indicators"), nullptr, &g_Render->IndicatorList, &g_Render->IndicatorIterator);
		sub->draw_option<toggle<bool>>("Glare", nullptr, &g_Render->m_render_glare, BoolDisplay::OnOff);
		sub->draw_option<toggle<bool>>("Log Script Events", nullptr, &g_LogScriptEvents, BoolDisplay::OnOff);
		sub->draw_option<RegularOption>("Save Theme", "", []
			{
				g_ThemeLoading->save();
			});
		sub->draw_option<RegularOption>("Load Theme", "", []
			{
				g_ThemeLoading->load();
			});

		sub->draw_option<RegularOption>("Unload", nullptr, []
			{
				g_Running = false;
			});
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

		sub->draw_option<number<std::uint8_t>>("Toggled (R)", nullptr, &g_Render->m_ToggleOnColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Toggled (G)", nullptr, &g_Render->m_ToggleOnColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Toggled (B)", nullptr, &g_Render->m_ToggleOnColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Toggled (A)", nullptr, &g_Render->m_ToggleOnColor.a, '\0', static_cast<std::uint8_t>(255));
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
		sub->draw_option<number<std::uint8_t>>("Text R", nullptr, &g_Render->m_FooterTextColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Text G", nullptr, &g_Render->m_FooterTextColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Text B", nullptr, &g_Render->m_FooterTextColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Text A", nullptr, &g_Render->m_FooterTextColor.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_Render->draw_submenu<sub>("Options", SubmenuSettingsOption, [](sub* sub)
			{
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
		sub->draw_option<number<float>>("Text Size", nullptr, &g_Render->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);
		sub->draw_option<UnclickOption>(("Colors"), nullptr, [] {});
		sub->draw_option<number<std::uint8_t>>("Selected Background R", nullptr, &g_Render->m_OptionSelectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Selected Background G", nullptr, &g_Render->m_OptionSelectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Selected Background B", nullptr, &g_Render->m_OptionSelectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Selected Background A", nullptr, &g_Render->m_OptionSelectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Unselected Background R", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Unselected Background G", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Unselected Background B", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Unselected Background A", nullptr, &g_Render->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));

		sub->draw_option<number<std::uint8_t>>("Selected Text R", nullptr, &g_Render->m_OptionSelectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Selected Text G", nullptr, &g_Render->m_OptionSelectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Selected Text B", nullptr, &g_Render->m_OptionSelectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Selected Text A", nullptr, &g_Render->m_OptionSelectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Unselected Text R", nullptr, &g_Render->m_OptionUnselectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Unselected Text G", nullptr, &g_Render->m_OptionUnselectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Unselected Text B", nullptr, &g_Render->m_OptionUnselectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Unselected Text A", nullptr, &g_Render->m_OptionUnselectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_Render->draw_submenu<sub>("Footer", SubmenuSettingsFooter, [](sub* sub)
			{
				sub->draw_option<number<float>>("Height", nullptr, &g_Render->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
		sub->draw_option<number<float>>("Sprite Size", nullptr, &g_Render->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);
		sub->draw_option<toggle<bool>>("Dynamic Footer", nullptr, &g_Render->m_dynamic_footer, BoolDisplay::OnOff);
		sub->draw_option<UnclickOption>(("Colors"), nullptr, [] {});
		sub->draw_option<number<std::uint8_t>>("Background R", nullptr, &g_Render->m_FooterBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Background G", nullptr, &g_Render->m_FooterBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Background B", nullptr, &g_Render->m_FooterBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Background A", nullptr, &g_Render->m_FooterBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Sprite R", nullptr, &g_Render->m_FooterSpriteColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Sprite G", nullptr, &g_Render->m_FooterSpriteColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Sprite B", nullptr, &g_Render->m_FooterSpriteColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("Sprite A", nullptr, &g_Render->m_FooterSpriteColor.a, '\0', static_cast<std::uint8_t>(255));
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
				sub->draw_option<number<std::uint8_t>>("R", nullptr, &g_Render->m_HeaderBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("G", nullptr, &g_Render->m_HeaderBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("B", nullptr, &g_Render->m_HeaderBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("A", nullptr, &g_Render->m_HeaderBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_Render->draw_submenu<sub>("Header Gradient", SubmenuSettingsHeaderGradientBackground, [](sub* sub)
			{
				sub->draw_option<toggle<bool>>("Transparent", nullptr, &g_Render->m_HeaderGradientTransparent, BoolDisplay::YesNo);
		sub->draw_option<toggle<bool>>("Flip", nullptr, &g_Render->m_HeaderGradientFlip, BoolDisplay::YesNo);
		sub->draw_option<UnclickOption>(("Colors"), nullptr, [] {});
		sub->draw_option<number<std::uint8_t>>("R1", nullptr, &g_Render->m_HeaderGradientColorLeft.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("G1", nullptr, &g_Render->m_HeaderGradientColorLeft.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("B1", nullptr, &g_Render->m_HeaderGradientColorLeft.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("A1", nullptr, &g_Render->m_HeaderGradientColorLeft.a, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("R2", nullptr, &g_Render->m_HeaderGradientColorRight.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("G2", nullptr, &g_Render->m_HeaderGradientColorRight.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("B2", nullptr, &g_Render->m_HeaderGradientColorRight.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("A2", nullptr, &g_Render->m_HeaderGradientColorRight.a, '\0', static_cast<std::uint8_t>(255));
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
		sub->draw_option<number<std::uint8_t>>("R", nullptr, &g_Render->m_HeaderTextColor.r, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("G", nullptr, &g_Render->m_HeaderTextColor.g, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("B", nullptr, &g_Render->m_HeaderTextColor.b, '\0', static_cast<std::uint8_t>(255));
		sub->draw_option<number<std::uint8_t>>("A", nullptr, &g_Render->m_HeaderTextColor.a, '\0', static_cast<std::uint8_t>(255));
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
			fbr::cur()->wait();
		}
	}
}

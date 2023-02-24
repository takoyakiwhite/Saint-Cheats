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
#include "Enums.h"
namespace Arctic
{
	enum Submenu : std::uint32_t
	{
		//HOME
		SubmenuHome,

		//SELF
		SubmenuSelf,
		SubmenuNoClip,
		SubmenuInvisible,
		SubmenuSuperjump,
		SubmenuMultipliers,
		//SESSION
		SubmenuNetwork,
		SubmenuPlayerList,
		SubmenuSelectedPlayer,
		SubmenuAntiCheat,
		
		//SELECTEDPLAYER
		SubmenuBodyguards,
		SubmenuDrops,
		SubmenuPlayerTeleport,
		//SELECTED_TROLLING
		SubmenuTrolling,
		SubmenuFakeDrops,

		//VEHICLE
		SubmenuVehicle,
		SubmenuVehicleMultipliers,
		SubmenuHornBoost,
		SubmenuEngineSound,
		SubmenuNegitiveTorque,
		SubmenuCustomize,
		//WEAPON
		SubmenuWeapon,
		SubmenuExplosiveAmmo,
		SubmenuRapidFire,
		SubmenuWeaponAnimation,
		SubmenuGunLocker,
		SubmenuGunLockerGive,
		SubmenuGunLockerAmmo,
		SubmenuWeaponMultipliers,
		
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

		//LSC
		LosSantosArmor,
		LosSantosBrakes,
		LosSantosBumpers,
		LosSantosEngine,
		LosSantosExhaust,
		LosSantosGrille,
		LosSantosHood,
		LosSantosHorn,
		LosSantosLights,
		LosSantosPlate,
		LosSantosRespray,
		LosSantosRoof,
		LosSantosSkirts,
		LosSantosSpoiler,
		LosSantosSuspension,
		LosSantosTransmission,
		LosSantosTurbo,
		LosSantosWheels,
		LosSantosWindows,
		
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

		g_Render->AddSubmenu<RegularSubmenu>("Arctic", SubmenuHome, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Player", nullptr, SubmenuSelf);
			sub->AddOption<SubOption>("Network", nullptr, SubmenuNetwork);
			sub->AddOption<SubOption>("Protections", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Teleport", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Weapon", nullptr, SubmenuWeapon);
			sub->AddOption<SubOption>("Vehicle", nullptr, SubmenuVehicle);
			sub->AddOption<SubOption>("Spawner", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Miscellaneous", nullptr, SubmenuSettings);
			sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
		});
		g_Render->AddSubmenu<RegularSubmenu>(("Self"), SubmenuSelf, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("No-Clip", nullptr, SubmenuNoClip);
				sub->AddOption<SubOption>("Invisible", nullptr, SubmenuInvisible);
				sub->AddOption<SubOption>("Super Jump", nullptr, SubmenuSuperjump);
				sub->AddOption<SubOption>("Multipliers", nullptr, SubmenuMultipliers);
				sub->AddOption<BoolOption<bool>>(("Godmode"), nullptr, &godmode, BoolDisplay::OnOff, false, [] {
					if (!godmode)
					{
						(*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits = 0;
						
					}
					});
				sub->AddOption<BoolOption<bool>>(("Never Wanted"), nullptr, &neverWantedBool, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Auto Parachute"), "Automaticly pulls you're parachite", &features.auto_parachute, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Seatbelt"), nullptr, &features.seatbelt, BoolDisplay::OnOff, false, [] {
					if (!features.seatbelt) {
						PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), false);
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, true);
					}
					});
				sub->AddOption<BoolOption<bool>>(("Pickup Entities"), nullptr, &features.pickup_mode, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Auto Clean"), nullptr, &features.autoclean, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Swim Anywhere"), nullptr, &features.swim_anywhere, BoolDisplay::OnOff, false, [] {
					if (!features.swim_anywhere)
					{
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 65, false);
					}
					});
				sub->AddOption<BoolOption<bool>>(("Tiny Ped"), nullptr, &features.tiny_ped, BoolDisplay::OnOff, false, [] {
					if (!features.tiny_ped)
					{
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, false);
					}
					});
				sub->AddOption<BoolOption<bool>>(("Unlimited Special Ability"), nullptr, &features.unlim, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Attack Friendly"), nullptr, &features.attack_friendly, BoolDisplay::OnOff, false, [] {
					if (!features.attack_friendly)
					{
						PED::SET_CAN_ATTACK_FRIENDLY(PLAYER::PLAYER_PED_ID(), false, true);
					}
					});
				sub->AddOption<BoolOption<bool>>(("Reduced Collision"), nullptr, &features.reduced, BoolDisplay::OnOff, false, [] {
					if (!features.reduced)
					{
						PED::SET_PED_CAPSULE(PLAYER::PLAYER_PED_ID(), false);
					}
					});
				sub->AddOption<BoolOption<bool>>(("Bound Ankles"), nullptr, &features.bound_ankles, BoolDisplay::OnOff, false, [] {
					if (!features.bound_ankles)
					{
						PED::SET_ENABLE_BOUND_ANKLES(PLAYER::PLAYER_PED_ID(), false);
					}
					});
				sub->AddOption<BoolOption<bool>>(("Ignored By Peds"), nullptr, &features.ignored, BoolDisplay::OnOff, false, [] {
					if (!features.ignored)
					{
						PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
							PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
							PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(PLAYER::PLAYER_ID(), true);
							PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(PLAYER::PLAYER_ID(), false);
						
					}
					});
			
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Invisible"), SubmenuInvisible, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &invisible.enabled, BoolDisplay::OnOff, false, [] {
				if (!invisible.enabled) {
					ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, false);

				}
					});
				sub->AddOption<BoolOption<bool>>(("Locally Visible"), nullptr, &invisible.local_visible, BoolDisplay::OnOff);
			});
		g_Render->AddSubmenu<RegularSubmenu>(("No-Clip"), SubmenuNoClip, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &no_clip.enabled, BoolDisplay::OnOff, false, [] {
				if (!no_clip.enabled) {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
						if (no_clip.DisableCollision) {
							ENTITY::SET_ENTITY_COLLISION(veh, true, true);
						}
					}
				}
					});
				sub->AddOption<BoolOption<bool>>(("Set Rotation"), nullptr, &no_clip.SetRotation, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Include Vehicles"), nullptr, &no_clip.WorkForVehicles, BoolDisplay::OnOff);
				if (no_clip.WorkForVehicles) {
					sub->AddOption<BoolOption<bool>>(("Stop After No Input"), nullptr, &no_clip.StopAfterNoInput, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(("Disable Collision"), nullptr, &no_clip.DisableCollision, BoolDisplay::OnOff);
				}
				
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Movement Type", nullptr, &no_clip.FlyType, &no_clip.FlyInt);
				}
				sub->AddOption<NumberOption<float>>("Speed", nullptr, &no_clip.speed, 0.1f, 50.f, 0.01f, 2);
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Multipliers"), SubmenuMultipliers, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Run Speed"), nullptr, &multipliers.run, BoolDisplay::OnOff, false, [] {
				if (!multipliers.run) {
					(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_run_speed = 1.0f;
				}
					});
				if (multipliers.run) {
					sub->AddOption<NumberOption<float>>("Speed", nullptr, &multipliers.run_speed, 0.1f, 10.f, 0.01f, 2);
				}
		
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Super Jump"), SubmenuSuperjump, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &superjump.enabled, BoolDisplay::OnOff);
		sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &superjump.Jump_Type, &superjump.Jump_Int);
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Vehicle"), SubmenuVehicle, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Handling", nullptr, Submenu::SubmenuVehicleMultipliers);
				sub->AddOption<SubOption>("Horn Boost", nullptr, Submenu::SubmenuHornBoost);
				sub->AddOption<SubOption>("Engine Sound", nullptr, Submenu::SubmenuEngineSound);
				sub->AddOption<SubOption>("Negitive Torque", nullptr, Submenu::SubmenuNegitiveTorque);
				sub->AddOption<SubOption>("LSC", nullptr, Submenu::SubmenuCustomize);
				sub->AddOption<BoolOption<bool>>(("Godmode"), nullptr, &features.vehicle_godmode, BoolDisplay::OnOff);
				
				sub->AddOption<BoolOption<bool>>(("No Plane Turbulence"), nullptr, &NoPlaneTurbulance, BoolDisplay::OnOff);

			});
		g_Render->AddSubmenu<RegularSubmenu>(("LSC"), SubmenuCustomize, [](RegularSubmenu* sub)
			{


				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					Vehicle veh; veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
					VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_XENONLIGHTS) > 0)
					{
						sub->AddOption<SubOption>("Lights", "", LosSantosLights);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) > 0)
					{
						sub->AddOption<SubOption>("Armor", "", LosSantosArmor);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) > 0)
					{
						sub->AddOption<SubOption>("Plates", "", LosSantosPlate);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE) > 0)
					{
						sub->AddOption<SubOption>("Engine", "", LosSantosEngine);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST) > 0)
					{
						sub->AddOption<SubOption>("Exhaust", "", LosSantosExhaust);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_BRAKES) > 0)
					{
						sub->AddOption<SubOption>("Brakes", "", LosSantosBrakes);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_GRILLE) > 0)
					{
						sub->AddOption<SubOption>("Grille", "", LosSantosGrille);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HOOD) > 0)
					{
						sub->AddOption<SubOption>("Hood", "", LosSantosHood);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HORNS) > 0)
					{
						sub->AddOption<SubOption>("Horn", "", LosSantosHorn);
					}
					
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ROOF) > 0)
					{
						sub->AddOption<SubOption>("Roof", "", LosSantosRoof);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SIDESKIRT) > 0)
					{
						sub->AddOption<SubOption>("Skirts", "", LosSantosSkirts);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPOILER) > 0)
					{
						sub->AddOption<SubOption>("Spoiler", "", LosSantosSpoiler);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SUSPENSION) > 0)
					{
						sub->AddOption<SubOption>("Suspension", "", LosSantosSuspension);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRANSMISSION) > 0)
					{
						sub->AddOption<SubOption>("Transmission", "", LosSantosTransmission);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) > 0)
					{
						//	sub->AddOption<SubOption>("Wheels", "", LosSantosWheels);
					}
					if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_WINDOWS) > 0)
					{
						sub->AddOption<SubOption>("Windows", "", LosSantosWindows);
					}
				}
				else
				{
					sub->AddOption<RegularOption>("Vehicle Not Found", "");
				}


			});
		g_Render->AddSubmenu<RegularSubmenu>("Windows", LosSantosWindows, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_WINDOWS, -1);
					});
		sub->AddOption<RegularOption>("Light Smoke", "", []
			{
				VehicleModifier(MOD_WINDOWS, 1);
			});
		sub->AddOption<RegularOption>("Dark Smoke", "", []
			{
				VehicleModifier(MOD_WINDOWS, 2);
			});
		sub->AddOption<RegularOption>("Limo", "", []
			{
				VehicleModifier(MOD_WINDOWS, 3);
			});
			});
		g_Render->AddSubmenu<RegularSubmenu>("Armor", LosSantosArmor, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_ARMOR, -1);
					});
		sub->AddOption<RegularOption>("20%", "", []
			{
				VehicleModifier(MOD_ARMOR, 0);
			});
		sub->AddOption<RegularOption>("40%", "", []
			{
				VehicleModifier(MOD_ARMOR, 1);
			});
		sub->AddOption<RegularOption>("60%", "", []
			{
				VehicleModifier(MOD_ARMOR, 2);
			});
		sub->AddOption<RegularOption>("80%", "", []
			{
				VehicleModifier(MOD_ARMOR, 3);
			});
		sub->AddOption<RegularOption>("100%", "", []
			{
				VehicleModifier(MOD_ARMOR, 4);
			});
			});
		g_Render->AddSubmenu<RegularSubmenu>("Horns", LosSantosHorn, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_HORNS, -1);
					});
		sub->AddOption<RegularOption>("1", "", []
			{
				VehicleModifier(MOD_HORNS, 0);
			});
		sub->AddOption<RegularOption>("2", "", []
			{
				VehicleModifier(MOD_HORNS, 1);
			});
		sub->AddOption<RegularOption>("3", "", []
			{
				VehicleModifier(MOD_HORNS, 2);
			});
		sub->AddOption<RegularOption>("4", "", []
			{
				VehicleModifier(MOD_HORNS, 3);
			});
		sub->AddOption<RegularOption>("5", "", []
			{
				VehicleModifier(MOD_HORNS, 4);
			});
		sub->AddOption<RegularOption>("6", "", []
			{
				VehicleModifier(MOD_HORNS, 5);
			});
		sub->AddOption<RegularOption>("7", "", []
			{
				VehicleModifier(MOD_HORNS, 6);
			});
		sub->AddOption<RegularOption>("8", "", []
			{
				VehicleModifier(MOD_HORNS, 7);
			});
		sub->AddOption<RegularOption>("9", "", []
			{
				VehicleModifier(MOD_HORNS, 8);
			});
		sub->AddOption<RegularOption>("10", "", []
			{
				VehicleModifier(MOD_HORNS, 9);
			});
		sub->AddOption<RegularOption>("11", "", []
			{
				VehicleModifier(MOD_HORNS, 10);
			});
		sub->AddOption<RegularOption>("12", "", []
			{
				VehicleModifier(MOD_HORNS, 11);
			});
		sub->AddOption<RegularOption>("13", "", []
			{
				VehicleModifier(MOD_HORNS, 12);
			});
		sub->AddOption<RegularOption>("14", "", []
			{
				VehicleModifier(MOD_HORNS, 13);
			});
		sub->AddOption<RegularOption>("15", "", []
			{
				VehicleModifier(MOD_HORNS, 14);
			});
		sub->AddOption<RegularOption>("16", "", []
			{
				VehicleModifier(MOD_HORNS, 15);
			});
		sub->AddOption<RegularOption>("17", "", []
			{
				VehicleModifier(MOD_HORNS, 16);
			});
		sub->AddOption<RegularOption>("18", "", []
			{
				VehicleModifier(MOD_HORNS, 17);
			});
		sub->AddOption<RegularOption>("19", "", []
			{
				VehicleModifier(MOD_HORNS, 18);
			});
		sub->AddOption<RegularOption>("20", "", []
			{
				VehicleModifier(MOD_HORNS, 19);
			});
		sub->AddOption<RegularOption>("21", "", []
			{
				VehicleModifier(MOD_HORNS, 20);
			});
		sub->AddOption<RegularOption>("22", "", []
			{
				VehicleModifier(MOD_HORNS, 21);
			});
		sub->AddOption<RegularOption>("23", "", []
			{
				VehicleModifier(MOD_HORNS, 22);
			});
		sub->AddOption<RegularOption>("24", "", []
			{
				VehicleModifier(MOD_HORNS, 23);
			});
		sub->AddOption<RegularOption>("25", "", []
			{
				VehicleModifier(MOD_HORNS, 24);
			});
		sub->AddOption<RegularOption>("26", "", []
			{
				VehicleModifier(MOD_HORNS, 25);
			});
		sub->AddOption<RegularOption>("27", "", []
			{
				VehicleModifier(MOD_HORNS, 26);
			});
		sub->AddOption<RegularOption>("28", "", []
			{
				VehicleModifier(MOD_HORNS, 27);
			});
		sub->AddOption<RegularOption>("29", "", []
			{
				VehicleModifier(MOD_HORNS, 28);
			});
		sub->AddOption<RegularOption>("30", "", []
			{
				VehicleModifier(MOD_HORNS, 29);
			});
		sub->AddOption<RegularOption>("31", "", []
			{
				VehicleModifier(MOD_HORNS, 30);
			});
		sub->AddOption<RegularOption>("32", "", []
			{
				VehicleModifier(MOD_HORNS, 31);
			});
		sub->AddOption<RegularOption>("33", "", []
			{
				VehicleModifier(MOD_HORNS, 32);
			});
		sub->AddOption<RegularOption>("34", "", []
			{
				VehicleModifier(MOD_HORNS, 33);
			});
		sub->AddOption<RegularOption>("35", "", []
			{
				VehicleModifier(MOD_HORNS, 34);
			});
		sub->AddOption<RegularOption>("36", "", []
			{
				VehicleModifier(MOD_HORNS, 35);
			});
		sub->AddOption<RegularOption>("37", "", []
			{
				VehicleModifier(MOD_HORNS, 36);
			});
		sub->AddOption<RegularOption>("38", "", []
			{
				VehicleModifier(MOD_HORNS, 37);
			});
		sub->AddOption<RegularOption>("39", "", []
			{
				VehicleModifier(MOD_HORNS, 38);
			});
		sub->AddOption<RegularOption>("40", "", []
			{
				VehicleModifier(MOD_HORNS, 39);
			});
			});
		g_Render->AddSubmenu<RegularSubmenu>("Brakes", LosSantosBrakes, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_BRAKES, -1);
					});
		sub->AddOption<RegularOption>("Street Brakes", "", []
			{
				VehicleModifier(MOD_BRAKES, 0);
			});
		sub->AddOption<RegularOption>("Street Brakes", "", []
			{
				VehicleModifier(MOD_BRAKES, 1);
			});
		sub->AddOption<RegularOption>("Race Brakes", "", []
			{
				VehicleModifier(MOD_BRAKES, 2);
			});
			});
		g_Render->AddSubmenu<RegularSubmenu>("Engine", LosSantosEngine, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_ENGINE, -1);
					});
		sub->AddOption<RegularOption>("1", "", []
			{
				VehicleModifier(MOD_ENGINE, 0);
			});
		sub->AddOption<RegularOption>("2", "", []
			{
				VehicleModifier(MOD_ENGINE, 1);
			});
		sub->AddOption<RegularOption>("3", "", []
			{
				VehicleModifier(MOD_ENGINE, 2);
			});
		sub->AddOption<RegularOption>("4", "", []
			{
				VehicleModifier(MOD_ENGINE, 3);
			});
			});
		g_Render->AddSubmenu<RegularSubmenu>("Exhaust", LosSantosExhaust, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_EXHAUST, -1);
					});
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST); i++)
		{
			sub->AddOption<RegularOption>(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_EXHAUST, i)), "", [i]
				{
					VehicleModifier(MOD_EXHAUST, i);
				});
		}
			});
		g_Render->AddSubmenu<RegularSubmenu>("Grille", LosSantosGrille, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_GRILLE, -1);
					});
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_GRILLE);
		for (int i = 0; i < AmountOfVehicleMods; i++)
		{
			const char* GrilleTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_GRILLE, i);
			const char* GrilleName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(GrilleTextLabel);
			sub->AddOption<RegularOption>(GrilleName, "", [i]
				{
					VehicleModifier(MOD_GRILLE, i);
				});
		}
			});
		g_Render->AddSubmenu<RegularSubmenu>("Hood", LosSantosHood, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_HOOD, -1);
					});
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HOOD);
		for (int i = 0; i < AmountOfVehicleMods; i++)
		{
			const char* HoodTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_HOOD, i);
			const char* HoodName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(HoodTextLabel);
			sub->AddOption<RegularOption>(HoodName, "", [i]
				{
					VehicleModifier(MOD_HOOD, i);
				});
		}
			});
		g_Render->AddSubmenu<RegularSubmenu>("Roof", LosSantosRoof, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_ROOF, -1);
					});
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ROOF);
		for (int i = 0; i < AmountOfVehicleMods; i++)
		{
			const char* RoofTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_ROOF, i);
			const char* RoofName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(RoofTextLabel);
			sub->AddOption<RegularOption>(RoofName, "", [i]
				{
					VehicleModifier(MOD_ROOF, i);
				});
		}
			});
		g_Render->AddSubmenu<RegularSubmenu>("Skirts", LosSantosSkirts, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("None", "", []
					{
						VehicleModifier(MOD_SIDESKIRT, -1);
					});
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SIDESKIRT);
		for (int i = 0; i < AmountOfVehicleMods; i++)
		{
			const char* SkirtsTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_SIDESKIRT, i);
			const char* SkirtsName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SkirtsTextLabel);
			sub->AddOption<RegularOption>(SkirtsName, "", [i]
				{
					VehicleModifier(MOD_SIDESKIRT, i);
				});
		}
			});
		g_Render->AddSubmenu<RegularSubmenu>("Suspension", LosSantosSuspension, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("Stock Suspension", "", []
					{
						VehicleModifier(MOD_SUSPENSION, -1);
					});
		sub->AddOption<RegularOption>("Lowered Suspension", "", []
			{
				VehicleModifier(MOD_SUSPENSION, 0);
			});
		sub->AddOption<RegularOption>("Street Suspension", "", []
			{
				VehicleModifier(MOD_SUSPENSION, 1);
			});
		sub->AddOption<RegularOption>("Sport Suspension", "", []
			{
				VehicleModifier(MOD_SUSPENSION, 2);
			});
		sub->AddOption<RegularOption>("Competition Suspension", "", []
			{
				VehicleModifier(MOD_SUSPENSION, 3);
			});
			});
		g_Render->AddSubmenu<RegularSubmenu>("Transmission", LosSantosTransmission, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("Stock Transmission", "", []
					{
						VehicleModifier(MOD_TRANSMISSION, -1);
					});
		sub->AddOption<RegularOption>("Street Transmission", "", []
			{
				VehicleModifier(MOD_TRANSMISSION, 0);
			});
		sub->AddOption<RegularOption>("Sports Transmission", "", []
			{
				VehicleModifier(MOD_TRANSMISSION, 1);
			});
		sub->AddOption<RegularOption>("Race Transmission", "", []
			{
				VehicleModifier(MOD_TRANSMISSION, 2);
			});
			});
		g_Render->AddSubmenu<RegularSubmenu>("Spoiler", LosSantosSpoiler, [](RegularSubmenu* sub)
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		int AmountOfVehicleMods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 0);
		for (int i = 0; i < AmountOfVehicleMods; i++)
		{
			const char* SpoilerTextLabel = VEHICLE::GET_MOD_TEXT_LABEL(veh, 0, i);
			const char* SpoilerName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(SpoilerTextLabel);
			sub->AddOption<RegularOption>(SpoilerName, "", [i]
				{
					VehicleModifier(0, i);
				});
		}
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Negitive Torque"), SubmenuNegitiveTorque, [](RegularSubmenu* sub)
			{

				
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &negitiveTorque.enabled, BoolDisplay::OnOff, false, [] {
				if (!negitiveTorque.enabled) {
					VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1.0);
				}
					});
			sub->AddOption<NumberOption<float>>("Multiplier", nullptr, &negitiveTorque.multiplier, 0.1f, 100.f, 0.10f, 2);


			});
		g_Render->AddSubmenu<RegularSubmenu>(("Engine Sound"), SubmenuEngineSound, [](RegularSubmenu* sub)
			{
				
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &sound_type, &sound_int);
				sub->AddOption<RegularOption>(("Apply"), nullptr, []
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						AUDIO::FORCE_USE_AUDIO_GAME_OBJECT(veh, sound_data[sound_int]);
					});

		
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Handling"), SubmenuVehicleMultipliers, [](RegularSubmenu* sub)
			{
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				sub->AddOption<NumberOption<float>>("Mass", nullptr, &handling->m_mass, 0.f, 10000.f, 0.25f, 1);
				sub->AddOption<NumberOption<float>>("Initial Drag Coeff", nullptr, &handling->m_initial_drag_coeff, 0.f, 10000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Downforce Multiplier", nullptr, &handling->m_downforce_multiplier, 0.f, 10000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Popup Light Rotation", nullptr, &handling->m_popup_light_rotation, 0.f, 10000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Centre Of Max X", nullptr, &handling->m_centre_of_mass.x, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Centre Of Max Y", nullptr, &handling->m_centre_of_mass.y, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Centre Of Max Z", nullptr, &handling->m_centre_of_mass.z, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Inertia Multiplier X", nullptr, &handling->m_inertia_mult.x, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Inertia Multiplier Y", nullptr, &handling->m_inertia_mult.y, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Inertia Multiplier Z", nullptr, &handling->m_inertia_mult.z, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Buoyancy", nullptr, &handling->m_buoyancy, -1000.f, 1000.f, 1.0f, 1);
				sub->AddOption<NumberOption<float>>("Drive Bias Rear", nullptr, &handling->m_drive_bias_rear, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Drive Bias Front", nullptr, &handling->m_drive_bias_front, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Acceleration", nullptr, &handling->m_acceleration, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Upshift", nullptr, &handling->m_upshift, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Downshift", nullptr, &handling->m_downshift, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Initial Drive Force", nullptr, &handling->m_initial_drive_force, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Drive Maxx Flat Velocity", nullptr, &handling->m_drive_max_flat_velocity, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Initial Drive Max Flat Velocity", nullptr, &handling->m_initial_drive_max_flat_vel, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Brake Force", nullptr, &handling->m_brake_force, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Brake Bias Front", nullptr, &handling->m_brake_bias_front, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Brake Bias Rear", nullptr, &handling->m_brake_bias_rear, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Handbrake Force", nullptr, &handling->m_handbrake_force, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Steering Lock", nullptr, &handling->m_steering_lock, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Steering Lock Ratio", nullptr, &handling->m_steering_lock_ratio, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Curve Max", nullptr, &handling->m_traction_curve_max, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Curve Min", nullptr, &handling->m_traction_curve_min, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Curve Lateral", nullptr, &handling->m_traction_curve_lateral, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Curve Ratio", nullptr, &handling->m_traction_curve_ratio, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Curve Lateral", nullptr, &handling->m_curve_lateral, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Curve Lateral Ratio", nullptr, &handling->m_curve_lateral_ratio, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Spring Delta Max", nullptr, &handling->m_traction_spring_delta_max, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Spring Delta Max Ratio", nullptr, &handling->m_traction_spring_delta_max_ratio, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Low Speed Traction Loss Multiplier", nullptr, &handling->m_low_speed_traction_loss_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Camber Stiffness", nullptr, &handling->m_camber_stiffness, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Bias Front", nullptr, &handling->m_traction_bias_front, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Bias Rear", nullptr, &handling->m_traction_bias_rear, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Traction Loss Multiplier", nullptr, &handling->m_traction_loss_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Suspension Force", nullptr, &handling->m_suspension_force, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Suspension Comp Damp", nullptr, &handling->m_suspension_comp_damp, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Suspension Rebound Damp", nullptr, &handling->m_suspension_rebound_damp, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Suspsension Upper Limit", nullptr, &handling->m_suspension_upper_limit, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Suspension Lower Limit", nullptr, &handling->m_suspension_lower_limit, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Suspension Raise", nullptr, &handling->m_suspension_raise, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Suspension Bias Front", nullptr, &handling->m_suspension_bias_front, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Suspension Bias Rear", nullptr, &handling->m_suspension_bias_rear, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Anti Rollbar Force", nullptr, &handling->m_anti_rollbar_force, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Anti Rollbar Bias Front", nullptr, &handling->m_anti_rollbar_bias_front, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Anti Rollbar Bias Rear", nullptr, &handling->m_anti_rollbar_bias_rear, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Roll Centre Height Front", nullptr, &handling->m_roll_centre_height_front, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Roll Centre Height Rear", nullptr, &handling->m_roll_centre_height_rear, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Collision Damage Multiplier", nullptr, &handling->m_collision_damage_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Weapon Damage Multiplier", nullptr, &handling->m_weapon_damamge_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Deformation Multiplier", nullptr, &handling->m_deformation_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Engine Damage Multiplier", nullptr, &handling->m_engine_damage_mult, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Petrol Tank Volume", nullptr, &handling->m_petrol_tank_volume, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Oil Volume", nullptr, &handling->m_oil_volume, -1000.f, 1000.f, 0.1f, 1);
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Horn Boost"), SubmenuHornBoost, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &hornboost.enabled, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Smooth"), nullptr, &hornboost.smooth, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Only On Ground"), nullptr, &hornboost.onlyOnGround, BoolDisplay::OnOff);
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Boost Type", nullptr, &hornboost.Boost_Type, &hornboost.Boost_Int);
				sub->AddOption<NumberOption<std::int32_t>>("Speed", nullptr, &hornboost.speed, 0, 1000);
				if (hornboost.smooth) {
					sub->AddOption<NumberOption<float>>("Boost Power", nullptr, &hornboost.boost_power, 0.1f, 50.f, 0.05f, 2);
				}
				

			});
		g_Render->AddSubmenu<RegularSubmenu>(("Weapon"), SubmenuWeapon, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Explosive Ammo", nullptr, SubmenuExplosiveAmmo);
				sub->AddOption<SubOption>("Rapid Fire", nullptr, SubmenuRapidFire);
				sub->AddOption<SubOption>("Multipliers", nullptr, SubmenuWeaponMultipliers);
				sub->AddOption<SubOption>("Animation", nullptr, SubmenuWeaponAnimation);
				sub->AddOption<SubOption>("Gun Locker", nullptr, SubmenuGunLocker);
				sub->AddOption<BoolOption<bool>>(("Infinite Ammo"), nullptr, &features.infinite_ammo, BoolDisplay::OnOff, false, [] {
					if (!features.infinite_ammo) {
						WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), false);
					}
					});
				sub->AddOption<BoolOption<bool>>(("Teleport"), nullptr, &features.teleport_gun, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Delete"), nullptr, &features.delete_gun, BoolDisplay::OnOff);
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Multipliers"), SubmenuWeaponMultipliers, [](RegularSubmenu* sub)
			{
				auto weapon = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info;
				
				sub->AddOption<BoolOption<bool>>(("No Recoil"), nullptr, &features.no_recoil, BoolDisplay::OnOff);
				sub->AddOption<NumberOption<float>>("Accuracy Spread", nullptr, &weapon->m_accuracy_spread, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Accurate Mode Acuracy Modifier", nullptr, &weapon->m_accurate_mode_accuracy_modifier, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("RNG Accuracy", nullptr, &weapon->m_run_and_gun_accuracy, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("RNG Min Accuracy", nullptr, &weapon->m_run_and_gun_min_accuracy, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Recoil Accuracy Max", nullptr, &weapon->m_recoil_accuracy_max, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Recoil Error Time", nullptr, &weapon->m_recoil_error_time, -1000.f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Recoil Recovery Rate", nullptr, &weapon->m_recoil_recovery_rate, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Recoil Accuracy To Allow Headshot AI", nullptr, &weapon->m_recoil_accuracy_to_allow_headshot_ai, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Min Headshot Distance AI", nullptr, &weapon->m_min_headshot_distance_ai, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Max Headshot Range AI", nullptr, &weapon->m_max_headshot_distance_ai, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Headshot Damage Modifie AIr", nullptr, &weapon->m_headshot_damage_modifier_ai, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Recoil Accuracy To Allow Headshot Player ", nullptr, &weapon->m_recoil_accuracy_to_allow_headshot_player, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Min Headshot Distance Player", nullptr, &weapon->m_min_headshot_distance_player, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Max Headshot Distance Player", nullptr, &weapon->m_max_headshot_distance_player, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Headshot Damage Modifier Player", nullptr, &weapon->m_headshot_damage_modifier_player, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Damage", nullptr, &weapon->m_damage, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Damage Time", nullptr, &weapon->m_damage_time, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Damage Time In Vehicle", nullptr, &weapon->m_damage_time_in_vehicle, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Damage Time In Vehicle Headshot", nullptr, &weapon->m_damage_time_in_vehicle_headshot, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Hit Limbs Damage Modifier", nullptr, &weapon->m_hit_limbs_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Network Hit Limbs Damage Modifier", nullptr, &weapon->m_network_hit_limbs_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Lightly Armoured Damage Modifier", nullptr, &weapon->m_lightly_armoured_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Vehilce Damage Modifier", nullptr, &weapon->m_vehicle_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Force", nullptr, &weapon->m_force, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Force On Ped", nullptr, &weapon->m_force_on_ped, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Force On Vehicle", nullptr, &weapon->m_force_on_vehicle, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Force On Heli", nullptr, &weapon->m_force_on_heli, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Force Max Strength Multiplier", nullptr, &weapon->m_force_max_strength_mult, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Force Falloff Range Start", nullptr, &weapon->m_force_falloff_range_start, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Force Falloff Range End", nullptr, &weapon->m_force_falloff_range_end, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Force Falloff Range Min", nullptr, &weapon->m_force_falloff_range_min, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Project Force", nullptr, &weapon->m_project_force, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Frag Impulse", nullptr, &weapon->m_frag_impulse, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Penetration", nullptr, &weapon->m_penetration, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Vertical Launch Ajustment", nullptr, &weapon->m_vertical_launch_adjustment, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Speed", nullptr, &weapon->m_speed, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Batch Spread", nullptr, &weapon->m_batch_spread, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reload Time MP", nullptr, &weapon->m_reload_time_mp, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reload Time SP", nullptr, &weapon->m_reload_time_sp, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Vehicle Reload Time", nullptr, &weapon->m_vehicle_reload_time, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Animation Reload Time", nullptr, &weapon->m_anim_reload_time, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Time Betweeen Shots", nullptr, &weapon->m_time_between_shots, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Time Left Between Shots", nullptr, &weapon->m_time_left_between_shots_where_should_fire_is_cached, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Spinup Time", nullptr, &weapon->m_spinup_time, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Spin Time", nullptr, &weapon->m_spin_time, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Spin Down Time", nullptr, &weapon->m_spindown_time, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Alternate Wait Time", nullptr, &weapon->m_alternate_wait_time, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Network Player Damage Modifier", nullptr, &weapon->m_network_player_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Network Ped Damage Modifier", nullptr, &weapon->m_network_ped_damage_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Network Headshot Modifier", nullptr, &weapon->m_network_headshot_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Lock On Range", nullptr, &weapon->m_lock_on_range, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Weapon Range", nullptr, &weapon->m_weapon_range, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("AI Sound Range", nullptr, &weapon->m_ai_sound_range, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("AI Potential Blast Event Range", nullptr, &weapon->m_ai_potential_blast_event_range, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Damage Fall Off Range Min", nullptr, &weapon->m_damage_fall_off_range_min, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Damage Fall Off Range Max", nullptr, &weapon->m_damage_fall_off_range_max, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Damage Fall Off Modifier", nullptr, &weapon->m_damage_fall_off_modifier, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Min Time Between Recoil Shakes", nullptr, &weapon->m_min_time_between_recoil_shakes, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Recoil Shake Amplitude", nullptr, &weapon->m_recoil_shake_amplitude, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Explosion Shake Amplitude (Actual Recoil)", nullptr, &weapon->m_explosion_shake_amplitude, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Camera FOV", nullptr, &weapon->m_camera_fov, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("First Person Aim Fov Min", nullptr, &weapon->m_first_person_aim_fov_min, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("First Person Aim Fov Max", nullptr, &weapon->m_first_person_aim_fov_max, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("First Person Scope FOV", nullptr, &weapon->m_first_person_scope_fov, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("First Person Scope Attachment FOV", nullptr, &weapon->m_first_person_scope_attachment_fov, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reticule Hud Position X", nullptr, &weapon->m_reticule_hud_position.x, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reticule Hud Position Y", nullptr, &weapon->m_reticule_hud_position.y, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reticule Hud Position POV Turret X", nullptr, &weapon->m_reticule_hud_position_pov_turret.x, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reticule Hud Position POV Turret Y", nullptr, &weapon->m_reticule_hud_position_pov_turret.y, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reticule Min Size Standing", nullptr, &weapon->m_reticule_min_size_standing, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reticule Min Size Crouched", nullptr, &weapon->m_reticule_min_size_crouched, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Reticule Size", nullptr, &weapon->m_reticule_scale, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("HUD Range", nullptr, &weapon->m_hud_range, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Aiming Breathing Additive Weight", nullptr, &weapon->m_aiming_breathing_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Firing Breathing Additive Weight", nullptr, &weapon->m_firing_breathing_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Stealth Aiming Breathing Additive Weight", nullptr, &weapon->m_stealth_aiming_breathing_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Stealth Firing Breathing Additive Weight", nullptr, &weapon->m_stealth_firing_breathing_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Aiming Lean Additive Weight", nullptr, &weapon->m_aiming_lean_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Firing Lean Additive Weight", nullptr, &weapon->m_firing_lean_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Stealth Aiming Lean Additive Weight", nullptr, &weapon->m_stealth_aiming_lean_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				sub->AddOption<NumberOption<float>>("Stealth Firing Lean Additive Weight", nullptr, &weapon->m_stealth_firing_lean_additive_weight, 0.0f, 1000.f, 0.1f, 1);
				


			});
		g_Render->AddSubmenu<RegularSubmenu>(("Gun Locker"), SubmenuGunLocker, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Ammo", nullptr, SubmenuGunLockerAmmo);
		sub->AddOption<SubOption>("Give", nullptr, SubmenuGunLockerGive);
				
		

			});
		g_Render->AddSubmenu<RegularSubmenu>(("Give"), SubmenuGunLockerGive, [](RegularSubmenu* sub)
			{
				int Maxammo = 0;
				
				if (give_weapon.type_int != 0) {
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), give_weapon.data[give_weapon.type_int], &Maxammo);
				}
				if (give_weapon.type_int == 0) {
					Maxammo = 9999;
				}
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &give_weapon.type, &give_weapon.type_int);
				sub->AddOption<NumberOption<std::int32_t>>("Ammo", nullptr, &give_weapon.amount, 1, Maxammo);
				sub->AddOption<RegularOption>(("Apply"), nullptr, []
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
		g_Render->AddSubmenu<RegularSubmenu>(("Ammo"), SubmenuGunLockerAmmo, [](RegularSubmenu* sub)
			{
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &give_ammo.type, &give_ammo.type_int);
		if (give_ammo.type_int == 1) {
			Hash weaponhash;
			int Maxammo = 0;
			WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
			WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), weaponhash, &Maxammo);
			sub->AddOption<NumberOption<std::int32_t>>("Amount", nullptr, &give_ammo.amount, 1, Maxammo);
		}
		else {
			sub->AddOption<NumberOption<std::int32_t>>("Amount", nullptr, &give_ammo.amount, 1, 9999);
			
		}
				sub->AddOption<RegularOption>(("Give"), nullptr, []
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
		g_Render->AddSubmenu<RegularSubmenu>(("Animation"), SubmenuWeaponAnimation, [](RegularSubmenu* sub)
			{
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &animation_type, &animation_int);
		sub->AddOption<RegularOption>(("Apply"), nullptr, []
			{
				WEAPON::SET_WEAPON_ANIMATION_OVERRIDE(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY(animation_data[animation_int]));
			});

			});
		g_Render->AddSubmenu<RegularSubmenu>(("Rapid Fire"), SubmenuRapidFire, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &rapid_fire.enabled, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Disable When Reloading"), nullptr, &rapid_fire.disable_when_reloading, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Disable Shooting"), nullptr, &rapid_fire.disable_shooting, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Only When Aiming"), nullptr, &rapid_fire.only_when_aiming, BoolDisplay::OnOff);
				sub->AddOption<NumberOption<std::int32_t>>("Delay", nullptr, &rapid_fire.delay, 0, 5000);

			});
		g_Render->AddSubmenu<RegularSubmenu>(("Explosive Ammo"), SubmenuExplosiveAmmo, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &explosiveAmmo.enabled, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Sound"), nullptr, &explosiveAmmo.sound, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>(("Invisible"), nullptr, &explosiveAmmo.invisible, BoolDisplay::OnOff);
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &explosiveAmmo.explode_type, &explosiveAmmo.explode_int);
				sub->AddOption<NumberOption<float>>("Damage", nullptr, &explosiveAmmo.damage, 0.0f, 150.f, 0.10f, 2);
				sub->AddOption<NumberOption<float>>("Camera Shake", nullptr, &explosiveAmmo.camera_shake, 0.0f, 150.f, 0.10f, 2);

			});
		g_Render->AddSubmenu<RegularSubmenu>(("Network"), SubmenuNetwork, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Players", nullptr, SubmenuPlayerList);
				sub->AddOption<SubOption>("Modder Detection", nullptr, SubmenuAntiCheat);
				sub->AddOption<BoolOption<bool>>(("Off The Radar"), nullptr, &features.off_the_radar, BoolDisplay::OnOff);
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Modder Detection"), SubmenuAntiCheat, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Enabled"), nullptr, &antiCheat.enabled, BoolDisplay::OnOff);
		sub->AddOption<BoolOption<bool>>(("Speed"), nullptr, &antiCheat.speed, BoolDisplay::OnOff);
		sub->AddOption<BoolOption<bool>>(("Config Flags"), nullptr, &antiCheat.configflag, BoolDisplay::OnOff);
		sub->AddOption<BoolOption<bool>>(("Invalid Model"), nullptr, &antiCheat.invalidmodel, BoolDisplay::OnOff);
		sub->AddOption<BoolOption<bool>>(("Wanted Level"), nullptr, &antiCheat.wantedlevel, BoolDisplay::OnOff);
		sub->AddOption<BoolOption<bool>>(("Godmode"), nullptr, &antiCheat.godmode, BoolDisplay::OnOff);
		

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
				sub->AddOption<SubOption>("Trolling", nullptr, SubmenuTrolling);
				sub->AddOption<SubOption>("Bodygaurds", nullptr, SubmenuBodyguards);
				sub->AddOption<SubOption>("Drops", nullptr, SubmenuDrops);
				sub->AddOption<SubOption>("Teleport", nullptr, SubmenuPlayerTeleport);
				
				if (g_SelectedPlayer != PLAYER::PLAYER_ID()) {
					sub->AddOption<BoolOption<bool>>(("Spectate"), nullptr, &features.spectate, BoolDisplay::OnOff, false, [] {
						if (!features.spectate) {
							NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::PLAYER_PED_ID());
						}
						});
				}
	
			});
		g_Render->AddSubmenu<RegularSubmenu>("Trolling", SubmenuTrolling, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Fake Drops", nullptr, SubmenuFakeDrops);
				
				sub->AddOption<RegularOption>(("Cage"), nullptr, []
					{
						NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
						OBJECT::CREATE_OBJECT(MISC::GET_HASH_KEY("prop_gold_cont_01"), c.x, c.y, c.z - 1.f, true, false, false);
					});
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Fake Drops"), SubmenuFakeDrops, [](RegularSubmenu* sub) {
			sub->AddOption<BoolOption<bool>>(("Money"), nullptr, &Fake_drops.money, BoolDisplay::OnOff);
		sub->AddOption<BoolOption<bool>>(("RP"), nullptr, &Fake_drops.rp, BoolDisplay::OnOff);
		sub->AddOption<NumberOption<std::int32_t>>("Height", nullptr, &Fake_drops.height, 0, 100);
		sub->AddOption<NumberOption<std::int32_t>>("Delay", nullptr, &Fake_drops.delay, 0, 5000);
			});
		g_Render->AddSubmenu<RegularSubmenu>("Teleport", SubmenuPlayerTeleport, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>(("To Player"), nullptr, []
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
							ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z, true, true, true, false);
						}
					});
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Bodygaurds"), SubmenuBodyguards, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>(("Godmode"), nullptr, &bodygaurd.godmode, BoolDisplay::OnOff);
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Weapon", nullptr, &bodygaurd.Weapon, &bodygaurd.WeaponInt);
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Model", nullptr, &bodygaurd.Models, &bodygaurd.ModelInt);
				sub->AddOption<BoolOption<bool>>(("Custom Firing Pattern"), nullptr, &bodygaurd.FiringPatternEnabled, BoolDisplay::OnOff);
				if (bodygaurd.FiringPatternEnabled) {
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Firing Pattern", nullptr, &bodygaurd.FiringPattern, &bodygaurd.FiringPatternInt);
				}
				sub->AddOption<NumberOption<std::int32_t>>("Accuary", nullptr, &bodygaurd.accuary, 0, 100);
				sub->AddOption<NumberOption<float>>("Damage Multiplier", nullptr, &bodygaurd.damagemultiplier, 0.0f, 150.f, 0.10f, 2);
				sub->AddOption<RegularOption>(("Spawn"), nullptr, []
				{
					STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY(bodygaurd.ModelHashes[bodygaurd.ModelInt]));
					if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY(bodygaurd.ModelHashes[bodygaurd.ModelInt]))) {
						fbr::cur()->wait();
					}
					else {
						Ped ped;
						NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
						ped = PED::CREATE_PED(26, MISC::GET_HASH_KEY(bodygaurd.ModelHashes[bodygaurd.ModelInt]), c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(g_SelectedPlayer), true, true);
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
					}
				});
			});
		g_Render->AddSubmenu<RegularSubmenu>(("Drops"), SubmenuDrops, [](RegularSubmenu* sub) {
			sub->AddOption<BoolOption<bool>>(("Money"), nullptr, &drops.money, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>(("RP"), nullptr, &drops.rp, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<std::int32_t>>("Height", nullptr, &drops.height, 0, 100);
			sub->AddOption<NumberOption<std::int32_t>>("Delay", nullptr, &drops.delay, 0, 5000);
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
				sub->AddOption<RegularOption>("Random", "", []
				{
					g_Render->ThemeIterator = MISC::GET_RANDOM_INT_IN_RANGE(0, 8);
				});
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

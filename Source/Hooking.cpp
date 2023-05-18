#include "Hooking.hpp"
#include "Signatures.hpp"
#include "ScriptManager.hpp"
#include "CustomText.hpp"
#include "Util.hpp"
#include "D3DRenderer.hpp"
#include "UI/Interface.hpp"
#include "Natives.hpp"
#include "FiberHelper.hpp"
#include <MinHook/MinHook.h>
#include "Chat Commands.h"
#include "Features.h"
#include "Spoofing.h"
#include "../Libraries/Include/GTAV-Classes/netsync/nodes/player/CPlayerGameStateDataNode.hpp"
#include <GTAV-Classes/base/CObject.hpp>
#ifdef BIGBASE_DEBUG
#  pragma comment(lib, "MinHook-Debug.lib")
#else
#  pragma comment(lib, "MinHook-Release.lib")
#endif

namespace Saint
{

	namespace
	{
		std::uint32_t g_HookFrameCount{};
	}

	static std::vector<std::pair<Hash, std::vector<uint64_t>>> trees = {
		{rage::joaat("CAutomobileSyncTree"),
			{
				rage::joaat("CVehicleCreationDataNode"),
				rage::joaat("CAutomobileCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CVehicleGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CVehicleScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CVehicleAppearanceDataNode"),
				rage::joaat("CVehicleDamageStatusDataNode"),
				rage::joaat("CVehicleComponentReservationDataNode"),
				rage::joaat("CVehicleHealthDataNode"),
				rage::joaat("CVehicleTaskDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CSectorPositionDataNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CVehicleAngVelocityDataNode"),
				rage::joaat("CVehicleSteeringDataNode"),
				rage::joaat("CVehicleControlDataNode"),
				rage::joaat("CVehicleGadgetDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CVehicleProximityMigrationDataNode"),
			}},
		{rage::joaat("CBikeSyncTree"),
			{
				rage::joaat("CVehicleCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CVehicleGameStateDataNode"),
				rage::joaat("CBikeGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CVehicleScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CVehicleAppearanceDataNode"),
				rage::joaat("CVehicleDamageStatusDataNode"),
				rage::joaat("CVehicleComponentReservationDataNode"),
				rage::joaat("CVehicleHealthDataNode"),
				rage::joaat("CVehicleTaskDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CSectorPositionDataNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CVehicleAngVelocityDataNode"),
				rage::joaat("CVehicleSteeringDataNode"),
				rage::joaat("CVehicleControlDataNode"),
				rage::joaat("CVehicleGadgetDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CVehicleProximityMigrationDataNode"),
			}},
		{rage::joaat("CBoatSyncTree"),
			{
				rage::joaat("CVehicleCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CVehicleGameStateDataNode"),
				rage::joaat("CBoatGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CVehicleScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CVehicleAppearanceDataNode"),
				rage::joaat("CVehicleDamageStatusDataNode"),
				rage::joaat("CVehicleComponentReservationDataNode"),
				rage::joaat("CVehicleHealthDataNode"),
				rage::joaat("CVehicleTaskDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CSectorPositionDataNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CVehicleAngVelocityDataNode"),
				rage::joaat("CVehicleSteeringDataNode"),
				rage::joaat("CVehicleControlDataNode"),
				rage::joaat("CVehicleGadgetDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CVehicleProximityMigrationDataNode"),
			}},
		{rage::joaat("CDoorSyncTree"),
			{
				rage::joaat("CDoorCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDoorScriptInfoDataNode"),
				rage::joaat("CDoorScriptGameStateDataNode"),
				rage::joaat("CDoorMovementDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
			}},
		{rage::joaat("CHeliSyncTree"),
			{
				rage::joaat("CVehicleCreationDataNode"),
				rage::joaat("CAutomobileCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CVehicleGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CVehicleScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CVehicleAppearanceDataNode"),
				rage::joaat("CVehicleDamageStatusDataNode"),
				rage::joaat("CVehicleComponentReservationDataNode"),
				rage::joaat("CVehicleHealthDataNode"),
				rage::joaat("CVehicleTaskDataNode"),
				rage::joaat("CHeliHealthDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CSectorPositionDataNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CVehicleAngVelocityDataNode"),
				rage::joaat("CVehicleSteeringDataNode"),
				rage::joaat("CVehicleControlDataNode"),
				rage::joaat("CVehicleGadgetDataNode"),
				rage::joaat("CHeliControlDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CVehicleProximityMigrationDataNode"),
			}},
		{rage::joaat("CObjectSyncTree"),
			{
				rage::joaat("CObjectCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CObjectGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CObjectScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CPhysicalHealthDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CObjectSectorPosNode"),
				rage::joaat("CObjectOrientationNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CPhysicalAngVelocityDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
			}},
		{rage::joaat("CPedSyncTree"),
			{
				rage::joaat("CPedCreationDataNode"),
				rage::joaat("CPedScriptCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CPedGameStateDataNode"),
				rage::joaat("CPedComponentReservationDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CPedScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPedAttachDataNode"),
				rage::joaat("CPedHealthDataNode"),
				rage::joaat("CPedMovementGroupDataNode"),
				rage::joaat("CPedAIDataNode"),
				rage::joaat("CPedAppearanceDataNode"),
				rage::joaat("CPedOrientationDataNode"),
				rage::joaat("CPedMovementDataNode"),
				rage::joaat("CPedTaskTreeDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CPedSectorPosMapNode"),
				rage::joaat("CPedSectorPosNavMeshNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CPedInventoryDataNode"),
				rage::joaat("CPedTaskSequenceDataNode"),
			}},
		{rage::joaat("CPickupSyncTree"),
			{
				rage::joaat("CPickupCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPickupScriptGameStateNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalHealthDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CPickupSectorPosNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CPhysicalAngVelocityDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
			}},
		{rage::joaat("CPickupPlacementSyncTree"),
			{
				rage::joaat("CPickupPlacementCreationDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CPickupPlacementStateDataNode"),
			}},
		{rage::joaat("CPlaneSyncTree"),
			{
				rage::joaat("CVehicleCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CVehicleGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CVehicleScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CVehicleAppearanceDataNode"),
				rage::joaat("CVehicleDamageStatusDataNode"),
				rage::joaat("CVehicleComponentReservationDataNode"),
				rage::joaat("CVehicleHealthDataNode"),
				rage::joaat("CVehicleTaskDataNode"),
				rage::joaat("CPlaneGameStateDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CSectorPositionDataNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CVehicleAngVelocityDataNode"),
				rage::joaat("CVehicleSteeringDataNode"),
				rage::joaat("CVehicleControlDataNode"),
				rage::joaat("CVehicleGadgetDataNode"),
				rage::joaat("CPlaneControlDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CVehicleProximityMigrationDataNode"),
			}},
		{rage::joaat("CSubmarineSyncTree"),
			{
				rage::joaat("CVehicleCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CVehicleGameStateDataNode"),
				rage::joaat("CSubmarineGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CVehicleScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CVehicleAppearanceDataNode"),
				rage::joaat("CVehicleDamageStatusDataNode"),
				rage::joaat("CVehicleComponentReservationDataNode"),
				rage::joaat("CVehicleHealthDataNode"),
				rage::joaat("CVehicleTaskDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CSectorPositionDataNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CVehicleAngVelocityDataNode"),
				rage::joaat("CVehicleSteeringDataNode"),
				rage::joaat("CVehicleControlDataNode"),
				rage::joaat("CVehicleGadgetDataNode"),
				rage::joaat("CSubmarineControlDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CVehicleProximityMigrationDataNode"),
			}},
		{rage::joaat("CPlayerSyncTree"),
			{
				rage::joaat("CPlayerCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CPedGameStateDataNode"),
				rage::joaat("CPedComponentReservationDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPlayerGameStateDataNode"),
				rage::joaat("CPedAttachDataNode"),
				rage::joaat("CPedHealthDataNode"),
				rage::joaat("CPedMovementGroupDataNode"),
				rage::joaat("CPedAIDataNode"),
				rage::joaat("CPlayerAppearanceDataNode"),
				rage::joaat("CPlayerPedGroupDataNode"),
				rage::joaat("CPlayerAmbientModelStreamingNode"),
				rage::joaat("CPlayerGamerDataNode"),
				rage::joaat("CPlayerExtendedGameStateNode"),
				rage::joaat("CPedOrientationDataNode"),
				rage::joaat("CPedMovementDataNode"),
				rage::joaat("CPedTaskTreeDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CPedTaskSpecificDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CPlayerSectorPosNode"),
				rage::joaat("CPlayerCameraDataNode"),
				rage::joaat("CPlayerWantedAndLOSDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
			}},
		{rage::joaat("CAutomobileSyncTree"),
			{
				rage::joaat("CVehicleCreationDataNode"),
				rage::joaat("CAutomobileCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CVehicleGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CVehicleScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CVehicleAppearanceDataNode"),
				rage::joaat("CVehicleDamageStatusDataNode"),
				rage::joaat("CVehicleComponentReservationDataNode"),
				rage::joaat("CVehicleHealthDataNode"),
				rage::joaat("CVehicleTaskDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CSectorPositionDataNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CVehicleAngVelocityDataNode"),
				rage::joaat("CVehicleSteeringDataNode"),
				rage::joaat("CVehicleControlDataNode"),
				rage::joaat("CVehicleGadgetDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CVehicleProximityMigrationDataNode"),
			}},
		{rage::joaat("CTrainSyncTree"),
			{
				rage::joaat("CVehicleCreationDataNode"),
				rage::joaat("CGlobalFlagsDataNode"),
				rage::joaat("CDynamicEntityGameStateDataNode"),
				rage::joaat("CPhysicalGameStateDataNode"),
				rage::joaat("CVehicleGameStateDataNode"),
				rage::joaat("CTrainGameStateDataNode"),
				rage::joaat("CEntityScriptGameStateDataNode"),
				rage::joaat("CPhysicalScriptGameStateDataNode"),
				rage::joaat("CVehicleScriptGameStateDataNode"),
				rage::joaat("CEntityScriptInfoDataNode"),
				rage::joaat("CPhysicalAttachDataNode"),
				rage::joaat("CVehicleAppearanceDataNode"),
				rage::joaat("CVehicleDamageStatusDataNode"),
				rage::joaat("CVehicleComponentReservationDataNode"),
				rage::joaat("CVehicleHealthDataNode"),
				rage::joaat("CVehicleTaskDataNode"),
				rage::joaat("CSectorDataNode"),
				rage::joaat("CSectorPositionDataNode"),
				rage::joaat("CEntityOrientationDataNode"),
				rage::joaat("CPhysicalVelocityDataNode"),
				rage::joaat("CVehicleAngVelocityDataNode"),
				rage::joaat("CVehicleSteeringDataNode"),
				rage::joaat("CVehicleControlDataNode"),
				rage::joaat("CVehicleGadgetDataNode"),
				rage::joaat("CMigrationDataNode"),
				rage::joaat("CPhysicalMigrationDataNode"),
				rage::joaat("CPhysicalScriptMigrationDataNode"),
				rage::joaat("CVehicleProximityMigrationDataNode"),
			}},
	};

	// By using this to hook natives, we are sacrificing performance for safety 
	// Detouring it is faster, but cockstar detects that
	void Hooks::GetStatInt(rage::scrNativeCallContext* src)
	{
		const auto statHash = src->get_arg<Hash>(0);
		const auto outValue = src->get_arg<int*>(1);
		const auto p2 = src->get_arg<int>(2);

		if (g_Running && g_HookFrameCount != *g_GameVariables->m_FrameCount)
		{
			g_HookFrameCount = *g_GameVariables->m_FrameCount;
			g_ScriptManager->OnGameTick();
			g_FiberManager.tick();
		}

		src->set_return_value(STATS::STAT_GET_INT(statHash, outValue, p2));
	}



	const char* Hooks::GetLabelText(void* unk, const char* label)
	{
		if (g_Running)
			if (auto text = g_CustomText->GetText(Joaat(label)))
				return text;

		return static_cast<decltype(&GetLabelText)>(g_Hooking->m_OriginalGetLabelText)(unk, label);
	}

	LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		g_D3DRenderer->WndProc(hWnd, msg, wParam, lParam);
		return static_cast<decltype(&WndProc)>(g_Hooking->m_OriginalWndProc)(hWnd, msg, wParam, lParam);
	}
	void Hooks::NETWORK_SESSION_HOST(rage::scrNativeCallContext* src)
	{
		if (join_queue)
		{
			g_GameFunctions->m_join_session_by_info(*g_GameFunctions->m_network, &g_Session_info, 1, 1 | 2 | 4, nullptr, 0);
			join_queue = false;
			src->set_return_value<BOOL>(TRUE);
		}
		else
		{
			src->set_return_value<BOOL>(NETWORK::NETWORK_SESSION_HOST(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<BOOL>(2)));
		}
	}

	void Hooks::SET_CURRENT_PED_WEAPON(rage::scrNativeCallContext* src)
	{
		const auto ped = src->get_arg<Ped>(0);
		const auto hash = src->get_arg<rage::joaat_t>(1);

		if (weapons_in_int && ped == PLAYER::PLAYER_PED_ID() && hash == rage::joaat("WEAPON_UNARMED"))
			return;

		WEAPON::SET_CURRENT_PED_WEAPON(ped, hash, src->get_arg<int>(2));
	}

	void Hooks::DISABLE_CONTROL_ACTION(rage::scrNativeCallContext* src)
	{
		const auto action = src->get_arg<ControllerInputs>(1);

		if (weapons_in_int) // Filtering from the inside of Kosatka
		{
			switch (action)
			{
				// case ControllerInputs::INPUT_JUMP: TODO: add as separate feature
			case ControllerInputs::INPUT_ATTACK:
			case ControllerInputs::INPUT_AIM:
			case ControllerInputs::INPUT_DUCK:
			case ControllerInputs::INPUT_SELECT_WEAPON:
			case ControllerInputs::INPUT_COVER:
			case ControllerInputs::INPUT_TALK:
			case ControllerInputs::INPUT_DETONATE:
			case ControllerInputs::INPUT_WEAPON_SPECIAL:
			case ControllerInputs::INPUT_WEAPON_SPECIAL_TWO:
			case ControllerInputs::INPUT_VEH_AIM:
			case ControllerInputs::INPUT_VEH_ATTACK:
			case ControllerInputs::INPUT_VEH_ATTACK2:
			case ControllerInputs::INPUT_VEH_HEADLIGHT:
			case ControllerInputs::INPUT_VEH_NEXT_RADIO:
			case ControllerInputs::INPUT_VEH_PREV_RADIO:
			case ControllerInputs::INPUT_VEH_NEXT_RADIO_TRACK:
			case ControllerInputs::INPUT_VEH_PREV_RADIO_TRACK:
			case ControllerInputs::INPUT_VEH_RADIO_WHEEL:
			case ControllerInputs::INPUT_VEH_PASSENGER_AIM:
			case ControllerInputs::INPUT_VEH_PASSENGER_ATTACK:
			case ControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON:
			case ControllerInputs::INPUT_VEH_SELECT_PREV_WEAPON:
			case ControllerInputs::INPUT_VEH_ROOF:
			case ControllerInputs::INPUT_VEH_JUMP:
			case ControllerInputs::INPUT_VEH_FLY_ATTACK:
			case ControllerInputs::INPUT_MELEE_ATTACK_LIGHT:
			case ControllerInputs::INPUT_MELEE_ATTACK_HEAVY:
			case ControllerInputs::INPUT_MELEE_ATTACK_ALTERNATE:
			case ControllerInputs::INPUT_MELEE_BLOCK:
			case ControllerInputs::INPUT_SELECT_WEAPON_UNARMED:
			case ControllerInputs::INPUT_SELECT_WEAPON_MELEE:
			case ControllerInputs::INPUT_SELECT_WEAPON_HANDGUN:
			case ControllerInputs::INPUT_SELECT_WEAPON_SHOTGUN:
			case ControllerInputs::INPUT_SELECT_WEAPON_SMG:
			case ControllerInputs::INPUT_SELECT_WEAPON_AUTO_RIFLE:
			case ControllerInputs::INPUT_SELECT_WEAPON_SNIPER:
			case ControllerInputs::INPUT_SELECT_WEAPON_HEAVY:
			case ControllerInputs::INPUT_SELECT_WEAPON_SPECIAL:
			case ControllerInputs::INPUT_ATTACK2:
			case ControllerInputs::INPUT_MELEE_ATTACK1:
			case ControllerInputs::INPUT_MELEE_ATTACK2:
			case ControllerInputs::INPUT_VEH_GUN_LEFT:
			case ControllerInputs::INPUT_VEH_GUN_RIGHT:
			case ControllerInputs::INPUT_VEH_GUN_UP:
			case ControllerInputs::INPUT_VEH_GUN_DOWN:
			case ControllerInputs::INPUT_VEH_HYDRAULICS_CONTROL_TOGGLE:
			case ControllerInputs::INPUT_VEH_MELEE_HOLD:
			case ControllerInputs::INPUT_VEH_MELEE_LEFT:
			case ControllerInputs::INPUT_VEH_MELEE_RIGHT:
			case ControllerInputs::INPUT_VEH_CAR_JUMP:
			case ControllerInputs::INPUT_VEH_ROCKET_BOOST:
			case ControllerInputs::INPUT_VEH_FLY_BOOST:
			case ControllerInputs::INPUT_VEH_PARACHUTE:
			case ControllerInputs::INPUT_VEH_BIKE_WINGS:
			case ControllerInputs::INPUT_VEH_TRANSFORM: return;
			}
		}

		PAD::DISABLE_CONTROL_ACTION(src->get_arg<int>(0), (int)action, src->get_arg<int>(2));
	}
	void Hooks::HUD_FORCE_WEAPON_WHEEL(rage::scrNativeCallContext* src)
	{
		if (weapons_in_int && src->get_arg<BOOL>(0) == false)
			return;

		HUD::HUD_FORCE_WEAPON_WHEEL(src->get_arg<BOOL>(0));
	}

	HRESULT Hooks::Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags)
	{
		if (g_Running)
		{
			g_D3DRenderer->BeginFrame();
			g_ScriptManager->OnD3DTick();
			g_D3DRenderer->EndFrame();
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&Present)>(PresentIndex)(dis, syncInterval, flags);
	}

	HRESULT Hooks::ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			g_D3DRenderer->PreResize();
			auto hr = g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
			if (SUCCEEDED(hr))
			{
				g_D3DRenderer->PostResize();
			}

			return hr;
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	}
	__int64 Hooks::CPlayerListMenuConstructor(__int64 a1, __int64 a2, __int64 a3)
	{
		auto result = static_cast<decltype(&CPlayerListMenuConstructor)>(g_Hooking->m_OriginalJoinSessionHook)(a1, a2, a3);
		m_PlayerListPointer = result;
		return result;
	}
	__int64* Hooks::PlayerWildCardHandler(std::int32_t friendIndex)
	{
		auto original = static_cast<decltype(&PlayerWildCardHandler)>(g_Hooking->m_OriginalRIDFunction)(friendIndex);
		if (m_EnableSCIDJoiner)
		{
			*original = m_SCIDJoiner;
			return original;
		}
		return static_cast<decltype(&PlayerWildCardHandler)>(g_Hooking->m_OriginalRIDFunction)(friendIndex);
	}

	bool Hooks::IncrementStatEvent(CNetworkIncrementStatEvent* neteventclass, CNetGamePlayer* Source)
	{
		if (protections.block_reports) {
			switch (neteventclass->m_stat)
			{

			case rage::joaat("MPPLY_BAD_CREW_STATUS"):
			case rage::joaat("MPPLY_BAD_CREW_MOTTO"):
			case rage::joaat("MPPLY_BAD_CREW_NAME"):
			case rage::joaat("MPPLY_BAD_CREW_EMBLEM"):
			case rage::joaat("MPPLY_EXPLOITS"):
			case rage::joaat("MPPLY_GAME_EXPLOITS"):
			case rage::joaat("MPPLY_TC_ANNOYINGME"):
			case rage::joaat("MPPLY_TC_HATE"):
			case rage::joaat("MPPLY_VC_ANNOYINGME"):
			case rage::joaat("MPPLY_VC_HATE"):
				char name[128];
				sprintf(name, ICON_FA_SHIELD_ALT"  %s reported you!", Source->m_player_info->m_net_player_data.m_name);
				g_NotificationManager->add(name, 2000);
				return true;
			}
		}

		return false;
	}

	bool Hooks::write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node) {
		if (spoofing.m_godmode) {
			node->m_is_invincible = false;
			node->m_bullet_proof = false;
			node->m_collision_proof = false;
			node->m_explosion_proof = false;
			node->m_fire_proof = false;
			node->m_melee_proof = false;
			node->m_steam_proof = false;
			node->m_water_proof = false;
		}
		if (spoofing.m_superjump) {
			node->m_super_jump = false;

		}
		if (spoofing.spectating)
		{
			node->m_is_spectating = false;
			node->m_spectating_net_id = 0;
		}
		if (spoofing.respawning) {
			node->m_respawning = false;

		}
		if (spoofing.seatbelt) {
			node->m_seatbelt = false;
		}
		return static_cast<decltype(&write_player_game_state_data_node)>(g_Hooking->m_Original_write_player_game_state_data_node)(player, node);
	}
	bool Hooks::SendNetInfo(netPlayerData* player, __int64 a2, __int64 a3, DWORD* a4)
	{


		if (spoofing.ip.enabled)
		{
			player->m_online_ip.m_field1 = spoofing.ip.field1;
			player->m_online_ip.m_field2 = spoofing.ip.field2;
			player->m_online_ip.m_field3 = spoofing.ip.field3;
			player->m_online_ip.m_field4 = spoofing.ip.field4;

		}

		return static_cast<decltype(&SendNetInfo)>(g_Hooking->m_OriginalSendNetInfo)(player, a2, a3, a4);
	}
	void Hooks::write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node) {
		if (spoofing.qa_tester) {
			//node->m_is_rockstar_qa = true;
		}

		if (spoofing.m_crew.enabled) {
			node->m_clan_data.m_clan_member_id = 1;
			node->m_clan_data.m_clan_id = 41564112;
			node->m_clan_data.m_clan_id_2 = 41564112;
			node->m_clan_data.m_is_system_clan = true;
			strcpy(node->m_clan_data.m_clan_name, spoofing.m_crew.name);
			strcpy(node->m_clan_data.m_clan_tag, spoofing.m_crew.tag.c_str());

		}

		return static_cast<decltype(&write_player_gamer_data_node)>(g_Hooking->m_Original_write_player_gamer_data_node)(player, node);
	}
	bool Hooks::send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, const char* message, bool is_team)
	{
		
		return static_cast<decltype(&send_chat_message)>(g_Hooking->m_OriginalChatSend)(team_mgr, local_gamer_info, message, is_team);
	}
	void* Hooks::AssignNewPhysicalIndexHandler(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index)
	{
		const auto* net_player_data = player->get_net_data();

		if (new_index == static_cast<uint8_t>(-1))
		{


			if (net_player_data)
			{

				char name[64];
				sprintf(name, ICON_FA_USER_MINUS"  %s is leaving slot %i", player->m_player_info->m_net_player_data.m_name, (int)player->m_player_id);
				antiCheat.remove_as_modder(player->m_player_id);
				protections.push_notification(name);
				if (all_players.notifications.log) {
					g_Logger->Info(name);
					g_Logger->Push("Leaving Player", LogFlag::Error, name);
				}


			}

			return static_cast<decltype(&AssignNewPhysicalIndexHandler)>(g_Hooking->m_OriginalAssignPhysicalIndex)(netPlayerMgr, player, new_index);
		}

		const auto result = static_cast<decltype(&AssignNewPhysicalIndexHandler)>(g_Hooking->m_OriginalAssignPhysicalIndex)(netPlayerMgr, player, new_index);


		if (net_player_data)
		{

			char name[64];
			sprintf(name, ICON_FA_USER_PLUS"  %s is joining slot %i", player->m_player_info->m_net_player_data.m_name, (int)player->m_player_id);
			if (player->m_player_info->m_net_player_data.m_name == (*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_net_player_data.m_name) {

				for (std::uint32_t i = 0; i < 32; ++i) {
					antiCheat.remove_as_modder(i);
				}
			}
			protections.push_notification(name);
			if (all_players.notifications.log) {
				g_Logger->Push("Joining Player", LogFlag::Success, name);
			}




		}

		return result;
	}

	void Hooks::InvalidModsCrashPatch(std::int64_t a1, std::int64_t a2, int a3, char a4)
	{
		if (protections.Crashes.vehicle) {
			if (!*(int64_t*)(a1 + 0xD8)) {
				protections.push_notification2("Prevented Crash (Vehicle Mods)");
				return;
			}
		}
		return static_cast<decltype(&InvalidModsCrashPatch)>(g_Hooking->m_OriginalModCrash)(a1, a2, a3, a4);
	}
	uint32_t crash_models[] = { rage::joaat("prop_dummy_01"), rage::joaat("prop_dummy_car"), rage::joaat("prop_dummy_light"), rage::joaat("prop_dummy_plane"), rage::joaat("slod_human"),
		rage::joaat("slod_small_quadped"), rage::joaat("slod_large_quadped"), rage::joaat("prop_distantcar_night"), rage::joaat("prop_distantcar_day"), rage::joaat("hei_bh1_08_details4_em_night"),
		rage::joaat("dt1_18_sq_night_slod"), rage::joaat("ss1_12_night_slod"), rage::joaat("raketrailer"), rage::joaat("boattrailer"), rage::joaat("baletrailer"), rage::joaat("prop_grass_dry_02"), rage::joaat("prop_grass_dry_03"), 1349725314, -1288391198, rage::joaat("h4_prop_bush_bgnvla_med_01"), rage::joaat("h4_prop_bush_bgnvla_lrg_01"),
		rage::joaat("h4_prop_bush_buddleia_low_01"), rage::joaat("h4_prop_bush_ear_aa"), rage::joaat("h4_prop_bush_ear_ab"), rage::joaat("h4_prop_bush_fern_low_01"),
		rage::joaat("h4_prop_bush_fern_tall_cc"), rage::joaat("h4_prop_bush_mang_ad"), rage::joaat("h4_prop_bush_mang_low_aa"), rage::joaat("h4_prop_bush_mang_low_ab"),
		rage::joaat("h4_prop_bush_seagrape_low_01"), rage::joaat("prop_h4_ground_cover"), rage::joaat("h4_prop_weed_groundcover_01"), rage::joaat("h4_prop_grass_med_01"),
		rage::joaat("h4_prop_grass_tropical_lush_01"), rage::joaat("h4_prop_grass_wiregrass_01"), rage::joaat("h4_prop_weed_01_plant"), rage::joaat("h4_prop_weed_01_row"),
		rage::joaat("urbanweeds02_l1"), rage::joaat("proc_forest_grass01"), rage::joaat("prop_small_bushyba"), rage::joaat("arbitergt"), rage::joaat("astron2"), rage::joaat("cyclone2"),
		rage::joaat("ignus2"), rage::joaat("s95"), rage::joaat("v_res_d_dildo_a"), rage::joaat("v_res_d_dildo_b"), rage::joaat("v_res_d_dildo_c"),
		rage::joaat("v_res_d_dildo_d"), rage::joaat("v_res_d_dildo_e"), rage::joaat("v_res_d_dildo_f"), rage::joaat("v_res_skateboard"), rage::joaat("prop_battery_01"), rage::joaat("prop_barbell_01"),
		rage::joaat("prop_barbell_02"), rage::joaat("prop_bandsaw_01"), rage::joaat("prop_bbq_3"), rage::joaat("v_med_curtainsnewcloth2"), rage::joaat("bh1_07_flagpoles"),
		92962485, rage::joaat("ig_wade"), rage::joaat("Entity3"), rage::joaat("Issi8") };

	bool crash_model_check(uint32_t model) {
		for (int i = 0; i < sizeof(crash_models) / sizeof(uint32_t); i++)
		{
			if (crash_models[i] == model) return true;
		}
		return false;
	}
	enum class ScriptEntityChangeType
	{
		BlockingOfNonTemporaryEvents,
		SettingOfPedRelationshipGroupHash,
		SettingOfDriveTaskCruiseSpeed,
		SettingOfLookAtEntity,
		SettingOfPlaneMinHeightAboveTerrain,
		SetPedRagdollBlockFlag,
		SettingOfTaskVehicleTempAction,
		SetPedFacialIdleAnimOverride,
		SetVehicleLockState,
		SetVehicleExclusiveDriver
	};
	enum class WorldStateDataType
	{
		CarGen,
		EntityArea,
		PopGroupOverride,
		PopMultiplierArea,
		PTFX,
		RoadNode,
		Rope,
		ScenarioBlockingArea,
		VehiclePlayerLocking
	};
	static void script_id_deserialize(CGameScriptId& id, datBitBuffer2& buffer)
	{
		id.m_hash = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
	}
	CPed* GetPed()
	{
		if (auto PedFactory = *g_GameFunctions->m_pedFactory)
			return PedFactory->m_local_ped;

		return nullptr;
	}
	bool is_in_car(Ped ped) {
		if (PED::GET_VEHICLE_PED_IS_IN(ped, false) == PED::GET_VEHICLE_PED_IS_IN(Game->Self(), false)) {
			return true;
		}
		else {
			return false;
		}
	}
	bool scripted_game_event2(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		//Optimized

		const auto args = scripted_game_event->m_args;
		const auto hash = static_cast<int64_t>(args[0]);
		auto sender_id = static_cast<std::int32_t>(args[1]);



		for (auto& m_event : gameEvents) {
			if (m_event.hash == hash) {
				char notification[64];
				sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", player->get_name(), m_event.name.c_str());
				if (m_event.allow_from_friends) {
					int netHandle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(sender_id, netHandle, 13);
					if (NETWORK::NETWORK_IS_FRIEND(&netHandle[0])) {
						return false;
					}
				}
				if (m_event.log) {
					if (hash == (std::int64_t)eRemoteEvent::RemoteOffradar && is_in_car(Game->PlayerIndex(sender_id)))
					{
						//dont spam notifcation when in car
					}
					else {
						g_Logger->Info(notification);
					}

				}
				if (m_event.notify) {
					if (hash == (std::int64_t)eRemoteEvent::RemoteOffradar && is_in_car(Game->PlayerIndex(sender_id)))
					{
						//dont spam notifcation when in car
					}
					else {
						g_NotificationManager->add(notification, 2000, 0);
					}

				}
				if (m_event.block) {
					return true;
					break;
				}


			}
		}
		return false;

	}

	void scan_explosion_event(CNetGamePlayer* player, datBitBuffer2* buffer)
	{
		uint16_t f186;
		uint16_t f208;
		int ownerNetId;
		uint16_t f214;
		eExplosionTag explosionType;
		float damageScale;

		float posX;
		float posY;
		float posZ;

		bool f242;
		uint16_t f104;
		float cameraShake;

		bool isAudible;
		bool f189;
		bool isInvisible;
		bool f126;
		bool f241;
		bool f243;

		uint16_t f210;

		float unkX;
		float unkY;
		float unkZ;

		bool f190;
		bool f191;

		uint32_t f164;

		float posX224;
		float posY224;
		float posZ224;

		bool f240;
		uint16_t f218;
		bool f216;

		// clang-format off

		f186 = buffer->Read<uint16_t>(16);
		f208 = buffer->Read<uint16_t>(13);
		ownerNetId = buffer->Read<uint16_t>(13);
		f214 = buffer->Read<uint16_t>(13);               // 1604+
		explosionType = (eExplosionTag)buffer->ReadSigned<int>(8);// 1604+ bit size
		damageScale = buffer->Read<int>(8) / 255.0f;

		posX = buffer->ReadSignedFloat(22, 27648.0f);
		posY = buffer->ReadSignedFloat(22, 27648.0f);
		posZ = buffer->ReadFloat(22, 4416.0f) - 1700.0f;

		f242 = buffer->Read<uint8_t>(1);
		f104 = buffer->Read<uint16_t>(16);
		cameraShake = buffer->Read<int>(8) / 127.0f;

		isAudible = buffer->Read<uint8_t>(1);
		f189 = buffer->Read<uint8_t>(1);
		isInvisible = buffer->Read<uint8_t>(1);
		f126 = buffer->Read<uint8_t>(1);
		f241 = buffer->Read<uint8_t>(1);
		f243 = buffer->Read<uint8_t>(1);// 1604+

		f210 = buffer->Read<uint16_t>(13);

		unkX = buffer->ReadSignedFloat(16, 1.1f);
		unkY = buffer->ReadSignedFloat(16, 1.1f);
		unkZ = buffer->ReadSignedFloat(16, 1.1f);

		f190 = buffer->Read<uint8_t>(1);
		f191 = buffer->Read<uint8_t>(1);
		f164 = buffer->Read<uint32_t>(32);

		if (f242)
		{
			posX224 = buffer->ReadSignedFloat(31, 27648.0f);
			posY224 = buffer->ReadSignedFloat(31, 27648.0f);
			posZ224 = buffer->ReadFloat(31, 4416.0f) - 1700.0f;
		}
		else
		{
			posX224 = 0;
			posY224 = 0;
			posZ224 = 0;
		}

		auto f168 = buffer->Read<uint32_t>(32);// >= 1868: f_168


		f240 = buffer->Read<uint8_t>(1);
		if (f240)
		{
			f218 = buffer->Read<uint16_t>(16);

			if (f191)
			{
				f216 = buffer->Read<uint8_t>(8);
			}
		}

		buffer->Seek(0);

		auto object = g_GameFunctions->m_get_net_object(*g_GameFunctions->m_network_object_mgr, ownerNetId, true);
		auto entity = object ? object->GetGameObject() : nullptr;

		auto offset_object = g_GameFunctions->m_get_net_object(*g_GameFunctions->m_network_object_mgr, f210, true);

		if (f208 == 0 && entity && entity->m_entity_type == 4 && reinterpret_cast<CPed*>(entity)->m_player_info
			&& player->m_player_info->m_ped && player->m_player_info->m_ped->m_net_object
			&& ownerNetId != player->m_player_info->m_ped->m_net_object->m_object_id && !offset_object)
		{
			char notification[64];
			sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", reinterpret_cast<CPed*>(entity)->m_player_info->m_net_player_data.m_name, "Explosion");
			g_NotificationManager->add(notification, 2000, 0);
			return;
		}

		

		
	}
	void Hooks::NetworkEventHandler(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int buffer_size, datBitBuffer2* buffer)
	{
		if (event_id > 91u)
		{
			g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return;
		}

		const auto event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);
		if (event_name == nullptr || source_player == nullptr || source_player->m_player_id < 0 || source_player->m_player_id >= 32)
		{
			g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return;
		}

		switch (static_cast<eNetworkEvents>(event_id))
		{
		case eNetworkEvents::CKickVotesEvent:
		{
			std::uint32_t player_bitfield = buffer->Read<uint32_t>(32);
			if (player_bitfield & (1 << target_player->m_player_id))
			{

				char notification[64];
				sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Vote Kick");
				g_NotificationManager->add(notification, 2000, 0);
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CNetworkIncrementStatEvent2:
		{
			const auto increment_stat_event = std::make_unique<CNetworkIncrementStatEvent>();
			buffer->ReadDword(&increment_stat_event->m_stat, 0x20);
			buffer->ReadDword(&increment_stat_event->m_amount, 0x20);
			if (IncrementStatEvent(increment_stat_event.get(), source_player))
			{
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CAlterWantedLevelEvent:
		{
			int net_id = buffer->Read<int>(13);

			if (Game->CPed() && Game->CPed()->m_net_object && Game->CPed()->m_net_object->m_object_id == net_id)
			{
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				char notification[64];
				sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Wanted Level");
				g_NotificationManager->add(notification, 2000, 0);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CScriptEntityStateChangeEvent:
		{
			uint16_t entity = buffer->Read<uint16_t>(13);
			auto type = buffer->Read<ScriptEntityChangeType>(4);
			uint32_t unk = buffer->Read<uint32_t>(32);
			if (type == ScriptEntityChangeType::SettingOfTaskVehicleTempAction)
			{
				uint16_t ped_id = buffer->Read<uint16_t>(13);
				uint32_t action = buffer->Read<uint32_t>(8);

				if ((action >= 15 && action <= 18) || action == 33)
				{
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Crash (Vehicle Temp)");
					g_NotificationManager->add(notification, 2000, 0);
					return;
				}
			}
			else if (type > ScriptEntityChangeType::SetVehicleExclusiveDriver || type < ScriptEntityChangeType::BlockingOfNonTemporaryEvents)
			{
				char notification[64];
				sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Crash (Entity Change)");
				g_NotificationManager->add(notification, 2000, 0);
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CScriptedGameEvent:
		{
			const auto scripted_game_event = std::make_unique<CScriptedGameEvent>();
			buffer->ReadDword(&scripted_game_event->m_args_size, 32);
			if (scripted_game_event->m_args_size - 1 <= 0x1AF)
				buffer->ReadArray(&scripted_game_event->m_args, 8 * scripted_game_event->m_args_size);

			if (scripted_game_event2(scripted_game_event.get(), source_player))
			{
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return;
			}
			buffer->Seek(0);

			break;
		}
		case eNetworkEvents::CNetworkClearPedTasksEvent:
		{
			int net_id = buffer->Read<int>(13);

			if (Game->CPed() && Game->CPed()->m_net_object && Game->CPed()->m_net_object->m_object_id == net_id)
			{
				if (protections.GameEvents.freeze) {
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Freeze");
					g_NotificationManager->add(notification, 2000, 0);
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CRagdollRequestEvent:
		{
			int net_id = buffer->Read<int>(13);

			if (Game->CPed() && Game->CPed()->m_net_object && Game->CPed()->m_net_object->m_object_id == net_id)
			{
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				char notification[64];
				sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Ragdoll");
				g_NotificationManager->add(notification, 2000, 0);
				return;
			}

			buffer->Seek(0);
			break;
		}
		
		case eNetworkEvents::CRequestControlEvent:
		{
			int net_id = buffer->Read<int>(13);
			if (Game->CPed() && Game->CPed()->m_vehicle && Game->CPed()->m_vehicle->m_net_object
				&& Game->CPed()->m_vehicle->m_net_object->m_object_id == net_id && Game->CPed()->m_vehicle->m_driver == Game->CPed())
			{
				if (protections.GameEvents.request_control) {
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Request Control");
					g_NotificationManager->add(notification, 2000, 0);
					return;
				}
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CScriptWorldStateEvent:
		{
			auto type = buffer->Read<WorldStateDataType>(4);
			buffer->Read<bool>(1);
			CGameScriptId id;
			script_id_deserialize(id, *buffer);

			if (type == WorldStateDataType::Rope)
			{
				buffer->Read<int>(9);    
				buffer->Read<float>(19); 
				buffer->Read<float>(19); 
				buffer->Read<float>(19); 
				buffer->Read<float>(19); 
				buffer->Read<float>(19); 
				buffer->Read<float>(19);
				buffer->Read<float>(16);
				int type = buffer->Read<int>(4);
				float initial_length = buffer->Read<float>(16);
				float min_length = buffer->Read<float>(16);

				if (type == 0 || initial_length < min_length)
				{
					// most definitely a crash
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Crash (Rope)");
					g_NotificationManager->add(notification, 2000, 0);
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}
			else if (type == WorldStateDataType::PopGroupOverride)
			{
				int pop_schedule = buffer->ReadSigned<int>(8); 
				int pop_group = buffer->Read<int>(32); 
				int percentage = buffer->Read<int>(7); 

				if (pop_group == 0 && (percentage == 0 || percentage == 103))
				{
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Crash (Pop Group)");
					g_NotificationManager->add(notification, 2000, 0);
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}
			else if (type > WorldStateDataType::VehiclePlayerLocking || type < WorldStateDataType::CarGen)
			{
				char notification[64];
				sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Crash (World State)");
				g_NotificationManager->add(notification, 2000, 0);
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CRemoveWeaponEvent:
		{
			int net_id = buffer->Read<int>(13);
			uint32_t hash = buffer->Read<uint32_t>(32);

			if (hash == rage::joaat("WEAPON_UNARMED"))
			{
				if (protections.Crashes.weapon) {
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Weapon Crash");
					g_NotificationManager->add(notification, 2000, 0);
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			if (Game->CPed() && Game->CPed()->m_net_object && Game->CPed()->m_net_object->m_object_id == net_id)
			{
				if (protections.GameEvents.remove_weapon) {
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Remove Weapon");
					g_NotificationManager->add(notification, 2000, 0);
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CRemoveAllWeaponsEvent:
		{
			int net_id = buffer->Read<int>(13);

			if (Game->CPed() && Game->CPed()->m_net_object && Game->CPed()->m_net_object->m_object_id == net_id)
			{
				if (protections.GameEvents.remove_all_weapons) {
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Remove All Weapons");
					g_NotificationManager->add(notification, 2000, 0);
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CGiveControlEvent:
		{
			uint32_t timestamp = buffer->Read<uint32_t>(32);
			int count = buffer->Read<int>(2);
			bool all_objects_migrate_together = buffer->Read<bool>(1);

			if (count > 3)
			{
				count = 3;
			}

			for (int i = 0; i < count; i++)
			{
				int net_id = buffer->Read<int>(13);
				eNetObjType object_type = buffer->Read<eNetObjType>(4);
				int migration_type = buffer->Read<int>(3);

				if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
				{
					
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Give Control");
					g_NotificationManager->add(notification, 2000, 0);
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			m_syncing_player = source_player;
			break;
		}
		case eNetworkEvents::CNetworkPlaySoundEvent:
		{
			
			
			bool is_entity = buffer->Read<bool>(1);
			std::int16_t entity_net_id;
			rage::fvector3 position;
			std::uint32_t ref_hash;

			if (is_entity)
				entity_net_id = buffer->Read<std::int16_t>(13);
			else
			{
				position.x = buffer->ReadSignedFloat(19, 1337.0f);
				position.y = buffer->ReadSignedFloat(19, 1337.0f);
				position.z = buffer->ReadFloat(19, 1337.0f);
			}

			bool has_ref = buffer->Read<bool>(1);
			if (has_ref)
				ref_hash = buffer->Read<std::uint32_t>(32);

			std::uint32_t sound_hash = buffer->Read<std::uint32_t>(32);

			if (sound_hash == rage::joaat("Remote_Ring"))
			{
				if (protections.GameEvents.play_sound) {
					char notification[64];
					sprintf(notification, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", source_player->get_name(), "Sound Spam");
					g_NotificationManager->add(notification, 2000, 0);
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::CExplosionEvent:
		{
			scan_explosion_event(source_player, buffer);
			break;
		}
		
		default: break;
		}

		return static_cast<decltype(&NetworkEventHandler)>(g_Hooking->m_OriginalNetworkHandler)(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, buffer_size, buffer);
	}

	
	//crash protection
	bool Hooks::fragment_physics_crash(uintptr_t a1, uint32_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5)
	{
		if (protections.Crashes.fragment) {
			if (auto ptr = *reinterpret_cast<uintptr_t*>(a5 + 0x70); ptr)
				if (auto ptr2 = *reinterpret_cast<uintptr_t*>(ptr + 8 * a2); !ptr2) {
					protections.push_notification2(ICON_FA_SHIELD_ALT"  Prevented Crash | Fragment");
					return false;
				}
		}
		return static_cast<decltype(&fragment_physics_crash)>(g_Hooking->m_OriginalFragmentCrash)(a1, a2, a3, a4, a5);
	}
	std::int64_t Hooks::constraint_attachment_crash(std::uintptr_t a1)
	{
		if (protections.Crashes.train) {
			if (!*reinterpret_cast<void**>(a1 + 0x38)) {
				protections.push_notification2(ICON_FA_SHIELD_ALT"  Prevented Crash | Train");
				return 0;
			}
		}
		return static_cast<decltype(&constraint_attachment_crash)>(g_Hooking->AttachmentCrash)(a1);
	}
	bool Hooks::received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp)
	{
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
		{
			if (protections.Crashes.entity) {
				protections.push_notification2(ICON_FA_SHIELD_ALT"  Prevented crash | Entity");
				return true;
			}
		}

		m_syncing_player = src;
		return static_cast<decltype(&received_clone_create)>(g_Hooking->InvalidObjectCrash2)(mgr, src, dst, object_type, object_id, object_flag, buffer, timestamp);
	}
	eAckCode Hooks::received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, datBitBuffer2* buffer, uint16_t unk, uint32_t timestamp)
	{
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
		{
			if (protections.Crashes.object) {
				protections.push_notification2(ICON_FA_SHIELD_ALT"  Prevented crash | Object");
				return eAckCode::ACKCODE_FAIL;
			}
		}

		if (auto net_obj = g_GameFunctions->m_get_net_object(mgr, object_id, true); net_obj && net_obj->m_object_type != (int16_t)object_type)
		{
			if (protections.Crashes.object) {
				protections.push_notification2(ICON_FA_SHIELD_ALT"  Prevented crash | Object");
				return eAckCode::ACKCODE_FAIL;
			}
		}/*
		int64_t fortnite = buffer->ReadInt64((int64_t*)0x94828921, 64);
		int64_t fn = buffer->ReadInt64((int64_t*)0x784, 1);
		if (buffer->ReadArray(nullptr, 0) && fortnite && fn) {
			protections.push_notification2(ICON_FA_SHIELD_ALT"  Prevented crash | Sync Fuzzer");
			return eAckCode::ACKCODE_FAIL;
		}*/
		m_syncing_player = src;
		return static_cast<decltype(&received_clone_sync)>(g_Hooking->InvalidObjectCrash)(mgr, src, dst, object_type, object_id, buffer, unk, timestamp);
	}
	bool Hooks::fragment_physics_crash_2(float* a1, float* a2)
	{
		if (protections.Crashes.fragment) {
			if (!a1 || !a2) {
				protections.push_notification2(ICON_FA_SHIELD_ALT"  Prevented Crash | Fragment");
				return false;
			}
		}

		return static_cast<decltype(&fragment_physics_crash_2)>(g_Hooking->m_OriginalFragmentCrash2)(a1, a2);
	}
	
	
	bool Hooks::object_creation_data_node(CObjectCreationDataNode* node, rage::netObject* obj)
	{
		auto result = static_cast<decltype(&object_creation_data_node)>(g_Hooking->m_OriginalInvalidPlayer222)(node, obj);

		if (protections.Crashes.object) {

			if (Lists::crash_model_check(node->m_model)) {
				protections.push_notification2(ICON_FA_SHIELD_ALT"  Prevented crash | Object");
				return true;
			}

		}
	
		return result;
	}
	//normal
	void Hooks::invalid_player_crash(uint64_t a1, uint64_t a2)
	{
		if (protections.Crashes.player) {
			uint64_t v6;
			uint64_t* v8;

			v6 = 0i64;

			v8 = *(uint64_t**)(a1 + 0x50);

			if (!is_valid_ptr(v8)) {
				protections.push_notification(ICON_FA_SHIELD_ALT"  Prevented Crash | Player");
				return;
			}

			
		}

		return static_cast<decltype(&invalid_player_crash)>(g_Hooking->m_OriginalInvalidPlayer)(a1, a2);
	}
	bool Hooks::hk_ped_creation_data_node(CPedCreationDataNode* node)
	{

		auto result = static_cast<decltype(&hk_ped_creation_data_node)>(g_Hooking->ped_creation)(node);
		if (protections.Crashes.ped) {
			if (Lists::crash_model_check(node->m_model) || Lists::crash_model_check(node->m_prop_model)) {
				protections.push_notification(ICON_FA_SHIELD_ALT"  Prevented crash | Ped");
				return true;
			}
		}



		return result;
	}
	bool Hooks::hk_vehicle_creation_data_node(CVehicleCreationDataNode* node)
	{
		auto result = static_cast<decltype(&hk_vehicle_creation_data_node)>(g_Hooking->vehicle_creation)(node);

		if (!result)
			return result;
		if (protections.Crashes.vehicle) {
			if (Lists::crash_model_check(node->m_model)) {
				protections.push_notification(ICON_FA_SHIELD_ALT"  Prevented crash | Vehicle");
				return false;
			}
		}



		return result;
	}
	namespace am_hunt_the_beast
	{
		constexpr static auto broadcast_idx = 599;
		constexpr static auto player_broadcast_idx = 2583;
	}
	bool Hooks::received_array_update(rage::netArrayHandlerBase* array, CNetGamePlayer* sender, rage::datBitBuffer* buffer, int size, std::int16_t cycle) {
		static script_global gsbd(2648605);
		auto result = static_cast<decltype(&received_array_update)>(g_Hooking->array_update)(array, sender, buffer, size, cycle);
		int old_beast_index = -1;
		int participant_id = 0;
		auto beast = find_script_thread(rage::joaat("am_hunt_the_beast"));
		if (array->m_array == gsbd.as<void*>() && *gsbd.as<eFreemodeState*>() == eFreemodeState::CLOSING)
		{
			*gsbd.as<eFreemodeState*>() = eFreemodeState::RUNNING;
			char g_RemoveWeapons[64];
			sprintf(g_RemoveWeapons, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", sender->m_player_info->m_net_player_data.m_name, "Kick");
			g_NotificationManager->add(g_RemoveWeapons, 2000, 0);
			return false;
		}
		if (beast && array->m_array == script_local(beast->m_stack, am_hunt_the_beast::broadcast_idx).as<void*>()
			&& old_beast_index
			!= *script_local(beast->m_stack, am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>()
			&& *script_local(beast->m_stack, am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>() == participant_id
			&& !m_GetBits.has_bit_set(script_local(beast->m_stack, am_hunt_the_beast::player_broadcast_idx)
				.at(participant_id, 4)
				.at(3)
				.as<int*>(),
				1))
		{
			*script_local(beast->m_stack, am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>() = -1;
			*script_local(beast->m_stack, am_hunt_the_beast::broadcast_idx).at(1).at(7).as<Player*>() = -1;

			char g_RemoveWeapons[64];
			sprintf(g_RemoveWeapons, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", sender->m_player_info->m_net_player_data.m_name, "Turn Into Beast");
			g_NotificationManager->add(g_RemoveWeapons, 2000, 0);
		}




		return result;
	}
	uint64_t Hooks::task_parachute_object_0x270(uint64_t _this, int a2, int a3)
	{
		if (a2 == 1 && a3 == 1)
		{
			if (auto ptr = *(uint64_t*)(_this + 16))
				if (auto ptr2 = *(uint64_t*)(ptr + 80))
					if (auto ptr3 = *(uint64_t*)(ptr2 + 64))
						return static_cast<decltype(&task_parachute_object_0x270)>(g_Hooking->parachute)(_this, a2, a3);
			return 0;
		}
		return static_cast<decltype(&task_parachute_object_0x270)>(g_Hooking->parachute)(_this, a2, a3);
	}
	void Hooks::serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer)
	{
		static_cast<decltype(&serialize_take_off_ped_variation_task)>(g_Hooking->parachute2)(info, serializer);
		if (info->m_prop_hash != 0 && info->m_variation_component == 5 && info->m_prop_hash != rage::joaat("p_parachute_s"))
		{
			// thanks yim (its open source so dont call me a skid)
			info->m_prop_hash = 0;
		}
	}
	template<typename T>
	constexpr void SetBit(T* value, T bit)
	{
		*value |= (1 << bit);
	}

	template<typename T, typename ...T2>
	constexpr void SetBits(T* value, T2... bit)
	{
		(SetBit<T>(value, std::forward<T>(bit)), ...);
	}
	std::uint64_t* Hooks::FallTaskConstructor(std::uint64_t* _this, std::uint32_t flags)
	{
		if (BeastLanding)
			SetBits<std::uint32_t>(&flags, 10, 11, 12, 16);
		return static_cast<decltype(&FallTaskConstructor)>(g_Hooking->m_OriginalFallTaskConstructor)(_this, flags);
	}
	void Hooks::serialize_vehicle_gadget_data_node(CVehicleGadgetDataNode* node, rage::CSyncDataBase* data)
	{
		data->SerializeBool(&node->m_has_parent_offset);
		if (node->m_has_parent_offset || data->IsSizeCalculator())
		{
			data->SerializeSignedFloat((float*)&node->m_parent_offset_x, 24.0f, 14);
			data->SerializeSignedFloat((float*)&node->m_parent_offset_y, 24.0f, 14);
			data->SerializeSignedFloat((float*)&node->m_parent_offset_z, 24.0f, 14);
		}
		else
		{
			node->m_parent_offset_x = 0;
			node->m_parent_offset_y = 0;
			node->m_parent_offset_z = 0;
			node->m_parent_offset_w = 0;
		}

		data->SerializeDwordAlt(&node->m_gadget_count, 2);

		if (data->IsSizeCalculator())
			node->m_gadget_count = 2;

		if (node->m_gadget_count > 2)
		{

			return;
		}

		for (uint32_t i = 0; i < node->m_gadget_count; i++)
		{
			data->SerializeDwordAlt((uint32_t*)&node->m_gadget_data[i].m_gadget_type, 3);

			int size;
			if (data->IsSizeCalculator())
				size = 94;
			else
				size = g_GameFunctions->m_get_vehicle_gadget_array_size(node->m_gadget_data[i].m_gadget_type);

			data->SerializeArray(&node->m_gadget_data[i].m_data, size);
		}
	}
	

	static auto nodes = std::to_array<std::pair<Hash, uint64_t>>({ {rage::joaat("CAutomobileCreationDataNode"), 0}, {rage::joaat("CBikeGameStateDataNode"), 0}, {rage::joaat("CBoatGameStateDataNode"), 0}, {rage::joaat("CDoorCreationDataNode"), 0}, {rage::joaat("CDoorMovementDataNode"), 0}, {rage::joaat("CDoorScriptGameStateDataNode"), 0}, {rage::joaat("CDoorScriptInfoDataNode"), 0}, {rage::joaat("CDynamicEntityGameStateDataNode"), 0}, {rage::joaat("CEntityOrientationDataNode"), 0}, {rage::joaat("CEntityScriptGameStateDataNode"), 0}, {rage::joaat("CEntityScriptInfoDataNode"), 0}, {rage::joaat("CGlobalFlagsDataNode"), 0}, {rage::joaat("CHeliControlDataNode"), 0}, {rage::joaat("CHeliHealthDataNode"), 0}, {rage::joaat("CMigrationDataNode"), 0}, {rage::joaat("CObjectCreationDataNode"), 0}, {rage::joaat("CObjectGameStateDataNode"), 0}, {rage::joaat("CObjectOrientationNode"), 0}, {rage::joaat("CObjectScriptGameStateDataNode"), 0}, {rage::joaat("CObjectSectorPosNode"), 0}, {rage::joaat("CPedAIDataNode"), 0}, {rage::joaat("CPedAppearanceDataNode"), 0}, {rage::joaat("CPedAttachDataNode"), 0}, {rage::joaat("CPedComponentReservationDataNode"), 0}, {rage::joaat("CPedCreationDataNode"), 0}, {rage::joaat("CPedGameStateDataNode"), 0}, {rage::joaat("CPedHealthDataNode"), 0}, {rage::joaat("CPedInventoryDataNode"), 0}, {rage::joaat("CPedMovementDataNode"), 0}, {rage::joaat("CPedMovementGroupDataNode"), 0}, {rage::joaat("CPedOrientationDataNode"), 0}, {rage::joaat("CPedScriptCreationDataNode"), 0}, {rage::joaat("CPedScriptGameStateDataNode"), 0}, {rage::joaat("CPedSectorPosMapNode"), 0}, {rage::joaat("CPedSectorPosNavMeshNode"), 0}, {rage::joaat("CPedTaskSequenceDataNode"), 0}, {rage::joaat("CPedTaskSpecificDataNode"), 0}, {rage::joaat("CPedTaskTreeDataNode"), 0}, {rage::joaat("CPhysicalAngVelocityDataNode"), 0}, {rage::joaat("CPhysicalAttachDataNode"), 0}, {rage::joaat("CPhysicalGameStateDataNode"), 0}, {rage::joaat("CPhysicalHealthDataNode"), 0}, {rage::joaat("CPhysicalMigrationDataNode"), 0}, {rage::joaat("CPhysicalScriptGameStateDataNode"), 0}, {rage::joaat("CPhysicalScriptMigrationDataNode"), 0}, {rage::joaat("CPhysicalVelocityDataNode"), 0}, {rage::joaat("CPickupCreationDataNode"), 0}, {rage::joaat("CPickupPlacementCreationDataNode"), 0}, {rage::joaat("CPickupPlacementStateDataNode"), 0}, {rage::joaat("CPickupScriptGameStateNode"), 0}, {rage::joaat("CPickupSectorPosNode"), 0}, {rage::joaat("CPlaneControlDataNode"), 0}, {rage::joaat("CPlaneGameStateDataNode"), 0}, {rage::joaat("CPlayerAmbientModelStreamingNode"), 0}, {rage::joaat("CPlayerAppearanceDataNode"), 0}, {rage::joaat("CPlayerCameraDataNode"), 0}, {rage::joaat("CPlayerCreationDataNode"), 0}, {rage::joaat("CPlayerExtendedGameStateNode"), 0}, {rage::joaat("CPlayerGameStateDataNode"), 0}, {rage::joaat("CPlayerGamerDataNode"), 0}, {rage::joaat("CPlayerPedGroupDataNode"), 0}, {rage::joaat("CPlayerSectorPosNode"), 0}, {rage::joaat("CPlayerWantedAndLOSDataNode"), 0}, {rage::joaat("CSectorDataNode"), 0}, {rage::joaat("CSectorPositionDataNode"), 0}, {rage::joaat("CSubmarineControlDataNode"), 0}, {rage::joaat("CSubmarineGameStateDataNode"), 0}, {rage::joaat("CTrainGameStateDataNode"), 0}, {rage::joaat("CVehicleAngVelocityDataNode"), 0}, {rage::joaat("CVehicleAppearanceDataNode"), 0}, {rage::joaat("CVehicleComponentReservationDataNode"), 0}, {rage::joaat("CVehicleControlDataNode"), 0}, {rage::joaat("CVehicleCreationDataNode"), 0}, {rage::joaat("CVehicleDamageStatusDataNode"), 0}, {rage::joaat("CVehicleGadgetDataNode"), 0}, {rage::joaat("CVehicleGameStateDataNode"), 0}, {rage::joaat("CVehicleHealthDataNode"), 0}, {rage::joaat("CVehicleProximityMigrationDataNode"), 0}, {rage::joaat("CVehicleScriptGameStateDataNode"), 0}, {rage::joaat("CVehicleSteeringDataNode"), 0}, {rage::joaat("CVehicleTaskDataNode"), 0} });
	static void cache_nodes()
	{
		for (int i = (int)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; i <= (int)eNetObjType::NET_OBJ_TYPE_TRAIN; i++)
		{
			if (i == (int)eNetObjType::NET_OBJ_TYPE_TRAILER)
				continue;
			rage::netSyncTree* tree = g_GameFunctions->m_get_sync_tree_for_type(*g_GameFunctions->m_network_object_mgr, i);
			if (tree->m_child_node_count > trees[i].second.size())
			{
				//LOG(FATAL) << "Cache nodes failed " << i << tree->m_child_node_count << " " << trees[i].second.size();
				throw std::runtime_error("Failed to cache nodes");
			}
			for (int j = 0; j < tree->m_child_node_count; j++)
			{
				PVOID vft = *(PVOID*)tree->m_child_nodes[j];
				for (auto& n : nodes)
				{
					if (n.first == trees[i].second[j])
					{
						n.second = (uint64_t)vft;
						break;
					}
				}
			}
		}
	}
	inline CObject* get_game_object(rage::netObject* object)
	{
		return *(CObject**)((__int64)object + 0x50);
	}
	inline bool is_attachment_infinite(rage::CDynamicEntity* object, uint16_t attached_to_net_id)
	{
		if (object == nullptr)
			return false;

		constexpr size_t reasonable_limit = 150;
		size_t i = 0;
		while (object && i < reasonable_limit)
		{
			if (object->m_net_object && object->m_net_object->m_object_id == attached_to_net_id)
				return true;

			object = g_GameFunctions->m_get_entity_attached_to(object);
			i++;
		}

		return false;
	}
	

	template<typename T = CBaseModelInfo*>
	static T get_model(const rage::joaat_t hash)
	{
		const auto model_table = g_GameFunctions->m_model_table;
		for (auto i = model_table->m_lookup_table[hash % model_table->m_lookup_key]; i; i = i->m_next)
		{
			if (i->m_hash == hash)
			{
				if (const auto model = model_table->m_data[i->m_idx]; model)
				{
					return reinterpret_cast<T>(model);
				}
			}
		}
		return nullptr;
	}
	template<typename T, typename... Args>
	static bool is_model_of_type(const rage::joaat_t hash, const T arg, const Args... args)
	{
		bool of_type = false;
		if (const auto model = get_model(hash))
		{
			of_type = model->m_model_type == arg;
			(
				[&of_type, &model](eModelType type) {
					of_type |= model->m_model_type == type;
				}(args),
					...);
		}
		return of_type;
	}
	
	bool is_in_vehicle(CPed* ped, CVehicle* vehicle)
	{
		if (!ped || !vehicle)
			return false;

		if (ped == vehicle->m_driver)
			return true;

		for (int i = 0; i < 15; i++)
			if (vehicle->m_passengers[i] == ped)
				return true;

		return false;
	}
	constexpr uint32_t crash_peds[] = { rage::joaat("slod_human"), rage::joaat("slod_small_quadped"), rage::joaat("slod_large_quadped") };

	constexpr uint32_t crash_vehicles[] = { rage::joaat("arbitergt"), rage::joaat("astron2"), rage::joaat("cyclone2"), rage::joaat("ignus2"), rage::joaat("s95") };

	constexpr uint32_t crash_objects[] = { rage::joaat("prop_dummy_01"), rage::joaat("prop_dummy_car"), rage::joaat("prop_dummy_light"), rage::joaat("prop_dummy_plane"), rage::joaat("prop_distantcar_night"), rage::joaat("prop_distantcar_day"), rage::joaat("hei_bh1_08_details4_em_night"), rage::joaat("dt1_18_sq_night_slod"), rage::joaat("ss1_12_night_slod"), -1288391198, rage::joaat("h4_prop_bush_bgnvla_med_01"), rage::joaat("h4_prop_bush_bgnvla_lrg_01"), rage::joaat("h4_prop_bush_buddleia_low_01"), rage::joaat("h4_prop_bush_ear_aa"), rage::joaat("h4_prop_bush_ear_ab"), rage::joaat("h4_prop_bush_fern_low_01"), rage::joaat("h4_prop_bush_fern_tall_cc"), rage::joaat("h4_prop_bush_mang_ad"), rage::joaat("h4_prop_bush_mang_low_aa"), rage::joaat("h4_prop_bush_mang_low_ab"), rage::joaat("h4_prop_bush_seagrape_low_01"), rage::joaat("prop_h4_ground_cover"), rage::joaat("h4_prop_weed_groundcover_01"), rage::joaat("h4_prop_grass_med_01"), rage::joaat("h4_prop_grass_tropical_lush_01"), rage::joaat("h4_prop_grass_wiregrass_01"), rage::joaat("h4_prop_weed_01_plant"), rage::joaat("h4_prop_weed_01_row"), rage::joaat("urbanweeds02_l1"), rage::joaat("proc_forest_grass01"), rage::joaat("prop_small_bushyba"), rage::joaat("v_res_d_dildo_a"), rage::joaat("v_res_d_dildo_b"), rage::joaat("v_res_d_dildo_c"), rage::joaat("v_res_d_dildo_d"), rage::joaat("v_res_d_dildo_e"), rage::joaat("v_res_d_dildo_f"), rage::joaat("v_res_skateboard"), rage::joaat("prop_battery_01"), rage::joaat("prop_barbell_01"), rage::joaat("prop_barbell_02"), rage::joaat("prop_bandsaw_01"), rage::joaat("prop_bbq_3"), rage::joaat("v_med_curtainsnewcloth2"), rage::joaat("bh1_07_flagpoles"), 92962485 };

	

	inline bool is_crash_ped(uint32_t model)
	{
		if (!is_model_of_type(model, eModelType::Ped, eModelType::OnlineOnlyPed))
			return true;
		for (auto iterator : crash_peds)
			if (iterator == model)
				return true;
		return false;
	}

	inline bool is_crash_vehicle(uint32_t model)
	{
		if (!is_model_of_type(model, eModelType::Vehicle, eModelType::Unk133))
			return true;
		for (auto iterator : crash_vehicles)
			if (iterator == model)
				return true;
		return false;
	}

	inline bool is_crash_object(uint32_t model)
	{
		if (!is_model_of_type(model, eModelType::Object, eModelType::Time, eModelType::Weapon, eModelType::Destructable, eModelType::WorldObject, eModelType::Sprinkler, eModelType::Unk65, eModelType::Plant, eModelType::LOD, eModelType::Unk132, eModelType::Building))
			return true;
		for (auto iterator : crash_objects)
			if (iterator == model)
				return true;
		return false;
	}
	bool check_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, rage::netObject* object)
	{
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
				if (check_node(child, sender, object))
					return true;
			}
		}
		else if (node->IsDataNode())
		{
			auto vtable = *(void**)node;
			Hash node_hash = 0;

			for (const auto& n : nodes)
			{
				if ((void*)n.second == vtable)
				{
					node_hash = n.first;
					break;
				}
			}

			switch (node_hash) {
			case rage::joaat("CPedAttachDataNode"):
			{
				const auto attach_node = (CPedAttachDataNode*)(node);
				if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id)
				{
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", sender->m_player_info->m_net_player_data.m_name, "Crash (Bro Hug)");
					g_NotificationManager->add(g_RemoveWeapons, 2000, 0);
					return true;
				}
				else if (attach_node->m_attached && is_attachment_infinite(get_game_object(object), attach_node->m_attached_to))
				{
					return true;
				}

				break;
			}
			
			
			
			case rage::joaat("CVehicleProximityMigrationDataNode"):
			{
				if (object && Game->CPed() && Game->CPed()->m_net_object)
				{
					const auto migration_node = (CVehicleProximityMigrationDataNode*)(node);
					if (is_in_vehicle(Game->CPed(), Game->CPed()->m_vehicle) && Game->CPed()->m_vehicle->m_net_object
						&& Game->CPed()->m_vehicle->m_net_object->m_object_id == object->m_object_id) {
						char g_RemoveWeapons[64];
						sprintf(g_RemoveWeapons, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", sender->m_player_info->m_net_player_data.m_name, "Vehicle Kick 2");
						g_NotificationManager->add(g_RemoveWeapons, 2000, 0);
						return false; // vehicle kick?
					}

					if (!Game->CPed()->m_vehicle || !Game->CPed()->m_vehicle->m_net_object
						|| Game->CPed()->m_vehicle->m_net_object->m_object_id != object->m_object_id
						|| !is_in_vehicle(Game->CPed(), Game->CPed()->m_vehicle))
					{
						for (int i = 0; i < 16; i++)
						{
							if (migration_node->m_has_occupants[i] && migration_node->m_occupants[i] == Game->CPed()->m_net_object->m_object_id) {
								char g_RemoveWeapons[64];
								sprintf(g_RemoveWeapons, ICON_FA_SHIELD_ALT"  %s tried to send the event '%s'", sender->m_player_info->m_net_player_data.m_name, "Vehicle Migration");
								g_NotificationManager->add(g_RemoveWeapons, 2000, 0);
								return true;
							}
						}
					}
				}

				break;
			}
			}
		}
		return false;
	}
	bool Hooks::can_apply_data(rage::netSyncTree* tree, rage::netObject* object)
	{
		static bool init = ([] { cache_nodes(); }(), true);

		if (tree->m_child_node_count && check_node(tree->m_next_sync_node, m_syncing_player, object))
		{
			return false;
		}

		return static_cast<decltype(&can_apply_data)>(g_Hooking->can_applydata)(tree, object);
	}
	Hooking::Hooking() :
		m_D3DHook(g_GameVariables->m_Swapchain, 18)
	{

		MH_Initialize();
		MH_CreateHook(g_GameFunctions->m_GetLabelText, &Hooks::GetLabelText, &m_OriginalGetLabelText);
		MH_CreateHook(g_GameFunctions->m_WndProc, &Hooks::WndProc, &m_OriginalWndProc);

		MH_CreateHook(g_GameFunctions->m_write_player_game_state_data_node, &Hooks::write_player_game_state_data_node, &m_Original_write_player_game_state_data_node);
		MH_CreateHook(g_GameFunctions->m_write_player_gamer_data_node, &Hooks::write_player_gamer_data_node, &m_Original_write_player_gamer_data_node);
		MH_CreateHook(g_GameFunctions->m_SendNetInfo, &Hooks::SendNetInfo, &m_OriginalSendNetInfo);
		MH_CreateHook(g_GameFunctions->m_send_chat_message, &Hooks::send_chat_message, &m_OriginalChatSend);
		MH_CreateHook(g_GameFunctions->m_AssignPhysicalIndexHandler, &Hooks::AssignNewPhysicalIndexHandler, &m_OriginalAssignPhysicalIndex);
		MH_CreateHook(g_GameFunctions->crashProtection, &Hooks::InvalidModsCrashPatch, &m_OriginalModCrash);

		MH_CreateHook(g_GameFunctions->m_NetworkEvents, &Hooks::NetworkEventHandler, &m_OriginalNetworkHandler);
		//crashes
		MH_CreateHook(g_GameFunctions->m_fragment_physics_crash, &Hooks::fragment_physics_crash, &m_OriginalFragmentCrash);
		MH_CreateHook(g_GameFunctions->m_fragment_physics_crash_2, &Hooks::fragment_physics_crash_2, &m_OriginalFragmentCrash2);
		MH_CreateHook(g_GameFunctions->m_received_clone_sync, &Hooks::received_clone_sync, &InvalidObjectCrash);
		MH_CreateHook(g_GameFunctions->m_received_clone_create, &Hooks::received_clone_create, &InvalidObjectCrash2);
		MH_CreateHook(g_GameFunctions->m_constraint_attachment_crash, &Hooks::constraint_attachment_crash, &AttachmentCrash);
		MH_CreateHook(g_GameFunctions->m_object_creation_data_node, &Hooks::object_creation_data_node, &m_OriginalInvalidPlayer222);
		MH_CreateHook(g_GameFunctions->m_invalid_player_crash_patch, &Hooks::invalid_player_crash, &m_OriginalInvalidPlayer);
		MH_CreateHook(g_GameFunctions->m_ped_creation_data_node, &Hooks::hk_ped_creation_data_node, &ped_creation);
		MH_CreateHook(g_GameFunctions->m_vehicle_creation_data_node, &Hooks::hk_vehicle_creation_data_node, &vehicle_creation);
		MH_CreateHook(g_GameFunctions->m_received_array_update, &Hooks::received_array_update, &array_update);
		MH_CreateHook(g_GameFunctions->m_task_parachute_object_0x270, &Hooks::task_parachute_object_0x270, &parachute);
		MH_CreateHook(g_GameFunctions->m_serialize_take_off_ped_variation_task, &Hooks::serialize_take_off_ped_variation_task, &parachute2);
		MH_CreateHook(g_GameFunctions->m_serialize_vehicle_gadget_data_node, &Hooks::serialize_vehicle_gadget_data_node, &yim_crash);
		MH_CreateHook(g_GameFunctions->m_can_apply_data, &Hooks::can_apply_data, &can_applydata);
		m_D3DHook.Hook(&Hooks::Present, Hooks::PresentIndex);
		m_D3DHook.Hook(&Hooks::ResizeBuffers, Hooks::ResizeBuffersIndex);
	}

	Hooking::~Hooking() noexcept
	{

		MH_RemoveHook(g_GameFunctions->m_GetLabelText);
		MH_RemoveHook(g_GameFunctions->m_WndProc);
		MH_RemoveHook(g_GameFunctions->m_write_player_game_state_data_node);
		MH_RemoveHook(g_GameFunctions->m_write_player_gamer_data_node);
		MH_RemoveHook(g_GameFunctions->m_SendNetInfo);
		MH_RemoveHook(g_GameFunctions->m_send_chat_message);
		MH_RemoveHook(g_GameFunctions->m_AssignPhysicalIndexHandler);
		MH_RemoveHook(g_GameFunctions->crashProtection);
		MH_RemoveHook(g_GameFunctions->m_NetworkEvents);
		MH_RemoveHook(g_GameFunctions->m_fragment_physics_crash);
		MH_RemoveHook(g_GameFunctions->m_fragment_physics_crash_2);
		MH_RemoveHook(g_GameFunctions->m_received_clone_sync);
		MH_RemoveHook(g_GameFunctions->m_received_clone_create);
		MH_RemoveHook(g_GameFunctions->m_constraint_attachment_crash);
		MH_RemoveHook(g_GameFunctions->m_object_creation_data_node);
		MH_RemoveHook(g_GameFunctions->m_invalid_player_crash_patch);
		MH_RemoveHook(g_GameFunctions->m_ped_creation_data_node);
		MH_RemoveHook(g_GameFunctions->m_vehicle_creation_data_node);
		MH_RemoveHook(g_GameFunctions->m_received_array_update);
		MH_RemoveHook(g_GameFunctions->m_task_parachute_object_0x270);
		MH_RemoveHook(g_GameFunctions->m_serialize_take_off_ped_variation_task);
		MH_RemoveHook(g_GameFunctions->m_serialize_vehicle_gadget_data_node);
		MH_RemoveHook(g_GameFunctions->m_can_apply_data);
		MH_Uninitialize();
	}

	void Hooking::Hook()
	{
		m_D3DHook.Enable();
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void Hooking::Unhook()
	{
		m_D3DHook.Disable();
		MH_DisableHook(MH_ALL_HOOKS);
	}
	}

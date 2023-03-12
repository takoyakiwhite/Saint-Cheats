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
			g_GameFunctions->m_join_session_by_info(*g_GameFunctions->m_network, &g_Session_info, 1, 1 | 2, nullptr, 0);
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

	int Hooks::IncrementStatEvent(__int64 neteventclass, CNetGamePlayers* Source)
	{
		const auto StatHash = *reinterpret_cast<DWORD*>(neteventclass + 0x30);
		if (protections.block_reports) {
			switch (StatHash)
			{
			case 0xE7072CD: {
				char name[64];
				sprintf(name, "%s reported you for hate", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0xB722D6C0: {
				char name[64];
				sprintf(name, "%s reported you for hate", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0x762F9994: {
				char name[64];
				sprintf(name, "%s reported you for annoying", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0x9F79BA0B: {
				char name[64];
				sprintf(name, "%s reported you for exploits", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0xCBFD04A4: {
				char name[64];
				sprintf(name, "%s reported you for exploits", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0x9C6A0C42: {
				char name[64];
				sprintf(name, "%s reported you for griefing", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0x3CDB43E2: {
				char name[64];
				sprintf(name, "%s reported you for offensive language", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0xE8FB6DD5: {
				char name[64];
				sprintf(name, "%s reported you for offensive tag plate??", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0xF3DE4879: {
				char name[64];
				sprintf(name, "%s reported you for ugc??", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0xAA238FF0: {
				char name[64];
				sprintf(name, "%s reported you for bad crew name", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0x03511A79: {
				char name[64];
				sprintf(name, "%s reported you for bad crew moto", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0x3B566D5C: {
				char name[64];
				sprintf(name, "%s reported you for bad crew status", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}
			case 0x368F6FD9: {
				char name[64];
				sprintf(name, "%s reported you for bad crew emblem", Source->PlayerInfo->m_net_player_data.m_name);
				protections.push_notification(name);
				return true;
				break;
			}


			}
		}

		return static_cast<decltype(&IncrementStatEvent)>(g_Hooking->m_OriginalIncrementStatEvent)(neteventclass, Source);
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
				sprintf(name, "%s is leaving slot %i", player->m_player_info->m_net_player_data.m_name, (int)player->m_player_id);
				antiCheat.remove_as_modder(player->m_player_id);
				protections.push_notification(name);
				if (all_players.notifications.log) {
					g_Logger->Info(name);
				}


			}

			return static_cast<decltype(&AssignNewPhysicalIndexHandler)>(g_Hooking->m_OriginalAssignPhysicalIndex)(netPlayerMgr, player, new_index);
		}

		const auto result = static_cast<decltype(&AssignNewPhysicalIndexHandler)>(g_Hooking->m_OriginalAssignPhysicalIndex)(netPlayerMgr, player, new_index);


		if (net_player_data)
		{

			char name[64];
			sprintf(name, "%s is joining slot %i", player->m_player_info->m_net_player_data.m_name, (int)player->m_player_id);
			if (player->m_player_info->m_net_player_data.m_name == (*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_net_player_data.m_name) {
				
				for (std::uint32_t i = 0; i < 32; ++i) {
					antiCheat.remove_as_modder(i);
				}
			}
			protections.push_notification(name);
			if (all_players.notifications.log) {
				g_Logger->Info(name);
			}




		}

		return result;
	}

	void Hooks::InvalidModsCrashPatch(std::int64_t a1, std::int64_t a2, int a3, char a4)
	{
		if (protections.Crashes.vehicle) {
			if (!*(int64_t*)(a1 + 0xD8)) {
				protections.push_notification2("Blocked crash.");
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
	 
	void Hooks::NetworkEventHandler(__int64 networkMgr, CNetGamePlayer* source, CNetGamePlayer* target, unsigned __int16 event_id, int event_index, int event_bitset, __int64 buffer_size, __int64 buffer)
	{
		if (event_id > 91u)
		{
			

			return;
		}

		const auto event_name = *(char**)((DWORD64)networkMgr + 8i64 * event_id + 243376);
		if (event_name == nullptr || target == nullptr || source->m_player_id < 0 || source->m_player_id >= 32)
		{
		
			return;
		}
		switch (static_cast<eNetworkEvents>(event_id))
		{
			case eNetworkEvents::CRemoveAllWeaponsEvent: {
				if (protections.GameEvents.remove_all_weapons) {
					char name1[64];
					sprintf(name1, "Remove weapons from %s blocked.", source->m_player_info->m_net_player_data.m_name);
					g_NotificationManager->add(name1, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CRequestControlEvent: {
				if (protections.GameEvents.request_control) {
					char name[64];
					sprintf(name, "Request control from %s blocked.", source->m_player_info->m_net_player_data.m_name);
					g_NotificationManager->add(name, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CNetworkPlaySoundEvent: {
				if (protections.GameEvents.play_sound) {
					char name2[64];
					sprintf(name2, "Play sound from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(name2, 2000, 1);

					return;
				}
				break;
			}
			
			case eNetworkEvents::CExplosionEvent: {
				if (protections.GameEvents.explosion) {
					char name2324[64];
					sprintf(name2324, "Explosion from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(name2324, 2000, 1);
					return;
				}
				break;
			}
			
			case eNetworkEvents::CGiveWeaponEvent: {
				if (protections.GameEvents.give_weapons) {
					char name2324545645[64];
					sprintf(name2324545645, "Give weapon from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(name2324545645, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CNetworkClearPedTasksEvent: {
				if (protections.GameEvents.freeze) {
					char g_Freeze[64];
					sprintf(g_Freeze, "Freeze from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_Freeze, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CNetworkPtfxEvent: {
				if (protections.GameEvents.particle_spam) {
					char g_PTFX[64];
					sprintf(g_PTFX, "Particle spam from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_PTFX, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CRemoveWeaponEvent: {
				if (protections.GameEvents.remove_weapon) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Remove weapon from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CRagdollRequestEvent: {
				if (protections.GameEvents.ragdoll_request) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Ragdoll from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CRequestPickupEvent: {
				if (protections.GameEvents.request_pickup) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Request pickup from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CGivePickupRewardsEvent: {
				if (protections.GameEvents.give_pickup_rewards) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Give pickup rewards from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CRequestMapPickupEvent: {
				if (protections.GameEvents.request_map_pickup) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Request map pickup from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CRemoveStickyBombEvent: {
				if (protections.GameEvents.remove_sticky_bomb) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Remove sticky bomb from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			
			case eNetworkEvents::CWeaponDamageEvent: {
				if (protections.GameEvents.weapon_damage) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Weapon damage from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CVehicleComponentControlEvent: {
				if (protections.GameEvents.vehicle_component_control) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Component control from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CChangeRadioStationEvent: {
				if (protections.GameEvents.chnage_radio_station) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Change radio station from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			
			case eNetworkEvents::CKickVotesEvent: {
				if (protections.GameEvents.vote_kick) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Vote kick from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
			case eNetworkEvents::CBlowUpVehicleEvent: {
				if (protections.GameEvents.blow_up_vehicle) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "Blow up vehicle from %s blocked.", source->m_player_info->m_net_player_data.m_name);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return;
				}
				break;
			}
		}

		return static_cast<decltype(&NetworkEventHandler)>(g_Hooking->m_OriginalNetworkHandler)(networkMgr, source, target, event_id, event_index, event_bitset, buffer_size, buffer);
	}
	bool Hooks::GetEventData(int32_t eventGroup, int32_t eventIndex, int64_t* args, uint32_t argCount)
	{
		auto result = static_cast<decltype(&GetEventData)>(g_Hooking->m_OriginalGetEventData)(eventGroup, eventIndex, args, argCount);
	
		if (result && *g_GameVariables->m_is_session_started) {
			auto sender = g_GameVariables->m_net_game_player(args[1]);
			for (auto& evnt : m_scriptEvents) {
				if (args[0] == evnt.eventHash && *evnt.eventBlockToggle) {
					char g_RemoveWeapons[64];
					sprintf(g_RemoveWeapons, "%s has tried to send the event '%s'", sender->get_name(), evnt.eventName);

					g_NotificationManager->add(g_RemoveWeapons, 2000, 1);
					return false;
				}
			}
			
		}
		return result;
	}
	Hooking::Hooking() :
		m_D3DHook(g_GameVariables->m_Swapchain, 18)
	{

		MH_Initialize();
		MH_CreateHook(g_GameFunctions->m_GetLabelText, &Hooks::GetLabelText, &m_OriginalGetLabelText);
		MH_CreateHook(g_GameFunctions->m_WndProc, &Hooks::WndProc, &m_OriginalWndProc);
		MH_CreateHook(g_GameFunctions->m_PlayerListMenuConstructor, &Hooks::CPlayerListMenuConstructor, &m_OriginalJoinSessionHook);
		MH_CreateHook(g_GameFunctions->m_PlayerWildcard, &Hooks::PlayerWildCardHandler, &m_OriginalRIDFunction);
		MH_CreateHook(g_GameFunctions->m_IncrementStatEvent, &Hooks::IncrementStatEvent, &m_OriginalIncrementStatEvent);
		MH_CreateHook(g_GameFunctions->m_write_player_game_state_data_node, &Hooks::write_player_game_state_data_node, &m_Original_write_player_game_state_data_node);
		MH_CreateHook(g_GameFunctions->m_write_player_gamer_data_node, &Hooks::write_player_gamer_data_node, &m_Original_write_player_gamer_data_node);
		MH_CreateHook(g_GameFunctions->m_SendNetInfo, &Hooks::SendNetInfo, &m_OriginalSendNetInfo);
		MH_CreateHook(g_GameFunctions->m_send_chat_message, &Hooks::send_chat_message, &m_OriginalChatSend);
		MH_CreateHook(g_GameFunctions->m_AssignPhysicalIndexHandler, &Hooks::AssignNewPhysicalIndexHandler, &m_OriginalAssignPhysicalIndex);
		MH_CreateHook(g_GameFunctions->crashProtection, &Hooks::InvalidModsCrashPatch, &m_OriginalModCrash);
	
		MH_CreateHook(g_GameFunctions->m_NetworkEvents, &Hooks::NetworkEventHandler, &m_OriginalNetworkHandler);
		MH_CreateHook(g_GameFunctions->m_GetEventData, &Hooks::GetEventData, &m_OriginalGetEventData);
		//MH_CreateHook(g_GameFunctions->m_GetScriptEvent, &Hooks::NetworkEventHandler, &m_OriginalNetworkHandler);
		//MH_CreateHook(g_GameFunctions->m_get_network_event_data, &Hooks::GetNetworkEventData, &originalDetection);
		//MH_CreateHook(g_GameFunctions->m_received_event, &Hooks::GameEvent, &OriginalRecivied);
		m_D3DHook.Hook(&Hooks::Present, Hooks::PresentIndex);
		m_D3DHook.Hook(&Hooks::ResizeBuffers, Hooks::ResizeBuffersIndex);
	}

	Hooking::~Hooking() noexcept
	{

		MH_RemoveHook(g_GameFunctions->m_GetLabelText);
		MH_RemoveHook(g_GameFunctions->m_WndProc);
		MH_RemoveHook(g_GameFunctions->m_PlayerListMenuConstructor);
		MH_RemoveHook(g_GameFunctions->m_PlayerWildcard);
		//MH_RemoveHook(g_GameFunctions->m_ChatMessage);
		MH_RemoveHook(g_GameFunctions->m_IncrementStatEvent);
		MH_RemoveHook(g_GameFunctions->m_write_player_game_state_data_node);
		MH_RemoveHook(g_GameFunctions->m_write_player_gamer_data_node);
		MH_RemoveHook(g_GameFunctions->m_SendNetInfo);
		MH_RemoveHook(g_GameFunctions->m_send_chat_message);
		MH_RemoveHook(g_GameFunctions->m_AssignPhysicalIndexHandler);
		MH_RemoveHook(g_GameFunctions->crashProtection);
		//MH_RemoveHook(g_GameFunctions->m_pickup_creation);
		MH_RemoveHook(g_GameFunctions->m_NetworkEvents);
		MH_RemoveHook(g_GameFunctions->m_GetEventData);
		//MH_RemoveHook(g_GameFunctions->m_GetScriptEvent);
		//MH_RemoveHook(g_GameFunctions->m_get_network_event_data);
		//MH_RemoveHook(g_GameFunctions->m_received_event);
		//MH_RemoveHook(g_GameFunctions->m_GetEventData);
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

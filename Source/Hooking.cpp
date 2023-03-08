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
#include "Protections.h"
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
	void Hooks::GetEventData2(rage::scrNativeCallContext* src)
	{
		const auto eventGroup = src->get_arg<int>(0);
		const auto eventIndex = src->get_arg<int>(1);
		const auto args = src->get_arg<Any*>(2);
		const auto argCount = src->get_arg<Hash>(3);

		if (g_LogScriptEvents)
		{
			g_Logger->Info("Script event group: %i", eventGroup);
			g_Logger->Info("Script event index: %i", eventIndex);
			g_Logger->Info("Script event argcount: %i", argCount);
			for (std::uint32_t i = 0; i < argCount; ++i)
				g_Logger->Info("Script event args[%u] : %" PRIi64, i, args[i]);
		}

		src->set_return_value(SCRIPT::GET_EVENT_DATA(eventGroup, eventIndex, args, argCount));
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
		if (protections.crash.vehicle) {
			if (!*(int64_t*)(a1 + 0xD8)) {
				protections.push_notification2("Blocked crash.");
				return;
			}
		}
		return static_cast<decltype(&InvalidModsCrashPatch)>(g_Hooking->m_OriginalModCrash)(a1, a2, a3, a4);
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

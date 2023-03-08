#include "Signatures.hpp"
#include "Invoker.hpp"

namespace Saint
{

	GameVariables::GameVariables() :
		m_GameState(Signature("83 3D ? ? ? ? ? 75 17 8B 43 20 25").Scan().Add(2).Rip().As<decltype(m_GameState)>()),
		m_FrameCount(Signature("8B 15 ? ? ? ? 41 FF CF").Scan().Add(2).Rip().As<decltype(m_FrameCount)>()),
		m_GameWindow(FindWindowA("grcWindow", nullptr)),
		m_Swapchain(Signature("44 38 35 ? ? ? ? 48 8B 01").Scan().Sub(13).Rip().As<decltype(m_Swapchain)&>()),
		m_ScriptProgramTable(Signature("44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1").Scan().Add(17).Rip().As<decltype(m_ScriptProgramTable)>()),
		m_NativeRegistrations(Signature("76 32 48 8B 53 40 48 8D 0D").Scan().Add(9).Rip().As<decltype(m_NativeRegistrations)>()),
		m_NativeReturnAddress(Signature("FF E3").Scan().As<decltype(m_NativeReturnAddress)>()),
		m_GlobalBase(Signature("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D").Scan().Add(3).Rip().As<decltype(m_GlobalBase)>()),
		m_region_code(Signature("48 83 EC 28 83 3D ? ? ? ? ? 75 10").Scan().Add(16).Rip().Add(1).As<decltype(m_region_code)>()),
		m_net_game_player(Signature("48 83 EC ? 33 C0 38 05 ? ? ? ? 74 ? 83 F9").Scan().As<decltype(m_net_game_player)>()),
		m_handle_to_ptr(Signature("83 F9 FF 74 31 4C 8B 0D").Scan().As<decltype(m_handle_to_ptr)>()),
		m_request_control(Signature("E8 ? ? ? ? EB 3E 48 8B D3").Scan().Add(1).Rip().As<decltype(m_request_control)>()),
		ui_3d_draw_manager(Signature("4C 8B 15 ? ? ? ? F3 0F 11 45 ? F3 0F 10 05 ? ? ? ? BF ? ? ? ? BB ? ? ? ? 41 BE ? ? ? ? F3 0F 11").Scan().Add(3).Rip().As<decltype(ui_3d_draw_manager)>()),
		push_scene_preset_manager(Signature("40 53 48 83 EC 20 8B 02 48 8D 54 24 38 48 8B D9 89 44 24 38 E8 ? ? ? ? 48 8B C8").Scan().As<decltype(push_scene_preset_manager)>()),
		add_element_to_scene(Signature("4C 8B DC 48 83 EC 58 8B").Scan().As<decltype(add_element_to_scene)>()),
		set_scene_element_lighting(Signature("48 8B C4 48 89 58 10 48 89 70 18 57 48 83 EC 30 48 83 B9").Scan().As<decltype(set_scene_element_lighting)>()),
		get_scene_preset(Signature("0F B7 81 10 08 00 00").Scan().As<decltype(get_scene_preset)>()),
		m_is_session_started(Signature("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE").Scan().Add(3).Rip().As<bool*>()),
		m_ModelSpawnBypass(Signature("48 8B C8 FF 52 30 84 C0 74 05 48").Scan().Add(8).As<decltype(m_ModelSpawnBypass)>())
	{
		m_GameBuild = Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8").Scan().Sub(17).Add(268).Rip().As<decltype(m_GameBuild)>();
	}

	void GameVariables::PostInit()
	{
	}

	GameFunctions::GameFunctions() :
		m_GetLabelText(Signature("48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8").Scan().As<decltype(m_GetLabelText)>()),
		m_WndProc(Signature("44 8B E2 4C 8B E9 3B D0").Scan().Sub(52).As<decltype(m_WndProc)>()),
		m_GetNativeHandler(Signature("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A").Scan().Add(12).Rip().As<decltype(m_GetNativeHandler)>()),
		m_FixVectors(Signature("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA").Scan().As<decltype(m_FixVectors)>()),
		m_pedFactory(Signature("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81").Scan().Add(3).Rip().As<decltype(m_pedFactory)>()),
		m_owned_explosion(Signature("0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8").Scan().As<decltype(m_owned_explosion)>()),
		m_vehicle_hash_pool(Signature("4C 03 05 ? ? ? ? EB 09 49 83 C2 04 EB 8B").Scan().Add(3).Rip().As<decltype(m_vehicle_hash_pool)>()),
		m_trigger_script_event(Signature("45 8B F0 41 8B F9 48 8B EA").Scan().Sub(0x1C).As<decltype(m_trigger_script_event)>()),
		m_PlayerGUIOptions(Signature("75 29 48 85 C0 0F").Scan().Sub(65).As<decltype(m_PlayerGUIOptions)>()),
		m_PlayerWildcard(Signature("75 1C E8 ? ? ? ? 48 85").Scan().Sub(11).As<decltype(m_PlayerWildcard)>()),
		m_PlayerListMenuConstructor(Signature("75 1B 48 8D 4F").Scan().Sub(248).As<decltype(m_PlayerListMenuConstructor)>()),
		//m_GetEventData(Signature("48 85 C0 74 14 4C 8B 10").Scan().Sub(28).As<decltype(m_GetEventData)>()),
		m_remote_increment(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F0 8B EA 8B F9 E8").Scan().As<decltype(m_remote_increment)>()),
		m_IncrementStatEvent(Signature("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 55 41 56 41 57 48 8B EC 48 83 EC 60 8B 79 30").Scan().As<decltype(m_IncrementStatEvent)>()),
		get_chat_sender(Signature("E8 ? ? ? ? 83 BD ? ? ? ? ? 48 8B D8 0F 8D ? ? ? ? 48 8B ? ? ?").Scan().Add(0x1).Rip().As<decltype(get_chat_sender)>()),
		m_write_player_game_state_data_node(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 30 0F B7 81").Scan().As<decltype(m_write_player_game_state_data_node)>()),
		m_write_player_gamer_data_node(Signature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 81 C1 ? ? ? ? 48 8B DA E8").Scan().As<PVOID>()),
		m_SendNetInfo(Signature("E8 ? ? ? ? 84 C0 74 26 8B 96").Scan().Sub(0xC4).As<decltype(m_SendNetInfo)>()),
		m_send_chat_ptr(Signature("83 7E 1C 01 48 8B 3D").Scan().Add(7).Rip().As<int64_t**>()),
		m_send_chat_message(Signature("48 83 EC 20 48 8B F1 48 8B CA 41 8A E9").Scan().Sub(21).As<decltype(m_send_chat_message)>()),
		//	m_ChatMessage(Signature("40 88 B3 ? ? ? ? 89 73 08 48 39 B3 ? ? ? ? 75 24 48 8D 05 ? ? ? ? 48 8B CB 48 89 B3").Scan().Add(0x16).Rip().As<decltype(m_ChatMessage)>()),
		m_AssignPhysicalIndexHandler(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8").Scan().As<PVOID>()),
		m_clear_ped_tasks_network(Signature("E8 ? ? ? ? EB 28 48 8B 8F A0 10 00 00").Scan().Add(1).Rip().As<decltype(m_clear_ped_tasks_network)>()),
		crashProtection(Signature("E8 ? ? ? ? 40 88 7C 24 ? 49 89 9C 24").Scan().Add(1).Rip().As<PVOID>()),
		m_RegisterFile(Signature("84 C0 74 0D 4C 8B 07").Scan().Sub(0x6C).As<decltype(m_RegisterFile)>()),
		should_sync_money_rewards(Signature("40 8A 2D ? ? ? ? 48 83 64 24 40 00").Scan().Add(3).Rip().As<decltype(should_sync_money_rewards)>())

	{
	}

}

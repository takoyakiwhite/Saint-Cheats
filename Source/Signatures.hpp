#pragma once

// GTA-V
#include <GTAV-Classes/script/scrProgramTable.hpp>
#include <GTAV-Classes/script/scrNativeHandler.hpp>
#include <GTAV-Classes/script/scrNativeRegistration.hpp>
#include <GTAV-Classes/script/scrNativeRegistrationTable.hpp>
#include <GTAV-Classes/ped/CPedFactory.hpp>
#include <GTAV-Classes/network/CMsgTextMessage.hpp>
#include "Classes.h"
#include "Types.hpp"
#include <GTAV-Classes/netsync/nodes/player/CPlayerGameStateDataNode.hpp>

#include "Protections.h"
#include "Common.hpp"
#include <GTAV-Classes/rage/rlSessionByGamerTaskResult.hpp>
#include <GTAV-Classes/rage/rlScHandle.hpp>
#include <GTAV-Classes/rage/rlQueryPresenceAttributesContext.hpp>
#include <GTAV-Classes/rage/rlTaskStatus.hpp>
#include <GTAV-Classes/network/Network.hpp>
#include <GTAV-Classes/socialclub/FriendRegistry.hpp>
namespace Saint
{

	class netConnectionManager;
	class netConnectionPeer
	{
	public:
		uint32_t m_internal_ip; //0x0000
		uint16_t m_internal_port; //0x0004
		uint32_t m_external_ip; //0x0008
		uint16_t m_external_port; //0x000C
		uint64_t m_peer_id; //0x0010
		uint32_t unk_0018; //0x0018
		uint16_t unk_001C; //0x001C
		uint8_t m_platform; //0x001E
	};
	static_assert(sizeof(netConnectionPeer) == 0x20);

	class GameVariables
	{
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		void PostInit();

		std::uint32_t* m_GameState;
		std::uint32_t* m_FrameCount;
		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;

		rage::scrProgramTable* m_ScriptProgramTable;
		rage::scrNativeRegistrationTable* m_NativeRegistrations;
		void* m_NativeReturnAddress;
		std::uint64_t** m_GlobalBase;
		PVOID m_ModelSpawnBypass;
		char* m_GameBuild;
		uint32_t* m_region_code;

		using get_net_game_player = CNetGamePlayer * (*) (uint32_t player);
		get_net_game_player m_net_game_player;

		using handle_to_ptr = rage::CDynamicEntity* (*)(Entity);
		handle_to_ptr m_handle_to_ptr{};

		bool* m_is_session_started{};

		using request_control = void (*)(rage::netObject* net_object);
		request_control m_request_control;

		uintptr_t ui_3d_draw_manager;
		uintptr_t add_element_to_scene;
		uintptr_t push_scene_preset_manager;
		uintptr_t set_scene_element_lighting;
		uintptr_t get_scene_preset;

		uint64_t m_WorldPtr;

		FriendRegistry* m_friendRegistry;


	};

	class GameFunctions
	{
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const&) = delete;
		GameFunctions(GameFunctions&&) = delete;
		GameFunctions& operator=(GameFunctions const&) = delete;
		GameFunctions& operator=(GameFunctions&&) = delete;

		using NetworkHandler = void(__int64 a1, __int64 a2, __int64 a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8);
		NetworkHandler* m_NetworkEvents;


		

		using clear_ped_tasks_network = void(*)(CPed* ped, bool immediately);
		clear_ped_tasks_network m_clear_ped_tasks_network;

		int64_t** m_send_chat_ptr{};
		using chat_message = bool(*)(int64_t* send_chat_ptr, rage::rlGamerInfo* gamer_info, char* message, bool is_team);
		chat_message m_send_chat_message{};

		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc* m_WndProc;

		PVOID crashProtection;

		using GetLabelText = const char* (void* unk, const char* label);
		GetLabelText* m_GetLabelText;

		using GetNativeHandler = rage::scrNativeHandler(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
		GetNativeHandler* m_GetNativeHandler;

		using FixVectors = void(rage::scrNativeCallContext*);
		FixVectors* m_FixVectors;

		CPedFactory** m_pedFactory;

		using CPlayerListMenuConstructor = __int64(__int64 a1, __int64 a2, __int64 a3);
		CPlayerListMenuConstructor* m_PlayerListMenuConstructor;

		using ChatSender = CNetGamePlayers * (__int64 player);
		ChatSender* get_chat_sender;

		using ChatMessage = void(void* thisptr, __int64  unk1, __int64 unk2, const char* message);
		ChatMessage* m_ChatMessage;

		PVOID m_owned_explosion;
		rage::hash_list* m_vehicle_hash_pool;

		bool* should_sync_money_rewards;

		using trigger_script_event = void(*)(int event_group, int64_t* args, int arg_count, int player_bits);
		trigger_script_event m_trigger_script_event{};

		using CPlayerActionsMenu = void(__int64 a1, unsigned int* a2);
		CPlayerActionsMenu* m_PlayerGUIOptions;

		using CPlayerWildCard = __int64* (std::int32_t friendindex);
		CPlayerWildCard* m_PlayerWildcard;

		using RegisterFile = std::uint32_t(*)(std::uint32_t* texture_id, const char* path, bool p1, const char* name, bool p2);
		RegisterFile m_RegisterFile;

		using send_event_ack = void(*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
		send_event_ack m_send_event_ack{};

		using GetEventData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		GetEventData* m_GetEventData;

		using IncrementStatEvent = int(__int64 neteventsclass, CNetGamePlayers* targetPlayer);
		IncrementStatEvent* m_IncrementStatEvent;

		using increment_Stat = void (*) (Hash hash, unsigned int value, CNetGamePlayer* player);
		increment_Stat m_remote_increment;
		PVOID m_write_player_gamer_data_node{};

		using write_player_game_state_data_node2 = bool(*)(rage::netObject* plr, CPlayerGameStateDataNode* node);
		write_player_game_state_data_node2 m_write_player_game_state_data_node;

		using SendNetInfoo = bool(netPlayerData* player, __int64 a2, __int64 a3, DWORD* a4);
		SendNetInfoo* m_SendNetInfo;

		PVOID m_AssignPhysicalIndexHandler;

		PVOID m_received_event{};

		PVOID m_pickup_creation{};

		using start_get_session_by_gamer_handle = bool (*)(int profile_index, rage::rlGamerHandle* handles, int count, rage::rlSessionByGamerTaskResult* result, int unk, bool* success, rage::rlTaskStatus* state);
		start_get_session_by_gamer_handle m_start_get_session_by_gamer_handle;
		Network** m_network;
		using join_session_by_info = bool (*)(Network* network, rage::rlSessionInfo* info, int unk, int flags, rage::rlGamerHandle* handles, int handlecount);
		join_session_by_info m_join_session_by_info;

		PVOID m_get_network_event_data;

		
		using GetNetworkData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		GetNetworkData* m_GetScriptEvent;


		void* m_data; //0x0000
		uint32_t m_bitOffset; //0x0008
		uint32_t m_maxBit; //0x000C
		uint32_t m_bitsRead; //0x0010
		uint32_t m_curBit; //0x0014
		uint32_t m_highestBitsRead; //0x0018
		uint8_t m_flagBits; //0x001C

		

		

		


	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;

	


}

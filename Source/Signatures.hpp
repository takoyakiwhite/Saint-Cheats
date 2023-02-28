#pragma once

// GTA-V
#include <GTAV-Classes/script/scrProgramTable.hpp>
#include <GTAV-Classes/script/scrNativeHandler.hpp>
#include <GTAV-Classes/script/scrNativeRegistration.hpp>
#include <GTAV-Classes/script/scrNativeRegistrationTable.hpp>
#include <GTAV-Classes/ped/CPedFactory.hpp>
#include <GTAV-Classes/network/CMsgTextMessage.hpp>
#include "Classes.h"
namespace Arctic
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

		using GetNetPed = CPed * (int playerID);
		GetNetPed* m_GetNetPed;
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

		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc* m_WndProc;

		using GetLabelText = const char*(void* unk, const char* label);
		GetLabelText* m_GetLabelText;

		using GetNativeHandler = rage::scrNativeHandler(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
		GetNativeHandler* m_GetNativeHandler;

		using FixVectors = void(rage::scrNativeCallContext*);
		FixVectors* m_FixVectors;

		CPedFactory** m_pedFactory;

		
		PVOID m_owned_explosion;
		rage::hash_list* m_vehicle_hash_pool;

		bool* should_sync_money_rewards;
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;

	
}

#pragma once

// GTA-V
#include <GTAV-Classes/script/scrProgramTable.hpp>
#include <GTAV-Classes/script/scrNativeHandler.hpp>
#include <GTAV-Classes/script/scrNativeRegistration.hpp>
#include <GTAV-Classes/script/scrNativeRegistrationTable.hpp>
#include <GTAV-Classes/ped/CPedFactory.hpp>
namespace Arctic
{
	
	
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

		intptr_t** m_globalPtr;

		bool* should_sync_money_rewards;
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;

	class globals {
	private:
		uint64_t m_index;
		static void* getScriptGlobal(uint64_t index) { return g_GameFunctions->m_globalPtr[index >> 18 & 0x3F] + (index & 0x3FFFF); }
		static void* getLocalGlobal(PVOID stack, uint64_t index) { return reinterpret_cast<uintptr_t*>(uintptr_t(stack) + (index * sizeof(uintptr_t))); }
	public:
		globals(uint64_t index) {
			m_index = index;
		}
		globals at(uint64_t index) {
			return globals(m_index + index);
		}
		globals at(uint64_t index, uint64_t size) {
			return at(1 + (index * size));
		}
		//Script Globals
		template <typename T> std::enable_if_t<std::is_pointer<T>::value, T> as() {
			return (T)getScriptGlobal(m_index);
		}
		//Local Globals
		template <typename T> std::enable_if_t<std::is_pointer<T>::value, T> asLocal(PVOID stack) {
			return (T)getLocalGlobal(stack, m_index);
		}
	};
}

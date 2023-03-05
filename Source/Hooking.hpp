#pragma once
#include "VMTHook.hpp"
#include "Invoker.hpp"
#include "../Libraries/Include/GTAV-Classes/netsync/nodes/player/CPlayerGamerDataNode.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetworkPlayerMgr.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetGamePlayer.hpp"
namespace Saint
{
	inline bool m_EnableSCIDJoiner;
	inline __int64 m_SCIDJoiner;
	inline __int64 m_PlayerListPointer;
	inline int menu_version = 87456845654;
	struct Hooks
	{
		static void GetStatInt(rage::scrNativeCallContext* src);

		static const char* GetLabelText(void* unk, const char* label);
		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static constexpr auto PresentIndex = 8;
		static HRESULT Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags);

		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);

		static __int64* PlayerWildCardHandler(std::int32_t friendIndex);
		static __int64 CPlayerListMenuConstructor(__int64 a1, __int64 a2, __int64 a3);

		static bool GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		static void GetEventData2(rage::scrNativeCallContext* src);

		static int IncrementStatEvent(__int64 neteventclass, CNetGamePlayers* Source);

		static void ChatMessage(void* thisptr, __int64 unk1, __int64 unk2, const char* message);
		static bool write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node);
		static void write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node);

		static bool SendNetInfo(netPlayerData* player, __int64 a2, __int64 a3, DWORD* a4);

		static bool send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, const char* message, bool is_team);

		static void* AssignNewPhysicalIndexHandler(CNetworkPlayerMgr* NetworkPlayerMgr, CNetGamePlayer* player, uint8_t new_index);
		static void InvalidModsCrashPatch(std::int64_t a1, std::int64_t a2, int a3, char a4);






	};

	class Hooking
	{
	public:
		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(Hooking const&) = delete;
		Hooking& operator=(Hooking&&) = delete;

		void Hook();
		void Unhook();

		friend struct Hooks;
		void* m_OriginalChatSend{};
	private:
		void* m_NtQueryVirtualMemory{};

		void* m_OriginalGetLabelText{};
		void* m_OriginalWndProc{};
		VMTHook m_D3DHook;
		void* m_OriginalRIDFunction{};
		void* m_OriginalJoinSessionHook{};
		void* m_OriginalGetEventData{};
		void* m_OriginalIncrementStatEvent{};

		void* m_Original_write_player_game_state_data_node{};
		void* m_Original_write_player_gamer_data_node{};
		void* m_OriginalSendNetInfo{};

		void* m_OriginalAssignPhysicalIndex{};
		void* m_OriginalRecieveEvent{};
		void* m_OriginalModCrash{};


	};

	inline std::unique_ptr<Hooking> g_Hooking;
}

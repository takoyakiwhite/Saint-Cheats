#pragma once
#include "VMTHook.hpp"
#include "Invoker.hpp"
#include "../Libraries/Include/GTAV-Classes/netsync/nodes/player/CPlayerGamerDataNode.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetworkPlayerMgr.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetGamePlayer.hpp"
#include "Enums.h"
#include <GTAV-Classes/netsync/nodes/object/CObjectCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/ped/CPedCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/vehicle/CVehicleCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/task/ClonedTakeOffPedVariationInfo.hpp>
namespace Saint
{
	
	
	inline bool m_EnableSCIDJoiner;
	inline __int64 m_SCIDJoiner;
	inline __int64 m_PlayerListPointer;
	inline int menu_version = 87456845654;
	inline bool streamer_mode = false;
	inline std::string streamer_mode_name = "Saint";
	inline bool weapons_in_int = false;
	inline bool join_queue = false;
	inline CNetGamePlayer* m_syncing_player = nullptr;
	inline rage::rlSessionInfo g_Session_info;
	inline bool BeastLanding = false;
	class MenuFlag {
	public:
		bool isDev() {
			#ifndef DEV
				return false;
			#else
				return true;
			#endif	
		}
	};
	
	inline MenuFlag* Flags;
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

		static bool GetScriptEvent(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		static void NETWORK_SESSION_HOST(rage::scrNativeCallContext* src);
		static void DISABLE_CONTROL_ACTION(rage::scrNativeCallContext* src);
		static void HUD_FORCE_WEAPON_WHEEL(rage::scrNativeCallContext* src);
		static void SET_CURRENT_PED_WEAPON(rage::scrNativeCallContext* src);
		static bool IncrementStatEvent(CNetworkIncrementStatEvent* neteventclass, CNetGamePlayer* Source);

		static void ChatMessage(void* thisptr, __int64 unk1, __int64 unk2, const char* message);
		static bool write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node);
		static void write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node);

		static bool SendNetInfo(netPlayerData* player, __int64 a2, __int64 a3, DWORD* a4);

		static bool send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, const char* message, bool is_team);

		static void* AssignNewPhysicalIndexHandler(CNetworkPlayerMgr* NetworkPlayerMgr, CNetGamePlayer* player, uint8_t new_index);
		static void InvalidModsCrashPatch(std::int64_t a1, std::int64_t a2, int a3, char a4);

		

		static bool GameEvent(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int buffer_size, rage::datBitBuffer* buffer);
		static bool pickup_creation_node(CPickupCreationDataNode* node, rage::netObject* obj);

		static void NetworkEventHandler(rage::netEventMgr* networkMgr, CNetGamePlayer* source, CNetGamePlayer* target, unsigned __int16 event_id, int event_index, int event_bitset, __int64 buffer_size, datBitBuffer2* buffer);

		static bool GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount, int64_t sender);

		//crashes
		static bool received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp);
		static eAckCode received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, rage::datBitBuffer* bufer, uint16_t unk, uint32_t timestamp);
		static std::int64_t constraint_attachment_crash(std::uintptr_t a1);
		static bool fragment_physics_crash(uintptr_t a1, uint32_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5);
		static bool fragment_physics_crash_2(float* a1, float* a2);

		static void invalid_player_crash(uint64_t a1, uint64_t a2);
		static bool object_creation_data_node(CObjectCreationDataNode* node, rage::netObject* obj);
		static bool hk_ped_creation_data_node(CPedCreationDataNode* node);
		static bool hk_vehicle_creation_data_node(CVehicleCreationDataNode* node);

		static bool received_array_update(rage::netArrayHandlerBase* array, CNetGamePlayer* sender, rage::datBitBuffer* buffer, int size, std::int16_t cycle);
		static uint64_t task_parachute_object_0x270(uint64_t _this, int a2, int a3);
		static void serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer);
		static std::uint64_t* FallTaskConstructor(std::uint64_t* _this, std::uint32_t flags);

		static bool can_apply_data(rage::netSyncTree* tree, rage::netObject* object);

		

		






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
		void* m_OriginalIncrementStatEvent{};

		void* m_Original_write_player_game_state_data_node{};
		void* m_Original_write_player_gamer_data_node{};
		void* m_OriginalSendNetInfo{};

		void* m_OriginalAssignPhysicalIndex{};
		void* m_OriginalRecieveEvent{};
		void* m_OriginalModCrash{};

		void* OriginalRecivied{};

		void* m_OriginalPickupNode{};

		void* m_OriginalNetworkHandler{};

		void* originalDetection{};

		void* m_OriginalGetEventData{};
		void* m_OriginalFragmentCrash{};
		void* m_OriginalFragmentCrash2{};
		void* AttachmentCrash{};
		void* InvalidObjectCrash{};
		void* InvalidObjectCrash2{};

		void* m_OriginalInvalidPlayer{};
		void* m_OriginalInvalidPlayer222{};
		void* ped_creation{};
		void* vehicle_creation{};
		void* array_update{};
		void* parachute{};
		void* parachute2{};
		void* m_OriginalFallTaskConstructor{};

		void* crashover{};
	


	};

	inline std::unique_ptr<Hooking> g_Hooking;
}

#pragma once
#include "../Libraries/Include/GTAV-Classes/network/netPlayer.hpp"
#include "../Libraries/Include/GTAV-Classes/network/ClanData.hpp"
#include "../Libraries/Include/GTAV-Classes/rage/rlSessionInfo.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetGamePlayer.hpp"
#include "Signatures.hpp"
#include <GTAV-Classes/script/GtaThread.hpp>
namespace rage {
	

	static_assert(sizeof(GtaThread) == 0x160);
	enum class eEventNetworkType : int64_t
	{
		CEventNetworkPlayerJoinScript = 153,
		CEventNetworkPlayerLeftScript = 154,
		CEventNetworkStorePlayerLeft = 155,
		CEventNetworkStartSession = 156,
		CEventNetworkEndSession = 157,
		CEventNetworkStartMatch = 158,
		CEventNetworkRemovedFromSessionDueToStall = 160,
		CEventNetworkRemovedFromSessionDueToComplaints = 161,
		CEventNetworkConnectionTimeout = 162,
		CEventNetworkPedDroppedWeapon = 163,
		CEventNetworkPlayerSpawn = 164,
		CEventNetworkPlayerCollectedPickup = 165,
		CEventNetworkPlayerCollectedAmbientPickup = 166,
		CEventNetworkPlayerCollectedPortablePickup = 167,
		CEventNetworkPlayerDroppedPortablePickup = 168,
		CEventNetworkInviteAccepted = 170,
		CEventNetworkInviteConfirmed = 171,
		CEventNetworkInviteRejected = 172,
		CEventNetworkSummo = 173,
		CEventNetworkScriptEvent = 174,
		CEventNetworkSignInStateChanged = 176,
		CEventNetworkSignInChangeActioned = 177,
		CEventNetworkRosChanged = 178,
		CEventNetworkBail = 179,
		CEventNetworkHostMigration = 180,
		CEventNetworkFindSession = 181,
		EventNetworkHostSession = 182,
		CEventNetworkJoinSession = 183,
		CEventNetworkJoinSessionResponse = 184,
		CEventNetworkCheatTriggered = 185,
		CEventNetworkEntityDamage = 186,
		CEventNetworkPlayerArrest = 187,
		CEventNetworkTimedExplosion = 188,
		CEventNetworkPrimaryClanChanged = 189,
		CEventNetworkClanJoined = 190,
		CEventNetworkClanLeft = 191,
		CEventNetworkClanInviteReceived = 192,
		CEventNetworkVoiceSessionStarted = 193,
		CEventNetworkVoiceSessionEnded = 194,
		CEventNetworkVoiceConnectionRequested = 195,
		CEventNetworkVoiceConnectionResponse = 196,
		CEventNetworkVoiceConnectionTerminated = 197,
		CEventNetworkTextMessageReceived = 198,
		CEventNetworkCloudFileResponse = 199,
		CEventNetworkPickupRespawned = 200,
		CEventNetworkPresence_StatUpdate = 201,
		CEventNetworkPedLeftBehind = 202,
		CEventNetwork_InboxMsgReceived = 203,
		CEventNetworkAttemptHostMigration = 204,
		CEventNetworkIncrementStat = 205,
		CEventNetworkSessionEvent = 206,
		CEventNetworkTransitionStarted = 207,
		CEventNetworkTransitionEvent = 208,
		CEventNetworkTransitionMemberJoined = 209,
		CEventNetworkTransitionMemberLeft = 210,
		CEventNetworkTransitionParameterChanged = 211,
		CEventNetworkClanKicked = 212,
		CEventNetworkTransitionStringChanged = 213,
		EventNetworkTransitionGamerInstruction = 214,
		CEventNetworkPresenceInvite = 215,
		EventNetworkPresenceInviteRemoved = 216,
		EventNetworkPresenceInviteReply = 217,
		CEventNetworkCashTransactionLog = 218,
		CEventNetworkClanRankChanged = 219,
		CEventNetworkVehicleUndrivable = 220,
		CEventNetworkPresenceTriggerEvent = 221,
		CEventNetworkEmailReceivedEvent = 222,
		CEventNetworkFollowInviteReceived = 223,
		CEventNetworkSpectateLocal = 225,
		CEventNetworkCloudEvent = 226,
		CEventNetworkShopTransaction = 227,
		CEventNetworkOnlinePermissionsUpdated = 230,
		CEventNetworkSystemServiceEvent = 231,
		CEventNetworkRequestDelay = 232,
		CEventNetworkSocialClubAccountLinked = 233,
		CEventNetworkScAdminPlayerUpdated = 234,
		CEventNetworkScAdminReceivedCash = 235,
		CEventNetworkClanInviteRequestReceived = 236,
		CEventNetworkMarketingEmailReceivedEvent = 237,
		CEventNetworkStuntPerformed = 238,
		CEventNetworkFiredDummyProjectile = 239,
		CEventNetworkPlayerEnteredVehicle = 240,
		CEventNetworkPlayerActivatedSpecialAbility = 241,
		CEventNetworkPlayerDeactivatedSpecialAbility = 242,
		CEventNetworkPlayerSpecialAbilityFailedActivation = 243,
		CEventNetworkFiredVehicleProjectile = 244,
	};
	class CEventNetwork
	{
	public:
		virtual ~CEventNetwork() = default; //0x0000 (0)
		virtual void unk_0008() = 0; //0x0008 (1)
		virtual void unk_0010() = 0; //0x0010 (2)
		virtual eEventNetworkType get_type2() = 0; //0x0018 (3)
		virtual void unk_0020() = 0; //0x0020 (4)
		virtual void unk_0028() = 0; //0x0028 (5)
		virtual bool get_extra_information(void* info_array, int check) = 0; //0x0030 (6)
		virtual void unk_0038() = 0; //0x0038 (7)
	}; //Size: 0x0008
	class netEventMgr;
#pragma pack(push, 1)
	
	class netGameEvent
	{
	public:
		virtual ~netGameEvent() = default;

		virtual const char* get_name()
		{
			return 0;
		};
		virtual bool is_in_scope(netPlayer* player)
		{
			return 0;
		};
		virtual bool time_to_resend(std::uint32_t time)
		{
			return 0;
		};
		virtual bool can_change_scope()
		{
			return 0;
		};

		virtual void prepare_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual void handle_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};

		virtual bool decide(netPlayer* source_player, netPlayer* target_player)
		{
			return 0;
		};

		virtual void prepare_reply(datBitBuffer* buffer, netPlayer* reply_player) {};
		virtual void handle_reply(datBitBuffer* buffer, netPlayer* souce_player) {};

		virtual void prepare_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};
		virtual void handle_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};

	private:
		virtual void unk_0x60() {};
		virtual void unk_0x68() {};
		virtual void unk_0x70() {};
		virtual void unk_0x78() {};

	public:
		virtual bool operator==(netGameEvent const& other)
		{
			return 0;
		};
		virtual bool operator!=(netGameEvent const& other)
		{
			return 0;
		};

		virtual bool must_persist()
		{
			return 0;
		};
		virtual bool must_persist_when_out_of_scope()
		{
			return 0;
		};
		virtual bool has_timed_out()
		{
			return 0;
		};

	public:
		std::uint16_t m_id;   // 0x08
		bool m_requires_reply;// 0x0A
	private:
		char m_padding1[0x05];// 0x0B
	public:
		netPlayer* m_source_player; // 0x10
		netPlayer* m_target_player; // 0x18
		std::uint32_t m_resend_time;// 0x20
	private:
		std::uint16_t m_0x24;// 0x24
		std::uint8_t m_0x26; // 0x26
		std::uint8_t m_0x27; // 0x27
		std::uint32_t m_0x28;// 0x28
		char m_padding2[0x04];
	};
	class hash_list
	{
	public:
		std::uint64_t* list; //0x0000
		std::int32_t capacity; //0x0008
		char pad_000C[4]; //0x000C
		std::int32_t free; //0x0010
		char pad_0014[4]; //0x0014
		std::uint64_t item_size; //0x0018
		char pad_0020[16]; //0x0020
		std::uint32_t* data; //0x0030
		char pad_0038[16]; //0x0038
		std::int32_t occupied; //0x0048
		const std::uint64_t get(std::int32_t index) const {
			if ((this->data[index >> 5] >> (index & 0x1F)) & 1)
				return this->list[index];
			return NULL;
		}
	}; // Size: 0x004C
#pragma pack(pop)
}

namespace Saint {
	class CScriptParticipant
	{
	public:
		char pad_0000[16];                      //0x0000
		class CNetGamePlayer* m_net_game_player;//0x0010
		char pad_0018[2];                       //0x0018
		int16_t m_participant_index;            //0x001A
		char pad_001C[12];                      //0x001C
	};                                          //Size: 0x0028
	static_assert(sizeof(CScriptParticipant) == 0x28);
	class CGameScriptHandler : public rage::scriptHandler
	{
	public:
		CGameScriptId m_script_id;// 0x60
	};

	class CGameScriptHandlerNetwork : public CGameScriptHandler
	{
	public:
		std::uint8_t m_0xA0;       // 0xA0
		std::uint8_t m_0xA1;       // 0xA1
		std::uint8_t m_0xA2;       // 0xA2
		std::uint8_t m_0xA3;       // 0xA3
		std::uint8_t m_num_players;// 0xA4
		std::uint8_t m_0xA5;       // 0xA5
		std::uint8_t m_0xA6;       // 0xA6
		std::uint8_t m_0xA7;       // 0xA7
		std::uint8_t m_0xA8;       // 0xA8
		std::uint8_t m_0xA9;       // 0xA9
		std::uint8_t m_0xAA;       // 0xAA
		std::uint8_t m_0xAB;       // 0xAB
		std::uint8_t m_0xAC;       // 0xAC
		std::uint8_t m_0xAD;       // 0xAD
		std::uint8_t m_0xAE;       // 0xAE
		std::uint8_t m_0xAF;       // 0xAF
	};
	class CGameScriptHandlerNetComponent
	{
	public:
		virtual ~CGameScriptHandlerNetComponent() = default;

		virtual bool _0x08(void*) = 0;

		virtual void _0x10(CNetGamePlayer*) = 0;// creates a scriptId?

		virtual void* player_left(CNetGamePlayer* player) = 0;

		virtual void* send_host_migration_event(CNetGamePlayer* player) = 0;

		virtual void* player_joined(void**, void* msg_ctx) = 0;

		virtual void* player_joined_ack(void**, void* msg_ctx) = 0;

		virtual bool _0x38(void*, void*) = 0;// join_script?

		virtual void* _0x40(void*, void*) = 0;

		virtual void* _0x48(void*, void*, void*) = 0;

		virtual void* _0x50(void*, void*) = 0;

		virtual void* _0x58(void*, void*) = 0;

		virtual void* _0x60(void*, void*) = 0;

		virtual void* _0x68(void*, void*) = 0;

		virtual void _0x70(void*, void*) = 0;

		virtual void _0x78(void*, void*) = 0;

		virtual short _0x80(void*, void*) = 0;

		virtual void* _0x88(void*, void*) = 0;

		virtual void* _0x90(void*, void*) = 0;// HOST_MIGRATION_FAILED

		virtual bool _0x98(void*, void*) = 0;

		virtual void* _0xA0(void*, void*) = 0;

		virtual void* _0xA8(void*, void*) = 0;

		virtual short _0xB0(void*, void*) = 0;

		virtual bool register_host_broadcast_data(void* data, int size, char* a3) = 0;

		virtual bool register_player_broadcast_data(int a1, int size, bool a3) = 0;

		virtual bool _0xC8() = 0;// something to do to joining session

		virtual bool _0xD0() = 0;

		virtual bool add_player_to_script(CNetGamePlayer* player, short* outParticipantID, short* outSlot, int* outFailReason) = 0;

		virtual bool add_player_to_script_internal(CNetGamePlayer* player, short participantID, short slot) = 0;// player aka participant

		virtual bool remove_player_from_script(CNetGamePlayer* player) = 0;

		virtual void* player_left_impl(CNetGamePlayer*, bool) = 0;

		virtual bool do_host_migration(CNetGamePlayer* player, short host_token, bool unk) = 0;// aka _0xF8

		virtual void* leave_from_script() = 0;// calls above function with player = nullptr

		virtual bool _0x108() = 0;

		virtual void* _0x110() = 0;

		virtual bool _0x118() = 0;// related to above function

		CGameScriptHandler* m_script_handler;        //0x0008
		char pad_0010[32];                           //0x0010
		class CScriptParticipant* m_host;            //0x0030
		int16_t m_local_participant_index;           //0x0038
		char pad_003A[6];                            //0x003A
		uint32_t m_participant_bitset;               //0x0040
		char pad_0044[36];                           //0x0044
		class CScriptParticipant* m_participants[32];//0x0068
		char pad_0168[12];                           //0x0168
		int16_t m_num_participants;                  //0x0174
		char pad_0176[28];                           //0x0176
		uint8_t m_host_migration_flags;              //0x0192
		char pad_0193[29];                           //0x0193

		int get_participant_index(CNetGamePlayer* player);
		bool is_player_a_participant(CNetGamePlayer* player);

		inline bool is_local_player_host()
		{
			if (!m_host)
				return true;// or return false?

			return m_host->m_participant_index == m_local_participant_index;
		}

		inline CNetGamePlayer* get_host()
		{
			if (!m_host)
				return nullptr;

			return m_host->m_net_game_player;
		}

		// not 100% foolproof
		inline void block_host_migration(bool toggle)
		{
			if (toggle)
				m_host_migration_flags |= (1 << 7);
			else
				m_host_migration_flags &= ~(1 << 7);
		}

	};//Size: 0x01B0
	static_assert(sizeof(CGameScriptHandlerNetComponent) == 0x1B0);
	class CNetworkObjectMgr;
#pragma pack(push, 8)
	class CPickupCreationDataNode
	{
	public:
		char pad_0000[192]; //0x0000
		bool m_has_placement; //0x00C0
		char pad_00C1[7]; //0x00C1
		uint64_t* unk_struct_00C8; //0x00C8
		uint32_t unk_00D0; //0x00D0
		uint16_t unk_00D4; //0x00D4
		char pad_00D6[66]; //0x00D6
		uint32_t m_pickup_hash; //0x0118
		uint32_t m_amount; //0x011C
		uint32_t m_custom_model; //0x0120
		uint32_t m_life_time; //0x0124
		uint32_t m_weapon_component[11]; //0x0128
		uint32_t m_num_weapon_components; //0x0154
		uint32_t m_tint_index; //0x0158
		bool m_player_gift; //0x015C
		bool unk_015D; //0x015D
		char pad_015E[6]; //0x015E
		uint32_t unk_0164; //0x0164
		bool unk_0168; //0x0168
	}; //Size: 0x0170
	static_assert(sizeof(CPickupCreationDataNode) == 0x170);
#pragma pack(pop)
#ifndef __PE_IMAGE__
#define __PE_IMAGE__
	typedef const IMAGE_NT_HEADERS64 NT64H;
	typedef std::vector<char> bufferVec;

	class PEImage {
	public:

		PEImage();
		~PEImage();

		bool			Load(const std::string& path);

		bool			IsOpenVHookCompatible();

		bool			PatchCompatibility();

	private:

		uint64_t		GetDirectoryAddress(int index);
		uint64_t		RVAToVA(uint32_t rva) const;

		bool			ParsePE();

	private:

		std::string		filePath;
		bufferVec		fileBuffer;
		NT64H* ntHeader = nullptr;
	};
#endif // __PE_IMAGE__
#pragma pack(push, 4)
	class vehicle_item final
	{
	public:
		char m_name[16];
		char m_display_name[32];
		char m_display_manufacturer[32];
		char m_vehicle_class[32];
		std::uint32_t m_hash;
	};
#pragma pack(pop)
	class CScriptedGameEvent : public rage::netGameEvent
	{
	public:
		char m_padding[0x40];     // 0x30
		std::int64_t m_args[54];  // 0x70
		std::uint32_t m_bitset;   // 0x220
		std::uint32_t m_args_size;// 0x224
	};
	
	class netPlayerData
	{
	public:
		char pad_0000[8]; //0x0000
		int64_t m_rockstar_id_0; //0x0008
		char pad_0010[56]; //0x0010
		uint16_t N000005BF; //0x0048
		char pad_004A[2]; //0x004A
		netAddress m_online_ip; //0x0054
		int16_t m_online_port; //0x0058
		netAddress m_relay_ip; //0x004C
		int32_t m_relay_port; //0x0050
		char pad_005A[6]; //0x005A
		uint32_t m_host_token; //0x0060
		char pad_0064[12]; //0x0064
		int64_t m_rockstar_id; //0x0070
		char pad_0078[12]; //0x0078
		const char* m_name; //0x0084
	}; //Size: 0x0098
	


	class CNetGamePlayers : public rage::netPlayer
	{
	public:
		char pad_0x0008[0x10]; //0x0008
		std::uint32_t msg_id; // 0x18
		char pad_0x001C[0x4]; //0x001C
		std::int8_t active_id; //0x0020 
		std::int8_t m_player_id; //0x0021 
		char pad_0x0022[0x6E]; //0x0022
		BYTE local_player_check;//0x0090
		char pad_0x00A1[0xF]; //0x0091
		CPlayerInfo* PlayerInfo; //0x00A0

		inline bool is_local_player()
		{
			return local_player_check & 1;
		}
	};
}

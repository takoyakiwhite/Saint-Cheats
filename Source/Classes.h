#pragma once
#include "../Libraries/Include/GTAV-Classes/network/netPlayer.hpp"
#include "../Libraries/Include/GTAV-Classes/network/ClanData.hpp"
#include "../Libraries/Include/GTAV-Classes/rage/rlSessionInfo.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetGamePlayer.hpp"

namespace rage {
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
	union netAddress
	{
		uint32_t m_raw;
		struct
		{
			uint8_t m_field4;
			uint8_t m_field3;
			uint8_t m_field2;
			uint8_t m_field1;
		};
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

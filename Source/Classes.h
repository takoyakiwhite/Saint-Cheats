#pragma once
#include "../Libraries/Include/GTAV-Classes/network/netPlayer.hpp"
#include "../Libraries/Include/GTAV-Classes/network/ClanData.hpp"
#include "../Libraries/Include/GTAV-Classes/rage/rlSessionInfo.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetGamePlayer.hpp"
namespace rage {
#pragma pack(push, 1)
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

namespace Arctic {
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

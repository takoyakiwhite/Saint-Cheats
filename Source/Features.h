#pragma once
#include "Natives.hpp"
#include "FiberHelper.hpp"
#include <GTAV-Classes/ped/CPed.hpp>
namespace Arctic {
	inline bool neverWantedBool = false;
	inline bool godmode = false;
	class NoClip {
	public:
		bool enabled = false;
		bool WorkForVehicles = true;
		bool StopAfterNoInput = true;
		float speed = 2.5f;
		const char* FlyType[2]
		{
			"Camera", "Keyboard"
		};

		std::size_t FlyInt = 0;
	};
	inline void FeatureInitalize() {
		if (godmode) {
			uint32_t last_bits = 0;
			uint32_t proof_mask = 0;
			proof_mask |= static_cast<int>(1 << 8);
			uint32_t bits = proof_mask;
			uint32_t changed_bits = bits ^ last_bits;
			uint32_t changed_or_enabled_bits = bits | changed_bits;

			if (changed_or_enabled_bits)
			{
				uint32_t unchanged_bits = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits & ~changed_or_enabled_bits;
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits = unchanged_bits | bits;
				last_bits = bits;
			}
		}
		if (!godmode)
		{
			(*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits = 0;
		}
		if (neverWantedBool)
		{
			PLAYER::SET_MAX_WANTED_LEVEL(0);
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, true);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), true);
		}
	}
	
}
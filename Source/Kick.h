#pragma once

#include "Natives.hpp"
#include "Queue.h"
namespace Arctic {
	class Kicks {
	public:
		
		const char* Menu[2]
		{
			"Kiddions", "Rebound"
		};

		std::size_t Menu_Data = 0;
		const char* CrashMenu[1]
		{
			"Cherax"
		};

		std::size_t Menu_DataCrash = 0;
		void crash() {
			NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
			OBJECT::CREATE_OBJECT(3613262246, c.x, c.y, c.z, true, false, false);
		}
		void remove() {
			if (Menu_Data == 0) {
				const size_t arg_count = 15;
				int64_t args[arg_count] =
				{
					(int64_t)1727896103,
					(int64_t)PLAYER::PLAYER_ID(),
					(int64_t)(int)-1
				};

				g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << g_SelectedPlayer);
				
				m_queue.add(18s, "Removing player..", [] {});
			}
		}
	};
}
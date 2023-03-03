#pragma once
#include "Flash Blip.h"
#include "OTR.h"
#include "Kick.h"
namespace Arctic {
	class GetSelected {
	public:
		FlashBlip flash_blip;
		OTR otr;
		Kicks events;
        int wanted_level = 0;
        bool freeze = false;
        uint8_t get_id() {
            return g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_id;
        }
        void kick_from_vehicle() {
            const size_t arg_count = 9;
            int64_t args[arg_count] = {
                (int64_t)-1603050746,
                PLAYER::PLAYER_ID(), 0, 0, 0, 0, 0, 0, 0
            };

            g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << get_id());
        }
        bool network_has_control_of_entity(rage::netObject* net_object)
        {
            return !net_object || !net_object->m_next_owner_id && (net_object->m_control_id == -1);
        }
        bool request_control(Entity ent, int timeout = 300)
        {
            auto ptr = g_GameVariables->m_handle_to_ptr(ent);
            if (ptr)
            {
                if (!*g_GameVariables->m_is_session_started || network_has_control_of_entity(ptr->m_net_object))
                    return true;
                for (int i = 0; !network_has_control_of_entity(ptr->m_net_object) && i < timeout; i++)
                {
                    g_GameVariables->m_request_control(ptr->m_net_object);
                    if (timeout != 0)
                        fbr::cur()->wait();
                }
                if (!network_has_control_of_entity(ptr->m_net_object))
                    return false;
                int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
                NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);
            }
            return true;
        }

        void set_wanted_level(int level) {
            PLAYER::REPORT_CRIME(g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_id, 8, PLAYER::GET_WANTED_LEVEL_THRESHOLD(level));
        }
        void taze() {
            int currentAttempt = 0;
            int maxAttempts = 20;
            while (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0))
            {
                if (currentAttempt >= maxAttempts)
                {
                    break;
                }
                else
                {
                    NativeVector3 destination = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), SKEL_ROOT, 0.0f, 0.0f, 0.0f);
                    NativeVector3 origin = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), SKEL_R_Hand, 0.0f, 0.0f, 0.2f);
                    Hash tazerHash = MISC::GET_HASH_KEY("WEAPON_STUNGUN");
                    MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, tazerHash, PLAYER::PLAYER_PED_ID(), false, false, 1);
                    currentAttempt++;
                }
                m_queue.add(1s, "Tazing player..", [] {});
            }
        }
		void init() {
            if (freeze) {
               
            }
			flash_blip.init();
			otr.init();
			
		}
	};
	
}
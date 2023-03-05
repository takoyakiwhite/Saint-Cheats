#pragma once
#include "Flash Blip.h"
#include "OTR.h"
#include "Kick.h"
#include "Notifications.h"
namespace Saint {
    class ExplosiveAmmo2 {
    public:
        bool enabled = false;
        bool invisible = false;
        bool sound = true;
        float damage = 1.0f;
        float camera_shake = 0.0f;
        const char* explode_type[81] = { "Grenade", "Grenade (Launcher)", "Sticky Bomb", "Molotov", "Rocket", "Tank Shell", "HI Octane", "Car", "Plane", "Gas Pump", "Bike", "Steam", "Flame", "Water", "Gas", "Boat", "Ship Destroy", "Truck", "Bullet", "Smoke", "Smoke 2", "BZ Gas", "Flare",
            "Unkown", "Extinguisher", "Unkown", "Train", "Barrel", "Propane", "Blimp", "Flame 2", "Tanker", "Plane Rocket", "Vehicle Bullet", "Gas Tank", "Bird Crap", "Railgun", "Blimp 2", "Firework", "Snowball", "Proximity Mine", "Valkyrie Cannon", "Air Defense", "Pipe Bomb",
            "Vehicle Mine", "Explosive Ammo", "APC Shell", "Cluster Bomb", "Gas Bomb", "Incendiary Bomb", "Bomb", "Torpedo", "Torpedo (Underwater)", "Bombushka Cannon", "Cluster Bomb 2", "Hunter Barrage", "Hunter Cannon", "Rouge Cannon", "Underwater Mine", "Orbital Cannon",
            "Bomb (Wide)", "Explosive Ammo (Shotgun)", "Oppressor MK II", "Kinetic Mortar", "Kinetic Vehicle Mine", "EMP Vehicle Mine", "Spike Vehicle Mine", "Slick Vehicle Mine", "Tar Vehicle Mine", "Script Drone", "Up-n-Atomizer", "Burried Mine", "Script Missle", "RC Tank Rocket",
            "Bomb (Water)", "Bomb (Water 2)", "Flash Grenade", "Stun Grenade", "Script Missle (Large)", "Submarine (Big)", "EMP Launcher" };
        std::size_t explode_int = 0;
        void add(Ped ped, float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) {
            *(unsigned short*)g_GameFunctions->m_owned_explosion = 0xE990;
            FIRE::ADD_OWNED_EXPLOSION(ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
            *(unsigned short*)g_GameFunctions->m_owned_explosion = 0x850F;
        }
        void init() {
            if (enabled) {
                if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer)))
                {
                    float Tmp[6];
                    WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), (NativeVector3*)Tmp);
                    if (Tmp[0] != 0 || Tmp[2] != 0 || Tmp[4] != 0) {
                       add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), Tmp[0], Tmp[2], Tmp[4], explode_int, damage, sound, invisible, camera_shake);

                        
                    }
                }
            }
        }
    };
	class GetSelected {
	public:
        ExplosiveAmmo2 explosiveAmmo;
		FlashBlip flash_blip;
		OTR otr;
		Kicks events;
        int wanted_level = 0;
        bool freeze = false;
        std::string buffer;
        std::uint64_t int_id = 0;
        uint8_t get_id() {
            return g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_id;
        }
        void send_to_int(const std::vector<std::uint64_t>& _args) {
            if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
                float max = 1e+38f;
                auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_id), FALSE);
                const size_t arg_count = 15;
                int64_t args[arg_count] =
                {
                    (int64_t)1727896103,
                    (int64_t)PLAYER::PLAYER_ID(),
                    (int64_t)(int)_args[0],
                    (int64_t)PLAYER::PLAYER_ID(),
                    (int64_t)false,
                    (int64_t)true, // true means enter sender interior
                    (int64_t) * (uint32_t*)&coords.x,
                    (int64_t) * (uint32_t*)&coords.y,
                    (int64_t) * (uint32_t*)&coords.z,
                    0,
                    0,
                    1,
                    (int64_t) * (uint32_t*)&max,
                    (int64_t)true,
                    -1
                };

                g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_id);
            }
            else {
                g_Notifcations->add("Please start a session.");

            }
           
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
                CPed* ped = g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_info->m_ped;
                g_GameFunctions->m_clear_ped_tasks_network(ped, true);
            }
            explosiveAmmo.init();
			flash_blip.init();
			otr.init();
			
		}
	};
	
}
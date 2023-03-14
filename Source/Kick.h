#pragma once

#include "Natives.hpp"
#include "Queue.h"

namespace Saint {
	class Kicks {
	public:

		const char* Menu[3]
		{
			"Kiddions", "Rebound", "All"
		};

		std::size_t Menu_Data = 0;
		const char* CrashMenu[1]
		{
			"Cherax"
		};

		std::size_t Menu_DataCrash = 0;
		void VehicleModifier2(int type, int index, Vehicle veh)
		{
			if (index == -1)
			{
				VEHICLE::REMOVE_VEHICLE_MOD(veh, type);
			}
			else
			{
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, type, index, false);
			}
		}
		void spawn_for_ped2(Hash hash, Vehicle* buffer) {
			*script_global(4540726).as<bool*>() = true;
			g_CallbackScript->AddCallback<ModelCallback>(hash, [=]
				{



					NativeVector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), { 0.f, 0.f, 1.0f });
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer)), true, false, false);

			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);

			auto networkId = NETWORK::VEH_TO_NET(vehicle);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);

			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
			VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true, true);
			fbr::cur()->wait(1s);
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
			VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HOOD, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, 7), false);




				});
		}
		void crash() {
			Vehicle crash;
			spawn_for_ped2(0x6838FC1D, &crash);

		}
		Network* get_network()
		{
			return *g_GameFunctions->m_network;
		}
		rage::rlGamerInfo* get_net_data() const
		{
			return g_GameVariables->m_net_game_player(g_SelectedPlayer) == nullptr ? nullptr : g_GameVariables->m_net_game_player(g_SelectedPlayer)->get_net_data();
		}
		rage::snPeer* get_session_peer()
		{
			for (std::uint32_t i = 0; i < get_network()->m_game_session_ptr->m_peer_count; i++)
			{
				if (get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_gamer_handle.m_rockstar_id == get_net_data()->m_gamer_handle.m_rockstar_id)
				{
					return get_network()->m_game_session_ptr->m_peers[i];
				}
			}

			return nullptr;
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
			if (Menu_Data == 1) {
				g_FiberPool.queue([]
					{
						const size_t arg_count = 3;
				int64_t args[arg_count] =
				{
					(int64_t)1674887089,
					(int64_t)PLAYER::PLAYER_ID(),
					*script_global(1892703).at(g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_id, 599).at(510).as<int64_t*>()
				};

				g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_id);
					});

				m_queue.add(18s, "Removing player..", [] {});
			}
			if (Menu_Data == 2) {

				
			}
		}
	};
}
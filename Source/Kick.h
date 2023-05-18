#pragma once

#include "Natives.hpp"
#include "Queue.h"
#include "All Players.h"
#include "FiberHelper.hpp"
namespace Saint {
	class Kicks {
	public:
		inline CNetworkPlayerMgr* GetNetworkPlayerMgr()
		{
			if (auto NetworkPlayerMgr = *g_GameFunctions->m_NetworkPlayerManager)
				return NetworkPlayerMgr;

			return nullptr;
		}
		std::chrono::system_clock::time_point last{};
		void DeleteEntity(Entity ent)
		{
			ENTITY::DETACH_ENTITY(ent, TRUE, TRUE);
			ENTITY::SET_ENTITY_VISIBLE(ent, FALSE, FALSE);
			NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(ent, TRUE);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, 0.f, 0.f, 0.f, FALSE, FALSE, FALSE);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ent, TRUE, TRUE);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ent);
			ENTITY::DELETE_ENTITY(&ent);
			OBJECT::DELETE_OBJECT(&ent);
		}
		const char* Menu[4]
		{
			"Kiddions", "Kiddions 2", "Desync", "Remove Gamer Card"
		};

		std::size_t Menu_Data = 0;
		const char* CrashMenu[1]
		{
			"Basic"
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
			if (Menu_DataCrash == 0) {
				std::int64_t Args1[] = { (std::int64_t)-992162568, (std::int64_t)PLAYER::PLAYER_ID() };
				g_GameFunctions->m_trigger_script_event(1, Args1, sizeof(Args1) / sizeof(Args1[0]), 1 << g_SelectedPlayer);

				std::int64_t Args2[] = { (std::int64_t)1131623211, (std::int64_t)PLAYER::PLAYER_ID(), rand() % INT64_MAX };
				g_GameFunctions->m_trigger_script_event(1, Args2, sizeof(Args2) / sizeof(Args2[0]), 1 << g_SelectedPlayer);

				std::int64_t Args3[] = { (std::int64_t)1556360603, (std::int64_t)PLAYER::PLAYER_ID(), rand() % INT64_MAX, rand() % INT64_MAX };
				g_GameFunctions->m_trigger_script_event(1, Args3, sizeof(Args3) / sizeof(Args3[0]), 1 << g_SelectedPlayer);
			}
			if (Menu_DataCrash == 1) {
				WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0xA2719263);
			}
			if (Menu_DataCrash == 2) {
				auto Ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				auto Coords = ENTITY::GET_ENTITY_COORDS(Ped, TRUE);
				auto CrashModel = rage::joaat("prop_fragtest_cnst_04");

				// Freeze them
				g_CallbackScript->AddCallback<ModelCallback>(CrashModel, [=] {
					if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
						g_GameFunctions->m_clear_ped_tasks_network(all_players.get_ped(g_SelectedPlayer), true);
					}

					while (!STREAMING::HAS_MODEL_LOADED(CrashModel)) {
						STREAMING::REQUEST_MODEL(CrashModel);
						fbr::cur()->wait(100ms);
					}

					auto Object = OBJECT::CREATE_OBJECT(CrashModel, Coords.x, Coords.y, Coords.z, TRUE, TRUE, FALSE);
					OBJECT::BREAK_OBJECT_FRAGMENT_CHILD(Object, NULL, NULL);

					fbr::cur()->wait(1s);

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(CrashModel);
					DeleteEntity(Object);
					});
				
			}

			
			

		}
		Network* get_network()
		{
			return *g_GameFunctions->m_network;
		}
		rage::rlGamerInfo* get_net_data() const
		{
			return g_GameVariables->m_net_game_player(g_SelectedPlayer) == nullptr ? nullptr : g_GameVariables->m_net_game_player(g_SelectedPlayer)->get_net_data();
		}
		
		inline rage::snPeer* get_session_peer(CNetGamePlayer* target)
		{
			for (std::uint32_t i = 0; i < get_network()->m_game_session_ptr->m_peer_count; i++)
			{
				if (get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_gamer_handle_2.m_rockstar_id == target->get_net_data()->m_gamer_handle_2.m_rockstar_id)
				{
					return get_network()->m_game_session_ptr->m_peers[i];
				}
			}

			return nullptr;
		}
		bool is_host() const
		{
			return  g_GameVariables->m_net_game_player(g_SelectedPlayer) == nullptr ? false : g_GameVariables->m_net_game_player(g_SelectedPlayer)->is_host();
		}
		bool is_host2(int p) const
		{
			return  g_GameVariables->m_net_game_player(p) == nullptr ? false : g_GameVariables->m_net_game_player(p)->is_host();
		}
		inline rage::snPlayer* GetSessionPlayer(CNetGamePlayer* target)
		{
			for (std::uint32_t i = 0; i < get_network()->m_game_session_ptr->m_player_count; i++)
			{
				if (get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == target->get_net_data()->m_host_token)
				{
					return get_network()->m_game_session_ptr->m_players[i];
				}
			}

			if (get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == target->get_net_data()->m_host_token)
				return &get_network()->m_game_session_ptr->m_local_player;

			return nullptr;
		}
		void remove(int pos) {
			if (pos == 0) {
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
			if (pos == 1) {
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
			if (pos == 2) {
				if (std::chrono::system_clock::now() - last < 10s)
				{
					return;
				}

				last = std::chrono::system_clock::now();

				auto PlayerManager = GetNetworkPlayerMgr();
				if (PlayerManager == nullptr) {
					return;
				}
				auto LocalPlayer = PlayerManager->m_local_net_player;
				auto target = g_GameFunctions->m_GetNetPlayer(g_SelectedPlayer);
				if (LocalPlayer == nullptr) {
					return;
				}
				if (target == nullptr) {
					return;
				}
				if (target == LocalPlayer) {
					return;
				}
				if (target->is_host()) {
					return;
				}

				PlayerManager->RemovePlayer(target);
				WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->m_player_id), FALSE);
				PlayerManager->UpdatePlayerListsForPlayer(LocalPlayer);
			}
			if (pos == 3) {
				auto PlayerManager = GetNetworkPlayerMgr();
				auto target = g_GameFunctions->m_GetNetPlayer(g_SelectedPlayer);
				if (PlayerManager == nullptr) {
					return;
				}
				auto LocalPlayer = PlayerManager->m_local_net_player;
				if (LocalPlayer == nullptr) {
					return;
				}
				if (target == nullptr) {
					return;
				}
				if (target == LocalPlayer) {
					return;
				}

				rage::snMsgRemoveGamersFromSessionCmd cmd{};
				cmd.m_session_id = get_network()->m_game_session_ptr->m_rline_session.m_session_id;
				cmd.m_num_peers = 1;
				cmd.m_peer_ids[0] = get_session_peer(target)->m_peer_data.m_peer_id_2;

				

				if (get_network()->m_game_session.is_host())
				{
					g_GameFunctions->m_handle_remove_gamer_cmd(get_network()->m_game_session_ptr, GetSessionPlayer(target), &cmd);
				}
				else if (target->is_host())
				{
					for (auto Player : PlayerManager->m_player_list)
					{
						if (Player != nullptr)
						{
							if (Player->is_valid())
							{
								if (Player->m_player_id != target->m_player_id)
								{
									g_GameFunctions->m_send_remove_gamer_cmd(get_network()->m_game_session_ptr->m_net_connection_mgr,
										g_GameFunctions->m_get_connection_peer(get_network()->m_game_session_ptr->m_net_connection_mgr, (int)GetSessionPlayer(Player)->m_player_data.m_peer_id_2),
										get_network()->m_game_session_ptr->m_connection_identifier, &cmd, 0x1000000);
								}
							}
						}
					}

					g_GameFunctions->m_handle_remove_gamer_cmd(get_network()->m_game_session_ptr, GetSessionPlayer(target), &cmd);
				}
				else
				{
					for (auto Player : PlayerManager->m_player_list)
					{
						if (Player != nullptr)
						{
							if (Player->is_host())
							{
								g_GameFunctions->m_send_remove_gamer_cmd(get_network()->m_game_session_ptr->m_net_connection_mgr,
									g_GameFunctions->m_get_connection_peer(get_network()->m_game_session_ptr->m_net_connection_mgr, (int)GetSessionPlayer(Player)->m_player_data.m_peer_id_2),
									get_network()->m_game_session_ptr->m_connection_identifier, &cmd, 0x1000000);
							}
						}
					}
				}

				

			}
		}
	};
}
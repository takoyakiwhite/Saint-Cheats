#pragma once
#include "Natives.hpp"
#include "ScriptCallback.hpp"
#include "Jets.h"
#include "Explode.h"
namespace Saint {
	class Notifications {
	public:
		bool leaving_and_joining = true;
		bool log = false;
		bool log_ips = false;
		bool log_rid = false;
	};
	class All_players {
	public:
		uint8_t get_id(int p) const
		{
			
			return g_GameVariables->m_net_game_player(p) == nullptr ? -1 : g_GameVariables->m_net_game_player(p)->m_player_id;
		}
		CPlayerInfo* get_player_info(int p) const
		{
			if (g_GameVariables->m_net_game_player(p) != nullptr && g_GameVariables->m_net_game_player(p)->m_player_info != nullptr)
				return g_GameVariables->m_net_game_player(p)->m_player_info;
			return nullptr;
		}
		
		Notifications notifications;
		m_Jets jet;
		Explode m_explode;
		int bounty_amount = 10000;
		void set_bounty(int i) {
			const size_t arg_count = 22;
			int64_t args[arg_count] = { (int64_t)1459520933,
				PLAYER::PLAYER_ID(),
				get_id(i),
				1,
				bounty_amount,
				0,
				1,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				*script_global(1923597).at(9).as<int64_t*>(),
				*script_global(1923597).at(10).as<int64_t*>() };

			g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << get_id(i));
		}
		void get(std::uint32_t buffer) {
			buffer = PLAYER::GET_NUMBER_OF_PLAYERS();
		}
		bool off_the_radar = false;
		void init() {
			if (off_the_radar) {
				for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
					script_global gpbd_fm_3(1894573);
					constexpr size_t arg_count = 7;
					int64_t args[arg_count] = {
						static_cast<int64_t>(1141648445),
						(int64_t)PLAYER::PLAYER_ID(),
						(int64_t)(NETWORK::GET_NETWORK_TIME() + 1),
						0,
						true,
						false,
						*gpbd_fm_3.at(i, 608).at(510).as<int64_t*>()
					};

					g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << i);
				}
			}
		}
	};
	inline All_players all_players;
}
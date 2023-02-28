#pragma once
#include "Natives.hpp"
#include "ScriptCallback.hpp"
#include "Jets.h"
#include "Explode.h"
namespace Arctic {
	class All_players {
	public:
		m_Jets jet;
		Explode m_explode;
		void get(std::uint32_t buffer) {
			buffer = PLAYER::GET_NUMBER_OF_PLAYERS();
		}
	};
	inline All_players all_players;
}
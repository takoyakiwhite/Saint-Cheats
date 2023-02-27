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
	};
	inline All_players all_players;
}
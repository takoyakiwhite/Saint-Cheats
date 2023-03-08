#pragma once
#include "UI/Interface.hpp"

namespace Saint::Lists
{
	inline const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient"
	};

	inline UserInterface::HeaderType HeaderTypesBackend[]
	{
		UserInterface::HeaderType::Static,
		UserInterface::HeaderType::YTD
	};

	inline std::size_t HeaderTypesPosition = 1;
	inline UserInterface::Outfits HeaderTypesBackend2[]
	{
		UserInterface::Outfits::Face,
		UserInterface::Outfits::Head,
		UserInterface::Outfits::Hair,
		UserInterface::Outfits::Torso,
		UserInterface::Outfits::Torso2,
		UserInterface::Outfits::Legs,
		UserInterface::Outfits::Hands,
		UserInterface::Outfits::Feet,
		UserInterface::Outfits::Eyes,
		UserInterface::Outfits::Accessories,
		UserInterface::Outfits::Vests,
		UserInterface::Outfits::Decals,
		UserInterface::Outfits::HeadProps,
	};
	inline std::size_t HeaderTypesPosition2 = 0;
	inline const char* HeaderTypesFrontend2[]
	{
		"Face",
		"Head",
		"Hair",
		"Torso",
		"Torso 2",
		"Legs",
		"Hands",
		"Feet",
		"Eyes",
		"Accessories",
		"Vests",
		"Decals",
		"Head Props"
	};
	inline std::size_t MatchPos = 1;
	inline const char* DemoList[10]
	{
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten"
	};

	inline std::size_t DemoListPos = 0;
	inline const char* DamageList[16]
	{
		"Unkown",
		"None",
		"Melee",
		"Bullet",
		"Rubber",
		"Explosive",
		"Fire",
		"Collision",
		"Fall",
		"Drown",
		"Electric",
		"Barbed Wire",
		"Fire Extinguisher",
		"Smoke",
		"Water Cannon",
		"Tranquilizer"
	};

	inline std::size_t DamagePos = 0;
}

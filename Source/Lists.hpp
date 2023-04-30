#pragma once
#include "UI/Interface.hpp"

namespace Saint::Lists
{
	inline uint32_t crash_models[] = { rage::joaat("prop_dummy_01"), rage::joaat("prop_dummy_car"), rage::joaat("prop_dummy_light"), rage::joaat("prop_dummy_plane"), rage::joaat("prop_distantcar_night"), rage::joaat("prop_distantcar_day"), 
		rage::joaat("hei_bh1_08_details4_em_night"), rage::joaat("dt1_18_sq_night_slod"), rage::joaat("ss1_12_night_slod"), -1288391198, rage::joaat("h4_prop_bush_bgnvla_med_01"), rage::joaat("h4_prop_bush_bgnvla_lrg_01"), 
		rage::joaat("h4_prop_bush_buddleia_low_01"), rage::joaat("h4_prop_bush_ear_aa"), rage::joaat("h4_prop_bush_ear_ab"), rage::joaat("h4_prop_bush_fern_low_01"), rage::joaat("h4_prop_bush_fern_tall_cc"), rage::joaat("h4_prop_bush_mang_ad"), 
		rage::joaat("h4_prop_bush_mang_low_aa"), rage::joaat("h4_prop_bush_mang_low_ab"), rage::joaat("h4_prop_bush_seagrape_low_01"), rage::joaat("prop_h4_ground_cover"), rage::joaat("h4_prop_weed_groundcover_01"), rage::joaat("h4_prop_grass_med_01"), 
		rage::joaat("h4_prop_grass_tropical_lush_01"), rage::joaat("h4_prop_grass_wiregrass_01"), rage::joaat("h4_prop_weed_01_plant"), rage::joaat("h4_prop_weed_01_row"), rage::joaat("urbanweeds02_l1"), rage::joaat("proc_forest_grass01"), 
		rage::joaat("prop_small_bushyba"), rage::joaat("v_res_d_dildo_a"), rage::joaat("v_res_d_dildo_b"), rage::joaat("v_res_d_dildo_c"), rage::joaat("v_res_d_dildo_d"), rage::joaat("v_res_d_dildo_e"), rage::joaat("v_res_d_dildo_f"), 
		rage::joaat("v_res_skateboard"), rage::joaat("prop_battery_01"), rage::joaat("prop_barbell_01"), rage::joaat("prop_barbell_02"), rage::joaat("prop_bandsaw_01"), rage::joaat("prop_bbq_3"), rage::joaat("v_med_curtainsnewcloth2"), 
		rage::joaat("bh1_07_flagpoles"), 92962485, rage::joaat("slod_human"), rage::joaat("slod_small_quadped"), rage::joaat("slod_large_quadped") };
	inline bool crash_model_check(uint32_t model) {
		for (int i = 0; i < sizeof(crash_models) / sizeof(uint32_t); i++)
		{
			if (crash_models[i] == model) return true;
		}
		return false;
	}
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
	};

	inline std::size_t HeaderTypesPosition2 = 0;
	inline std::size_t HeaderTypesPosition22 = 0;
	inline const char* HeaderTypesFrontend2[]
	{
		"Face",
		"Head",
		"Hair",
		"Torso",
		"Tops",
		"Legs",
		"Hands",
		"Feet",
		"Chains",
		"Accessories",
		"Vests",
		"Decals",
	};
	inline std::size_t HeaderTypesPosition3 = 0;
	inline std::size_t HeaderTypesPosition32 = 0;
	inline const char* HeaderTypesFrontend3[]
	{
		"Hats",
		"Glasses",
		"Ears",
		"Watches",
		"Bracelets"
	};
	inline UserInterface::Props HeaderTypesBackend3[]
	{
		UserInterface::Props::Hats,
		UserInterface::Props::Glasses,
		UserInterface::Props::Ears,
		UserInterface::Props::Watches,
		UserInterface::Props::Bracelets,
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

#pragma once
#include "Natives.hpp"
#include "FiberHelper.hpp"
#include <GTAV-Classes/ped/CPed.hpp>
#include "Math.h"
#include "ScriptCallback.hpp"
#include "CustomText.hpp"
#include "ImGui/imgui.h"
#include "Enums.h"
#include "Lists.hpp"
#include <filesystem>
#include "Vehicle.h"
#include "Players.h"
#include "All Players.h"
#include "Hooking.hpp"
#include "Render.h"
#include "hex_memory.h"
#include "ScriptLocal.h"
#include "Timer.hpp"
namespace Saint {
	inline std::string handlingBuffer = "";
	inline std::string VehNameBuffer = "";
	inline std::string ridBuffer = "";
	inline uint64_t selected_rid = 0;

	inline std::string replaceTextBuffer = "";
	inline std::string replaceTextBuffer2 = "";
	inline bool replaced = false;
	inline bool replaced2 = false;
	inline CVehicle* get_ped_vehicle() {
		return (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle;
	}
	inline bool raycast_with_cam(Cam cam, NativeVector3& raycastHitCoords) {
		bool raycastHit;
		NativeVector3 surfaceNormal;
		Entity raycastHitEntity;
		NativeVector3 camCoords = CAM::GET_CAM_COORD(cam);
		NativeVector3 cameraDirection = RotationToDirection(CAM::GET_CAM_ROT(cam, 0));
		NativeVector3 cameraMultiply = multiply(&cameraDirection, 1999999.0f);
		NativeVector3 farCoords = addn(&camCoords, &cameraMultiply);
		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &raycastHit, &raycastHitCoords, &surfaceNormal, &raycastHitEntity);
		return raycastHit;
	}
	inline bool raycast(NativeVector3& raycastHitCoords) {
		bool raycastHit;
		NativeVector3 surfaceNormal;
		Entity raycastHitEntity;
		NativeVector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		NativeVector3 cameraDirection = RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0));
		NativeVector3 cameraMultiply = multiply(&cameraDirection, 1999999.0f);
		NativeVector3 farCoords = addn(&camCoords, &cameraMultiply);
		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &raycastHit, &raycastHitCoords, &surfaceNormal, &raycastHitEntity);
		return raycastHit;
	}

	inline bool raycast(Entity& raycastHitEntity) {
		bool raycastHit;
		NativeVector3 surfaceNormal;
		NativeVector3 raycastHitCoords;
		NativeVector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		NativeVector3 cameraDirection = RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0));
		NativeVector3 cameraMultiply = multiply(&cameraDirection, 1999999.0f);
		NativeVector3 farCoords = addn(&camCoords, &cameraMultiply);
		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &raycastHit, &raycastHitCoords, &surfaceNormal, &raycastHitEntity);
		return raycastHit;
	}
	inline bool neverWantedBool = false;
	inline bool godmode = false;
	class m_all_weapons {
	public:
		const char* name[106]
		{ "Antique Cavalry Dagger", "Baseball Bat", "Broken Bottle", "Crowbar", "Unarmed", "Flashlight", "Golf Club", "Hammer", "Hatchet", "Brass Knucles", "Knife", "Machete", "Switchblade", "Nightstick", "Pipe Wrench",
			"Battle Axe", "Pool Cue", "Stone Hatchet", "Pistol", "Pistol Mk II", "Combat Pistol", "AP Pistol", "Stun Gun", "Pistol .50", "SNS Pistol", "SNS Pistol Mk II", "Heavy Pistol", "Vintage Pistol", "Flare Gun", "Marksman Pistol",
			"Heavy Revolver", "Heavy Revolver Mk II", "Double Action Revolver", "Up-n-Atomizer", "Ceramic Pistol", "Navy Revolver", "Perico Pistol", "Stun Gun",
			"Micro SMG", "SMG", "SMG Mk II", "Assault SMG", "Combat PDW", "Machine Pistol", "Mini SMG", "Unholy Hellbringer",
			"Pump Shotgun", "Pump Shotgun Mk II", "Sawed-Off Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "Double Barrel Shotgun", "Sweeper Shotgun", "Combat Shotgun",
			"Assault Rifle", "Assault Rifle Mk II", "Carbine Rifle", "Carbine Rifle Mk II", "Advanced Rifle", "Special Carbine", "Special Carbine Mk II", "Bullpup Rifle", "Bullpup Rifle Mk II", "Compact Rifle", "Military Rifle", "Heavy Rifle", "Service Carbine",
			"MG", "Combat MG", "Combat MG Mk II", "Gusenberg Sweeper",
			"Sniper Rifle", "Heavy Sniper", "Heavy Sniper Mk II", "Marksman Rifle", "Marksman Rifle Mk II", "Precision Rifle",
			"RPG", "Grenade Launcher", "Grenade Launcher Smoke", "Minigun", "Firework Launcher", "Railgun", "Homing Launcher", "Compact Grenade Launcher","Widowmaker","Compact EMP Launcher", "Grenade", "BZ Gas", "Molotov Cocktail", "Molotov Cocktail", "Proximity Mines",
			"Snowballs", "Pipe Bombs", "Baseball", "Tear Gas", "Flare", "Jerry Can", "Parachute", "Fire Extinguisher", "Hazardous Jerry Can", "Fertilizer Can", "Candy Cane", "Acid Package"};
		std::uint32_t hash[106]
		{ 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
			0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
			0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
			0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
			0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A, 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0xAB564B93,
			0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, 0x34A67B97, 0xFBAB5776, 0xFBAB5776, 0xBA536372, 0x184140A1, 0x6589186A, 0xF7F1E25E
		};

		const char* name_all[107]
		{	"All", "Antique Cavalry Dagger", "Baseball Bat", "Broken Bottle", "Crowbar", "Unarmed", "Flashlight", "Golf Club", "Hammer", "Hatchet", "Brass Knucles", "Knife", "Machete", "Switchblade", "Nightstick", "Pipe Wrench",
			"Battle Axe", "Pool Cue", "Stone Hatchet", "Pistol", "Pistol Mk II", "Combat Pistol", "AP Pistol", "Stun Gun", "Pistol .50", "SNS Pistol", "SNS Pistol Mk II", "Heavy Pistol", "Vintage Pistol", "Flare Gun", "Marksman Pistol",
			"Heavy Revolver", "Heavy Revolver Mk II", "Double Action Revolver", "Up-n-Atomizer", "Ceramic Pistol", "Navy Revolver", "Perico Pistol", "Stun Gun",
			"Micro SMG", "SMG", "SMG Mk II", "Assault SMG", "Combat PDW", "Machine Pistol", "Mini SMG", "Unholy Hellbringer",
			"Pump Shotgun", "Pump Shotgun Mk II", "Sawed-Off Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "Double Barrel Shotgun", "Sweeper Shotgun", "Combat Shotgun",
			"Assault Rifle", "Assault Rifle Mk II", "Carbine Rifle", "Carbine Rifle Mk II", "Advanced Rifle", "Special Carbine", "Special Carbine Mk II", "Bullpup Rifle", "Bullpup Rifle Mk II", "Compact Rifle", "Military Rifle", "Heavy Rifle", "Service Carbine",
			"MG", "Combat MG", "Combat MG Mk II", "Gusenberg Sweeper",
			"Sniper Rifle", "Heavy Sniper", "Heavy Sniper Mk II", "Marksman Rifle", "Marksman Rifle Mk II", "Precision Rifle",
			"RPG", "Grenade Launcher", "Grenade Launcher Smoke", "Minigun", "Firework Launcher", "Railgun", "Homing Launcher", "Compact Grenade Launcher","Widowmaker","Compact EMP Launcher", "Grenade", "BZ Gas", "Molotov Cocktail", "Molotov Cocktail", "Proximity Mines",
			"Snowballs", "Pipe Bombs", "Baseball", "Tear Gas", "Flare", "Jerry Can", "Parachute", "Fire Extinguisher", "Hazardous Jerry Can", "Fertilizer Can", "Candy Cane", "Acid Package" };
		std::uint32_t hash_all[107]
		{	0x11111, 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
			0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
			0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
			0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
			0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A, 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0xAB564B93,
			0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, 0x34A67B97, 0xFBAB5776, 0xFBAB5776, 0xBA536372, 0x184140A1, 0x6589186A, 0xF7F1E25E
		};
	};
	inline m_all_weapons all_weapons;
	class NoClip {
	public:
		bool enabled = false;
		bool WorkForVehicles = true;
		bool StopAfterNoInput = true;
		bool SetRotation = false;
		bool DisableCollision = true;
		float speed = 2.5f;
		bool transparent = false;
		bool spin = false;
		const char* FlyType[2]
		{
			"None", "T-Pose"
		};

		std::size_t FlyInt = 0;
		void onDisable() {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
				if (DisableCollision) {
					ENTITY::SET_ENTITY_COLLISION(veh, true, true);
				}
			}
		}
		void init() {
			if (enabled) {
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					static bool turnoff = true;
					if (!transparent)
					{
						ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), 255, false);
						turnoff = false;
					}
					if (transparent) {
						ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), 180, false);
					}
					if (spin) {
						static int Heading;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						Heading++;
						ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), Heading);
					}

					NativeVector3 coords4 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
					NativeVector3 coords5 = CAM::GET_GAMEPLAY_CAM_COORD();
					auto ped = PLAYER::PLAYER_PED_ID();
					auto startDist = std::distance(&coords5, &coords4);
					auto pos = ENTITY::GET_ENTITY_COORDS(ped, false);
					if (FlyInt == 1) {
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, false, false, false);
					}
					if (FlyInt == 0) {
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, true, true, true);
					}
					NativeVector3 meow2 = CAM::GET_GAMEPLAY_CAM_ROT(0);
					NativeVector3 meow = rot_to_direction(&meow2);
					NativeVector3 coords6 = multiply(&meow, speed);


					if (GetAsyncKeyState(0x57) || PAD::IS_CONTROL_PRESSED(2, 32))
					{
						NativeVector3 pos = addn(&coords4, &coords6);
						if (FlyInt == 1) {
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), pos.x, pos.y, pos.z, false, false, false);
						}
						if (FlyInt == 0) {
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), pos.x, pos.y, pos.z, true, true, true);
						}
					}
					if (SetRotation) {
						NativeVector3 rotation = CAM::GET_GAMEPLAY_CAM_ROT(0);
						ENTITY::SET_ENTITY_ROTATION(PLAYER::PLAYER_PED_ID(), rotation.x, rotation.y, rotation.z, 2, 1);
					}
				}
				else
				{
					if (WorkForVehicles)
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						VEHICLE::SET_VEHICLE_GRAVITY(veh, !(enabled && !StopAfterNoInput));
						NativeVector3 cam_pos = CAM::GET_GAMEPLAY_CAM_ROT(0);
						ENTITY::SET_ENTITY_ROTATION(veh, cam_pos.x, cam_pos.y, cam_pos.z, 1, TRUE);
						if (DisableCollision) {
							ENTITY::SET_ENTITY_COLLISION(veh, false, false);
						}
						if (!DisableCollision) {
							if (ENTITY::GET_ENTITY_COLLISION_DISABLED(PLAYER::PLAYER_PED_ID())) {
								ENTITY::SET_ENTITY_COLLISION(veh, true, true);
							}
						}
						Player play(PLAYER::PLAYER_ID());
						if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 32))
						{
							!StopAfterNoInput ? ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0.0f, 150.f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1) : VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, !IsKeyPressed(VK_SHIFT) ? speed * 200 : speed * 200 * 2);
						}
						if (PAD::IS_CONTROL_PRESSED(2, 33))
						{
							!StopAfterNoInput ? ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0.0f, 0 - (!IsKeyPressed(VK_SHIFT) ? speed : speed * 2), 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1) : VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0 - (!IsKeyPressed(VK_SHIFT) ? speed * 200 : speed * 200 * 2));
						}
						if (PAD::IS_CONTROL_PRESSED(2, 63))
						{
							!StopAfterNoInput ? ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, (!IsKeyPressed(VK_SHIFT) ? 0 - speed : (0 - speed) * 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1) : ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0 - (!IsKeyPressed(VK_SHIFT) ? speed * 200 : speed * 200 * 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
						}
						if (PAD::IS_CONTROL_PRESSED(2, 64))
						{
							!StopAfterNoInput ? ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, !IsKeyPressed(VK_SHIFT) ? speed : speed * 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1) : ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, !IsKeyPressed(VK_SHIFT) ? speed * 200 : speed * 200 * 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
						}
						if (!PAD::IS_CONTROL_PRESSED(2, 64) && !PAD::IS_CONTROL_PRESSED(2, 63) && !PAD::IS_CONTROL_PRESSED(2, 72) && !PAD::IS_CONTROL_PRESSED(2, 71) && StopAfterNoInput)
						{
							//VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0f);
						}
						if (StopAfterNoInput && !PAD::IS_CONTROL_PRESSED(2, 71) && !PAD::IS_CONTROL_PRESSED(2, 72)) VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0f);
					}
				}
			}

		}
	};
	inline NoClip no_clip;
	class Invisible {
	public:
		bool enabled = false;
		bool local_visible = false;
		void init() {
			if (enabled) {
				if (local_visible) {
					NETWORK::SET_ENTITY_LOCALLY_VISIBLE(PLAYER::PLAYER_PED_ID());
				}
				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, false);
			}

		}
	};
	inline Invisible invisible;
	class Bodygaurd {
	public:
		bool godmode = false;
		
		std::size_t WeaponInt = 0;
		int accuary = 75;

		//models
		const char* Models[3]
		{ "FIB", "Cop", "Blackops" };
		const char* ModelHashes[3]
		{ "mp_m_fibsec_01", "s_m_y_cop_01", "s_m_y_blackops_01" };
		std::size_t ModelInt = 0;

		//firing pattern
		bool FiringPatternEnabled = false;
		const char* FiringPattern[7]
		{ "Burst", "Full Auto", "Pistol", "Shotgun", "Slow Fire Tank", "Rifle", "Delayed By One Second" };
		std::uint32_t FiringPatternHashes[7]
		{ 0xD6FF6D61 , 0xC6EE6B4C, 0xA018DB8A, 0x00BAC39B, 0xE2CA3A71, 0x9C74B406, 0x7A845691 };
		std::size_t FiringPatternInt = 0;

		float damagemultiplier = 1.0f;
	};
	inline Bodygaurd bodygaurd;
	inline bool disableLockOn = false;
	class Acceleration {
	public:
		bool enabled = false;
		float speed = 5.0f;
		void init() {
			if (enabled) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, 1) == PLAYER::PLAYER_PED_ID())
				{

					if (PAD::IS_CONTROL_PRESSED(2, 71)) {
						if (!VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh))) {
							if (VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veh)) {
								ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0.0, (float)(((speed - 1.0f) * 2.1f) / 69.0f), 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
							}
						}
					}

				}
			}
		}
	};
	inline Acceleration acceleration;
	class HornBoost {
	public:
		bool enabled = false;
		bool smooth = false;
		bool onlyOnGround = false;
		const char* Boost_Type[2] = { "Forward", "Jump" };
		std::size_t Boost_Int = 0;
		int speed = 0;
		float boost_power = 1.0f;
		void init() {
			if (enabled) {
				if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
				{
					if (Boost_Int == 0)
					{
						Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						if (onlyOnGround && !VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(playerVehicle)) {

						}
						else {
							if (smooth) {
								if (ENTITY::GET_ENTITY_SPEED(playerVehicle) < speed) {
									VEHICLE::SET_VEHICLE_FORWARD_SPEED(playerVehicle, ENTITY::GET_ENTITY_SPEED(playerVehicle) + boost_power);
								}
							}
							else {
								VEHICLE::SET_VEHICLE_FORWARD_SPEED(playerVehicle, speed);
							}
						}


					}
					if (Boost_Int == 1)
					{
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(vehicle), 0 + ENTITY::GET_ENTITY_FORWARD_Y(vehicle), 0.5f, 0, 0, 0, 1, 0, 1, 1, 1, 1);

					}
				}
			}
		}
	};
	inline HornBoost hornboost;
	inline bool NoPlaneTurbulance = false;

	class superJump {
	public:
		bool enabled = false;
		bool add_force = false;
		const char* Jump_Type[2] = { "Normal", "Beast"};
		std::size_t Jump_Int = 0;
		void init() {
			if (enabled) {
				if (Jump_Int == 0) {
					MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
				}
				if (Jump_Int == 1) {
					if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) && !ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_DOING_A_BEAST_JUMP(PLAYER::PLAYER_PED_ID()))
						if (PAD::IS_CONTROL_JUST_PRESSED(0, 22))
							TASK::TASK_JUMP(PLAYER::PLAYER_PED_ID(), true, true, true);
				}
				if (add_force) {
					if (PED::IS_PED_JUMPING(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_RAGDOLL(PLAYER::PLAYER_PED_ID())) {
						ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 0.f, 1.5f, 0.f, 0.f, 0.f, 0.f, 1, true, true, true, false, true);
					}
				}
			}
		}
	};
	inline superJump superjump;
	class Upgrades {
	public:
		const char* types[3] = { "All", "Visual", "Performance" };
		std::size_t data = 0;
		void apply(int type) {

			switch (type) {
			case 0:
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					VEHICLE::SET_VEHICLE_MOD_KIT(playerVehicle, 0);
					for (int i = 0; i < 50; i++)
					{
						VEHICLE::SET_VEHICLE_MOD(playerVehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(playerVehicle, i) - 1), false);

					}
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
				}
			case 1:
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					VEHICLE::SET_VEHICLE_MOD_KIT(playerVehicle, 0);
					for (int i = 0; i < 10; i++)
					{
						VEHICLE::SET_VEHICLE_MOD(playerVehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(playerVehicle, i) - 1), false);

					}
					for (int i = 19; i < 49; i++)
					{
						VEHICLE::SET_VEHICLE_MOD(playerVehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(playerVehicle, i) - 1), false);

					}

					//VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
				}
			case 2:
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					VEHICLE::SET_VEHICLE_MOD_KIT(playerVehicle, 0);
					for (int i = 11; i < 18; i++)
					{
						VEHICLE::SET_VEHICLE_MOD(playerVehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(playerVehicle, i), false);

					}
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));


				}
			}
			data = type;
			g_Render->m_SubmenuStack.pop();
		}
	};
	inline Upgrades m_upgrades;
	inline const char* sound_type[9] = { "Schafter V12", "Coquette", "Banshee", "Tempesta", "Casco", "Tyrus", "Carbonizzare", "I-Wagen (Eletric)", "Space Docker" };
	inline const char* sound_data[9] = { "schafter3", "coquette", "banshee2", "tempesta", "casco", "tyrus", "carbonizzare", "iwagen", "dune2" };
	inline std::size_t sound_int = 0;
	inline const char* animation_type[3] = { "Gangster", "Cowboy", "Default" };
	inline const char* animation_data[3] = { "Gang1H", "Hillbilly", "Default" };
	inline std::size_t  animation_int = 0;
	inline const char* acrobatic_type[4] = { "Backflip", "Frontflip", "Kickflip", "Bunny Hop" };
	inline std::size_t acrobatic_int = 0;
	inline const char* jump_type[2] = { "Normal", "Beast" };
	inline std::size_t jump_int = 0;
	class Weather {
	public:
		const char* data[14] = { "Extra Sunny", "Clouds", "Smog", "Foggy", "Overcast", "Rain", "Clearing", "Neutral", "Snow", "Blizzard", "Snow (Light)", "Christmas", "Halloween", "Clear" };
		const char* type[6] = { "BLIZZARD", "CLEAR", "HALLOWEEN", "NEUTRAL", "XMAS", "RAIN"};
		std::size_t init = 0;
		bool randomize = false;
		int randomize_delay = 550;
		void override(const char* type) {
			MISC::SET_WEATHER_TYPE_NOW_PERSIST(type);
		}
		int delay2 = 0;
		void init2() {
			if (randomize) {
				
				if (delay2 == 0 || (int)(GetTickCount64() - delay2) > randomize_delay)
				{

					MISC::SET_WEATHER_TYPE_NOW_PERSIST(type[MISC::GET_RANDOM_INT_IN_RANGE(0, 6)]);
					delay2 = GetTickCount64();
				}
			}
		}
	};
	inline Weather weather;
	class targeting_mode {
	public:
		const char* data[4]{ "Assisted Aim - Full",
		"Assisted Aim - Partial",
		"Free Aim - Assisted",
		"Free Aim" };
		std::size_t init = 0;

	};
	inline targeting_mode t_mode;
	inline bool get_blip_location(NativeVector3& location, int sprite, int color = -1)
	{
		Blip blip;
		for (
			blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite);
			HUD::DOES_BLIP_EXIST(blip) && color != -1 && HUD::GET_BLIP_COLOUR(blip) != color;
			blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite)
			);

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color)) return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}
	inline NativeVector3 GetBlipIcon()
	{
		static NativeVector3 zero;
		NativeVector3 coords;

		bool blipFound = false;
		// search for marker blip
		int blipIterator = HUD::GET_WAYPOINT_BLIP_ENUM_ID();
		for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blipIterator))
		{
			if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4)
			{
				coords = HUD::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound)
		{
			return coords;
		}

		return zero;
	}
	inline bool get_objective_location(NativeVector3& location)
	{
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission)) return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission2)) return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Mission)) return true;
		if (get_blip_location(location, (int)BlipIcons::RaceFinish, (int)BlipColors::None)) return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Green)) return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Blue)) return true;
		if (get_blip_location(location, (int)BlipIcons::CrateDrop)) return true;

		static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };
		for (const auto& blip : blips)
		{
			if (get_blip_location(location, blip, 5)) return true;
		}

		return false;
	}
	class Autopilot {
	public:
		std::string avoid_roads_name = "Slot 3";
		bool wreckless = true;
		bool avoid_roads = false;
		int avoid_roads_flag = 20972036;
		std::string avoid_roads_buffer;
		int wreckless_flag = 786972;
		std::string wreckless_buffer;
		int nonwreckless_flag = 387;
		std::string nonwreckless_flag_buffer;
		float speed = 100.f;
		float stop_range = 50.f;
		const char* destination[3] = { "Waypoint", "Objective", "Wander" };
		std::size_t destination_i = 0;
	};
	inline Autopilot autopilot;
	class Give_weapon {
	public:
		const char* type[90]
		{ "All", "Antique Cavalry Dagger", "Baseball Bat", "Broken Bottle", "Crowbar", "Unarmed", "Flashlight", "Golf Club", "Hammer", "Hatchet", "Brass Knucles", "Knife", "Machete", "Switchblade", "Nightstick", "Pipe Wrench",
			"Battle Axe", "Pool Cue", "Stone Hatchet", "Pistol", "Pistol Mk II", "Combat Pistol", "AP Pistol", "Stun Gun", "Pistol .50", "SNS Pistol", "SNS Pistol Mk II", "Heavy Pistol", "Vintage Pistol", "Flare Gun", "Marksman Pistol",
			"Heavy Revolver", "Heavy Revolver Mk II", "Double Action Revolver", "Up-n-Atomizer", "Ceramic Pistol", "Navy Revolver", "Perico Pistol", "Stun Gun",
			"Micro SMG", "SMG", "SMG Mk II", "Assault SMG", "Combat PDW", "Machine Pistol", "Mini SMG", "Unholy Hellbringer",
			"Pump Shotgun", "Pump Shotgun Mk II", "Sawed-Off Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "Double Barrel Shotgun", "Sweeper Shotgun", "Combat Shotgun",
			"Assault Rifle", "Assault Rifle Mk II", "Carbine Rifle", "Carbine Rifle Mk II", "Advanced Rifle", "Special Carbine", "Special Carbine Mk II", "Bullpup Rifle", "Bullpup Rifle Mk II", "Compact Rifle", "Military Rifle", "Heavy Rifle", "Service Carbine",
			"MG", "Combat MG", "Combat MG Mk II", "Gusenberg Sweeper",
			"Sniper Rifle", "Heavy Sniper", "Heavy Sniper Mk II", "Marksman Rifle", "Marksman Rifle Mk II", "Precision Rifle",
			"RPG", "Grenade Launcher", "Grenade Launcher Smoke", "Minigun", "Firework Launcher", "Railgun", "Homing Launcher", "Compact Grenade Launcher","Widowmaker","Compact EMP Launcher" };
		std::uint32_t data[90]
		{ 0x11111, 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
		0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
		0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
		0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
		0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A };
		std::size_t type_int = 0;
		int amount = 9999;
	};
	inline Give_weapon give_weapon;
	class Give_ammo {
	public:
		const char* type[2] = { "All", "Current" };
		std::size_t type_int = 0;
		int amount = 9999;
	};
	inline Give_ammo give_ammo;
	inline bool has_string_attached(std::string str, std::string check)
	{
		std::size_t found = str.find(' ');
		if (found != std::string::npos)
		{
			if (str.substr(0, found) == check)
			{
				str = str.substr(found + 1, str.size());
				return true;
			}
		}
		else
		{
			if (str == check)
				return true;
		}
		return false;
	}
	inline std::string separateByCommas2(int num) {
		std::string numStr = std::to_string(num);
		std::string result;
		int count = 0;

		// Iterate through the string from the right and add commas
		for (int i = numStr.size() - 1; i >= 0; i--) {
			result = numStr[i] + result;
			count++;
			if (count == 3 && i != 0) {
				result = "," + result;
				count = 0;
			}
		}

		return result;
	}
	class Features {
	public:
		bool vehicle_godmode = false;
		bool auto_parachute = false;
		bool seatbelt = false;
		bool off_the_radar = false;
		bool teleport_gun = false;
		const char* teleport_gun_type[2] = { "Smooth", "Rough" };
		std::size_t teleport_gun_int = 0;
		const char* veh_density[2] = { "None", "Normal" };
		std::size_t vden_pos = 0;
		bool delete_gun = false;
		bool infinite_ammo = false;
		bool spectate = false;
		bool pickup_mode = false;
		bool autoclean = false;
		bool swim_anywhere = false;
		bool tiny_ped = false;
		bool unlim = false;
		bool attack_friendly = false;
		bool reduced = false;
		bool bound_ankles = false;
		bool ignored = false;
		bool no_recoil = false;
		bool keep_engine_on = false;
		bool auto_repair = false;
		const char* auto_repair_type[2] = {"Smart", "Constant"};
		std::size_t get_repair_type = 0;
		bool match = false;
		bool bypass_c4_limit = false;
		bool remove_def = false;
		bool stick_to_ground = false;
		bool burned = false;
		bool infiniter = false;
		bool drugs = false;
		bool no_ragdoll = false;
		bool invisible_car = false;
		bool invisible_carlocal_visible = false;
		int boost_speed = 150;
		bool disable_lock_on = false;
		bool aim_tracer = false;
		bool walk_underwater = false;
		bool push_water_away = false;
		bool is_free_aiming() {
			return PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 78, true);
		}
		bool slide_run = false;
		bool force_gun = false;
		int force_gun_mult = 150;
		bool move_with_mouse = false;
		bool disable_wanted_stars = false;
		int fake_wanted_levels = 0;
		bool hide_hsw_mods = false;
		bool disable_camber = false;
		bool no_idle_kick = false;
		bool show_skidmarks = false;
		bool wet = false;
		bool reveal_all_players = false;
		bool hide_map = false;
		bool use_stunt_jump_camera = false;
		bool nigthclub300k = false;
		bool stop_cut = false;
		bool no_grav_veh = false;
		bool clean_veh = false;
		float forklight_height = 0.0f;
		bool can_be_used_by_peds = false;
		bool ragdoll_on_q = false;
		std::size_t bullet_int = 0;
		void init() {
			if (ragdoll_on_q) {
				if (GetAsyncKeyState(0x51) & 1) {
					NativeVector3 v = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::PLAYER_PED_ID());
					PED::SET_PED_TO_RAGDOLL_WITH_FALL(PLAYER::PLAYER_PED_ID(), 1500, 2000, 1, -v.x, -v.y, -v.z, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
				}
			}
			if (can_be_used_by_peds) {
				VEHICLE::SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
			}
			if (clean_veh) {
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0.0);
			}
			if (no_grav_veh) {
				VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
			}
			if (stop_cut) {
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			}
			if (nigthclub300k) {
				*script_global(262145 + 24045).as<int*>() = 300000;
				*script_global(262145 + 24041).as<int*>() = 300000;
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_POPULARITY"), 10000, true);
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_PAY_TIME_LEFT"), -1, true);
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_POPULARITY"), 100000, true);
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLUB_POPULARITY"), 10000, true);
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLUB_PAY_TIME_LEFT"), -1, true);
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLUB_POPULARITY"), 100000, true);
			}
			if (use_stunt_jump_camera) {
				CAM::USE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE();
			}
			if (hide_map) {
				HUD::DISPLAY_RADAR(false);
			}
			if (reveal_all_players) {
				*script_global(2657589).at(PLAYER::PLAYER_ID(), 466).at(213).as<std::int32_t*>() = 1;
				*script_global(2672505).at(58).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME() + 60;
			}
			if (wet) {
				PED::SET_PED_WETNESS_ENABLED_THIS_FRAME(PLAYER::PLAYER_PED_ID());
				PED::SET_PED_WETNESS_HEIGHT(PLAYER::PLAYER_PED_ID(), 10.0);
			}
			if (show_skidmarks) {
				GRAPHICS::USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(true);
			}
			if (no_idle_kick) {
				*script_global(1653913).at(1172).as<int*>() = -1; 
				*script_global(1653913).at(1156).as<int*>() = -1;
			}
			if (disable_camber) {
				VEHICLE::SET_CAN_USE_HYDRAULICS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
			}
			if (disable_wanted_stars) {
				HUD::HIDE_HUD_COMPONENT_THIS_FRAME(1);
			}
			if (move_with_mouse) {
				g_Settings.m_LockMouse = true;
				Vector2 pos = g_Render->GetMousePos();
				g_Render->m_PosX = pos.x / 2830;
				g_Render->m_PosY = pos.y / 2370;
			}
			if (force_gun) {
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					Entity hitEntity;
					if (raycast(hitEntity)) {
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(hitEntity, force_gun_mult);
					}
				}
				
				
			}
			if (slide_run) {
				if (TASK::IS_PED_RUNNING(PLAYER::PLAYER_PED_ID()) || TASK::IS_PED_SPRINTING(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_RAGDOLL(PLAYER::PLAYER_PED_ID())) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 0.f, 1.5f, 0.f, 0.f, 0.f, 0.f, 1, true, true, true, false, true);
				}
			}
			if (walk_underwater)
			{
				if (ENTITY::IS_ENTITY_IN_WATER(PLAYER::PLAYER_PED_ID()))
				{
					PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 65, false);
					PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 66, false);
					PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 168, false);

					NativeVector3 PlayerPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
					

					if (PED::IS_PED_JUMPING(PLAYER::PLAYER_PED_ID()))
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), true, 0, 0, 0.7f, 0, 0, 0, true, true, true, true, false, true);
					}

					if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(PLAYER::PLAYER_PED_ID()) > 1)
					{
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 60, false);
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 61, false);
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 104, false);
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 276, false);
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 76, true);
						ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), true, 0, 0, -0.7f, 0, 0, 0, true, true, true, true, false, true);
					}

					if (TASK::GET_IS_TASK_ACTIVE(PLAYER::PLAYER_PED_ID(), 281) || PED::IS_PED_SWIMMING(PLAYER::PLAYER_PED_ID()) || PED::IS_PED_SWIMMING_UNDER_WATER(PLAYER::PLAYER_PED_ID()))
					{
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
					}
				}
			}
			if (push_water_away)
			{
				NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				for (int i = -8; i <= 15; i++)
				{
					for (int j = -8; j <= 15; j++)
					{
						WATER::MODIFY_WATER(Coords.x + i, Coords.y + j, -8, 8);
					}
				}
			}
			if (aim_tracer) {
				Vector3 minV, maxV;
					Hash weapHash;

					Entity weap = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0);
					WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weapHash, 1);
					NativeVector3 pos = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(weap, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(weap, "gun_muzzle"));
					NativeVector3 rot = ENTITY::GET_ENTITY_ROTATION(weap, 2);
					Entity get_ent;
					if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_PED_ID(), &get_ent)) {
						NativeVector3 hitCoords;
						if (raycast(hitCoords)) {
							GRAPHICS::DRAW_LINE(pos.x, pos.y, pos.z, hitCoords.x, hitCoords.y, hitCoords.z, 255, 0, 0, 255);
						}
					}
					else {
						if (is_free_aiming()) {
							NativeVector3 hitCoords;
							if (raycast(hitCoords)) {
								GRAPHICS::DRAW_LINE(pos.x, pos.y, pos.z, hitCoords.x, hitCoords.y, hitCoords.z, 255, 255, 255, 255);
							}
						}
					}


				
			}
			if (disable_lock_on) {
				auto g_local_player = (*g_GameFunctions->m_pedFactory)->m_local_ped;
				if (g_local_player && g_local_player->m_vehicle)
					g_local_player->m_vehicle->m_is_targetable = false;
			}
			if (invisible_car) {
				if (invisible_carlocal_visible) {
					NETWORK::SET_ENTITY_LOCALLY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
				}
				ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false, false);
			}
			if (no_ragdoll) {
				PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false);
			}
			if (drugs) {
				GRAPHICS::ENABLE_ALIEN_BLOOD_VFX(true);
				GRAPHICS::ANIMPOSTFX_PLAY("DrugsMichaelAliensFight", 9999999, false);
				//stop
				//GRAPHICS::ANIMPOSTFX_STOP("DrugsMichaelAliensFight");
			}
			if (infiniter) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				if (VEHICLE::GET_HAS_ROCKET_BOOST(veh))
				{
					//VEHICLE::SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(veh, 0);

					VEHICLE::SET_ROCKET_BOOST_FILL(veh, 100.0f);

				}
			}
			if (burned) {
				ENTITY::SET_ENTITY_RENDER_SCORCHED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
			}
			if (stick_to_ground) {
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, 0);
			}
			if (remove_def) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);

			}
			if (bypass_c4_limit) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->fired_sticky_bombs = 0;

			}
			if (match) {
				Lists::MatchPos = g_Render->ThemeIterator;
				switch (g_Render->ThemeIterator) {
				case 0:
					g_Render->m_ToggleOnColor = { 138, 43, 226, 255 };
					break;
				case 1:
					g_Render->m_ToggleOnColor = { 255, 108, 116, 255 };
					break;
				case 2:
					g_Render->m_ToggleOnColor = { 15, 82, 186, 255 };
					break;
				case 3:
					g_Render->m_ToggleOnColor = { 24, 26, 24, 255 };
					break;
				case 4:
					g_Render->m_ToggleOnColor = { 0, 155, 119, 255 };
					break;
				case 5:
					g_Render->m_ToggleOnColor = { 70, 38, 180, 255 };
					break;
				case 6:
					g_Render->m_ToggleOnColor = { 255, 145, 164, 255 };
					break;
				case 7:
					g_Render->m_ToggleOnColor = { 17, 17, 17, 255 };
					break;
				}
			}
			if (auto_repair) {
				if (get_repair_type == 0) {

					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
					{
						Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(playerVehicle)) {
							VEHICLE::SET_VEHICLE_FIXED(playerVehicle);
							VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(playerVehicle);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVehicle, false);
						}
						
					}
					
				}
				if (get_repair_type == 1) {
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
					{
						Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						VEHICLE::SET_VEHICLE_FIXED(playerVehicle);
						VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(playerVehicle);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVehicle, false);
					}
				}

			}
			if (keep_engine_on) {
				Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				VEHICLE::SET_VEHICLE_ENGINE_ON(playerVehicle, true, true, true);
			}
			if (no_recoil) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_explosion_shake_amplitude = 0.0f;
			}
			if (ignored) {
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;
				Ped* peds = new Ped[ArrSize];
				peds[0] = ElementAmount;
				int PedFound = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);
				for (int i = 0; i < PedFound; i++)
				{
					int OffsetID = i * 2 + 2;
					Ped ped = peds[OffsetID];
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
					PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
					PED::SET_PED_FLEE_ATTRIBUTES(ped, 0, false);
					PED::SET_PED_COMBAT_ATTRIBUTES(ped, 17, true);
				}
				PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), true);
				PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), true);
				PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(PLAYER::PLAYER_ID(), false);
				PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(PLAYER::PLAYER_ID(), true);
			}
			if (bound_ankles) {
				PED::SET_ENABLE_BOUND_ANKLES(PLAYER::PLAYER_PED_ID(), true);
			}
			if (reduced) {
				PED::SET_PED_CAPSULE(PLAYER::PLAYER_PED_ID(), 0.001);
			}
			if (attack_friendly) {
				PED::SET_CAN_ATTACK_FRIENDLY(PLAYER::PLAYER_PED_ID(), true, true);
			}
			if (unlim) {
				PLAYER::SPECIAL_ABILITY_FILL_METER(PLAYER::PLAYER_ID(), true, 0);
			}
			if (tiny_ped) {
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, true);
			}
			if (swim_anywhere) {
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 65, true);
			}
			if (autoclean) {
				PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
				PED::RESET_PED_VISIBLE_DAMAGE(PLAYER::PLAYER_PED_ID());
			}
			if (pickup_mode) {
				static bool Locked = false;
				HUD::DISPLAY_SNIPER_SCOPE_THIS_FRAME();

				PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false);



				Entity target;

				if (Locked) {
					if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &target) && PAD::IS_CONTROL_PRESSED(0, 25)) {
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);
						if (ENTITY::IS_ENTITY_A_PED(target) && PED::IS_PED_IN_ANY_VEHICLE(target, true)) {
							target = PED::GET_VEHICLE_PED_IS_IN(target, false);
						}



						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(target);

						NativeVector3 gameplayCam = CAM::GET_GAMEPLAY_CAM_COORD();
						NativeVector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
						NativeVector3 camera_direction = RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0));
						NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
						NativeVector3 multiply2 = multiply(&camera_direction, (DistanceBetweenVector3(&gameplayCam, &self_coords) + 6));
						NativeVector3 set_position = addn(&gameplayCam, &multiply2);

						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, set_position.x, set_position.y, set_position.z, false, false, false);

						if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 24)) {



							ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, camera_direction.x * 10000.0f, camera_direction.y * 10000.0f, camera_direction.z * 10000.0f, 0.0f, 0.0f, 0.0f, 0, false, true, true, false, true);
							Locked = false;
							PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);

						}
					}
				}

				if (!PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &target)) {
					Locked = true;
					PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
				}
			}
			if (spectate) {
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));

				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
				ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);

				STREAMING::SET_FOCUS_ENTITY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
			}

			if (infinite_ammo) {
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true);
			}

			if (delete_gun) {
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					Entity hitEntity;
					if (raycast(hitEntity)) {
						ENTITY::SET_ENTITY_COORDS(hitEntity, 6400.f, 6400.f, 0.f, false, false, false, false);
					}
				}
			}
			if (teleport_gun) {
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					NativeVector3 c;
					if (raycast(c)) {
						if (teleport_gun_int == 0) {
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z, true, true, true);
						}
						if (teleport_gun_int == 1) {
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z, false, false, false);
						}
					}
				}
			}

			if (seatbelt) {
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), true);
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, false);
			}

			if (auto_parachute) {
				if (PED::GET_PED_PARACHUTE_STATE(PLAYER::PLAYER_PED_ID()) == 0)
				{
					PED::FORCE_PED_TO_OPEN_PARACHUTE(PLAYER::PLAYER_PED_ID());

				}
			}
			if (vehicle_godmode) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					ENTITY::SET_ENTITY_INVINCIBLE(playerVehicle, true);
					ENTITY::SET_ENTITY_PROOFS(playerVehicle, true, true, true, true, true, true, true, true);
					VEHICLE::SET_VEHICLE_DAMAGE(playerVehicle, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, false);
					//VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(playerVehicle);
					//VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVehicle, 0.0f);
					VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(playerVehicle, true);
					VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(playerVehicle, true);
					VEHICLE::SET_VEHICLE_BODY_HEALTH(playerVehicle, 1000.0f);
					VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(playerVehicle, !true);
					VEHICLE::SET_VEHICLE_CAN_BREAK(playerVehicle, !true);
					VEHICLE::SET_VEHICLE_ENGINE_HEALTH(playerVehicle, 1000.0f);
					VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(playerVehicle, !true);
					VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(playerVehicle, !true);
					VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(playerVehicle, 1000.0f);
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVehicle, !true);
					VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(playerVehicle, !true);
				}
			}

		}
	};

	inline Features features;
	class ExplosiveAmmo {
	public:
		bool enabled = false;
		bool invisible = false;
		bool sound = true;
		float damage = 1.0f;
		float camera_shake = 0.0f;
		int blamed_person = 0;
		bool blame = false;
		const char* explode_type[81] = { "Grenade", "Grenade (Launcher)", "Sticky Bomb", "Molotov", "Rocket", "Tank Shell", "HI Octane", "Car", "Plane", "Gas Pump", "Bike", "Steam", "Flame", "Water", "Gas", "Boat", "Ship Destroy", "Truck", "Bullet", "Smoke", "Smoke 2", "BZ Gas", "Flare",
			"Unknown", "Extinguisher", "Unknown", "Train", "Barrel", "Propane", "Blimp", "Flame 2", "Tanker", "Plane Rocket", "Vehicle Bullet", "Gas Tank", "Bird Crap", "Railgun", "Blimp 2", "Firework", "Snowball", "Proximity Mine", "Valkyrie Cannon", "Air Defense", "Pipe Bomb",
			"Vehicle Mine", "Explosive Ammo", "APC Shell", "Cluster Bomb", "Gas Bomb", "Incendiary Bomb", "Bomb", "Torpedo", "Torpedo (Underwater)", "Bombushka Cannon", "Cluster Bomb 2", "Hunter Barrage", "Hunter Cannon", "Rouge Cannon", "Underwater Mine", "Orbital Cannon",
			"Bomb (Wide)", "Explosive Ammo (Shotgun)", "Oppressor MK II", "Kinetic Mortar", "Kinetic Vehicle Mine", "EMP Vehicle Mine", "Spike Vehicle Mine", "Slick Vehicle Mine", "Tar Vehicle Mine", "Script Drone", "Up-n-Atomizer", "Burried Mine", "Script Missle", "RC Tank Rocket",
			"Bomb (Water)", "Bomb (Water 2)", "Flash Grenade", "Stun Grenade", "Script Missle (Large)", "Submarine (Big)", "EMP Launcher" };
		std::size_t explode_int = 0;
		void add(Ped ped, NativeVector3 vec, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) {
			*(unsigned short*)g_GameFunctions->m_owned_explosion = 0xE990;
			FIRE::ADD_OWNED_EXPLOSION(ped, vec.x, vec.y, vec.z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
			*(unsigned short*)g_GameFunctions->m_owned_explosion = 0x850F;
		}
		void init() {
			if (enabled) {
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					NativeVector3 c;
					if (raycast(c)) {
						if (blame) {

							add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(blamed_person), c, explode_int, damage, sound, invisible, camera_shake);
						}
						else {
							FIRE::ADD_EXPLOSION(c.x, c.y, c.z, explode_int, damage, sound, invisible, camera_shake, false);
						}
					}
				}
			}
		}
	};
	inline ExplosiveAmmo explosiveAmmo;
	class Rapid_fire {
	public:
		bool enabled = false;
		bool disable_when_reloading = false;
		bool only_when_aiming = false;
		bool disable_shooting = false;
		int delay = 0;
		void init() {
			if (enabled)
			{
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
					Player playerPed = PLAYER::PLAYER_PED_ID();
					NativeVector3 gameplayCam = CAM::GET_GAMEPLAY_CAM_COORD();
					NativeVector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
					NativeVector3 gameplayCamDirection = RotationToDirection(gameplayCamRot);
					NativeVector3 startMultiply = multiply(&gameplayCamDirection, 1.0f);
					NativeVector3 endMultiply = multiply(&gameplayCamDirection, 500.0f);
					NativeVector3 startCoords = addn(&gameplayCam, &startMultiply);
					NativeVector3 endCoords = addn(&startCoords, &endMultiply);
					Hash weaponhash;
					WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponhash, 1);
					static int delay2 = 0;
					if (disable_shooting) {
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), true);
					}
					if (delay2 == 0 || (int)(GetTickCount64() - delay2) > delay)
					{

						if (disable_when_reloading && !only_when_aiming) {
							if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000 && !PED::IS_PED_RELOADING(PLAYER::PLAYER_PED_ID()))) {
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS2(startCoords, endCoords, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000);
							}
						}
						else if (disable_when_reloading && only_when_aiming) {
							if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000 && !PED::IS_PED_RELOADING(PLAYER::PLAYER_PED_ID()) && PAD::IS_CONTROL_PRESSED(2, 25))) {
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS2(startCoords, endCoords, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000);
							}
						}
						else if (!disable_when_reloading && only_when_aiming) {
							if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000 && PAD::IS_CONTROL_PRESSED(2, 25))) {
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS2(startCoords, endCoords, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000);
							}
						}
						else
						{
							if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000)) {
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS2(startCoords, endCoords, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000);
							}
						}
						delay2 = GetTickCount64();
					}
				}
			}
		}

	};
	inline Rapid_fire rapid_fire;
	class NegitiveTorque {
	public:
		bool enabled = false;
		float multiplier = 1.0f;
		void init() {
			if (enabled) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(veh, 0.0 - multiplier);
			}

		}
	};
	inline NegitiveTorque negitiveTorque;
	class Drops {
	public:
		bool money = false;
		bool rp = false;
		bool health = false;
		bool armor = false;
		int height = 0;
		int delay = 1100;
		bool random_rp_model = false;
		const char* location[2] = {"Traditional", "Rain"};
		std::size_t data = 0;
		const char* rp_model[8] = { "Alien", "Beast", "Impotent Rage", "Pogo", "Princess Bubblegum", "Ranger", "Generic", "Sasquatch"};
		const char* rp_model_init[8] = { "vw_prop_vw_colle_alien", "vw_prop_vw_colle_beast", "vw_prop_vw_colle_imporage", "vw_prop_vw_colle_pogo", "vw_prop_vw_colle_prbubble", "vw_prop_vw_colle_rsrcomm", "vw_prop_vw_colle_rsrgeneric", "vw_prop_vw_colle_sasquatch"};
		std::size_t rp_model_data = 0;
		const char* money_model[3] = { "Store Bag", "Bank Bag", "Single Stack"};
		int money_model_init[3] = { -1666779307, 289396019, 1282927707 };
		std::size_t money_model_data = 0;
		std::int32_t model_delay = 550;
		void init() {
			if (random_rp_model) {
				static int timer;
				if (timer == 0 || (int)(GetTickCount64() - timer) > model_delay) {
					if (rp_model_data == 7) {
						rp_model_data = 0;
						
					}
					if (rp_model_data < 7) {
						rp_model_data++;
			
					}
					

					
					timer = GetTickCount64();
				}
			}
			Player p = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			NativeVector3 rp_c;
			NativeVector3 money_c;
			if (data == 0) {
				rp_c = ENTITY::GET_ENTITY_COORDS(p, false);
				money_c = ENTITY::GET_ENTITY_COORDS(p, false);
			}
			if (data == 1) {
				NativeVector3 pos_get = ENTITY::GET_ENTITY_COORDS(p, false);
				NativeVector3 pos = { pos_get.x - MISC::GET_RANDOM_INT_IN_RANGE(-20, 15), pos_get.y + MISC::GET_RANDOM_INT_IN_RANGE(-13, 6), pos_get.z };
				rp_c = pos;

				NativeVector3 pos_get2 = ENTITY::GET_ENTITY_COORDS(p, false);
				NativeVector3 pos2 = { pos_get2.x - MISC::GET_RANDOM_INT_IN_RANGE(-20, 15), pos_get2.y + MISC::GET_RANDOM_INT_IN_RANGE(-13, 6), pos_get2.z };
				money_c = pos2;
			}
			static int delayfr3 = 0;
			if (delayfr3 == 0 || (int)(GetTickCount64() - delayfr3) > delay)
			{
				
				if (rp) {
					float dz = rp_c.z;
					rp_c.z = dz + height;

					g_CallbackScript->AddCallback<ModelCallback>(MISC::GET_HASH_KEY(rp_model_init[rp_model_data]), [=] {
						*g_GameFunctions->should_sync_money_rewards = true;
					OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, rp_c.x, rp_c.y, rp_c.z, 0, 10, MISC::GET_HASH_KEY(rp_model_init[rp_model_data]), false, true);
					*g_GameFunctions->should_sync_money_rewards = false;




					delayfr3 = GetTickCount64();

						});


				}
				if (money) {
					float dz = money_c.z;
					money_c.z = dz + height;
					g_CallbackScript->AddCallback<ModelCallback>(money_model_init[money_model_data], [=] {
						*g_GameFunctions->should_sync_money_rewards = true;
					OBJECT::CREATE_AMBIENT_PICKUP(1704231442, money_c.x, money_c.y, money_c.z, 1, 2500, money_model_init[money_model_data], false, true);
					*g_GameFunctions->should_sync_money_rewards = false;


					//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-1666779307);

					delayfr3 = GetTickCount64();
						});

				}
			}
		}
	};
	inline Drops drops;
	class Fake_Drops {
	public:
		bool money = false;
		bool rp = false;
		int height = 0;
		int delay = 1100;
		void init() {
			Player p = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			NativeVector3 c = ENTITY::GET_ENTITY_COORDS(p, false);
			static int delayfr3 = 0;
			if (delayfr3 == 0 || (int)(GetTickCount64() - delayfr3) > delay)
			{
				if (rp) {
					float dz = c.z;
					c.z = dz + height;
					g_CallbackScript->AddCallback<ModelCallback>(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"), [=] {

						*g_GameFunctions->should_sync_money_rewards = true;
					OBJECT::CREATE_AMBIENT_PICKUP(1704231442, c.x, c.y, c.z, 1, 0, MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"), false, true);
					*g_GameFunctions->should_sync_money_rewards = false;




					delayfr3 = GetTickCount64();

						});

				}
				if (money) {
					float dz = c.z;
					c.z = dz + height;
					g_CallbackScript->AddCallback<ModelCallback>(-1666779307, [=] {
						*g_GameFunctions->should_sync_money_rewards = true;
					OBJECT::CREATE_AMBIENT_PICKUP(1704231442, c.x, c.y, c.z, 1, 0, -1666779307, false, true);
					*g_GameFunctions->should_sync_money_rewards = false;




					delayfr3 = GetTickCount64();
						});

				}
			}
		}
	};
	inline Fake_Drops Fake_drops;
	inline void VehicleModifier(int type, int index)
	{
		if (index == -1)
		{
			VEHICLE::REMOVE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), type);
		}
		else
		{
			VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0);
			VEHICLE::SET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), type, index, false);
		}
	}

	class AntiCheat {
	public:
		bool enabled = false;
		bool invalidmodel = false;
		bool configflag = true;
		bool speed = true;
		bool wantedlevel = true;
		bool godmode = true;
		Interior get_interior_from_player(Player player)
		{
			script_global globalplayer_bd(2657589);
			return *globalplayer_bd.at(player, 466).at(245).as<Interior*>();
		}
		bool is_in_cutscene(int i)
		{
			if (g_GameVariables->m_net_game_player(i) && g_GameVariables->m_net_game_player(i)->m_player_info)
				return g_GameVariables->m_net_game_player(i)->m_player_info->m_game_state == eGameState::InMPCutscene;
			return false;
		}

		bool is_in_interior(int i)
		{

			return get_interior_from_player(g_GameVariables->m_net_game_player(i)->m_player_id) != 0;
		}
		void mapNotification(const char* body, const char* who) {

			char messageBuffer[256];
			sprintf_s(messageBuffer, sizeof(messageBuffer), "Saint | ~t~%s ~w~failed ~r~%s", who, body);
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");

			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(messageBuffer);
			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(FALSE, TRUE);




		}
		bool infinite_ammo = true;
		bool infinite_ammo2 = true;
		bool scenario = true;
		bool tiny_ped = true;
		bool UnobtainableVehicle = true;
		bool scenarios = true;
		bool fly = true;
		bool no_ragdoll = false;
		bool ready_for_godmode(int i, Ped ped) {
			if (g_GameVariables->m_net_game_player(i)->m_player_info->m_ped->m_player_info->m_game_state != eGameState::InMPCutscene && !is_in_interior(i) && !ENTITY::IS_ENTITY_DEAD(ped, 0)) {
				return true;
			}
		}
		bool is_modding(int slot) {
			if (cheater[slot] == true) {
				return true;
			}
		}
		bool cheater[32];
		bool excluded[32];
		bool excludethatuck = false;
		void exclude_player(int slot) {
			excluded[slot] = true;
		}
		void remove_exclude(int slot) {
			excluded[slot] = false;
		}
		void flag_as_modder(int slot, int slot2, bool manual = false, const char* reason = "") {
			if (excluded[slot]) {

			}
			else {
				if (cheater[slot] == true) {

				}
				else {
					if (manual) {
						char input2[64];
						sprintf(input2, "%s was manually marked as cheater", g_GameVariables->m_net_game_player(slot2)->m_player_info->m_net_player_data.m_name);
						Noti::InsertNotification({ ImGuiToastType_None, 2000, input2 });
						cheater[slot] = true;
					}
					else {
						char input2[64];
						sprintf(input2, "%s marked as cheater | %s", g_GameVariables->m_net_game_player(slot2)->m_player_info->m_net_player_data.m_name, reason);
						Noti::InsertNotification({ ImGuiToastType_None, 2000, input2 });
						cheater[slot] = true;
					}
				}
			}
		}
		void remove_as_modder(int slot) {
			if (cheater[slot] == true) {
				cheater[slot] = false;
			}
		}
		bool is_cheater(int slot) {
			if (cheater[slot] == true) {
				return true;
			}
			else {
				return false;
			}
		}
		void init() {
			if (enabled) {
				for (int i = 0; i < 32; i++) {
					if (Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)) {


						int speedflags2 = 0;
						bool invalidModel = false;
						Hash playerModel = ENTITY::GET_ENTITY_MODEL(ped);
						if (playerModel != MISC::GET_HASH_KEY("mp_m_freemode_01")) {
							if (playerModel != MISC::GET_HASH_KEY("mp_f_freemode_01")) {
								invalidModel = true;
							}
						}



						if (invalidmodel) {
							mapNotification("Invalid Model", PLAYER::GET_PLAYER_NAME(i));


						}
						//anti-cheat
						if (tiny_ped) {
							if (PED::GET_PED_CONFIG_FLAG(ped, 223, true)) {

								flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Tiny Ped");
							}
						}
						bool godmodec = false;

						




						if (fly) {
							if (ENTITY::GET_ENTITY_SPEED(ped) > 77.0f) {
								if (!PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Fly");
								}
							}
						}
						if (scenarios) {
							if (PED::GET_PED_CONFIG_FLAG(ped, 194, true)) {

								flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Scenario");
							}
						}
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(ped, false);
						Hash cutter = MISC::GET_HASH_KEY("cutter");
						Hash cutter2 = MISC::GET_HASH_KEY("mesa2");
						Hash cutter3 = MISC::GET_HASH_KEY("policeold1");
						Hash cutter4 = MISC::GET_HASH_KEY("policeold2");
						Hash cutter5 = MISC::GET_HASH_KEY("speedo2");
						Hash cutter6 = MISC::GET_HASH_KEY("stockade3");
						Hash cutter7 = MISC::GET_HASH_KEY("asea2");
						Hash cutter8 = MISC::GET_HASH_KEY("burrito5");

						if (UnobtainableVehicle) {
							if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
								if (ENTITY::GET_ENTITY_MODEL(veh) == cutter) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);
								}
								if (ENTITY::GET_ENTITY_MODEL(veh) == cutter2) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);
								}
								if (ENTITY::GET_ENTITY_MODEL(veh) == cutter3) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);
								}
								if (ENTITY::GET_ENTITY_MODEL(veh) == cutter4) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);
								}
								if (ENTITY::GET_ENTITY_MODEL(veh) == cutter5) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);
								}
								if (ENTITY::GET_ENTITY_MODEL(veh) == cutter6) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);
								}
								if (ENTITY::GET_ENTITY_MODEL(veh) == cutter7) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);

								}
								if (ENTITY::GET_ENTITY_MODEL(veh) == cutter8) {
									flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);

								}
							}
						}
						if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, 1) == ped) {
							if (VEHICLE::GET_HAS_ROCKET_BOOST(veh)) {
								Hash getveh = MISC::GET_HASH_KEY("scramjet");
								Hash getveh2 = MISC::GET_HASH_KEY("oppressor2");
								if (ENTITY::GET_ENTITY_MODEL(veh) == getveh2) {
									if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 67 && speed) {



										if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
											if (!VEHICLE::IS_ROCKET_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(ped, false))) {
												if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
													flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Vehicle Speed");


												}
											}

										}


									}
								}
								else {
									if (ENTITY::GET_ENTITY_MODEL(veh) == getveh) {
										if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 74 && speed) {



											if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
												if (!VEHICLE::IS_ROCKET_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(ped, false))) {
													if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
														flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Vehicle Speed");


													}
												}

											}


										}
									}
									else {


										if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 67 && speed) {



											if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
												if (!VEHICLE::IS_ROCKET_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(ped, false))) {
													if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
														flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Vehicle Speed");


													}
												}

											}


										}
									}
								}
							}
							else {
								if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 67 && speed) {



									if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
										if (!VEHICLE::IS_ROCKET_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(ped, false))) {
											if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
												flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Vehicle Speed");
											}
										}

									}


								}
							}
						}
						if (PED::IS_PED_IN_ANY_PLANE(ped) && PED::IS_PED_IN_ANY_HELI(ped)) {
							if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 161 && speed) {
								if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
									if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
										flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Vehicle Speed");
									}

								}

							}
						}


						if (PLAYER::GET_PLAYER_FAKE_WANTED_LEVEL(ped) == 6 && wantedlevel) {

							flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i, false, "Fly");
						}
						if (godmodec && godmode) {

							flag_as_modder(g_GameVariables->m_net_game_player(i)->m_player_id, i);
						}

					}
				}
			}
		}
	};
	inline AntiCheat antiCheat;
	class Multipliers {
	public:
		bool run = false;
		float run_speed = 1.0f;
		bool swim_run = false;
		float swim_speed = 1.0f;
		void init() {
			if (run) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_run_speed = run_speed;
			}
			if (swim_run) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_swim_speed = run_speed;
			}
		}
	};
	inline float acceleration_power = 0.0f;
	inline float deformation = 0.0f;
	inline float camber = 0.0f;
	inline float vehicle_mass = 0.0f;
	class multis {
	public:
		float drive_bias_rear = 0.0f;
		float drive_bias_front = 0.0f;
	};
	inline multis multi;
	inline Multipliers multipliers;

	

	inline void showKeyboard(const char* title, const char* defaultText, int length, std::string* buffer, std::function<void()> action) {
		g_CustomText->AddText(CONSTEXPR_JOAAT("FMMC_KEY_TIP8"), title);
		g_Render->controlsEnabled = false;
		MISC::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", defaultText, "", "", "", length);
		g_CallbackScript->AddCallback<KeyboardCallBack>(title, length, [=] {
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
				*buffer = "";
			}
			else {
				*buffer = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
			}

		std::invoke(std::move(action));
		g_Render->controlsEnabled = true;
			});
		buffer = buffer;
		g_CustomText->RemoveText(CONSTEXPR_JOAAT("FMMC_KEY_TIP8"));
	}
	class Speedo {
	public:
		bool enabled = false;
		const char* type[4] = { "MPH", "KPH", "Game", "Custom"};
		std::size_t type_i = 0;
		float x_offset = 0.00f;
		float y_offset = 0.00f;
		float scale = 0.25f;
		std::size_t font2 = 0;
		int r = 255;
		int g = 255;
		int b = 255;
		int a = 255;
		float custom_times = 5.0;
		std::string custom_name;
		void drawText(const char* text, float x, float y, float size, int font, bool center, bool right) {
			HUD::SET_TEXT_SCALE(size, size);
			HUD::SET_TEXT_FONT(font2);
			HUD::SET_TEXT_COLOUR(r, g, b, a);
			HUD::SET_TEXT_CENTRE(center);
			if (right) {
				HUD::SET_TEXT_WRAP(0.0f, x);
				HUD::SET_TEXT_RIGHT_JUSTIFY(true);
			}
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
		}
		void init() {
			if (enabled) {
				char buffer[32];
				if (type_i == 0) {
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					float vehicleSpeed = ENTITY::GET_ENTITY_SPEED(playerVehicle);
					snprintf(buffer, sizeof(buffer), "%.0f MPH", vehicleSpeed * 2.236936);
					drawText(buffer, 0.01f + x_offset, 0.01f + y_offset, scale, 0, false, false);
				}
				if (type_i == 1) {
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					float vehicleSpeed = ENTITY::GET_ENTITY_SPEED(playerVehicle);
					snprintf(buffer, sizeof(buffer), "%.0f KPH", vehicleSpeed * 3.6);
					drawText(buffer, 0.01f + x_offset, 0.01f + y_offset, scale, 0, false, false);
				}
				if (type_i == 2) {
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					float vehicleSpeed = ENTITY::GET_ENTITY_SPEED(playerVehicle);
					snprintf(buffer, sizeof(buffer), "%i GMPH", (int)vehicleSpeed);
					drawText(buffer, 0.01f + x_offset, 0.01f + y_offset, scale, 0, false, false);
				}
				if (type_i == 3) {
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					float vehicleSpeed = ENTITY::GET_ENTITY_SPEED(playerVehicle) * custom_times;
					snprintf(buffer, sizeof(buffer), "%i %s", (int)vehicleSpeed, custom_name.c_str());
					drawText(buffer, 0.01f + x_offset, 0.01f + y_offset, scale, 0, false, false);
				}
			}
		}
	};
	inline Speedo speedo;
	class aitstrike {
	public:
		bool enabled = false;
		float scale = false;
		float height = 100.f;
		int damage = 250;
		void init() {
			if (enabled) {

				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					NativeVector3 hitCoords;
					if (raycast(hitCoords)) {
						Hash airStrike = MISC::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET");
						if (!WEAPON::HAS_WEAPON_ASSET_LOADED(airStrike))
						{
							WEAPON::REQUEST_WEAPON_ASSET(airStrike, 31, 0);
						}
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(hitCoords.x, hitCoords.y, height, hitCoords.x, hitCoords.y, 0, damage, 1, airStrike, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0);
					}
				}
			}
		}
	};
	inline aitstrike airstrike;
	class Triggerbot {
	public:
		bool enabled = false;
		bool exclude_friends = false;
		bool d1 = true;
		bool d2 = true;
		int delay = 0;
		const char* filter[3] = { "Player", "Ped", "Both" };
		const char* shoot_coords[2] = { "None", "Mouth" };
		std::size_t filter_i = 0;
		std::size_t scoords_i = 0;
		Entity AimedAtEntity;
		void shoot() {
			if (!ENTITY::IS_ENTITY_DEAD(AimedAtEntity, 0) && ENTITY::GET_ENTITY_ALPHA(AimedAtEntity) == 255)
			{
				NativeVector3 Mouth = PED::GET_PED_BONE_COORDS(AimedAtEntity, 31086, 0.1f, 0.0f, 0.0f);
				NativeVector3 hitCoords;
				if (raycast(hitCoords)) {
					static int delay2 = 0;
					if (delay2 == 0 || (int)(GetTickCount64() - delay2) > delay) {
						if (scoords_i == 0) {
							PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), hitCoords.x, hitCoords.y, hitCoords.z, true);
						}
						if (scoords_i == 1) {
							PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), Mouth.x, Mouth.y, Mouth.z, true);
						}
						delay2 = GetTickCount64();
					}

				}
			}
		}
		void init() {
			if (enabled) {

				if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &AimedAtEntity))
				{
					if (PED::IS_PED_RELOADING(PLAYER::PLAYER_PED_ID())) {
						if (d2) {
							return;
						}
					}
					if (PED::IS_PED_RAGDOLL(PLAYER::PLAYER_PED_ID())) {
						if (d1) {
							return;
						}
					}
					if (filter_i == 0) {
						if (PED::IS_PED_A_PLAYER(AimedAtEntity)) {
							int netHandle[13];
							NETWORK::NETWORK_HANDLE_FROM_PLAYER(AimedAtEntity, netHandle, 13);
							if (NETWORK::NETWORK_IS_FRIEND(&netHandle[0])) {

							}
							else {
								shoot();
							}

						}

					}
					else if (filter_i == 1) {
						if (ENTITY::IS_ENTITY_A_PED(AimedAtEntity)) {
							shoot();
						}

					}
					else if (filter_i == 2) {
						shoot();
					}

				}
			}
		}
	};
	inline Triggerbot triggerbot;

	class Text_spam {
	public:
		bool enabled = false;
		std::string text;
		int delay = 50;
		std::size_t data = 0;
		void init() {
			if (enabled) {
				int handle[26];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), &handle[0], 13);
				if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13)) {
					NETWORK::NETWORK_SEND_TEXT_MESSAGE(text.c_str(), &handle[0]);
				}

			}
		}
	};
	inline Text_spam text_spam;
	inline int i_hate_niggers = 0;
	inline float move_rate = 1.0f;
	class Max_loop {
	public:
		bool enabled = false;
		bool randomizeprimary = false;
		bool randomizesecondary = false;
		int delay = 550;
		int upgradedelay = 0;
		void init() {
			if (enabled) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{

					if (upgradedelay == 0 || (int)(GetTickCount64() - upgradedelay) > delay)
					{
						Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						VEHICLE::SET_VEHICLE_MOD_KIT(playerVehicle, 0);
						for (int i = 0; i < 50; i++)
						{
							VEHICLE::SET_VEHICLE_MOD(playerVehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(playerVehicle, i) - 1), false);

						}
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));
						if (randomizeprimary) {
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
						}
						if (randomizesecondary) {
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
						}
						VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
						upgradedelay = GetTickCount64();
					}

				}
			}
		}
	};
	inline Max_loop max_loop;
	inline int facetexture = 0;
	inline int facetexture1 = 0;
	inline int facetexture2 = 0;
	inline int facetexture3 = 0;
	inline int facetexture4 = 0;
	inline int facetexture5 = 0;
	inline int facetexture6 = 0;
	inline int facetexture7 = 0;
	inline int facetexture8 = 0;
	inline int facetexture9 = 0;
	inline int facetexture10 = 0;
	inline int facetexture11 = 0;
	inline int facetexture12 = 0;
	inline int testa = 0;
	inline int testb = 0;
	inline int testc = 0;
	inline int testd = 0;
	inline int testdtexture = 0;
	inline int torso2texture = 0;
	inline int teste = 0;
	inline int testf = 0;
	inline int testg = 0;
	inline int testh = 0;
	inline int testi = 0;
	inline int testj = 0;
	inline int testk = 0;
	inline int testl = 0;
	inline int testm = 0;
	inline int testn = 0;
	inline int testo = 0;

	inline int hatDrawable = 0;
	inline int hatTexture = 0;
	inline int glassesDrawable = 0;
	inline int glassesTexture = 0;
	inline int earsDrawable = 0;
	inline int earsTexture = 0;
	inline int watchesDrawable = 0;
	inline int watchesTexture = 0;
	inline int braceDrawable = 0;
	inline int braceTexture = 0;
	inline std::string ModelInput;
	inline std::string messageFriendInput = "";
	class Owned_explosion {
	public:
		bool blame_enabled = false;
		bool blame = true;
		int blamed_person = 0;
		bool looped = false;
		bool sound = true;
		bool invisible = false;
		float cameraShake = 0.0f;
		float damage_scale = 100.0f;
		const char* data[81] = { "Grenade", "Grenade (Launcher)", "Sticky Bomb", "Molotov", "Rocket", "Tank Shell", "HI Octane", "Car", "Plane", "Gas Pump", "Bike", "Steam", "Flame", "Water", "Gas", "Boat", "Ship Destroy", "Truck", "Bullet", "Smoke", "Smoke 2", "BZ Gas", "Flare",
			"Unknown", "Extinguisher", "Unknown", "Train", "Barrel", "Propane", "Blimp", "Flame 2", "Tanker", "Plane Rocket", "Vehicle Bullet", "Gas Tank", "Bird Crap", "Railgun", "Blimp 2", "Firework", "Snowball", "Proximity Mine", "Valkyrie Cannon", "Air Defense", "Pipe Bomb",
			"Vehicle Mine", "Explosive Ammo", "APC Shell", "Cluster Bomb", "Gas Bomb", "Incendiary Bomb", "Bomb", "Torpedo", "Torpedo (Underwater)", "Bombushka Cannon", "Cluster Bomb 2", "Hunter Barrage", "Hunter Cannon", "Rouge Cannon", "Underwater Mine", "Orbital Cannon",
			"Bomb (Wide)", "Explosive Ammo (Shotgun)", "Oppressor MK II", "Kinetic Mortar", "Kinetic Vehicle Mine", "EMP Vehicle Mine", "Spike Vehicle Mine", "Slick Vehicle Mine", "Tar Vehicle Mine", "Script Drone", "Up-n-Atomizer", "Burried Mine", "Script Missle", "RC Tank Rocket",
			"Bomb (Water)", "Bomb (Water 2)", "Flash Grenade", "Stun Grenade", "Script Missle (Large)", "Submarine (Big)", "EMP Launcher" };
		std::size_t data_i = 0;
		void add(Ped ped, NativeVector3 vec, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) {
			*(unsigned short*)g_GameFunctions->m_owned_explosion = 0xE990;
			FIRE::ADD_OWNED_EXPLOSION(ped, vec.x, vec.y, vec.z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
			*(unsigned short*)g_GameFunctions->m_owned_explosion = 0x850F;
		}
		void init() {
			if (looped) {
				if (blame) {
					NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
					add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(blamed_person), c, data_i, damage_scale, sound, invisible, cameraShake);
				}
				else {
					NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
					FIRE::ADD_EXPLOSION(c.x, c.y, c.z, data_i, damage_scale, sound, invisible, cameraShake, false);
				}
			}
		}
	};
	inline bool search_completed = false;
	inline Owned_explosion owned_explosion;
	class P_filter {
	public:
		const char* data[4] = { "None", "Vehicle", "Interior", "On Foot" };
		std::size_t data_i = 0;
	};
	inline P_filter p_filter;
	class Attackers {
	public:
		const char* mode[3] = { "None", "Police", "Jet" };
		std::size_t mode_i = 1;
		bool godmode = false;
		const char* data[89]
		{ "Antique Cavalry Dagger", "Baseball Bat", "Broken Bottle", "Crowbar", "Unarmed", "Flashlight", "Golf Club", "Hammer", "Hatchet", "Brass Knucles", "Knife", "Machete", "Switchblade", "Nightstick", "Pipe Wrench",
			"Battle Axe", "Pool Cue", "Stone Hatchet", "Pistol", "Pistol Mk II", "Combat Pistol", "AP Pistol", "Stun Gun", "Pistol .50", "SNS Pistol", "SNS Pistol Mk II", "Heavy Pistol", "Vintage Pistol", "Flare Gun", "Marksman Pistol",
			"Heavy Revolver", "Heavy Revolver Mk II", "Double Action Revolver", "Up-n-Atomizer", "Ceramic Pistol", "Navy Revolver", "Perico Pistol", "Stun Gun",
			"Micro SMG", "SMG", "SMG Mk II", "Assault SMG", "Combat PDW", "Machine Pistol", "Mini SMG", "Unholy Hellbringer",
			"Pump Shotgun", "Pump Shotgun Mk II", "Sawed-Off Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "Double Barrel Shotgun", "Sweeper Shotgun", "Combat Shotgun",
			"Assault Rifle", "Assault Rifle Mk II", "Carbine Rifle", "Carbine Rifle Mk II", "Advanced Rifle", "Special Carbine", "Special Carbine Mk II", "Bullpup Rifle", "Bullpup Rifle Mk II", "Compact Rifle", "Military Rifle", "Heavy Rifle", "Service Carbine",
			"MG", "Combat MG", "Combat MG Mk II", "Gusenberg Sweeper",
			"Sniper Rifle", "Heavy Sniper", "Heavy Sniper Mk II", "Marksman Rifle", "Marksman Rifle Mk II", "Precision Rifle",
			"RPG", "Grenade Launcher", "Grenade Launcher Smoke", "Minigun", "Firework Launcher", "Railgun", "Homing Launcher", "Compact Grenade Launcher","Widowmaker","Compact EMP Launcher" };
		std::uint32_t data2[89]
		{ 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
		0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
		0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
		0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
		0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A };
		std::size_t data_i = 0;
		const char* cop_models[2]
		{ "Normal", "FIB" };
		const char* cop_hashes[2]
		{ "s_m_y_cop_01", "mp_m_fibsec_01" };
		std::size_t cop_int = 0;
		const char* veh[1]
		{ "Lazar" };
		const char* veh_hash[1]
		{ "lazer" };
		std::size_t veh_int = 0;
		Vehicle angryPlanesPlane;
		Ped angryPlanesPed;
		Object asteroidObject;
		int how_many_planes = 1;
		Ped ped;
		void remove() {
			if (ENTITY::DOES_ENTITY_EXIST(angryPlanesPed)) {
				ENTITY::DELETE_ENTITY(&angryPlanesPed);
			}
			if (ENTITY::DOES_ENTITY_EXIST(angryPlanesPlane)) {
				ENTITY::DELETE_ENTITY(&angryPlanesPlane);
			}
		}
		void add() {

			if (mode_i == 1) {
				NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);

				g_CallbackScript->AddCallback<ModelCallback>(MISC::GET_HASH_KEY(cop_hashes[cop_int]), [=] {

					ped = PED::CREATE_PED(26, MISC::GET_HASH_KEY(cop_hashes[cop_int]), c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(g_SelectedPlayer), true, true);
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, data2[data_i], 9998, true);
				TASK::TASK_COMBAT_PED(ped, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 16);
				if (godmode)
				{
					ENTITY::SET_ENTITY_INVINCIBLE(ped, godmode);
				}


					});
				g_CallbackScript->AddCallback<ModelCallback>(MISC::GET_HASH_KEY("police3"), [=] {
					*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
				Vehicle vehicle = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("police3"), c.x + MISC::GET_RANDOM_INT_IN_RANGE(20, 50), c.y + MISC::GET_RANDOM_INT_IN_RANGE(20, 50), c.z, ENTITY::GET_ENTITY_HEADING(g_SelectedPlayer), true, false, false);
				*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				auto networkId = NETWORK::VEH_TO_NET(vehicle);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
				TASK::TASK_COMBAT_PED(ped, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 16);
				PED::SET_PED_INTO_VEHICLE(ped, vehicle, -1);

					});
			}
			if (mode_i == 2) {
				Entity playerEntity = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				NativeVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerEntity, true);
				const char* modelName = "TITAN";
				float spawnX = MISC::GET_RANDOM_FLOAT_IN_RANGE(playerCoords.x - 10.0f, playerCoords.x + 10.0f);
				float spawnY = MISC::GET_RANDOM_FLOAT_IN_RANGE(playerCoords.y - 10.0f, playerCoords.y + 10.0f);
				float spawnZ = MISC::GET_RANDOM_FLOAT_IN_RANGE(300.0f, 500.0f);
				float spawnHeading = 360.0f;
				modelName = veh_hash[veh_int];


				Hash modelHash = MISC::GET_HASH_KEY(modelName);
				Hash pedModelHash = MISC::GET_HASH_KEY("A_F_Y_Golfer_01");
				for (std::uint32_t i = 0; i < how_many_planes; ++i) {
					g_CallbackScript->AddCallback<ModelCallback>(modelHash, [=] {
						*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
					angryPlanesPlane = VEHICLE::CREATE_VEHICLE(modelHash, spawnX + MISC::GET_RANDOM_INT_IN_RANGE(50, 550), spawnY + MISC::GET_RANDOM_INT_IN_RANGE(50, 550), spawnZ, spawnHeading, true, false, false);
					*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
					DECORATOR::DECOR_SET_INT(angryPlanesPlane, "MPBitset", 0);
					auto networkId = NETWORK::VEH_TO_NET(angryPlanesPlane);
					if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(angryPlanesPlane))
						NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
					VEHICLE::SET_VEHICLE_IS_STOLEN(angryPlanesPlane, FALSE);
					VEHICLE::SET_VEHICLE_ENGINE_ON(angryPlanesPlane, true, true, true);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(angryPlanesPlane, MISC::GET_RANDOM_INT_IN_RANGE(50, 350));
					//ENTITY::SET_ENTITY_INVINCIBLE(angryPlanesPlane, 1);
					ENTITY::SET_ENTITY_PROOFS(angryPlanesPlane, true, true, true, true, true, true, true, true);
					VEHICLE::SET_VEHICLE_DAMAGE(angryPlanesPlane, 0.f, 0.f, 0.f, 0.f, 200.f, false);
						});
					g_CallbackScript->AddCallback<ModelCallback>(pedModelHash, [=]
						{
							angryPlanesPed = PED::CREATE_PED(26, pedModelHash, spawnX, spawnY, spawnZ + 100.0f, spawnHeading, true, true);
					PED::SET_PED_INTO_VEHICLE(angryPlanesPed, angryPlanesPlane, -1);
					PED::SET_DRIVER_ABILITY(angryPlanesPed, 0.99f);
					ENTITY::SET_ENTITY_INVINCIBLE(angryPlanesPed, 1);
					TASK::TASK_COMBAT_PED(angryPlanesPed, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 16);
						});

				}
			}
		}
	};
	inline Attackers attackers;
	inline const char* get_vehicle_class_name(int id) {
		std::stringstream ss; ss << "VEH_CLASS_" << id;
		return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()) == "NULL" ? "Unknown Class" : HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str());
	}
	inline int m_selected_vehicle_class;
	inline int m_selected_player_vehicle_class;
	class spawnedVeh {
	public:
		spawnedVeh(std::string name, Vehicle id) {
			m_name = name;
			m_id = id;

		}
	public:
		std::string m_name;
		Vehicle m_id = 0;
	};
	class SpawnedVehicles {
	public:
		std::vector<spawnedVeh> spawned = {

		};
		int selectedveh = 0;
		int selectedclass = 0;
		const char* seletedname = "";
	};
	inline SpawnedVehicles spawned_veh;
	class Veh_spawner {
	public:
		bool spawn_in_air = true;
		bool spawninair = true;
		bool fade_in = true;
		bool spawn_in = true;
		bool setengineon = true;
		bool forward_speed = true;
		int forwardspeedmutli = 150;
		int heightmulti = 100;
		bool dellast = false;
		bool spawnwithcolor = false;
		int spawnr = 0;
		int spawng = 0;
		int spawnb = 0;
		int spawnr2 = 0;
		int spawng2 = 0;
		int spawnb2 = 0;
		const char* fade_speed[2] = {"Fast", "Slow"};
		std::size_t fade_speed_i = 0;
		bool max = false;
		void spawn(Hash hash, Vehicle* buffer) {
			*script_global(4540726).as<bool*>() = true;
			g_CallbackScript->AddCallback<ModelCallback>(hash, [=]
				{
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			float veh_speed = ENTITY::GET_ENTITY_SPEED(playerVehicle);
			if (dellast) {
				Vehicle lastVehicle = PLAYER::GET_PLAYERS_LAST_VEHICLE();
				VEHICLE::DELETE_VEHICLE(&lastVehicle);
			}


			NativeVector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(PLAYER::PLAYER_PED_ID(), { 0.f, dellast ? 0.f : 8.0f, (VEHICLE::IS_THIS_MODEL_A_PLANE(hash) && spawninair || VEHICLE::IS_THIS_MODEL_A_HELI(hash) && spawninair) ? 1.0f + heightmulti : 1.0f });
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, false, false);
			spawned_veh.spawned.push_back({ HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(vehicle))), vehicle });
			*buffer = vehicle;
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
			auto networkId = NETWORK::VEH_TO_NET(vehicle);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, veh_speed);
			if (max) {
				VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
				for (int i = 0; i < 50; i++)
				{
					VEHICLE::SET_VEHICLE_MOD(vehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1), false);

				}
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));
				
			}
			if (setengineon) {
				VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true, true);
			}
			if (forward_speed) {
				if (VEHICLE::IS_THIS_MODEL_A_PLANE(hash)) {
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, forwardspeedmutli);

				}
			}
			if (spawn_in) {
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
			}
			if (fade_in) {
				if (fade_speed_i == 0) {
					NETWORK::NETWORK_FADE_IN_ENTITY(vehicle, true, false);
				}
				if (fade_speed_i == 1) {
					NETWORK::NETWORK_FADE_IN_ENTITY(vehicle, true, true);
				}
				
			}
			if (spawnwithcolor) {
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, spawnr, spawng, spawnb);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, spawnr2, spawng2, spawnb2);
			}
				});
		}
		bool selected_fade = true;
		void spawn_for_ped(Hash hash, Vehicle* buffer) {
			*script_global(4540726).as<bool*>() = true;
			g_CallbackScript->AddCallback<ModelCallback>(hash, [=]
				{



					NativeVector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), { 0.f, dellast ? 0.f : 8.0f, 1.0f });
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer)), true, false, false);
			*buffer = vehicle;
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
			auto networkId = NETWORK::VEH_TO_NET(vehicle);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
			VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true, true);



			if (selected_fade) {
				NETWORK::NETWORK_FADE_IN_ENTITY(vehicle, true, false);
			}

				});
		}
		void spawn_for_ped2(Hash hash, Vehicle* buffer) {
			*script_global(4540726).as<bool*>() = true;
			g_CallbackScript->AddCallback<ModelCallback>(hash, [=]
				{



					NativeVector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), { 0.f, 0.f, 1.0f });
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer)), true, false, false);
			*buffer = vehicle;
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
			auto networkId = NETWORK::VEH_TO_NET(vehicle);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
			VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true, true);



			if (selected_fade) {
				NETWORK::NETWORK_FADE_IN_ENTITY(vehicle, true, false);
			}

				});
		}
	};
	inline Veh_spawner veh_spawner;
	class Region {
	public:

		const char* type[9]
		{
			"CIS",
			"Africa",
			"East" ,
			"Europe" ,
			"China",
			"Australia",
			"West",
			"Japan",
			"Unknown",
		};
		std::size_t region_id = 0;

		void override(uint32_t id) {

			*g_GameVariables->m_region_code = id;
		}
	};
	inline Region region;
	class c_FOV {
	public:
		Cam freecamCamera;
		bool enabled = false;
		float value = 90.0f;
		void init() {
			if (enabled) {
				NativeVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

				if (!CAM::DOES_CAM_EXIST(freecamCamera)) {
					freecamCamera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", true);
					CAM::SET_CAM_ROT(freecamCamera, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
					CAM::SET_CAM_COORD(freecamCamera, CAM::GET_GAMEPLAY_CAM_COORD());
					value = CAM::GET_GAMEPLAY_CAM_FOV();
				}

				CAM::RENDER_SCRIPT_CAMS(true, true, 700, true, true, true);
				CAM::SET_CAM_ACTIVE(freecamCamera, true);
				CAM::SET_CAM_ROT(freecamCamera, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
				CAM::SET_CAM_COORD(freecamCamera, CAM::GET_GAMEPLAY_CAM_COORD());
				CAM::SET_CAM_FOV(freecamCamera, value);
				if (PAD::IS_CONTROL_PRESSED(2, 25)) {
					HUD::DISPLAY_SNIPER_SCOPE_THIS_FRAME();
				}
			}


		}
	};
	inline c_FOV m_fov;
	class Blink {
	public:
		Cam freecamCamera;
		bool enabled = false;
		void init() {
			if (enabled) {
				NativeVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

				if (!CAM::DOES_CAM_EXIST(freecamCamera)) {
					freecamCamera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", true);
					CAM::SET_CAM_ROT(freecamCamera, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
					CAM::SET_CAM_COORD(freecamCamera, CAM::GET_GAMEPLAY_CAM_COORD());
				}

				CAM::RENDER_SCRIPT_CAMS(true, true, 700, true, true, true);
				CAM::SET_CAM_ACTIVE(freecamCamera, true);
				CAM::SET_CAM_ROT(freecamCamera, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);

				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), true);
				//HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
				PAD::DISABLE_CONTROL_ACTION(2, 8, true);
				PAD::DISABLE_CONTROL_ACTION(2, 32, true);
				PAD::DISABLE_CONTROL_ACTION(2, 34, true);

				NativeVector3 freecamCoords = CAM::GET_CAM_COORD(freecamCamera);
				NativeVector3 cameraDirection = RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0));
				NativeVector3 accelerateCoords = multiply(&cameraDirection, 0.1f);
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 8)) {

					NativeVector3 newCoords = addn(&freecamCoords, &accelerateCoords);
					CAM::SET_CAM_COORD(freecamCamera, newCoords);
				}
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 32)) {
					NativeVector3 newCoords = addn(&freecamCoords, &accelerateCoords);
					CAM::SET_CAM_COORD(freecamCamera, newCoords);
				}
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 34)) {
					CAM::SET_CAM_ROT(freecamCamera, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
				}
			}
		}
	};
	inline Blink blink;
	class Excludes466 {
	public:
		bool friends = false;
		bool players = false;
		bool peds = false;
		bool team = false;
	};
	class Aimbot {
	public:
		Excludes466 excludes;
		bool enabled = false;
		float distance = 50.0f;
		const char* bone[2] = { "Head", "Lower Chest" };
		std::size_t data = 0;

		Ped aimbot_ped;
		Cam aimcam;
		int SKEL_Head = 0x796e;
		bool fov_circle = false;
		std::uint32_t BoneHashes[2]
		{ 0x796e, 0xdd1c };
		std::size_t WeaponInt = 0;
		void aim() {
			NativeVector3 aimpos = CAM::GET_GAMEPLAY_CAM_COORD();
			CAM::DESTROY_ALL_CAMS(true);
			aimcam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", aimpos.x, aimpos.y, aimpos.z, 0, 0, 0, 50, 1, 2);
			CAM::RENDER_SCRIPT_CAMS(1, true, 700, 1, 1, 0);
			CAM::SET_CAM_ACTIVE(aimcam, 1);
			CAM::SET_CAM_ROT(aimcam, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);

			for (int i = 0; i < 32; i++)
			{
				NativeVector3 target_coords = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), BoneHashes[data], 0, 0, 0);
				NativeVector3 ped_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1);
				NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);

				Ped PlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				NativeVector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
				NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(PlayerPed, false);
				float distance = GetDistanceFloat(PedCoords, Coords);

				if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
				{
					HUD::DISPLAY_SNIPER_SCOPE_THIS_FRAME();
					if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
					{
						if (i == PLAYER::PLAYER_ID())
							continue;


						const int numElements = 10;
						const int arrSize = numElements * 2 + 2;
						int veh[arrSize];
						veh[0] = numElements;
						int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, -1);
						Ped closest = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						if (excludes.team) {
							if (PLAYER::GET_PLAYER_TEAM(closest) != PLAYER::GET_PLAYER_TEAM(PLAYER::PLAYER_PED_ID())) {
								if (veh != NULL) {
									for (int i = 0; i < count; i++)
									{
										int offsettedID = i * 2 + 2;
										if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
										{
											for (int j = -1; j <= 2; ++j)
											{
												Any ped = veh[offsettedID];

												if (closest == 0) closest = ped;
												else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
												Hash weaponhash;
												WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
												float screenX, screenY;
												BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
												if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
												{
													CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
												}
											}
										}
									}
								}
							}
						}
						if (excludes.peds) {
							if (!ENTITY::IS_ENTITY_A_PED(closest)) {
								if (veh != NULL) {
									for (int i = 0; i < count; i++)
									{
										int offsettedID = i * 2 + 2;
										if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
										{
											for (int j = -1; j <= 2; ++j)
											{
												Any ped = veh[offsettedID];

												if (closest == 0) closest = ped;
												else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
												Hash weaponhash;
												WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
												float screenX, screenY;
												BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
												if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
												{
													CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
												}
											}
										}
									}
								}
							}
						}
						if (excludes.friends) {
							int netHandle[13];
							NETWORK::NETWORK_HANDLE_FROM_PLAYER(closest, netHandle, 13);
							if (!NETWORK::NETWORK_IS_FRIEND(&netHandle[0])) {
								if (veh != NULL) {
									for (int i = 0; i < count; i++)
									{
										int offsettedID = i * 2 + 2;
										if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
										{
											for (int j = -1; j <= 2; ++j)
											{
												Any ped = veh[offsettedID];

												if (closest == 0) closest = ped;
												else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
												Hash weaponhash;
												WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
												float screenX, screenY;
												BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
												if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
												{
													CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
												}
											}
										}
									}
								}
							}
						}
						if (excludes.players) {
							if (!PED::IS_PED_A_PLAYER(closest)) {
								if (veh != NULL) {
									for (int i = 0; i < count; i++)
									{
										int offsettedID = i * 2 + 2;
										if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
										{
											for (int j = -1; j <= 2; ++j)
											{
												Any ped = veh[offsettedID];

												if (closest == 0) closest = ped;
												else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
												Hash weaponhash;
												WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
												float screenX, screenY;
												BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
												if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
												{
													CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
												}
											}
										}
									}
								}
							}
						}
						if (!excludes.friends && !excludes.peds && !excludes.players) {
							if (veh != NULL) {
								for (int i = 0; i < count; i++)
								{
									int offsettedID = i * 2 + 2;
									if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
									{
										for (int j = -1; j <= 2; ++j)
										{
											Any ped = veh[offsettedID];

											if (closest == 0) closest = ped;
											else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
											Hash weaponhash;
											WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
											float screenX, screenY;
											BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
											if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
											{
												CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
											}
										}
									}
								}
							}
						}

					}
				}
			}
			if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
			{
				const int numElements = 10;
				const int arrSize = numElements * 2 + 2;
				int veh[arrSize];
				veh[0] = numElements;
				int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, -1);
				Ped closest = 0;
				NativeVector3 target_coords = PED::GET_PED_BONE_COORDS(closest, SKEL_Head, 0, 0, 0);
				NativeVector3 ped_coords = ENTITY::GET_ENTITY_COORDS(closest, 1);
				NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
				if (excludes.team) {
					if (PLAYER::GET_PLAYER_TEAM(closest) != PLAYER::GET_PLAYER_TEAM(PLAYER::PLAYER_PED_ID())) {
						if (veh != NULL) {
							for (int i = 0; i < count; i++)
							{
								int offsettedID = i * 2 + 2;
								if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
								{
									for (int j = -1; j <= 2; ++j)
									{
										Any ped = veh[offsettedID];

										if (closest == 0) closest = ped;
										else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
										Hash weaponhash;
										WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
										float screenX, screenY;
										BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
										if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
										{
											CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
										}
									}
								}
							}
						}
					}
				}
				if (excludes.peds) {
					if (!ENTITY::IS_ENTITY_A_PED(closest)) {
						if (veh != NULL) {
							for (int i = 0; i < count; i++)
							{
								int offsettedID = i * 2 + 2;
								if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
								{
									for (int j = -1; j <= 2; ++j)
									{
										Any ped = veh[offsettedID];

										if (closest == 0) closest = ped;
										else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
										Hash weaponhash;
										WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
										float screenX, screenY;
										BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
										if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
										{
											CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
										}
									}
								}
							}
						}
					}
				}
				if (excludes.friends) {
					int netHandle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(closest, netHandle, 13);
					if (!NETWORK::NETWORK_IS_FRIEND(&netHandle[0])) {
						if (veh != NULL) {
							for (int i = 0; i < count; i++)
							{
								int offsettedID = i * 2 + 2;
								if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
								{
									for (int j = -1; j <= 2; ++j)
									{
										Any ped = veh[offsettedID];

										if (closest == 0) closest = ped;
										else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
										Hash weaponhash;
										WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
										float screenX, screenY;
										BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
										if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
										{
											CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
										}
									}
								}
							}
						}
					}
				}
				if (excludes.players) {
					if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(closest)) {
						if (veh != NULL) {
							for (int i = 0; i < count; i++)
							{
								int offsettedID = i * 2 + 2;
								if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
								{
									for (int j = -1; j <= 2; ++j)
									{
										Any ped = veh[offsettedID];

										if (closest == 0) closest = ped;
										else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
										Hash weaponhash;
										WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
										float screenX, screenY;
										BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
										if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
										{
											CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
										}
									}
								}
							}
						}
					}
				}
				if (!excludes.friends && !excludes.peds && !excludes.players) {
					if (veh != NULL) {
						for (int i = 0; i < count; i++)
						{
							int offsettedID = i * 2 + 2;
							if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
							{
								for (int j = -1; j <= 2; ++j)
								{
									Any ped = veh[offsettedID];

									if (closest == 0) closest = ped;
									else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;
									Hash weaponhash;
									WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
									float screenX, screenY;
									BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
									if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
									{
										CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, BoneHashes[data], 0, 0, .1, 0);
									}
								}
							}
						}
					}
				}
			}
		}
		void init() {
			if (enabled) {
				aim();
			}
		}
	};
	inline Aimbot aimbot;
	class DamageC {
	public:
		void change(int size) {



			switch (size) {
			case 0:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Unknown;
				Lists::DamagePos = (std::size_t)eDamageType::Unknown;
				break;
			case 1:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::None;
				Lists::DamagePos = (std::size_t)eDamageType::None;
				break;
			case 2:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Melee;
				Lists::DamagePos = (std::size_t)eDamageType::Melee;
				break;
			case 3:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Bullet;
				Lists::DamagePos = (std::size_t)eDamageType::Bullet;
				break;
			case 4:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::BulletRubber;
				Lists::DamagePos = (std::size_t)eDamageType::BulletRubber;
				break;
			case 5:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Explosive;
				Lists::DamagePos = (std::size_t)eDamageType::Explosive;
				break;
			case 6:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Fire;
				Lists::DamagePos = (std::size_t)eDamageType::Fire;
				break;
			case 7:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Collision;
				Lists::DamagePos = (std::size_t)eDamageType::Collision;
				break;
			case 8:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Fall;
				Lists::DamagePos = (std::size_t)eDamageType::Fall;
				break;
			case 9:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Drown;
				Lists::DamagePos = (std::size_t)eDamageType::Drown;
				break;
			case 10:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Electric;
				Lists::DamagePos = (std::size_t)eDamageType::Electric;
				break;
			case 11:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::BarbedWire;
				Lists::DamagePos = (std::size_t)eDamageType::BarbedWire;
				break;
			case 12:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::FireExtinguisher;
				Lists::DamagePos = (std::size_t)eDamageType::FireExtinguisher;
				break;
			case 13:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Smoke;
				Lists::DamagePos = (std::size_t)eDamageType::Smoke;
				break;
			case 14:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::WaterCannon;
				Lists::DamagePos = (std::size_t)eDamageType::WaterCannon;
				break;
			case 15:
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_damage_type = eDamageType::Tranquilizer;
				Lists::DamagePos = (std::size_t)eDamageType::Tranquilizer;
				break;
			}


			g_Render->m_SubmenuStack.pop();
		}
	};
	inline DamageC damage_type;
	class TargetingMode {
	public:
		void change(int size) {

			//PLAYER::SET_PLAYER_TARGETING_MODE(size);
			t_mode.init = size;
			g_Render->m_SubmenuStack.pop();
		}
	};
	inline TargetingMode target_c;
	class Globals {
	public:
		int mobile = 2793046;
		int radar = 2657589;
		int time = 2672505;
		template <typename T>
		void add(int base, int at, int value, Any type) {
			*script_global(base).at(at).as<int*>() = value;
		}
	};
	inline Globals global;
	class Requests {
	public:
		const char* data[7] = { "Helicopter Pickup", "Boat Pickup", "Backup Helicopter", "Airstrike", "Ammo Drop", "BST", "Ballistic Armor" };
		std::size_t data_i = 0;
		void add(int type) {
			*script_global(global.mobile).at(type).as<int*>() = 1;
		}
	};
	inline Requests requests;
	class Load {
	public:

		void add(std::string text) {
			HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
			HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(3);





		}
		void remove() {
			HUD::BUSYSPINNER_OFF();
		}
	};
	inline Load m_load;
	class off_the_radar {
	public:
		bool enabled = false;
		const char* time[4] = { "Normal", "13:37", "69:69", "99:99" };
		std::size_t data = 0;
		void init() {
			if (enabled) {
				script_global globalplayer_bd(2657589);
				switch (data) {
				case 0:

					*globalplayer_bd.at(PLAYER::GET_PLAYER_INDEX(), 466).at(210).as<int*>() = true;
					*script_global(2672505).at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
					break;
				case 1:

					*globalplayer_bd.at(PLAYER::GET_PLAYER_INDEX(), 466).at(210).as<int*>() = true;
					*script_global(2672505).at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1337;
					break;
				case 2:

					*globalplayer_bd.at(PLAYER::GET_PLAYER_INDEX(), 466).at(210).as<int*>() = true;
					*script_global(2672505).at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 6969;
					break;
				case 3:

					*globalplayer_bd.at(PLAYER::GET_PLAYER_INDEX(), 466).at(210).as<int*>() = true;
					*script_global(2672505).at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 9999;
					break;
				}
			}
		}
	};
	inline off_the_radar m_radar;
	class join_ses {
	public:
		const char* name[10] = { "Populated Public", "New Public", "Closed Crew", "Crew", "Closed Friend", "Find Friend", "Solo", "Invite Only", "Social-Club TV", "Story Mode" };
		std::size_t data = 0;
		void join(eSessionType session) {
			*script_global(2695915).as<int*>() = (session == eSessionType::SC_TV ? 1 : 0);

			if (session == eSessionType::LEAVE_ONLINE)
				*script_global(1574589).at(2).as<int*>() = -1;
			else
				*script_global(1575017).as<int*>() = (int)session;

			*script_global(1574589).as<int*>() = 1;
			fbr::cur()->wait(200ms);
			*script_global(1574589).as<int*>() = 0;
		}
	};
	inline join_ses session;
	class Flag_creator {
	public:
		const char* direction[3] = { "Reckless", "Non-Reckless",autopilot.avoid_roads_name.c_str() };
		std::size_t data = 0;
		bool auto_save = false;
		bool stop_before_vehicles = false;
		bool stop_before_peds = false;
		bool avoid_vehicles = false;
		bool avoid_empty_vehicles = false;
		bool avoid_peds = false;
		bool avoid_objects = false;
		bool stop_at_traffic_lights = false;
		bool use_blinkers = false;
		bool allow_going_wrong_way = false;
		bool drive_in_reverse = false;
		bool take_shortest_path = false;
		bool wreckless = false;
		bool ignore_roads = false;
		bool ignore_all_pathing = false;
		bool avoid_highways = false;
		int current = 0;
		void init() {
			if (auto_save) {
				switch (data) {
				case 0:
					autopilot.wreckless_flag = current;
					break;
				case 1:
					autopilot.nonwreckless_flag = current;
					break;
				case 2:
					autopilot.avoid_roads_flag = current;
					break;
				}
			}
		}

	};
	inline Flag_creator flag_creator;
	class teleport {
	public:
		bool automatic = false;
		Cam m_TeleportCam = NULL;
		bool GetBlipLocation(NativeVector3& location, int sprite, int color = -1)
		{
			Blip Blip;
			for (
				Blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite);
				HUD::DOES_BLIP_EXIST(Blip) && color != -1 && HUD::GET_BLIP_COLOUR(Blip) != color;
				Blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite)
				);

			if (!HUD::DOES_BLIP_EXIST(Blip) || (color != -1 && HUD::GET_BLIP_COLOUR(Blip) != color))
				return false;

			location = HUD::GET_BLIP_COORDS(Blip);

			return true;
		}
		bool GetObjectiveLocation(NativeVector3& location)
		{
			if (GetBlipLocation(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission))
				return true;
			if (GetBlipLocation(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission2))
				return true;
			if (GetBlipLocation(location, (int)BlipIcons::Circle, (int)BlipColors::Mission))
				return true;
			if (GetBlipLocation(location, (int)BlipIcons::RaceFinish, (int)BlipColors::None))
				return true;
			if (GetBlipLocation(location, (int)BlipIcons::Circle, (int)BlipColors::Green))
				return true;
			if (GetBlipLocation(location, (int)BlipIcons::Circle, (int)BlipColors::Blue))
				return true;
			if (GetBlipLocation(location, (int)BlipIcons::CrateDrop))
				return true;

			static const int Blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };
			for (const auto& Blip : Blips)
			{
				if (GetBlipLocation(location, Blip, 5))
					return true;
			}

			return false;
		}
		void objective() {
			NativeVector3 Location;

			if (!GetObjectiveLocation(Location))
			{
				return;
			}

			PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), Location.x, Location.y, Location.z);
		}
		void waypoint() {

			NativeVector3 coords = GetBlipIcon();
			Ped ped = PLAYER::PLAYER_PED_ID();

			

			if (coords.x == 0 && coords.y == 0) { return; }

			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 0))
				ped = PED::GET_VEHICLE_PED_IS_USING(ped);

			bool isGroundAvailable = false;
			std::vector<float> GROUND_HEIGHT{ 100.0f, 150.0f, 50.0f, 0.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f };
			m_load.add("Getting coordinates...");
			for (int i = 0; i < GROUND_HEIGHT.size(); i++)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, GROUND_HEIGHT[i], true, true, true);

				fbr::cur()->wait(100ms);




				if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, GROUND_HEIGHT[i], &coords.z, 0, false))
				{
					isGroundAvailable = true;
					coords.z += 3.0;
					break;
				}
			}
			m_load.remove();
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, true, true, true);
		}
		void object() {
			NativeVector3 coords = GetBlipIcon();
			Ped ped = PLAYER::PLAYER_PED_ID();

			if (coords.x == 0 && coords.y == 0) { return; }

			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 0))
				ped = PED::GET_VEHICLE_PED_IS_USING(ped);

			bool isGroundAvailable = false;
			std::vector<float> GROUND_HEIGHT{ 100.0f, 150.0f, 50.0f, 0.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f };
			m_load.add("Getting coordinates...");
			for (int i = 0; i < GROUND_HEIGHT.size(); i++)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, GROUND_HEIGHT[i], true, true, true);

				fbr::cur()->wait(100ms);




				if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, GROUND_HEIGHT[i], &coords.z, 0, false))
				{
					isGroundAvailable = true;
					coords.z += 3.0;
					break;
				}
			}
			m_load.remove();
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, true, true, true);
		}
		void init() {
			if (automatic) {
				waypoint();
			}
		}
	};
	inline teleport m_teleport;
	class CWaterDataItem
	{
	public:
		__int16 iMinX; //0x0000 X Coord 1
		__int16 iMinY; //0x0002  Y Coord 1
		__int16 iMaxX; //0x0004 X Coord 2
		__int16 iMaxY; //0x0006 Y Coord 2
		__int8 iAlphaSW; //0x0008  (South West, default 26)
		__int8 iAlphaSE; //0x0009  (South East, default 26)
		__int8 iAlphaNW; //0x000A  (North West, default 26)
		__int8 iAlphaNE; //0x000B  (North East, default 26)
		char _0x000C[8]; // (Unknown, appear to be two floats?)
		float fHeight; //0x0014 (Z-Height, default 0.0)
		BYTE bHasLimitedDepth; //0x0018  (Second bit [binary 10] = On, gives the water quad an effective range of 6 z-points)
		char _0x0019[3]; // (Unknown)
	};//Size=0x001C
	class CWaterTune
	{
	public:
		DWORD dwWaterColor; //0x0000  Default: 0x1A00191C
		float fRippleScale; //0x0004  Default: 0.040000f
		float fOceanFoamScale; //0x0008  Default: 0.050000f
		float fSpecularFalloff; //0x000C  Default: 1118.000000f
		float fFodPierceIntensity; //0x0010  Default: 1.100000f
		float fRefractionBlend; //0x0014  Default: 0.700000f
		float fRefractionExponent; //0x0018  Default: 0.250000f
		float fWaterCycleDepth; //0x001C  Default: 10.000000f
		float fWaterCycleFade; //0x0020  Default: 50.000000f
		float fWaterLightningDepth; //0x0024  Default: 0.000000f
		float fWaterLightningFade; //0x0028  Default: 10.000000f
		float fDeepWaterModDepth; //0x002C  Default: 90.000000f
		float fDeepWaterModFade; //0x0030  Default: 80.000000f
		float fGodRaysLerpStart; //0x0034  Default: 0.000000f
		float fGodRaysLerpEnd; //0x0038  Default: 200.000000f
		float fDisturbFoamScale; //0x003C  Default: 0.050000f
		void* vec2FogMin; //0x0040  Default: x = -4000.000000 y = -4000.000000
		void* vec2FogMax; //0x0048  Default: x = 4500.000000 y= 8000.000000
	};
	inline uintptr_t ModuleBaseAdress = (uintptr_t)GetModuleHandle(NULL);
	class RainbowColor {
	public:
		bool enabled = false;
		bool change_secondary = false;
		int delay = 0;


	};
	class ChangeVehicleColor {
	public:
		int r = 0;
		int g = 0;
		int b = 0;
		RainbowColor rainbow;
		void override() {

		}
		void init() {
			if (rainbow.enabled) {

				static int timer;
				if (timer == 0 || (int)(GetTickCount64() - timer) > rainbow.delay) {
					if (r > 0 && b == 0) {
						r--;
						g++;
					}
					if (g > 0 && r == 0) {
						g--;
						b++;
					}
					if (b > 0 && g == 0) {
						r++;
						b--;
					}
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVehicle, r, g, b);
					if (rainbow.change_secondary) {
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVehicle, r, g, b);
					}
					timer = GetTickCount64();
				}
			}
		}
	};
	inline ChangeVehicleColor changeVehicleColor;
	class Chat {
	public:
		std::string text;
		bool team_only = false;
		bool spammer = false;
		int delay = 300;
		int spoofed_sender = 0;
		bool spoof_sender = false;
		void add_message(const char* msg, const char* player_name, bool is_team)
		{
			if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
				if (Hooks::send_chat_message(*g_GameFunctions->m_send_chat_ptr, g_GameVariables->m_net_game_player(PLAYER::PLAYER_ID())->get_net_data(), msg, false)) {
					g_GameFunctions->m_send_chat_message(*g_GameFunctions->m_send_chat_ptr, g_GameVariables->m_net_game_player(PLAYER::PLAYER_ID())->get_net_data(), msg, false);
					g_GameFunctions->m_send_chat_ptr, g_GameVariables->m_net_game_player(PLAYER::PLAYER_ID())->get_net_data(), msg, false;
					int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MULTIPLAYER_CHAT");
					GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "ADD_MESSAGE");
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name);
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(msg);
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(is_team ? "MP_CHAT_TEAM" : "MP_CHAT_ALL"));
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(false);
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
					GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
					GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SET_FOCUS");
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name);
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
					GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
					GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, 255, 255, 255, 255, 0);
				}
			}
			

		}
		void init() {
			if (spammer) {
				if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
					static int timer;
					if (timer == 0 || (int)(GetTickCount64() - timer) > delay) {
						add_message(text.c_str(), g_GameVariables->m_net_game_player(PLAYER::PLAYER_ID())->get_name(), false);
						timer = GetTickCount64();
					}
				}
			}
			if (team_only) {
				NETWORK::NETWORK_SET_TEAM_ONLY_CHAT(true);
			}
		}
		void send_once() {
			if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
				add_message(text.c_str(), g_GameVariables->m_net_game_player(PLAYER::PLAYER_ID())->get_name(), false);
			}
		}
	};
	inline Chat chat;
	class Team {
	public:
		bool override_restrictions = false;
		bool use_player_colour_instead_of_team = false;
		const char* type[2] = { "Red", "Blue" };
		std::size_t data = 0;
		void init() {
			if (use_player_colour_instead_of_team) {
				NETWORK::USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(true);
			}
			if (override_restrictions) {
				NETWORK::NETWORK_OVERRIDE_TEAM_RESTRICTIONS(PLAYER::GET_PLAYER_TEAM(PLAYER::PLAYER_PED_ID()), true);
			}
		}
	};
	inline Team team;
	inline Ped selected_ped_i = 0;

	class Scenarios {
	public:
		const char* name[3] = {
			"Showering",
			"Stripper Dance",
			"Crouch Walking",
		};
		const char* dict[3] = {
			"mp_safehouseshower@male@",
			"mini@strip_club@private_dance@part1",
			"move_weapon@rifle@generic"
		};
		const char* id[3] = {
			"male_shower_idle_b",
			"priv_dance_p1",
			"walk_crouch",
		};
		std::size_t size = 3;
	};
	class Animations {
	public:
		const char* suc[2] = { "Pistol", "Pill" };
		std::size_t suc_data;
		std::string dictInput;
		std::string idInput;
		bool does_exist = false;
		Scenarios scenarios;
		bool contort = false;
		bool controllable = false;
		void start(const char* anim, const char* animid)
		{
			g_CallbackScript->AddCallback<AnimationCallback>(anim, [=]
				{
					if (controllable) {
						TASK::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), (char*)anim, (char*)animid, 9.0f, 0.0f, -1, 120, 0, false, false, false);
					}
					else
					{
						TASK::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), (char*)anim, (char*)animid, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
					}
				});
		}
	};
	inline Animations animation;
	inline bool mark_as_Saint = true;
	class WantedLev {
	public:
		bool always = false;
		void init() {
			if (always) {
				g_players.get_selected.set_wanted_level(3);
			}
		}
	};
	inline WantedLev wanted_lev;
	class Cage {
	public:
		bool is_invisible = false;
		const char* type[2] = { "Stunt Tube", "Normal" };
		std::size_t data = 0;
		void add() {
			switch (data) {
			case 0:
				m_queue.add(10ms, "Adding Cage", [=] {
					Player ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				NativeVector3 c = ENTITY::GET_ENTITY_COORDS(ped, true);
				Hash hash = MISC::GET_HASH_KEY("stt_prop_stunt_tube_l");


				Object cage = OBJECT::CREATE_OBJECT_NO_OFFSET(hash, c.x, c.y, c.z, true, false, false);
				if (is_invisible) {
					ENTITY::SET_ENTITY_VISIBLE(cage, false, 0);
				}
				ENTITY::SET_ENTITY_ROTATION(cage, 0.0, 90.0, 0.0, 1, true);
					});
				break;
			case 1:
				m_queue.add(10ms, "Adding Cage", [=] {
					NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);

				Object cage = OBJECT::CREATE_OBJECT(MISC::GET_HASH_KEY("prop_gold_cont_01"), c.x, c.y, c.z, true, false, false);
				if (is_invisible) {
					ENTITY::SET_ENTITY_VISIBLE(cage, false, 0);
				}
					});
				break;
			}

		}
	};
	inline Cage cage;
	class Incr {
	public:
		const char* type[5] = { "Griefing", "Game Exploits", "Exploits", "Punished", "Cheats" };
		std::size_t data;
		void add() {
			g_GameFunctions->m_remote_increment(*(Hash*)type[data], 100, g_GameVariables->m_net_game_player(g_SelectedPlayer));
		}
	};
	inline Incr incr;
	class GravityG {
	public:
		bool enabled = false;
		float m_force{ 250.0f };
		bool take_control_of(Entity ent)
		{
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return true;
			for (uint8_t i = 0; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) && i < 10; i++)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);

				fbr::cur()->wait();
			}
			if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return false;

			int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);

			return true;
		}
		float GravityGunGoto(float aimX, float entityX)
		{
			static float GravityGunVeloPos;

			if (aimX > 0 && entityX > 0) GravityGunVeloPos = aimX - (entityX);

			if (aimX < 0 && entityX < 0) GravityGunVeloPos = aimX - (entityX);

			if (aimX > 0 && entityX < 0) GravityGunVeloPos = aimX + (entityX);

			if (aimX < 0 && entityX > 0) GravityGunVeloPos = aimX + (entityX);

			return GravityGunVeloPos;
		}
		void init() {
			if (enabled) {

				static bool locked = false;
				static int zoom = 5;
				static Entity current_entity{ NULL };

				if (locked) {
					if (PAD::IS_CONTROL_PRESSED(2, 25))
					{
						if (current_entity == NULL) {
							PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &current_entity);
						}
						else
						{
							if (ENTITY::IS_ENTITY_A_PED(current_entity) && PED::IS_PED_IN_ANY_VEHICLE(current_entity, true)) {
								current_entity = PED::GET_VEHICLE_PED_IS_IN(current_entity, 0);
							}

							take_control_of(current_entity);

							NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
							NativeVector3 coord = CAM::GET_GAMEPLAY_CAM_COORD();
							NativeVector3 dir = RotationToDirection(rot);
							NativeVector3 multiplyfr = multiply(&dir, zoom);
							NativeVector3 spawnPosition = addn(&coord, &multiplyfr);

							NativeVector3 getcoords = ENTITY::GET_ENTITY_COORDS(current_entity, 0);
							float getaimcoordsX = GravityGunGoto(spawnPosition.x, getcoords.x);
							float getaimcoordsY = GravityGunGoto(spawnPosition.y, getcoords.y);
							float getaimcoordsZ = GravityGunGoto(spawnPosition.z, getcoords.z);
							if (!PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
								ENTITY::SET_ENTITY_VELOCITY(current_entity, getaimcoordsX * 2.0, getaimcoordsY * 2.0, getaimcoordsZ * 2.0);
							}

							if (PAD::IS_CONTROL_PRESSED(2, 24))
							{

								ENTITY::APPLY_FORCE_TO_ENTITY(current_entity, 1, dir.x * m_force, dir.y * m_force, dir.z * m_force, 0.0f, 0.0f, 0.0f, false, false, true, true, false, true);
								PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
								current_entity = NULL;
								locked = false;
							}

						}

					}
					else {
						current_entity = NULL;
					}
				}

				if (!PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &current_entity)) {
					locked = true;
					PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
				}
			}
		}
	};
	inline GravityG gravity;
	inline const char* DriveType[3]
	{
		"Reckless", "Non-Reckless", "Avoid Roads"
	};
	class CRampTypes {
	public:
		bool m_left = false;
		Object left;
		bool m_right = false;
		Object right;
		bool m_front = false;
		Object front;
		bool m_back = false;
		Object back;
	};
	class CVehicleRamps {
	public:
		CRampTypes m_ramp_location;
		bool m_is_trasparent = false;
		const char* m_ramp_trasparency[6]
		{
			"0%", "20%", "40%", "60%", "80%", "100%"
		};
		std::size_t m_ramp_transparency_data = 5;
		const char* m_ramp_type[3]
		{
			"Small", "Medium", "Large"
		};
		const char* m_ramp_data[3]
		{
			 "prop_mp_ramp_01", "lts_prop_lts_ramp_02", "lts_prop_lts_ramp_03"
		};
		std::size_t m_ramp_type_data = 0;
		const char* m_remove_type[2]
		{
			 "Last", "Force"
		};
		std::size_t m_remove_data = 0;
		void init() {
			if (m_is_trasparent) {
				if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.back)) {
					switch (m_ramp_transparency_data) {
					case 0:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.back, 0, true);
						break;
					case 1:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.back, 51, true);
						break;
					case 2:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.back, 102, true);
						break;
					case 3:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.back, 153, true);
						break;
					case 4:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.back, 204, true);
						break;
					case 5:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.back, 255, false);
						break;
					}
				}
				if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.front)) {
					switch (m_ramp_transparency_data) {
					case 0:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.front, 0, true);
						break;
					case 1:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.front, 51, true);
						break;
					case 2:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.front, 102, true);
						break;
					case 3:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.front, 153, true);
						break;
					case 4:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.front, 204, true);
						break;
					case 5:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.front, 255, false);
						break;
					}
				}
				if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.left)) {
					switch (m_ramp_transparency_data) {
					case 0:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.left, 0, true);
						break;
					case 1:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.left, 51, true);
						break;
					case 2:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.left, 102, true);
						break;
					case 3:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.left, 153, true);
						break;
					case 4:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.left, 204, true);
						break;
					case 5:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.left, 255, false);
						break;
					}
				}
				if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.right)) {
					switch (m_ramp_transparency_data) {
					case 0:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.right, 0, true);
						break;
					case 1:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.right, 51, true);
						break;
					case 2:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.right, 102, true);
						break;
					case 3:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.right, 153, true);
						break;
					case 4:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.right, 204, true);
						break;
					case 5:
						ENTITY::SET_ENTITY_ALPHA(m_ramp_location.right, 255, false);
						break;
					}
				}
			}
		}
		void m_remove() {
			if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.left)) {
				OBJECT::DELETE_OBJECT(&m_ramp_location.left);
			}
			if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.front)) {
				OBJECT::DELETE_OBJECT(&m_ramp_location.front);
			}
			if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.back)) {
				OBJECT::DELETE_OBJECT(&m_ramp_location.back);
			}
			if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.right)) {
				OBJECT::DELETE_OBJECT(&m_ramp_location.right);
			}
		}
		void m_add_ramp() {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			Hash ramp = MISC::GET_HASH_KEY(m_ramp_data[m_ramp_type_data]);

			STREAMING::REQUEST_MODEL(ramp);
			if (ENTITY::DOES_ENTITY_EXIST(veh))
			{
				//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(veh);

				if (m_ramp_location.m_front)
				{
					m_ramp_location.front = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.front))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(m_ramp_location.front, veh, 0, 0, 5, 0.3f, 0, 0, 180, 0, 0, 0, 0, 2, 1, false);
						ENTITY::SET_ENTITY_COLLISION(m_ramp_location.front, 1, 0);
					}
				}

				if (m_ramp_location.m_back)
				{
					m_ramp_location.back = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.back))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(m_ramp_location.back, veh, 0, 0, -5, 0.3f, 0, 0, 360, 0, 0, 0, 0, 2, 1, false);
						ENTITY::SET_ENTITY_COLLISION(m_ramp_location.back, 1, 0);
					}
				}

				if (m_ramp_location.m_left)
				{
					m_ramp_location.left = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.left))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(m_ramp_location.left, veh, 0, -5, 0, 0.3f, 0, 0, -90, 0, 0, 0, 0, 2, 1, false);
						ENTITY::SET_ENTITY_COLLISION(m_ramp_location.left, 1, 0);
					}
				}

				if (m_ramp_location.m_right)
				{
					m_ramp_location.right = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(m_ramp_location.right))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(m_ramp_location.right, veh, 0, 5, 0, 0.3f, 0, 0, 90, 0, 0, 0, 0, 2, 1, false);
						ENTITY::SET_ENTITY_COLLISION(m_ramp_location.right, 1, 0);
					}
				}

			}
		}
	};
	inline CVehicleRamps m_vehicle_ramps;
	class CopyToClipboard {
	public:
		const char* to_copy[3] = { "RID", "Name", "Crew Data" };
		std::size_t data = 0;
	};
	inline CopyToClipboard c_clipboard;
	inline void copytoclipboard(const std::string& tocopy)
	{
		OpenClipboard(NULL);
		EmptyClipboard();
		HGLOBAL HG = GlobalAlloc(GMEM_MOVEABLE, tocopy.size());
		if (!HG)
		{
			CloseClipboard();
		}
		memcpy(GlobalLock(HG), tocopy.c_str(), tocopy.size());
		GlobalUnlock(HG);
		SetClipboardData(CF_TEXT, HG);
		CloseClipboard();
		GlobalFree(HG);
	}
	class Ini
	{
	private:
		std::string inifile;
	public:
		Ini(std::string file)
		{
			this->inifile = file;
		}

		void WriteString(std::string string, std::string app, std::string key)
		{
			WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), this->inifile.c_str());
		}
		std::string GetString(std::string app, std::string key)
		{
			char buf[100];
			GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, this->inifile.c_str());
			return (std::string)buf;
		}

		void WriteInt(int value, std::string app, std::string key)
		{
			WriteString(std::to_string(value), app, key);
		}
		void WriteHash(Hash value, std::string app, std::string key)
		{
			WriteString(std::to_string(value), app, key);
		}
		int GetInt(std::string app, std::string key)
		{
			return std::stoi(GetString(app, key));
		}

		void WriteFloat(float value, std::string app, std::string key)
		{
			WriteString(std::to_string(value), app, key);
		}
		float GetFloat(std::string app, std::string key)
		{
			return std::stof(GetString(app, key));
		}

		void WriteBool(bool value, std::string app, std::string key)
		{
			WriteString(std::to_string(value), app, key);
		}
		bool GetBool(std::string app, std::string key)
		{
			std::string Fetched = GetString(app, key);
			if (Fetched == "1") {
				return true;
			}
			if (Fetched == "0") {
				return false;
			}
			return false;
		}

	};
	class VehicleLoading {
	public:
		std::string name;
		bool VehicleIniExist(const char* path)
		{

			struct stat buffer;
			return (stat(path, &buffer) == 0);

		}

		void save() {
			std::string AppDataPath = getenv("APPDATA");
			std::string MenuFolderPath = AppDataPath + "\\Saint\\Vehicles\\";
			Ini* ColorIni = new Ini(MenuFolderPath + "Saved.ini");
			Hash hash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
			ColorIni->WriteHash(hash, "Info", "hash");
		}
		void load() {
			std::string AppDataPath = getenv("APPDATA");
			std::string MenuFolderPath = AppDataPath + "\\Saint\\Vehicles\\";
			if (VehicleIniExist((MenuFolderPath + "Saved.ini").c_str())) {
				Ini* ColorIni = new Ini(MenuFolderPath + "Saved.ini");
				Vehicle spawned;
				veh_spawner.spawn(ColorIni->GetInt("Info", "hash"), &spawned);
			}
		}
	};
	inline VehicleLoading* g_VehicleLoading;
	class ThemeLoading {
	public:
		std::string buffer;
		bool DoesIniExists(const char* path)
		{

			struct stat buffer;
			return (stat(path, &buffer) == 0);

		}
		void save(std::string name) {
			auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
			std::string MenuFolderPath = "C:\\Saint\\Themes\\";
			Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");


			ColorIni->WriteString(g_Render->header_name, "Header", "text");
			ColorIni->WriteInt(g_Render->ToggleIterator, "Toggles", "icon");
			ColorIni->WriteBool(g_Render->submenu_enabled, "Subheader", "enabled");
			ColorIni->WriteBool(g_Render->m_render_glare, "Glare", "enabled");
			ColorIni->WriteInt(g_Render->m_OptionUnselectedBackgroundColor.r, "BackgroundUnselected", "r");
			ColorIni->WriteInt(g_Render->m_OptionUnselectedBackgroundColor.g, "BackgroundUnselected", "g");
			ColorIni->WriteInt(g_Render->m_OptionUnselectedBackgroundColor.b, "BackgroundUnselected", "b");
			ColorIni->WriteInt(g_Render->m_OptionUnselectedBackgroundColor.a, "BackgroundUnselected", "a");

			ColorIni->WriteInt(g_Render->m_OptionSelectedBackgroundColor.r, "BackgroundSelected", "r");
			ColorIni->WriteInt(g_Render->m_OptionSelectedBackgroundColor.g, "BackgroundSelected", "g");
			ColorIni->WriteInt(g_Render->m_OptionSelectedBackgroundColor.b, "BackgroundSelected", "b");
			ColorIni->WriteInt(g_Render->m_OptionSelectedBackgroundColor.a, "BackgroundSelected", "a");

			ColorIni->WriteInt(g_Render->m_HeaderBackgroundColor.r, "HeaderBackground", "r");
			ColorIni->WriteInt(g_Render->m_HeaderBackgroundColor.g, "HeaderBackground", "g");
			ColorIni->WriteInt(g_Render->m_HeaderBackgroundColor.b, "HeaderBackground", "b");
			ColorIni->WriteInt(g_Render->m_HeaderBackgroundColor.a, "HeaderBackground", "a");

			ColorIni->WriteBool(g_Render->m_dynamic_footer, "Footer", "dynamic");
			ColorIni->WriteBool(g_Render->lines_enabled, "Lines", "enabled");

			//footer
			ColorIni->WriteFloat(g_Render->m_FooterHeight, "Footer", "height");
			ColorIni->WriteFloat(g_Render->m_FooterSpriteSize, "Footer", "sprite_size");

			//submenu
			ColorIni->WriteInt(g_Render->IndicatorIterator, "Submenu", "icon");

			//smooth scroll
			ColorIni->WriteFloat(g_Render->smooth_scroll_speed, "SmoothScroll", "speed");

			//toggles
			ColorIni->WriteFloat(g_Render->toggle_height, "Toggles", "on_height");
			ColorIni->WriteFloat(g_Render->toggle_height_off, "Toggles", "off_height");
			ColorIni->WriteFloat(g_Render->toggle_width, "Toggles", "on_width");
			ColorIni->WriteFloat(g_Render->toggle_width_off, "Toggles", "off_width");


		}
		void load(std::string name) {
			std::string MenuFolderPath = "C:\\Saint\\Themes\\";
			if (DoesIniExists((MenuFolderPath + name + ".ini").c_str())) {
				Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
				g_Render->header_name = ColorIni->GetString("Header", "text");
				g_Render->ToggleIterator = ColorIni->GetInt("Toggles", "icon");
				g_Render->submenu_enabled = ColorIni->GetBool("Subheader", "enabled");
				g_Render->m_render_glare = ColorIni->GetBool("Glare", "enabled");
				g_Render->m_OptionUnselectedBackgroundColor.r = ColorIni->GetInt("BackgroundUnselected", "r");
				g_Render->m_OptionUnselectedBackgroundColor.g = ColorIni->GetInt("BackgroundUnselected", "g");
				g_Render->m_OptionUnselectedBackgroundColor.b = ColorIni->GetInt("BackgroundUnselected", "b");
				g_Render->m_OptionUnselectedBackgroundColor.a = ColorIni->GetInt("BackgroundUnselected", "a");

				g_Render->m_OptionSelectedBackgroundColor.r = ColorIni->GetInt("BackgroundSelected", "r");
				g_Render->m_OptionSelectedBackgroundColor.g = ColorIni->GetInt("BackgroundSelected", "g");
				g_Render->m_OptionSelectedBackgroundColor.b = ColorIni->GetInt("BackgroundSelected", "b");
				g_Render->m_OptionSelectedBackgroundColor.a = ColorIni->GetInt("BackgroundSelected", "a");

				g_Render->m_HeaderBackgroundColor.r = ColorIni->GetInt("HeaderBackground", "r");
				g_Render->m_HeaderBackgroundColor.g = ColorIni->GetInt("HeaderBackground", "g");
				g_Render->m_HeaderBackgroundColor.b = ColorIni->GetInt("HeaderBackground", "b");
				g_Render->m_HeaderBackgroundColor.a = ColorIni->GetInt("HeaderBackground", "a");

				g_Render->m_dynamic_footer = ColorIni->GetBool("Footer", "dynamic");
				g_Render->lines_enabled = ColorIni->GetBool("Lines", "enabled");

				//footer
				g_Render->m_FooterHeight = ColorIni->GetFloat("Footer", "height");
				g_Render->m_FooterSpriteSize = ColorIni->GetFloat("Footer", "sprite_size");

				//submenu
				g_Render->IndicatorIterator = ColorIni->GetInt("Submenu", "icon");

				//smooth scroll
				g_Render->smooth_scroll_speed = ColorIni->GetFloat("SmoothScroll", "speed");

				//toggles
				g_Render->toggle_height = ColorIni->GetFloat("Toggles", "on_height");
				g_Render->toggle_height_off = ColorIni->GetFloat("Toggles", "off_height");
				g_Render->toggle_width = ColorIni->GetFloat("Toggles", "on_width");
				g_Render->toggle_width_off = ColorIni->GetFloat("Toggles", "off_width");

				Noti::InsertNotification({ ImGuiToastType_None, 2000, "Loaded '%s'", name });




			}
		}
	};
	inline ThemeLoading g_ThemeLoading;
	class SaveHandling {
	public:
		bool DoesIniExists(const char* path)
		{

			struct stat buffer;
			return (stat(path, &buffer) == 0);

		}
		void save(std::string name) {
			auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
			std::string MenuFolderPath = "C:\\Saint\\Handling\\";
			Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
			ColorIni->WriteFloat(handling->m_acceleration, "Handling", "m_acceleration");
			ColorIni->WriteFloat(handling->m_mass, "Handling", "m_mass");
			ColorIni->WriteFloat(handling->m_buoyancy, "Handling", "m_buoyancy");
			ColorIni->WriteFloat(handling->m_brake_force, "Handling", "m_brake_force");
			ColorIni->WriteFloat(handling->m_traction_bias_front, "Handling", "m_traction_bias_front");
			ColorIni->WriteFloat(handling->m_traction_bias_rear, "Handling", "m_traction_bias_rear");
			ColorIni->WriteFloat(handling->m_traction_curve_min, "Handling", "m_traction_curve_min");
			ColorIni->WriteFloat(handling->m_traction_curve_max, "Handling", "m_traction_curve_max");
			ColorIni->WriteFloat(handling->m_centre_of_mass.x, "Handling", "m_centre_of_mass_x");
			ColorIni->WriteFloat(handling->m_centre_of_mass.y, "Handling", "m_centre_of_mass_y");
			ColorIni->WriteFloat(handling->m_centre_of_mass.z, "Handling", "m_centre_of_mass_z");
			ColorIni->WriteFloat(handling->m_drive_bias_front, "Handling", "m_drive_bias_front");
			ColorIni->WriteFloat(handling->m_drive_bias_rear, "Handling", "m_drive_bias_rear");
			ColorIni->WriteFloat(handling->m_drive_inertia, "Handling", "m_drive_inertia");
			ColorIni->WriteFloat(handling->m_inertia_mult.x, "Handling", "m_inertia_mult_x");
			ColorIni->WriteFloat(handling->m_inertia_mult.y, "Handling", "m_inertia_mult_y");
			ColorIni->WriteFloat(handling->m_inertia_mult.z, "Handling", "m_inertia_mult_z");
			ColorIni->WriteFloat(handling->m_steering_lock, "Handling", "m_steering_lock");
			ColorIni->WriteFloat(handling->m_traction_curve_lateral, "Handling", "m_traction_curve_lateral");
			ColorIni->WriteFloat(handling->m_traction_curve_ratio, "Handling", "m_traction_curve_ratio");
			ColorIni->WriteFloat(handling->m_low_speed_traction_loss_mult, "Handling", "m_low_speed_traction_loss_mult");
			ColorIni->WriteFloat(handling->m_traction_spring_delta_max, "Handling", "m_traction_spring_delta_max");
			ColorIni->WriteFloat(handling->m_traction_spring_delta_max_ratio, "Handling", "m_traction_spring_delta_max_ratio");
		}
		void load(std::string name) {
			std::string MenuFolderPath = "C:\\Saint\\Handling\\";
			if (DoesIniExists((MenuFolderPath + name + ".ini").c_str())) {
				Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
				auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
				handling->m_acceleration = ColorIni->GetFloat("Handling", "m_acceleration");
				handling->m_mass = ColorIni->GetFloat("Handling", "m_mass");
				handling->m_buoyancy = ColorIni->GetFloat("Handling", "m_buoyancy");
				handling->m_brake_force = ColorIni->GetFloat("Handling", "m_brake_force");
				handling->m_traction_bias_front = ColorIni->GetFloat("Handling", "m_traction_bias_front");
				handling->m_traction_bias_rear = ColorIni->GetFloat("Handling", "m_traction_bias_rear");
				handling->m_traction_curve_min = ColorIni->GetFloat("Handling", "m_traction_curve_min");
				handling->m_traction_curve_max = ColorIni->GetFloat("Handling", "m_traction_curve_max");
				handling->m_centre_of_mass.x = ColorIni->GetFloat("Handling", "m_centre_of_mass_x");
				handling->m_centre_of_mass.y = ColorIni->GetFloat("Handling", "m_centre_of_mass_y");
				handling->m_centre_of_mass.z = ColorIni->GetFloat("Handling", "m_centre_of_mass_z");
				handling->m_drive_bias_front = ColorIni->GetFloat("Handling", "m_drive_bias_front");
				handling->m_drive_bias_rear = ColorIni->GetFloat("Handling", "m_drive_bias_rear");
				handling->m_drive_inertia = ColorIni->GetFloat("Handling", "m_drive_inertia");
				handling->m_inertia_mult.x = ColorIni->GetFloat("Handling", "m_inertia_mult_x");
				handling->m_inertia_mult.y = ColorIni->GetFloat("Handling", "m_inertia_mult_y");
				handling->m_inertia_mult.z = ColorIni->GetFloat("Handling", "m_inertia_mult_z");
				handling->m_steering_lock = ColorIni->GetFloat("Handling", "m_steering_lock");
				handling->m_traction_curve_lateral = ColorIni->GetFloat("Handling", "m_traction_curve_lateral");
				handling->m_traction_curve_ratio = ColorIni->GetFloat("Handling", "m_traction_curve_ratio");
				handling->m_low_speed_traction_loss_mult = ColorIni->GetFloat("Handling", "m_low_speed_traction_loss_mult");
				handling->m_traction_spring_delta_max = ColorIni->GetFloat("Handling", "m_traction_spring_delta_max");
				handling->m_traction_spring_delta_max_ratio = ColorIni->GetFloat("Handling", "m_traction_spring_delta_max_ratio");
				Noti::InsertNotification({ ImGuiToastType_None, 2000, "Loaded '%s'", name});




			}
		}
	};
	inline SaveHandling m_handling;
	class VehicleLoad {
	public:

		bool DoesIniExists(const char* path)
		{

			struct stat buffer;
			return (stat(path, &buffer) == 0);

		}
		void save(std::string name) {
			
			std::string MenuFolderPath = "C:\\Saint\\Vehicles\\";
			Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			int r, g, b;
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &r, &g, &b);
			int r2, g2, b2;
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &r2, &g2, &b2);
			int hash = ENTITY::GET_ENTITY_MODEL(veh);
			int primaryColor, secondaryColor;
			VEHICLE::GET_VEHICLE_COLOURS(veh, &primaryColor, &secondaryColor);
			ColorIni->WriteString(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(veh)), "Info", "Name");
			ColorIni->WriteInt(r, "Color", "R");
			ColorIni->WriteInt(g, "Color", "G");
			ColorIni->WriteInt(b, "Color", "B");
			ColorIni->WriteInt(r2, "Color", "R2");
			ColorIni->WriteInt(g2, "Color", "G2");
			ColorIni->WriteInt(b2, "Color", "B2");
			ColorIni->WriteInt(VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh), "wheel", "type");
			ColorIni->WriteInt(VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh), "plate", "index");
			ColorIni->WriteString(VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(veh), "plate", "text");
			ColorIni->WriteInt(VEHICLE::GET_VEHICLE_MOD(veh, MOD_LIVERY), "upgrades", "livery");
			ColorIni->WriteInt(VEHICLE::GET_VEHICLE_MOD(veh, MOD_SPOILER), "upgrades", "spoiler");
			ColorIni->WriteInt(primaryColor, "Color1", "index");
			ColorIni->WriteInt(secondaryColor, "Color2", "index");
			for (int i = 0; i < 50; i++)
			{
				char input2[64];
				sprintf(input2, "index_%i", i);
				ColorIni->WriteInt(VEHICLE::GET_VEHICLE_MOD(veh, i), "upgrades", input2);
				
			}
			
		}
		void load(std::string name) {
			std::string MenuFolderPath = "C:\\Saint\\Vehicles\\";
			if (DoesIniExists((MenuFolderPath + name + ".ini").c_str())) {
				Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
				
				
				
				*script_global(4540726).as<bool*>() = true;
				Hash hash = MISC::GET_HASH_KEY(ColorIni->GetString("Info", "Name").c_str());
				g_CallbackScript->AddCallback<ModelCallback>(hash, [=]
					{
						
				


						NativeVector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(PLAYER::PLAYER_PED_ID(), { 0.f, 0.f, 1.0f });
						*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
						Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, false, false);
						*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
						DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
						auto networkId = NETWORK::VEH_TO_NET(vehicle);
						if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
							NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
						VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, ColorIni->GetInt("Color", "R"), ColorIni->GetInt("Color", "G"), ColorIni->GetInt("Color", "B"));
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, ColorIni->GetInt("Color", "R2"), ColorIni->GetInt("Color", "G2"), ColorIni->GetInt("Color", "B2"));
						VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
						VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, ColorIni->GetInt("wheel", "type"));
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, ColorIni->GetInt("plate", "index"));
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, ColorIni->GetString("plate", "text").c_str());
						VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_LIVERY, ColorIni->GetInt("upgrades", "livery"), false);
						VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SPOILER, ColorIni->GetInt("upgrades", "spoiler"), false);
						VEHICLE::SET_VEHICLE_COLOURS(vehicle, ColorIni->GetInt("Color1", "index"), ColorIni->GetInt("Color2", "index"));
						for (int i = 0; i < 50; i++)
						{
							char input2[64];
							sprintf(input2, "index_%i", i);
							VEHICLE::SET_VEHICLE_MOD(vehicle, i, ColorIni->GetInt("upgrades", input2), false);
						}
				
				
					});
				


			}
		}
	};
	inline VehicleLoad m_VehicleLoad;
	class Scripts {
	public:
		void load(fs::path asi_path) {
			PEImage pluginImage;
			if (!pluginImage.Load(asi_path.string().data())) {

				g_Logger->Info("Failed to load image...");
			}
			// Image not compatible, needs patching
			if (!pluginImage.IsOpenVHookCompatible()) {

				g_Logger->Info("Incompatible image identified, patching...");

				if (pluginImage.PatchCompatibility()) {
					g_Logger->Info("Patching complete...");
				}
				else {

					g_Logger->Info("Failed to patch image...");
				}
			}
			g_Logger->Info("Loading \"%s\"", asi_path.string().data());

			auto module = LoadLibraryA(asi_path.string().data());
			if (!module)
			{
				DWORD error = ::GetLastError();
				//g_Logger->Info(to_string(error).c_str());
				LPSTR messageBuffer = nullptr;
				FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
			}
			Noti::InsertNotification({ ImGuiToastType_None, 2000, "Loaded!" });
			return;
		}
	};
	inline Scripts* g_Scripts;
	class CLevel {
	public:
		int Levels[8000] = { 0, 800, 2100, 3800, 6100, 9500, 12500, 16000, 19800, 24000, 28500, 33400, 38700, 44200, 50200, 56400, 63000, 69900, 77100, 84700, 92500, 100700, 109200, 118000, 127100, 136500, 146200,
	156200, 166500, 177100, 188000, 199200, 210700, 222400, 234500, 246800, 259400, 272300, 285500, 299000, 312700, 326800, 341000, 355600, 370500, 385600, 401000, 416600, 432600, 448800, 465200, 482000, 499000,
	516300, 533800, 551600, 569600, 588000, 606500, 625400, 644500, 663800, 683400, 703300, 723400, 743800, 764500, 785400, 806500, 827900, 849600, 871500, 893600, 916000, 938700, 961600, 984700, 1008100, 1031800,
	1055700, 1079800, 1104200, 1128800, 1153700, 1178800, 1204200, 1229800, 1255600, 1281700, 1308100, 1334600, 1361400, 1388500, 1415800, 1443300, 1471100, 1499100, 1527300, 1555800, 1584350, 1612950, 1641600,
	1670300, 1699050, 1727850, 1756700, 1785600, 1814550, 1843550, 1872600, 1901700, 1930850, 1960050, 1989300, 2018600, 2047950, 2077350, 2106800, 2136300, 2165850, 2195450, 2225100, 2254800, 2284550, 2314350,
	2344200, 2374100, 2404050, 2434050, 2464100, 2494200, 2524350, 2554550, 2584800, 2615100, 2645450, 2675850, 2706300, 2736800, 2767350, 2797950, 2828600, 2859300, 2890050, 2920850, 2951700, 2982600, 3013550,
	3044550, 3075600, 3106700, 3137850, 3169050, 3200300, 3231600, 3262950, 3294350, 3325800, 3357300, 3388850, 3420450, 3452100, 3483800, 3515550, 3547350, 3579200, 3611100, 3643050, 3675050, 3707100, 3739200,
	3771350, 3803550, 3835800, 3868100, 3900450, 3932850, 3965300, 3997800, 4030350, 4062950, 4095600, 4128300, 4161050, 4193850, 4226700, 4259600, 4292550, 4325550, 4358600, 4391700, 4424850, 4458050, 4491300,
	4524600, 4557950, 4591350, 4624800, 4658300, 4691850, 4725450, 4759100, 4792800, 4826550, 4860350, 4894200, 4928100, 4962050, 4996050, 5030100, 5064200, 5098350, 5132550, 5166800, 5201100, 5235450, 5269850,
	5304300, 5338800, 5373350, 5407950, 5442600, 5477300, 5512050, 5546850, 5581700, 5616600, 5651550, 5686550, 5721600, 5756700, 5791850, 5827050, 5862300, 5897600, 5932950, 5968350, 6003800, 6039300, 6074850,
	6110450, 6146100, 6181800, 6217550, 6253350, 6289200, 6325100, 6361050, 6397050, 6433100, 6469200, 6505350, 6541550, 6577800, 6614100, 6650450, 6686850, 6723300, 6759800, 6796350, 6832950, 6869600, 6906300,
	6943050, 6979850, 7016700, 7053600, 7090550, 7127550, 7164600, 7201700, 7238850, 7276050, 7313300, 7350600, 7387950, 7425350, 7462800, 7500300, 7537850, 7575450, 7613100, 7650800, 7688550, 7726350, 7764200,
	7802100, 7840050, 7878050, 7916100, 7954200, 7992350, 8030550, 8068800, 8107100, 8145450, 8183850, 8222300, 8260800, 8299350, 8337950, 8376600, 8415300, 8454050, 8492850, 8531700, 8570600, 8609550, 8648550,
	8687600, 8726700, 8765850, 8805050, 8844300, 8883600, 8922950, 8962350, 9001800, 9041300, 9080850, 9120450, 9160100, 9199800, 9239550, 9279350, 9319200, 9359100, 9399050, 9439050, 9479100, 9519200, 9559350,
	9599550, 9639800, 9680100, 9720450, 9760850, 9801300, 9841800, 9882350, 9922950, 9963600, 10004300, 10045050, 10085850, 10126700, 10167600, 10208550, 10249550, 10290600, 10331700, 10372850, 10414050, 10455300,
	10496600, 10537950, 10579350, 10620800, 10662300, 10703850, 10745450, 10787100, 10828800, 10870550, 10912350, 10954200, 10996100, 11038050, 11080050, 11122100, 11164200, 11206350, 11248550, 11290800, 11333100,
	11375450, 11417850, 11460300, 11502800, 11545350, 11587950, 11630600, 11673300, 11716050, 11758850, 11801700, 11844600, 11887550, 11930550, 11973600, 12016700, 12059850, 12103050, 12146300, 12189600, 12232950,
	12276350, 12319800, 12363300, 12406850, 12450450, 12494100, 12537800, 12581550, 12625350, 12669200, 12713100, 12757050, 12801050, 12845100, 12889200, 12933350, 12977550, 13021800, 13066100, 13110450, 13154850,
	13199300, 13243800, 13288350, 13332950, 13377600, 13422300, 13467050, 13511850, 13556700, 13601600, 13646550, 13691550, 13736600, 13781700, 13826850, 13872050, 13917300, 13962600, 14007950, 14053350, 14098800,
	14144300, 14189850, 14235450, 14281100, 14326800, 14372550, 14418350, 14464200, 14510100, 14556050, 14602050, 14648100, 14694200, 14740350, 14786550, 14832800, 14879100, 14925450, 14971850, 15018300, 15064800,
	15111350, 15157950, 15204600, 15251300, 15298050, 15344850, 15391700, 15438600, 15485550, 15532550, 15579600, 15626700, 15673850, 15721050, 15768300, 15815600, 15862950, 15910350, 15957800, 16005300, 16052850,
	16100450, 16148100, 16195800, 16243550, 16291350, 16339200, 16387100, 16435050, 16483050, 16531100, 16579200, 16627350, 16675550, 16723800, 16772100, 16820450, 16868850, 16917300, 16965800, 17014350, 17062950,
	17111600, 17160300, 17209050, 17257850, 17306700, 17355600, 17404550, 17453550, 17502600, 17551700, 17600850, 17650050, 17699300, 17748600, 17797950, 17847350, 17896800, 17946300, 17995850, 18045450, 18095100,
	18144800, 18194550, 18244350, 18294200, 18344100, 18394050, 18444050, 18494100, 18544200, 18594350, 18644550, 18694800, 18745100, 18795450, 18845850, 18896300, 18946800, 18997350, 19047950, 19098600, 19149300,
	19200050, 19250850, 19301700, 19352600, 19403550, 19454550, 19505600, 19556700, 19607850, 19659050, 19710300, 19761600, 19812950, 19864350, 19915800, 19967300, 20018850, 20070450, 20122100, 20173800, 20225550,
	20277350, 20329200, 20381100, 20433050, 20485050, 20537100, 20589200, 20641350, 20693550, 20745800, 20798100, 20850450, 20902850, 20955300, 21007800, 21060350, 21112950, 21165600, 21218300, 21271050, 21323850,
	21376700, 21429600, 21482550, 21535550, 21588600, 21641700, 21694850, 21748050, 21801300, 21854600, 21907950, 21961350, 22014800, 22068300, 22121850, 22175450, 22229100, 22282800, 22336550, 22390350, 22444200,
	22498100, 22552050, 22606050, 22660100, 22714200, 22768350, 22822550, 22876800, 22931100, 22985450, 23039850, 23094300, 23148800, 23203350, 23257950, 23312600, 23367300, 23422050, 23476850, 23531700, 23586600,
	23641550, 23696550, 23751600, 23806700, 23861850, 23917050, 23972300, 24027600, 24082950, 24138350, 24193800, 24249300, 24304850, 24360450, 24416100, 24471800, 24527550, 24583350, 24639200, 24695100, 24751050,
	24807050, 24863100, 24919200, 24975350, 25031550, 25087800, 25144100, 25200450, 25256850, 25313300, 25369800, 25426350, 25482950, 25539600, 25596300, 25653050, 25709850, 25766700, 25823600, 25880550, 25937550,
	25994600, 26051700, 26108850, 26166050, 26223300, 26280600, 26337950, 26395350, 26452800, 26510300, 26567850, 26625450, 26683100, 26740800, 26798550, 26856350, 26914200, 26972100, 27030050, 27088050, 27146100,
	27204200, 27262350, 27320550, 27378800, 27437100, 27495450, 27553850, 27612300, 27670800, 27729350, 27787950, 27846600, 27905300, 27964050, 28022850, 28081700, 28140600, 28199550, 28258550, 28317600, 28376700,
	28435850, 28495050, 28554300, 28613600, 28672950, 28732350, 28791800, 28851300, 28910850, 28970450, 29030100, 29089800, 29149550, 29209350, 29269200, 29329100, 29389050, 29449050, 29509100, 29569200, 29629350,
	29689550, 29749800, 29810100, 29870450, 29930850, 29991300, 30051800, 30112350, 30172950, 30233600, 30294300, 30355050, 30415850, 30476700, 30537600, 30598550, 30659550, 30720600, 30781700, 30842850, 30904050,
	30965300, 31026600, 31087950, 31149350, 31210800, 31272300, 31333850, 31395450, 31457100, 31518800, 31580550, 31642350, 31704200, 31766100, 31828050, 31890050, 31952100, 32014200, 32076350, 32138550, 32200800,
	32263100, 32325450, 32387850, 32450300, 32512800, 32575350, 32637950, 32700600, 32763300, 32826050, 32888850, 32951700, 33014600, 33077550, 33140550, 33203600, 33266700, 33329850, 33393050, 33456300, 33519600,
	33582950, 33646350, 33709800, 33773300, 33836850, 33900450, 33964100, 34027800, 34091550, 34155350, 34219200, 34283100, 34347050, 34411050, 34475100, 34539200, 34603350, 34667550, 34731800, 34796100, 34860450,
	34924850, 34989300, 35053800, 35118350, 35182950, 35247600, 35312300, 35377050, 35441850, 35506700, 35571600, 35636550, 35701550, 35766600, 35831700, 35896850, 35962050, 36027300, 36092600, 36157950, 36223350,
	36288800, 36354300, 36419850, 36485450, 36551100, 36616800, 36682550, 36748350, 36814200, 36880100, 36946050, 37012050, 37078100, 37144200, 37210350, 37276550, 37342800, 37409100, 37475450, 37541850, 37608300,
	37674800, 37741350, 37807950, 37874600, 37941300, 38008050, 38074850, 38141700, 38208600, 38275550, 38342550, 38409600, 38476700, 38543850, 38611050, 38678300, 38745600, 38812950, 38880350, 38947800, 39015300,
	39082850, 39150450, 39218100, 39285800, 39353550, 39421350, 39489200, 39557100, 39625050, 39693050, 39761100, 39829200, 39897350, 39965550, 40033800, 40102100, 40170450, 40238850, 40307300, 40375800, 40444350,
	40512950, 40581600, 40650300, 40719050, 40787850, 40856700, 40925600, 40994550, 41063550, 41132600, 41201700, 41270850, 41340050, 41409300, 41478600, 41547950, 41617350, 41686800, 41756300, 41825850, 41895450,
	41965100, 42034800, 42104550, 42174350, 42244200, 42314100, 42384050, 42454050, 42524100, 42594200, 42664350, 42734550, 42804800, 42875100, 42945450, 43015850, 43086300, 43156800, 43227350, 43297950, 43368600,
	43439300, 43510050, 43580850, 43651700, 43722600, 43793550, 43864550, 43935600, 44006700, 44077850, 44149050, 44220300, 44291600, 44362950, 44434350, 44505800, 44577300, 44648850, 44720450, 44792100, 44863800,
	44935550, 45007350, 45079200, 45151100, 45223050, 45295050, 45367100, 45439200, 45511350, 45583550, 45655800, 45728100, 45800450, 45872850, 45945300, 46017800, 46090350, 46162950, 46235600, 46308300, 46381050,
	46453850, 46526700, 46599600, 46672550, 46745550, 46818600, 46891700, 46964850, 47038050, 47111300, 47184600, 47257950, 47331350, 47404800, 47478300, 47551850, 47625450, 47699100, 47772800, 47846550, 47920350,
	47994200, 48068100, 48142050, 48216050, 48290100, 48364200, 48438350, 48512550, 48586800, 48661100, 48735450, 48809850, 48884300, 48958800, 49033350, 49107950, 49182600, 49257300, 49332050, 49406850, 49481700,
	49556600, 49631550, 49706550, 49781600, 49856700, 49931850, 50007050, 50082300, 50157600, 50232950, 50308350, 50383800, 50459300, 50534850, 50610450, 50686100, 50761800, 50837550, 50913350, 50989200, 51065100,
	51141050, 51217050, 51293100, 51369200, 51445350, 51521550, 51597800, 51674100, 51750450, 51826850, 51903300, 51979800, 52056350, 52132950, 52209600, 52286300, 52363050, 52439850, 52516700, 52593600, 52670550,
	52747550, 52824600, 52901700, 52978850, 53056050, 53133300, 53210600, 53287950, 53365350, 53442800, 53520300, 53597850, 53675450, 53753100, 53830800, 53908550, 53986350, 54064200, 54142100, 54220050, 54298050,
	54376100, 54454200, 54532350, 54610550, 54688800, 54767100, 54845450, 54923850, 55002300, 55080800, 55159350, 55237950, 55316600, 55395300, 55474050, 55552850, 55631700, 55710600, 55789550, 55868550, 55947600,
	56026700, 56105850, 56185050, 56264300, 56343600, 56422950, 56502350, 56581800, 56661300, 56740850, 56820450, 56900100, 56979800, 57059550, 57139350, 57219200, 57299100, 57379050, 57459050, 57539100, 57619200,
	57699350, 57779550, 57859800, 57940100, 58020450, 58100850, 58181300, 58261800, 58342350, 58422950, 58503600, 58584300, 58665050, 58745850, 58826700, 58907600, 58988550, 59069550, 59150600, 59231700, 59312850,
	59394050, 59475300, 59556600, 59637950, 59719350, 59800800, 59882300, 59963850, 60045450, 60127100, 60208800, 60290550, 60372350, 60454200, 60536100, 60618050, 60700050, 60782100, 60864200, 60946350, 61028550,
	61110800, 61193100, 61275450, 61357850, 61440300, 61522800, 61605350, 61687950, 61770600, 61853300, 61936050, 62018850, 62101700, 62184600, 62267550, 62350550, 62433600, 62516700, 62599850, 62683050, 62766300,
	62849600, 62932950, 63016350, 63099800, 63183300, 63266850, 63350450, 63434100, 63517800, 63601550, 63685350, 63769200, 63853100, 63937050, 64021050, 64105100, 64189200, 64273350, 64357550, 64441800, 64526100,
	64610450, 64694850, 64779300, 64863800, 64948350, 65032950, 65117600, 65202300, 65287050, 65371850, 65456700, 65541600, 65626550, 65711550, 65796600, 65881700, 65966850, 66052050, 66137300, 66222600, 66307950,
	66393350, 66478800, 66564300, 66649850, 66735450, 66821100, 66906800, 66992550, 67078350, 67164200, 67250100, 67336050, 67422050, 67508100, 67594200, 67680350, 67766550, 67852800, 67939100, 68025450, 68111850,
	68198300, 68284800, 68371350, 68457950, 68544600, 68631300, 68718050, 68804850, 68891700, 68978600, 69065550, 69152550, 69239600, 69326700, 69413850, 69501050, 69588300, 69675600, 69762950, 69850350, 69937800,
	70025300, 70112850, 70200450, 70288100, 70375800, 70463550, 70551350, 70639200, 70727100, 70815050, 70903050, 70991100, 71079200, 71167350, 71255550, 71343800, 71432100, 71520450, 71608850, 71697300, 71785800,
	71874350, 71962950, 72051600, 72140300, 72229050, 72317850, 72406700, 72495600, 72584550, 72673550, 72762600, 72851700, 72940850, 73030050, 73119300, 73208600, 73297950, 73387350, 73476800, 73566300, 73655850,
	73745450, 73835100, 73924800, 74014550, 74104350, 74194200, 74284100, 74374050, 74464050, 74554100, 74644200, 74734350, 74824550, 74914800, 75005100, 75095450, 75185850, 75276300, 75366800, 75457350, 75547950,
	75638600, 75729300, 75820050, 75910850, 76001700, 76092600, 76183550, 76274550, 76365600, 76456700, 76547850, 76639050, 76730300, 76821600, 76912950, 77004350, 77095800, 77187300, 77278850, 77370450, 77462100,
	77553800, 77645550, 77737350, 77829200, 77921100, 78013050, 78105050, 78197100, 78289200, 78381350, 78473550, 78565800, 78658100, 78750450, 78842850, 78935300, 79027800, 79120350, 79212950, 79305600, 79398300,
	79491050, 79583850, 79676700, 79769600, 79862550, 79955550, 80048600, 80141700, 80234850, 80328050, 80421300, 80514600, 80607950, 80701350, 80794800, 80888300, 80981850, 81075450, 81169100, 81262800, 81356550,
	81450350, 81544200, 81638100, 81732050, 81826050, 81920100, 82014200, 82108350, 82202550, 82296800, 82391100, 82485450, 82579850, 82674300, 82768800, 82863350, 82957950, 83052600, 83147300, 83242050, 83336850,
	83431700, 83526600, 83621550, 83716550, 83811600, 83906700, 84001850, 84097050, 84192300, 84287600, 84382950, 84478350, 84573800, 84669300, 84764850, 84860450, 84956100, 85051800, 85147550, 85243350, 85339200,
	85435100, 85531050, 85627050, 85723100, 85819200, 85915350, 86011550, 86107800, 86204100, 86300450, 86396850, 86493300, 86589800, 86686350, 86782950, 86879600, 86976300, 87073050, 87169850, 87266700, 87363600,
	87460550, 87557550, 87654600, 87751700, 87848850, 87946050, 88043300, 88140600, 88237950, 88335350, 88432800, 88530300, 88627850, 88725450, 88823100, 88920800, 89018550, 89116350, 89214200, 89312100, 89410050,
	89508050, 89606100, 89704200, 89802350, 89900550, 89998800, 90097100, 90195450, 90293850, 90392300, 90490800, 90589350, 90687950, 90786600, 90885300, 90984050, 91082850, 91181700, 91280600, 91379550, 91478550,
	91577600, 91676700, 91775850, 91875050, 91974300, 92073600, 92172950, 92272350, 92371800, 92471300, 92570850, 92670450, 92770100, 92869800, 92969550, 93069350, 93169200, 93269100, 93369050, 93469050, 93569100,
	93669200, 93769350, 93869550, 93969800, 94070100, 94170450, 94270850, 94371300, 94471800, 94572350, 94672950, 94773600, 94874300, 94975050, 95075850, 95176700, 95277600, 95378550, 95479550, 95580600, 95681700,
	95782850, 95884050, 95985300, 96086600, 96187950, 96289350, 96390800, 96492300, 96593850, 96695450, 96797100, 96898800, 97000550, 97102350, 97204200, 97306100, 97408050, 97510050, 97612100, 97714200, 97816350,
	97918550, 98020800, 98123100, 98225450, 98327850, 98430300, 98532800, 98635350, 98737950, 98840600, 98943300, 99046050, 99148850, 99251700, 99354600, 99457550, 99560550, 99663600, 99766700, 99869850, 99973050,
	100076300, 100179600, 100282950, 100386350, 100489800, 100593300, 100696850, 100800450, 100904100, 101007800, 101111550, 101215350, 101319200, 101423100, 101527050, 101631050, 101735100, 101839200, 101943350,
	102047550, 102151800, 102256100, 102360450, 102464850, 102569300, 102673800, 102778350, 102882950, 102987600, 103092300, 103197050, 103301850, 103406700, 103511600, 103616550, 103721550, 103826600, 103931700,
	104036850, 104142050, 104247300, 104352600, 104457950, 104563350, 104668800, 104774300, 104879850, 104985450, 105091100, 105196800, 105302550, 105408350, 105514200, 105620100, 105726050, 105832050, 105938100,
	106044200, 106150350, 106256550, 106362800, 106469100, 106575450, 106681850, 106788300, 106894800, 107001350, 107107950, 107214600, 107321300, 107428050, 107534850, 107641700, 107748600, 107855550, 107962550,
	108069600, 108176700, 108283850, 108391050, 108498300, 108605600, 108712950, 108820350, 108927800, 109035300, 109142850, 109250450, 109358100, 109465800, 109573550, 109681350, 109789200, 109897100, 110005050,
	110113050, 110221100, 110329200, 110437350, 110545550, 110653800, 110762100, 110870450, 110978850, 111087300, 111195800, 111304350, 111412950, 111521600, 111630300, 111739050, 111847850, 111956700, 112065600,
	112174550, 112283550, 112392600, 112501700, 112610850, 112720050, 112829300, 112938600, 113047950, 113157350, 113266800, 113376300, 113485850, 113595450, 113705100, 113814800, 113924550, 114034350, 114144200,
	114254100, 114364050, 114474050, 114584100, 114694200, 114804350, 114914550, 115024800, 115135100, 115245450, 115355850, 115466300, 115576800, 115687350, 115797950, 115908600, 116019300, 116130050, 116240850,
	116351700, 116462600, 116573550, 116684550, 116795600, 116906700, 117017850, 117129050, 117240300, 117351600, 117462950, 117574350, 117685800, 117797300, 117908850, 118020450, 118132100, 118243800, 118355550,
	118467350, 118579200, 118691100, 118803050, 118915050, 119027100, 119139200, 119251350, 119363550, 119475800, 119588100, 119700450, 119812850, 119925300, 120037800, 120150350, 120262950, 120375600, 120488300,
	120601050, 120713850, 120826700, 120939600, 121052550, 121165550, 121278600, 121391700, 121504850, 121618050, 121731300, 121844600, 121957950, 122071350, 122184800, 122298300, 122411850, 122525450, 122639100,
	122752800, 122866550, 122980350, 123094200, 123208100, 123322050, 123436050, 123550100, 123664200, 123778350, 123892550, 124006800, 124121100, 124235450, 124349850, 124464300, 124578800, 124693350, 124807950,
	124922600, 125037300, 125152050, 125266850, 125381700, 125496600, 125611550, 125726550, 125841600, 125956700, 126071850, 126187050, 126302300, 126417600, 126532950, 126648350, 126763800, 126879300, 126994850,
	127110450, 127226100, 127341800, 127457550, 127573350, 127689200, 127805100, 127921050, 128037050, 128153100, 128269200, 128385350, 128501550, 128617800, 128734100, 128850450, 128966850, 129083300, 129199800,
	129316350, 129432950, 129549600, 129666300, 129783050, 129899850, 130016700, 130133600, 130250550, 130367550, 130484600, 130601700, 130718850, 130836050, 130953300, 131070600, 131187950, 131305350, 131422800,
	131540300, 131657850, 131775450, 131893100, 132010800, 132128550, 132246350, 132364200, 132482100, 132600050, 132718050, 132836100, 132954200, 133072350, 133190550, 133308800, 133427100, 133545450, 133663850,
	133782300, 133900800, 134019350, 134137950, 134256600, 134375300, 134494050, 134612850, 134731700, 134850600, 134969550, 135088550, 135207600, 135326700, 135445850, 135565050, 135684300, 135803600, 135922950,
	136042350, 136161800, 136281300, 136400850, 136520450, 136640100, 136759800, 136879550, 136999350, 137119200, 137239100, 137359050, 137479050, 137599100, 137719200, 137839350, 137959550, 138079800, 138200100,
	138320450, 138440850, 138561300, 138681800, 138802350, 138922950, 139043600, 139164300, 139285050, 139405850, 139526700, 139647600, 139768550, 139889550, 140010600, 140131700, 140252850, 140374050, 140495300,
	140616600, 140737950, 140859350, 140980800, 141102300, 141223850, 141345450, 141467100, 141588800, 141710550, 141832350, 141954200, 142076100, 142198050, 142320050, 142442100, 142564200, 142686350, 142808550,
	142930800, 143053100, 143175450, 143297850, 143420300, 143542800, 143665350, 143787950, 143910600, 144033300, 144156050, 144278850, 144401700, 144524600, 144647550, 144770550, 144893600, 145016700, 145139850,
	145263050, 145386300, 145509600, 145632950, 145756350, 145879800, 146003300, 146126850, 146250450, 146374100, 146497800, 146621550, 146745350, 146869200, 146993100, 147117050, 147241050, 147365100, 147489200,
	147613350, 147737550, 147861800, 147986100, 148110450, 148234850, 148359300, 148483800, 148608350, 148732950, 148857600, 148982300, 149107050, 149231850, 149356700, 149481600, 149606550, 149731550, 149856600,
	149981700, 150106850, 150232050, 150357300, 150482600, 150607950, 150733350, 150858800, 150984300, 151109850, 151235450, 151361100, 151486800, 151612550, 151738350, 151864200, 151990100, 152116050, 152242050,
	152368100, 152494200, 152620350, 152746550, 152872800, 152999100, 153125450, 153251850, 153378300, 153504800, 153631350, 153757950, 153884600, 154011300, 154138050, 154264850, 154391700, 154518600, 154645550,
	154772550, 154899600, 155026700, 155153850, 155281050, 155408300, 155535600, 155662950, 155790350, 155917800, 156045300, 156172850, 156300450, 156428100, 156555800, 156683550, 156811350, 156939200, 157067100,
	157195050, 157323050, 157451100, 157579200, 157707350, 157835550, 157963800, 158092100, 158220450, 158348850, 158477300, 158605800, 158734350, 158862950, 158991600, 159120300, 159249050, 159377850, 159506700,
	159635600, 159764550, 159893550, 160022600, 160151700, 160280850, 160410050, 160539300, 160668600, 160797950, 160927350, 161056800, 161186300, 161315850, 161445450, 161575100, 161704800, 161834550, 161964350,
	162094200, 162224100, 162354050, 162484050, 162614100, 162744200, 162874350, 163004550, 163134800, 163265100, 163395450, 163525850, 163656300, 163786800, 163917350, 164047950, 164178600, 164309300, 164440050,
	164570850, 164701700, 164832600, 164963550, 165094550, 165225600, 165356700, 165487850, 165619050, 165750300, 165881600, 166012950, 166144350, 166275800, 166407300, 166538850, 166670450, 166802100, 166933800,
	167065550, 167197350, 167329200, 167461100, 167593050, 167725050, 167857100, 167989200, 168121350, 168253550, 168385800, 168518100, 168650450, 168782850, 168915300, 169047800, 169180350, 169312950, 169445600,
	169578300, 169711050, 169843850, 169976700, 170109600, 170242550, 170375550, 170508600, 170641700, 170774850, 170908050, 171041300, 171174600, 171307950, 171441350, 171574800, 171708300, 171841850, 171975450,
	172109100, 172242800, 172376550, 172510350, 172644200, 172778100, 172912050, 173046050, 173180100, 173314200, 173448350, 173582550, 173716800, 173851100, 173985450, 174119850, 174254300, 174388800, 174523350,
	174657950, 174792600, 174927300, 175062050, 175196850, 175331700, 175466600, 175601550, 175736550, 175871600, 176006700, 176141850, 176277050, 176412300, 176547600, 176682950, 176818350, 176953800, 177089300,
	177224850, 177360450, 177496100, 177631800, 177767550, 177903350, 178039200, 178175100, 178311050, 178447050, 178583100, 178719200, 178855350, 178991550, 179127800, 179264100, 179400450, 179536850, 179673300,
	179809800, 179946350, 180082950, 180219600, 180356300, 180493050, 180629850, 180766700, 180903600, 181040550, 181177550, 181314600, 181451700, 181588850, 181726050, 181863300, 182000600, 182137950, 182275350,
	182412800, 182550300, 182687850, 182825450, 182963100, 183100800, 183238550, 183376350, 183514200, 183652100, 183790050, 183928050, 184066100, 184204200, 184342350, 184480550, 184618800, 184757100, 184895450,
	185033850, 185172300, 185310800, 185449350, 185587950, 185726600, 185865300, 186004050, 186142850, 186281700, 186420600, 186559550, 186698550, 186837600, 186976700, 187115850, 187255050, 187394300, 187533600,
	187672950, 187812350, 187951800, 188091300, 188230850, 188370450, 188510100, 188649800, 188789550, 188929350, 189069200, 189209100, 189349050, 189489050, 189629100, 189769200, 189909350, 190049550, 190189800,
	190330100, 190470450, 190610850, 190751300, 190891800, 191032350, 191172950, 191313600, 191454300, 191595050, 191735850, 191876700, 192017600, 192158550, 192299550, 192440600, 192581700, 192722850, 192864050,
	193005300, 193146600, 193287950, 193429350, 193570800, 193712300, 193853850, 193995450, 194137100, 194278800, 194420550, 194562350, 194704200, 194846100, 194988050, 195130050, 195272100, 195414200, 195556350,
	195698550, 195840800, 195983100, 196125450, 196267850, 196410300, 196552800, 196695350, 196837950, 196980600, 197123300, 197266050, 197408850, 197551700, 197694600, 197837550, 197980550, 198123600, 198266700,
	198409850, 198553050, 198696300, 198839600, 198982950, 199126350, 199269800, 199413300, 199556850, 199700450, 199844100, 199987800, 200131550, 200275350, 200419200, 200563100, 200707050, 200851050, 200995100,
	201139200, 201283350, 201427550, 201571800, 201716100, 201860450, 202004850, 202149300, 202293800, 202438350, 202582950, 202727600, 202872300, 203017050, 203161850, 203306700, 203451600, 203596550, 203741550,
	203886600, 204031700, 204176850, 204322050, 204467300, 204612600, 204757950, 204903350, 205048800, 205194300, 205339850, 205485450, 205631100, 205776800, 205922550, 206068350, 206214200, 206360100, 206506050,
	206652050, 206798100, 206944200, 207090350, 207236550, 207382800, 207529100, 207675450, 207821850, 207968300, 208114800, 208261350, 208407950, 208554600, 208701300, 208848050, 208994850, 209141700, 209288600,
	209435550, 209582550, 209729600, 209876700, 210023850, 210171050, 210318300, 210465600, 210612950, 210760350, 210907800, 211055300, 211202850, 211350450, 211498100, 211645800, 211793550, 211941350, 212089200,
	212237100, 212385050, 212533050, 212681100, 212829200, 212977350, 213125550, 213273800, 213422100, 213570450, 213718850, 213867300, 214015800, 214164350, 214312950, 214461600, 214610300, 214759050, 214907850,
	215056700, 215205600, 215354550, 215503550, 215652600, 215801700, 215950850, 216100050, 216249300, 216398600, 216547950, 216697350, 216846800, 216996300, 217145850, 217295450, 217445100, 217594800, 217744550,
	217894350, 218044200, 218194100, 218344050, 218494050, 218644100, 218794200, 218944350, 219094550, 219244800, 219395100, 219545450, 219695850, 219846300, 219996800, 220147350, 220297950, 220448600, 220599300,
	220750050, 220900850, 221051700, 221202600, 221353550, 221504550, 221655600, 221806700, 221957850, 222109050, 222260300, 222411600, 222562950, 222714350, 222865800, 223017300, 223168850, 223320450, 223472100,
	223623800, 223775550, 223927350, 224079200, 224231100, 224383050, 224535050, 224687100, 224839200, 224991350, 225143550, 225295800, 225448100, 225600450, 225752850, 225905300, 226057800, 226210350, 226362950,
	226515600, 226668300, 226821050, 226973850, 227126700, 227279600, 227432550, 227585550, 227738600, 227891700, 228044850, 228198050, 228351300, 228504600, 228657950, 228811350, 228964800, 229118300, 229271850,
	229425450, 229579100, 229732800, 229886550, 230040350, 230194200, 230348100, 230502050, 230656050, 230810100, 230964200, 231118350, 231272550, 231426800, 231581100, 231735450, 231889850, 232044300, 232198800,
	232353350, 232507950, 232662600, 232817300, 232972050, 233126850, 233281700, 233436600, 233591550, 233746550, 233901600, 234056700, 234211850, 234367050, 234522300, 234677600, 234832950, 234988350, 235143800,
	235299300, 235454850, 235610450, 235766100, 235921800, 236077550, 236233350, 236389200, 236545100, 236701050, 236857050, 237013100, 237169200, 237325350, 237481550, 237637800, 237794100, 237950450, 238106850,
	238263300, 238419800, 238576350, 238732950, 238889600, 239046300, 239203050, 239359850, 239516700, 239673600, 239830550, 239987550, 240144600, 240301700, 240458850, 240616050, 240773300, 240930600, 241087950,
	241245350, 241402800, 241560300, 241717850, 241875450, 242033100, 242190800, 242348550, 242506350, 242664200, 242822100, 242980050, 243138050, 243296100, 243454200, 243612350, 243770550, 243928800, 244087100,
	244245450, 244403850, 244562300, 244720800, 244879350, 245037950, 245196600, 245355300, 245514050, 245672850, 245831700, 245990600, 246149550, 246308550, 246467600, 246626700, 246785850, 246945050, 247104300,
	247263600, 247422950, 247582350, 247741800, 247901300, 248060850, 248220450, 248380100, 248539800, 248699550, 248859350, 249019200, 249179100, 249339050, 249499050, 249659100, 249819200, 249979350, 250139550,
	250299800, 250460100, 250620450, 250780850, 250941300, 251101800, 251262350, 251422950, 251583600, 251744300, 251905050, 252065850, 252226700, 252387600, 252548550, 252709550, 252870600, 253031700, 253192850,
	253354050, 253515300, 253676600, 253837950, 253999350, 254160800, 254322300, 254483850, 254645450, 254807100, 254968800, 255130550, 255292350, 255454200, 255616100, 255778050, 255940050, 256102100, 256264200,
	256426350, 256588550, 256750800, 256913100, 257075450, 257237850, 257400300, 257562800, 257725350, 257887950, 258050600, 258213300, 258376050, 258538850, 258701700, 258864600, 259027550, 259190550, 259353600,
	259516700, 259679850, 259843050, 260006300, 260169600, 260332950, 260496350, 260659800, 260823300, 260986850, 261150450, 261314100, 261477800, 261641550, 261805350, 261969200, 262133100, 262297050, 262461050,
	262625100, 262789200, 262953350, 263117550, 263281800, 263446100, 263610450, 263774850, 263939300, 264103800, 264268350, 264432950, 264597600, 264762300, 264927050, 265091850, 265256700, 265421600, 265586550,
	265751550, 265916600, 266081700, 266246850, 266412050, 266577300, 266742600, 266907950, 267073350, 267238800, 267404300, 267569850, 267735450, 267901100, 268066800, 268232550, 268398350, 268564200, 268730100,
	268896050, 269062050, 269228100, 269394200, 269560350, 269726550, 269892800, 270059100, 270225450, 270391850, 270558300, 270724800, 270891350, 271057950, 271224600, 271391300, 271558050, 271724850, 271891700,
	272058600, 272225550, 272392550, 272559600, 272726700, 272893850, 273061050, 273228300, 273395600, 273562950, 273730350, 273897800, 274065300, 274232850, 274400450, 274568100, 274735800, 274903550, 275071350,
	275239200, 275407100, 275575050, 275743050, 275911100, 276079200, 276247350, 276415550, 276583800, 276752100, 276920450, 277088850, 277257300, 277425800, 277594350, 277762950, 277931600, 278100300, 278269050,
	278437850, 278606700, 278775600, 278944550, 279113550, 279282600, 279451700, 279620850, 279790050, 279959300, 280128600, 280297950, 280467350, 280636800, 280806300, 280975850, 281145450, 281315100, 281484800,
	281654550, 281824350, 281994200, 282164100, 282334050, 282504050, 282674100, 282844200, 283014350, 283184550, 283354800, 283525100, 283695450, 283865850, 284036300, 284206800, 284377350, 284547950, 284718600,
	284889300, 285060050, 285230850, 285401700, 285572600, 285743550, 285914550, 286085600, 286256700, 286427850, 286599050, 286770300, 286941600, 287112950, 287284350, 287455800, 287627300, 287798850, 287970450,
	288142100, 288313800, 288485550, 288657350, 288829200, 289001100, 289173050, 289345050, 289517100, 289689200, 289861350, 290033550, 290205800, 290378100, 290550450, 290722850, 290895300, 291067800, 291240350,
	291412950, 291585600, 291758300, 291931050, 292103850, 292276700, 292449600, 292622550, 292795550, 292968600, 293141700, 293314850, 293488050, 293661300, 293834600, 294007950, 294181350, 294354800, 294528300,
	294701850, 294875450, 295049100, 295222800, 295396550, 295570350, 295744200, 295918100, 296092050, 296266050, 296440100, 296614200, 296788350, 296962550, 297136800, 297311100, 297485450, 297659850, 297834300,
	298008800, 298183350, 298357950, 298532600, 298707300, 298882050, 299056850, 299231700, 299406600, 299581550, 299756550, 299931600, 300106700, 300281850, 300457050, 300632300, 300807600, 300982950, 301158350,
	301333800, 301509300, 301684850, 301860450, 302036100, 302211800, 302387550, 302563350, 302739200, 302915100, 303091050, 303267050, 303443100, 303619200, 303795350, 303971550, 304147800, 304324100, 304500450,
	304676850, 304853300, 305029800, 305206350, 305382950, 305559600, 305736300, 305913050, 306089850, 306266700, 306443600, 306620550, 306797550, 306974600, 307151700, 307328850, 307506050, 307683300, 307860600,
	308037950, 308215350, 308392800, 308570300, 308747850, 308925450, 309103100, 309280800, 309458550, 309636350, 309814200, 309992100, 310170050, 310348050, 310526100, 310704200, 310882350, 311060550, 311238800,
	311417100, 311595450, 311773850, 311952300, 312130800, 312309350, 312487950, 312666600, 312845300, 313024050, 313202850, 313381700, 313560600, 313739550, 313918550, 314097600, 314276700, 314455850, 314635050,
	314814300, 314993600, 315172950, 315352350, 315531800, 315711300, 315890850, 316070450, 316250100, 316429800, 316609550, 316789350, 316969200, 317149100, 317329050, 317509050, 317689100, 317869200, 318049350,
	318229550, 318409800, 318590100, 318770450, 318950850, 319131300, 319311800, 319492350, 319672950, 319853600, 320034300, 320215050, 320395850, 320576700, 320757600, 320938550, 321119550, 321300600, 321481700,
	321662850, 321844050, 322025300, 322206600, 322387950, 322569350, 322750800, 322932300, 323113850, 323295450, 323477100, 323658800, 323840550, 324022350, 324204200, 324386100, 324568050, 324750050, 324932100,
	325114200, 325296350, 325478550, 325660800, 325843100, 326025450, 326207850, 326390300, 326572800, 326755350, 326937950, 327120600, 327303300, 327486050, 327668850, 327851700, 328034600, 328217550, 328400550,
	328583600, 328766700, 328949850, 329133050, 329316300, 329499600, 329682950, 329866350, 330049800, 330233300, 330416850, 330600450, 330784100, 330967800, 331151550, 331335350, 331519200, 331703100, 331887050,
	332071050, 332255100, 332439200, 332623350, 332807550, 332991800, 333176100, 333360450, 333544850, 333729300, 333913800, 334098350, 334282950, 334467600, 334652300, 334837050, 335021850, 335206700, 335391600,
	335576550, 335761550, 335946600, 336131700, 336316850, 336502050, 336687300, 336872600, 337057950, 337243350, 337428800, 337614300, 337799850, 337985450, 338171100, 338356800, 338542550, 338728350, 338914200,
	339100100, 339286050, 339472050, 339658100, 339844200, 340030350, 340216550, 340402800, 340589100, 340775450, 340961850, 341148300, 341334800, 341521350, 341707950, 341894600, 342081300, 342268050, 342454850,
	342641700, 342828600, 343015550, 343202550, 343389600, 343576700, 343763850, 343951050, 344138300, 344325600, 344512950, 344700350, 344887800, 345075300, 345262850, 345450450, 345638100, 345825800, 346013550,
	346201350, 346389200, 346577100, 346765050, 346953050, 347141100, 347329200, 347517350, 347705550, 347893800, 348082100, 348270450, 348458850, 348647300, 348835800, 349024350, 349212950, 349401600, 349590300,
	349779050, 349967850, 350156700, 350345600, 350534550, 350723550, 350912600, 351101700, 351290850, 351480050, 351669300, 351858600, 352047950, 352237350, 352426800, 352616300, 352805850, 352995450, 353185100,
	353374800, 353564550, 353754350, 353944200, 354134100, 354324050, 354514050, 354704100, 354894200, 355084350, 355274550, 355464800, 355655100, 355845450, 356035850, 356226300, 356416800, 356607350, 356797950,
	356988600, 357179300, 357370050, 357560850, 357751700, 357942600, 358133550, 358324550, 358515600, 358706700, 358897850, 359089050, 359280300, 359471600, 359662950, 359854350, 360045800, 360237300, 360428850,
	360620450, 360812100, 361003800, 361195550, 361387350, 361579200, 361771100, 361963050, 362155050, 362347100, 362539200, 362731350, 362923550, 363115800, 363308100, 363500450, 363692850, 363885300, 364077800,
	364270350, 364462950, 364655600, 364848300, 365041050, 365233850, 365426700, 365619600, 365812550, 366005550, 366198600, 366391700, 366584850, 366778050, 366971300, 367164600, 367357950, 367551350, 367744800,
	367938300, 368131850, 368325450, 368519100, 368712800, 368906550, 369100350, 369294200, 369488100, 369682050, 369876050, 370070100, 370264200, 370458350, 370652550, 370846800, 371041100, 371235450, 371429850,
	371624300, 371818800, 372013350, 372207950, 372402600, 372597300, 372792050, 372986850, 373181700, 373376600, 373571550, 373766550, 373961600, 374156700, 374351850, 374547050, 374742300, 374937600, 375132950,
	375328350, 375523800, 375719300, 375914850, 376110450, 376306100, 376501800, 376697550, 376893350, 377089200, 377285100, 377481050, 377677050, 377873100, 378069200, 378265350, 378461550, 378657800, 378854100,
	379050450, 379246850, 379443300, 379639800, 379836350, 380032950, 380229600, 380426300, 380623050, 380819850, 381016700, 381213600, 381410550, 381607550, 381804600, 382001700, 382198850, 382396050, 382593300,
	382790600, 382987950, 383185350, 383382800, 383580300, 383777850, 383975450, 384173100, 384370800, 384568550, 384766350, 384964200, 385162100, 385360050, 385558050, 385756100, 385954200, 386152350, 386350550,
	386548800, 386747100, 386945450, 387143850, 387342300, 387540800, 387739350, 387937950, 388136600, 388335300, 388534050, 388732850, 388931700, 389130600, 389329550, 389528550, 389727600, 389926700, 390125850,
	390325050, 390524300, 390723600, 390922950, 391122350, 391321800, 391521300, 391720850, 391920450, 392120100, 392319800, 392519550, 392719350, 392919200, 393119100, 393319050, 393519050, 393719100, 393919200,
	394119350, 394319550, 394519800, 394720100, 394920450, 395120850, 395321300, 395521800, 395722350, 395922950, 396123600, 396324300, 396525050, 396725850, 396926700, 397127600, 397328550, 397529550, 397730600,
	397931700, 398132850, 398334050, 398535300, 398736600, 398937950, 399139350, 399340800, 399542300, 399743850, 399945450, 400147100, 400348800, 400550550, 400752350, 400954200, 401156100, 401358050, 401560050,
	401762100, 401964200, 402166350, 402368550, 402570800, 402773100, 402975450, 403177850, 403380300, 403582800, 403785350, 403987950, 404190600, 404393300, 404596050, 404798850, 405001700, 405204600, 405407550,
	405610550, 405813600, 406016700, 406219850, 406423050, 406626300, 406829600, 407032950, 407236350, 407439800, 407643300, 407846850, 408050450, 408254100, 408457800, 408661550, 408865350, 409069200, 409273100,
	409477050, 409681050, 409885100, 410089200, 410293350, 410497550, 410701800, 410906100, 411110450, 411314850, 411519300, 411723800, 411928350, 412132950, 412337600, 412542300, 412747050, 412951850, 413156700,
	413361600, 413566550, 413771550, 413976600, 414181700, 414386850, 414592050, 414797300, 415002600, 415207950, 415413350, 415618800, 415824300, 416029850, 416235450, 416441100, 416646800, 416852550, 417058350,
	417264200, 417470100, 417676050, 417882050, 418088100, 418294200, 418500350, 418706550, 418912800, 419119100, 419325450, 419531850, 419738300, 419944800, 420151350, 420357950, 420564600, 420771300, 420978050,
	421184850, 421391700, 421598600, 421805550, 422012550, 422219600, 422426700, 422633850, 422841050, 423048300, 423255600, 423462950, 423670350, 423877800, 424085300, 424292850, 424500450, 424708100, 424915800,
	425123550, 425331350, 425539200, 425747100, 425955050, 426163050, 426371100, 426579200, 426787350, 426995550, 427203800, 427412100, 427620450, 427828850, 428037300, 428245800, 428454350, 428662950, 428871600,
	429080300, 429289050, 429497850, 429706700, 429915600, 430124550, 430333550, 430542600, 430751700, 430960850, 431170050, 431379300, 431588600, 431797950, 432007350, 432216800, 432426300, 432635850, 432845450,
	433055100, 433264800, 433474550, 433684350, 433894200, 434104100, 434314050, 434524050, 434734100, 434944200, 435154350, 435364550, 435574800, 435785100, 435995450, 436205850, 436416300, 436626800, 436837350,
	437047950, 437258600, 437469300, 437680050, 437890850, 438101700, 438312600, 438523550, 438734550, 438945600, 439156700, 439367850, 439579050, 439790300, 440001600, 440212950, 440424350, 440635800, 440847300,
	441058850, 441270450, 441482100, 441693800, 441905550, 442117350, 442329200, 442541100, 442753050, 442965050, 443177100, 443389200, 443601350, 443813550, 444025800, 444238100, 444450450, 444662850, 444875300,
	445087800, 445300350, 445512950, 445725600, 445938300, 446151050, 446363850, 446576700, 446789600, 447002550, 447215550, 447428600, 447641700, 447854850, 448068050, 448281300, 448494600, 448707950, 448921350,
	449134800, 449348300, 449561850, 449775450, 449989100, 450202800, 450416550, 450630350, 450844200, 451058100, 451272050, 451486050, 451700100, 451914200, 452128350, 452342550, 452556800, 452771100, 452985450,
	453199850, 453414300, 453628800, 453843350, 454057950, 454272600, 454487300, 454702050, 454916850, 455131700, 455346600, 455561550, 455776550, 455991600, 456206700, 456421850, 456637050, 456852300, 457067600,
	457282950, 457498350, 457713800, 457929300, 458144850, 458360450, 458576100, 458791800, 459007550, 459223350, 459439200, 459655100, 459871050, 460087050, 460303100, 460519200, 460735350, 460951550, 461167800,
	461384100, 461600450, 461816850, 462033300, 462249800, 462466350, 462682950, 462899600, 463116300, 463333050, 463549850, 463766700, 463983600, 464200550, 464417550, 464634600, 464851700, 465068850, 465286050,
	465503300, 465720600, 465937950, 466155350, 466372800, 466590300, 466807850, 467025450, 467243100, 467460800, 467678550, 467896350, 468114200, 468332100, 468550050, 468768050, 468986100, 469204200, 469422350,
	469640550, 469858800, 470077100, 470295450, 470513850, 470732300, 470950800, 471169350, 471387950, 471606600, 471825300, 472044050, 472262850, 472481700, 472700600, 472919550, 473138550, 473357600, 473576700,
	473795850, 474015050, 474234300, 474453600, 474672950, 474892350, 475111800, 475331300, 475550850, 475770450, 475990100, 476209800, 476429550, 476649350, 476869200, 477089100, 477309050, 477529050, 477749100,
	477969200, 478189350, 478409550, 478629800, 478850100, 479070450, 479290850, 479511300, 479731800, 479952350, 480172950, 480393600, 480614300, 480835050, 481055850, 481276700, 481497600, 481718550, 481939550, 482160600, 482381700, 482602850, 482824050, 483045300, 483266600, 483487950, 483709350, 483930800, 484152300, 484373850, 484595450, 484817100, 485038800, 485260550, 485482350, 485704200, 485926100, 486148050, 486370050, 486592100, 486814200, 487036350, 487258550, 487480800, 487703100, 487925450, 488147850, 488370300, 488592800, 488815350, 489037950, 489260600, 489483300, 489706050, 489928850, 490151700, 490374600, 490597550, 490820550, 491043600, 491266700, 491489850, 491713050, 491936300, 492159600, 492382950, 492606350, 492829800, 493053300, 493276850, 493500450, 493724100, 493947800, 494171550, 494395350, 494619200, 494843100, 495067050, 495291050, 495515100, 495739200, 495963350, 496187550, 496411800, 496636100, 496860450, 497084850, 497309300, 497533800, 497758350, 497982950, 498207600, 498432300, 498657050, 498881850, 499106700, 499331600, 499556550, 499781550, 500006600, 500231700, 500456850, 500682050, 500907300, 501132600, 501357950, 501583350, 501808800, 502034300, 502259850, 502485450, 502711100, 502936800, 503162550, 503388350, 503614200, 503840100, 504066050, 504292050, 504518100, 504744200, 504970350, 505196550, 505422800, 505649100, 505875450, 506101850, 506328300, 506554800, 506781350, 507007950, 507234600, 507461300, 507688050, 507914850, 508141700, 508368600, 508595550, 508822550, 509049600, 509276700, 509503850, 509731050, 509958300, 510185600, 510412950, 510640350, 510867800, 511095300, 511322850, 511550450, 511778100, 512005800, 512233550, 512461350, 512689200, 512917100, 513145050, 513373050, 513601100, 513829200, 514057350, 514285550, 514513800, 514742100, 514970450, 515198850, 515427300, 515655800, 515884350, 516112950, 516341600, 516570300, 516799050, 517027850, 517256700, 517485600, 517714550, 517943550, 518172600, 518401700, 518630850, 518860050, 519089300, 519318600, 519547950, 519777350, 520006800, 520236300, 520465850, 520695450, 520925100, 521154800, 521384550, 521614350, 521844200, 522074100, 522304050, 522534050, 522764100, 522994200, 523224350, 523454550, 523684800, 523915100, 524145450, 524375850, 524606300, 524836800, 525067350, 525297950, 525528600, 525759300, 525990050, 526220850, 526451700, 526682600, 526913550, 527144550, 527375600, 527606700, 527837850, 528069050, 528300300, 528531600, 528762950, 528994350, 529225800, 529457300, 529688850, 529920450, 530152100, 530383800, 530615550, 530847350, 531079200, 531311100, 531543050, 531775050, 532007100, 532239200, 532471350, 532703550, 532935800, 533168100, 533400450, 533632850, 533865300, 534097800, 534330350, 534562950, 534795600, 535028300, 535261050, 535493850, 535726700, 535959600, 536192550, 536425550, 536658600, 536891700, 537124850, 537358050, 537591300, 537824600, 538057950, 538291350, 538524800, 538758300, 538991850, 539225450, 539459100, 539692800, 539926550, 540160350, 540394200, 540628100, 540862050, 541096050, 541330100, 541564200, 541798350, 542032550, 542266800, 542501100, 542735450, 542969850, 543204300, 543438800, 543673350, 543907950, 544142600, 544377300, 544612050, 544846850, 545081700, 545316600, 545551550, 545786550, 546021600, 546256700, 546491850, 546727050, 546962300, 547197600, 547432950, 547668350, 547903800, 548139300, 548374850, 548610450, 548846100, 549081800, 549317550, 549553350, 549789200, 550025100, 550261050, 550497050, 550733100, 550969200, 551205350, 551441550, 551677800, 551914100, 552150450, 552386850, 552623300, 552859800, 553096350, 553332950, 553569600, 553806300, 554043050, 554279850, 554516700, 554753600, 554990550, 555227550, 555464600, 555701700, 555938850, 556176050, 556413300, 556650600, 556887950, 557125350, 557362800, 557600300, 557837850, 558075450, 558313100, 558550800, 558788550, 559026350, 559264200, 559502100, 559740050, 559978050, 560216100, 560454200, 560692350, 560930550, 561168800, 561407100, 561645450, 561883850, 562122300, 562360800, 562599350, 562837950, 563076600, 563315300, 563554050, 563792850, 564031700, 564270600, 564509550, 564748550, 564987600, 565226700, 565465850, 565705050, 565944300, 566183600, 566422950, 566662350, 566901800, 567141300, 567380850, 567620450, 567860100, 568099800, 568339550, 568579350, 568819200, 569059100, 569299050, 569539050, 569779100, 570019200, 570259350, 570499550, 570739800, 570980100, 571220450, 571460850, 571701300, 571941800, 572182350, 572422950, 572663600, 572904300, 573145050, 573385850, 573626700, 573867600, 574108550, 574349550, 574590600, 574831700, 575072850, 575314050, 575555300, 575796600, 576037950, 576279350, 576520800, 576762300, 577003850, 577245450, 577487100, 577728800, 577970550, 578212350, 578454200, 578696100, 578938050, 579180050, 579422100, 579664200, 579906350, 580148550, 580390800, 580633100, 580875450, 581117850, 581360300, 581602800, 581845350, 582087950, 582330600, 582573300, 582816050, 583058850, 583301700, 583544600, 583787550, 584030550, 584273600, 584516700, 584759850, 585003050, 585246300, 585489600, 585732950, 585976350, 586219800, 586463300, 586706850, 586950450, 587194100, 587437800, 587681550, 587925350, 588169200, 588413100, 588657050, 588901050, 589145100, 589389200, 589633350, 589877550, 590121800, 590366100, 590610450, 590854850, 591099300, 591343800, 591588350, 591832950, 592077600, 592322300, 592567050, 592811850, 593056700, 593301600, 593546550, 593791550, 594036600, 594281700, 594526850, 594772050, 595017300, 595262600, 595507950, 595753350, 595998800, 596244300, 596489850, 596735450, 596981100, 597226800, 597472550, 597718350, 597964200, 598210100, 598456050, 598702050, 598948100, 599194200, 599440350, 599686550, 599932800, 600179100, 600425450, 600671850, 600918300, 601164800, 601411350, 601657950, 601904600, 602151300, 602398050, 602644850, 602891700, 603138600, 603385550, 603632550, 603879600, 604126700, 604373850, 604621050, 604868300, 605115600, 605362950, 605610350, 605857800, 606105300, 606352850, 606600450, 606848100, 607095800, 607343550, 607591350, 607839200, 608087100, 608335050, 608583050, 608831100, 609079200, 609327350, 609575550, 609823800, 610072100, 610320450, 610568850, 610817300, 611065800, 611314350, 611562950, 611811600, 612060300, 612309050, 612557850, 612806700, 613055600, 613304550, 613553550, 613802600, 614051700, 614300850, 614550050, 614799300, 615048600, 615297950, 615547350, 615796800, 616046300, 616295850, 616545450, 616795100, 617044800, 617294550, 617544350, 617794200, 618044100, 618294050, 618544050, 618794100, 619044200, 619294350, 619544550, 619794800, 620045100, 620295450, 620545850, 620796300, 621046800, 621297350, 621547950, 621798600, 622049300, 622300050, 622550850, 622801700, 623052600, 623303550, 623554550, 623805600, 624056700, 624307850, 624559050, 624810300, 625061600, 625312950, 625564350, 625815800, 626067300, 626318850, 626570450, 626822100, 627073800, 627325550, 627577350, 627829200, 628081100, 628333050, 628585050, 628837100, 629089200, 629341350, 629593550, 629845800, 630098100, 630350450, 630602850, 630855300, 631107800, 631360350, 631612950, 631865600, 632118300, 632371050, 632623850, 632876700, 633129600, 633382550, 633635550, 633888600, 634141700, 634394850, 634648050, 634901300, 635154600, 635407950, 635661350, 635914800, 636168300, 636421850, 636675450, 636929100, 637182800, 637436550, 637690350, 637944200, 638198100, 638452050, 638706050, 638960100, 639214200, 639468350, 639722550, 639976800, 640231100, 640485450, 640739850, 640994300, 641248800, 641503350, 641757950, 642012600, 642267300, 642522050, 642776850, 643031700, 643286600, 643541550, 643796550, 644051600, 644306700, 644561850, 644817050, 645072300, 645327600, 645582950, 645838350, 646093800, 646349300, 646604850, 646860450, 647116100, 647371800, 647627550, 647883350, 648139200, 648395100, 648651050, 648907050, 649163100, 649419200, 649675350, 649931550, 650187800, 650444100, 650700450, 650956850, 651213300, 651469800, 651726350, 651982950, 652239600, 652496300, 652753050, 653009850, 653266700, 653523600, 653780550, 654037550, 654294600, 654551700, 654808850, 655066050, 655323300, 655580600, 655837950, 656095350, 656352800, 656610300, 656867850, 657125450, 657383100, 657640800, 657898550, 658156350, 658414200, 658672100, 658930050, 659188050, 659446100, 659704200, 659962350, 660220550, 660478800, 660737100, 660995450, 661253850, 661512300, 661770800, 662029350, 662287950, 662546600, 662805300, 663064050, 663322850, 663581700, 663840600, 664099550, 664358550, 664617600, 664876700, 665135850, 665395050, 665654300, 665913600, 666172950, 666432350, 666691800, 666951300, 667210850, 667470450, 667730100, 667989800, 668249550, 668509350, 668769200, 669029100, 669289050, 669549050, 669809100, 670069200, 670329350, 670589550, 670849800, 671110100, 671370450, 671630850, 671891300, 672151800, 672412350, 672672950, 672933600, 673194300, 673455050, 673715850, 673976700, 674237600, 674498550, 674759550, 675020600, 675281700, 675542850, 675804050, 676065300, 676326600, 676587950, 676849350, 677110800, 677372300, 677633850, 677895450, 678157100, 678418800, 678680550, 678942350, 679204200, 679466100, 679728050, 679990050, 680252100, 680514200, 680776350, 681038550, 681300800, 681563100, 681825450, 682087850, 682350300, 682612800, 682875350, 683137950, 683400600, 683663300, 683926050, 684188850, 684451700, 684714600, 684977550, 685240550, 685503600, 685766700, 686029850, 686293050, 686556300, 686819600, 687082950, 687346350, 687609800, 687873300, 688136850, 688400450, 688664100, 688927800, 689191550, 689455350, 689719200, 689983100, 690247050, 690511050, 690775100, 691039200, 691303350, 691567550, 691831800, 692096100, 692360450, 692624850, 692889300, 693153800, 693418350, 693682950, 693947600, 694212300, 694477050, 694741850, 695006700, 695271600, 695536550, 695801550, 696066600, 696331700, 696596850, 696862050, 697127300, 697392600, 697657950, 697923350, 698188800, 698454300, 698719850, 698985450, 699251100, 699516800, 699782550, 700048350, 700314200, 700580100, 700846050, 701112050, 701378100, 701644200, 701910350, 702176550, 702442800, 702709100, 702975450, 703241850, 703508300, 703774800, 704041350, 704307950, 704574600, 704841300, 705108050, 705374850, 705641700, 705908600, 706175550, 706442550, 706709600, 706976700, 707243850, 707511050, 707778300, 708045600, 708312950, 708580350, 708847800, 709115300, 709382850, 709650450, 709918100, 710185800, 710453550, 710721350, 710989200, 711257100, 711525050, 711793050, 712061100, 712329200, 712597350, 712865550, 713133800, 713402100, 713670450, 713938850, 714207300, 714475800, 714744350, 715012950, 715281600, 715550300, 715819050, 716087850, 716356700, 716625600, 716894550, 717163550, 717432600, 717701700, 717970850, 718240050, 718509300, 718778600, 719047950, 719317350, 719586800, 719856300, 720125850, 720395450, 720665100, 720934800, 721204550, 721474350, 721744200, 722014100, 722284050, 722554050, 722824100, 723094200, 723364350, 723634550, 723904800, 724175100, 724445450, 724715850, 724986300, 725256800, 725527350, 725797950, 726068600, 726339300, 726610050, 726880850, 727151700, 727422600, 727693550, 727964550, 728235600, 728506700, 728777850, 729049050, 729320300, 729591600, 729862950, 730134350, 730405800, 730677300, 730948850, 731220450, 731492100, 731763800, 732035550, 732307350, 732579200, 732851100, 733123050, 733395050, 733667100, 733939200, 734211350, 734483550, 734755800, 735028100, 735300450, 735572850, 735845300, 736117800, 736390350, 736662950, 736935600, 737208300, 737481050, 737753850, 738026700, 738299600, 738572550, 738845550, 739118600, 739391700, 739664850, 739938050, 740211300, 740484600, 740757950, 741031350, 741304800, 741578300, 741851850, 742125450, 742399100, 742672800, 742946550, 743220350, 743494200, 743768100, 744042050, 744316050, 744590100, 744864200, 745138350, 745412550, 745686800, 745961100, 746235450, 746509850, 746784300, 747058800, 747333350, 747607950, 747882600, 748157300, 748432050, 748706850, 748981700, 749256600, 749531550, 749806550, 750081600, 750356700, 750631850, 750907050, 751182300, 751457600, 751732950, 752008350, 752283800, 752559300, 752834850, 753110450, 753386100, 753661800, 753937550, 754213350, 754489200, 754765100, 755041050, 755317050, 755593100, 755869200, 756145350, 756421550, 756697800, 756974100, 757250450, 757526850, 757803300, 758079800, 758356350, 758632950, 758909600, 759186300, 759463050, 759739850, 760016700, 760293600, 760570550, 760847550, 761124600, 761401700, 761678850, 761956050, 762233300, 762510600, 762787950, 763065350, 763342800, 763620300, 763897850, 764175450, 764453100, 764730800, 765008550, 765286350, 765564200, 765842100, 766120050, 766398050, 766676100, 766954200, 767232350, 767510550, 767788800, 768067100, 768345450, 768623850, 768902300, 769180800, 769459350, 769737950, 770016600, 770295300, 770574050, 770852850, 771131700, 771410600, 771689550, 771968550, 772247600, 772526700, 772805850, 773085050, 773364300, 773643600, 773922950, 774202350, 774481800, 774761300, 775040850, 775320450, 775600100, 775879800, 776159550, 776439350, 776719200, 776999100, 777279050, 777559050, 777839100, 778119200, 778399350, 778679550, 778959800, 779240100, 779520450, 779800850, 780081300, 780361800, 780642350, 780922950, 781203600, 781484300, 781765050, 782045850, 782326700, 782607600, 782888550, 783169550, 783450600, 783731700, 784012850, 784294050, 784575300, 784856600, 785137950, 785419350, 785700800, 785982300, 786263850, 786545450, 786827100, 787108800, 787390550, 787672350, 787954200, 788236100, 788518050, 788800050, 789082100, 789364200, 789646350, 789928550, 790210800, 790493100, 790775450, 791057850, 791340300, 791622800, 791905350, 792187950, 792470600, 792753300, 793036050, 793318850, 793601700, 793884600, 794167550, 794450550, 794733600, 795016700, 795299850, 795583050, 795866300, 796149600, 796432950, 796716350, 796999800, 797283300, 797566850, 797850450, 798134100, 798417800, 798701550, 798985350, 799269200, 799553100, 799837050, 800121050, 800405100, 800689200, 800973350, 801257550, 801541800, 801826100, 802110450, 802394850, 802679300, 802963800, 803248350, 803532950, 803817600, 804102300, 804387050, 804671850, 804956700, 805241600, 805526550, 805811550, 806096600, 806381700, 806666850, 806952050, 807237300, 807522600, 807807950, 808093350, 808378800, 808664300, 808949850, 809235450, 809521100, 809806800, 810092550, 810378350, 810664200, 810950100, 811236050, 811522050, 811808100, 812094200, 812380350, 812666550, 812952800, 813239100, 813525450, 813811850, 814098300, 814384800, 814671350, 814957950, 815244600, 815531300, 815818050, 816104850, 816391700, 816678600, 816965550, 817252550, 817539600, 817826700, 818113850, 818401050, 818688300, 818975600, 819262950, 819550350, 819837800, 820125300, 820412850, 820700450, 820988100, 821275800, 821563550, 821851350, 822139200, 822427100, 822715050, 823003050, 823291100, 823579200, 823867350, 824155550, 824443800, 824732100, 825020450, 825308850, 825597300, 825885800, 826174350, 826462950, 826751600, 827040300, 827329050, 827617850, 827906700, 828195600, 828484550, 828773550, 829062600, 829351700, 829640850, 829930050, 830219300, 830508600, 830797950, 831087350, 831376800, 831666300, 831955850, 832245450, 832535100, 832824800, 833114550, 833404350, 833694200, 833984100, 834274050, 834564050, 834854100, 835144200, 835434350, 835724550, 836014800, 836305100, 836595450, 836885850, 837176300, 837466800, 837757350, 838047950, 838338600, 838629300, 838920050, 839210850, 839501700, 839792600, 840083550, 840374550, 840665600, 840956700, 841247850, 841539050, 841830300, 842121600, 842412950, 842704350, 842995800, 843287300, 843578850, 843870450, 844162100, 844453800, 844745550, 845037350, 845329200, 845621100, 845913050, 846205050, 846497100, 846789200, 847081350, 847373550, 847665800, 847958100, 848250450, 848542850, 848835300, 849127800, 849420350, 849712950, 850005600, 850298300, 850591050, 850883850, 851176700, 851469600, 851762550, 852055550, 852348600, 852641700, 852934850, 853228050, 853521300, 853814600, 854107950, 854401350, 854694800, 854988300, 855281850, 855575450, 855869100, 856162800, 856456550, 856750350, 857044200, 857338100, 857632050, 857926050, 858220100, 858514200, 858808350, 859102550, 859396800, 859691100, 859985450, 860279850, 860574300, 860868800, 861163350, 861457950, 861752600, 862047300, 862342050, 862636850, 862931700, 863226600, 863521550, 863816550, 864111600, 864406700, 864701850, 864997050, 865292300, 865587600, 865882950, 866178350, 866473800, 866769300, 867064850, 867360450, 867656100, 867951800, 868247550, 868543350, 868839200, 869135100, 869431050, 869727050, 870023100, 870319200, 870615350, 870911550, 871207800, 871504100, 871800450, 872096850, 872393300, 872689800, 872986350, 873282950, 873579600, 873876300, 874173050, 874469850, 874766700, 875063600, 875360550, 875657550, 875954600, 876251700, 876548850, 876846050, 877143300, 877440600, 877737950, 878035350, 878332800, 878630300, 878927850, 879225450, 879523100, 879820800, 880118550, 880416350, 880714200, 881012100, 881310050, 881608050, 881906100, 882204200, 882502350, 882800550, 883098800, 883397100, 883695450, 883993850, 884292300, 884590800, 884889350, 885187950, 885486600, 885785300, 886084050, 886382850, 886681700, 886980600, 887279550, 887578550, 887877600, 888176700, 888475850, 888775050, 889074300, 889373600, 889672950, 889972350, 890271800, 890571300, 890870850, 891170450, 891470100, 891769800, 892069550, 892369350, 892669200, 892969100, 893269050, 893569050, 893869100, 894169200, 894469350, 894769550, 895069800, 895370100, 895670450, 895970850, 896271300, 896571800, 896872350, 897172950, 897473600, 897774300, 898075050, 898375850, 898676700, 898977600, 899278550, 899579550, 899880600, 900181700, 900482850, 900784050, 901085300, 901386600, 901687950, 901989350, 902290800, 902592300, 902893850, 903195450, 903497100, 903798800, 904100550, 904402350, 904704200, 905006100, 905308050, 905610050, 905912100, 906214200, 906516350, 906818550, 907120800, 907423100, 907725450, 908027850, 908330300, 908632800, 908935350, 909237950, 909540600, 909843300, 910146050, 910448850, 910751700, 911054600, 911357550, 911660550, 911963600, 912266700, 912569850, 912873050, 913176300, 913479600, 913782950, 914086350, 914389800, 914693300, 914996850, 915300450, 915604100, 915907800, 916211550, 916515350, 916819200, 917123100, 917427050, 917731050, 918035100, 918339200, 918643350, 918947550, 919251800, 919556100, 919860450, 920164850, 920469300, 920773800, 921078350, 921382950, 921687600, 921992300, 922297050, 922601850, 922906700, 923211600, 923516550, 923821550, 924126600, 924431700, 924736850, 925042050, 925347300, 925652600, 925957950, 926263350, 926568800, 926874300, 927179850, 927485450, 927791100, 928096800, 928402550, 928708350, 929014200, 929320100, 929626050, 929932050, 930238100, 930544200, 930850350, 931156550, 931462800, 931769100, 932075450, 932381850, 932688300, 932994800, 933301350, 933607950, 933914600, 934221300, 934528050, 934834850, 935141700, 935448600, 935755550, 936062550, 936369600, 936676700, 936983850, 937291050, 937598300, 937905600, 938212950, 938520350, 938827800, 939135300, 939442850, 939750450, 940058100, 940365800, 940673550, 940981350, 941289200, 941597100, 941905050, 942213050, 942521100, 942829200, 943137350, 943445550, 943753800, 944062100, 944370450, 944678850, 944987300, 945295800, 945604350, 945912950, 946221600, 946530300, 946839050, 947147850, 947456700, 947765600, 948074550, 948383550, 948692600, 949001700, 949310850, 949620050, 949929300, 950238600, 950547950, 950857350, 951166800, 951476300, 951785850, 952095450, 952405100, 952714800, 953024550, 953334350, 953644200, 953954100, 954264050, 954574050, 954884100, 955194200, 955504350, 955814550, 956124800, 956435100, 956745450, 957055850, 957366300, 957676800, 957987350, 958297950, 958608600, 958919300, 959230050, 959540850, 959851700, 960162600, 960473550, 960784550, 961095600, 961406700, 961717850, 962029050, 962340300, 962651600, 962962950, 963274350, 963585800, 963897300, 964208850, 964520450, 964832100, 965143800, 965455550, 965767350, 966079200, 966391100, 966703050, 967015050, 967327100, 967639200, 967951350, 968263550, 968575800, 968888100, 969200450, 969512850, 969825300, 970137800, 970450350, 970762950, 971075600, 971388300, 971701050, 972013850, 972326700, 972639600, 972952550, 973265550, 973578600, 973891700, 974204850, 974518050, 974831300, 975144600, 975457950, 975771350, 976084800, 976398300, 976711850, 977025450, 977339100, 977652800, 977966550, 978280350, 978594200, 978908100, 979222050, 979536050, 979850100, 980164200, 980478350, 980792550, 981106800, 981421100, 981735450, 982049850, 982364300, 982678800, 982993350, 983307950, 983622600, 983937300, 984252050, 984566850, 984881700, 985196600, 985511550, 985826550, 986141600, 986456700, 986771850, 987087050, 987402300, 987717600, 988032950, 988348350, 988663800, 988979300, 989294850, 989610450, 989926100, 990241800, 990557550, 990873350, 991189200, 991505100, 991821050, 992137050, 992453100, 992769200, 993085350, 993401550, 993717800, 994034100, 994350450, 994666850, 994983300, 995299800, 995616350, 995932950, 996249600, 996566300, 996883050, 997199850, 997516700, 997833600, 998150550, 998467550, 998784600, 999101700, 999418850, 999736050, 1000053300, 1000370600, 1000687950, 1001005350, 1001322800, 1001640300, 1001957850, 1002275450, 1002593100, 1002910800, 1003228550, 1003546350, 1003864200, 1004182100, 1004500050, 1004818050, 1005136100, 1005454200, 1005772350, 1006090550, 1006408800, 1006727100, 1007045450, 1007363850, 1007682300, 1008000800, 1008319350, 1008637950, 1008956600, 1009275300, 1009594050, 1009912850, 1010231700, 1010550600, 1010869550, 1011188550, 1011507600, 1011826700, 1012145850, 1012465050, 1012784300, 1013103600, 1013422950, 1013742350, 1014061800, 1014381300, 1014700850, 1015020450, 1015340100, 1015659800, 1015979550, 1016299350, 1016619200, 1016939100, 1017259050, 1017579050, 1017899100, 1018219200, 1018539350, 1018859550, 1019179800, 1019500100, 1019820450, 1020140850, 1020461300, 1020781800, 1021102350, 1021422950, 1021743600, 1022064300, 1022385050, 1022705850, 1023026700, 1023347600, 1023668550, 1023989550, 1024310600, 1024631700, 1024952850, 1025274050, 1025595300, 1025916600, 1026237950, 1026559350, 1026880800, 1027202300, 1027523850, 1027845450, 1028167100, 1028488800, 1028810550, 1029132350, 1029454200, 1029776100, 1030098050, 1030420050, 1030742100, 1031064200, 1031386350, 1031708550, 1032030800, 1032353100, 1032675450, 1032997850, 1033320300, 1033642800, 1033965350, 1034287950, 1034610600, 1034933300, 1035256050, 1035578850, 1035901700, 1036224600, 1036547550, 1036870550, 1037193600, 1037516700, 1037839850, 1038163050, 1038486300, 1038809600, 1039132950, 1039456350, 1039779800, 1040103300, 1040426850, 1040750450, 1041074100, 1041397800, 1041721550, 1042045350, 1042369200, 1042693100, 1043017050, 1043341050, 1043665100, 1043989200, 1044313350, 1044637550, 1044961800, 1045286100, 1045610450, 1045934850, 1046259300, 1046583800, 1046908350, 1047232950, 1047557600, 1047882300, 1048207050, 1048531850, 1048856700, 1049181600, 1049506550, 1049831550, 1050156600, 1050481700, 1050806850, 1051132050, 1051457300, 1051782600, 1052107950, 1052433350, 1052758800, 1053084300, 1053409850, 1053735450, 1054061100, 1054386800, 1054712550, 1055038350, 1055364200, 1055690100, 1056016050, 1056342050, 1056668100, 1056994200, 1057320350, 1057646550, 1057972800, 1058299100, 1058625450, 1058951850, 1059278300, 1059604800, 1059931350, 1060257950, 1060584600, 1060911300, 1061238050, 1061564850, 1061891700, 1062218600, 1062545550, 1062872550, 1063199600, 1063526700, 1063853850, 1064181050, 1064508300, 1064835600, 1065162950, 1065490350, 1065817800, 1066145300, 1066472850, 1066800450, 1067128100, 1067455800, 1067783550, 1068111350, 1068439200, 1068767100, 1069095050, 1069423050, 1069751100, 1070079200, 1070407350, 1070735550, 1071063800, 1071392100, 1071720450, 1072048850, 1072377300, 1072705800, 1073034350, 1073362950, 1073691600, 1074020300, 1074349050, 1074677850, 1075006700, 1075335600, 1075664550, 1075993550, 1076322600, 1076651700, 1076980850, 1077310050, 1077639300, 1077968600, 1078297950, 1078627350, 1078956800, 1079286300, 1079615850, 1079945450, 1080275100, 1080604800, 1080934550, 1081264350, 1081594200, 1081924100, 1082254050, 1082584050, 1082914100, 1083244200, 1083574350, 1083904550, 1084234800, 1084565100, 1084895450, 1085225850, 1085556300, 1085886800, 1086217350, 1086547950, 1086878600, 1087209300, 1087540050, 1087870850, 1088201700, 1088532600, 1088863550, 1089194550, 1089525600, 1089856700, 1090187850, 1090519050, 1090850300, 1091181600, 1091512950, 1091844350, 1092175800, 1092507300, 1092838850, 1093170450, 1093502100, 1093833800, 1094165550, 1094497350, 1094829200, 1095161100, 1095493050, 1095825050, 1096157100, 1096489200, 1096821350, 1097153550, 1097485800, 1097818100, 1098150450, 1098482850, 1098815300, 1099147800, 1099480350, 1099812950, 1100145600, 1100478300, 1100811050, 1101143850, 1101476700, 1101809600, 1102142550, 1102475550, 1102808600, 1103141700, 1103474850, 1103808050, 1104141300, 1104474600, 1104807950, 1105141350, 1105474800, 1105808300, 1106141850, 1106475450, 1106809100, 1107142800, 1107476550, 1107810350, 1108144200, 1108478100, 1108812050, 1109146050, 1109480100, 1109814200, 1110148350, 1110482550, 1110816800, 1111151100, 1111485450, 1111819850, 1112154300, 1112488800, 1112823350, 1113157950, 1113492600, 1113827300, 1114162050, 1114496850, 1114831700, 1115166600, 1115501550, 1115836550, 1116171600, 1116506700, 1116841850, 1117177050, 1117512300, 1117847600, 1118182950, 1118518350, 1118853800, 1119189300, 1119524850, 1119860450, 1120196100, 1120531800, 1120867550, 1121203350, 1121539200, 1121875100, 1122211050, 1122547050, 1122883100, 1123219200, 1123555350, 1123891550, 1124227800, 1124564100, 1124900450, 1125236850, 1125573300, 1125909800, 1126246350, 1126582950, 1126919600, 1127256300, 1127593050, 1127929850, 1128266700, 1128603600, 1128940550, 1129277550, 1129614600, 1129951700, 1130288850, 1130626050, 1130963300, 1131300600, 1131637950, 1131975350, 1132312800, 1132650300, 1132987850, 1133325450, 1133663100, 1134000800, 1134338550, 1134676350, 1135014200, 1135352100, 1135690050, 1136028050, 1136366100, 1136704200, 1137042350, 1137380550, 1137718800, 1138057100, 1138395450, 1138733850, 1139072300, 1139410800, 1139749350, 1140087950, 1140426600, 1140765300, 1141104050, 1141442850, 1141781700, 1142120600, 1142459550, 1142798550, 1143137600, 1143476700, 1143815850, 1144155050, 1144494300, 1144833600, 1145172950, 1145512350, 1145851800, 1146191300, 1146530850, 1146870450, 1147210100, 1147549800, 1147889550, 1148229350, 1148569200, 1148909100, 1149249050, 1149589050, 1149929100, 1150269200, 1150609350, 1150949550, 1151289800, 1151630100, 1151970450, 1152310850, 1152651300, 1152991800, 1153332350, 1153672950, 1154013600, 1154354300, 1154695050, 1155035850, 1155376700, 1155717600, 1156058550, 1156399550, 1156740600, 1157081700, 1157422850, 1157764050, 1158105300, 1158446600, 1158787950, 1159129350, 1159470800, 1159812300, 1160153850, 1160495450, 1160837100, 1161178800, 1161520550, 1161862350, 1162204200, 1162546100, 1162888050, 1163230050, 1163572100, 1163914200, 1164256350, 1164598550, 1164940800, 1165283100, 1165625450, 1165967850, 1166310300, 1166652800, 1166995350, 1167337950, 1167680600, 1168023300, 1168366050, 1168708850, 1169051700, 1169394600, 1169737550, 1170080550, 1170423600, 1170766700, 1171109850, 1171453050, 1171796300, 1172139600, 1172482950, 1172826350, 1173169800, 1173513300, 1173856850, 1174200450, 1174544100, 1174887800, 1175231550, 1175575350, 1175919200, 1176263100, 1176607050, 1176951050, 1177295100, 1177639200, 1177983350, 1178327550, 1178671800, 1179016100, 1179360450, 1179704850, 1180049300, 1180393800, 1180738350, 1181082950, 1181427600, 1181772300, 1182117050, 1182461850, 1182806700, 1183151600, 1183496550, 1183841550, 1184186600, 1184531700, 1184876850, 1185222050, 1185567300, 1185912600, 1186257950, 1186603350, 1186948800, 1187294300, 1187639850, 1187985450, 1188331100, 1188676800, 1189022550, 1189368350, 1189714200, 1190060100, 1190406050, 1190752050, 1191098100, 1191444200, 1191790350, 1192136550, 1192482800, 1192829100, 1193175450, 1193521850, 1193868300, 1194214800, 1194561350, 1194907950, 1195254600, 1195601300, 1195948050, 1196294850, 1196641700, 1196988600, 1197335550, 1197682550, 1198029600, 1198376700, 1198723850, 1199071050, 1199418300, 1199765600, 1200112950, 1200460350, 1200807800, 1201155300, 1201502850, 1201850450, 1202198100, 1202545800, 1202893550, 1203241350, 1203589200, 1203937100, 1204285050, 1204633050, 1204981100, 1205329200, 1205677350, 1206025550, 1206373800, 1206722100, 1207070450, 1207418850, 1207767300, 1208115800, 1208464350, 1208812950, 1209161600, 1209510300, 1209859050, 1210207850, 1210556700, 1210905600, 1211254550, 1211603550, 1211952600, 1212301700, 1212650850, 1213000050, 1213349300, 1213698600, 1214047950, 1214397350, 1214746800, 1215096300, 1215445850, 1215795450, 1216145100, 1216494800, 1216844550, 1217194350, 1217544200, 1217894100, 1218244050, 1218594050, 1218944100, 1219294200, 1219644350, 1219994550, 1220344800, 1220695100, 1221045450, 1221395850, 1221746300, 1222096800, 1222447350, 1222797950, 1223148600, 1223499300, 1223850050, 1224200850, 1224551700, 1224902600, 1225253550, 1225604550, 1225955600, 1226306700, 1226657850, 1227009050, 1227360300, 1227711600, 1228062950, 1228414350, 1228765800, 1229117300, 1229468850, 1229820450, 1230172100, 1230523800, 1230875550, 1231227350, 1231579200, 1231931100, 1232283050, 1232635050, 1232987100, 1233339200, 1233691350, 1234043550, 1234395800, 1234748100, 1235100450, 1235452850, 1235805300, 1236157800, 1236510350, 1236862950, 1237215600, 1237568300, 1237921050, 1238273850, 1238626700, 1238979600, 1239332550, 1239685550, 1240038600, 1240391700, 1240744850, 1241098050, 1241451300, 1241804600, 1242157950, 1242511350, 1242864800, 1243218300, 1243571850, 1243925450, 1244279100, 1244632800, 1244986550, 1245340350, 1245694200, 1246048100, 1246402050, 1246756050, 1247110100, 1247464200, 1247818350, 1248172550, 1248526800, 1248881100, 1249235450, 1249589850, 1249944300, 1250298800, 1250653350, 1251007950, 1251362600, 1251717300, 1252072050, 1252426850, 1252781700, 1253136600, 1253491550, 1253846550, 1254201600, 1254556700, 1254911850, 1255267050, 1255622300, 1255977600, 1256332950, 1256688350, 1257043800, 1257399300, 1257754850, 1258110450, 1258466100, 1258821800, 1259177550, 1259533350, 1259889200, 1260245100, 1260601050, 1260957050, 1261313100, 1261669200, 1262025350, 1262381550, 1262737800, 1263094100, 1263450450, 1263806850, 1264163300, 1264519800, 1264876350, 1265232950, 1265589600, 1265946300, 1266303050, 1266659850, 1267016700, 1267373600, 1267730550, 1268087550, 1268444600, 1268801700, 1269158850, 1269516050, 1269873300, 1270230600, 1270587950, 1270945350, 1271302800, 1271660300, 1272017850, 1272375450, 1272733100, 1273090800, 1273448550, 1273806350, 1274164200, 1274522100, 1274880050, 1275238050, 1275596100, 1275954200, 1276312350, 1276670550, 1277028800, 1277387100, 1277745450, 1278103850, 1278462300, 1278820800, 1279179350, 1279537950, 1279896600, 1280255300, 1280614050, 1280972850, 1281331700, 1281690600, 1282049550, 1282408550, 1282767600, 1283126700, 1283485850, 1283845050, 1284204300, 1284563600, 1284922950, 1285282350, 1285641800, 1286001300, 1286360850, 1286720450, 1287080100, 1287439800, 1287799550, 1288159350, 1288519200, 1288879100, 1289239050, 1289599050, 1289959100, 1290319200, 1290679350, 1291039550, 1291399800, 1291760100, 1292120450, 1292480850, 1292841300, 1293201800, 1293562350, 1293922950, 1294283600, 1294644300, 1295005050, 1295365850, 1295726700, 1296087600, 1296448550, 1296809550, 1297170600, 1297531700, 1297892850, 1298254050, 1298615300, 1298976600, 1299337950, 1299699350, 1300060800, 1300422300, 1300783850, 1301145450, 1301507100, 1301868800, 1302230550, 1302592350, 1302954200, 1303316100, 1303678050, 1304040050, 1304402100, 1304764200, 1305126350, 1305488550, 1305850800, 1306213100, 1306575450, 1306937850, 1307300300, 1307662800, 1308025350, 1308387950, 1308750600, 1309113300, 1309476050, 1309838850, 1310201700, 1310564600, 1310927550, 1311290550, 1311653600, 1312016700, 1312379850, 1312743050, 1313106300, 1313469600, 1313832950, 1314196350, 1314559800, 1314923300, 1315286850, 1315650450, 1316014100, 1316377800, 1316741550, 1317105350, 1317469200, 1317833100, 1318197050, 1318561050, 1318925100, 1319289200, 1319653350, 1320017550, 1320381800, 1320746100, 1321110450, 1321474850, 1321839300, 1322203800, 1322568350, 1322932950, 1323297600, 1323662300, 1324027050, 1324391850, 1324756700, 1325121600, 1325486550, 1325851550, 1326216600, 1326581700, 1326946850, 1327312050, 1327677300, 1328042600, 1328407950, 1328773350, 1329138800, 1329504300, 1329869850, 1330235450, 1330601100, 1330966800, 1331332550, 1331698350, 1332064200, 1332430100, 1332796050, 1333162050, 1333528100, 1333894200, 1334260350, 1334626550, 1334992800, 1335359100, 1335725450, 1336091850, 1336458300, 1336824800, 1337191350, 1337557950, 1337924600, 1338291300, 1338658050, 1339024850, 1339391700, 1339758600, 1340125550, 1340492550, 1340859600, 1341226700, 1341593850, 1341961050, 1342328300, 1342695600, 1343062950, 1343430350, 1343797800, 1344165300, 1344532850, 1344900450, 1345268100, 1345635800, 1346003550, 1346371350, 1346739200, 1347107100, 1347475050, 1347843050, 1348211100, 1348579200, 1348947350, 1349315550, 1349683800, 1350052100, 1350420450, 1350788850, 1351157300, 1351525800, 1351894350, 1352262950, 1352631600, 1353000300, 1353369050, 1353737850, 1354106700, 1354475600, 1354844550, 1355213550, 1355582600, 1355951700, 1356320850, 1356690050, 1357059300, 1357428600, 1357797950, 1358167350, 1358536800, 1358906300, 1359275850, 1359645450, 1360015100, 1360384800, 1360754550, 1361124350, 1361494200, 1361864100, 1362234050, 1362604050, 1362974100, 1363344200, 1363714350, 1364084550, 1364454800, 1364825100, 1365195450, 1365565850, 1365936300, 1366306800, 1366677350, 1367047950, 1367418600, 1367789300, 1368160050, 1368530850, 1368901700, 1369272600, 1369643550, 1370014550, 1370385600, 1370756700, 1371127850, 1371499050, 1371870300, 1372241600, 1372612950, 1372984350, 1373355800, 1373727300, 1374098850, 1374470450, 1374842100, 1375213800, 1375585550, 1375957350, 1376329200, 1376701100, 1377073050, 1377445050, 1377817100, 1378189200, 1378561350, 1378933550, 1379305800, 1379678100, 1380050450, 1380422850, 1380795300, 1381167800, 1381540350, 1381912950, 1382285600, 1382658300, 1383031050, 1383403850, 1383776700, 1384149600, 1384522550, 1384895550, 1385268600, 1385641700, 1386014850, 1386388050, 1386761300, 1387134600, 1387507950, 1387881350, 1388254800, 1388628300, 1389001850, 1389375450, 1389749100, 1390122800, 1390496550, 1390870350, 1391244200, 1391618100, 1391992050, 1392366050, 1392740100, 1393114200, 1393488350, 1393862550, 1394236800, 1394611100, 1394985450, 1395359850, 1395734300, 1396108800, 1396483350, 1396857950, 1397232600, 1397607300, 1397982050, 1398356850, 1398731700, 1399106600, 1399481550, 1399856550, 1400231600, 1400606700, 1400981850, 1401357050, 1401732300, 1402107600, 1402482950, 1402858350, 1403233800, 1403609300, 1403984850, 1404360450, 1404736100, 1405111800, 1405487550, 1405863350, 1406239200, 1406615100, 1406991050, 1407367050, 1407743100, 1408119200, 1408495350, 1408871550, 1409247800, 1409624100, 1410000450, 1410376850, 1410753300, 1411129800, 1411506350, 1411882950, 1412259600, 1412636300, 1413013050, 1413389850, 1413766700, 1414143600, 1414520550, 1414897550, 1415274600, 1415651700, 1416028850, 1416406050, 1416783300, 1417160600, 1417537950, 1417915350, 1418292800, 1418670300, 1419047850, 1419425450, 1419803100, 1420180800, 1420558550, 1420936350, 1421314200, 1421692100, 1422070050, 1422448050, 1422826100, 1423204200, 1423582350, 1423960550, 1424338800, 1424717100, 1425095450, 1425473850, 1425852300, 1426230800, 1426609350, 1426987950, 1427366600, 1427745300, 1428124050, 1428502850, 1428881700, 1429260600, 1429639550, 1430018550, 1430397600, 1430776700, 1431155850, 1431535050, 1431914300, 1432293600, 1432672950, 1433052350, 1433431800, 1433811300, 1434190850, 1434570450, 1434950100, 1435329800, 1435709550, 1436089350, 1436469200, 1436849100, 1437229050, 1437609050, 1437989100, 1438369200, 1438749350, 1439129550, 1439509800, 1439890100, 1440270450, 1440650850, 1441031300, 1441411800, 1441792350, 1442172950, 1442553600, 1442934300, 1443315050, 1443695850, 1444076700, 1444457600, 1444838550, 1445219550, 1445600600, 1445981700, 1446362850, 1446744050, 1447125300, 1447506600, 1447887950, 1448269350, 1448650800, 1449032300, 1449413850, 1449795450, 1450177100, 1450558800, 1450940550, 1451322350, 1451704200, 1452086100, 1452468050, 1452850050, 1453232100, 1453614200, 1453996350, 1454378550, 1454760800, 1455143100, 1455525450, 1455907850, 1456290300, 1456672800, 1457055350, 1457437950, 1457820600, 1458203300, 1458586050, 1458968850, 1459351700, 1459734600, 1460117550, 1460500550, 1460883600, 1461266700, 1461649850, 1462033050, 1462416300, 1462799600, 1463182950, 1463566350, 1463949800, 1464333300, 1464716850, 1465100450, 1465484100, 1465867800, 1466251550, 1466635350, 1467019200, 1467403100, 1467787050, 1468171050, 1468555100, 1468939200, 1469323350, 1469707550, 1470091800, 1470476100, 1470860450, 1471244850, 1471629300, 1472013800, 1472398350, 1472782950, 1473167600, 1473552300, 1473937050, 1474321850, 1474706700, 1475091600, 1475476550, 1475861550, 1476246600, 1476631700, 1477016850, 1477402050, 1477787300, 1478172600, 1478557950, 1478943350, 1479328800, 1479714300, 1480099850, 1480485450, 1480871100, 1481256800, 1481642550, 1482028350, 1482414200, 1482800100, 1483186050, 1483572050, 1483958100, 1484344200, 1484730350, 1485116550, 1485502800, 1485889100, 1486275450, 1486661850, 1487048300, 1487434800, 1487821350, 1488207950, 1488594600, 1488981300, 1489368050, 1489754850, 1490141700, 1490528600, 1490915550, 1491302550, 1491689600, 1492076700, 1492463850, 1492851050, 1493238300, 1493625600, 1494012950, 1494400350, 1494787800, 1495175300, 1495562850, 1495950450, 1496338100, 1496725800, 1497113550, 1497501350, 1497889200, 1498277100, 1498665050, 1499053050, 1499441100, 1499829200, 1500217350, 1500605550, 1500993800, 1501382100, 1501770450, 1502158850, 1502547300, 1502935800, 1503324350, 1503712950, 1504101600, 1504490300, 1504879050, 1505267850, 1505656700, 1506045600, 1506434550, 1506823550, 1507212600, 1507601700, 1507990850, 1508380050, 1508769300, 1509158600, 1509547950, 1509937350, 1510326800, 1510716300, 1511105850, 1511495450, 1511885100, 1512274800, 1512664550, 1513054350, 1513444200, 1513834100, 1514224050, 1514614050, 1515004100, 1515394200, 1515784350, 1516174550, 1516564800, 1516955100, 1517345450, 1517735850, 1518126300, 1518516800, 1518907350, 1519297950, 1519688600, 1520079300, 1520470050, 1520860850, 1521251700, 1521642600, 1522033550, 1522424550, 1522815600, 1523206700, 1523597850, 1523989050, 1524380300, 1524771600, 1525162950, 1525554350, 1525945800, 1526337300, 1526728850, 1527120450, 1527512100, 1527903800, 1528295550, 1528687350, 1529079200, 1529471100, 1529863050, 1530255050, 1530647100, 1531039200, 1531431350, 1531823550, 1532215800, 1532608100, 1533000450, 1533392850, 1533785300, 1534177800, 1534570350, 1534962950, 1535355600, 1535748300, 1536141050, 1536533850, 1536926700, 1537319600, 1537712550, 1538105550, 1538498600, 1538891700, 1539284850, 1539678050, 1540071300, 1540464600, 1540857950, 1541251350, 1541644800, 1542038300, 1542431850, 1542825450, 1543219100, 1543612800, 1544006550, 1544400350, 1544794200, 1545188100, 1545582050, 1545976050, 1546370100, 1546764200, 1547158350, 1547552550, 1547946800, 1548341100, 1548735450, 1549129850, 1549524300, 1549918800, 1550313350, 1550707950, 1551102600, 1551497300, 1551892050, 1552286850, 1552681700, 1553076600, 1553471550, 1553866550, 1554261600, 1554656700, 1555051850, 1555447050, 1555842300, 1556237600, 1556632950, 1557028350, 1557423800, 1557819300, 1558214850, 1558610450, 1559006100, 1559401800, 1559797550, 1560193350, 1560589200, 1560985100, 1561381050, 1561777050, 1562173100, 1562569200, 1562965350, 1563361550, 1563757800, 1564154100, 1564550450, 1564946850, 1565343300, 1565739800, 1566136350, 1566532950, 1566929600, 1567326300, 1567723050, 1568119850, 1568516700, 1568913600, 1569310550, 1569707550, 1570104600, 1570501700, 1570898850, 1571296050, 1571693300, 1572090600, 1572487950, 1572885350, 1573282800, 1573680300, 1574077850, 1574475450, 1574873100, 1575270800, 1575668550, 1576066350, 1576464200, 1576862100, 1577260050, 1577658050, 1578056100, 1578454200, 1578852350, 1579250550, 1579648800, 1580047100, 1580445450, 1580843850, 1581242300, 1581640800, 1582039350, 1582437950, 1582836600, 1583235300, 1583634050, 1584032850, 1584431700, 1584830600, 1585229550, 1585628550, 1586027600, 1586426700, 1586825850, 1587225050, 1587624300, 1588023600, 1588422950, 1588822350, 1589221800, 1589621300, 1590020850, 1590420450, 1590820100, 1591219800, 1591619550, 1592019350, 1592419200, 1592819100, 1593219050, 1593619050, 1594019100, 1594419200, 1594819350, 1595219550, 1595619800, 1596020100, 1596420450, 1596820850, 1597221300, 1597621800, 1598022350, 1598422950, 1598823600, 1599224300, 1599625050, 1600025850, 1600426700, 1600827600, 1601228550, 1601629550, 1602030600, 1602431700, 1602832850, 1603234050, 1603635300, 1604036600, 1604437950, 1604839350, 1605240800, 1605642300, 1606043850, 1606445450, 1606847100, 1607248800, 1607650550, 1608052350, 1608454200, 1608856100, 1609258050, 1609660050, 1610062100, 1610464200, 1610866350, 1611268550, 1611670800, 1612073100, 1612475450, 1612877850, 1613280300, 1613682800, 1614085350, 1614487950, 1614890600, 1615293300, 1615696050, 1616098850, 1616501700, 1616904600, 1617307550, 1617710550, 1618113600, 1618516700, 1618919850, 1619323050, 1619726300, 1620129600, 1620532950, 1620936350, 1621339800, 1621743300, 1622146850, 1622550450, 1622954100, 1623357800, 1623761550, 1624165350, 1624569200, 1624973100, 1625377050, 1625781050, 1626185100, 1626589200, 1626993350, 1627397550, 1627801800, 1628206100, 1628610450, 1629014850, 1629419300, 1629823800, 1630228350, 1630632950, 1631037600, 1631442300, 1631847050, 1632251850, 1632656700, 1633061600, 1633466550, 1633871550, 1634276600, 1634681700, 1635086850, 1635492050, 1635897300, 1636302600, 1636707950, 1637113350, 1637518800, 1637924300, 1638329850, 1638735450, 1639141100, 1639546800, 1639952550, 1640358350, 1640764200, 1641170100, 1641576050, 1641982050, 1642388100, 1642794200, 1643200350, 1643606550, 1644012800, 1644419100, 1644825450, 1645231850, 1645638300, 1646044800, 1646451350, 1646857950, 1647264600, 1647671300, 1648078050, 1648484850, 1648891700, 1649298600, 1649705550, 1650112550, 1650519600, 1650926700, 1651333850, 1651741050, 1652148300, 1652555600, 1652962950, 1653370350, 1653777800, 1654185300, 1654592850, 1655000450, 1655408100, 1655815800, 1656223550, 1656631350, 1657039200, 1657447100, 1657855050, 1658263050, 1658671100, 1659079200, 1659487350, 1659895550, 1660303800, 1660712100, 1661120450, 1661528850, 1661937300, 1662345800, 1662754350, 1663162950, 1663571600, 1663980300, 1664389050, 1664797850, 1665206700, 1665615600, 1666024550, 1666433550, 1666842600, 1667251700, 1667660850, 1668070050, 1668479300, 1668888600, 1669297950, 1669707350, 1670116800, 1670526300, 1670935850, 1671345450, 1671755100, 1672164800, 1672574550, 1672984350, 1673394200, 1673804100, 1674214050, 1674624050, 1675034100, 1675444200, 1675854350, 1676264550, 1676674800, 1677085100, 1677495450, 1677905850, 1678316300, 1678726800, 1679137350, 1679547950, 1679958600, 1680369300, 1680780050, 1681190850, 1681601700, 1682012600, 1682423550, 1682834550, 1683245600, 1683656700, 1684067850, 1684479050, 1684890300, 1685301600, 1685712950, 1686124350, 1686535800, 1686947300, 1687358850, 1687770450, 1688182100, 1688593800, 1689005550, 1689417350, 1689829200, 1690241100, 1690653050, 1691065050, 1691477100, 1691889200, 1692301350, 1692713550, 1693125800, 1693538100, 1693950450, 1694362850, 1694775300, 1695187800, 1695600350, 1696012950, 1696425600, 1696838300, 1697251050, 1697663850, 1698076700, 1698489600, 1698902550, 1699315550, 1699728600, 1700141700, 1700554850, 1700968050, 1701381300, 1701794600, 1702207950, 1702621350, 1703034800, 1703448300, 1703861850, 1704275450, 1704689100, 1705102800, 1705516550, 1705930350, 1706344200, 1706758100, 1707172050, 1707586050, 1708000100, 1708414200, 1708828350, 1709242550, 1709656800, 1710071100, 1710485450, 1710899850, 1711314300, 1711728800, 1712143350, 1712557950, 1712972600, 1713387300, 1713802050, 1714216850, 1714631700, 1715046600, 1715461550, 1715876550, 1716291600, 1716706700, 1717121850, 1717537050, 1717952300, 1718367600, 1718782950, 1719198350, 1719613800, 1720029300, 1720444850, 1720860450, 1721276100, 1721691800, 1722107550, 1722523350, 1722939200, 1723355100, 1723771050, 1724187050, 1724603100, 1725019200, 1725435350, 1725851550, 1726267800, 1726684100, 1727100450, 1727516850, 1727933300, 1728349800, 1728766350, 1729182950, 1729599600, 1730016300, 1730433050, 1730849850, 1731266700, 1731683600, 1732100550, 1732517550, 1732934600, 1733351700, 1733768850, 1734186050, 1734603300, 1735020600, 1735437950, 1735855350, 1736272800, 1736690300, 1737107850, 1737525450, 1737943100, 1738360800, 1738778550, 1739196350, 1739614200, 1740032100, 1740450050, 1740868050, 1741286100, 1741704200, 1742122350, 1742540550, 1742958800, 1743377100, 1743795450, 1744213850, 1744632300, 1745050800, 1745469350, 1745887950, 1746306600, 1746725300, 1747144050, 1747562850, 1747981700, 1748400600, 1748819550, 1749238550, 1749657600, 1750076700, 1750495850, 1750915050, 1751334300, 1751753600, 1752172950, 1752592350, 1753011800, 1753431300, 1753850850, 1754270450, 1754690100, 1755109800, 1755529550, 1755949350, 1756369200, 1756789100, 1757209050, 1757629050, 1758049100, 1758469200, 1758889350, 1759309550, 1759729800, 1760150100, 1760570450, 1760990850, 1761411300, 1761831800, 1762252350, 1762672950, 1763093600, 1763514300, 1763935050, 1764355850, 1764776700, 1765197600, 1765618550, 1766039550, 1766460600, 1766881700, 1767302850, 1767724050, 1768145300, 1768566600, 1768987950, 1769409350, 1769830800, 1770252300, 1770673850, 1771095450, 1771517100, 1771938800, 1772360550, 1772782350, 1773204200, 1773626100, 1774048050, 1774470050, 1774892100, 1775314200, 1775736350, 1776158550, 1776580800, 1777003100, 1777425450, 1777847850, 1778270300, 1778692800, 1779115350, 1779537950, 1779960600, 1780383300, 1780806050, 1781228850, 1781651700, 1782074600, 1782497550, 1782920550, 1783343600, 1783766700, 1784189850, 1784613050, 1785036300, 1785459600, 1785882950, 1786306350, 1786729800, 1787153300, 1787576850 };
		std::string m_level_buffer;
		int m_level = 0;
	};
	class CRecovery {
	public:
		CLevel m_level;
	};
	inline CRecovery m_recovery;
	inline std::vector<std::string> outfitNames;
	inline std::vector<std::string> OutfitList()
	{
		std::string folderpath = "C:\\Saint\\Outfits\\";
		if (!fs::exists(folderpath.c_str()))
		{
			fs::create_directory(folderpath.c_str());
		}
		std::vector<std::string> tempVector;
		int fileCount = 0;
		std::stringstream tempStringStream;
		for (auto& collectedFiles : fs::directory_iterator("C:\\Saint\\Outfits\\"))
		{

			std::string oing = tempStringStream.str();
			if (oing.substr(oing.find_last_of(".") + 1) == "ini")
			{
				unsigned foundAmount = oing.find_last_of("/\\");
				std::string TempHolder = oing.substr(0, foundAmount);
				std::string TempHolder2 = oing.substr(foundAmount + 1);
				tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
				outfitNames = tempVector;
			}
		}
		return tempVector;
	}
	class OutfitLoader {
	public:
		std::string buffer;
		bool DoesIniExists(const char* path)
		{

			struct stat buffer;
			return (stat(path, &buffer) == 0);

		}
		void save(std::string name) {
			auto handling = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_handling_data;
			std::string MenuFolderPath = "C:\\Saint\\Outfits\\";
			Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
			

			ColorIni->WriteInt(testb, "Head", "index");
			ColorIni->WriteInt(facetexture1, "Head", "texture");

			

			ColorIni->WriteInt(testd, "Torso", "index");
			ColorIni->WriteInt(facetexture3, "Torso", "texture");

			ColorIni->WriteInt(testl, "Tops", "index");
			ColorIni->WriteInt(facetexture4, "Tops", "texture");

			ColorIni->WriteInt(teste, "Legs", "index");
			ColorIni->WriteInt(facetexture5, "Legs", "texture");

			ColorIni->WriteInt(testf, "Hands", "index");
			ColorIni->WriteInt(facetexture6, "Hands", "texture");

			ColorIni->WriteInt(testg, "Feet", "index");
			ColorIni->WriteInt(facetexture7, "Feet", "texture");

			ColorIni->WriteInt(testh, "Chains", "index");
			ColorIni->WriteInt(facetexture8, "Chains", "texture");

			ColorIni->WriteInt(testi, "Accessories", "index");
			ColorIni->WriteInt(facetexture9, "Accessories", "texture");

			ColorIni->WriteInt(testj, "Vests", "index");
			ColorIni->WriteInt(facetexture10, "Vests", "texture");

			ColorIni->WriteInt(testk, "Decals", "index");
			ColorIni->WriteInt(facetexture11, "Decals", "texture");

			ColorIni->WriteInt(hatDrawable, "Hats", "index");
			ColorIni->WriteInt(hatTexture, "Hats", "texture");

			ColorIni->WriteInt(glassesDrawable, "Glasses", "index");
			ColorIni->WriteInt(glassesTexture, "Glasses", "texture");

			ColorIni->WriteInt(earsDrawable, "Ears", "index");
			ColorIni->WriteInt(earsTexture, "Ears", "texture");

			ColorIni->WriteInt(watchesDrawable, "Watches", "index");
			ColorIni->WriteInt(watchesTexture, "Watches", "texture");

			ColorIni->WriteInt(braceDrawable, "Bracelets", "index");
			ColorIni->WriteInt(braceTexture, "Bracelets", "texture");

			
		}
		void load(std::string name) {
			std::string MenuFolderPath = "C:\\Saint\\Outfits\\";
			if (DoesIniExists((MenuFolderPath + name + ".ini").c_str())) {
				Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
				testb = ColorIni->GetInt("Head", "index");
				facetexture1 = ColorIni->GetInt("Head", "texture");

				testd = ColorIni->GetInt("Torso", "index");
				facetexture3 = ColorIni->GetInt("Torso", "texture");

				testl = ColorIni->GetInt("Tops", "index");
				facetexture4 = ColorIni->GetInt("Tops", "texture");

				teste = ColorIni->GetInt("Legs", "index");
				facetexture5 = ColorIni->GetInt("Legs", "texture");

				testf = ColorIni->GetInt("Hands", "index");
				facetexture6 = ColorIni->GetInt("Hands", "texture");

				testg = ColorIni->GetInt("Feet", "index");
				facetexture7 = ColorIni->GetInt("Feet", "texture");

				testh = ColorIni->GetInt("Chains", "index");
				facetexture8 = ColorIni->GetInt("Chains", "texture");

				testi = ColorIni->GetInt("Accessories", "index");
				facetexture9 = ColorIni->GetInt("Accessories", "texture");

				testj = ColorIni->GetInt("Vests", "index");
				facetexture10 = ColorIni->GetInt("Vests", "texture");

				testk = ColorIni->GetInt("Decals", "index");
				facetexture11 = ColorIni->GetInt("Decals", "texture");

				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, ColorIni->GetInt("Head", "index"), ColorIni->GetInt("Head", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, ColorIni->GetInt("Torso", "index"), ColorIni->GetInt("Torso", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, ColorIni->GetInt("Tops", "index"), ColorIni->GetInt("Tops", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, ColorIni->GetInt("Legs", "index"), ColorIni->GetInt("Legs", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, ColorIni->GetInt("Hands", "index"), ColorIni->GetInt("Hands", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, ColorIni->GetInt("Feet", "index"), ColorIni->GetInt("Feet", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, ColorIni->GetInt("Chains", "index"), ColorIni->GetInt("Chains", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, ColorIni->GetInt("Accessories", "index"), ColorIni->GetInt("Accessories", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, ColorIni->GetInt("Vests", "index"), ColorIni->GetInt("Vests", "texture"), 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, ColorIni->GetInt("Decals", "index"), ColorIni->GetInt("Decals", "texture"), 0);
				PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, ColorIni->GetInt("Hats", "index"), ColorIni->GetInt("Hats", "texture"), 0);
				PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, ColorIni->GetInt("Glasses", "index"), ColorIni->GetInt("Glasses", "texture"), 0);
				PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, ColorIni->GetInt("Ears", "index"), ColorIni->GetInt("Ears", "texture"), 0);
				PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 6, ColorIni->GetInt("Watches", "index"), ColorIni->GetInt("Watches", "texture"), 0);
				PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 7, ColorIni->GetInt("Bracelets", "index"), ColorIni->GetInt("Bracelets", "texture"), 0);
				Noti::InsertNotification({ ImGuiToastType_None, 2000, "Loaded '%s'", name });




			}
		}
	};
	inline OutfitLoader g_Outfits;
	class FrameFlags {
	public:
		bool m_fire = false;
		bool m_explosive_melee = false;
		void init() {
			if (m_explosive_melee) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_frame_flags = 1 << 13;
			}
			if (m_fire) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_frame_flags = 1 << 12;
			}
		}
	};
	inline FrameFlags m_frame_flags;
	class EntityShooter2 {
	public:
		int selected_class;
		std::string buffer;
		Hash selected_hash = 0x6838FC1D;
		bool enabled = false;
		Vehicle entityGunVehicle;
		void init() {
			if (enabled) {
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
						NativeVector3 cameraCoords = CAM::GET_GAMEPLAY_CAM_COORD();
						NativeVector3 cameraDirection = RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0));
						NativeVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
						NativeVector3 startMutliply = multiply(&cameraDirection, std::distance(&cameraCoords, &playerCoords) + 15.25f);
						NativeVector3 start = addn(&cameraCoords, &startMutliply);
						NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
						float pitch = DegreeToRadian(rot.x);
						float yaw = DegreeToRadian(rot.z + 90);
						NativeVector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
						
						g_CallbackScript->AddCallback<ModelCallback>(selected_hash, [=] {
							*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
							entityGunVehicle = VEHICLE::CREATE_VEHICLE(selected_hash, start.x, start.y, start.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, false, false);
							*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
							DECORATOR::DECOR_SET_INT(entityGunVehicle, "MPBitset", 0);
							auto networkId = NETWORK::VEH_TO_NET(entityGunVehicle);
							if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(entityGunVehicle))
								NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
							VEHICLE::SET_VEHICLE_IS_STOLEN(entityGunVehicle, FALSE);
							NativeVector3 velocity;
							NativeVector3 other = ENTITY::GET_ENTITY_COORDS(entityGunVehicle, true);
							velocity.x = location.x + (1000.0f * cos(pitch) * cos(yaw)) - other.x;
							velocity.y = location.y + (1000.0f * sin(yaw) * cos(pitch)) - other.y;
							velocity.z = location.z + (1000.0f * sin(pitch)) - other.z;
							ENTITY::SET_ENTITY_ROTATION(entityGunVehicle, rot.x, rot.y, rot.z, 2, false);
							ENTITY::SET_ENTITY_VELOCITY2(entityGunVehicle, { velocity.x * (float)3.0, velocity.y * (float)3.0, velocity.z * (float)3.0 });
						});
					
				}
			}
		}
	};
	inline EntityShooter2 m_entity_shooter;
	inline const char* casino_teleport[4] = { "Mantrap Door", "Inside The Vault", "Main Gate", "Planning Boards" };
	inline std::size_t casino_tp = 0;
	inline const char* Aproach[4] = { "Diamonds", "Gold", "Artwork", "Cash" };
	inline std::size_t Opreracogh2 = 0;
	inline const char* Aproach2[5] = { "Chester McCoy (Best)", "Eddie Toh", "Taliana Martinez", "Zach Nelson", "Karim Denz" };
	inline std::size_t Opreracogh22 = 0;
	inline const char* Aproach3[5] = { "Tequila", "Ruby Necklace", "Bearer Bonds", "Pink Diamond", "Panther Statue" };
	inline std::size_t Opreracogh223 = 0;
	inline const char* AproachVeh[6] = { "Kosatka", "Alkonost", "Velum", "Stealth Annihilator", "Patrol Boat", "Longfin" };
	inline std::size_t Opreracogh2232 = 0;
	class Disables2 {
	public:
		bool recording = false;
		bool cin = false;
		bool stuntjumps = false;
		bool idle_cam = false;
		void init() {
			if (idle_cam) {
				CAM::INVALIDATE_IDLE_CAM();
			}
			if (cin) {
				CAM::SET_CINEMATIC_BUTTON_ACTIVE(false);
			}
			if (recording) {
				RECORDING::CANCEL_REPLAY_RECORDING();
				RECORDING::REPLAY_PREVENT_RECORDING_THIS_FRAME();
			}
			if (stuntjumps)
			{
				MISC::CANCEL_STUNT_JUMP();
			}
		}
	};
	inline Disables2 m_disables;
	class Traffic {
	public:
		bool horn = false;
		bool rainbow = false;
		std::size_t acrobatic = 0;
		int r = 0;
		int g = 255;
		int b = 0;
		const char* rainbow_type[2] = { "Stop", "Constant"};
		std::size_t rainbow_int = 0;
		bool max_loop = false;
		int max_loop_delay = 250;
		void init() {
			
			if (rainbow_int == 1) {
				if (r > 0 && b == 0) {
					r--;
					g++;
				}
				if (g > 0 && r == 0) {
					g--;
					b++;
				}
				if (b > 0 && g == 0) {
					r++;
					b--;
				}
			}

			if (rainbow) {
				if (rainbow_int == 0) {
					if (r > 0 && b == 0) {
						r--;
						g++;
					}
					if (g > 0 && r == 0) {
						g--;
						b++;
					}
					if (b > 0 && g == 0) {
						r++;
						b--;
					}
				}
			}
			Vehicle* vehicles = new Vehicle[(10 * 2 + 2)];
			vehicles[0] = 10;
			for (int i = 0; i < PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehicles); i++)
			{
				Vehicle vehicle = vehicles[(i * 2 + 2)];
				if (vehicle != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)) {
					NativeVector3 vehicleCoords = ENTITY::GET_ENTITY_COORDS(vehicle, true);
					if (horn) {
						AUDIO::SET_HORN_PERMANENTLY_ON(vehicle);
					}
					if (rainbow) {
						
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, r, g, b);
					}
					if (max_loop) {
						
						Vehicle playerVehicle = vehicle;
						VEHICLE::SET_VEHICLE_MOD_KIT(playerVehicle, 0);
						for (int i = 0; i < 50; i++)
						{
							VEHICLE::SET_VEHICLE_MOD(playerVehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(playerVehicle, i) - 1), false);

						}
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
						VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
					}
					
				}
			}
			delete vehicles;
			
		}
	};
	class PedN {
	public:
		bool IsPedShooting(Ped ped)
		{
			NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(ped, true);
			return PED::IS_PED_SHOOTING_IN_AREA(ped, Coords.x, Coords.y, Coords.z, Coords.x, Coords.y, Coords.z, true, true);
		}
		bool activated = false;
		bool enabled = false;
		float speed = 3.0f;
		NativeVector3 coords;
		bool riot = false;
		void init() {
			if (enabled) {
				if (IsPedShooting(PLAYER::PLAYER_PED_ID()))
				{
					NativeVector3 hitCoords;
					if (raycast(hitCoords)) {
						auto BulletCoord = hitCoords;
						coords = { BulletCoord.x, BulletCoord.y, BulletCoord.z };
						activated = true;

					}
				}

				if (activated)
				{
					Ped* peds = new Ped[(10 * 2 + 2)];
					peds[0] = 10;
					for (int i = 0; i < PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, 0); i++)
					{
						Ped ped = peds[(i * 2 + 2)];
						auto Coords = ENTITY::GET_ENTITY_COORDS(ped, true);
						auto Distance = SYSTEM::VDIST(coords.x, coords.y, coords.z, Coords.x, Coords.y, Coords.z);
						if (Distance < 3.0f)
						{
							TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
							TASK::CLEAR_PED_SECONDARY_TASK(ped);
							activated = false;
						}
						else
						{
							NativeVector3 Velocity;
							Velocity.x = (coords.x - Coords.x) * 3.0f;
							Velocity.y = (coords.y - Coords.y) * 3.0f;
							Velocity.z = (coords.z - Coords.z) * 3.0f;
							TASK::TASK_SKY_DIVE(ped, 0);
							ENTITY::SET_ENTITY_VELOCITY(ped, Velocity.x, Velocity.y, Velocity.z);
						}

					}
					delete peds;
					
				}
			}
			if (riot) {
				MISC::SET_RIOT_MODE_ENABLED(true);
			}
		}
	};
	class Nearby {
	public:
		Traffic m_traffic;
		PedN m_peds;
	};
	inline Nearby m_nearby;
	class PlayerImpacts {
	public:
		bool teleport = false;
		void init() {
			if (teleport) {
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer)))
					{
						float c[6];
						WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), (NativeVector3*)c);
						if (c[0] != 0 || c[2] != 0 || c[4] != 0) {
							
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), c[0], c[2], c[4], true, true, true);

						}
					}
				
			}
		}
	};
	inline PlayerImpacts m_impacts;
	class m_no_clip_hotkey {
	public:
		bool enabled = false;
		int key = 0;
	};
	class Hotkeys {
	public:
		m_no_clip_hotkey no_clip_hotkey;
		void add(bool buffer, int key) {

		}
		void init() {
			
			
		}
	};
	inline Hotkeys m_hotkeys;
	inline std::string Spawner_buffer = "";
	class VehicleFX {
	public:
		bool lf = false;
		bool bl5 = false;
		bool fr5 = false;
		bool br = false;
		bool exaust2 = false;
		bool brakele = false;
		bool brakerig = false;
		bool taill = false;
		bool tailr = false;
		bool spoilerr = false;
		float vscale = 0.50f;
		bool enabled = false;
		bool networked = true;
		const char* type[8] = { "Banknotes", "Fireworks (Trailburst)", "Fireworks (Burst)", "Fireworks (Spiral Starburst)","Fireworks (Trailburst Spawn)","Clown Appears", "Water Splash", "Cartoon" };
		const char* particle_asset[8] = { "scr_ornate_heist", "scr_indep_fireworks", "proj_xmas_firework", "proj_xmas_firework","scr_rcpaparazzo1","scr_rcbarry2", "scr_fbi5a", "scr_rcbarry2"};
		const char* particle_fx[8] = { "scr_heist_ornate_banknotes", "scr_indep_firework_trailburst", "scr_firework_xmas_burst_rgw", "scr_firework_xmas_spiral_burst_rgw","scr_mich4_firework_trailburst_spawn","scr_clown_appears", "scr_fbi5_ped_water_splash", "muz_clown" };
		std::size_t size = 0;
		bool gas_cap = false;
		void init() {
			Vehicle vplayerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			NativeVector3 wheelOne = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "wheel_lf"));
			NativeVector3 wheelTwo = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "wheel_lr"));
			NativeVector3 wheelThree = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "wheel_rf"));
			NativeVector3 wheelFour = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "wheel_rr"));
			NativeVector3 exaust = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "exhaust"));
			NativeVector3 brakeleft = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "brakelight_l"));
			NativeVector3 brakeright = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "brakelight_r"));
			NativeVector3 tailleft = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "taillight_l"));
			NativeVector3 trailright = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "taillight_r"));
			NativeVector3 spoiler = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "spoiler"));
			NativeVector3 gas_cap_location = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vplayerVehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vplayerVehicle, "petrolcap"));
			g_CallbackScript->AddCallback<PTFXCallback>(particle_asset[size], [=] {
				if (gas_cap)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], gas_cap_location, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (lf)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], wheelOne, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (bl5)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);

					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], wheelTwo, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (fr5)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], wheelThree, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (br)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], wheelFour, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				//other
				if (exaust2)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], exaust, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (brakele)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], brakeleft, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (brakerig)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], brakeright, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (taill)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], tailleft, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (tailr)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], trailright, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
				if (spoilerr)
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(particle_asset[size]);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle_fx[size], spoiler, { 0.f, 0.f, 0.f }, vscale, false, false, false, true);
				}
			});
		}
	};
	inline VehicleFX m_fx;
	inline void statSetBool(const char* stat, bool value, bool direct = false, int slot = 0) {
		if (direct) {
			STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY(stat), value, true);
		}
		else {
			if (slot == 0) {
				STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY((std::string("MP0_") + std::string(stat)).c_str()), value, true);
			}
			else if (slot == 1) {
				STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY((std::string("MP1_") + std::string(stat)).c_str()), value, true);
			}
			else {
				STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY((std::string("MP0_") + std::string(stat)).c_str()), value, true);
				STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY((std::string("MP1_") + std::string(stat)).c_str()), value, true);
			}
		}
	}
	inline void statSetInt(const char* stat, int value, bool direct = false, int slot = 0) {
		if (direct) {
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY(stat), value, true);
		}
		else {
			if (slot == 0) {
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY((std::string("MP0_") + std::string(stat)).c_str()), value, true);
			}
			else if (slot == 1) {
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY((std::string("MP1_") + std::string(stat)).c_str()), value, true);
			}
			else {
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY((std::string("MP0_") + std::string(stat)).c_str()), value, true);
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY((std::string("MP1_") + std::string(stat)).c_str()), value, true);
			}
		}
	}
	class ShotGunMode {
	public:
		bool enabled = false;
		void onDisable() {
			(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_batch_spread = 0.1f;
			(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_bullets_in_batch = 1;
			(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_force = 200.0f;
			(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_speed = 5000.0f;
		}
		void init() {
			if (enabled) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_batch_spread = 0.5f;
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_bullets_in_batch = 30;
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_force = 200.0f;
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_weapon_manager->m_weapon_info->m_speed = 5000.0f;
			}
		}
	};
	inline ShotGunMode m_shotgun;
	class HandTrail {
	public:
		void ParticleOnBone(const char* dict, const char* particle, PedBones bone, float scale, bool color = false, float r = 1.f, float g = 1.f, float b = 1.f)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET(dict);
			GRAPHICS::USE_PARTICLE_FX_ASSET(dict);
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particle, PLAYER::PLAYER_PED_ID(), 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.0f, bone, scale, TRUE, TRUE, TRUE);
			if (color)
				GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(r, g, b);
			STREAMING::REMOVE_PTFX_ASSET();
		}

		const char* type[2] = { "Normal", "Sphere" };
		std::size_t size = 0;
		bool enabled = false;
		bool rainbow = false;
		int r = 255;
		int g = 255;
		int b = 255;
		void init() {
			if (enabled) {
				if (size == 0) {
					if (rainbow) {
						if (r > 0 && b == 0) {
							r--;
							g++;
						}
						if (g > 0 && r == 0) {
							g--;
							b++;
						}
						if (b > 0 && g == 0) {
							r++;
							b--;
						}
					}
					float r2 = r / 255.f;
					float g2 = g / 255.f;
					float b2 = b / 255.f;
					ParticleOnBone("scr_powerplay", "sp_powerplay_beast_appear_trails", SKEL_L_Hand, 0.2f, true, r2, g2, b2);
					ParticleOnBone("scr_powerplay", "sp_powerplay_beast_appear_trails", SKEL_R_Hand, 0.2f, true, r2, g2, b2);
				}
				if (size == 1) {
					if (rainbow) {
						if (r > 0 && b == 0) {
							r--;
							g++;
						}
						if (g > 0 && r == 0) {
							g--;
							b++;
						}
						if (b > 0 && g == 0) {
							r++;
							b--;
						}
					}
					float r2 = r / 255.f;
					float g2 = g / 255.f;
					float b2 = b / 255.f;
					ParticleOnBone("scr_indep_fireworks", "scr_indep_firework_sparkle_spawn", SKEL_L_Hand, 0.5f, true, r2, g2, b2);
					ParticleOnBone("scr_indep_fireworks", "scr_indep_firework_sparkle_spawn", SKEL_R_Hand, 0.5f, true, r2, g2, b2);
				}
			}
		}
	};
	inline HandTrail g_HandTrails;
	inline std::string LiscenePlate;
	inline void controlid(Entity netid)
	{
		int tick = 0;

		while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
			tick++;
		}
	}
	inline void control(Entity entity)
	{
		int tick = 0;
		while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
			tick++;
		}
		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
			controlid(netID);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
		}
	}
	class SavedPlayers {
	public:
		bool DoesIniExists(const char* path)
		{

			struct stat buffer;
			return (stat(path, &buffer) == 0);

		}
		
		
		void delete_all() {

		}
		void add(Player player) {
			std::string name = PLAYER::GET_PLAYER_NAME(player);
			int netHandle[13];
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, netHandle, 13);
			std::string MenuFolderPath = "C:\\Saint\\Players\\";
			if (DoesIniExists((MenuFolderPath + name + ".ini").c_str())) {
				Noti::InsertNotification({ ImGuiToastType_None, 2000, "%s is already saved!", name});
			}
			else {
				Ini* ColorIni = new Ini(MenuFolderPath + name + ".ini");
				ColorIni->WriteString(name, "Info", "Name");
				ColorIni->WriteString(NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]), "Info", "RID");
			}
		}
	};
	inline SavedPlayers m_saved_players;
	class RIDToolkit {
	public:
		
		void join_type(eSessionType session)
		{
			*script_global(2695915).as<int*>() = (session == eSessionType::SC_TV ? 1 : 0); // If SC TV Then Enable Spectator Mode

			if (session == eSessionType::LEAVE_ONLINE)
				*script_global(1574589).at(2).as<int*>() = -1;
			else
				*script_global(1575017).as<int*>() = (int)session;

			*script_global(1574589).as<int*>() = 1;
			fbr::cur()->wait(200ms);
			*script_global(1574589).as<int*>() = 0;
		}

		void join_session(const rage::rlSessionInfo& info)
		{
			join_queue = true;
			g_Session_info = info;
			join_type({ eSessionType::NEW_PUBLIC });
			if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) == 0)
			{
				Noti::InsertNotification({ ImGuiToastType_None, 2000, "Unknown error" });
				join_queue = false;
				
			}
			return;
		}

		void join(uint64_t rid)
		{
			if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) != 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
			{
				Noti::InsertNotification({ ImGuiToastType_None, 2000, "Unknown error" });
				return;
			}

			rage::rlGamerHandle player_handle(rid);
			rage::rlSessionByGamerTaskResult result;
			bool success = false;
			rage::rlTaskStatus state{};

			if (g_GameFunctions->m_start_get_session_by_gamer_handle(0, &player_handle, 1, &result, 1, &success, &state))
			{
				while (state.status == 1)
					fbr::cur()->wait();

				if (state.status == 3 && success)
				{
					join_session(result.m_session_info);
					return;
				}
			}

			Noti::InsertNotification({ ImGuiToastType_None, 2000, "Player is offline." });
		}
	};
	inline RIDToolkit rid_toolkit;
	
	class Skip {
	public:
		
	};
	class WalkStyles {
	public:
		
		const char* get_name[45] = {
			"Ballistic",
			 "Lemar Alley",
			 "Fast Turn/Trash",
			 "Fast Runner",
			 "Garbage Man",
			 "Franklin",
			 "Jimmy",
			 "Michael",
			 "Flee",
			 "Scared",
			 "Sexy",
			 "Lester",
			 "Injured",
			 "Lester (Caneup)",
			 "Bag",
			 "Bond Not Tazered",
			 "Bond Tazered",
			 "Brave",
			 "Casual",
			 "Moderate Drunk",
			 "Moderate Drunk 2",
			 "Moderate Drunk 3",
			 "Slightly Drunk",
			 "Very Drunk",
			 "Fire",
			 "Gangster 1",
			 "Gangster 2",
			 "Gangster 3",
			 "Jog",
			 "Prison Gaurd",
			 "One",
			 "Briefcase",
			 "Janitor",
			 "Slow",
			 "Bucket",
			 "Crouched",
			 "Mop",
			 "Femme",
			 "Femme 2",
			 "Gangster 4",
			 "Gangster 5",
			 "Posh",
			 "Posh 2",
			 "Tough Guy",
			 "Tough Guy 2",
		};
		const char* type[45] = { "ANIM_GROUP_MOVE_BALLISTIC",
				 "ANIM_GROUP_MOVE_LEMAR_ALLEY",
				 "clipset@move@trash_fast_turn",
				 "FEMALE_FAST_RUNNER",
				 "missfbi4prepp1_garbageman",
				 "move_characters@franklin@fire",
				 "move_characters@Jimmy@slow@",
				 "move_characters@michael@fire",
				 "move_f@flee@a",
				 "move_f@scared",
				 "move_f@sexy@a",
				 "move_heist_lester",
				 "move_injured_generic",
				 "move_lester_CaneUp",
				 "move_m@bag",
				 "MOVE_M@BAIL_BOND_NOT_TAZERED",
				 "MOVE_M@BAIL_BOND_TAZERED",
				 "move_m@brave",
				 "move_m@casual@d",
				 "move_m@drunk@moderatedrunk",
				 "MOVE_M@DRUNK@MODERATEDRUNK",
				 "MOVE_M@DRUNK@MODERATEDRUNK_HEAD_UP",
				 "MOVE_M@DRUNK@SLIGHTLYDRUNK",
				 "MOVE_M@DRUNK@VERYDRUNK",
				 "move_m@fire",
				 "move_m@gangster@var_e",
				 "move_m@gangster@var_f",
				 "move_m@gangster@var_i",
				 "move_m@JOG@",
				 "MOVE_M@PRISON_GAURD",
				 "MOVE_P_M_ONE",
				 "MOVE_P_M_ONE_BRIEFCASE",
				 "move_p_m_zero_janitor",
				 "move_p_m_zero_slow",
				 "move_ped_bucket",
				 "move_ped_crouched",
				 "move_ped_mop",
				 "MOVE_M@FEMME@",
				 "MOVE_F@FEMME@",
				 "MOVE_M@GANGSTER@NG",
				 "MOVE_F@GANGSTER@NG",
				 "MOVE_M@POSH@",
				 "MOVE_F@POSH@",
				 "MOVE_M@TOUGH_GUY@",
				 "MOVE_F@TOUGH_GUY@"
		};
		std::size_t size;
		void change(const char* name) {
			
			g_CallbackScript->AddCallback<WalkStyleCallback>(name, [=] {
				PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), name, 2.0f);
				});
		}
		
	};
	inline WalkStyles* walk_style;
	class GetModelInfo {
	public:
		bool width = false;
		bool height = false;
		float widthm = 1.0f;
		float heightm = 1.0f;
		void init() {
			if (width) {
				Memory::set_value<float>({ 0x08, 0x0064 }, widthm);
			}
			if (height) {
				Memory::set_value<float>({ 0x08, 0x88 }, heightm);
			}
		}
	};
	inline GetModelInfo get_model_info;
	class parachute {
	public:
		bool enabled = false;
		void init() {
			Memory::set_value<int>({ 0x8, 0xD10, 0x20, 0x58C }, static_cast<int>(true));
				VEHICLE::VEHICLE_START_PARACHUTING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
			
		}
	};
	inline parachute m_parachute;
	inline int SelectedFriend;
	inline std::string getFriendStateStr(int state, bool joinable) {
		switch (state) {
		case -1: return "~g~[Online]"; break;
		case 1: return "~g~[Online]"; break;
		case 2: return "~b~[Multiplayer]"; break;
		case 3: return joinable ? "~b~[Multiplayer]" : "~m~[Story]"; break;
		default: return "~m~[Offline]";
		}
		return "null";
	}
	class Bits {
	public:
		void clear_bit(int* address, int pos)
		{
			*address &= ~(1 << pos);
		}

		void clear_bits(int* address, int bits)
		{
			*address &= ~(bits);
		}

		bool has_bit_set(int* address, int pos)
		{
			return *address & 1 << pos;
		}

		template<typename T>
		bool has_bits_set(T* address, T bits)
		{
			return (*address & bits) == bits;
		}

		bool has_bits_set(int* address, int bits)
		{
			return (*address & bits) == bits;
		}

		void set_bit(int* address, int pos)
		{
			*address |= 1 << pos;
		}

		void set_bits(int* address, int bits)
		{
			*address |= bits;
		}
	};
	inline Bits m_GetBits;
	inline script_global vehicle_global = script_global(1586468);
	class GetVehicles {
	public:
		bool fix_index(int veh_idx, bool spawn_veh = false)
		{
			bool can_be_fixed = m_GetBits.has_bits_set(vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::DESTROYED | eVehicleFlags::HAS_INSURANCE);

			if (can_be_fixed)
			{
				m_GetBits.clear_bits(vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::DESTROYED | eVehicleFlags::IMPOUNDED | eVehicleFlags::UNK2);

				if (spawn_veh)
				{
					m_GetBits.set_bits(vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::TRIGGER_SPAWN_TOGGLE | eVehicleFlags::SPAWN_AT_MORS_MUTUAL);
				}
			}
			return can_be_fixed;
		}

		int fix_all()
		{
			int fixed_count = 0;

			const int arr_size = *vehicle_global.as<int*>();
			for (int i = 0; i < arr_size; i++)
				if (fix_index(i, true))
					fixed_count++;

			return fixed_count;
		}
	};
	class PersonalVehicle {
	public:
		const char* type[2] = {"Normal", "Spawn Into"};
		std::size_t size;
		void fix_all() {
			GetVehicles get;
			get.fix_all();
		}
		inline Vehicle get()
		{
			script_global mechanic_global = script_global(2793046);
			return *mechanic_global.at(299).as<Vehicle*>();
		}
	};
	inline PersonalVehicle personal_vehicle;
	struct get_model_changer_hash {
		const char* name;
		const char* model;
	};
	class GetClasses {
	public:
		int size = 1;
		std::map<int, get_model_changer_hash> all_models = {
			{0, {"Beach 1", "a_f_m_beach_01"}},
			{0, {"Fortnite", "hey"}}
		};
	};
	enum ModelClass {
		Beach,
		Fat,
		Pedestrain,
		Bodybuilder,
		Rich,
		Special,
		Business,
		Gang,
		Animal,
		Known,
		Prison,
		Construction,
		Story,
		Medical,
		Military,
		Police,
		CIA,
		Althedic,
		Main,
		Casino,
	};
	class modelHandler {
	public:
		modelHandler(std::string model_name, std::string name, ModelClass get_class) {
			m_model = model_name;
			m_name = name;
			m_class = get_class;
		}
	public:
		std::string m_model;
		std::string m_name;
		int m_class = 0;
	};
	class CreatorHandler {
	public:
		CreatorHandler(std::string model_name) {
			m_model = model_name;
			
		}
	public:
		std::string m_model;
	};
	class Creator {
	public:
		bool enabled = false;
		Entity selected_object;
		std::string selected_object_name = "apa_mp_h_yacht_sofa_01";
		std::string selected_buffer;
		std::vector<CreatorHandler> m_Objects = {
			{ "prop_box_wood02a"},
			{ "prop_air_woodsteps"},
			{"apa_mp_h_bed_with_table_02"},
		};
		std::string m_selected = "prop_dog_cage_02";
		Cam creator_cam;
		Object preview;
		bool frozen = false;
		void init() {
			if (enabled) {
				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
				NativeVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

				if (!CAM::DOES_CAM_EXIST(creator_cam)) {
					creator_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", true);
					CAM::SET_CAM_ROT(creator_cam, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
					CAM::SET_CAM_COORD(creator_cam, CAM::GET_GAMEPLAY_CAM_COORD());
				}

				NativeVector3 get_coords;
				if (raycast_with_cam(creator_cam, get_coords)) {
					GRAPHICS::DRAW_MARKER(25, get_coords.x, get_coords.y, get_coords.z + 0.1f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0, 2.0, 255, 0, 0, 255, false, false, 2, false, NULL, NULL, true);
				}
				
				CAM::RENDER_SCRIPT_CAMS(true, true, 700, true, true, true);
				CAM::SET_CAM_ACTIVE(creator_cam, true);
				CAM::SET_CAM_ROT(creator_cam, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);

				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), true);
				HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
				PAD::DISABLE_CONTROL_ACTION(2, 8, true);
				PAD::DISABLE_CONTROL_ACTION(2, 32, true);
				PAD::DISABLE_CONTROL_ACTION(2, 34, true);

				NativeVector3 freecamCoords = CAM::GET_CAM_COORD(creator_cam);
				NativeVector3 cameraDirection = RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0));
				NativeVector3 accelerateCoords = multiply(&cameraDirection, 0.2f);
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 8)) {

					NativeVector3 newCoords = addn(&freecamCoords, &accelerateCoords);
					CAM::SET_CAM_COORD(creator_cam, newCoords);
				}
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 32)) {
					NativeVector3 newCoords = addn(&freecamCoords, &accelerateCoords);
					CAM::SET_CAM_COORD(creator_cam, newCoords);
				}
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 34)) {
					CAM::SET_CAM_ROT(creator_cam, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
				}

				
				if (!g_Render->m_Opened) {
					if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, 18)) {
						NativeVector3 get_coords55;
						if (raycast_with_cam(creator_cam, get_coords55)) {
							AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
							Hash hash = MISC::GET_HASH_KEY(m_selected.c_str());

							Object cage = OBJECT::CREATE_OBJECT_NO_OFFSET(hash, get_coords55.x, get_coords55.y, get_coords55.z, true, false, false);
							if (frozen) {
								ENTITY::FREEZE_ENTITY_POSITION(cage, true);
							}
						}
					}
				}
			}
		}
	};
	inline Creator m_creator;
	
	
	class ModelChanger {
	public:
		std::vector<modelHandler> m_GetModels = {

			{ "a_f_m_beach_01", "Bikini (Female)", ModelClass::Beach },
			{ "a_f_y_beach_01", "Bikini (With Extra Stuff)", ModelClass::Beach },
			{ "a_f_m_bevhills_01", "Beverly Hills", ModelClass::Rich },
			{ "a_f_m_bevhills_02", "Beverly Hills 2", ModelClass::Rich },
			{ "a_f_y_bevhills_01", "Beverly Hills 3", ModelClass::Rich },
			{ "a_f_y_bevhills_02", "Beverly Hills 4", ModelClass::Rich },
			{ "a_f_y_bevhills_03", "Beverly Hills 5", ModelClass::Rich },
			{ "a_f_y_bevhills_04", "Beverly Hills 6", ModelClass::Rich },

			{ "a_f_m_bodybuild_01", "Bikini (Semi-Fat)", ModelClass::Bodybuilder },

			{ "a_f_m_business_02", "Regular Female", ModelClass::Business },

			{ "a_f_m_downtown_01", "Downtown", ModelClass::Pedestrain },
			{ "a_f_m_eastsa_01", "East SA", ModelClass::Pedestrain },
			{ "a_f_m_eastsa_02", "East SA", ModelClass::Pedestrain },
			{ "a_f_m_ktown_01", "KTown", ModelClass::Pedestrain },
			{ "a_f_m_ktown_02", "KTown 2", ModelClass::Pedestrain },
			{ "a_f_m_salton_01", "Salton", ModelClass::Pedestrain },

			{ "a_f_m_fatbla_01", "Typical", ModelClass::Fat },
			{ "a_f_m_fatcult_01", "Cult", ModelClass::Fat },
			{ "a_f_m_fatwhite_01", "White", ModelClass::Fat },
			{ "a_f_m_prolhost_01", "Prolouge Hostage", ModelClass::Known },
			{ "a_f_m_skidrow_01", "Skid Row", ModelClass::Pedestrain },
			{ "a_f_m_soucent_01", "Soucent", ModelClass::Pedestrain },
			{ "a_f_m_soucent_02", "Soucent 2", ModelClass::Pedestrain },
			{ "a_f_o_soucent_01", "Soucent 3", ModelClass::Pedestrain },
			{ "a_f_o_soucent_02", "Soucent 4", ModelClass::Pedestrain },
			{ "a_f_m_soucentmc_01", "Soucent (MC)", ModelClass::Pedestrain },
			{ "a_f_m_tourist_01", "Tourist", ModelClass::Pedestrain },
			{ "a_f_m_tramp_01", "Tramp", ModelClass::Fat },
			{ "a_f_m_trampbeac_01", "Tramp Beach", ModelClass::Beach },
			{ "a_f_o_genstreet_01", "Gen Street", ModelClass::Pedestrain },
			{ "a_f_o_indian_01", "Indian", ModelClass::Special },
			{ "a_f_o_ktown_01", "KTown 3", ModelClass::Pedestrain },
			{ "a_f_o_salton_01", "Salton 2", ModelClass::Pedestrain },
			{ "a_f_y_business_01", "Typical (With Cool Outfit)", ModelClass::Business },
			{ "a_f_y_business_02", "Typical (Interesting Hair)", ModelClass::Business },
			{ "a_f_y_business_03", "Full Black", ModelClass::Business },
			{ "a_f_y_business_04", "White", ModelClass::Business },

			//construction
			{ "s_m_y_construct_01", "Greenish Vest", ModelClass::Construction },
			{ "s_m_y_construct_02", "Orange Vest", ModelClass::Construction },

			//military
			{ "s_m_y_armymech_01", "Mech", ModelClass::Military },
			{ "s_m_y_blackops_01", "Black Ops", ModelClass::Military },
			{ "s_m_y_blackops_02", "Black Ops 2", ModelClass::Military },
			{ "s_m_y_blackops_03", "Black Ops 3", ModelClass::Military },
			{ "s_m_y_marine_01", "Marine", ModelClass::Military },
			{ "s_m_y_marine_02", "Marine (Shirt Off)", ModelClass::Military },
			{ "s_m_y_marine_03", "Marine 2", ModelClass::Military },
			{ "mp_m_exarmy_01", "Ex-Army", ModelClass::Military },

			//police
			{ "s_m_y_cop_01", "Normal (Male)", ModelClass::Police },
			{ "s_f_y_cop_01", "Normal (Female)", ModelClass::Police },
			{ "s_m_y_ranger_01", "Ranger (Male)", ModelClass::Police },
			{ "s_f_y_ranger_01", "Ranger (Female)", ModelClass::Police },
			{ "s_m_y_sheriff_01", "Sheriff (Male)", ModelClass::Police },
			{ "s_f_y_sheriff_01", "Sheriff (Female)", ModelClass::Police },
			{ "s_m_m_snowcop_01", "Snow", ModelClass::Police },
			{ "s_m_y_hwaycop_01", "Highway", ModelClass::Police },
			{ "s_m_y_swat_01", "Swat", ModelClass::Police },
			{ "ig_casey", "Casey", ModelClass::Police },

			//medical
			{ "s_f_y_scrubs_01", "Scrubs (Female)", ModelClass::Medical },
			{ "s_m_y_autopsy_01", "Autopsy", ModelClass::Medical },
			{ "s_m_m_paramedic_01", "Paramedic", ModelClass::Medical },
			{ "s_m_m_doctor_01", "Doctor", ModelClass::Medical },
			{ "u_m_y_corpse_01", "Corpse", ModelClass::Medical },
			{ "u_f_y_corpse_01", "Corpse 2", ModelClass::Medical },
			{ "u_f_y_corpse_02", "Corpse 3", ModelClass::Medical },
			{ "u_f_m_corpse_01", "Corpse 4", ModelClass::Medical },

			//cia
			{ "ig_karen_daniels", "Karen Daniels", ModelClass::CIA },
			{ "ig_josh", "Josh", ModelClass::CIA },
			{ "ig_michelle", "Michelle", ModelClass::CIA },
			{ "s_m_m_fibsec_01", "Secruity", ModelClass::CIA },
			{ "s_m_m_ciasec_01", "Secruity 2", ModelClass::CIA },
			{ "cs_davenorton", "Dave Nortan", ModelClass::CIA },

			//special
			{ "u_m_y_zombie_01", "Zombie", ModelClass::Special },
			{ "u_m_y_rsranger_01", "Space Ranger", ModelClass::Special },
			{ "u_m_y_juggernaut_01", "Doomsday Juggernaut", ModelClass::Special },
			{ "u_m_y_mani", "Mani", ModelClass::Special },
			{ "u_m_y_pogo_01", "Pogo", ModelClass::Special },
			{ "u_m_y_imporage", "Impotent Rage", ModelClass::Special },
			{ "u_m_m_streetart_01", "Street Tart", ModelClass::Special },
			{ "ig_orleans", "Bigfoot", ModelClass::Special },
			{ "ig_johnnyklebitz", "Johhny Klebitz", ModelClass::Special },
			{ "s_m_y_mime", "Mime", ModelClass::Special },
			{ "s_m_y_clown_01", "Clown (Kyro)", ModelClass::Special },
			{ "s_m_m_movspace_01", "Astronaut", ModelClass::Special },
			{ "s_m_m_movalien_01", "Alien", ModelClass::Special },
			{ "mp_m_niko_01", "Niko", ModelClass::Special },
			{ "mp_m_marston_01", "Marston", ModelClass::Special },
			{ "cs_bradcadaver", "Brad Cadaver", ModelClass::Special },
			{ "u_m_m_jesus_01", "Jesus", ModelClass::Special },

			//prison
			{ "csb_rashcosvki", "Rashcovski", ModelClass::Prison },
			{ "u_m_y_prisoner_01", "Inmate", ModelClass::Prison },
			{ "s_m_y_prismuscl_01", "Inmate (No Shirt)", ModelClass::Prison },
			{ "s_m_y_prismuscl_01", "Inmate 2", ModelClass::Prison },

			//main
			{ "mp_m_freemode_01", "Freemode (Male)", ModelClass::Main },
			{ "mp_f_freemode_01", "Freemode (Female)", ModelClass::Main },
			{ "player_zero", "Micheal", ModelClass::Main },
			{ "player_two", "Trevor", ModelClass::Main },
			{ "player_two", "Franklin", ModelClass::Main },

			//casino
			{ "csb_agatha", "Agatha Baker", ModelClass::Casino },
			{ "csb_tomcasino", "Tom", ModelClass::Casino },
			{ "csb_vincent", "Vincent", ModelClass::Casino },
			{ "csb_tonyprince", "Tony Prince", ModelClass::Casino },
			{ "u_f_m_casinocash_01", "Cash (Female)", ModelClass::Casino },
			{ "u_f_m_casinoshop_01", "Shop", ModelClass::Casino },
			{ "s_f_y_casino_01", "Assistant (Female)", ModelClass::Casino },
			{ "s_m_y_casino_01", "Assistant (Male)", ModelClass::Casino },

			//animals

			{ "a_c_boar", "Boar", ModelClass::Animal },
			{ "a_c_cat_01", "Cat", ModelClass::Animal },
			{ "a_c_chickenhawk", "Chickenhawk", ModelClass::Animal },
			{ "a_c_chimp", "Chimp", ModelClass::Animal },
			{ "a_c_chop", "Chop", ModelClass::Animal },
			{ "a_c_cormorant", "Cormorant", ModelClass::Animal },
			{ "a_c_cow", "Cow", ModelClass::Animal },
			{ "a_c_coyote", "Coyote", ModelClass::Animal },
			{ "a_c_crow", "Crow", ModelClass::Animal },
			{ "a_c_deer", "Deer", ModelClass::Animal },
			{ "a_c_dolphin", "Dolphin", ModelClass::Animal },
			{ "a_c_fish", "Fish", ModelClass::Animal },
			{ "a_c_hen", "Hen", ModelClass::Animal },
			{ "a_c_humpback", "Humpback", ModelClass::Animal },
			{ "a_c_husky", "Husky", ModelClass::Animal },
			{ "a_c_mtlion", "Mountain Lion", ModelClass::Animal },
			{ "a_c_killerwhale", "Killerwhale", ModelClass::Animal },
			{ "a_c_panther", "Panther", ModelClass::Animal },
			{ "a_c_pig", "Pig", ModelClass::Animal },
			{ "a_c_pigeon", "Pigeon", ModelClass::Animal },
			{ "a_c_poodle", "Poodle", ModelClass::Animal },
			{ "a_c_pug", "Pug", ModelClass::Animal },
			{ "a_c_rabbit_01", "Rabbit", ModelClass::Animal },
			{ "a_c_rabbit_02", "Rabbit (Large)", ModelClass::Animal },
			{ "a_c_rat", "Rat", ModelClass::Animal },
			{ "a_c_retriever", "Retriever", ModelClass::Animal },
			{ "a_c_rhesus", "Rhesus", ModelClass::Animal },
			{ "a_c_rottweiler", "Rottweiler", ModelClass::Animal },
			{ "a_c_seagull", "Seagull", ModelClass::Animal },
			{ "a_c_sharkhammer", "Hammerhead Shark", ModelClass::Animal },
			{ "a_c_sharktiger", "Tiger Shark", ModelClass::Animal },
			{ "a_c_shepherd", "Shepherd", ModelClass::Animal },
			{ "a_c_stingray", "Stringray", ModelClass::Animal },
			{ "a_c_westy", "Westy", ModelClass::Animal },
		};
		GetClasses get_classes;
		int selected_class = 0;
		int size = 19;
		const char* get_class_name[20] = {"Beach", "Fat", "Pedestrain", "Bodybuilder", "Rich", "Special", "Business", "Gang", "Animal", "Known", "Prison", "Construction", "Story", "Medical", "Military/Army", "Police", "CIA/FIB/IAA", "Althedic", 
		"Main Characters", "Casino"
		};
		
		
		bool change(const Hash hash)
		{
			g_FiberPool.queue([=] {
				for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
				{
					STREAMING::REQUEST_MODEL(hash);
					fbr::cur()->wait();
				}
				if (!STREAMING::HAS_MODEL_LOADED(hash))
				{
					return false;
				}
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), hash);
				Ped ped = PLAYER::PLAYER_PED_ID();
				fbr::cur()->wait();
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				for (int i = 0; i < 12; i++)
				{
					PED::SET_PED_COMPONENT_VARIATION(ped, i, PED::GET_PED_DRAWABLE_VARIATION(ped, i), PED::GET_PED_TEXTURE_VARIATION(ped, i), PED::GET_PED_PALETTE_VARIATION(ped, i));
				}
			});
			return true;
		}

		
	};
	inline ModelChanger m_ModelChanger;
	class Recovery {
	public:
		const char* get_char_name[2] = { "First", "Second"};
		std::size_t selected = 0;
	};
	inline Recovery g_RecoveryManager;
	class boolOption {
	public:
		boolOption(const char* m_name, const char* m_description, bool m_buffer) {
			name = m_name;
			description = m_description;
			buffer = m_buffer;
		}
	public:
		const char* name;
		const char* description;
		bool buffer;
	};
	class intOption {
	public:
		intOption(const char* m_name, const char* m_description, int m_min, int m_max, int m_step) {
			name = m_name;
			description = m_description;
			min = m_min;
			max = m_max;
			step = m_step;
		}
	public:
		const char* name;
		const char* description;
		int min;
		int max;
		int step;
	};
	inline boolOption auto_repair = { "Auto-Repair", "Repairs your vehicle.", features.auto_repair };
	inline intOption rainbow_delay = { "Example", "This is an example.", 0, 5000, 50 };
	class p_cha {
	public:
		std::string text;
		rage::rlGamerInfo* get_selected_net_data() const
		{
			return g_GameVariables->m_net_game_player(g_SelectedPlayer) == nullptr ? nullptr : g_GameVariables->m_net_game_player(g_SelectedPlayer)->get_net_data();
		}
		const char* get_name() const
		{
			return g_GameVariables->m_net_game_player(g_SelectedPlayer) == nullptr ? "" : g_GameVariables->m_net_game_player(g_SelectedPlayer)->get_name();
		}
		void add_message(const char* msg, const char* player_name, bool is_team)
		{
			if (Hooks::send_chat_message(*g_GameFunctions->m_send_chat_ptr, get_selected_net_data(), msg, false)) {
				g_GameFunctions->m_send_chat_ptr, get_selected_net_data(), msg, false;
				int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MULTIPLAYER_CHAT");
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "ADD_MESSAGE");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name); // player name
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(msg); // content
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(is_team ? "MP_CHAT_TEAM" : "MP_CHAT_ALL")); // scope
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(false); // teamOnly
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // eHudColour
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SET_FOCUS");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1); // VISIBLE_STATE_DEFAULT
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // scopeType (unused)
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // scope (unused)
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name); // player
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // eHudColour
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, 255, 255, 255, 255, 0);
			}

		}
		void send_once() {
			static int timer;
			if (timer == 0 || (int)(GetTickCount64() - timer) > 500) {
				if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
					add_message(text.c_str(), get_name(), false);
				}
				timer = GetTickCount64();
			}
		}
	};
	inline p_cha p_chat;
	inline std::string Bufferfrrrr;
	inline int boost_power = 150;
	class rainb3ow_ui {
	public:
		bool main = false;
		void init() {
			if (main) {
				if (g_Render->m_HeaderBackgroundColor.r > 0 && g_Render->m_HeaderBackgroundColor.b == 0) {
					g_Render->m_HeaderBackgroundColor.r--;
					g_Render->m_HeaderBackgroundColor.g++;
				}
				if (g_Render->m_HeaderBackgroundColor.g > 0 && g_Render->m_HeaderBackgroundColor.r == 0) {
					g_Render->m_HeaderBackgroundColor.g--;
					g_Render->m_HeaderBackgroundColor.b++;
				}
				if (g_Render->m_HeaderBackgroundColor.b > 0 && g_Render->m_HeaderBackgroundColor.g == 0) {
					g_Render->m_HeaderBackgroundColor.r++;
					g_Render->m_HeaderBackgroundColor.b--;
				}
				
			}
		}
	};
	inline rainb3ow_ui rainbow_ui;
	class ESP {
	public:
		bool skeleton = false;
		void draw_bone(NativeVector3 first, NativeVector3 second) {
			GRAPHICS::DRAW_LINE(first.x, first.y, first.z, second.x, second.y, second.z, 255, 255, 255, 255);
		}
		void init() {
			if (skeleton) {
				NativeVector3 RightFoot = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_R_Foot, 0, 0, 0);
				NativeVector3 RightKnee = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), MH_R_Knee, 0, 0, 0);
				NativeVector3 RightThigh = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_R_Thigh, 0, 0, 0);
				NativeVector3 LeftFoot = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_L_Foot, 0, 0, 0);
				NativeVector3 LeftKnee = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), MH_L_Knee, 0, 0, 0);
				NativeVector3 LeftThigh = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_L_Thigh, 0, 0, 0);
				NativeVector3 Center = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_ROOT, 0, 0, 0);
				NativeVector3 Neck = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_Neck_1, 0, 0, 0);
				NativeVector3 Head = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_Head, 0, 0, 0);
				NativeVector3 ForearmR = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_R_UpperArm, 0, 0, 0);
				NativeVector3 Forearm2 = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_R_Forearm, 0, 0, 0);
				NativeVector3 HandR = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_R_Hand, 0, 0, 0);

				NativeVector3 ForearmL = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_L_UpperArm, 0, 0, 0);
				NativeVector3 Forearm2L = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_L_Forearm, 0, 0, 0);
				NativeVector3 HandL = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_L_Hand, 0, 0, 0);

				NativeVector3 RightToe = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_R_Toe0, 0, 0, 0);
				NativeVector3 LeftToe = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_L_Toe0, 0, 0, 0);

				
				GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(8);
				GRAPHICS::DRAW_LINE(RightFoot.x, RightFoot.y, RightFoot.z, RightKnee.x, RightKnee.y, RightKnee.z, 255, 255, 255, 255);
				GRAPHICS::DRAW_LINE(RightKnee.x, RightKnee.y, RightKnee.z, RightThigh.x, RightThigh.y, RightThigh.z, 255, 255, 255, 255);

				GRAPHICS::DRAW_LINE(RightThigh.x, RightThigh.y, RightThigh.z, Center.x, Center.y, Center.z, 255, 255, 255, 255);
				GRAPHICS::DRAW_LINE(LeftFoot.x, LeftFoot.y, LeftFoot.z, LeftKnee.x, LeftKnee.y, LeftKnee.z, 255, 255, 255, 255);

				GRAPHICS::DRAW_LINE(LeftKnee.x, LeftKnee.y, LeftKnee.z, LeftThigh.x, LeftThigh.y, LeftThigh.z, 255, 255, 255, 255);
				GRAPHICS::DRAW_LINE(LeftThigh.x, LeftThigh.y, LeftThigh.z, Center.x, Center.y, Center.z, 255, 255, 255, 255);

				GRAPHICS::DRAW_LINE(Center.x, Center.y, Center.z, Neck.x, Neck.y, Neck.z, 255, 255, 255, 255);
				GRAPHICS::DRAW_LINE(Neck.x, Neck.y, Neck.z, Head.x, Head.y, Head.z, 255, 255, 255, 255);

				GRAPHICS::DRAW_LINE(Neck.x, Neck.y, Neck.z, ForearmR.x, ForearmR.y, ForearmR.z, 255, 255, 255, 255);
				GRAPHICS::DRAW_LINE(ForearmR.x, ForearmR.y, ForearmR.z, Forearm2.x, Forearm2.y, Forearm2.z, 255, 255, 255, 255);

				GRAPHICS::DRAW_LINE(Forearm2.x, Forearm2.y, Forearm2.z, HandR.x, HandR.y, HandR.z, 255, 255, 255, 255);

				GRAPHICS::DRAW_LINE(Neck.x, Neck.y, Neck.z, ForearmL.x, ForearmL.y, ForearmL.z, 255, 255, 255, 255);
				GRAPHICS::DRAW_LINE(ForearmL.x, ForearmL.y, ForearmL.z, Forearm2L.x, Forearm2L.y, Forearm2L.z, 255, 255, 255, 255);

				GRAPHICS::DRAW_LINE(Forearm2L.x, Forearm2L.y, Forearm2L.z, HandL.x, HandL.y, HandL.z, 255, 255, 255, 255);


			}
		}
	};
	inline ESP esp;
	namespace am_criminal_damage
	{
		constexpr static auto broadcast_idx = 110;
		constexpr static auto score_idx = 105;
	}
	inline GtaThread* find_script_thread(rage::joaat_t hash)
	{
		for (auto thread : *g_GameFunctions->m_script_threads)
		{
			if (thread && thread->m_context.m_thread_id && thread->m_handler && thread->m_script_hash == hash)
			{
				return thread;
			}
		}

		return nullptr;
	}
	inline bool force_host(rage::joaat_t hash)
	{
		uint32_t self = PLAYER::PLAYER_ID();
		if (auto launcher = find_script_thread(hash); launcher && launcher->m_net_component)
		{
			for (int i = 0; !((CGameScriptHandlerNetComponent*)launcher->m_net_component)->is_local_player_host(); i++)
			{
				if (i > 200)
					return false;

				((CGameScriptHandlerNetComponent*)launcher->m_net_component)
					->send_host_migration_event(g_GameVariables->m_net_game_player(self));
				fbr::cur()->wait(10ms);

				if (!launcher->m_stack || !launcher->m_net_component)
					return false;
			}
		}

		return true;
	}
	
	class SpectateOptions {
	public:
		const char* type[2] = { "Stop", "Random" };
		std::size_t pos;
		int roll = 0;
		void stop() {
			features.spectate = false;
			
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(roll));
			HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(roll));
			STREAMING::SET_FOCUS_ENTITY(PLAYER::PLAYER_PED_ID());
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			
		}
		void random() {
			features.spectate = false;
			roll = MISC::GET_RANDOM_INT_IN_RANGE(0, 32);
			if (roll == PLAYER::PLAYER_ID()) {
				roll = MISC::GET_RANDOM_INT_IN_RANGE(0, 32);
				if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(roll)) {
					ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);

					NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, ped);
					STREAMING::SET_FOCUS_ENTITY(ped);
					HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, ped);
					if (PED::IS_PED_DEAD_OR_DYING(PLAYER::PLAYER_PED_ID(), 1))
					{
						NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::PLAYER_PED_ID());
					}
				}
			}
			if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(roll)) {
				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);

				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, ped);
				STREAMING::SET_FOCUS_ENTITY(ped);
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, ped);
				if (PED::IS_PED_DEAD_OR_DYING(PLAYER::PLAYER_PED_ID(), 1))
				{
					NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::PLAYER_PED_ID());
				}
			}
		}
	};
	inline SpectateOptions spectateo;
	class TimeEditor {
	public:
		const char* type[3] = { "Seconds", "Minutes", "Hours"};
		std::size_t pos;
		int second = 0;
		int min = 0;
		int hour = 0;
		bool sync = false;
		void add(int min, int second, int hour) {
			CLOCK::ADD_TO_CLOCK_TIME(hour, min, second);
		}
		void init() {
			if (sync) {
				static Timer syncTimer(0ms);
				syncTimer.SetDelay(std::chrono::seconds(1));
				if (syncTimer.Update())
				{
					CLOCK::PAUSE_CLOCK(sync);
					std::int32_t Time[6];
					CLOCK::GET_LOCAL_TIME(&Time[0], &Time[1], &Time[2], &Time[3], &Time[4], &Time[5]);
					NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(Time[3], Time[4], Time[5]);
					CLOCK::SET_CLOCK_TIME(Time[3], Time[4], Time[5]);
				}
			}
		}
	};
	inline uintptr_t g_base_address = (uintptr_t)GetModuleHandle(NULL);
	inline uintptr_t scan_address(uintptr_t ptr, std::vector<unsigned int> offsets)
	{
		uintptr_t addr = ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];
		}
		return addr;
	}
	inline TimeEditor time_gta;
	class East {
	public:
		bool changed = false;
		int r = 0;
		int g = 0;
		int b = 0;
		float brightness = 1.0;
	};
	class West {
	public:
		bool changed = false;
		int r = 0;
		int g = 0;
		int b = 0;
		float brightness = 1.0;
	};
	class SouthNorth {
	public:
		bool changed = false;
		int r = 0;
		int g = 0;
		int b = 0;
		float brightness = 1.0;
	};
	class Cloud {
	public:
		bool changed = false;
		int r = 0;
		int g = 0;
		int b = 0;
		float brightness = 1.0;
	};
	class SkyData {
	public:
		East east;
		West west;
		SouthNorth southnorth;
		Cloud cloud;
		void change_effect() {
			if (east.changed) {
				uintptr_t east_red = scan_address(g_base_address + 0x26CFAB0, {});
				uintptr_t east_green = scan_address(g_base_address + 0x26CFAB4, {});
				uintptr_t east_blue = scan_address(g_base_address + 0x26CFAB8, {});

				*(float*)east_red = (east.r / 255.f) * east.brightness;
				*(float*)east_green = (east.g / 255.f) * east.brightness;
				*(float*)east_blue = (east.b / 255.f) * east.brightness;
			}
			if (west.changed) {
				uintptr_t west_red = scan_address(g_base_address + 0x26CFAE0, {});
				uintptr_t west_green = scan_address(g_base_address + 0x26CFAE4, {});
				uintptr_t west_blue = scan_address(g_base_address + 0x26CFAE8, {});

				*(float*)west_red = (west.r / 255.f) * west.brightness;
				*(float*)west_green = (west.g / 255.f) * west.brightness;
				*(float*)west_blue = (west.b / 255.f) * west.brightness;
			}
			if (southnorth.changed) {
				uintptr_t west_red = scan_address(g_base_address + 0x26CFB10, {});
				uintptr_t west_green = scan_address(g_base_address + 0x26CFB14, {});
				uintptr_t west_blue = scan_address(g_base_address + 0x26CFB18, {});

				*(float*)west_red = (southnorth.r / 255.f) * southnorth.brightness;
				*(float*)west_green = (southnorth.g / 255.f) * southnorth.brightness;
				*(float*)west_blue = (southnorth.b / 255.f) * southnorth.brightness;
			}
			if (cloud.changed) {
				uintptr_t west_red = scan_address(g_base_address + 0x26CFE10, {});
				uintptr_t west_green = scan_address(g_base_address + 0x26CFE14, {});
				uintptr_t west_blue = scan_address(g_base_address + 0x26CFE18, {});

				*(float*)west_red = (cloud.r / 255.f) * cloud.brightness;
				*(float*)west_green = (cloud.g / 255.f) * cloud.brightness;
				*(float*)west_blue = (cloud.b / 255.f) * cloud.brightness;

				

				
			}
		}
	};
	inline SkyData sky_data;
	class Autostart {
	public:
		bool enabled = false;
		int max;
		void init() {
			if (enabled) {
				if (NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS() < max) {
					if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
						session.join(eSessionType::JOIN_PUBLIC);
					}
				}
			}
		}
	};
	inline Autostart autostart;
	inline int max_players = 0;
	inline int max_spectators = 0;
	class ParachuteSelf {
	public:
		const char* types[15] = {"None", "Rainbow", "Red", "Seaside Stripes", "Widow Maker", "Patriot", "Blue", "Black", "Hornet", "Air Focce", "Desert", "Shadow", "High Altitude", "Airbone", "Sunrise"};
		std::size_t pos;
		bool give_when_in_plane = false;
		bool use_reservered = false;
		int r;
		int g;
		int b;
		void init() {
			if (use_reservered) {
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 363, true);
			}
			if (give_when_in_plane) {
				PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(PLAYER::PLAYER_PED_ID(), true);
			}
		}
		void set_color(int r, int g, int b) {
			PLAYER::SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(PLAYER::PLAYER_PED_ID(), r, g, b);
		}
		void set_tint(int id) {
			PLAYER::SET_PLAYER_PARACHUTE_TINT_INDEX(PLAYER::PLAYER_PED_ID(), id);
		}
	};
	inline ParachuteSelf parachutes;
	class GrappleHook {
	public:
		bool IsPedShooting(Ped ped)
		{
			NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(ped, true);
			return PED::IS_PED_SHOOTING_IN_AREA(ped, Coords.x, Coords.y, Coords.z, Coords.x, Coords.y, Coords.z, true, true);
		}
		bool activated = false;
		bool enabled = false;
		float speed = 3.0f;
		NativeVector3 coords;
		void init() {
			if (enabled) {
				if (IsPedShooting(PLAYER::PLAYER_PED_ID()))
				{
					NativeVector3 hitCoords;
					if (raycast(hitCoords)) {
						auto BulletCoord = hitCoords;
						coords = { BulletCoord.x, BulletCoord.y, BulletCoord.z };
						activated = true;
						
					}
				}

				if (activated)
				{
					auto Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
					auto Distance = SYSTEM::VDIST(coords.x, coords.y, coords.z, Coords.x, Coords.y, Coords.z);
					if (Distance < 3.0f)
					{
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
						TASK::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID());
						activated = false;
					}
					else
					{
						NativeVector3 Velocity;
						Velocity.x = (coords.x - Coords.x) * speed;
						Velocity.y = (coords.y - Coords.y) * speed;
						Velocity.z = (coords.z - Coords.z) * speed;
						TASK::TASK_SKY_DIVE(PLAYER::PLAYER_PED_ID(), 0);
						ENTITY::SET_ENTITY_VELOCITY(PLAYER::PLAYER_PED_ID(), Velocity.x, Velocity.y, Velocity.z);
					}
				}
			}
		}
	};
	inline GrappleHook ghook;
	class MiniMap {
	public:
		bool hide_fow = false;
		bool force_exterior = false;
		int zoom = 1;
		void init() {
			if (force_exterior) {
				HUD::SET_RADAR_AS_EXTERIOR_THIS_FRAME();
			}
			if (hide_fow) {
				HUD::SET_MINIMAP_HIDE_FOW(true);
			}
		}
	};
	inline MiniMap minimap;
	class Ocean {
	public:
		const char* type[3] = { "Normal", "Smooth", "Bubbly" };
		std::size_t pos;
		float intensity;
	};
	inline Ocean ocean;
	class BypassWeaponRestrictions {
	public:
		
	};
	inline BypassWeaponRestrictions bypass_weapon;
	inline bool freeze_time = false;
	class Phone {
	public:
		const char* type[4] = { "Michael", "Trevor", "Franklin", "Prologue" };
		std::size_t pos;
		bool disable = false;
		float scale = 500.0f;
		bool scaler = false;
		int x;
		int y;
		int z;
		int rotx;
		int roty;
		int rotz;
		void init() {
			if (scaler) {
				MOBILE::SET_MOBILE_PHONE_SCALE(scale);
			}
			if (disable) {
				MOBILE::DESTROY_MOBILE_PHONE();
			}
		}
	};
	inline Phone phone;
	class Yacht {
	public:
		void change_name(const char* name) {
			script_global globalplayer_bd(2657589);
			auto& stats3 = globalplayer_bd.as<GlobalPlayerBD*>()->Entries[PLAYER::PLAYER_ID()];
		}
	};
	inline void fade(int r, int g, int b)
	{
		if (r > 0 && b == 0) {
			r--;
			g++;
		}
		if (g > 0 && r == 0) {
			g--;
			b++;
		}
		if (b > 0 && g == 0) {
			r++;
			b--;
		}
	}
	inline bool IsEmpty(NativeVector3 vector)
	{
		if (vector.x == 0.f && vector.y == 0.f && vector.z == 0.f)
			return true;
		return false;
	}
	class Paint {
	public:
		bool enabled = false;
		bool rainbow = false;
		int r;
		int g;
		int b;
		float range = 0.25f;
		float brightness = 250.0f;
		bool shadow = false;
		float shadow_value = 5.0f;
		void init() {
			if (enabled) {
				if (rainbow) {
					if (r > 0 && b == 0) {
						r--;
						g++;
					}
					if (g > 0 && r == 0) {
						g--;
						b++;
					}
					if (b > 0 && g == 0) {
						r++;
						b--;
					}
				}
				static std::vector<NativeVector3> a;
				NativeVector3 b2;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &b2));
				{
					a.push_back(b2);
				}
				for (auto pos : a)
				{
					if (shadow) {
						GRAPHICS::DRAW_LIGHT_WITH_RANGEEX(pos.x, pos.y, pos.z, r, g, b, range, brightness, shadow_value);
					}
					else {
						GRAPHICS::DRAW_LIGHT_WITH_RANGE(pos.x, pos.y, pos.z, r, g, b, range, brightness);
						
					}

				}
			}
		}
	};
	inline Paint paint;
	class ForgeModel {
	public:
		int selected_class = 0;
		void change(Hash hash) {
			if ((*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_model_info->m_hash) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_vehicle->m_model_info->m_hash = hash;
			}
		}
	};
	inline ForgeModel forge_model;
	
	class BulletChanger {
	public:
		std::size_t weapon_pos = 0;
		bool enabled = false;
		NativeVector3 get_coords_in_front_of_cam(std::float_t distance) {
			NativeVector3 pos = CAM::GET_GAMEPLAY_CAM_COORD();
			NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(NULL);
			NativeVector3 dir = RotationToDirection(rot);
			NativeVector3 dist = multiply(&dir, distance);
			return addn(&pos, &dist);
		}
		float velocity = 100.f;
		bool Audible = true;
		bool Invisible = false;
		void init() {
			if (enabled) {
				NativeVector3 aim = get_coords_in_front_of_cam(500.0f);
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					NativeVector3 hitCoords;
					if (raycast(hitCoords)) {
						std::int32_t hash = all_weapons.hash[weapon_pos];
						WEAPON::REQUEST_WEAPON_ASSET(hash, 31, 0);
						g_FiberPool.queue([=] {
							while (!WEAPON::HAS_WEAPON_ASSET_LOADED(hash))
								fbr::cur()->wait();
							});

						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(hitCoords.x, hitCoords.y, hitCoords.z, aim.x, aim.y, aim.z, 250, FALSE, hash, PLAYER::PLAYER_PED_ID(), Invisible, velocity, 100.0f);
					}
				}
			}
		}
	};
	inline int bike_lean = 0;
	inline int bike_lean2 = 0;
	inline BulletChanger bullet_changer;
	class RocketBoost {
	public:
		const char* action[2] = { "View", "Spawn" };
		std::size_t pos;
		bool always_active;
		float percentage;
		float refill_time;
		void init() {
			if (always_active) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				VEHICLE::SET_ROCKET_BOOST_ACTIVE(veh, true);
			}
		}
	};
	inline RocketBoost rocket_boost;
	class Doors {
	public:
		const char* action[3] = { "Open", "Close", "Delete"};
		std::size_t pos;
	};
	inline Doors doors;
	class Cargobob {
	public:
		bool magnet = false;
		float strength;
		float eraidus;
		float falloff;
		void init() {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			if (magnet) {
				VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(veh, true);
			}
		}
	};
	inline Cargobob cargobob;
	class jforce {
	public:
		bool increase = false;
		const char* action[2] = { "View", "Spawn" };
		std::size_t pos;
		void init() {
			if (increase) {
				VEHICLE::SET_USE_HIGHER_CAR_JUMP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
			}
		}
	};
	inline jforce jump_force;
	inline void FeatureInitalize() {
		jump_force.init();
		cargobob.init();
		rocket_boost.init();
		bullet_changer.init();
		paint.init();
		phone.init();
		time_gta.init();
		CLOCK::PAUSE_CLOCK(freeze_time);
		minimap.init();
		ghook.init();
		parachutes.init();
		autostart.init();
		sky_data.change_effect();
		weather.init2();
		esp.init();
		rainbow_ui.init();
		get_model_info.init();
	
		if (mark_as_Saint) {
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 109, true);

		}
		
		if (protections.Entities.cage) {
			static int timer;
			if ((GetTickCount() - timer) > 200) {

				Ped playerPed = PLAYER::PLAYER_PED_ID();
				NativeVector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
				const char* cages[52] = { "bkr_prop_cashtrolley_01a", "p_cablecar_s_door_r", "p_cablecar_s_door_l", "p_cablecar_s_door_l" ,"p_cablecar_s", "prop_rub_cage01a", "prop_gold_cont_01", "prop_gold_cont_01b",
					"prop_dog_cage_01", "prop_dog_cage_02", "stt_prop_stunt_tube_l", "stt_prop_stunt_tube_crn2", "stt_prop_stunt_tube_crn", "stt_prop_stunt_tube_crn2", "stt_prop_stunt_tube_crn_15d",
					"stt_prop_stunt_tube_crn_30d", "stt_prop_stunt_tube_crn_5d", "stt_prop_stunt_tube_cross", "stt_prop_stunt_tube_end", "stt_prop_stunt_tube_xs", "stt_prop_stunt_tube_xxs", "stt_prop_stunt_tube_speeda",
					"stt_prop_stunt_tube_qg", "stt_prop_stunt_tube_s", "stt_prop_stunt_tube_m", "stt_prop_stunt_tube_l", "stt_prop_stunt_tube_jmp2", "stt_prop_stunt_tube_jmp", "stt_prop_stunt_tube_hg",
					"stt_prop_stunt_tube_gap_03", "stt_prop_stunt_tube_gap_02", "stt_prop_stunt_tube_gap_01", "stt_prop_stunt_tube_fork", "stt_prop_stunt_tube_fn_05", "stt_prop_stunt_tube_fn_04",
					"stt_prop_stunt_tube_fn_03", "stt_prop_stunt_tube_fn_02", "stt_prop_stunt_tube_fn_01", "stt_prop_stunt_tube_ent", "bkr_prop_biker_tube_gap_02", "bkr_prop_biker_tube_gap_01",
					"bkr_prop_biker_tube_xs", "bkr_prop_biker_tube_s", "bkr_prop_biker_tube_m", "bkr_prop_biker_tube_l", "bkr_prop_biker_tube_gap_03", "prop_fnclink_05crnr1", "prop_rub_cage01a", "prop_fnclink_05crnr1", "prop_fnclink_02n", "prop_fnclink_04g", "prop_fnclink_09b" };

				const char* cage_name[52] = { "Trolly", "Cablecar Door", "Cablecar Door 2", "Cablecar Door 3" ,"Cablecar", "Stunt Tube", "Normal", "Normal 2", "Dog Cage", "Dog Cage 2", "Stunt Tube (L)",
									"Stunt Tube (Crn)", "Stunt Tube (Crn 2)", "Stunt Tube (Crn 3)", "Stunt Tube (15D)", "Stunt Tube (30D)", "Stunt Tube (5D)", "Stunt Tube (Cross)", "Stunt Tube (End)", "Stunt Tube (XS)",
									"Stunt Tube (XXS)", "Stunt Tube (Speed)", "Stunt Tube (qg)", "Stunt Tube (S)", "Stunt Tube (M)", "Stunt Tube (L)", "Stunt Tube (Jump)", "Stunt Tube (Jump 2)", "Stunt Tube (HG)", "Stunt Tube (Gap)",
									"Stunt Tube (Gap 2)", "Stunt Tube (Gap 3)", "Stunt Tube (Fork)", "Stunt Tube (FN5)", "Stunt Tube (FN4)", "Stunt Tube (FN3)", "Stunt Tube (FN2)", "Stunt Tube (FN1)", "Stunt Tube (Ent)",
									"Stunt Tube (Gap 4)", "Stunt Tube (Gap 5)", "Stunt Tube (Biker XS)", "Stunt Tube (Biker S)", "Stunt Tube (Biker M)", "Stunt Tube (Biker L)", "Stunt Tube (Gap 6)", "Stunt Tube (Clink)", "Rub", "Fence 1", "Fence Part 2", "Fence Part 3", "Fence Part 4" };

				for (int i = 0; i < 47; i++)
				{
					Object cage = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 15.0f, MISC::GET_HASH_KEY(cages[i]), 0, 0, 1);
					if (ENTITY::DOES_ENTITY_EXIST(cage))
					{
						if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
						{
							ENTITY::SET_ENTITY_COLLISION(cage, false, true);
							ENTITY::SET_ENTITY_ALPHA(cage, 0, true);
							ENTITY::SET_ENTITY_VISIBLE(cage, false, false);
							NativeVector3 objcoords = ENTITY::GET_ENTITY_COORDS(cage, false);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(MISC::GET_HASH_KEY(cages[i]));
							control(cage);
							ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&cage);
							ENTITY::DELETE_ENTITY(&cage);
							Noti::InsertNotification({ ImGuiToastType_None, 2000, "Deleted cage, type: '%s'", cage_name[i]});
							MISC::CLEAR_AREA(objcoords.x, objcoords.y, objcoords.z, 15.0f, 0, 0, 0, 0);
						}
					}
				}
				timer = GetTickCount();
			}
		
		}
		m_creator.init();
		g_HandTrails.init();
		m_shotgun.init();
		m_fx.init();
		m_impacts.init();
		m_nearby.m_traffic.init();
		m_nearby.m_peds.init();
		m_disables.init();
		m_entity_shooter.init();
		m_frame_flags.init();
		m_vehicle_ramps.init();
		flag_creator.init();
		invisible.init();
		no_clip.init();
		acceleration.init();
		hornboost.init();
		features.init();
		superjump.init();
		explosiveAmmo.init();
		rapid_fire.init();
		negitiveTorque.init();
		drops.init();
		Fake_drops.init();
		antiCheat.init();
		multipliers.init();
		speedo.init();
		airstrike.init();
		triggerbot.init();
		text_spam.init();
		max_loop.init();
		owned_explosion.init();
		m_vehicle.bypass_max_speed.init();
		m_fov.init();
		blink.init();
		aimbot.init();
		g_players.get_selected.init();
		m_radar.init();
		m_teleport.init();
		changeVehicleColor.init();
		chat.init();
		team.init();
		wanted_lev.init();
		all_players.m_explode.init();
		all_players.init();
		gravity.init();
		m_hotkeys.init();
		if (NoPlaneTurbulance) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			VEHICLE::SET_PLANE_TURBULENCE_MULTIPLIER(veh, 0.0f);
		}
		if (!NoPlaneTurbulance) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			VEHICLE::SET_PLANE_TURBULENCE_MULTIPLIER(veh, 0.5f);
		}
		if (godmode) {
			uint32_t last_bits = 0;
			uint32_t proof_mask = 0;
			proof_mask |= static_cast<int>(1 << 8);
			uint32_t bits = proof_mask;
			uint32_t changed_bits = bits ^ last_bits;
			uint32_t changed_or_enabled_bits = bits | changed_bits;

			if (changed_or_enabled_bits)
			{
				uint32_t unchanged_bits = (*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits & ~changed_or_enabled_bits;
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits = unchanged_bits | bits;
				last_bits = bits;

			}
		}

		if (neverWantedBool)
		{
			PLAYER::SET_MAX_WANTED_LEVEL(0);
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, true);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), true);
		}
	}

}
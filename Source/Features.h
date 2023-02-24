#pragma once
#include "Natives.hpp"
#include "FiberHelper.hpp"
#include <GTAV-Classes/ped/CPed.hpp>
#include "Math.h"
namespace Arctic {
	
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
	class NoClip {
	public:
		bool enabled = false;
		bool WorkForVehicles = true;
		bool StopAfterNoInput = true;
		bool SetRotation = false;
		bool DisableCollision = true;
		float speed = 2.5f;
		const char* FlyType[2]
		{
			"T-Pose", "None"
		};

		std::size_t FlyInt = 0;
		void init() {
			if (enabled) {
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					static bool turnoff = true;
					if (turnoff)
					{
						ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), 255, false);
						turnoff = false;
					}

					NativeVector3 coords4 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
					NativeVector3 coords5 = CAM::GET_GAMEPLAY_CAM_COORD();
					auto ped = PLAYER::PLAYER_PED_ID();
					auto startDist = std::distance(&coords5, &coords4);
					auto pos = ENTITY::GET_ENTITY_COORDS(ped, false);
					if (FlyInt == 0) {
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, false, false, false);
					}
					if (FlyInt == 1) {
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, true, true, true);
					}
					NativeVector3 meow2 = CAM::GET_GAMEPLAY_CAM_ROT(0);
					NativeVector3 meow = rot_to_direction(&meow2);
					NativeVector3 coords6 = multiply(&meow, speed);


					if (GetAsyncKeyState(0x57) || PAD::IS_CONTROL_PRESSED(2, 32))
					{
						NativeVector3 pos = addn(&coords4, &coords6);
						if (FlyInt == 0) {
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), pos.x, pos.y, pos.z, false, false, false);
						}
						if (FlyInt == 1) {
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
						if (PAD::IS_CONTROL_PRESSED(2, 32))
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
		const char* Weapon[89]
		{ "Antique Cavalry Dagger", "Baseball Bat", "Broken Bottle", "Crowbar", "Unarmed", "Flashlight", "Golf Club", "Hammer", "Hatchet", "Brass Knucles", "Knife", "Machete", "Switchblade", "Nightstick", "Pipe Wrench",
			"Battle Axe", "Pool Cue", "Stone Hatchet", "Pistol", "Pistol Mk II", "Combat Pistol", "AP Pistol", "Stun Gun", "Pistol .50", "SNS Pistol", "SNS Pistol Mk II", "Heavy Pistol", "Vintage Pistol", "Flare Gun", "Marksman Pistol",
			"Heavy Revolver", "Heavy Revolver Mk II", "Double Action Revolver", "Up-n-Atomizer", "Ceramic Pistol", "Navy Revolver", "Perico Pistol", "Stun Gun",
			"Micro SMG", "SMG", "SMG Mk II", "Assault SMG", "Combat PDW", "Machine Pistol", "Mini SMG", "Unholy Hellbringer",
			"Pump Shotgun", "Pump Shotgun Mk II", "Sawed-Off Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "Double Barrel Shotgun", "Sweeper Shotgun", "Combat Shotgun",
			"Assault Rifle", "Assault Rifle Mk II", "Carbine Rifle", "Carbine Rifle Mk II", "Advanced Rifle", "Special Carbine", "Special Carbine Mk II", "Bullpup Rifle", "Bullpup Rifle Mk II", "Compact Rifle", "Military Rifle", "Heavy Rifle", "Service Carbine",
			"MG", "Combat MG", "Combat MG Mk II", "Gusenberg Sweeper",
			"Sniper Rifle", "Heavy Sniper", "Heavy Sniper Mk II", "Marksman Rifle", "Marksman Rifle Mk II", "Precision Rifle",
			"RPG", "Grenade Launcher", "Grenade Launcher Smoke", "Minigun", "Firework Launcher", "Railgun", "Homing Launcher", "Compact Grenade Launcher","Widowmaker","Compact EMP Launcher" };
		std::uint32_t WeaponHashes[89]
		{ 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
		0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
		0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
		0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
		0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A };
		std::size_t WeaponInt = 0;
		int accuary = 75;

		//models
		const char* Models[3]
		{ "FIB", "Cop", "Blackops"};
		const char* ModelHashes[3]
		{ "mp_m_fibsec_01", "s_m_y_cop_01", "s_m_y_blackops_01"};
		std::size_t ModelInt = 0;

		//firing pattern
		bool FiringPatternEnabled = false;
		const char* FiringPattern[7]
		{ "Burst", "Full Auto", "Pistol", "Shotgun", "Slow Fire Tank", "Rifle", "Delayed By One Second"};
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
		const char* Boost_Type[2] = { "Boost", "Jump" };
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
								if (ENTITY::GET_ENTITY_SPEED(playerVehicle) != speed) {
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
		const char* Jump_Type[2] = { "Normal", "Beast" };
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
			}
		}
	};
	inline superJump superjump;
	inline const char* sound_type[9] = { "Schafter V12", "Coquette", "Banshee", "Tempesta", "Casco", "Tyrus", "Carbonizzare", "I-Wagen (Eletric)", "Space Docker" };
	inline const char* sound_data[9] = { "schafter3", "coquette", "banshee2", "tempesta", "casco", "tyrus", "carbonizzare", "iwagen", "dune2" };
	inline std::size_t sound_int = 0;
	inline const char* animation_type[3] = { "Gangster", "Cowboy", "Default" };
	inline const char* animation_data[3] = { "Gang1H", "Hillbilly", "Default" };
	inline std::size_t  animation_int = 0;
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
	class Features {
	public:
		bool vehicle_godmode = false;
		bool auto_parachute = false;
		bool seatbelt = false;
		bool off_the_radar = false;
		bool teleport_gun = false;
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
		void init() {
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
						while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(target))
						{
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(target);

						}




						NativeVector3 gameplayCam = CAM::GET_GAMEPLAY_CAM_COORD();
						NativeVector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
						NativeVector3 camera_direction = RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0));
						NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
						NativeVector3 multiply2 = multiply(&camera_direction, (DistanceBetweenVector3(&gameplayCam, &self_coords) + 6));
						NativeVector3 set_position = addn(&gameplayCam, &multiply2);

						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, set_position.x, set_position.y, set_position.z, false, false, false);

						if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 24)) {
							while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(target))
							{
								NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(target);

							}
							if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(target)) {
								ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, camera_direction.x * 10000.0f, camera_direction.y * 10000.0f, camera_direction.z * 10000.0f, 0.0f, 0.0f, 0.0f, 0, false, true, true, false, true);
								Locked = false;
								PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
							}
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
				if (PED::IS_PED_DEAD_OR_DYING(PLAYER::PLAYER_PED_ID(), 1))
				{
					NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::PLAYER_PED_ID());
				}
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
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z, true, true, true);
					}
				}
			}
			if (off_the_radar) {
				*globals(2689235).at(PLAYER::PLAYER_ID(), 453).at(208).as<bool*>() = off_the_radar;
				*globals(2703735).at(56).as<int*>() = NETWORK::GET_NETWORK_TIME() + (off_the_radar ? 0xB8D08 : NULL);
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
					VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(playerVehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVehicle, 0.0f);
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
			if (!vehicle_godmode) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				{
					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
					ENTITY::SET_ENTITY_INVINCIBLE(playerVehicle, false);
					ENTITY::SET_ENTITY_PROOFS(playerVehicle, false, false, false, false, false, false, false, false);
					VEHICLE::SET_VEHICLE_DAMAGE(playerVehicle, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, false);
					VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(playerVehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVehicle, 0.0f);
					VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(playerVehicle, false);
					VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(playerVehicle, false);
					VEHICLE::SET_VEHICLE_BODY_HEALTH(playerVehicle, 1000.0f);
					VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(playerVehicle, !false);
					VEHICLE::SET_VEHICLE_CAN_BREAK(playerVehicle, !false);
					VEHICLE::SET_VEHICLE_ENGINE_HEALTH(playerVehicle, 1000.0f);
					VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(playerVehicle, !false);
					VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(playerVehicle, !false);
					VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(playerVehicle, 1000.0f);
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVehicle, !false);
					VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(playerVehicle, !false);
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
		const char* explode_type[81] = { "Grenade", "Grenade (Launcher)", "Sticky Bomb", "Molotov", "Rocket", "Tank Shell", "HI Octane", "Car", "Plane", "Gas Pump", "Bike", "Steam", "Flame", "Water", "Gas", "Boat", "Ship Destroy", "Truck", "Bullet", "Smoke", "Smoke 2", "BZ Gas", "Flare", 
			"Unkown", "Extinguisher", "Unkown", "Train", "Barrel", "Propane", "Blimp", "Flame 2", "Tanker", "Plane Rocket", "Vehicle Bullet", "Gas Tank", "Bird Crap", "Railgun", "Blimp 2", "Firework", "Snowball", "Proximity Mine", "Valkyrie Cannon", "Air Defense", "Pipe Bomb", 
			"Vehicle Mine", "Explosive Ammo", "APC Shell", "Cluster Bomb", "Gas Bomb", "Incendiary Bomb", "Bomb", "Torpedo", "Torpedo (Underwater)", "Bombushka Cannon", "Cluster Bomb 2", "Hunter Barrage", "Hunter Cannon", "Rouge Cannon", "Underwater Mine", "Orbital Cannon", 
			"Bomb (Wide)", "Explosive Ammo (Shotgun)", "Oppressor MK II", "Kinetic Mortar", "Kinetic Vehicle Mine", "EMP Vehicle Mine", "Spike Vehicle Mine", "Slick Vehicle Mine", "Tar Vehicle Mine", "Script Drone", "Up-n-Atomizer", "Burried Mine", "Script Missle", "RC Tank Rocket", 
			"Bomb (Water)", "Bomb (Water 2)", "Flash Grenade", "Stun Grenade", "Script Missle (Large)", "Submarine (Big)", "EMP Launcher" };
		std::size_t explode_int = 0;
		void init() {
			if (enabled) {
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					NativeVector3 c;
					if (raycast(c)) {
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, explode_int, damage, sound, invisible, camera_shake, false);
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
					STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"));
						if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"))) {
						fbr::cur()->wait();
						}
						else {

							*g_GameFunctions->should_sync_money_rewards = true;
								OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, c.x, c.y, c.z, 0, 10, MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"), false, true);
								*g_GameFunctions->should_sync_money_rewards = false;
							


							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"));
							delayfr3 = GetTickCount64();

						}
					
				}
				if(money) {
					float dz = c.z;
					c.z = dz + height;
					STREAMING::REQUEST_MODEL(-1666779307);
					if (!STREAMING::HAS_MODEL_LOADED(-1666779307)) {
						fbr::cur()->wait();
					}
					else {
						*g_GameFunctions->should_sync_money_rewards = true;
							OBJECT::CREATE_AMBIENT_PICKUP(1704231442, c.x, c.y, c.z, 1, 2500, -1666779307, false, true);
							*g_GameFunctions->should_sync_money_rewards = false;
						

						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-1666779307);

						delayfr3 = GetTickCount64();
					}

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
					STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"));
					if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"))) {
						fbr::cur()->wait();
					}
					else {

						*g_GameFunctions->should_sync_money_rewards = true;
						OBJECT::CREATE_AMBIENT_PICKUP(1704231442, c.x, c.y, c.z, 1, 0, MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"), false, true);
						*g_GameFunctions->should_sync_money_rewards = false;



						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"));
						delayfr3 = GetTickCount64();

					}

				}
				if (money) {
					float dz = c.z;
					c.z = dz + height;
					STREAMING::REQUEST_MODEL(-1666779307);
					if (!STREAMING::HAS_MODEL_LOADED(-1666779307)) {
						fbr::cur()->wait();
					}
					else {
						*g_GameFunctions->should_sync_money_rewards = true;
						OBJECT::CREATE_AMBIENT_PICKUP(1704231442, c.x, c.y, c.z, 1, 0, -1666779307, false, true);
						*g_GameFunctions->should_sync_money_rewards = false;


						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-1666779307);

						delayfr3 = GetTickCount64();
					}

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
		void mapNotification(const char* body, const char* who) {

			char messageBuffer[256];
			sprintf_s(messageBuffer, sizeof(messageBuffer), "Arctic | ~t~%s ~w~failed ~r~%s", who, body);
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");

			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(messageBuffer);
			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(FALSE, TRUE);




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
						bool godmodec = false;
						if (PLAYER::GET_PLAYER_INVINCIBLE(ped) == true) {
							godmodec = true;
						}
						
						if (invalidmodel) {
							mapNotification("Invalid Model", PLAYER::GET_PLAYER_NAME(i));


						}
						//anti-cheat

						if (PED::GET_PED_CONFIG_FLAG(ped, 223, true) && configflag) {

							mapNotification("Tiny Ped", PLAYER::GET_PLAYER_NAME(i));
						}
						if (ENTITY::GET_ENTITY_SPEED(ped) > 11.0f) {
							if (TASK::IS_PED_RUNNING(ped) && INTERIOR::GET_ROOM_KEY_FROM_ENTITY(ped) == 0) {

								if (!PED::IS_PED_IN_ANY_VEHICLE(ped, false) && !ENTITY::IS_ENTITY_IN_AIR(ped)) {
									mapNotification("Run Speed", PLAYER::GET_PLAYER_NAME(i));
								}

							}
						}
						if (ENTITY::GET_ENTITY_SPEED(ped) > 77.0f) {
							if (!PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
								mapNotification("Fly", PLAYER::GET_PLAYER_NAME(i));
							}
						}
						if (PED::GET_PED_CONFIG_FLAG(ped, 194, true) && configflag) {

							mapNotification("Scenario", PLAYER::GET_PLAYER_NAME(i));
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

						if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
							if (ENTITY::GET_ENTITY_MODEL(veh) == cutter) {
								mapNotification("Unobtainable Vehicle", PLAYER::GET_PLAYER_NAME(i));
							}
							if (ENTITY::GET_ENTITY_MODEL(veh) == cutter2) {
								mapNotification("Unobtainable Vehicle", PLAYER::GET_PLAYER_NAME(i));
							}
							if (ENTITY::GET_ENTITY_MODEL(veh) == cutter3) {
								mapNotification("Unobtainable Vehicle", PLAYER::GET_PLAYER_NAME(i));
							}
							if (ENTITY::GET_ENTITY_MODEL(veh) == cutter4) {
								mapNotification("Unobtainable Vehicle", PLAYER::GET_PLAYER_NAME(i));
							}
							if (ENTITY::GET_ENTITY_MODEL(veh) == cutter5) {
								mapNotification("Unobtainable Vehicle", PLAYER::GET_PLAYER_NAME(i));
							}
							if (ENTITY::GET_ENTITY_MODEL(veh) == cutter6) {
								mapNotification("Unobtainable Vehicle", PLAYER::GET_PLAYER_NAME(i));
							}
							if (ENTITY::GET_ENTITY_MODEL(veh) == cutter7) {
								mapNotification("Unobtainable Vehicle", PLAYER::GET_PLAYER_NAME(i));

							}
							if (ENTITY::GET_ENTITY_MODEL(veh) == cutter8) {
								mapNotification("Unobtainable Vehicle", PLAYER::GET_PLAYER_NAME(i));

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
													mapNotification("Vehicle Speed", PLAYER::GET_PLAYER_NAME(i));


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
														mapNotification("Vehicle Speed", PLAYER::GET_PLAYER_NAME(i));


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
														mapNotification("Vehicle Speed", PLAYER::GET_PLAYER_NAME(i));


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
												mapNotification("Vehicle Speed", PLAYER::GET_PLAYER_NAME(i));
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
										mapNotification("Vehicle Speed", PLAYER::GET_PLAYER_NAME(i));
									}

								}

							}
						}


						if (PLAYER::GET_PLAYER_FAKE_WANTED_LEVEL(ped) == 6 && wantedlevel) {

							mapNotification("6 Star Fake Wanted Level", PLAYER::GET_PLAYER_NAME(i));
						}
						if (godmodec && godmode) {

							mapNotification("Godmode", PLAYER::GET_PLAYER_NAME(i));
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
		void init() {
			if (run) {
				(*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_run_speed = run_speed;
				
				
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
	inline void FeatureInitalize() {
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
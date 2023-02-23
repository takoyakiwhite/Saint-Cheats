#pragma once
#include "Natives.hpp"
#include "FiberHelper.hpp"
#include <GTAV-Classes/ped/CPed.hpp>
#include "Math.h"
namespace Arctic {
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
			if (!enabled) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
					if (DisableCollision) {
						ENTITY::SET_ENTITY_COLLISION(veh, true, true);
					}
				}
			}
		}
	};
	inline NoClip no_clip;
	inline void FeatureInitalize() {
		no_clip.init();
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
		if (!godmode)
		{
			(*g_GameFunctions->m_pedFactory)->m_local_ped->m_damage_bits = 0;
		}
		if (neverWantedBool)
		{
			PLAYER::SET_MAX_WANTED_LEVEL(0);
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, true);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), true);
		}
	}
	
}
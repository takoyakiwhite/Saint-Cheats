#pragma once

#include <cstdint>

namespace rage
{
	class CVehicleStreamRender {
	public:
		char _0x0000[8];
		BYTE UNK1;
		BYTE UNK2;
		unsigned char TireSize; //0x000B 
		char pad_0x000C[0x4]; //0x000C
		unsigned char CustomTires; //0x0010 
		//char pad_0x0011[0xF]; //0x0011
		char pad_0x0011[0xB8F]; //0x0011
		float m_tireWidth; //0x0BA0 
		char pad_0x0BA4[0x464]; //0x0BA4

	}; //Size=0x0020
#pragma pack(push, 4)
    class fwDrawData
    {
    public:
        char pad_0x0000[0x370]; //0x0000
        //CVehicleSteamRenderGFX* m_vehicleStreamRenderGfx; //0x0370 
        CVehicleStreamRender* m_vehicleStreamRender; //0x0370
        char pad_0x0378[0x8B0]; //0x0378
    };
    //static_assert(sizeof(fwDrawData) == 0x2C);
#pragma pack(pop)
}

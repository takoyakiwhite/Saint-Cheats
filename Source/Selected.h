#pragma once
#include "Flash Blip.h"
#include "OTR.h"
#include "Kick.h"
namespace Arctic {
	class GetSelected {
	public:
		FlashBlip flash_blip;
		OTR otr;
		Kicks events;
		void init() {
			flash_blip.init();
			otr.init();
			
		}
	};
	
}
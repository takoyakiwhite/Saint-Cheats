#pragma once
#include "Flash Blip.h"
#include "OTR.h"

namespace Arctic {
	class GetSelected {
	public:
		FlashBlip flash_blip;
		OTR otr;
		void init() {
			flash_blip.init();
			otr.init();
			
		}
	};
	
}
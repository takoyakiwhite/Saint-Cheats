#pragma once

namespace Saint
{
	class Settings
	{
	public:
		std::atomic_bool m_LogWindow = false;
		std::atomic_bool m_LockMouse = false;
	};

	inline Settings g_Settings;
}

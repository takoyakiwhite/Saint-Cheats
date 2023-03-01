#include "Hooking.hpp"
#include "Signatures.hpp"
#include "ScriptManager.hpp"
#include "CustomText.hpp"
#include "Util.hpp"
#include "D3DRenderer.hpp"
#include "UI/Interface.hpp"
#include "Natives.hpp"
#include "FiberHelper.hpp"
#include <MinHook/MinHook.h>
#include "Protections.h"

#ifdef BIGBASE_DEBUG
#  pragma comment(lib, "MinHook-Debug.lib")
#else
#  pragma comment(lib, "MinHook-Release.lib")
#endif

namespace Arctic
{
	namespace
	{
		std::uint32_t g_HookFrameCount{};
	}

	// By using this to hook natives, we are sacrificing performance for safety 
	// Detouring it is faster, but cockstar detects that
	void Hooks::GetStatInt(rage::scrNativeCallContext* src)
	{
		const auto statHash = src->get_arg<Hash>(0);
		const auto outValue = src->get_arg<int*>(1);
		const auto p2 = src->get_arg<int>(2);

		if (g_Running && g_HookFrameCount != *g_GameVariables->m_FrameCount)
		{
			g_HookFrameCount = *g_GameVariables->m_FrameCount;
			g_ScriptManager->OnGameTick();
			g_FiberManager.tick();
		}

		src->set_return_value(STATS::STAT_GET_INT(statHash, outValue, p2));
	}

	

	const char* Hooks::GetLabelText(void* unk, const char* label)
	{
		if (g_Running)
			if (auto text = g_CustomText->GetText(Joaat(label)))
				return text;

		return static_cast<decltype(&GetLabelText)>(g_Hooking->m_OriginalGetLabelText)(unk, label);
	}

	LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		g_D3DRenderer->WndProc(hWnd, msg, wParam, lParam);
		return static_cast<decltype(&WndProc)>(g_Hooking->m_OriginalWndProc)(hWnd, msg, wParam, lParam);
	}
	void Hooks::GetEventData2(rage::scrNativeCallContext* src)
	{
		const auto eventGroup = src->get_arg<int>(0);
		const auto eventIndex = src->get_arg<int>(1);
		const auto args = src->get_arg<Any*>(2);
		const auto argCount = src->get_arg<Hash>(3);

		if (g_LogScriptEvents)
		{
			g_Logger->Info("Script event group: %i", eventGroup);
			g_Logger->Info("Script event index: %i", eventIndex);
			g_Logger->Info("Script event argcount: %i", argCount);
			for (std::uint32_t i = 0; i < argCount; ++i)
				g_Logger->Info("Script event args[%u] : %" PRIi64, i, args[i]);
		}

		src->set_return_value(SCRIPT::GET_EVENT_DATA(eventGroup, eventIndex, args, argCount));
	}
	HRESULT Hooks::Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags)
	{
		if (g_Running)
		{
			g_D3DRenderer->BeginFrame();
			g_ScriptManager->OnD3DTick();
			g_D3DRenderer->EndFrame();
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&Present)>(PresentIndex)(dis, syncInterval, flags);
	}

	HRESULT Hooks::ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			g_D3DRenderer->PreResize();
			auto hr = g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
			if (SUCCEEDED(hr))
			{
				g_D3DRenderer->PostResize();
			}

			return hr;
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	}
	__int64 Hooks::CPlayerListMenuConstructor(__int64 a1, __int64 a2, __int64 a3)
	{
		auto result = static_cast<decltype(&CPlayerListMenuConstructor)>(g_Hooking->m_OriginalJoinSessionHook)(a1, a2, a3);
		m_PlayerListPointer = result;
		return result;
	}
	__int64* Hooks::PlayerWildCardHandler(std::int32_t friendIndex)
	{
		auto original = static_cast<decltype(&PlayerWildCardHandler)>(g_Hooking->m_OriginalRIDFunction)(friendIndex);
		if (m_EnableSCIDJoiner)
		{
			*original = m_SCIDJoiner;
			return original;
		}
		return static_cast<decltype(&PlayerWildCardHandler)>(g_Hooking->m_OriginalRIDFunction)(friendIndex);
	}
	bool Hooks::GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount)
	{
		auto result = static_cast<decltype(&GetEventData)>(g_Hooking->m_OriginalGetEventData)(eventGroup, eventIndex, args, argCount);
		if (NETWORK::NETWORK_IS_SESSION_ACTIVE())
		{
			if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(args[1]))
			{
				if (ENTITY::DOES_ENTITY_EXIST(ped))
				{
					if (result && g_LogScriptEvents)
					{
						
					}

					int netHandle[13];
					const char* RID = "Nigga";
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, netHandle, 13);
					RID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);

					switch (args[0])
					{
					case 330622597:
						if (protections.send_to_location)
						{
							char name[64];
							sprintf(name, "Player: %s\nReason: Send To Location", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])));
							protections.push_notification(name);
							
							
							args[0] = 1234;
							return false;
						}
						break;
					case -702866045:
						if (protections.send_to_location)
						{
							char name[64];
							sprintf(name, "Player: %s\nReason: Send To Location", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])));
							protections.push_notification(name);


							args[0] = 1234;
							return false;
						}
						break;
					case -1796714618:
						if (protections.send_to_location)
						{
							char name[64];
							sprintf(name, "Player: %s\nReason: Send To Location", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])));
							protections.push_notification(name);


							args[0] = 1234;
							return false;
						}
						break;
					case 891653640:
						if (protections.send_to_location)
						{
							char name[64];
							sprintf(name, "Player: %s\nReason: Send To Location", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])));
							protections.push_notification(name);


							args[0] = 1234;
							return false;
						}
						break;
					case -369672308:
						if (protections.send_to_location)
						{
							char name[64];
							sprintf(name, "Player: %s\nReason: Send To Location", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])));
							protections.push_notification(name);


							args[0] = 1234;
							return false;
						}
						break;
					case 1727896103:
						if (protections.send_to_location)
						{
							char name[64];
							sprintf(name, "Player: %s\nReason: Send To Location", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])));
							protections.push_notification(name);


							args[0] = 1234;
							return false;
						}
						break;
					}
				}
			}
		}
		return result;
	}
	Hooking::Hooking():
		m_D3DHook(g_GameVariables->m_Swapchain, 18)
	{

		MH_Initialize();
		MH_CreateHook(g_GameFunctions->m_GetLabelText, &Hooks::GetLabelText, &m_OriginalGetLabelText);
		MH_CreateHook(g_GameFunctions->m_WndProc, &Hooks::WndProc, &m_OriginalWndProc);
		MH_CreateHook(g_GameFunctions->m_PlayerListMenuConstructor, &Hooks::CPlayerListMenuConstructor, &m_OriginalJoinSessionHook);
		MH_CreateHook(g_GameFunctions->m_PlayerWildcard, &Hooks::PlayerWildCardHandler, &m_OriginalRIDFunction);
		MH_CreateHook(g_GameFunctions->m_GetEventData, &Hooks::GetEventData, &m_OriginalGetEventData);
		m_D3DHook.Hook(&Hooks::Present, Hooks::PresentIndex);
		m_D3DHook.Hook(&Hooks::ResizeBuffers, Hooks::ResizeBuffersIndex);
	}

	Hooking::~Hooking() noexcept
	{
		MH_RemoveHook(g_GameFunctions->m_WndProc);
		MH_RemoveHook(g_GameFunctions->m_GetLabelText);
		MH_RemoveHook(g_GameFunctions->m_PlayerListMenuConstructor);
		MH_RemoveHook(g_GameFunctions->m_PlayerWildcard);
		MH_RemoveHook(g_GameFunctions->m_GetEventData);
		MH_Uninitialize();
	}

	void Hooking::Hook()
	{
		m_D3DHook.Enable();
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void Hooking::Unhook()
	{
		m_D3DHook.Disable();
		MH_DisableHook(MH_ALL_HOOKS);
	}
}

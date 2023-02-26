#include "Signatures.hpp"
#include "Invoker.hpp"

namespace Arctic
{

	GameVariables::GameVariables():
		m_GameState(Signature("48 85 C9 74 4B 83 3D").Scan().Add(7).Rip().As<decltype(m_GameState)>()),
		m_FrameCount(Signature("8B 15 ? ? ? ? 41 FF CF").Scan().Add(2).Rip().As<decltype(m_FrameCount)>()),
		m_GameWindow(FindWindowA("grcWindow", nullptr)),
		m_Swapchain(Signature("44 38 35 ? ? ? ? 48 8B 01").Scan().Sub(13).Rip().As<decltype(m_Swapchain)&>()),
		m_ScriptProgramTable(Signature("44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1").Scan().Add(17).Rip().As<decltype(m_ScriptProgramTable)>()),
		m_NativeRegistrations(Signature("76 32 48 8B 53 40 48 8D 0D").Scan().Add(9).Rip().As<decltype(m_NativeRegistrations)>()),
		m_NativeReturnAddress(Signature("FF E3").Scan().As<decltype(m_NativeReturnAddress)>()),
		m_GlobalBase(Signature("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D").Scan().Add(3).Rip().As<decltype(m_GlobalBase)>()),
		m_ModelSpawnBypass(Signature("48 8B C8 FF 52 30 84 C0 74 05 48").Scan().Add(8).As<decltype(m_ModelSpawnBypass)>())
	{
		m_GameBuild = Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8").Scan().Sub(17).Add(268).Rip().As<decltype(m_GameBuild)>();
	}

	void GameVariables::PostInit()
	{
	}

	GameFunctions::GameFunctions() :
		m_GetLabelText(Signature("48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8").Scan().As<decltype(m_GetLabelText)>()),
		m_WndProc(Signature("44 8B E2 4C 8B E9 3B D0").Scan().Sub(52).As<decltype(m_WndProc)>()),
		m_GetNativeHandler(Signature("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A").Scan().Add(12).Rip().As<decltype(m_GetNativeHandler)>()),
		m_FixVectors(Signature("83 79 18 ? 48 8B D1 74 4A FF 4A 18").Scan().As<decltype(m_FixVectors)>()),
		m_pedFactory(Signature("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81").Scan().Add(3).Rip().As<decltype(m_pedFactory)>()),
		m_owned_explosion(Signature("0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8").Scan().As<decltype(m_owned_explosion)>()),
		
		should_sync_money_rewards(Signature("40 8A 2D ? ? ? ? 48 83 64 24 40 00").Scan().Add(3).Rip().As<decltype(should_sync_money_rewards)>())
		
	{
	}
	
}

#include "Signatures.hpp"
#include "Hooking.hpp"
#include "NativeHook.hpp"
#include "ScriptManager.hpp"
#include "LogScript.hpp"
#include "ScriptCallback.hpp"
#include "Invoker.hpp"
#include "CustomText.hpp"
#include "D3DRenderer.hpp"
#include "UI/Interface.hpp"
#include "Translation.hpp"
#include "FiberHelper.hpp"
#include "Script.h"
#include "Render.h"
BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	using namespace Arctic;
	if (reason == DLL_PROCESS_ATTACH)
	{
		g_Module = hInstance;
		CreateThread(nullptr, 0, [](LPVOID) -> DWORD
		{
			g_Logger = std::make_unique<Logger>();
			g_Logger->Info("Arctic Version V2.5.");
			g_Logger->Info("This build was compiled at " __DATE__ ", " __TIME__ ".");

			g_FiberPool.registerFbrPool();
			g_TranslationManager = std::make_unique<TranslationManager>();
			switch (LOCALIZATION::GET_CURRENT_LANGUAGE()) {
			case 0:
				g_TranslationManager->LoadTranslations("English");
				break;
			case 1:
				g_TranslationManager->LoadTranslations("French");
				break;
			case 2:
				g_TranslationManager->LoadTranslations("German");
				break;
			case 3:
				g_TranslationManager->LoadTranslations("Italian");
				break;
			case 4:
				g_TranslationManager->LoadTranslations("Spanish");
				break;
			case 5:
				g_TranslationManager->LoadTranslations("Brazilian");
				break;
			case 6:
				g_TranslationManager->LoadTranslations("Polish");
				break;
			case 7:
				g_TranslationManager->LoadTranslations("Russian");
				break;
			case 8:
				g_TranslationManager->LoadTranslations("Korean");
				break;
			case 9:
				g_TranslationManager->LoadTranslations("Chinese");
				break;
			case 10:
				g_TranslationManager->LoadTranslations("Japanese");
				break;
			case 12:
				g_TranslationManager->LoadTranslations("Chinse_Simplified");
				break;
			}
			

			g_GameFunctions = std::make_unique<GameFunctions>();
			g_GameVariables = std::make_unique<GameVariables>();

			//Game Functions
			if (*g_GameFunctions->m_WndProc)
			{
				g_Logger->Debug("Scanned WndProc.");
			}
			if (*g_GameFunctions->m_GetLabelText)
			{
				g_Logger->Debug("Scanned Label Text.");
			}
			if (*g_GameFunctions->m_GetNativeHandler)
			{
				g_Logger->Debug("Scanned Native Handler.");
			}
			if (*g_GameFunctions->m_FixVectors)
			{
				g_Logger->Debug("Scanned Fix Vectors.");
			}
			g_Logger->Debug("Game Functions Finished Scanning.");
			//patek learning how to do github fr no cap on god 100% luna better than ozark paragon exit scam nigger menu
			//Game Variables
			if (*g_GameVariables->m_GameState)
			{
				g_Logger->Debug("Scanned Game State.");
			}
			if (*g_GameVariables->m_FrameCount)
			{
				g_Logger->Debug("Scanned Frame Count.");
			}
			if (g_GameVariables->m_Swapchain)
			{
				g_Logger->Debug("Scanned Swapchain.");
			}
			if (g_GameVariables->m_ScriptProgramTable)
			{
				g_Logger->Debug("Scanned Script Program Table.");
			}
			if (g_GameVariables->m_NativeRegistrations)
			{
				g_Logger->Debug("Scanned Native Registrations.");
			}
			if (g_GameVariables->m_NativeReturnAddress)
			{
				g_Logger->Debug("Scanned Native Return Address.");
			}
			if (g_GameVariables->m_GlobalBase)
			{
				g_Logger->Debug("Scanned Global Base.");
			}
			if (g_GameVariables->m_ModelSpawnBypass)
			{
				g_Logger->Debug("Scanned Model Spawn Bypass.");
			}
			g_Logger->Debug("Game Variables Finished Scanning.");

			// Wait for the game to load
			while (*g_GameVariables->m_GameState != 0)
			{
				std::this_thread::sleep_for(3s);
				std::this_thread::yield();
			}

			//If game not started when injected say "Waitng for game to load" when loaded say "Game loaded" 
			if (*g_GameVariables->m_GameState = 0)
			{
				g_Logger->Info("Waiting For Game To Load.");
				if (*g_GameVariables->m_GameState = 1)
				{
					g_Logger->Info("Game Loaded.");
				}
			}

			g_GameVariables->PostInit();
			g_CustomText = std::make_unique<CustomText>();
			g_D3DRenderer = std::make_unique<D3DRenderer>();
			g_Render = std::make_unique<UserInterface::UIManager>();
			g_ScriptManager = std::make_unique<ScriptManager>();
			g_MainScript = std::make_shared<MainScript>();
			g_LogScript = std::make_shared<LogScript>();
			g_CallbackScript = std::make_shared<CallbackScript>();
			g_ScriptManager->AddScript(g_LogScript);
			g_ScriptManager->AddScript(g_CallbackScript);
			g_FiberManager.add(std::make_unique<fbr>([=] { g_MainScript->Tick(); }), "main_script");
			g_Hooking = std::make_unique<Hooking>();
			g_Hooking->Hook();
			auto g_NativeHook = std::make_unique<NativeHooks>();

			g_Logger->Info("Game Version %s", g_GameVariables->m_GameBuild);
			g_Logger->Info("Finished Injecting Have A Fun Time!");
			Noti::InsertNotification({ ImGuiToastType_None, 2000, "Menu Injected" });
			while (g_Running)
			{
				if (IsKeyPressed(VK_DELETE))
					g_Running = false;
				std::this_thread::sleep_for(3ms);
				std::this_thread::yield();
			}

			std::this_thread::sleep_for(500ms);

			g_NativeHook.reset();

			g_Hooking->Unhook();

			g_ScriptManager.reset();
			g_LogScript.reset();
			g_MainScript.reset();
			g_CallbackScript.reset();

			g_Render.reset();
			g_D3DRenderer.reset();
			g_CustomText.reset();

			std::this_thread::sleep_for(500ms);

			g_Hooking.reset();

			g_TranslationManager.reset();

			g_GameVariables.reset();
			g_GameFunctions.reset();
			
			g_Logger->Info("Come Again!");
			g_Logger.reset();

			FreeLibraryAndExitThread(g_Module, 0);
		}, nullptr, 0, nullptr);
	}

	return true;
}

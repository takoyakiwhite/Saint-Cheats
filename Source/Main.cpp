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
#include "Discord/DiscordHandler.hpp"
#define MENU_VERSION "1.12.1"
BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	using namespace Saint;
	if (reason == DLL_PROCESS_ATTACH)
	{
		g_Module = hInstance;
		CreateThread(nullptr, 0, [](LPVOID) -> DWORD
		{
			g_Logger = std::make_unique<Logger>();
			g_Logger->Info("Saint Version 1.12.1");
			g_Logger->Info("This build was compiled at " __DATE__ ", " __TIME__ ".");

			g_FiberPool.registerFbrPool();
			g_TranslationManager = std::make_unique<TranslationManager>();
			g_TranslationManager->LoadTranslations("English");
			
			

			g_GameFunctions = std::make_unique<GameFunctions>();
			g_GameVariables = std::make_unique<GameVariables>();

			//Game Functions
			
			

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
			g_Discord->Init();
			g_Render->m_HeaderBackgroundColor = { 108, 60, 175, 255 };

			//Footer

			//Footer
			g_Render->m_FooterBackgroundColor = { 0, 0, 0, 255 };

			//Option
			g_Render->m_OptionSelectedBackgroundColor = { 255, 255, 255, 255 };

			//Description
			//g_Render->m_DescriptionBackgroundColor = { 234, 90, 81, 255 };

			//Background
			g_Render->m_OptionSelectedTextColor = { 0, 0, 0, 255 };
			g_Render->m_Width = 0.21;
			g_Render->glare_x_offset = 0.008;
			g_Render->header_name = "Saint";

			g_Render->m_HeaderText = false;
			g_Render->m_HeaderNativeText = true;

			g_Render->submenu_enabled = true;

			g_Render->IndicatorIterator = 0;

			//registering
			
			//Noti::InsertNotification({ ImGuiToastType_None, 2000, "Welcome %s",PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_PED_ID()) });
			while (g_Running)
			{
				if (IsKeyPressed(VK_DELETE))
					g_Running = false;
				std::this_thread::sleep_for(3ms);
				std::this_thread::yield();
			}

			std::this_thread::sleep_for(500ms);

			g_Discord->Shutdown();

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

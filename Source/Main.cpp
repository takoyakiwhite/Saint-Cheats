#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "md5.h"
#include "obfuscate.h"
#define obfuscatestring(s) std::string(AY_OBFUSCATE(s))
#include "VirtualizerSDK.h"
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
#include <Windows.h>
#include <ShellAPI.h>
#include <urlmon.h>


#pragma comment (lib, "urlmon.lib") 
#define MENU_VERSION "1.2"
void load_dir() {
	using namespace Saint;
	fs::create_directories("C:\\Saint\\");
	fs::create_directories("C:\\Saint\\Fonts");

	int yes18 = _wmkdir((const wchar_t*)"C:\\Saint\\Fonts\\Chinese-Rocks.ttf");
	int yes19 = _wmkdir((const wchar_t*)"C:\\Saint\\Textures.ytd");

	std::string path;
	std::ofstream file;
	std::string DownloadPP = std::string("C:\\Saint\\Fonts\\Chinese-Rocks.ttf");
	std::string DownloadPP2 = std::string("C:\\Saint\\Textures.ytd");


	URLDownloadToFileA(0, "https://saintcheats.xyz/Chinese-Rocks.ttf", DownloadPP.c_str(), 0, 0);
	URLDownloadToFileA(0, "https://saintcheats.xyz/Textures.ytd", DownloadPP2.c_str(), 0, 0);
}
std::string wideToString(std::wstring strw) {
	if (strw.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &strw[0], (int)strw.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &strw[0], (int)strw.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}
#ifndef DEV
std::string gethwid(void) {
	HW_PROFILE_INFOW winapiHWID;
	GetCurrentHwProfileW(&winapiHWID);
	return md5(wideToString(winapiHWID.szHwProfileGuid));
}
std::string encryptDecrypt(std::string toEncrypt) {
	char key[3] = { 'V', 'B', 'C' };
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
	return output;
}
#endif
BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	using namespace Saint;
	if (reason == DLL_PROCESS_ATTACH)
	{
		
		g_Module = hInstance;
		CreateThread(nullptr, 0, [](LPVOID) -> DWORD
			{
				std::unique_ptr<NativeHooks> g_NativeHook;
#ifndef DEV
				VIRTUALIZER_DOLPHIN_BLACK_START
				bool authed = false;
				ATOM Atom1;
				std::string hash;
				std::ifstream i(obfuscatestring("C:\\Saint\\key.txt"));
				std::stringstream s;
				s << i.rdbuf();
				i.close();
				std::string key = s.str();
				auto client = httplib::SSLClient(obfuscatestring("saintcheats.xyz"));
				auto response2 = client.Get(obfuscatestring("/saintauth.php?init=true"));
				std::string hwid = gethwid();
				std::string times = std::to_string(time(NULL));
				std::string times2 = encryptDecrypt(response2->body);
				httplib::MultipartFormDataItems form = {
					{obfuscatestring("key"), key},
					{obfuscatestring("hwid"), hwid},
					{obfuscatestring("key1"), times},
					{obfuscatestring("key2"), times2},
				};
				auto response = client.Post(obfuscatestring("/saintauth.php"), form);
				std::string body = response->body;
				if (body == obfuscatestring("err2"))
				{
					exit(-1);
					goto yeet;
				}
				hash = md5(key + times + obfuscatestring("ikey"));
				if (body == hash) {
					exit(-1);
					goto yeet;
				}
				hash = md5(key + times + hwid + obfuscatestring("ihwid"));
				if (body == hash) {
					exit(-1);
					goto yeet;
				}
				hash = md5(key + times + hwid + obfuscatestring("success"));
				if (body != hash) {
					exit(-1);
					goto yeet;
				}
				else {
					authed = true;
				}
#endif
				g_Logger = std::make_unique<Logger>();
				g_Logger->Info("Saint Version %s", MENU_VERSION);
				g_Logger->Info("This build was compiled at " __DATE__ ", " __TIME__ ".");

				g_FiberPool.registerFbrPool();
				
				g_GameFunctions = std::make_unique<GameFunctions>();
				g_GameVariables = std::make_unique<GameVariables>();
#ifndef DEV
				Atom1 = GlobalFindAtomA(AY_OBFUSCATE("R'g^gc]]pQkEE.wWQp"));
				if (!Atom1)
				{
					exit(-1);
					goto yeet;
				}
				while (Atom1) {
					GlobalDeleteAtom(Atom1);
					Atom1 = GlobalFindAtomA(AY_OBFUSCATE("R'g^gc]]pQkEE.wWQp"));
				}
#endif	
				g_Logger->Info("Authed successfully");
				//Game Functions
				// 
				// Wait for the game to load
				if (*g_GameVariables->m_GameState != 0) 
					g_Logger->Info("Waiting For Game To Load.");
				
				while (*g_GameVariables->m_GameState != 0)
				{
					std::this_thread::sleep_for(3s);
					std::this_thread::yield();
				}
				g_Logger->Info("Game Loaded.");
				

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
				g_NativeHook = std::make_unique<NativeHooks>();
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
				g_Render->glare_x_offset = 0.007;
				g_Render->header_name = "Saint";

				g_Render->m_HeaderText = false;
				g_Render->m_HeaderNativeText = true;

				g_Render->submenu_enabled = true;

				g_Render->IndicatorIterator = 0;

				//registering
				load_dir();
				Noti::InsertNotification({ ImGuiToastType_None, 2000, "Welcome, if your looking to disable phone its in misc",PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_PED_ID()) });
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


				g_GameVariables.reset();
				g_GameFunctions.reset();

				g_Logger->Info("Come Again!");
				g_Logger.reset();
			yeet:
#ifndef DEV
				VIRTUALIZER_DOLPHIN_BLACK_END
#endif
				FreeLibraryAndExitThread(g_Module, 0);
			
			}, nullptr, 0, nullptr);
	}

	return true;
}

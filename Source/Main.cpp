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
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include "Features.h"

#pragma comment (lib, "urlmon.lib") 
#pragma comment(lib, "winmm.lib")

const char* meower = "";
bool fileExists(const std::string& filePath) {
	std::ifstream file(filePath);
	return file.good();
}
bool does_exist(const char* path, const char* file) {
	std::string MenuFolderPath = path;
	if (fileExists(MenuFolderPath + file)) {
		return true;
	}
	else {
		return false;
	}
	return false;
}
void load_dir() {
	using namespace Saint;
	fs::create_directories("C:\\Saint\\");
	fs::create_directories("C:\\Saint\\Sounds");

	//int yes18 = _wmkdir((const wchar_t*)"C:\\Saint\\Fonts\\Chinese-Rocks.ttf");
	if (!does_exist("C:\\Saint\\", "Textures.ytd")) {
		int yes19 = _wmkdir((const wchar_t*)"C:\\Saint\\Textures.ytd");
	}
	int yes18 = _wmkdir((const wchar_t*)"C:\\Saint\\Sounds\\Intro.wav");
	if (!does_exist("C:\\Saint\\Sounds\\", "Notification.wav")) {
		//int yes20 = _wmkdir((const wchar_t*)"C:\\Saint\\Sounds\\Notification.wav");
	}

	std::string path;
	std::ofstream file;
	std::string DownloadPP3 = std::string("C:\\Saint\\Sounds\\Notification.wav");
	std::string DownloadPP2 = std::string("C:\\Saint\\Textures.ytd");


	//URLDownloadToFileA(0, "https://saintcheats.xyz/Chinese-Rocks.ttf", DownloadPP.c_str(), 0, 0);
	if (!does_exist("C:\\Saint\\", "Textures.ytd")) {
		URLDownloadToFileA(0, "https://saintcheats.xyz/Textures.ytd", DownloadPP2.c_str(), 0, 0);
	}
	
	if (!does_exist("C:\\Saint\\Sounds\\", "Notification.wav")) {
		URLDownloadToFileA(0, "https://cdn.discordapp.com/attachments/1104892686386876427/1104971663755464814/Notification.wav", DownloadPP3.c_str(), 0, 0); // dont work nice tim
	}
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
std::string branding = " | Saint Cheats";
std::array<std::string, 3> Titles = {
	"What am I doing wrong - Patek/Jayden." + branding,
	"Unleash your inner vali" + branding,
	"\"is this scooby?\"" + branding
};
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
				g_Logger->Info(R"( 
					   _____ ___    _____   ________
					  / ___//   |  /  _/ | / /_  __/
					  \__ \/ /| |  / //  |/ / / /   
					 ___/ / ___ |_/ // /|  / / /    
					/____/_/  |_/___/_/ |_/ /_/     
                                
				)");
				g_Logger->Info("Version: %s", MENU_VERSION);
				g_Logger->Info("This build was compiled on " __DATE__ ". ");
			//	PlaySound(TEXT("C:\\Saint\\Sounds\\Intro.wav"), NULL, SND_FILENAME | SND_ASYNC);
				g_FiberPool.registerFbrPool();

				g_GameFunctions = std::make_unique<GameFunctions>();
				g_GameVariables = std::make_unique<GameVariables>();
				srand(time(NULL));
				SetWindowTextA(g_GameVariables->m_GameWindow, Titles[rand() % Titles.size()].c_str());
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

				g_Logger->Info("Authed successfully");
#else
				g_Logger->Error("Running in dev mode! NEVER release a dev build.");
#endif	
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

				//everybody forgot me and the work i put in


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


				//registering
				load_dir();
				if (does_exist("C:\\Saint\\Sounds\\", "Notification.wav")) { // prevent crashes
					Noti::InsertNotification({ ImGuiToastType_None, 2000, "Welcome, thanks for buying Saint!", });
				}
				//PlaySound(TEXT("C:\\Saint\\Sounds\\Intro.wav"), NULL, SND_FILENAME | SND_ASYNC);

				if (tutorial.get_theme_path() != "NoneActive" || tutorial.get_theme_path() != "") {
					g_ThemeLoading.load(tutorial.get_theme_path());
				}

				
				while (g_Running)
				{

					if (Flags->isDev()) {
						if (IsKeyPressed(VK_DELETE))
							g_Running = false;
						std::this_thread::sleep_for(3ms);
						std::this_thread::yield();
					}
				}

				std::this_thread::sleep_for(500ms);
				PlaySound(NULL, NULL, 0);
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

				SetWindowTextA(g_GameVariables->m_GameWindow, "Grand Theft Auto V"); //Restore Game Name on unload
				g_GameVariables.reset();
				g_GameFunctions.reset();

				g_Logger->Info("Come Again!");
				g_Logger.reset();
			yeet:
#ifndef DEV
				VIRTUALIZER_DOLPHIN_BLACK_END
#endif
					OPENSSL_thread_stop();
				FreeLibraryAndExitThread(g_Module, 0);

			}, nullptr, 0, nullptr);
	}

	return true;
}

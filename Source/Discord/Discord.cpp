#include "DiscordHandler.hpp"
#include "Discord_Register.h"
#include "Discord_RPC.h"
#include <chrono>
#include "../Common.hpp"
#include "../Natives.hpp"
#pragma comment(lib, "discord-rpc.lib")

using namespace Saint;

void discordhandler::Init() {
    DiscordEventHandlers handlers;
    std::memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize("1081824913767276594", &handlers, 1, "0");
}

void discordhandler::Tick() {
    static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    DiscordRichPresence discordPresence;
    std::memset(&discordPresence, 0, sizeof(discordPresence));
    if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
        discordPresence.state = "Online";
        discordPresence.partySize = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
        discordPresence.partyMax = 32;
    } else {
        discordPresence.state = "Story Mode";
    }
    discordPresence.details = "Modding With Saint [PAID]";
    discordPresence.startTimestamp = StartTime;
    discordPresence.largeImageKey = "saint";
    discordPresence.largeImageText = "Saint Mod Menu";
    discordPresence.button1name = "Website";
    discordPresence.button1link = "https://saintcheats.xyz";
    discordPresence.button2name = "Discord";
    discordPresence.button2link = "https://discord.com/invite/UVm93H6J";
    discordPresence.instance = 1;

    Discord_UpdatePresence(&discordPresence);
}

void discordhandler::Shutdown() {
    Discord_ClearPresence();
    Discord_Shutdown();
}
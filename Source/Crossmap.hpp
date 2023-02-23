#pragma once
#include "Common.hpp"

namespace Arctic
{
    constexpr auto g_NativeCount = 6439;
    using CrossMap = std::array<std::pair<rage::scrNativeHash, rage::scrNativeHash>, g_NativeCount>;
    extern CrossMap g_CrossMap;
}
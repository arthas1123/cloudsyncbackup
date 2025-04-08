#pragma once
#include <string>

namespace Emoji
{
    inline bool enabled =
#if defined(__APPLE__) || defined(__linux__)
        true;
#else
        false; // Windows cmd.exe 通常不支援
#endif

    inline std::string Rocket() { return enabled ? "🚀" : "[RUN]"; }
    inline std::string Check() { return enabled ? "✅" : "[OK]"; }
    inline std::string Trash() { return enabled ? "🗑️" : "[DEL]"; }
    inline std::string Note() { return enabled ? "📝" : "[NOTE]"; }
    inline std::string Warning() { return enabled ? "⚠️" : "[WARN]"; }
    inline std::string Error() { return enabled ? "❌" : "[ERR]"; }
    inline std::string File() { return enabled ? "📁" : "[FILE]"; }
    inline std::string Menu() { return enabled ? "📖" : "[MENU]"; }
    inline std::string Question() { return enabled ? "❓" : "[?]"; }
}

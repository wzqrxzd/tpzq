#ifndef CONFIG_MANAGER_HXX
#define CONFIG_MANAGER_HXX

#include "json.hpp"
#include <filesystem>
#include <unordered_set>

using json = nlohmann::json;
namespace fs = std::filesystem;

class ConfigManager
{
  public:
    ConfigManager(const fs::path& themesDir);
    std::unordered_set<fs::path> getThemesSet();
    json getTheme(const fs::path& theme);
  private:
    const fs::path themesDir;
    std::unordered_set<fs::path> themesSet;
};

#endif

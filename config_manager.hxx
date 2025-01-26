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
    ConfigManager(const fs::path& config, const fs::path& themesDir);
    std::unordered_set<fs::path> getThemesSet();
    json getConfig();
    json getTheme(const fs::path& themePath);
    void saveConfig(const json& config);
  private:
    const fs::path configPath;
    const fs::path themesDir;
    std::unordered_set<fs::path> themesSet;

    void createDefaultConfig();
};

#endif

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
    ConfigManager();
    std::unordered_set<fs::path> getThemesSet();
    json getConfig();
    json getTheme(const fs::path& themePath);
    void saveConfig(const json& config);
  private:
    const fs::path configPath = std::getenv("HOME") + std::string("/.config/tpzq/config.json");
    const fs::path themesDir = std::getenv("HOME") + std::string("/.config/tpzq/themes/");
    std::unordered_set<fs::path> themesSet;

    void createDefaultConfig();
    const json defaultConfig {
      {"background-color", "#0F0F17"},
      {"accent_color", "#A0302B"},
      {"hovered_color", "#782420"}
    };
};

#endif

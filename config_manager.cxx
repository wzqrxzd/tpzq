#include "config_manager.hxx"

#include <fstream>
#include <spdlog/spdlog.h>

ConfigManager::ConfigManager(const fs::path& themesDir) : themesDir{themesDir}
{
  if (!fs::exists(themesDir))
    throw std::runtime_error("Themes Dir not valid");
}

std::unordered_set<fs::path> ConfigManager::getThemesSet()
{
  for (const auto& entry : fs::directory_iterator(themesDir))
  {
    if (fs::is_regular_file(entry))
      themesSet.insert(entry);
  }

  return themesSet;
}

json ConfigManager::getTheme(const fs::path& theme)
{
  std::ifstream configFile(theme);
  if (!configFile.is_open())
  {
    spdlog::error("Failed to open {} file", theme.string());
    throw std::runtime_error("Failed to open config file");
  }

  json config;
  try {
    configFile >> config;
  } catch (const json::exception& e)
  {
    spdlog::error("Error reading JSON: {}", e.what());
    throw std::runtime_error("Error reading JSON");
  }

  return config;
}

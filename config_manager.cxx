#include "config_manager.hxx"

#include <fstream>
#include <spdlog/spdlog.h>

ConfigManager::ConfigManager(const fs::path& configPath, const fs::path& themesDir) : configPath{configPath}, themesDir{themesDir}
{
  if (!fs::exists(configPath))
  {
    createDefaultConfig();
    spdlog::warn("create default config.");
  }
  if (!fs::exists(themesDir) || !fs::exists(configPath))
    throw std::runtime_error("Config manager argument not valid");
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

json ConfigManager::getTheme(const fs::path& themePath)
{
  std::ifstream themeFile(themePath);
  if (!themeFile.is_open())
  {
    spdlog::error("Failed to open {} file", themePath.string());
    throw std::runtime_error("Failed to open config file");
  }

  json theme;
  try {
    themeFile >> theme;
  } catch (const json::exception& e)
  {
    spdlog::error("Error reading JSON: {}", e.what());
    throw std::runtime_error("Error reading JSON");
  }

  return theme;
}

json ConfigManager::getConfig()
{
  std::ifstream configFile(configPath);
  if (!configFile.is_open())
  {
    spdlog::error("Failed to open {} file", configPath.string());
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

void ConfigManager::createDefaultConfig()
{
  json defaultConfig = {
    {"background-color", "#0F0F17"},
    {"accent_color", "#A0302B"},
    {"hovered_color", "#782420"}
  };

  saveConfig(defaultConfig);
}

void ConfigManager::saveConfig(const json& config)
{
  std::ofstream ofile(configPath);
  if (!ofile.is_open())
  {
    spdlog::error("Failed to open {} file", configPath.string());
    throw std::runtime_error("Failed to open config file");
  }

  ofile << config.dump(4);
  ofile.close();
}

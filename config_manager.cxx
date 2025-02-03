#include "config_manager.hxx"

#include <fstream>
#include <spdlog/spdlog.h>

ConfigManager::ConfigManager()
{
  if (!fs::exists(configPath))
  {
    saveConfig(defaultConfig);
    spdlog::warn("Default config been created.");
  }

  if (!fs::exists(themesDir))
  {
   fs::create_directory(themesDir); 
   spdlog::warn("Themes dir been created.");
   throw std::runtime_error("0 themes exists.");
  }

  if (!fs::exists(themesDir) || !fs::exists(configPath))
    throw std::runtime_error("Config manager argument is not valid.");
}

std::unordered_set<fs::path> ConfigManager::getThemesSet()
{
  for (const auto& entry : fs::directory_iterator(themesDir))
  {
    if (fs::is_regular_file(entry))
      themesSet.insert(entry);
  }

  for (const auto& theme : themesSet)
    spdlog::info("Themes set: {}", theme.string());
  return themesSet;
}

json ConfigManager::getTheme(const fs::path& themePath)
{
  std::ifstream themeFile(themePath);
  if (!themeFile.is_open())
  {
    spdlog::error("Failed to open {} file.", themePath.string());
    throw std::runtime_error(std::format("Failed to open {} file.", themePath.string()));
  }

  json theme;
  try {
    themeFile >> theme;
  } catch (const json::exception& e)
  {
    spdlog::error("Error reading JSON: {}", e.what());
    throw std::runtime_error(std::format("Error reading JSON: {}", e.what()));
  }

  return theme;
}

json ConfigManager::getConfig()
{
  std::ifstream configFile(configPath);
  if (!configFile.is_open())
  {
    spdlog::error("Failed to open {} file.", configPath.string());
    throw std::runtime_error(std::format("Failed to open {} file.", configPath.string()));
  }

  json config;
  try {
    configFile >> config;
  } catch (const json::exception& e)
  {
    spdlog::error("Error reading JSON: {}", e.what());
    throw std::runtime_error(std::format("Error reading JSON: {}", e.what()));
  }

  return config;
}

void ConfigManager::createDefaultConfig()
{

  saveConfig(defaultConfig);
}

void ConfigManager::saveConfig(const json& config)
{
  if (!fs::exists(configPath.parent_path()))
   fs::create_directory(configPath.parent_path()); 

  spdlog::info("Config dir: {}", configPath.parent_path().string());

  std::ofstream ofile(configPath);
  if (!ofile.is_open())
  {
    spdlog::error("Failed to open {} file", configPath.string());
    throw std::runtime_error(std::format("Failed to open {} file.", configPath.string()));
  }

  ofile << config.dump(4);
  ofile.close();
}

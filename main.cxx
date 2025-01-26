#include <iostream>
#include <spdlog/spdlog.h>

#include "config_manager.hxx"
#include "hyprland_controller.hxx"
#include "waybar_controller.hxx"
#include "wallpaper_controller.hxx"
#include "wofi_controller.hxx"

int main()
{
  fs::path themesDir("/home/wzqrxzd/projects/tpzq/themes/");
  ConfigManager cfgManager(themesDir);
  auto themesSet = cfgManager.getThemesSet();

  for (const auto& theme : themesSet)
    spdlog::info("Theme: {}", theme.string());

  std::string inputName;

  std::cout << "Enter theme name: ";
  std::cin >> inputName;

  fs::path inputPath(themesDir.string() + inputName);

  if (themesSet.find(inputPath) == themesSet.end())
  {
    spdlog::error("theme not exists");
    throw std::runtime_error("theme not exists");
  }

  json config = cfgManager.getTheme(inputPath);
  std::vector<std::unique_ptr<Controller>> controllers;
  controllers.push_back(std::make_unique<WaybarController>(&config));
  controllers.push_back(std::make_unique<HyprlandController>(&config));
  controllers.push_back(std::make_unique<WofiController>(&config));
  controllers.push_back(std::make_unique<WallpaperController>(&config));

  for (const auto& controller : controllers)
    controller->apply();
}

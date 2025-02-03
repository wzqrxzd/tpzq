#include "wallpaper_controller.hxx"
#include <fstream>
#include <regex>
#include <cstdlib>

WallpaperController::WallpaperController(const nlohmann::json* json)
{
  if (json == nullptr)
    throw std::invalid_argument("WallpaperController Json: pointer == nullptr.");

  if (!json->contains("wallpaper"))
    throw std::invalid_argument("WallpaperController Json: wallpaper cfg not exists.");

  if (!(*json)["wallpaper"].contains("current"))
    throw std::invalid_argument("WallpaperController Json: wallpaper curent not exists.");

  config = json;
}

void WallpaperController::apply()
{
  std::ifstream ifile(configPath);
  if (!ifile.is_open())
    throw std::runtime_error("WallpaperController: error during reading file.");

  std::string configData((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());
  ifile.close();

  std::regex pattern_preload(R"(preload = .+)");
  std::regex pattern_wallpaper(R"(wallpaper = .+)");

  configData = std::regex_replace(configData, pattern_preload, "preload = " + (*config)["wallpaper"]["current"].get<std::string>());
  configData = std::regex_replace(configData, pattern_wallpaper, "wallpaper = eDP-1," + (*config)["wallpaper"]["current"].get<std::string>());

  std::ofstream ofile(configPath);
  if (!ofile.is_open())
    throw std::runtime_error("WallpaperController: error during saving file.");
  ofile << configData;
  ofile.close();

  std::system("pkill hyprpaper >/dev/null 2>&1");
  std::system("hyprpaper &>/dev/null &");
}

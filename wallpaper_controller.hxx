#ifndef WALLPAPER_CONTROLLER_HXX
#define WALLPAPER_CONTROLLER_HXX

#include "controller.hxx"

namespace fs = std::filesystem;

class WallpaperController : public Controller
{
  public:
    WallpaperController(const nlohmann::json* json);
    void apply() override;
  private:
    const fs::path configPath = std::getenv("HOME") + std::string("/.config/hypr/hyprpaper.conf");
};

#endif

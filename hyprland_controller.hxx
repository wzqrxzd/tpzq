#ifndef HYPRLAND_CONTROLLER_HXX
#define HYPRLAND_CONTROLLER_HXX

#include "controller.hxx"

namespace fs = std::filesystem;

class HyprlandController : public Controller {
  public:
    HyprlandController(const nlohmann::json* json);
    void apply() override;
  private:
    const fs::path configPath = std::getenv("HOME") + std::string("/.config/hypr/hyprland.conf");
};

#endif

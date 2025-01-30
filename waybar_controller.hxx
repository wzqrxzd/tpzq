#ifndef WAYBAR_CONTROLLER_HXX
#define WAYBAR_CONTROLLER_HXX

#include "controller.hxx"

namespace fs = std::filesystem;

class WaybarController : public Controller {
  public:
    WaybarController(const nlohmann::json* json);
    void apply() override;
  private:
    const fs::path configPath = std::getenv("HOME") + std::string("/.config/waybar/style.css");
};

#endif

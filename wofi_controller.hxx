#ifndef WOFI_CONTROLLER_HXX
#define WOFI_CONTROLLER_HXX

#include "controller.hxx"

namespace fs = std::filesystem;

class WofiController : public Controller {
  public:
    WofiController(const nlohmann::json* json);
    void apply() override;
  private:
    const fs::path configPath = std::getenv("HOME") + std::string("/.config/wofi/style.css");
};

#endif

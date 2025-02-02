#ifndef CAVA_CONTROLLER_HXX
#define CAVA_CONTROLLER_HXX

#include "controller.hxx"

using json = nlohmann::json;
namespace fs = std::filesystem;

class CavaController : public Controller {
  public:
    CavaController(const json* json);
    void apply() override;
  private:
    const fs::path configPath = std::getenv("HOME") + std::string("/.config/cava/config");
};

#endif

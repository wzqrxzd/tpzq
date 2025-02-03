#include "wofi_controller.hxx"
#include <fstream>
#include <regex>

WofiController::WofiController(const nlohmann::json* json)
{
  if (json == nullptr)
    throw std::invalid_argument("WofiController Json: pointer == nullptr.");

  if (!json->contains("wofi"))
    throw std::invalid_argument("WofiController Json: wofi cfg not exists.");

  if (!(*json)["wofi"].contains("color"))
    throw std::invalid_argument("WofiController Json: wofi color not exists.");

  config = json;
}

void WofiController::apply()
{
  std::ifstream ifile(configPath);
  if (!ifile.is_open())
    throw std::runtime_error("WofiController: error during reading file.");

  std::string configData((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());
  ifile.close();

  std::regex pattern_selected(R"((#entry:selected\s*\{\s*background-color:\s*)#[0-9A-Fa-f]{6})");
  configData = std::regex_replace(configData, pattern_selected, "$1" + (*config)["wofi"]["color"].get<std::string>());

  std::ofstream ofile(configPath);
  if (!ofile.is_open())
    throw std::runtime_error("WofiController: error during saving file.");

  ofile << configData;
  ofile.close();
}

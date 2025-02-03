#include "hyprland_controller.hxx"
#include <fstream>
#include <regex>

HyprlandController::HyprlandController(const nlohmann::json* json)
{
  if (json == nullptr)
    throw std::invalid_argument("HyprlandController Json: pointer == nullptr.");

  if (!json->contains("hyprland"))
    throw std::invalid_argument("HyprlandController Json: hyprland cfg not exists.");

  if (!(*json)["hyprland"].contains("active_color"))
    throw std::invalid_argument("HyprlandController Json: hyprland active color not exists.");

  if (!(*json)["hyprland"].contains("inactive_color"))
    throw std::invalid_argument("HyprlandController Json: hyprland inactive color not exists.");

  config = json;
}

void HyprlandController::apply()
{
  std::ifstream ifile(configPath);
  if (!ifile.is_open())
    throw std::runtime_error("HyprlandController: error during reading file.");

  std::string configData((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());

  ifile.close();

  std::regex activeBorderRegex(R"(col\.active_border = .+)");
  std::regex inactiveBorderRegex(R"(col\.inactive_border = .+)");

  configData = std::regex_replace(configData, activeBorderRegex, "col.active_border = " + (*config)["hyprland"]["active_color"].get<std::string>());
  configData = std::regex_replace(configData, inactiveBorderRegex, "col.inactive_border = " + (*config)["hyprland"]["inactive_color"].get<std::string>());

  std::ofstream ofile(configPath);
  if (!ofile.is_open())
    throw std::runtime_error("HyprlandController: error during saving file.");

  ofile << configData;
  ofile.close();
}

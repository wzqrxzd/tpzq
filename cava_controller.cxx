#include "cava_controller.hxx"
#include <fstream>
#include <regex>

CavaController::CavaController(const json* json)
{
  if (json == nullptr)
    throw std::invalid_argument("CavaController Json: pointer = nullptr.");

  if (!json->contains("cava"))
    throw std::invalid_argument("CavaController Json: cava cfg not exists.");

  if (!(*json)["cava"].contains("color"))
    throw std::invalid_argument("CavaController Json: cava color not exists.");

  config = json;
}

void CavaController::apply()
{
  std::ifstream ifile(configPath);
  if (!ifile.is_open())
    throw std::runtime_error("CavaController: error during reading file.");

  std::string configData((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());

  ifile.close();

  std::regex colorRegex(R"((\s*foreground\s*=\s*)'#[0-9A-Fa-f]{6}')"); // убран лишний апостроф
  configData = std::regex_replace(configData, colorRegex, "$1'" + (*config)["cava"]["color"].get<std::string>() + "'"); // заменяем корректно

  std::ofstream ofile(configPath);
  if (!ofile.is_open())
    throw std::runtime_error("CavaController: error during saving file.");

  ofile << configData;
  ofile.close();

  std::system("pkill -USR1 cava");
}

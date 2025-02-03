#include "theme_switcher.hxx"
#include <format>

#include "hyprland_controller.hxx"
#include "waybar_controller.hxx"
#include "wallpaper_controller.hxx"
#include "wofi_controller.hxx"
#include "cava_controller.hxx"


ThemeSwitcher::ThemeSwitcher(QWidget* parent) : QWidget(parent), cfgManager()
{
  themesSet = cfgManager.getThemesSet();
  config = cfgManager.getConfig();
  setupUI();
}

std::string ThemeSwitcher::getButtonStyle()
{
  return std::format(
    "QPushButton {{ border-radius: 10px; background-color: {}; color: white; font-size: 14px; border: none; padding: 10px; }} "
    "QPushButton:hover {{ background-color: {}; }}"
    "QPushButton:focus {{ background-color: {}; outline: none; }}", 
    config["accent_color"].get<std::string>(), config["hovered_color"].get<std::string>(), config["hovered_color"].get<std::string>()
  );
}

std::string ThemeSwitcher::getWindowStyle()
{
  return std::format("background-color: {};", config["background-color"].get<std::string>());
}

void ThemeSwitcher::setupUI()
{
  layout = new QHBoxLayout(this);
  this->setStyleSheet(getWindowStyle().c_str());
  layout->setSpacing(spacing);
  layout->setContentsMargins(spacing, 0, spacing, 0);

  for (const auto& theme : themesSet)
  {
    QPushButton* button = new QPushButton(QString::fromStdString(theme.stem()));
    button->setFixedSize(buttonWidth, buttonHeight);
    button->setStyleSheet(getButtonStyle().c_str());

    QObject::connect(button, &QPushButton::clicked, [&theme, this](){ onButtonClick(theme); });
    layout->addWidget(button);
  }

  int windowWidth = spacing + (themesSet.size() * buttonWidth) + (themesSet.size() - 1) * spacing + spacing;
  this->setFixedWidth(windowWidth);
  this->setFixedHeight(100);
  this->setWindowTitle("tpzq");
};

void ThemeSwitcher::onButtonClick(const fs::path& theme)
{
  json configTheme = cfgManager.getTheme(theme);
  this->config["accent_color"] = configTheme["tpzq"]["accent_color"].get<std::string>();
  this->config["hovered_color"] = configTheme["tpzq"]["hovered_color"].get<std::string>();
  cfgManager.saveConfig(this->config);

  std::vector<std::unique_ptr<Controller>> controllers;
  controllers.push_back(std::make_unique<WaybarController>(&configTheme));
  controllers.push_back(std::make_unique<HyprlandController>(&configTheme));
  controllers.push_back(std::make_unique<WofiController>(&configTheme));
  controllers.push_back(std::make_unique<CavaController>(&configTheme));
  controllers.push_back(std::make_unique<WallpaperController>(&configTheme));

  for (const auto& controller : controllers)
    controller->apply();

  spdlog::info("Successfully updated theme");
  exit(0);
}

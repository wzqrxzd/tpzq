#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <spdlog/spdlog.h>

#include <format>
#include "config_manager.hxx"
#include "hyprland_controller.hxx"
#include "waybar_controller.hxx"
#include "wallpaper_controller.hxx"
#include "wofi_controller.hxx"

void onClick(ConfigManager& mgr, const fs::path& theme, json& configApp);

int main(int argc, char* argv[])
{
  fs::path configPath("/home/wzqrxzd/projects/tpzq/build/config.json");
  fs::path themesDir("/home/wzqrxzd/projects/tpzq/themes/");

  ConfigManager cfgManager(configPath, themesDir);
  auto themesSet = cfgManager.getThemesSet();
  json config = cfgManager.getConfig();

  QApplication app(argc, argv);

  QWidget* window = new QWidget();
  QHBoxLayout *layout = new QHBoxLayout(window);

  std::string windowStyle = std::format("background-color: {};", config["background-color"].get<std::string>());

  std::string buttonStyle = std::format(
    "QPushButton {{ border-radius: 10px; background-color: {}; color: white; font-size: 14px; border: none; padding: 10px; }} "
    "QPushButton:hover {{ background-color: {}; }}"
    "QPushButton:focus {{ background-color: {}; outline: none; }}", 
    config["accent_color"].get<std::string>(), config["hovered_color"].get<std::string>(), config["hovered_color"].get<std::string>()
  );

  window->setStyleSheet(windowStyle.c_str());

  for (const auto& theme : themesSet)
  {
    QPushButton* button = new QPushButton(QString::fromStdString(theme.stem()));
    button->setFixedSize(100, 100);
    layout->setSpacing(30);

    button->setStyleSheet(
        buttonStyle.c_str()
    );

    QObject::connect(button, &QPushButton::clicked, [&cfgManager, &theme, &config](){onClick(cfgManager, theme, config);});
    layout->addWidget(button);
  }

  int windowWidth = 100 + 30 * (themesSet.size() - 1) + 100 * themesSet.size();
  window->setFixedWidth(windowWidth);
  window->setFixedHeight(150);
  window->setWindowTitle("tpzq");

  window->show();
  return app.exec();
}

void onClick(ConfigManager& mgr, const fs::path& theme, json& configApp)
{
  json config = mgr.getTheme(theme);
  configApp["accent_color"] = config["tpzq"]["accent_color"].get<std::string>();
  configApp["hovered_color"] = config["tpzq"]["hovered_color"].get<std::string>();
  mgr.saveConfig(configApp);

  std::vector<std::unique_ptr<Controller>> controllers;
  controllers.push_back(std::make_unique<WaybarController>(&config));
  controllers.push_back(std::make_unique<HyprlandController>(&config));
  controllers.push_back(std::make_unique<WofiController>(&config));
  controllers.push_back(std::make_unique<WallpaperController>(&config));

  for (const auto& controller : controllers)
    controller->apply();

  spdlog::info("Successfully updated theme");
  exit(0);
}

#ifndef THEME_SWITCHER_HXX
#define THEME_SWITCHER_HXX

#include "config_manager.hxx"
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <spdlog/spdlog.h>

class ThemeSwitcher : public QWidget
{
  Q_OBJECT;

  public:
    ThemeSwitcher(QWidget* parent = nullptr);
  private:
    const int buttonHeight = 75;
    const int buttonWidth = 75;
    const int spacing = 20;

    ConfigManager cfgManager;
    json config;
    std::unordered_set<fs::path> themesSet;
    QHBoxLayout* layout;

    void setupUI();
    std::string getButtonStyle();
    std::string getWindowStyle();
    void onButtonClick(const fs::path& theme);
};

#endif

#include "theme_switcher.hxx"

int main(int argc, char* argv[])
{
  QApplication app (argc, argv);
  ThemeSwitcher window;
  window.show();
  return app.exec();
}

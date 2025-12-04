#include <iostream>
#include <QApplication>
#include "app_window.hpp"


int main(int argc, char* argv[])
{
  QApplication app (argc, argv);
  AppWindow window = AppWindow();
  window.show();
  app.exec();
  return 0;
}

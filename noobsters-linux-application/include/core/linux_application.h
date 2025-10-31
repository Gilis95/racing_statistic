#ifndef LINUX_APPLICATION_H
#define LINUX_APPLICATION_H

#include <adwaita.h>

#include <memory>
#include <sstream>

namespace noobsters::linux_platform {
class main_window;

class application {
 public:
  application(int argc, char **argv);

  ~application();

 public:
  int run();
  void on_activate(GtkApplication *app);

 private:
  static void load_ui_resources();
  static std::string construct_ui_resources_name();

 private:
  int m_argc;
  char **m_argv;

  AdwApplication *m_app;

  std::unique_ptr<main_window> m_window;
};
}  // namespace noobsters::linux_platform

#endif  // LINUX_APPLICATION_H

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <adwaita.h>

#include <memory>

namespace noobsters::linux_platform {
class main_window_controller;
class main_window_view;

class main_window {
 public:
  main_window();
  ~main_window();

 public:
  void register_sources();
  void show(const GtkApplication& app);

 private:
  GtkWidget*                              m_window;
  std::unique_ptr<main_window_view>       m_view;
  std::unique_ptr<main_window_controller> m_controller;
};
}  // namespace noobsters::linux_platform
#endif  // MAIN_WINDOW_H

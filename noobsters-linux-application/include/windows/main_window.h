#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <adwaita.h>

#include "controllers/main_window_controller.h"
#include "views/main_window_view.h"

namespace noobsters::linux_platform {

class main_window {
 public:
  main_window();
  ~main_window();

 public:
  void show(const GtkApplication& app);

 private:
  GtkWidget* m_window;
  main_window_view m_view;
  main_window_controller m_controller;
};
}  // namespace noobsters::linux_platform
#endif  // MAIN_WINDOW_H

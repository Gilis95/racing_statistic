#include "core/linux_application.h"

#include <adwaita.h>

#include <filesystem>

#include "config.h"
#include "core/linux_macros.h"
#include "core/noobsters_filesystem.h"
#include "core/noobsters_macros.h"
#include "core/resource_manager.h"
#include "windows/main_window.h"

namespace noobsters::linux_platform {

application::application(int argc, char **argv)
    : m_argc(argc),
      m_argv(argv),
      m_app(adw_application_new("org.noobsters", G_APPLICATION_DEFAULT_FLAGS)),
      m_window(nullptr) {
  auto &fs = noobsters::filesystem::instance();
  fs.set_work_dir(std::filesystem::path(std::string(PROJECT_WORKING_DIR)));

  load_ui_resources();

  m_window = std::make_unique<main_window>();

  g_signal_connect(m_app, "activate",
                   G_CALLBACK(+[](GtkApplication *app, gpointer custom_data) {
                     static_cast<application *>(custom_data)->on_activate(app);
                   }),
                   this);
}

application::~application() { g_object_unref(m_app); }

int application::run() {
  return g_application_run(G_APPLICATION(m_app), m_argc, m_argv);
}

void application::on_activate(GtkApplication *app) {
  CrashUnless(app);
  m_window->show(*app);
}

void application::load_ui_resources() {
  auto resource_name = construct_ui_resources_name();

  auto maybe_error = resource_manager::instance().load(
      resource_type::MAIN_MENUS, resource_name);
  check_critical_error(maybe_error);
}

std::string application::construct_ui_resources_name() {
  std::stringstream resource_name_builder;

  resource_name_builder << PROJECT_ID << ".gresource";

  return resource_name_builder.str();
}
}  // namespace noobsters::linux_platform

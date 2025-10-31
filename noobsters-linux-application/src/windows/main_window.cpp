#include "windows/main_window.h"

#include <adwaita.h>

#include "core/constants.h"
#include "core/linux_macros.h"
#include "core/noobsters_macros.h"
#include "core/resource_manager.h"

namespace noobsters::linux_platform {

/////////////////////////////////////////////////////////////////////////////////////////
main_window::main_window()
    : m_window(nullptr), m_view(), m_controller(m_view) {}

/////////////////////////////////////////////////////////////////////////////////////////
main_window::~main_window() { gtk_window_destroy(GTK_WINDOW(m_window)); }

/////////////////////////////////////////////////////////////////////////////////////////
void main_window::show(const GtkApplication &app) {
  auto object_or_error = resource_manager::instance().find_object(
      resource_type::MAIN_MENUS, constants::S_MAIN_MENU_PATH);
  check_critical_error(object_or_error);

  GBytes *menu_data = object_or_error.value();

  auto char_menu_data =
      static_cast<const char *>(g_bytes_get_data(menu_data, nullptr));
  auto menu_data_size = static_cast<gssize>(g_bytes_get_size(menu_data));

  auto window_builder =
      gtk_builder_new_from_string(char_menu_data, menu_data_size);

  m_window = GTK_WIDGET(gtk_builder_get_object(window_builder, "main_menu"));

  gtk_application_add_window(GTK_APPLICATION(&app), GTK_WINDOW(m_window));
  gtk_window_present(GTK_WINDOW(m_window));
}

}  // namespace noobsters::linux_platform
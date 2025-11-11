#include "windows/main_window.h"

#include <adwaita.h>

#include "contender.h"
#include "controller/main_window_controller.h"
#include "core/constants.h"
#include "core/linux_macros.h"
#include "core/noobsters_macros.h"
#include "core/resource_manager.h"
#include "view/main_window_view.h"

namespace {}

namespace noobsters::linux_platform {

// --------------------------------------------------------------------
// Function to generate one example entry
// --------------------------------------------------------------------
static contending_team make_example_team() {
  contending_team team;

  // Top-level info
  team.m_position     = 1;
  team.m_kart_number  = 42;
  team.m_nationality  = "RUS";
  team.m_lap_count    = 134;
  team.m_pit_count    = 2;
  team.m_pit_time     = time_unit(12'345ul);  // arbitrary units
  team.m_gap_to_first = time_unit(0ul);       // leader
  team.m_gap_to_next  = time_unit(1'234ul);   // time to next team

  // Current lap data
  team.m_current_lap.m_sector_times = {time_unit(27'512ul), time_unit(29'103ul),
                                       time_unit(31'220ul)};
  team.m_current_lap.m_total_time   = time_unit(27'512ul + 29'103ul + 31'220ul);

  // Build one contender (driver)
  contender_data driver1;
  driver1.m_contender_name = "Max Schnell";
  driver1.m_best_lap       = time_unit(1'259'321ul);

  // Build one stint (set of laps)
  stint_data stint;
  stint.m_contender = driver1;

  // Add a few laps
  for (std::uint64_t i = 0; i < 3; ++i) {
    lap_data lap;
    lap.m_sector_times = {time_unit(27'500ul + i * 10ul),
                          time_unit(29'000ul + i * 15ul),
                          time_unit(31'100ul + i * 20ul)};
    lap.m_total_time =
        lap.m_sector_times[0] + lap.m_sector_times[1] + lap.m_sector_times[2];
    stint.m_laps.push_back(lap);
  }

  // Compute total stint time
  stint.m_total_time = time_unit(0);
  for (const auto &lap : stint.m_laps) stint.m_total_time += lap.m_total_time;

  // Add stint to team
  team.m_stints.push_back(stint);

  // Optionally, add a second stint
  stint_data stint2                   = stint;
  stint2.m_contender.m_contender_name = "John Kartman";
  stint2.m_contender.m_best_lap       = time_unit(1'255'000ul);
  team.m_stints.push_back(stint2);

  return team;
}

/////////////////////////////////////////////////////////////////////////////////////////
main_window::main_window() : m_window(nullptr) {}

/////////////////////////////////////////////////////////////////////////////////////////
main_window::~main_window() { gtk_window_destroy(GTK_WINDOW(m_window)); }

/////////////////////////////////////////////////////////////////////////////////////////
void main_window::register_sources() {
   m_controller->register_sources();
}

/////////////////////////////////////////////////////////////////////////////////////////
void main_window::show(const GtkApplication &app) {
  auto object_or_error = resource_manager::instance().find_object(
      resource_type::MAIN_MENUS, constants::S_MAIN_MENU_PATH);
  check_critical_error(object_or_error);

  GBytes *menu_data = object_or_error.value();

  auto char_menu_data =
      static_cast<const char *>(g_bytes_get_data(menu_data, nullptr));
  auto menu_data_size = static_cast<gssize>(g_bytes_get_size(menu_data));

  auto *const window_builder =
      gtk_builder_new_from_string(char_menu_data, menu_data_size);
  AssertReturnUnless(window_builder);

  m_window = GTK_WIDGET(gtk_builder_get_object(window_builder, "main_window"));
  m_view   = std::make_unique<main_window_view>(*window_builder);
  m_controller = std::make_unique<main_window_controller>(*m_view);

  gtk_application_add_window(GTK_APPLICATION(&app), GTK_WINDOW(m_window));
  gtk_window_present(GTK_WINDOW(m_window));

  static auto to_be_visualized = make_example_team();
  m_view->add_row(to_be_visualized);
}

}  // namespace noobsters::linux_platform
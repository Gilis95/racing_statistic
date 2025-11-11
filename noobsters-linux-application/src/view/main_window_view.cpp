

#include "view/main_window_view.h"

#include <gtk/gtkcolumnview.h>

#include "core/linux_macros.h"
#include "core/noobsters_macros.h"
#include "core/time_unit.h"
#include "model/contender_model.h"

namespace noobsters::linux_platform {

/////////////////////////////////////////////////////////////////////////////////////////
main_window_view::main_window_view(GtkBuilder& builder) {
  m_view =
      GTK_COLUMN_VIEW(gtk_builder_get_object(&builder, "leaderboard-table"));
  AssertReturnUnless(m_view);

  m_model =
      G_LIST_STORE(gtk_builder_get_object(&builder, "leaderboard-entry-model"));
  AssertReturnUnless(m_model);

  setup_position_factory(builder);
  setup_kart_number_factory(builder);
  setup_nationality_factory(builder);
  setup_sector1_factory(builder);
  setup_sector2_factory(builder);
  setup_sector3_factory(builder);
  setup_lap_total_factory(builder);
  setup_lap_count_factory(builder);
  setup_pit_count_factory(builder);
  setup_pit_time_factory(builder);
  setup_gap_to_first_factory(builder);
  setup_gap_to_next_factory(builder);
  setup_contender_name_factory(builder);
  setup_best_lap_factory(builder);
  setup_stint_total_time_factory(builder);
}

/////////////////////////////////////////////////////////////////////////////////////////
void main_window_view::add_row(const contending_team& contender) {
  ContenderModel* model = map_contending_team_to_model(contender);

  g_list_store_append(m_model, model);
}

NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, position)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, kart_number)
NOOBSTERS_DEFINE_SETUP_STR_FACTORY_FN(main_window_view, nationality)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, sector1)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, sector2)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, sector3)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, lap_total)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, lap_count)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, pit_count)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, pit_time)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, gap_to_first)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, gap_to_next)
NOOBSTERS_DEFINE_SETUP_STR_FACTORY_FN(main_window_view, contender_name)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, best_lap)
NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(main_window_view, stint_total_time)

}  // namespace noobsters::linux_platform
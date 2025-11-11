#include "model/contender_model.h"

#include <gtk/gtk.h>

#include "core/noobsters_macros.h"

BEGIN_IGNORE_WARNINGS

void map_stint_data(const noobsters::contending_team &team,
                    ContenderModel &row);
G_DEFINE_TYPE(ContenderModel, contender_model, G_TYPE_OBJECT)

static void contender_model_dispose(GObject *obj) {
  auto *self = reinterpret_cast<ContenderModel *>(obj);
  g_clear_pointer(&self->nationality, g_free);
  g_clear_pointer(&self->contender_name, g_free);
  G_OBJECT_CLASS(contender_model_parent_class)->dispose(obj);
}

static void contender_model_class_init(ContenderModelClass *klass) {
  GObjectClass *object_class = G_OBJECT_CLASS(klass);
  object_class->dispose = contender_model_dispose;
}

static void contender_model_init(ContenderModel */*self*/) {}

ContenderModel *contender_model_new(
    guint64 position, gint32 kart_number, const char *nationality,
    guint64 sector1, guint64 sector2, guint64 sector3, guint64 lap_total,
    guint64 lap_count, guint64 pit_count, guint64 pit_time,
    guint64 gap_to_first, guint64 gap_to_next, const char *contender_name,
    guint64 best_lap, guint64 stint_total_time) {
  auto *model = static_cast<ContenderModel *>(
      g_object_new(CONTENDER_TYPE_MODEL, nullptr));

  model->position = position;
  model->kart_number = kart_number;
  model->nationality = g_strdup(nationality);
  model->sector1 = sector1;
  model->sector2 = sector2;
  model->sector3 = sector3;
  model->lap_total = lap_total;
  model->lap_count = lap_count;
  model->pit_count = pit_count;
  model->pit_time = pit_time;
  model->gap_to_first = gap_to_first;
  model->gap_to_next = gap_to_next;
  model->contender_name = g_strdup(contender_name);
  model->best_lap = best_lap;
  model->stint_total_time = stint_total_time;

  return model;
}

ContenderModel *contender_model_new_empty() {
  return static_cast<ContenderModel *>(
      g_object_new(CONTENDER_TYPE_MODEL, nullptr));
}

ContenderModel *map_contending_team_to_model(
    const noobsters::contending_team &team) {
  ContenderModel *row = contender_model_new_empty();

  row->position = team.m_position;
  row->kart_number = team.m_kart_number;
  row->nationality = g_strdup(team.m_nationality.c_str());
  row->pit_count = team.m_pit_count;
  row->pit_time = team.m_pit_time.as_miliseconds();
  row->gap_to_first = team.m_gap_to_first.as_miliseconds();
  row->gap_to_next = team.m_gap_to_next.as_miliseconds();

  // lap data
  row->sector1 = team.m_current_lap.m_sector_times.at(0).as_miliseconds();
  row->sector2 = team.m_current_lap.m_sector_times.at(1).as_miliseconds();
  row->sector3 = team.m_current_lap.m_sector_times.at(2).as_miliseconds();
  row->lap_total = team.m_current_lap.m_total_time.as_miliseconds();
  // lap data

  map_stint_data(team, *row);

  return row;
}

void map_stint_data(const noobsters::contending_team &team,
                    ContenderModel &row) {
  ReturnIf(team.m_stints.empty());

  const noobsters::stint_data &stint = team.m_stints.back();
  const noobsters::contender_data &contender = stint.m_contender;

  row.contender_name = g_strdup(contender.m_contender_name.c_str());
  row.best_lap = contender.m_best_lap.as_miliseconds();
  row.stint_total_time = stint.m_total_time.as_miliseconds();
}

END_IGNORE_WARNINGS
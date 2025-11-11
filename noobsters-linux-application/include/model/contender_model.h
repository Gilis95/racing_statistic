#ifndef CONTENDER_MODEL_H
#define CONTENDER_MODEL_H

#include <gtk/gtk.h>

#include "contender.h"
#include "model/contender_model.h"

G_BEGIN_DECLS

#define CONTENDER_TYPE_MODEL (contender_model_get_type())
G_DECLARE_FINAL_TYPE(ContenderModel, contender_model, , CONTENDER_MODEL,
                     GObject)

// Constructor helper
ContenderModel *contender_model_new(guint64 position, gint32 kart_number,
                                    const char *nationality, guint64 sector1,
                                    guint64 sector2, guint64 sector3,
                                    guint64 lap_total, guint64 lap_count,
                                    guint64 pit_count, guint64 pit_time,
                                    guint64 gap_to_first, guint64 gap_to_next,
                                    const char *contender_name,
                                    guint64 best_lap, guint64 stint_total_time);

ContenderModel *contender_model_new_empty();

G_END_DECLS

struct _ContenderModel {
  GObject parent_instance;

  guint64 position;
  gint32  kart_number;
  gchar  *nationality;

  guint64 sector1;
  guint64 sector2;
  guint64 sector3;
  guint64 lap_total;

  guint64 lap_count;
  guint64 pit_count;

  guint64 pit_time;
  guint64 gap_to_first;
  guint64 gap_to_next;

  gchar  *contender_name;
  guint64 best_lap;
  guint64 stint_total_time;
};

ContenderModel *map_contending_team_to_model(
    const noobsters::contending_team &team);

#endif  // CONTENDER_MODEL_H

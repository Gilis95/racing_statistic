#ifndef LINUX_MACROS_H
#define LINUX_MACROS_H
#include <glib/gerror.h>

#include <expected>
#include <optional>

#include "core/noobsters_logger.h"
#include "core/noobsters_macros.h"

void inline check_error(const GError* maybe_error) {
  ReturnUnless(maybe_error);

  NOOBSTERS_ERROR_TAG("UI", maybe_error->message);
}

void inline check_error(optional_const_ref<GError> maybe_error) {
  ReturnUnless(maybe_error);

  NOOBSTERS_ERROR_TAG("UI", maybe_error->get().message);
}

template <typename T>
void check_critical_error(std::expected<T, ref<GError>> object_or_error) {
  ReturnIf(object_or_error.has_value());

  NOOBSTERS_CRITICAL_TAG("UI", object_or_error.error().get().message);
  CRASH;
}

void inline check_critical_error(optional_const_ref<GError> maybe_error) {
  ReturnUnless(maybe_error);

  NOOBSTERS_CRITICAL_TAG("UI", maybe_error->get().message);
  CRASH;
}

void inline check_critical_error(GError* maybe_error) {
  ReturnUnless(maybe_error);

  NOOBSTERS_CRITICAL_TAG("UI", maybe_error->message);
  CRASH;
}

#define NOOBSTERS_DECLARE_SETUP_DIGIT_FACTORY_FN(field_name)                   \
  void                      setup_##field_name##_factory(GtkBuilder& builder); \
  GtkSignalListItemFactory* m_##field_name##_factory = nullptr

#define NOOBSTERS_DECLARE_SETUP_STR_FACTORY_FN(field_name)                     \
  void                      setup_##field_name##_factory(GtkBuilder& builder); \
  GtkSignalListItemFactory* m_##field_name##_factory = nullptr

#define NOOBSTERS_DEFINE_SETUP_DIGIT_FACTORY_FN(space, field_name)           \
  void space::setup_##field_name##_factory(GtkBuilder& builder) {            \
    m_##field_name##_factory = GTK_SIGNAL_LIST_ITEM_FACTORY(                 \
        gtk_builder_get_object(&builder, STRINGIFY(field_name) "-factory")); \
                                                                             \
    g_signal_connect(                                                        \
        m_##field_name##_factory, "bind",                                    \
        G_CALLBACK(+[](GtkListItemFactory* /*factory*/, GtkListItem* item,   \
                       gpointer /*user_data*/) {                             \
          const auto* row = static_cast<ContenderModel*>(                    \
              gtk_list_item_get_item(GTK_LIST_ITEM(item)));                  \
          GtkLabel* label = GTK_LABEL(gtk_list_item_get_child(item));        \
                                                                             \
          auto position_str = std::to_string(row->field_name);               \
          gtk_label_set_text(label, g_strdup(position_str.c_str()));         \
        }),                                                                  \
        nullptr);                                                            \
    g_signal_connect(                                                        \
        m_##field_name##_factory, "setup",                                   \
        G_CALLBACK(+[](GtkListItemFactory* /*factory*/, GtkListItem* item,   \
                       gpointer /*user_data*/) {                             \
          GtkWidget* label = gtk_label_new(NULL);                            \
          gtk_widget_set_halign(label, GTK_ALIGN_START);                     \
          gtk_list_item_set_child(item, label);                              \
        }),                                                                  \
        nullptr);                                                            \
  }

#define NOOBSTERS_DEFINE_SETUP_STR_FACTORY_FN(space, field_name)             \
  void space::setup_##field_name##_factory(GtkBuilder& builder) {            \
    m_##field_name##_factory = GTK_SIGNAL_LIST_ITEM_FACTORY(                 \
        gtk_builder_get_object(&builder, STRINGIFY(field_name) "-factory")); \
                                                                             \
    g_signal_connect(                                                        \
        m_##field_name##_factory, "bind",                                    \
        G_CALLBACK(+[](GtkListItemFactory* /*factory*/, GtkListItem* item,   \
                       gpointer /*user_data*/) {                             \
          const auto* row = static_cast<ContenderModel*>(                    \
              gtk_list_item_get_item(GTK_LIST_ITEM(item)));                  \
          GtkLabel* label = GTK_LABEL(gtk_list_item_get_child(item));        \
                                                                             \
          gtk_label_set_text(label, g_strdup(row->field_name));              \
        }),                                                                  \
        nullptr);                                                            \
    g_signal_connect(                                                        \
        m_##field_name##_factory, "setup",                                   \
        G_CALLBACK(+[](GtkListItemFactory* /*factory*/, GtkListItem* item,   \
                       gpointer /*user_data*/) {                             \
          GtkWidget* label = gtk_label_new(NULL);                            \
          gtk_widget_set_halign(label, GTK_ALIGN_START);                     \
          gtk_list_item_set_child(item, label);                              \
        }),                                                                  \
        nullptr);                                                            \
  }
#endif  // LINUX_MACROS_H

#include "controller/main_window_controller.h"

#include "contender_storage.h"
#include "event/event_handler.h"
#include "event/event_handler.hpp"
#include "event/racing_data_change_event.h"

extern "C" {
struct SourceData {
  GSource*                                           m_source;
  noobsters::linux_platform::main_window_controller* m_controller;
};
}

namespace noobsters::linux_platform {
/////////////////////////////////////////////////////////////////////////////////////////
main_window_controller::main_window_controller(main_window_view& view)
    : event_handler<contender_created>(),
      event_handler<contender_updated>(),
      m_view(view) {}

/////////////////////////////////////////////////////////////////////////////////////////
main_window_controller::~main_window_controller() = default;

/////////////////////////////////////////////////////////////////////////////////////////
void main_window_controller::register_sources() {
  static GSourceFuncs source_funcs(
      +[](GSource* base, gint* /*timeout_*/) -> gboolean {
        const auto* data = reinterpret_cast<SourceData*>(base);
        return static_cast<gboolean>(data->m_controller->event_source_check());
      },
      +[](GSource* source) -> gboolean {
        const auto* data = reinterpret_cast<SourceData*>(source);
        return static_cast<gboolean>(data->m_controller->event_source_check());
      },
      +[](GSource* source, GSourceFunc /*callback*/,
          gpointer /*user_data*/) -> gboolean {
        const auto* data = reinterpret_cast<SourceData*>(source);
        return static_cast<gboolean>(
            data->m_controller->event_source_dispatch());
      },
      nullptr);

  m_update_source = g_source_new(&source_funcs, sizeof(SourceData));
}

/////////////////////////////////////////////////////////////////////////////////////////
bool main_window_controller::event_source_check() const {
  return m_is_event_available.test(std::memory_order_acquire);
}

/////////////////////////////////////////////////////////////////////////////////////////
bool main_window_controller::event_source_dispatch() {
  const auto& contender_storage = contender_storage::instance();

  while (!is_event_queue_empty()) {
    auto event = pop_first_event();

    std::visit(overloaded{[](contender_updated update_event) {},
                          [&contender_storage,
                           &view = m_view](contender_created created_event) {
                            auto contender = contender_storage.get(
                                created_event.m_entry_idx);
                            AssertReturnUnless(contender);
                            view.add_row(contender->get());
                          }},
               event);
  }

  return update_event_flag();
}

/////////////////////////////////////////////////////////////////////////////////////////
void main_window_controller::on_event(
    const contender_updated& change_event) /*override*/ {
  store_event(change_event);
}

/////////////////////////////////////////////////////////////////////////////////////////
void main_window_controller::on_event(
    const contender_created& change_event) /*override*/ {
  store_event(change_event);
}

/////////////////////////////////////////////////////////////////////////////////////////
main_window_controller::event main_window_controller::pop_first_event() {
  std::lock_guard queue_lock(m_change_events_mutex);

  auto& stored_event = m_change_events.front();
  m_change_events.pop();

  return stored_event;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool main_window_controller::is_event_queue_empty() const {
  std::lock_guard queue_lock(m_change_events_mutex);

  return m_change_events.empty();
}

/////////////////////////////////////////////////////////////////////////////////////////
bool main_window_controller::update_event_flag() {
  bool event_queue_empty = is_event_queue_empty();
  event_queue_empty
      ? m_is_event_available.clear(std::memory_order_release)
      : m_is_event_available.test_and_set(std::memory_order_release);

  return event_queue_empty;
}

}  // namespace noobsters::linux_platform
#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

#include <queue>

#include "event/event_handler.h"
#include "event/racing_data_change_event.h"
#include "view/main_window_view.h"

namespace noobsters {
/////////////////////////////////////////////////////////////////////////////////////////
struct contender_updated;

}  // namespace noobsters

namespace noobsters::linux_platform {

/////////////////////////////////////////////////////////////////////////////////////////
class main_window_controller : private event_handler<contender_updated>,
                               private event_handler<contender_created> {
 private:
  using event       = std::variant<contender_updated, contender_created>;
  using event_queue = std::queue<event>;

 public:
  explicit main_window_controller(main_window_view& view);
  ~main_window_controller() override;

 public:
  void register_sources();
  bool event_source_check() const;

  bool event_source_dispatch();

 private:
  void on_event(const contender_updated&) override;
  void on_event(const contender_created&) override;

  template<typename contender_change_event>
  void store_event(const contender_change_event& change_event);

 private:
  [[nodiscard]] inline event pop_first_event();
  [[nodiscard]] inline bool  is_event_queue_empty() const;
  inline bool                update_event_flag();

 private:
  std::atomic_flag m_is_event_available{false};
  std::mutex       m_change_events_mutex;
  event_queue      m_change_events;

  GSource*          m_update_source;
  main_window_view& m_view;
};
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
template<typename contender_change_event>
void main_window_controller::store_event(const contender_change_event& change_event) {
  {
    std::lock_guard queue_lock(m_change_events_mutex);

    m_change_events.emplace(change_event);
  }

  update_event_flag();
  g_main_context_wakeup(nullptr);
}
}  // namespace noobsters::linux_platform

#endif  // MAIN_WINDOW_CONTROLLER_H

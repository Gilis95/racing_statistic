#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H
#include "core/time_unit.h"
#include "event/event_handler.h"
#include "event/racing_data_change_event.h"
#include "views/main_window_view.h"

namespace noobsters {
/////////////////////////////////////////////////////////////////////////////////////////
struct racing_entry_changed;


}  // namespace noobsters

namespace noobsters::linux_platform {

/////////////////////////////////////////////////////////////////////////////////////////
class main_window_controller : private event_handler<racing_entry_changed> {
 public:
  explicit main_window_controller(main_window_view& view);
private:
   void on_event(const racing_entry_changed&) override;

 public:

 private:
  main_window_view& m_view;
};
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
}  // namespace noobsters::linux_platform

#endif  // MAIN_WINDOW_CONTROLLER_H

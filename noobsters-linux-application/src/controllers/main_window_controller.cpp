#include "controllers/main_window_controller.h"

#include "event/event_handler.h"
#include "event/event_handler.hpp"
#include "event/racing_data_change_event.h"

namespace noobsters::linux_platform {
/////////////////////////////////////////////////////////////////////////////////////////
main_window_controller::main_window_controller(main_window_view& view)
    : event_handler(), m_view(view) {}

/////////////////////////////////////////////////////////////////////////////////////////
void main_window_controller::on_event(
    const racing_entry_changed&) /*override*/ {}

}  // namespace noobsters::linux_platform

#ifndef NOOBSTERS_EVENT_HANDLER_HPP_
#define NOOBSTERS_EVENT_HANDLER_HPP_
#include "event/event_controller.h"
#include "event/event_handler.h"

namespace noobsters {
template <typename event_type>
event_handler<event_type>::event_handler() {
  event_controller::register_event_handler<event_type>(this);
}

template <typename event_type>
event_handler<event_type>::~event_handler() {
  event_controller::unregister_event_handler<event_type>(this);
}
}  // namespace noobsters
#endif  // NOOBSTERS_EVENT_HANDLER_HPP_
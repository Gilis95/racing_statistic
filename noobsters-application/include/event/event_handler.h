#ifndef NOOBSTERS_EVENT_HANDLER_H_
#define NOOBSTERS_EVENT_HANDLER_H_

namespace noobsters {
template <typename event_type>
class event_handler {
 public:
  event_handler();
  virtual ~event_handler();

  virtual void on_event(const event_type&) = 0;
};

}  // namespace noobsters
#endif  // NOOBSTERS_EVENT_HANDLER_H_

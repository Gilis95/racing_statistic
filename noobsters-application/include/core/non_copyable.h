#ifndef NOOBSTERS_NON_COPYABLE_H
#define NOOBSTERS_NON_COPYABLE_H
namespace noobsters {
class non_copyable {
 public:
  non_copyable() = default;
  virtual ~non_copyable() = default;

 public:
  non_copyable(const non_copyable&) = delete;
  non_copyable& operator=(const non_copyable&) = delete;

 public:
  non_copyable(non_copyable&&) = default;
  non_copyable& operator=(non_copyable&&) = default;
};
}  // namespace noobsters
#endif  // WUNDER_NON_COPYABLE_H

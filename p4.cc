#ifndef SMART_POINTERS_HPP
#define SMART_POINTERS_HPP 1

#include <cstddef>
#include <utility>

template <typename T>
class UniquePtr {
  T *ptr_ = nullptr;

public:
  UniquePtr() = default;
  explicit UniquePtr(T *ptr) noexcept : ptr_(ptr) {}

  UniquePtr(const UniquePtr &) = delete;
  UniquePtr &operator=(const UniquePtr &) = delete;

  UniquePtr(UniquePtr &&other) noexcept : ptr_(other.release()) {}

  UniquePtr &operator=(UniquePtr &&other) noexcept {
    if (this != &other)
      reset(other.release());
    return *this;
  }

  ~UniquePtr() { delete ptr_; }

  T &operator*() noexcept { return *ptr_; }
  const T &operator*() const noexcept { return *ptr_; }

  T *operator->() noexcept { return ptr_; }
  const T *operator->() const noexcept { return ptr_; }

  explicit operator bool() const noexcept { return ptr_ != nullptr; }
  T *get() const noexcept { return ptr_; }

  void reset(T *ptr = nullptr) noexcept {
    if (ptr_ != ptr)
      delete std::exchange(ptr_, ptr);
  }

  T *release() noexcept { return std::exchange(ptr_, nullptr); }
};

template <typename T>
class SharedPtr {
  struct ControlBlock {
    T *ptr;
    std::size_t count;
  };

  ControlBlock *control_ = nullptr;

  void release() noexcept {
    if (control_ != nullptr && --control_->count == 0) {
      delete control_->ptr;
      delete control_;
    }
  }

public:
  SharedPtr() = default;

  explicit SharedPtr(T *ptr) {
    if (ptr != nullptr) {
      try {
        control_ = new ControlBlock{ptr, 1};
      } catch (...) {
        delete ptr;
        throw;
      }
    }
  }

  SharedPtr(const SharedPtr &other) noexcept : control_(other.control_) {
    if (control_ != nullptr)
      ++control_->count;
  }

  SharedPtr(SharedPtr &&other) noexcept
      : control_(std::exchange(other.control_, nullptr)) {}

  SharedPtr &operator=(const SharedPtr &other) noexcept {
    SharedPtr copy(other);
    std::swap(control_, copy.control_);
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) noexcept {
    if (this != &other) {
      SharedPtr moved(std::move(other));
      std::swap(control_, moved.control_);
    }
    return *this;
  }

  ~SharedPtr() { release(); }

  T &operator*() noexcept { return *control_->ptr; }
  const T &operator*() const noexcept { return *control_->ptr; }

  T *operator->() noexcept { return get(); }
  const T *operator->() const noexcept { return get(); }

  explicit operator bool() const noexcept { return control_ != nullptr; }

  T *get() const noexcept {
    return control_ == nullptr ? nullptr : control_->ptr;
  }

  std::size_t use_count() const noexcept {
    return control_ == nullptr ? 0 : control_->count;
  }
};

#endif // SMART_POINTERS_HPP

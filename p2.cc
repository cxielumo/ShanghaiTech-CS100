#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

class Dynarray {
  std::size_t size_ = 0;
  int *data_ = nullptr;

public:
  Dynarray() = default;

  explicit Dynarray(std::size_t n)
      : size_(n), data_(n == 0 ? nullptr : new int[n]{}) {}

  Dynarray(std::size_t n, int value) : Dynarray(n) {
    if (!empty())
      std::fill_n(data_, size_, value);
  }

  Dynarray(const int *begin, const int *end)
      : Dynarray(begin == end ? 0 : static_cast<std::size_t>(end - begin)) {
    if (!empty())
      std::copy_n(begin, size_, data_);
  }

  Dynarray(const Dynarray &other) : Dynarray(other.size_) {
    if (!empty())
      std::copy_n(other.data_, size_, data_);
  }

  Dynarray(Dynarray &&other) noexcept
      : size_(std::exchange(other.size_, 0)),
        data_(std::exchange(other.data_, nullptr)) {}

  Dynarray &operator=(const Dynarray &other) {
    if (this != &other)
      *this = Dynarray(other);
    return *this;
  }

  Dynarray &operator=(Dynarray &&other) noexcept {
    if (this != &other) {
      delete[] data_;
      size_ = std::exchange(other.size_, 0);
      data_ = std::exchange(other.data_, nullptr);
    }
    return *this;
  }

  ~Dynarray() { delete[] data_; }

  std::size_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  int &at(std::size_t index) {
    if (index >= size_)
      throw std::out_of_range{"Dynarray index out of range!"};
    return data_[index];
  }

  const int &at(std::size_t index) const {
    if (index >= size_)
      throw std::out_of_range{"Dynarray index out of range!"};
    return data_[index];
  }
};

#endif // DYNARRAY_HPP

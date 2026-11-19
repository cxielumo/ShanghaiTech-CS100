#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <algorithm>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <utility>

class Dynarray {
public:
  using size_type = std::size_t;
  using value_type = int;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;

private:
  size_type size_ = 0;
  pointer data_ = nullptr;

public:
  Dynarray() = default;

  explicit Dynarray(size_type n)
      : size_(n), data_(n == 0 ? nullptr : new value_type[n]{}) {}

  Dynarray(size_type n, value_type value) : Dynarray(n) {
    if (!empty())
      std::fill_n(data_, size_, value);
  }

  Dynarray(const_pointer begin, const_pointer end)
      : Dynarray(begin == end ? 0 : static_cast<size_type>(end - begin)) {
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

  size_type size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  reference at(size_type index) {
    if (index >= size_)
      throw std::out_of_range{"Dynarray index out of range!"};
    return data_[index];
  }

  const_reference at(size_type index) const {
    if (index >= size_)
      throw std::out_of_range{"Dynarray index out of range!"};
    return data_[index];
  }

  reference operator[](size_type index) noexcept { return data_[index]; }

  const_reference operator[](size_type index) const noexcept {
    return data_[index];
  }

  friend bool operator<(const Dynarray &lhs, const Dynarray &rhs) {
    if (lhs.empty() || rhs.empty())
      return lhs.size_ < rhs.size_;
    return std::lexicographical_compare(lhs.data_, lhs.data_ + lhs.size_,
                                        rhs.data_, rhs.data_ + rhs.size_);
  }

  friend bool operator==(const Dynarray &lhs, const Dynarray &rhs) {
    return lhs.size_ == rhs.size_ &&
           (lhs.empty() ||
            std::equal(lhs.data_, lhs.data_ + lhs.size_, rhs.data_));
  }

  friend bool operator<=(const Dynarray &lhs, const Dynarray &rhs) {
    return !(rhs < lhs);
  }

  friend bool operator>(const Dynarray &lhs, const Dynarray &rhs) {
    return rhs < lhs;
  }

  friend bool operator>=(const Dynarray &lhs, const Dynarray &rhs) {
    return !(lhs < rhs);
  }

  friend bool operator!=(const Dynarray &lhs, const Dynarray &rhs) {
    return !(lhs == rhs);
  }

  friend std::ostream &operator<<(std::ostream &out, const Dynarray &array) {
    out << '[';
    for (size_type i = 0; i < array.size_; ++i) {
      if (i != 0)
        out << ", ";
      out << array[i];
    }
    return out << ']';
  }
};

#endif // DYNARRAY_HPP

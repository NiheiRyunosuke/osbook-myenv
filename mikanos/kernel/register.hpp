#pragma once

#include <cstddef>
#include <cstdint>

template <class T>
union DefaultBitmap {
  T data[1];

  operator T() const {
    return data[0];
  }
};

template <class T>
struct MemMapRegister {
  T Read() const {
    T value;
    for (size_t i = 0; i < sizeof(T) / sizeof(T::data[0]); ++i) {
      value.data[i] = value_.data[i];
    }
    return value;
  }

  void Write(const T& value) {
    for (size_t i = 0; i < sizeof(T) / sizeof(T::data[0]); ++i) {
      value_.data[i] = value.data[i];
    }
  }

 private:
  volatile T value_;
};

template <class T>
class ArrayWrapper {
 public:
  ArrayWrapper(uintptr_t base, size_t size)
      : base_{reinterpret_cast<T*>(base)}, size_{size} {
  }

  T& operator[](size_t index) const {
    return base_[index];
  }

  size_t Size() const {
    return size_;
  }

 private:
  T* base_;
  size_t size_;
};

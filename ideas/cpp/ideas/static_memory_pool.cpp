// sandbox_idea: cpp/ideas
// sandbox_name: static_memory_pool
// sandbox_description:
// sandbox_env: cpp

#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <functional>

template <typename T>
class StaticMemoryPool {
  std::array<uint8_t, sizeof(T)> buffer_{};

 public:
  T* allocate() {
      return new (buffer_.data()) T{};
  }

  void deallocate_ptr(T*) {
    deallocate();
  }
  void deallocate() {
    reinterpret_cast<T*>(buffer_.data())->~T();
    buffer_.fill(0x00);
  }
};

struct Test {
  Test() { std::cout << "CTOR" << std::endl; }
  ~Test() { std::cout << "DTOR" << std::endl; }
};

int main(void) { 
  StaticMemoryPool<Test> pool {};

  Test* t = pool.allocate();
  pool.deallocate();

  std::unique_ptr<Test, decltype(&StaticMemoryPool<Test>::deallocate)> ptr {pool.allocate(), std::bind(pool, &StaticMemoryPool<Test>::deallocate_ptr, std::placeholders::_1)};
  return 0;
}

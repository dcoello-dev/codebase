// sandbox_idea: cpp/ideas
// sandbox_name: fixed_string_allocator
// sandbox_description:
// sandbox_env: cpp

#include <array>
#include <iostream>
#include <string>
#include <string.h>

template <typename T, size_t N>
struct Buffer {
  T *buffer() { return static_cast<T *>(buffer_.data()); }
  size_t max_size() { return N * sizeof(T); }

 private:
  std::array<T, N> buffer_{};
};

template <size_t N>
struct Arena {
  template <class T>
  struct Allocator : private Buffer<T, N> {
    typedef T value_type;
    typedef size_t size_type;
    const static size_t buffer_size = N;

    Allocator() = default;

    template <class U>
    constexpr Allocator(const Allocator<U> &) noexcept {}

    T * allocate(std::size_t n) {
      T *ret = this->buffer();
      if (n > this->max_size()) {
        std::abort();
      }
      report(ret, n);
      return ret;
    }

    void deallocate(T *p, std::size_t n) noexcept {
      report(p, n, 0);
    }

    // size_type max_size() const noexcept {
    //   std::cout << N << " " << sizeof(T) << std::endl;
    //   return N * sizeof(T);
    // }

   private:
    void report(T *p, std::size_t n, bool alloc = true) const {
      std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
                << " bytes at " << std::hex << std::showbase
                << reinterpret_cast<void *>(p) << std::dec << "max size " << buffer_size << '\n';
    }
    T *dynamic_ptr = nullptr;
  };
};

template<size_t N>
using FixedString = std::basic_string<char, std::char_traits<char>, typename Arena<N>::template Allocator<char>>;

using Token = FixedString<256>;

template<typename F, typename T>
static bool safe_asignation(F & cls, const T& other) noexcept {
  return safe_asignation(cls, other.c_str());
}

template<typename F>
static bool safe_asignation(F & cls, const char* other) noexcept {
  bool ret = false;
  if (strlen(other) <= F::basic_string::allocator_type::buffer_size) {
    cls = other;
    ret = true;
  }
  return ret;
} 

int main() {
  // std::basic_string<char, std::char_traits<char>,
  //                   Arena<1000>::Allocator<char>>
  //     str;
  // for (int i = 0; i < 1000; i++) {
  //   str.push_back('a');
  // }
  // std::cout << str << std::endl;
  // str = "hello sakjflksajdflkjsalkfjd sldjflsjkfdlsjflsdkj";
  // std::cout << str << std::endl;
  Token m {};
  Token k {"HOLA"};
  std::cout << m << std::endl;
  std::cout << k << std::endl;
  std::cout << m.max_size() << std::endl;
  safe_asignation(m,"sdlkfjslfdjs");
  std::cout << m << std::endl;
  std::string a (26, '.');
  std::cout << a << std::endl;
   m = a.c_str();
  // safe_asignation(m,a);
  std::cout << m << std::endl;
  std::cout << k << std::endl;


  
}

// sandbox_idea: cpp/ideas
// sandbox_name: ret_value
// sandbox_description:
// sandbox_env: cpp

#include <cassert>
#include <iostream>
#include <utility>

template <typename T> class Functor {
public:
  static bool condition(const T &) { return true; }
};

template <typename T, typename F = Functor<T>> class RetValue {
public:
  using InnerType = T;
  RetValue(T &&value) noexcept
      : mValue(std::forward<T>(value)), mStatus(F::condition(value)) {}

  RetValue() noexcept : mValue(), mStatus(false) {}

  ~RetValue() noexcept { assert(mObserved); }

  RetValue(const RetValue &cls) = default;
  RetValue &operator=(const RetValue &cls) = default;
  RetValue(RetValue &&cls) = default;
  RetValue &operator=(RetValue &&cls) = default;

  explicit operator bool() noexcept {
    mObserved = true;
    return mStatus;
  }

  operator T() noexcept {
    mObserved = true;
    return mValue;
  }

  bool operator==(const T &other) noexcept {
    mObserved = true;
    return mValue == other;
  }

  void operator=(const T &other) noexcept {
    mValue = other;
    mStatus = F::condition(other);
    mObserved = false;
  }

private:
  T mValue;
  bool mStatus;
  bool mObserved = false;
};

enum RETCODES { OK, ERROR, TIMEOUT };

class RetCodeCondition {
public:
  static bool condition(const RETCODES &code) { return (code == OK); }
};

template <typename T, T min, T max> class RangeCondition {
public:
  static bool condition(const T &val) { return val <= max && val >= min; }
};

template <typename T, T min, T max>
using RangeValue = RetValue<T, RangeCondition<T, min, max>>;

using SpeedValue = RangeValue<int, 0, 400>;

template<class...>
using void_t = void;

template<class T, class = void_t<>>
struct is_ret_value :std::false_type {
  static const bool value = false;
  template<typename I>
  using type = I;
};

template<class T>
struct is_ret_value<T, void_t<typename T::InnerType>>: std::true_type {
  static const bool value = true;
  template<typename I>
  using type = I&;
};

/// functions that can only be use with RetValues
template <typename T, bool is_ret = is_ret_value<T>::value> 
typename std::enable_if<is_ret, bool>::type enable_if_ret_val(T & value) noexcept {
  if (value){
    std::cout << "value is correct" << std::endl;
  } else {
    std::cout << "value is incorrect" << std::endl;
  }
  return true;
}

template <typename T>
bool use_inner_or_ret(typename is_ret_value<T>::template type<SpeedValue> value) noexcept {
  if (value){
    std::cout << "value is correct" << std::endl;
  } else {
    std::cout << "value is incorrect" << std::endl;
  }
  return true;
}

int main(void) {
  
  // enable_if_ret_val(500);
  SpeedValue speed_value{100};
  enable_if_ret_val<SpeedValue>(speed_value);
  use_inner_or_ret<decltype(speed_value)>(speed_value);
  use_inner_or_ret<decltype(501)>(501);

  RetValue<int> value{1};
  if (value) {
    std::cout << "is correct" << std::endl;
  }
  RetValue<int> value2{};
  if (!value2) {
    std::cout << "it is not correct" << std::endl;
  }
  value2 = 4;
  if (value2) {
    std::cout << "is correct" << std::endl;
  }

  RetValue<RETCODES, RetCodeCondition> value3{ERROR};
  if (!value3) {
    std::cout << "retcode not correct" << std::endl;
  }

  switch (value3) {
  case ERROR:
    std::cout << "ERROR" << std::endl;
    break;
  case OK:
    std::cout << "OK" << std::endl;
    break;
  case TIMEOUT:
    std::cout << "TIMEOUT" << std::endl;
    break;
  }

  RangeValue<int, 0, 10> range_value{0};

  if (range_value) {
    std::cout << "range valid" << std::endl;
  }

  range_value = 11;

  if (!range_value) {
    std::cout << "range invalid" << std::endl;
  }

  return 0;
}

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

int main(void) {
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

// sandbox_idea: cpp/basics
// sandbox_name: enum_types
// sandbox_description: enum types in cpp
// sandbox_env: cpp

#include <iostream>

// old type enum
enum OldEnum { FIRST = 1, LAST = 9999999999999999 };

// enum class to do not inject names on global namespace
enum class ClassEnum { FIRST = 1, LAST = 200 };

// typed enum
enum class TypedEnum : uint32_t { FIRST = 100, LAST = 99 };

int main(void) {
  std::cout << "old type " << static_cast<uint32_t>(LAST) << std::endl;
  std::cout << "class enum " << static_cast<uint32_t>(ClassEnum::LAST)
            << std::endl;
  std::cout << "typed enum " << static_cast<uint32_t>(TypedEnum::LAST)
            << std::endl;
  return 0;
}

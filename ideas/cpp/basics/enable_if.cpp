// sandbox_idea: cpp/basics
// sandbox_name: enable_if
// sandbox_description:
// sandbox_env: cpp

#include <iostream>
#include <type_traits>

// SFINAE
template<typename T>
typename std::enable_if_t<!std::is_signed<T>::value, bool> increase(T& index) noexcept {
    bool ret = false;
    if (index < static_cast<T>(T{0} - 1)) {
        index++;
        ret = true;
    }
    return ret;
}

int main(void) {
    uint8_t i1 = 255;
    auto val = increase(i1);
    std::cout << val << " " << static_cast<uint32_t>(i1) << std::endl;


    uint16_t i2 = 0xFFF0;
    auto val2 = increase(i2);
    std::cout << val2 << " " << static_cast<uint32_t>(i2) << std::endl;
    return 0;
}

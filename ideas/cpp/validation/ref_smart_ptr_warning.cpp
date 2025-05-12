// sandbox_idea: cpp/validation
// sandbox_name: ref_smart_ptr_warning
// sandbox_description: possible seg fault with unique ptr ref
// sandbox_env: cpp

#include <iostream>
#include <memory>

static std::unique_ptr<int> ret = nullptr;

std::unique_ptr<int>& foo() {
     ret = std::make_unique<int>(4);
    return ret;
}

int main(void) {
    // foo().release() ;
    std::unique_ptr<int>& ref = foo();
    foo().release() ;
    if (ref == nullptr){
        std::cout << "no lo pilla"  << std::endl;
        std::cout << "Hello World! " << *ref << std::endl;
    }
    return 0;
}

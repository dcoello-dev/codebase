// sandbox_idea: cpp/basics
// sandbox_name: multi_template_inheritance
// sandbox_description: inherit twice from same template interface
// sandbox_env: cpp

#include <iostream>

template <class I, class O> struct IInterface {
  virtual bool method(const I &input, O &output) = 0;
};

struct Implementation : public IInterface<int, float>,
                        public IInterface<float, int> {
  bool method(const int &input, float &output) { return true; }
  bool method(const float &input, int &output) { return false; }
};

void foo(IInterface<int, float> &i) {
  float f = 1.1;
  if (i.method(1, f)) {
    std::cout << "int float" << std::endl;
  }
}

void bar(IInterface<float, int> &i) {
  int integer = 1;
  float f = 1.1;
  if (!i.method(f, integer)) {
    std::cout << "float int" << std::endl;
  }
}

int main(void) {
  Implementation i{};
  foo(i);
  bar(i);
  return 0;
}

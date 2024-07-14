// sandbox_idea: arq/basics
// sandbox_name: scope
// sandbox_description: scope examples
// sandbox_env: cpp

#include <iostream>

struct Scope {
  Scope(std::string name) : name_(name) {
    std::cout << "START " << name_ << std::endl;
  }
  ~Scope() { std::cout << "STOP " << name_ << std::endl; }

private:
  std::string name_;
};

void normal_fnc() { Scope fn{"normal_fnc"}; }
void nested_fnc_2() { Scope fn{"nested_fnc_2"}; }
void nested_fnc_1() {
  Scope fn{"nested_fnc_1"};
  nested_fnc_2();
}
void reference_fnc(const Scope &sc) { Scope fn{"reference_fnc"}; }

int main(void) {
  Scope m{"main"};
  { Scope i{"inner"}; }
  normal_fnc();
  nested_fnc_1();
  reference_fnc(m);
  return 0;
}

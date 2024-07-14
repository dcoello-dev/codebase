// sandbox_idea: arq/basics
// sandbox_name: ownership
// sandbox_description: ownership examples
// sandbox_env: cpp

#include <iostream>

struct NaiveResource {
  NaiveResource(int val) { inner_ = new int(val); }
  ~NaiveResource() { delete inner_; }

  int get_val() { return *inner_; }

private:
  int *inner_ = nullptr;
};

int main(void) {
  NaiveResource resource{10};
  std::cout << resource.get_val() << std::endl;
  return 0;
}

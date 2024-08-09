// sandbox_idea: cpp/validation
// sandbox_name: aggregated_ut_data_gen
// sandbox_description: how to create data and compare on aggregated POCs
// sandbox_env: cpp

#include <cassert>
#include <cstring>

struct Element {
  int a;
  int b;
};

struct AggregateOfElements {
  Element elements[100];
};

int main(void) {
  AggregateOfElements elements{};
  for (int i = 0; i < sizeof(elements.elements) / sizeof(Element); i++) {
    char val = static_cast<char>(i);
    memset(&elements.elements[i], val, sizeof(Element));
  }

  for (int i = 0; i < sizeof(elements.elements) / sizeof(Element); i++) {
    char val = static_cast<char>(i);
    Element to_compare{};
    memset(&to_compare, val, sizeof(Element));
    assert(memcmp(&to_compare, &elements.elements[i], sizeof(Element)) == 0);
  }

  return 0;
}

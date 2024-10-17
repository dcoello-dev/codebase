# sandbox_idea: python/basics
# sandbox_name: regex_example
# sandbox_description: small regex examples
# sandbox_env: python

import re

if __name__ == "__main__":
    input_cpp = """// sandbox_idea:
// sandbox_name:
// sandbox_description:
// sandbox_env: cpp

#include <iostream>

int main(void) {
    std::cout << "Hello World!" << std::endl;
    return 0;
}
"""
    input_python = """# sandbox_idea:
# sandbox_name:
# sandbox_description:
# sandbox_env: python

if __name__ == "__main__":
    print("Hello World!")
"""

    input_markdown = """[//]: # (sandbox_idea: )
[//]: # (sandbox_name: )
[//]: # (sandbox_description: )
[//]: # (sandbox_env: markdown)

# IDEA
"""

    matcher = r"(sandbox_[a-z]+):\s*([a-z]*)"

    print(re.findall(matcher, input_cpp))
    print(re.findall(matcher, input_python))
    print(re.findall(matcher, input_markdown))

# sandbox_idea: regex/
# sandbox_name: cpp_compilation_error
# sandbox_description: regex to capture cpp compilation errors
# sandbox_env: regex

import re
import json

INPUT_TEXT = """
[ 50%] Building CXX object CMakeFiles/MyExample.dir/main.cpp.o
/home/dcoello/code/link/example/main.cpp: In function ‘int main()’:
/home/dcoello/code/link/example/main.cpp:4:14: error: ‘cut’ is not a member of ‘std’; did you mean ‘cout’?
    4 |         std::cut << "hello" << std::endl;
      |              ^~~
      |              cout
make[2]: *** [CMakeFiles/MyExample.dir/build.make:76: CMakeFiles/MyExample.dir/main.cpp.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:83: CMakeFiles/MyExample.dir/all] Error 2
make: *** [Makefile:91: all] Error 2
"""

INPUT_REGEX = r"(.*):(\d*):(\d*): error:(.*\n)"

if __name__ == "__main__":
    print(json.dumps(list(re.findall(INPUT_REGEX, INPUT_TEXT)), indent=2))

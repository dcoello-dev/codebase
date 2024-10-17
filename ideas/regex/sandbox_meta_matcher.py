# sandbox_idea: regex/
# sandbox_name: sandbox_meta_matcher
# sandbox_description: regex to match meta sandbox meta values
# sandbox_env: regex

import re
import json

INPUT_TEXT = """
// sandbox_idea: python/basics/coro
# sandbox_idea: regex/
# sandbox_name: sandbox_meta_matcher
# sandbox_description: regex to match meta sandbox meta values
# sandbox_env: regex
"""

INPUT_REGEX = r"(sandbox_[a-z]+):\s*(([a-z]*/*_*-* *)*)"

if __name__ == "__main__":
    print(json.dumps(list(re.findall(INPUT_REGEX, INPUT_TEXT)), indent=2))

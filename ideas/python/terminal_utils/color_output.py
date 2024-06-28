# sandbox_idea: python/terminal_utils
# sandbox_name: color_output
# sandbox_description: how to color terminal output
# sandbox_env: python

class CLIFormat:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    ORANGE = '\033[93m'
    RED = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    BACKSPACE = '\x08'

    @staticmethod
    def colored(str: str, color: str) -> str:
        return color + str + CLIFormat.ENDC

if __name__ == "__main__":
    print(CLIFormat.colored("hello world!", CLIFormat.GREEN))
    print(CLIFormat.colored("hello world!", CLIFormat.RED + CLIFormat.BOLD))

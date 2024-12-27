# sandbox_idea: global/setup
# sandbox_name: install_zig
# sandbox_description: install zig compiler
# sandbox_env: bash

sudo bash -c "$(curl -fsSL https://pacstall.dev/q/install)" && /usr/bin/pacstall -I zig-bin

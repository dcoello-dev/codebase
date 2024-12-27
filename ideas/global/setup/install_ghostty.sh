# sandbox_idea: global/setup
# sandbox_name: install_ghostty
# sandbox_description: install ghostty
# sandbox_env: bash

echo("be sure you already have zig installed")
sudo apt install libgtk-4-dev
sudo apt install libadwaita-1-dev

git clone https://github.com/ghostty-org/ghostty.git && cd ghostty && git checkout v1.0.0

zig build -p $HOME/.local -Doptimize=ReleaseFast

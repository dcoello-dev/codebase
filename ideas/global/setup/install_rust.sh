# sandbox_idea: global/setup
# sandbox_name: install_rust
# sandbox_description: install rust environment
# sandbox_env: bash

sudo curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

rustup override set stable
rustup update stable

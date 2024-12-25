# sandbox_idea: global/setup
# sandbox_name: install_tmux_tpm
# sandbox_description: tmux tpm install and conf
# sandbox_env: bash

sudo apt install -y tmux

git clone https://github.com/tmux-plugins/tpm ~/.tmux/plugins/tpm

echo("to install plugins run prefix + I")

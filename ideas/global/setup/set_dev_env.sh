# sandbox_idea: global/setup
# sandbox_name: set_dev_env
# sandbox_description: install and configure dev environment
# sandbox_env: bash

mkdir -p ~/doc/
mkdir -p ~/code/
mkdir -p ~/tools/

cd ~/tools

git clone --recursive --depth 1 --shallow-submodules https://github.com/akinomyoga/ble.sh.git
make -C ble.sh install PREFIX=~/.local

cd ~/doc/

gh repo clone dcoello-dev/dotfiles
cd dotfiles

rm ${HOME}/.bashrc
ln -s ${HOME}/doc/dotfiles/.bashrc ${HOME}/.bashrc
rm ${HOME}/.gitconfig
ln -s ${HOME}/doc/dotfiles/.gitconfig ${HOME}/.gitconfig

ln -s ${HOME}/doc/dotfiles/.config/tmux ${HOME}/.config/tmux
ln -s ${HOME}/doc/dotfiles/.config/bash ${HOME}/.config/bash
ln -s ${HOME}/doc/dotfiles/.config/blesh ${HOME}/.config/blesh
ln -s ${HOME}/doc/dotfiles/.config/git ${HOME}/.config/git
ln -s ${HOME}/doc/dotfiles/.config/i3 ${HOME}/.config/i3

cd ~/.config/ && gh repo clone dcoello-dev/nvim-conf.nvim nvim

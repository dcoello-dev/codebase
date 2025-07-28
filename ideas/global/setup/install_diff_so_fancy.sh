# sandbox_idea: global/setup
# sandbox_name: install_diff_so_fancy
# sandbox_description: install diff so fancy
# sandbox_env: bash

sudo add-apt-repository ppa:aos1/diff-so-fancy
sudo apt update
sudo apt install y diff-so-fancy

git config --global core.pager "diff-so-fancy | less --tabs=4 -RF"
git config --global interactive.diffFilter "diff-so-fancy --patch"

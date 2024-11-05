# sandbox_idea: global/setup
# sandbox_name: install_rgf
# sandbox_description: install rgf tool
# sandbox_env: bash

set -e

mkdir -p ~/tools/ && cd ~/tools

gh repo clone dcoello-dev/remote_gitlab_friend

cd remote_gitlab_friend

python3 -m build

pip install dist/*.whl --force-reinstall

echo "export GITLAB_API_TOKEN=\"\"" >> .bashrc

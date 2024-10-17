# sandbox_idea: global/setup
# sandbox_name: install_node
# sandbox_description: install node and npm
# sandbox_env: bash

sudo apt-get update
sudo apt install curl

# check nodesource for latest version
curl -fsSL https://deb.nodesource./setup_20.x | sudo bash -

sudo apt-get install nodejs

nodejs -v
npm -v

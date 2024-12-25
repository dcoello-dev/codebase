# sandbox_idea: global/setup
# sandbox_name: install_node
# sandbox_description: install node and npm
# sandbox_env: bash

# installs fnm (Fast Node Manager)
curl -fsSL https://fnm.vercel.app/install | bash

# activate fnm
source ~/.bashrc

# download and install Node.js
fnm use --install-if-missing 23

# verifies the right Node.js version is in the environment
node -v # should print `v23.1.0`

# verifies the right npm version is in the environment
npm -v # should print `10.9.0`

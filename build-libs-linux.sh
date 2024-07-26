#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Update package list
sudo apt-get update

# Install SDL2 and GLFW
sudo apt-get install -y libsdl2-dev libglfw3-dev

# Create a directory for building libraries
mkdir -p libs
cd libs

# Function to clone and install a library
install_from_git() {
  local repo_url=$1
  local repo_name=$(basename "$repo_url" .git)

  git clone "$repo_url"
  cd "$repo_name"
  mkdir build
  cd build
  cmake ..
  make
  sudo make install
  cd ../../
}

# Install GLAD
install_from_git https://github.com/Dav1dde/glad.git

# Install spdlog
install_from_git https://github.com/gabime/spdlog.git

echo "All libraries have been installed successfully!"

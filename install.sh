#!/bin/bash
set -e

echo "=== NiriFluidPaper Installer ==="

# Check dependencies
command -v meson >/dev/null 2>&1 || { echo "meson required"; exit 1; }
command -v ninja >/dev/null 2>&1 || { echo "ninja required"; exit 1; }

# Build
echo "Building..."
meson setup build
ninja -C build

# Install
echo "Installing..."
sudo ninja -C build install

echo ""
echo "=== Installation Complete ==="
echo ""
echo "Add to ~/.config/niri/config.kdl:"
echo ""
echo "spawn-at-startup \"nirifluidpaper\""
echo ""
echo "layer-rule {"
echo "    match namespace=\"nirifluidpaper\""
echo "    place-within-backdrop true"
echo "}"
echo ""
echo "layout {"
echo "    background-color \"transparent\""
echo "}"
echo ""
echo "Then run: niri msg action reload-config"

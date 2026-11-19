#!/usr/bin/env bash
set -eo pipefail

# Load the user's Geant4 and FLUKA settings from ~/.bashrc in a login shell.
if [[ -f "$HOME/.bashrc" ]]; then
  source "$HOME/.bashrc"
  set -u
fi

: "${G4COMP:?G4COMP is not set; check the Geant4 section in ~/.bashrc}"
: "${FLUPRO:?FLUPRO is not set; check the FLUKA section in ~/.bashrc}"

src_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
build_dir="$src_dir/build-fluka"

cmake -S "$src_dir" -B "$build_dir" \
  -DGeant4_DIR="$G4COMP" \
  -DG4_USE_FLUKA=ON \
  -DWITH_GEANT4_UIVIS=ON
cmake --build "$build_dir" --parallel "$(sysctl -n hw.ncpu 2>/dev/null || getconf _NPROCESSORS_ONLN)"

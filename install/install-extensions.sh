#!/usr/bin/env bash
set -euo pipefail

extensions=(
    # C++
    llvm-vs-code-extensions.vscode-clangd
    ms-vscode.cpptools-extension-pack

    # Misc
    mechatroner.rainbow-csv

    # Python
    ms-python.python
    ms-python.vscode-pylance
    ms-python.black-formatter

    # Jupyter
    ms-toolsai.jupyter
    ms-toolsai.jupyter-keymap
    ms-toolsai.jupyter-renderers
    ms-toolsai.vscode-jupyter-cell-tags
    ms-toolsai.vscode-jupyter-slideshow
)

for ext in "${extensions[@]}"; do
    code --install-extension "$ext"
done

# VSCode setup for competitive programming (Linux)

Setup instructions for getting a fresh Linux box ready for contest writing in VSCode with C++. Clone this repo and use it directly as your contests workspace.

Examples below assume Debian/Ubuntu (`apt`); adapt for your distro.

## 1. Install system tools

```sh
sudo apt update
sudo apt install -y build-essential gdb     # gcc, g++, make, gdb
sudo apt install -y clangd clang-format     # LSP + formatter (we compile with g++)
sudo apt install -y git curl
sudo apt install -y fonts-hack              # terminal font (or any monospace you like)
```

If `clangd`/`clang-format` aren't found, look for versioned packages (`clangd-18`, `clang-format-18`) and either install them and update the paths in `.vscode/settings.json`, or symlink them as `/usr/bin/clangd` and `/usr/bin/clang-format`.

To raise the stack limit (deep recursion otherwise crashes), append to `~/.bashrc` / `~/.zshrc`:

```sh
ulimit -s unlimited
```

## 2. Install extensions

```sh
./install/install-extensions.sh
```

The script installs:

- **clangd** — C++ language server (the C++ workflow uses clangd, not the Microsoft IntelliSense engine; `C_Cpp.intelliSenseEngine` is `disabled` in workspace settings).
- **C/C++ Extension Pack** (`ms-vscode.cpptools-extension-pack`) — provides the `cppdbg` debugger used by `launch.json` (gdb backend) plus C++ themes.
- **Rainbow CSV** — for inspecting tabular test data.
- **Python** + **Pylance** + **Black formatter** — for utility scripts / brute-force checkers.
- **Jupyter** (+ keymap, renderers, cell-tags, slideshow) — notebook support.

## 3. Install keybindings

VSCode doesn't support per-workspace keybindings, so this is the one file that must be copied to your user config:

```sh
mkdir -p "$HOME/.config/Code/User"
cp install/keybindings.json "$HOME/.config/Code/User/keybindings.json"
```

What's in there:
- `Ctrl+Tab` / `Ctrl+Shift+Tab` cycle editors in group.
- `Ctrl+R` runs the **Run with input** task (binary fed from `<file>.in`).
- `Shift+Enter` in the integrated terminal sends `\<newline>` so you can keep typing multiline input.

## 4. Open the workspace

```sh
code .
```

Everything else is workspace-local — clangd, formatter, build tasks, debug config, file associations all come from the checked-in `.vscode/`, `.clangd`, and `.clang-format`.

### Per-contest directories

Inside this workspace I keep one subdirectory per contest (e.g. `ucup4/260103/`), each containing the problem `.cpp` files plus their `.in` test files. The tasks all use `${fileDirname}` so building/running always happens inside the problem's own directory — no cross-contamination.

### What the workspace gives you

- **`.clangd`** — `-std=c++20 -DBZ -Wall -Werror -Wextra -Wno-unused-result -Wno-sign-compare`, unused-includes diagnostics off. The `-DBZ` macro disables the `#pragma GCC optimize "-O3"` at the top of templates so the language server doesn't choke on it.
- **`.clang-format`** — LLVM style with `ColumnLimit: 0` (no auto-wrapping; format-on-save won't reflow long lines).
- **`.vscode/settings.json`** — clangd path, clang-format path, `editor.formatOnSave`, tab size 2, Hack monospace in the integrated terminal, `git.defaultBranchName = master`, `*.in` / `*.out` associated with `plaintext`.
- **`.vscode/tasks.json`** — five build tasks, all compile `${file}` to `${fileDirname}/${fileBasenameNoExtension}`:
  - **Release** — `g++ -O3`
  - **Debug** — `g++ -g`
  - **Sanitize** *(default build task)* — `g++ -g -fsanitize=address,undefined`
  - **G++ debug** — `g++ -g -D_GLIBCXX_DEBUG` (catches STL misuse the sanitizers miss)
  - **Run with input** — runs `./<name> < <name>.in` from the file's directory (bound to `Ctrl+R`)
- **`.vscode/launch.json`** — `cppdbg` (gdb) launch config that pre-builds with the **Sanitize** task and feeds `<basename>.in` as stdin via `set args < <basename>.in`.
- **`template.cpp`** / **`mt.cpp`** — single-test and multi-test skeletons in the workspace root; copy into a contest subdir to start a problem.

## 5. Quick sanity check

1. Open `template.cpp`.
2. `Ctrl+Shift+B` → pick **Sanitize** → should produce `template` next to the source.
3. Create `template.in` with sample input.
4. `Ctrl+R` → runs the binary with that input.
5. `F5` → debugs with gdb (rebuilds with Sanitize first).

## Layout of this repo

```
vscode_setup/
├── README.md
├── .clang-format            # workspace
├── .clangd                  # workspace
├── .vscode/
│   ├── settings.json        # workspace + user-style settings, merged
│   ├── tasks.json
│   └── launch.json
├── install/
│   ├── install-extensions.sh
│   └── keybindings.json     # → ~/.config/Code/User/keybindings.json
├── template.cpp             # single-test-case skeleton
└── mt.cpp                   # multi-test-case skeleton (reads tt, calls solve())
```

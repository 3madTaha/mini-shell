# Mini Shell – Operating Systems Course Project

This project was developed as part of the Operating Systems course at Braude College, and received a perfect score (55/55).  
It simulates a basic Unix shell system, split into modular components, using low-level Linux system calls.

## 🧠 Project Overview

The main shell interface (`shell.c`) allows users to select one of three sub-shells:

- `shell1`: Executes basic Linux commands without parameters (e.g., `date`, `clear`, `ls`).
- `shell2`: Executes commands **with parameters** (e.g., `grep -c Hello a.txt`, `ls -l`).
- `shell3`: Performs **file-related operations**, including:
  - `Merge` two or three files
  - `Size` of a file (count characters)
  - `Delete` a file

Each shell includes a custom prompt (`Shell1$`, `Shell2$`, etc.) and supports `Esc` to return to the main shell menu.

---

## 🧰 Technologies Used

- Language: C
- System Calls: `fork()`, `execvp()`, `open()`, `read()`, `write()`, `unlink()`
- OS: Ubuntu Linux
- Compilation: `gcc`

---

## 🚀 How to Compile

```bash
gcc shell1.c -o shell1
gcc shell2.c -o shell2
gcc shell3.c -o shell3
gcc shell.c -o shell

Or use the provided script:

chmod +x Sys_shell.sh
./Sys_shell.sh

# tasosh
Tasosh is a simple shell made for test and play purposes. The word `tasosh` is an acronym for "Tiny Adaptable Simple Open SHell", as the program tries to be lightweight, easy to configure, relatively easy in use & development, and being open source.

# Installation
To install the program, either download the binary from the GitHub releases, or build it from source. Here is how to build it from source:

1. Copy the project's codebase with git:
```bash
git clone https://github.com/fif3x/tasosh
```
2. Give possible permissions to the file `build.sh` in the folder `build/`:
```bash
chmod +x build/build.sh
```
3. Run the script `build/build.sh`:
```bash
./build/build.sh
```

you can also use the `-dbg` flag when running the build script, and it will launchthe program immediately after building it and some more things that can help with development

4. Run  either `tasosh` in your command line if you used sudo in the script, or run `bin/tasosh` if you didnt.

# Development
To develop this program further or build it from source, you need `g++`, `make`, `git`, and if you use clangd, you need `bear` and run it with `bear -- make`
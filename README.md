# Open Stronghold Crusader

WIP Open Source Stornghold Crusader clone

## Demo

[Web Demo](https://adsgames.github.io/open-shc/)

## Setup

### Assets

Copy your entire Stronghold Crusader folder to `assets/proprietary/`

### Windows (MSYS2)

```bash
pacman -S mingw-w64-i686-gcc-libs mingw-w64-i686-SDL2 mingw-w64-i686-SDL2_mixer mingw-w64-i686-SDL2_image mingw-w64-i686-SDL2_ttf
```

### Mac OS

```bash
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer
```

### Linux

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

### Build

#### With VSCode

Install the [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension

Use `Shift+F5` to build and run

#### CLI

```bash
mkdir build
cd build
cmake ..
make
```

#### CLI Emscripten

```bash
mkdir build
cd build
emcmake cmake ..
make
```

# audacious-plugin-sort
Sort by file modified date in audacious player

# Install

1.Install audacious:

Arch:
```
sudo pacman -S audacious
```
Instructions for other: https://audacious-media-player.org/download

2.Install Qt5

Arch:
```
sudo pacman -S qt5-base
```
3.Install Plugin:
```
git clone https://github.com/Mykhail024/audacious-plugin-sort.git
cd audacious-plugin-sort
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
```

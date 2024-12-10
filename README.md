![Build status](https://github.com/xavierbasc/dmos/actions/workflows/build.yml/badge.svg)

# DM50 Operative System

# Prerequisites

- gcc
- make
- cmake
- git
- create-dmg (macos: brew install create-dmg)

# Download repository

[Download the latest compiled version](/releases)

```shell
git clone https://github.com/xavierbasc/DMOS.git`
```

# External libraries

SDL2: used for rendering on Windows, MacOS and Linux systems

To download the external repositories and compile the necessary static libraries, run the following command:

```shell
make external
```

# DMOS compilation

```shell
make
```

```shell
make PLATFORM=macos
```



# Tools

## Create image include

```shell
xxd -i dm50_skin.png > dm50_skin.h
```

# Windows, MacOS and Linux

## Skins

DM50 APP comes with one built-in skin, but you can use different ones by placing them in the directory:

macos:
```shell
$HOME/Library/Application Support/DM50
```

windows:
```shell
dm50.exe directory
```

skins:
  dm50.png
  dm50.layout

layout file:

  x1,y1: top_left x2,y2: bottom_right colors: RRGGBB

They will immediately appear in the Skins menu.

## "ldd" Utility - List Dynamic-Link Libraries

The utility "ldd" examines dm50 executable and displays a list of the shared libraries:

```shell
ldd ./dm50/bin/linux/dm50
```


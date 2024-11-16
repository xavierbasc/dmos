# DM50 Operative System

# Prerequisites

- gcc
- make
- cmake
- git

# Download repository

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


# Tools

## Create image include

```shell
xxd -i dm50_skin.png > dm50_skin.h
```


## "ldd" Utility - List Dynamic-Link Libraries

The utility "ldd" examines dm50 executable and displays a list of the shared libraries:

```shell
ldd ./dm50/bin/linux/dm50
```

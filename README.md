# DM50 Operative System

# Prerequisites

- gcc
- make
- cmake
- git

# Download repository

`git clone https://github.com/xavierbasc/DMOS.git`

# External libraries

SDL2: used for rendering on Windows, MacOS and Linux systems

To download the external repositories and compile the necessary static libraries, run the following command:

`make external`

# DMOS compilation

`make`


# Tools

## Create image include

```shell
xxd -i dm50_skin.png > dm50_skin.h
```

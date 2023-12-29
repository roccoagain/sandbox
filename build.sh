#!/opt/homebrew/bin/zsh

gcc-13 main.c -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework IOKit -framework Cocoa -framework OpenGL

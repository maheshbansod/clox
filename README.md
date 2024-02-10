# clox
Lox in C

## Requirements
This project uses [just](https://github.com/casey/just).  
If you don't have that, you can check the `Justfile` and run the appropriate command directly.  

This project was developed with clang, though gcc should work fine too.
Use `just build` to build the project, the executable is found at `./target/clox`.  
Run `just --list` to see the supported operations.

## Running
This command will build and run the project.
```
just run [args]
```

## LICENSE
MIT

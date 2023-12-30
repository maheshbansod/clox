alias b := build

SOURCES := `echo $(find . -type f -name "*.c")`
CC := 'clang'

build:
	@mkdir -p target
	{{CC}} {{SOURCES}} -o target/clox

run: build
	./target/clox

alias b := build

SOURCES := `echo $(find . -type f -name "*.c")`

build:
	@mkdir -p target
	clang {{SOURCES}} -o target/clox

run: build
	./target/clox

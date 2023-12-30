alias b := build

build:
	@mkdir -p target
	clang *.c -o target/clox

run:
	./target/clox

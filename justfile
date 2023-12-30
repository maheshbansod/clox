alias b := build

build:
	@mkdir -p target
	clang ./src/*.c -o target/clox

run: build
	./target/clox

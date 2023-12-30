alias b := build

build:
	@mkdir -p target
	cc *.c -o target/clox

run:
	./target/clox

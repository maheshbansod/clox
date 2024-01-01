alias b := build

SOURCES := `echo $(find . -type f -name "*.c")`
CC := 'clang'
DEBUG_BUILD_PARAMS := '-g'

build params='':
	@mkdir -p target
	{{CC}} {{params}} {{SOURCES}} -o target/clox

run args='': build
	./target/clox {{args}}

debug args='': (build '-g')
	gdb ./target/clox

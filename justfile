alias b := build

# can be configured based on user's system / preferences
CC := 'clang'
BUILD_PARAMS := '-Wall'
DEBUG_BUILD_PARAMS := '-g'

SOURCES := `echo $(find . -type f -name "*.c")`

build params='':
	@mkdir -p target
	{{CC}} {{BUILD_PARAMS}} {{params}} {{SOURCES}} -o target/clox

run args='': build
	./target/clox {{args}}

debug args='': (build '-g')
	gdb ./target/clox

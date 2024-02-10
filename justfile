# can be configured based on user's system / preferences
CC := 'clang'
BUILD_PARAMS := '-Wall'
DEBUG_BUILD_PARAMS := '-g'

SOURCES := `echo $(find . -type f -name "*.c")`

# build the project
build params='':
	@mkdir -p target
	{{CC}} {{BUILD_PARAMS}} {{params}} {{SOURCES}} -o target/clox

# run after building
run args='': build
	./target/clox {{args}}

run-log args='': (build '-DENABLE_DEBUG_CLOX')
	./target/clox {{args}}

# debug (after build)
debug args='': (build '-g')
	gdb ./target/clox

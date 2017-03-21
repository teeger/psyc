SHELL=/bin/bash
CC=gcc

default: all

.PHONY: clean

demo:
	cd src/demo/ && make all
neural_cli:
	cd src && make all
test:
	cd src/test && make all
profile:
	cd src/debug && make all
clean:
	if ! [ -e tmp/ ]; then mkdir tmp/; fi
	if [ -e bin/README ]; then cp bin/README tmp/; fi
	rm -f src/*.o
	rm -f src/demo/*.o
	rm -f src/test/*.o
	rm -f bin/*
	if [ -e tmp/README ]; then cp tmp/README bin/; fi
all: neural_cli demo
	
        

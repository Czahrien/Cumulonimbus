ifeq (performance, $(findstring performance, $(MAKECMDGOALS)))
	BUILD_TYPE=-D BUILD_RELEASE
	BUILD_STRING=performance
	BUILD_FLAGS=-O3

else ifeq (release, $(findstring release, $(MAKECMDGOALS)))
	BUILD_TYPE=-D BUILD_RELEASE
	BUILD_STRING=release
	BUILD_FLAGS=-O1

else ifeq (test, $(findstring test, $(MAKECMDGOALS)))
	BUILD_TYPE=-D BUILD_TEST
	BUILD_STRING=test
	BUILD_FLAGS=-O1
else
	BUILD_TYPE=-D BUILD_DEBUG
	BUILD_STRING=debug
	BUILD_FLAGS=
endif

export BUILD_TYPE BUILD_STRING BUILD_FLAGS

include Makefile.inc

SUB_DIRS=drivers services userland kernel

all: BuildImage.o
	@for d in $(SUB_DIRS); do \
	echo "make all in $$d..."; \
	($(MAKE) $(MAKEFLAGS) -C $$d); done

BuildImage.o: BuildImage.c
	gcc -o BuildImage.o BuildImage.c

clean:
	@rm -f *.o
	@for d in $(SUB_DIRS); do ($(ECHO) Cleaning $$d; cd $$d; $(MAKE) $(MFLAGS) clean); done
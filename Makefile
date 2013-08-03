# Makefile
#

PROG = a.out
CC = gcc
CPP = g++

CFLAGS = -g

TEMP_TOKENS_CPP = tokens.cpp
TEMP_PARSER_CPP = parser.hpp parser.cpp

SRCDIR = .
SRC = $(foreach s,$(SRCDIR),$(wildcard $(s)/*.cpp))
VPATH += $(SRCDIR)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
ifeq ($(findstring parser.o,$(OBJ)),)
OBJ += parser.o
endif
ifeq ($(findstring tokens.o,$(OBJ)),)
OBJ += tokens.o
endif

all: parser.cpp tokens.cpp $(PROG)

$(PROG): $(OBJ)
	$(CPP) $(OBJ) -o $(PROG)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<
	@$(CPP) $(CFLAGS) -MM -MP -MT $@ -o $*.d $<

parser.cpp: parser.y
	bison --verbose --debug -d -o $@ $<

tokens.cpp: tokens.l
	flex -o $@ $<

.PHONY: clean
clean:
	rm -rf $(PROG) $(TEMP_TOKENS_CPP) $(TEMP_PARSER_CPP) *.o *.d parser.output

-include $(OBJ:.o=.d)


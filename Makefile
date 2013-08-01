# Makefile
#

PROG = a.out
TEMP_TOKENS_CPP = tokens.cpp
TEMP_PARSER_CPP = parser.hpp parser.cpp

all: $(PROG)

$(PROG):
	flex -o tokens.cpp tokens.l
	bison -d -o parser.cpp parser.y

clean:
	rm -f $(TEMP_TOKENS_CPP) $(TEMP_PARSER_CPP)


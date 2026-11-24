TARGET := calc
SRC := ast.c genllvm.c lex.yy.c lrparser.tab.c main.c
HDR := ast.h genllvm.h
CFLAGS := -O0 -g -I/evecode/include/
LDFLAGS := -L/evecode/libs -lfl -lm

all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
	gcc $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

lrparser.tab.c lrparser.tab.h: lrparser.y
	bison -d lrparser.y

lex.yy.c: lrlex.l
	flex -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGET) lex.yy.c lrparser.tab.c lrparser.tab.h

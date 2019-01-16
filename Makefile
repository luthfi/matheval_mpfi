all: libivalarith.a

parser.c parser.h:	parser.y
	bison -d parser.y -o parser.h -o parser.c

lex.yy.c: scanner.l parser.h
	flex scanner.l

xmalloc.o: xmalloc.c
	gcc -c -DSTDC_HEADERS xmalloc.c

error.o: error.c
	gcc -c -DSTDC_HEADERS error.c

xmath.o: xmath.c
	gcc -c -DSTDC_HEADERS -DHAVE_MATH_H xmath.c -lm

symbol_table.o: symbol_table.c
	gcc -c -DSTDC_HEADERS -DHAVE_MATH_H symbol_table.c -lm

parser.o: parser.c parser.h
	gcc  -c  -DSTDC_HEADERS -DHAVE_MATH_H  parser.c lex.yy.c matheval.c -lfl -lmpfi -lm

matheval.o: lex.yy.c parser.c parser.h
	gcc  -c  -DSTDC_HEADERS -DHAVE_MATH_H  parser.c lex.yy.c matheval.c -lfl -lmpfi -lm

node_mpfi.o: node_mpfi.c
	gcc  -c -DSTDC_HEADERS -DHAVE_MATH_H node_mpfi.c -lfl -lmpfi

ivalarith.o: ivalarith.c
	gcc  -c -DSTDC_HEADERS -DHAVE_MATH_H ivalarith.c -lfl -lmpfi -lm -lmpfr

libivalarith.a: xmalloc.o error.o matheval.o ivalarith.o symbol_table.o xmath.o node.o node_mpfi.o parser.o lex.yy.o
	ar rcu libivalarith.a xmalloc.o error.o matheval.o ivalarith.o symbol_table.o xmath.o node.o node_mpfi.o parser.o lex.yy.o
	ranlib libivalarith.a

driver: libivalarith.a driver.c
	gcc -DSTDC_HEADERS -DHAVE_MATH_H -o driver driver.c libivalarith.a -lfl -lm -lmpfi -lmpfr

deepclean:
	rm lex.yy.c parser.c parser.h *.o *.a

clean:
	rm libivalarith.a

.phony: all deepclean clean

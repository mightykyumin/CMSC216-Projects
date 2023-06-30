
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror

all : main.x program1.x tester.x


program1.x: program1.o row-compare.o 
	$(CC) program1.o row-compare.o -o program1.x

main.x: main.o range-fill.o array-print.o 
	$(CC) main.o range-fill.o array-print.o -o  main.x

tester.x :tester.o range-fill.o array-sum.o row-sum.o
	$(CC) tester.o range-fill.o array-sum.o row-sum.o -o tester.x

array-print.o: array-print.c array-print.h
	$(CC) $(CFLAGS) -c array-print.c

array-sum.o: array-sum.c array-sum.h
	$(CC) $(CFLAGS) -c array-sum.c

main.o: main.c array-print.h range-fill.h
	$(CC) $(CFLAGS) -c main.c

row-compare.o: row-compare.c row-compare.h
	$(CC) $(CFLAGS) -c row-compare.c

range-fill.o: range-fill.c range-fill.h
	$(CC) $(CFLAGS) -c range-fill.c

row-sum.o: row-sum.c row-sum.h
	$(CC) $(CFLAGS) -c row-sum.c

program1.o: program1.c row-compare.h
	$(CC) $(CFLAGS) -c program1.c

tester.o: tester.c range-fill.h array-sum.h row-sum.h
	$(CC) $(CFLAGS) -c tester.c

clean:
	- rm *.x *.o

# Name : Kyumin Hwang
# University Directory ID: khwang77
#  Nine-digits ID : 119134092
#  Section number : 0205
#  I pledge on my honor that I have not given or received any unauthorized
#  assistance on this assignment*/

# These are the makefile of this programs that links the file into
# executable file
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror

all : public01.x public02.x public03.x public04.x public05.x public06.x \
public07.x public08.x public09.x public10.x

public01.x: public01.o string-graph.o
	$(CC) public01.o string-graph.o -o public01.x

public02.x: public02.o string-graph.o
	$(CC) public02.o string-graph.o -o public02.x

public03.x: public03.o string-graph.o
	$(CC) public03.o string-graph.o -o public03.x

public04.x: public04.o string-graph.o compare-vertex-lists.o
	$(CC) public04.o string-graph.o compare-vertex-lists.o -o public04.x

public05.x: public05.o string-graph.o
	$(CC) public05.o string-graph.o -o public05.x

public06.x: public06.o string-graph.o
	$(CC) public06.o string-graph.o -o public06.x

public07.x: public07.o string-graph.o
	$(CC) public07.o string-graph.o -o public07.x

public08.x: public08.o string-graph.o
	$(CC) public08.o string-graph.o -o public08.x

public09.x: public09.o string-graph.o
	$(CC) public09.o string-graph.o -o public09.x

public10.x: public10.o string-graph.o
	$(CC) public10.o string-graph.o -o public10.x

string-graph.o: string-graph.c string-graph-datastructure.h
	$(CC) $(CFLAGS) -c string-graph.c

public01.o: public01.c string-graph.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c string-graph.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c string-graph.h
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c string-graph.h compare-vertex-lists.h
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c string-graph.h
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c string-graph.h
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c string-graph.h
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c string-graph.h
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c string-graph.h
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c string-graph.h
	$(CC) $(CFLAGS) -c public10.c

clean:
	- rm *.x *.o

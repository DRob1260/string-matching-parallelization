#test_search: test_search.c
#	gcc test_search.o search_utils.o naive_search.o -o test_search
#
#test_search.o: test_search.c naive_search.h search_utils.h
#	gcc -c test_search.c
#
#search_utils.0: search_utils.c search_utils.h
#	gcc -c search_utils.c
#
#naive_search.o: naive_search.c naive_search.h
#	gcc -c naive_search.c

CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = search_utils.o naive_search.o test_search.o
TARGET = test_search

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
CC = gcc
CFLAGS = -Wall -lz -L/usr/local/include -I/usr/local/lib -lhts
LDFLAGS =
OBJFILES = search_utils.o naive_search.o bmh_search.o test_search.o
TARGET = test_search

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
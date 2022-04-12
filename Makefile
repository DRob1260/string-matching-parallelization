CC := gcc
CFLAGS := -Wall -Ihtslib-1.15/include -pthread -fopenmp
OBJFILES := search_utils.o naive_search.o bmh_search.o test_search.o
TARGET := test_search


all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) -Lhtslib-1.15/lib -lhts -lz

clean:
	rm -f $(OBJFILES) $(TARGET) *~

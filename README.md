# string-matching-parallelization
A demonstration of parallelized string-matching algorithms for IT388 at Illinois State University. 

## Compile

```shell
make
```

## Run

```shell
./test_search
```

## Files

### test_search.c 

`test_search.c` is the main program used to test the search algorithms.

### search_utils.c

`search_utils.c` is for common functions and definitions that are useful for all the search algorithms. For example, the getTime() method can be used in each multiple files to calculation the duration of each algorithm.

### naive_search.c

`naive_search.c` is for the naive search algorithms.

### bmh_search.c

`bmh_search.c` is for the Boyer-Moore-Horspool search algorithms.

#include <stdio.h>

struct SearchResult_struct {
    char *searchType;
    char *pattern;
    long matchTotal;
    long *matchIndexes;
    double duration;
};

typedef struct SearchResult_struct SearchResult;

struct SearchTarget_struct {
    char *target;
    long targetLength;
};

typedef struct SearchTarget_struct SearchTarget;

double getTime();

void printSearchResults(SearchResult searchResult);

SearchTarget buildSearchTarget(char *filepath, long lengthLimit);

SearchTarget initializeSearchTarget(char *filepath, long lengthLimit);

void finalizeSearchTarget(char *filepath, SearchTarget searchTarget);

void buildSearchPatterns(char *patterns[], char *filepath, int patternLength, int numPatterns);

FILE *initializeSearchResultsFile(char *filename);

void writeSearchResultToFile(FILE *file, SearchResult searchResult);

long getSearchTargetSize(char *filepath, long lengthLimit);

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

void buildSearchPatterns(char *patterns[], char *filepath, int patternLength, int numPatterns);

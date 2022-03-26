struct SearchResult_struct {
    char* searchType;
    int matchTotal;
    int *matchIndexes;
    double duration;
};

typedef struct SearchResult_struct SearchResult;

double getTime();

void printSearchResults(SearchResult searchResult);

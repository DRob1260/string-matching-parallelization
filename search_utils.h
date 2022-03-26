struct SearchResult_struct {
    char* searchType;
    int matchTotal;
    int *matchIndexes;
    double duration;
};

typedef struct SearchResult_struct SearchResult;

double get_time();

void printSearchResults(SearchResult searchResult);

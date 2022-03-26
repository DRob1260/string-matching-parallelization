#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "search_utils.h"
#include <stdlib.h>
#include <stdbool.h>
#endif

SearchResult naive_search(char *pattern, int patternSize, char *target, int targetSize) {
    SearchResult searchResult;
    searchResult.searchType = "Naive Serial Search";
    searchResult.matchIndexes = malloc((targetSize / patternSize) * sizeof(int));
    searchResult.matchTotal = 0;
    double startTime = get_time();

    for(int t=0; t < targetSize; t++) {
        bool isMatch = true;
        for(int p=0; p < patternSize; p++) {
            if(target[t+p] != pattern[p]) {
                isMatch = false;
                break;
            }
        }
        if(isMatch) {
            searchResult.matchIndexes[searchResult.matchTotal] = t;
            searchResult.matchTotal++;
        }
    }

    searchResult.duration = get_time() - startTime;

    return searchResult;
}

#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "search_utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#endif

SearchResult naiveSearch(char *pattern, int patternSize, char *target, long targetSize) {
    printf("Starting Naive Serial Search.\n");
    printf("patternSize: %i\n", patternSize);
    printf("targetSize: %li\n", targetSize);
    SearchResult searchResult;
    searchResult.searchType = "Naive Serial Search";
    searchResult.pattern = pattern;
    searchResult.matchIndexes = malloc((targetSize / patternSize) * sizeof(long));
    searchResult.matchTotal = 0;
    double startTime = getTime();

    for(long t=0; t < targetSize; t++) {
//        if(t % 100000000 == 0)
//            printf("Checking %lith genome character\n", t);
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

    searchResult.duration = getTime() - startTime;

    return searchResult;
}

SearchResult naiveSearchParallel(char *pattern, int patternSize, char *target, long targetSize, long targetStart, long targetEnd) {
    SearchResult searchResult;
    searchResult.searchType = "Naive Parallel Search";

    // TODO: implement naive parallel search

    return searchResult;
}
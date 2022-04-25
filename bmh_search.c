#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "bmh_search.h"
#include "search_utils.h"
#include <string.h>
#include <stdlib.h>
#endif
#define MAX 256

int buildShiftTable[](char p[]){
    int i,j,m;
    m = strlen(p);

    int shiftTable[MAX-1];

    for(i=0;i<MAX;i++){
        shiftTable[i]=m;
    }

    for(j=0;j<m-1;j++){
        shiftTable[p[j]]=m-1-j;
    }

    return shiftTable;
}

SearchResult bmhSearch(char *pattern, int patternSize, char *target, long targetSize) {
    SearchResult searchResult;
    searchResult.searchType = "Boyer-Moore-Horspool Serial Search";
    printf("Starting Naive Serial Search.\n");
    printf("patternSize: %i\n", patternSize);
    printf("targetSize: %li\n", targetSize);
    searchResult.pattern = pattern;
    searchResult.matchIndexes = malloc((targetSize / patternSize) * sizeof(long));
    searchResult.matchTotal = 0;
    double startTime = getTime();

    int shiftTable = buildShiftTable(pattern);
    int i = targetSize - 1;
    int k=0;
    int w=0;

    while(i<n){
        while((k<m) && (pattern[m-1-k] == target[i-k])) {
            k++;
        }
        if(k==m){
            i = i + shiftTable[str[i]];
            int location = (i-m+1);
            searchResult.matchIndexes[w] = location;
            searchResult.matchTotal++;
            k=0;
        }else{
            i = i + shiftTable[str[i]];
        }
    }

    return searchResult;
}

SearchResult bmhSearchParallel(char *pattern, int patternSize, char *target, long targetSize, long targetStart, long targetEnd) {
    SearchResult searchResult;
    searchResult.searchType = "Boyer-Moore-Horspool Parallel Search";

    // TODO: implement BMH parallel search

    return searchResult;
}

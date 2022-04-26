#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "bmh_search.h"
#include "search_utils.h"
#include <string.h>
#include <stdlib.h>
#endif
#define MAX 256
int st[MAX-1];

// void buildShiftTable(int shiftTable[], char p[]){
//     int i,j,m;
//     m = strlen(p);

//     for(i=0;i<MAX;i++){
//         shiftTable[i]=m;
//     }

//     for(j=0;j<m-1;j++){
//         shiftTable[p[j]]=m-1-j;
//     }
// }

void shiftTable(char p[]){
  int i,j,m;
  m = strlen(p);

  for(i=0;i<MAX;i++){
    st[i]=m;
  }

  for(j=0;j<m-1;j++){
    st[p[j]]=m-1-j;
  }
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

    long i,k,n,m;
    n = targetSize;
    m = patternSize;
    shiftTable(pattern);
    i=m-1;
    k=0;

    while(i<n){
        while((k<m)&&(pattern[m-1-k]==target[i-k])){
            k++;
        }
        if(k==m){
            k=0;
            i = i + st[target[i]];
            int location =(i-m+1);
            searchResult.matchIndexes[searchResult.matchTotal] = location;
            searchResult.matchTotal++;
        } else {
            i = i + st[target[i]];
        }
    }

    searchResult.duration = getTime() - startTime;

    return searchResult;
}

SearchResult bmhSearchParallel(char *pattern, int patternSize, char *target, long targetSize, long targetStart, long targetEnd) {
    SearchResult searchResult;
    searchResult.searchType = "Boyer-Moore-Horspool Parallel Search";

    // TODO: implement BMH parallel search

    return searchResult;
}

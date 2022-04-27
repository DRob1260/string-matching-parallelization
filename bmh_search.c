#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "bmh_search.h"
#include "search_utils.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#endif
#define MAX 256
int st[MAX]; 

void shiftTable(char p[]){
  int i,j,m;
  m = strlen(p);

  for(i=0;i<MAX;i++){
    st[i]=m;
  }

  for(j=0;j<m-1;j++){
    st[(int)p[j]]=m-1-j;
  }
}

struct BmhSearchParallelThreadFunctionParams {
    char *pattern;
    int patternSize;
    char *target;
    long targetSize;
    long targetStart;
    long targetEnd;
};

void *bmhSearchParallelPthreadFunction(void *params);

SearchResult bmhSearch(char *pattern, int patternSize, char *target, long targetSize) {
    SearchResult searchResult;
    searchResult.searchType = "Boyer-Moore-Horspool Serial Search";
    printf("Starting BMH Serial Search.\n");
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
        k=0;
        while((k<m)&&(pattern[m-1-k]==target[i-k])){
            k++;
        }
        if(k==m){
            k=0;
            long location =(i-m+1);
            searchResult.matchIndexes[searchResult.matchTotal] = location;
            searchResult.matchTotal++;
            i = i + st[(int)target[i]];
        } else {
            i = i + st[(int)target[i]];
        }
    }

    searchResult.duration = getTime() - startTime;

    return searchResult;
}

SearchResult bmhSearchParallel(char *pattern, int patternSize, char *target, long targetSize, int numThreads) {
    SearchResult searchResult;
    searchResult.searchType = "Boyer-Moore-Horspool Parallel Search";
    printf("Starting BMH Parallel Search.\n");
    printf("patternSize: %i\n", patternSize);
    printf("targetSize: %li\n", targetSize);
    searchResult.pattern = pattern;
    searchResult.matchIndexes = malloc((targetSize / patternSize) * sizeof(long));
    searchResult.matchTotal = 0;
    double startTime = getTime();

    pthread_t *pthreads = malloc(numThreads * sizeof(pthread_t));

    for(int i=0; i < numThreads; i++) {
        long targetStart = i * (targetSize / numThreads);
        long targetEnd = targetStart + (targetSize / numThreads) - 1;
        if(i == numThreads-1)
            targetEnd = targetSize - patternSize; // very last location in target a match can occur

        struct BmhSearchParallelThreadFunctionParams *params = malloc(sizeof(struct BmhSearchParallelThreadFunctionParams));
        params->pattern = pattern;
        params->patternSize = patternSize;
        params->target = target;
        params->targetSize = targetSize;
        params->targetStart = targetStart;
        params->targetEnd = targetEnd;
        pthread_create(&pthreads[i], NULL, bmhSearchParallelPthreadFunction, params);
    }

    SearchResult *searchResults[numThreads];
    for(int i=0; i < numThreads; i++) {
        pthread_join(pthreads[i], (void **)&searchResults[i]);
    }

    int currentMatchIndex = 0;
    for(int i=0; i < numThreads; i++) {
        SearchResult *sr = searchResults[i];
        searchResult.matchTotal += sr->matchTotal;
        for(int x=0; x < sr->matchTotal; x++) {
            searchResult.matchIndexes[currentMatchIndex] = sr->matchIndexes[x];
            currentMatchIndex++;
        }
    }

    searchResult.duration = getTime() - startTime;

    return searchResult;
}

void *bmhSearchParallelPthreadFunction(void *paramsPtr) {
    struct BmhSearchParallelThreadFunctionParams *params = paramsPtr;

    SearchResult *searchResult = malloc(sizeof(SearchResult));
    searchResult->matchIndexes = malloc((params->targetEnd-params->targetStart / params->patternSize) * sizeof(long));
    searchResult->matchTotal = 0;

    long i,k,n,m;
    n = params->targetEnd;
    m = params->patternSize;
    shiftTable(params->pattern);
    i=m-1+params->targetStart;
    k=0;

    while(i<n){
        k=0;
        while((k<m)&&(params->pattern[m-1-k]==params->target[i-k])){
            k++;
        }
        if(k==m){
            k=0;
            long location =(i-m+1);
            searchResult->matchIndexes[searchResult->matchTotal] = location;
            searchResult->matchTotal++;
            i = i + st[(int)params->target[i]];
        } else {
            i = i + st[(int)params->target[i]];
        }
    }

    return searchResult;
}
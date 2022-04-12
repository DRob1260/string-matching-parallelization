#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "search_utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <omp.h>
#endif

void *naiveSearchParallelPthreadFunction(void *params);

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

SearchResult naiveSearchParallelOMP(char *pattern, int patternSize, char *target, long targetSize, int numThreads) {
    printf("Starting Naive Parallel Search using OMP.\n");
    printf("patternSize: %i\n", patternSize);
    printf("targetSize: %li\n", targetSize);
    SearchResult searchResult;
    searchResult.searchType = "Naive Parallel OMP Search";
    searchResult.pattern = pattern;
    searchResult.matchIndexes = malloc((targetSize / patternSize) * sizeof(long));
    searchResult.matchTotal = 0;
    double startTime = getTime();

    omp_set_num_threads(numThreads);

    #pragma omp parallel for
    for(long t=0; t < targetSize; t++) {
        bool isMatch = true;
        for(int p=0; p < patternSize; p++) {
            if(target[t+p] != pattern[p]) {
                isMatch = false;
                break;
            }
        }

        if(isMatch) {
            #pragma omp critical 
            {
                searchResult.matchIndexes[searchResult.matchTotal] = t;
                searchResult.matchTotal++;
            }
        }
    }
    
    searchResult.duration = getTime() - startTime;

    return searchResult;
}

struct NaiveSearchParallelThreadFunctionParams {
    char *pattern;
    int patternSize;
    char *target;
    long targetSize;
    long targetStart;
    long targetEnd;
};

SearchResult naiveSearchParallelPthread(char *pattern, int patternSize, char *target, long targetSize, int numThreads) {
    printf("Starting Naive Parallel Pthread Search.\n");
    printf("patternSize: %i\n", patternSize);
    printf("targetSize: %li\n", targetSize);
    printf("numThreads: %i\n", numThreads);
    SearchResult searchResult;
    searchResult.searchType = "Naive Parallel Search";
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

        struct NaiveSearchParallelThreadFunctionParams *params = malloc(sizeof(struct NaiveSearchParallelThreadFunctionParams));
        params->pattern = pattern;
        params->patternSize = patternSize;
        params->target = target;
        params->targetSize = targetSize;
        params->targetStart = targetStart;
        params->targetEnd = targetEnd;
        pthread_create(&pthreads[i], NULL, naiveSearchParallelPthreadFunction, params);
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

void *naiveSearchParallelPthreadFunction(void *paramsPtr) {
    struct NaiveSearchParallelThreadFunctionParams *params = paramsPtr;

    SearchResult *searchResult = malloc(sizeof(SearchResult));
    searchResult->matchIndexes = malloc((params->targetEnd-params->targetStart / params->patternSize) * sizeof(long));
    searchResult->matchTotal = 0;

    for(long t=params->targetStart; t < params->targetEnd; t++) {
        bool isMatch = true;

        // if(t + params->patternSize == params->targetSize) {
        //     isMatch = false;
        //     printf("End of search location (%li) == targetSize (%li); stopping search.\n", t + params->patternSize, params->targetSize);
        //     break;
        // }

        for(int p=0; p < params->patternSize; p++) {
            if(params->target[t+p] != params->pattern[p]) {
                isMatch = false;
                break;
            }
        }

        if(isMatch) {
            searchResult->matchIndexes[searchResult->matchTotal] = t;
            searchResult->matchTotal++;
        }
    }

    pthread_exit(searchResult);
}
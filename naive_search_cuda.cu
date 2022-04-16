#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search_cuda.cuh"
#include "search_utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#endif

__global__ void cudaFunction(char *pattern, int patternSize, char *target, long targetSize, int numThreads, SearchResult *searchResults[]) {
    int threadIndex = blockIdx.x * blockDim.x + threadIdx.x;
    long searchSize = targetSize / numThreads;
    long start = threadIndex * searchSize;
    long end = start + searchSize;
    if(threadIndex+1 == numThreads) {
        end = targetSize-1;
    }

    SearchResult searchResult;
    searchResult.matchIndexes = (long *)malloc((searchSize / patternSize) * sizeof(long));
    searchResult.matchTotal = 0;

    for(long t=start; t < end; t++) {
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

    *searchResults[threadIndex] = searchResult;
}

SearchResult naiveSearchParallelCuda(char *pattern, int patternSize, char *target, long targetSize, int numThreads, int blockSize) {
    printf("Starting Naive Parallel Search using Cuda.\n");
    printf("patternSize: %i\n", patternSize);
    printf("targetSize: %li\n", targetSize);

    double startTime = getTime();

    SearchResult searchResult;
    searchResult.searchType = "Naive Parallel Cuda Search";
    searchResult.pattern = pattern;
    searchResult.matchIndexes = (long *)malloc((targetSize / patternSize) * sizeof(long));
    searchResult.matchTotal = 0;
   
    SearchResult *searchResults[numThreads]; 
    int numBlocks = ceil(double(numThreads)/blockSize);
    cudaFunction<<<numBlocks, blockSize>>>(pattern, patternSize, target, targetSize, numThreads, searchResults);
    cudaDeviceSynchronize();

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

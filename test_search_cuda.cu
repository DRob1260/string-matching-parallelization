#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search_cuda.cuh"
#include "search_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

// todo: malloc needs to be replaced with cudaMallocManaged
int main(int argc, char* argv[]) {

    if(argc < 7) {
        printf("Invalid arguments. Usage: alignments_filepath genome_filepath pattern_length number_of_patterns number_of_threads block_size target_length_limit(optional)\n");
        exit(1);
    }
    int patternLength = atoi(argv[3]);
    int numPatterns = atoi(argv[4]);
    int numThreads = atoi(argv[5]);
    int blockSize = atoi(argv[6]);
    long targetLengthLimit = -1;
    char *alignmentsFilepath = malloc(100 * sizeof(char));
    char *genomeFilePath = malloc(100 * sizeof(char));
    strncpy(alignmentsFilepath, argv[1], 100);
    strncpy(genomeFilePath, argv[2], 100);
    printf("Input alignments filepath: %s\n", alignmentsFilepath);
    printf("Input genome filepath: %s\n", genomeFilePath);
    printf("Input pattern length: %i\n", patternLength);
    printf("Input number of patterns: %i\n", numPatterns);
    printf("Input number of threads: %i\n", numThreads);
    if(argc == 8) {
        targetLengthLimit = atol(argv[7]);
        printf("Input target length limit: %li\n", targetLengthLimit);
    }

    char *patterns[numPatterns];
    buildSearchPatterns(patterns, alignmentsFilepath, patternLength, numPatterns);

    SearchTarget searchTarget = buildSearchTarget(genomeFilePath, targetLengthLimit);
    printf("SearchTarget length: %li\n", searchTarget.targetLength);

    SearchResult searchResult;

    // filename format is naive_parallel_cuda_<numThreads>_threads.csv
    char filename[100];
    strcat(filename, "naive_parallel_cuda_");
    char numThreadsStr[16];
    sprintf(numThreadsStr, "_%i_threads.csv", numThreads);
    strcat(filename,numThreadsStr);

    FILE *searchResultsFile = initializeSearchResultsFile(filename);
    for(int i=0; i < numPatterns; i++) {
        searchResult = naiveSearchParallelCuda(patterns[i], patternLength, searchTarget.target, searchTarget.targetLength, numThreads, blockSize);
        printSearchResults(searchResult);
        writeSearchResultToFile(searchResultsFile, searchResult);
    }
}
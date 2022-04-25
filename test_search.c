#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "bmh_search.h"
#include "search_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

int main(int argc, char* argv[]) {
    if(argc < 7) {
        printf("Invalid arguments. Usage: ./test_search algorithm alignments_filepath genome_filepath pattern_length number_of_patterns number_of_threads target_length_limit(optional)\n");
        exit(1);
    }
    int patternLength = atoi(argv[4]);
    int numPatterns = atoi(argv[5]);
    int numThreads = atoi(argv[6]);
    long targetLengthLimit = -1;
    char *algorithm = malloc(22 * sizeof(char));
    char *alignmentsFilepath = malloc(100 * sizeof(char));
    char *genomeFilePath = malloc(100 * sizeof(char));
    strncpy(algorithm, argv[1], 22);
    strncpy(alignmentsFilepath, argv[2], 100);
    strncpy(genomeFilePath, argv[3], 100);
    printf("Input algorithm: %s\n", algorithm);
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

    // filename format is <algorithm>_<numThreads>_threads.csv
    char filename[100];
    strcat(filename, algorithm);
    char numThreadsStr[16];
    sprintf(numThreadsStr, "_%i_threads.csv", numThreads);
    strcat(filename,numThreadsStr);
    if(strcmp(algorithm, "naive_serial") == 0) {
        FILE *searchResultsFile = initializeSearchResultsFile(filename);
        for(int i=0; i < numPatterns; i++) {
            searchResult = naiveSearch(patterns[i], patternLength, searchTarget.target, searchTarget.targetLength);
            printSearchResults(searchResult);
            writeSearchResultToFile(searchResultsFile, searchResult);
        }
    } else if(strcmp(algorithm, "naive_parallel_pthread") == 0) {
        FILE *searchResultsFile = initializeSearchResultsFile(filename);
        for(int i=0; i < numPatterns; i++) {
            searchResult = naiveSearchParallelPthread(patterns[i], patternLength, searchTarget.target, searchTarget.targetLength, numThreads);
            printSearchResults(searchResult);
            writeSearchResultToFile(searchResultsFile, searchResult);
        }
    } else if(strcmp(algorithm, "naive_parallel_omp") == 0) {
        FILE *searchResultsFile = initializeSearchResultsFile(filename);
        for(int i=0; i < numPatterns; i++) {
            searchResult = naiveSearchParallelOMP(patterns[i], patternLength, searchTarget.target, searchTarget.targetLength, numThreads);
            printSearchResults(searchResult);
            writeSearchResultToFile(searchResultsFile, searchResult);
        }
    }  else if(strcmp(algorithm, "bmh_serial") == 0) {
        FILE *searchResultsFile = initializeSearchResultsFile(filename);
        for(int i=0; i < numPatterns; i++) {
            searchResult = bmhSearch(patterns[i], patternLength, searchTarget.target, searchTarget.targetLength);
            printSearchResults(searchResult);
            writeSearchResultToFile(searchResultsFile, searchResult);
        }
    } else {
        fprintf(stderr, "Unrecognized value for algorithm name.\n");
        exit(1);
    }
}

#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "search_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

int main(int argc, char* argv[]) {
    if(argc < 5) {
        printf("Invalid arguments. Usage: ./test_search alignments_filepath genome_filepath pattern_length number_of_patterns target_length_limit(optional)\n");
        exit(1);
    }
    int patternLength = atoi(argv[3]);
    int numPatterns = atoi(argv[4]);
    long targetLengthLimit = -1;
    char *alignmentsFilepath = malloc(100 * sizeof(char));
    char *genomeFilePath = malloc(100 * sizeof(char));
    strncpy(alignmentsFilepath, argv[1], 100);
    strncpy(genomeFilePath, argv[2], 100);
    printf("Input alignments filepath: %s\n", alignmentsFilepath);
    printf("Input genome filepath: %s\n", genomeFilePath);
    printf("Input pattern length: %i\n", patternLength);
    printf("Input number of patterns: %i\n", numPatterns);
    if(argc == 6) {
        targetLengthLimit = atol(argv[5]);
        printf("Input target length limit: %li\n", targetLengthLimit);
    }

    char *patterns[numPatterns];
    buildSearchPatterns(patterns, alignmentsFilepath, patternLength, numPatterns);

    SearchTarget searchTarget = buildSearchTarget(genomeFilePath, targetLengthLimit);
    printf("SearchTarget length: %li\n", searchTarget.targetLength);

    FILE *naiveSerialSearchResultsFile = initializeSearchResultsFile("naive_serial_search_results.csv");

    for(int i=0; i < numPatterns; i++) {
        SearchResult naiveSerialSearchResult = naiveSearch(patterns[i], patternLength, searchTarget.target, searchTarget.targetLength);
        printSearchResults(naiveSerialSearchResult);
        writeSearchResultToFile(naiveSerialSearchResultsFile, naiveSerialSearchResult);
    }

    fclose(naiveSerialSearchResultsFile);
}

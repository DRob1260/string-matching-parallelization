#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "search_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

int main(int argc, char* argv[]) {
    if(argc != 5) {
        printf("Invalid arguments. Usage: ./test_search alignments_filepath genome_filepath pattern_length number_of_patterns\n");
        exit(1);
    }
    int patternLength = atoi(argv[3]); // Searching for the full alignment size usually results in 0 finds because it's common for alignments to have misreads, gaps, etc.
    int numPatterns = atoi(argv[4]);
    char *alignmentsFilepath = malloc(100 * sizeof(char));
    char *genomeFilePath = malloc(100 * sizeof(char));
    strncpy(alignmentsFilepath, argv[1], 100);
    strncpy(genomeFilePath, argv[2], 100);


    char *patterns[numPatterns];
    buildSearchPatterns(patterns, alignmentsFilepath, patternLength, numPatterns);

    SearchTarget searchTarget = buildSearchTarget(genomeFilePath);
    printf("SearchTarget length: %li\n", searchTarget.targetLength);

    for(int i=0; i < numPatterns; i++) {
        SearchResult naiveSerialSearchResult = naiveSearch(patterns[i], patternLength, searchTarget.target, searchTarget.targetLength);
        printSearchResults(naiveSerialSearchResult);
    }
}

#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "search_utils.h"
#include <stdio.h>
#endif

int main(int argc, char* argv[]) {

    // TODO: these values to be defined from command line arguments

    int patternLength = 14; // Searching for the full alignment size usually results in 0 finds because it's common for alignments to have misreads, gaps, etc.
    int numPatterns = 30;
    char *alignmentsFilepath = "alignments.fastq";
    char *genomeFilePath = "genome.bam";

    char *patterns[numPatterns];
    buildSearchPatterns(patterns, alignmentsFilepath, patternLength, numPatterns);

    SearchTarget searchTarget = buildSearchTarget(genomeFilePath);
    printf("SearchTarget length: %li\n", searchTarget.targetLength);

    for(int i=0; i < numPatterns; i++) {
        printf("Pattern: %s\n", patterns[i]);
        SearchResult naiveSerialSearchResult = naiveSearch(patterns[i], patternLength, searchTarget.target, searchTarget.targetLength);
        printSearchResults(naiveSerialSearchResult);
    }
}

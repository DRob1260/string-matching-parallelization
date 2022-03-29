#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "search_utils.h"
#include <stdio.h>
#endif

int main(int argc, char* argv[]) {

    // todo: import and use DNA data for testing.
    char* pattern = "the";
    char* target = "the dog chased the cat but the cat was too fast.";

    SearchResult naiveSerialSearchResult = naiveSearch(pattern, 3, target, 48);
    printSearchResults(naiveSerialSearchResult);

    SearchTarget searchTarget = buildSearchTarget("genome.bam");
    printf("SearchTarget length: %li\n", searchTarget.targetLength);
}

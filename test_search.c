#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "naive_search.h"
#include "search_utils.h"
#include <stdio.h>
#endif

int main(int argc, char* argv[]) {

    // TODO: read and search x patterns from alignments.fastq
    char* pattern = "CTCAAGGAGAGTCTGAGCTCAAACACATCTAGCCCCTCCCCAACCTGATGGTCCTTCCCTATCCACCCTGGTAGCAGAAGTCACAGAACATATACTCTTGG";

    SearchTarget searchTarget = buildSearchTarget("genome.bam");
    printf("SearchTarget length: %li\n", searchTarget.targetLength);

    // Searching for the full alignment size usually results in 0 finds because it's common for alignments to have misreads, gaps, etc.
    // 14 seems to be the max that will bring back results.
    SearchResult naiveSerialSearchResult = naiveSearch(pattern, 14, searchTarget.target, searchTarget.targetLength);
    printSearchResults(naiveSerialSearchResult);
}

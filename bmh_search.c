#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "bmh_search.h"
#include "search_utils.h"
#endif

SearchResult bmhSearch(char *pattern, int patternSize, char *target, int targetSize) {
    SearchResult searchResult;
    searchResult.searchType = "Boyer-Moore-Horspool Serial Search";

    // TODO: implement BMH serial search

    return searchResult;
}

SearchResult bmhSearchParallel(char *pattern, int patternSize, char *target, int targetSize, int targetStart, int targetEnd) {
    SearchResult searchResult;
    searchResult.searchType = "Boyer-Moore-Horspool Parallel Search";

    // TODO: implement BMH parallel search

    return searchResult;
}

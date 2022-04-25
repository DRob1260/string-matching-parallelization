#ifndef __INCLUDES_H_
#define __INCLUDES_H_
    #include "search_utils.h"
#endif

// TODO: figure out why this is needed.
// This typedef already exists in search_utils.h but without adding this, the compiler was unable to find SearchResult.
typedef struct SearchResult_struct SearchResult;

SearchResult bmhSearch(char *pattern, int patternSize, char *target, long targetSize);

SearchResult bmhSearchParallel(char *pattern, int patternSize, char *target, long targetSize, long targetStart, long targetEnd);

#ifndef __INCLUDES_H_
#define __INCLUDES_H_
    #include "search_utils.h"
    #include <sys/time.h>
    #include <stdio.h>
#endif

double getTime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec/1000000.0;
}

void printSearchResults(SearchResult searchResult) {
    printf("***********************************\n");
    printf("%s results:\n", searchResult.searchType);
    printf("\tTotal matches: %i\n", searchResult.matchTotal);
    printf("\tMatch locations: [ ");
    for(int i=0; i < searchResult.matchTotal; i++) {
        printf("%i", searchResult.matchIndexes[i]);
        if(i != searchResult.matchTotal - 1)
            printf(", ");
    }
    printf(" ]\n");
    printf("\tSearch duration: %f\n", searchResult.duration);
    printf("***********************************\n");
}
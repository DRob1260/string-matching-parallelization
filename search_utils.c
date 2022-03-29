#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "search_utils.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
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

SearchTarget buildSearchTarget(char *filepath) {
    SearchTarget searchTarget;
    searchTarget.targetLength = 5000000000;
    searchTarget.target = malloc(searchTarget.targetLength * sizeof(char));

    int currentTargetLength = 0;

    samFile *fp_in = hts_open(filepath,"r"); //open bam file
    bam_hdr_t *bamHdr = sam_hdr_read(fp_in); //read header
    bam1_t *aln = bam_init1(); //initialize an alignment

    while(sam_read1(fp_in,bamHdr,aln) > 0){
        uint32_t len = aln->core.l_qseq; //length of the read.
        uint8_t *q = bam_get_seq(aln); // sequence string

        char *qseq = (char *)malloc(len);
        for(int i=0; i < len ; i++){
            qseq[i] = seq_nt16_str[bam_seqi(q,i)]; //gets nucleotide id and converts them into IUPAC id.
        }

        // todo: a bus error occurs when running; I think it may be exceeding available memory so we may need to access the genome in chunks instead of having one big string.
        memcpy(searchTarget.target + currentTargetLength, qseq, len);
        currentTargetLength += len;
    }

    bam_destroy1(aln);
    sam_close(fp_in);

    return searchTarget;
}
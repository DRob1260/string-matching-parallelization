#ifndef __INCLUDES_H_
#define __INCLUDES_H_
#include "search_utils.h"
#include "kseq.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <zlib.h>
#endif
KSEQ_INIT(gzFile, gzread)

double getTime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec/1000000.0;
}

void printSearchResults(SearchResult searchResult) {
    printf("***********************************\n");
    printf("%s results:\n", searchResult.searchType);
    printf("Pattern: %s\n", searchResult.pattern);
    printf("\tTotal matches: %li\n", searchResult.matchTotal);
//    printf("\tMatch locations: [ ");
//    for(long i=0; i < searchResult.matchTotal; i++) {
//        printf("%li", searchResult.matchIndexes[i]);
//        if(i != searchResult.matchTotal - 1)
//            printf(", ");
//    }
//    printf(" ]\n");
    printf("\tSearch duration: %f\n", searchResult.duration);
    printf("***********************************\n");
}

// This function reads the genome.bam file using htslib.sam to build a SearchTarget.
// htslib.sam docs: http://dhtslib.dpldocs.info/htslib.sam.html.
SearchTarget buildSearchTarget(char *filepath) {
    SearchTarget searchTarget;
    searchTarget.targetLength = 0;

    samFile *file = hts_open(filepath,"r"); // open bam file
    bam_hdr_t *bamHeader = sam_hdr_read(file); // read header
    bam1_t *alignment = bam_init1(); // initialize an alignment

//    printf("n_targets: %i\n", bamHeader->n_targets);

    int numberReferences = bamHeader->n_targets;
    uint *referenceLengths = bamHeader->target_len; // target_len is a list of ints representing the size of each reference
    for(int i=0; i < numberReferences; i++) {
        searchTarget.targetLength += referenceLengths[i];
    }
    // For some reason, the length calculated above ends up being far less than the actual length read from the BAM file.
    // For now, searchTarget.target/targetLength are being hard-coded to the appropriate size.
    // TODO: figure out why the calculation above is incorrect.
//    searchTarget.target = malloc(searchTarget.targetLength * sizeof(char));
    searchTarget.target = malloc(4167543494 * sizeof(char));
    searchTarget.targetLength = 4167543494;

    printf("Reading genome into memory. This may take a while...\n");
    long currentTargetLength = 0;
    while(sam_read1(file, bamHeader, alignment) > 0){
        if(currentTargetLength % 10000000 == 0)
            printf("...\n");
        uint32_t alignmentLength = alignment->core.l_qseq;
        uint8_t *sequence = bam_get_seq(alignment);

        char *sequenceString = (char *)malloc(alignmentLength);
        for(int i=0; i < alignmentLength ; i++){
            sequenceString[i] = seq_nt16_str[bam_seqi(sequence, i)]; //gets nucleotide id and converts them into IUPAC id.
        }

        memcpy(searchTarget.target + currentTargetLength, sequenceString, alignmentLength);
        currentTargetLength += alignmentLength;
    }
    printf("Genome read complete.\n");
//    printf("currentTargetLength: %li\n", currentTargetLength);

    bam_destroy1(alignment);
    sam_close(file);

    return searchTarget;
}

void buildSearchPatterns(char *patterns[], char *filepath, int patternLength, int numPatterns) {
    FILE *file = fopen(filepath, "r");
    gzFile fp;
    kseq_t *seq;
    fp = gzdopen(fileno(file), "r");
    seq = kseq_init(fp);
    int currentNumPatterns = 0;
    while(kseq_read(seq) >= 0 && currentNumPatterns < numPatterns) {
        if(seq->seq.l > patternLength) {
            char *pat = malloc(patternLength * sizeof(char));
            memcpy(pat, seq->seq.s, patternLength);
            patterns[currentNumPatterns] = pat;
            currentNumPatterns++;
        }
    }
    kseq_destroy(seq);
    gzclose(fp);
}
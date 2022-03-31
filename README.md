# string-matching-parallelization
A demonstration of parallelized string-matching algorithms for IT388 at Illinois State University. 

## Compile
There is a Makefile that will handle compilation when the below command is run. 

```shell
make
```

## Run

```shell
./test_search
```

## Files

### test_search.c 

`test_search.c` is the main program used to test the search algorithms.

### search_utils.c

`search_utils.c` is for common functions and definitions that are useful for all the search algorithms. For example, the getTime() method can be used in each multiple files to calculation the duration of each algorithm.

### naive_search.c

`naive_search.c` is for the naive search algorithms.

### bmh_search.c

`bmh_search.c` is for the Boyer-Moore-Horspool search algorithms.

## Data 
DNA datasets used are from [The Genome in a Bottle Consortium](https://jimb.stanford.edu/giab).

* Alignments: ftp://ftp-trace.ncbi.nih.gov/ReferenceSamples/giab/data/NA12878/Garvan_NA12878_HG001_HiSeq_Exome/NIST7035_TAAGGCGA_L002_R1_001_trimmed.fastq.gz
  * Contains "alignments", or chunks of random DNA sequences; these will be the strings to search for. 
* Reference Genome: ftp://ftp-trace.ncbi.nih.gov/ReferenceSamples/giab/data/NA12878/Garvan_NA12878_HG001_HiSeq_Exome/project.NIST_NIST7086_H7AP8ADXX_CGTACTAG_2_NA12878.bwa.markDuplicates.bam
  * Contains the full DNA genome of a human being; this will be the target string being searched on.

## Source
Resources used to help write this program.

* https://github.com/lh3/readfq
* https://github.com/samtools/htslib
* http://dhtslib.dpldocs.info/htslib.sam.html
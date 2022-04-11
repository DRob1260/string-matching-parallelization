# string-matching-parallelization
A demonstration of parallelized string-matching algorithms for IT388 at Illinois State University. 

## Compile
___

### Prerequisites

#### Install htslib
htslib is used to read the BAM file that contains the human genome. Perform the below commands while within the project directory. 
```shell
# Download tar file into project directory
wget https://github.com/samtools/htslib/releases/download/1.15/htslib-1.15.tar.bz2
# Untar file
tar -xf htslib-1.15.tar.bz2
# Navigate to htslib-1.15 directory
cd htslib-1.15
# Run configure script
./configure --disable-lzma --disable-bz2
# Run installation
make && make prefix=. install
```

### Compilation using Makefile
There is a Makefile that will handle compilation when the below command is run.

```shell
make
```

## Run
___
### Prerequisites

#### Download & Prepare Datasets 
These are large files so they may take a while to download. Perform the below commands in the project directory.

##### Download
```shell
wget ftp://ftp-trace.ncbi.nih.gov/ReferenceSamples/giab/data/NA12878/Garvan_NA12878_HG001_HiSeq_Exome/NIST7035_TAAGGCGA_L002_R1_001_trimmed.fastq.gz
wget ftp://ftp-trace.ncbi.nih.gov/ReferenceSamples/giab/data/NA12878/Garvan_NA12878_HG001_HiSeq_Exome/project.NIST_NIST7086_H7AP8ADXX_CGTACTAG_2_NA12878.bwa.markDuplicates.bam
```

##### Unzip
The alignments file is compressed, so it needs to be decompressed.
```shell
gzip -d NIST7035_TAAGGCGA_L002_R1_001_trimmed.fastq.gz
```

##### Rename
For simplicity/clarity, rename the files.
```shell
mv NIST7035_TAAGGCGA_L002_R1_001_trimmed.fastq alignments.fastq
mv project.NIST_NIST7086_H7AP8ADXX_CGTACTAG_2_NA12878.bwa.markDuplicates.bam genome.bam
```

#### Set LD_LIBRARY_PATH
The `LD_LIBRARY_PATH` environment variable needs to be set before executing the program. This ensures the linker can find the hts library. This only needs to be done once in each terminal session. 
```shell
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:htslib-1.15/lib"
```

### Execute
```shell
./test_search algorithm alignments_filepath genome_filepath pattern_length number_of_patterns number_of_threads target_length_limit(optional)
```

### Parameters
* `algorithm`: Algorithm to be run. Options: "naive_serial", "naive_parallel", "bmh_serial", "bmh_parallel".
* `alignments_filepath`: Filepath to the .fastq file containing the random reads of DNA (alignments).
* `genome_filepath`: Filepath to the .bam file containing the full human genome.
* `pattern_length`: Length of the pattern (alignment) to use. It is common for alignments to have misreads, so searching for the full alignment will often lead to no matches. Using pattern_length of ~14 seems to give good results.
* `number_of_patterns`: Number of patterns (alignments) to search for.
* `number_of_threads`: Number of threads to use for parallel algorithms.
* `target_length_limit`: Optional. Limits the length of the target string (genome). This is useful while developing code and debugging since reading the genome into memory can take a while.

### Examples

Run 30 searches with pattern length of 14 against the full genome using the serial naive algorithm:
```shell
./test_search naive_serial alignments.fastq genome.bam 14 30 1
```

Run 1 search with pattern length of 5 against the first 1,000,000 bases of the genome using the parallel naive algorithm on 10 threads: 
```shell
./test_search naive_parallel alignments.fastq genome.bam 5 1 10 1000000
```

### Troubleshooting

#### Common Errors
`error while loading shared libraries: libhts.so.3: cannot open shared object file: No such file or directory`
* Make sure to set the LD_LIBRARY_PATH environment variable as specified under "Execution & Parameters".

## Files
___

### test_search.c 

`test_search.c` is the main program used to test the search algorithms.

### search_utils.c

`search_utils.c` is for common functions and definitions that are useful for all the search algorithms. For example, the getTime() method can be used in each multiple files to calculation the duration of each algorithm.

### naive_search.c

`naive_search.c` is for the naive search algorithms.

### bmh_search.c

`bmh_search.c` is for the Boyer-Moore-Horspool search algorithms.

## Data 
___
DNA datasets used are from [The Genome in a Bottle Consortium](https://jimb.stanford.edu/giab).

* Alignments: ftp://ftp-trace.ncbi.nih.gov/ReferenceSamples/giab/data/NA12878/Garvan_NA12878_HG001_HiSeq_Exome/NIST7035_TAAGGCGA_L002_R1_001_trimmed.fastq.gz
  * Contains "alignments", or chunks of random DNA sequences; these will be the strings to search for. 
* Reference Genome: ftp://ftp-trace.ncbi.nih.gov/ReferenceSamples/giab/data/NA12878/Garvan_NA12878_HG001_HiSeq_Exome/project.NIST_NIST7086_H7AP8ADXX_CGTACTAG_2_NA12878.bwa.markDuplicates.bam
  * Contains the full DNA genome of a human being; this will be the target string being searched on.

## Sources
___
Resources used to help write this program.

* https://github.com/lh3/readfq
* https://github.com/samtools/htslib
* http://dhtslib.dpldocs.info/htslib.sam.html

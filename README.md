# dex - dark matter exclusion
It's a wrapper for the fortran code written by Yellin (http://titus.stanford.edu/Upperlimit/)

#Usage
dex: dark exclusion\nUsage:\n-n, --mu0 expected signal events\n\
    -b, --muB expected background events\n\
    -c, --confidence desired confidence level\n\
    -s, --cross-section reference cross-section in cm^2\n\
    -i, --input input file: it contains the CDFs for the measured events (already sorted),\n\t\t\t \
     one for each line, lines beginning with # are ignored. Spaces are not allowed!\n\t\t\t \
     The first entry must be 0. and the last must be 1.\n\
    -o, --output File into which the output is written. If the file already exists, the output will be appended as a new line.\n\t\t\t\
      If the file is newly created a first comment line with the input parameters is written.\n

The idea is to have a list of files containing the CDF for the observed events for each DM mass, then dex will produce one limit for each of them.
The DM mass is not used in the code and is in there for convenience to have a plottable file at the end.
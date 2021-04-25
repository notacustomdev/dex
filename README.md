# dex - dark matter exclusion
It's a wrapper for the fortran code written by Yellin (http://titus.stanford.edu/Upperlimit/)

#Usage
dex: dark exclusion\nUsage:  
    -b, --muB expected background events  
    -c, --confidence desired confidence level  
    -s, --cross-section reference cross-section in cm^2  
    -i, --input input file: it contains the CDFs for the measured events (already sorted),  
     one for each line, lines beginning with # are ignored. Spaces are not allowed!  
     The first entry must be 0. and the last must be 1.  
    -o, --output File into which the output is written. If the file already exists, the output will be appended as a new line.  
      If the file is newly created a first comment line with the input parameters is written.  

The idea is to have a list of files containing the CDF for the observed events for each DM mass, then dex will produce one limit for each of them.
The DM mass is not used in the code and is in there for convenience to have a plottable file at the end.

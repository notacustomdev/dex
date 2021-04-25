#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "yellin_wrap.h"

int main (int argc, char **argv)
{

  int If, Iflag;
  
  char *inputFile=0;
  char *outputFile=0;

  Iflag = 1;
  If = 1;
  
  float cl, muB, xsec, mu0, chi_M;
  cl = .95;
  muB = .0;
  mu0 = .0;
  xsec = 1.E-42;
  /*TLDR command line parsing*/
  int c;

  while (1)
    {
      static struct option long_options[] =
        {
          /*parameters to determine the limit*/
          {"muB",  required_argument,       0, 'b'},
          {"cross-section",  required_argument, 0, 's'},
          {"confidence",  required_argument, 0, 'c'},
          {"mass",    required_argument, 0, 'm'},
          {"input",    required_argument, 0, 'i'},
          {"output",    required_argument, 0, 'o'},
	        {"help",    no_argument, 0, 'h'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "b:s:c:m:hi:o:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'b':
          printf ("muB = %s\n", optarg);
          muB = atof(optarg);
          break;

        case 'i':
          printf ("input file = %s\n", optarg);
          inputFile = (char*) malloc(strlen(optarg)+1);
          strcpy(inputFile, optarg);
          break;

        case 'o':
          printf ("output file = %s\n", optarg);
          outputFile = (char*) malloc(strlen(optarg)+1);
          strcpy(outputFile, optarg);
          break;

        case 's':
          printf ("cross-section = %s\n", optarg);
          xsec = atof(optarg);
          break;

        case 'c':
          printf ("confidence level = %s\n", optarg);
          cl = atof(optarg);
          break;

        case 'm':
          printf ("DM mass %sGeV\n", optarg);
          chi_M = atof(optarg);
          break;

        case 'h':
	  printf ("dex: dark exclusion\nUsage:\n-n, --mu0 expected signal events\n\
    -b, --muB expected background events\n\
    -c, --confidence desired confidence level\n\
    -s, --cross-section reference cross-section in cm^2\n\
    -m, --mass mass of the DM particle (to be appended at the output)\n\
    -i, --input input file: it contains the CDFs for the measured events (already sorted),\n\t\t\t \
     one for each line, lines beginning with # are ignored. Spaces are not allowed!\n\t\t\t \
     The first entry must be 0. and the last must be 1.\n\
    -o, --output File into which the output is written. If the file already exists, the output will be appended as a new line.\n\t\t\t\
      If the file is newly created a first comment line with the input parameters is written.\n");  
          if(inputFile)
            free(inputFile);
          if(outputFile)
            free(outputFile);

          exit(0);

        default:
          abort ();
        }
    }

   /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  printf("Running with the following settings:\ncross-section: %.4ecm^2\nmu0: %f\nmuB: %f\nConfidence level: %f\n", xsec, mu0, muB, cl*100.);

  FILE *fin = fopen(inputFile, "r");

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  if (fin == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  /*count the number of lines without # to allocate the cdf vector*/
  size_t n = 0;
  while ((nread = getline(&line, &len, fin)) != -1) {
    if(!(line[0] == '#'))
      n++;
  }
  
  printf("Found %ld lines containing data\n", n);

  n--;//one line is the number of expected events

  fseek(fin, 0, SEEK_SET );

  float *cdfevt = malloc(sizeof(float)*n);
  
  /*read the data and fill the cdf vector*/
  n = 0;
  bool firstzero = false;
  while ((nread = getline(&line, &len, fin)) != -1) {
    if(!(line[0] == '#')){
      if(!firstzero){
        mu0 = atof(line);
        firstzero = true;
        continue;
      }
      cdfevt[n++] = atof(line);
    }
  }

  printf("mu0: %f\n", mu0);
  
  fclose(fin);
  free(line);
  
  bool usenew = true;
 
  /*store the result*/
  float upl;
  
  yellin_init();
  upl = upperlim(cl, If, n-2, cdfevt,   muB, 0, &Iflag, usenew);
  yellin_end();

  printf("Upper limit mu0: %f\n", upl);
  printf("Upper limit: %.4ecm^2\n", (xsec/mu0)*upl);
  printf("Iflag: %d\n", Iflag);
  free(cdfevt);

  FILE *fout;
  /*check if the output file exists*/
  if( access(outputFile, F_OK ) != 0 ) {
    fout = fopen(outputFile, "a");
    fprintf(fout, "#dex written file (using Yellin's code) with: CL: %f, If: %d, muB: %f\n%f %.10e %d\n", 
            cl, If, muB, chi_M, (xsec/mu0)*upl, Iflag);
  } else {
    fout = fopen(outputFile, "a");
    fprintf(fout, "%f %.10e %d\n", chi_M, (xsec/mu0)*upl, Iflag);
  }

  fclose(fout);

  if(inputFile)
    free(inputFile);
  
  if(outputFile)
    free(outputFile);
  
  exit (0);
}

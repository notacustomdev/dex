#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>

#include "yellin_wrap.h"

int main (int argc, char **argv)
{

  int n, If, Iflag;
  
  Iflag = 1;
  If = 1;
  n=2;
  float cl, muB, xsec, mu0;
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
          /* One needs either to get a cross-section
             or the number of excluded events*/
          {"mu0",     required_argument,       0, 'n'},
          {"muB",  required_argument,       0, 'b'},
          {"cross-section",  required_argument, 0, 's'},
          {"confidence",  required_argument, 0, 'c'},
          {"mass",    required_argument, 0, 'M'},
	        {"help",    no_argument, 0, 'h'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "n:b:s:c:M:h",
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

        case 'n':
          printf ("mu0 = %s\n", optarg);
          mu0 = atof(optarg);
          break;

        case 'b':
          printf ("muB = %s\n", optarg);
          muB = atof(optarg);
          break;

        case 's':
          printf ("cross-section = %s\n", optarg);
          xsec = atof(optarg);
          break;

        case 'c':
          printf ("confidence level = %s\n", optarg);
          cl = atof(optarg);
          break;

        case 'M':
          printf ("DM mass %sGeV\n", optarg);
          break;

        case 'h':
	  printf ("Usage:\n-n, --mu0 expected signal events\n-b, --muB expected background events\n-c, --confidence desired confidence level\n-s, --cross-section reference cross-section in cm^2\n");          
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

  float cdfevt[] = {0., 0.05263, 0.47368, 1.};
  bool usenew = true;
  yellin_init();
  printf("Upper limit mu0:%.4e\n", upperlim(cl, If, n, cdfevt, muB, 0, &Iflag, usenew));
  printf("Upper limit:%.4ecm^2\n", (xsec/mu0)*upperlim(cl, If, n, cdfevt, muB, 0, &Iflag, usenew));
  yellin_end();
  exit (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

float upperlim(float*, int*, int*,float*,float*,int*);

int main (int argc, char **argv)
{
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
          puts ("option -a\n");
          break;

        case 'b':
          puts ("option -b\n");
          break;

        case 's':
          printf ("option -c with value `%s'\n", optarg);
          break;

        case 'c':
          printf ("option -d with value `%s'\n", optarg);
          break;

        case 'M':
          printf ("option -f with value `%s'\n", optarg);
          break;

        case 'h':
	  printf ("Usage:\n");          
          break;

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

  int n, If, Iflag;
  
  n = 2;
  Iflag = 1;
  If = 1;
  
  float cl, muB;
  float cdfevt[] = {0.094165087, 0.230128258};

  muB = .0;
  cl = 0.95;
  printf("Upper limit:%f\n", upperlim(&cl, &If, &n, &muB, cdfevt, &Iflag));
  
  exit (0);
}

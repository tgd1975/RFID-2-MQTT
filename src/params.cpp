#include "params.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

params getParams(int argc, char **argv) {
    params p;
 
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;
  int index;
  int c;

  opterr = 0;

    static struct option long_options[] = {
        {"area",      no_argument,       0,  'a' },
        {"perimeter", no_argument,       0,  'p' },
        {"length",    required_argument, 0,  'l' },
        {"breadth",   required_argument, 0,  'b' },
        {0,           0,                 0,  0   }
    };
    
  while ((c = getopt (argc, argv, "abc:")) != -1)
    switch (c)
      {
      case 'a':
        aflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'c':
        cvalue = optarg;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        //return 1;
      default:
        abort ();
      }

    return p;
}
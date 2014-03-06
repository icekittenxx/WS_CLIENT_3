/*
POSIX getopt for Windows

AT&T Public License

Code given out at the 1985 UNIFORUM conference in Dallas.  
*/


//#include "stdafx.h"
#include "getopt.h"
#include <stdio.h>
#include <string.h>


#define NULL	0
#define EOF	(-1)

int getopt(int argc, char **argv, char *opts, int optind)
{
	int c;
	int sp = 1;
	char *cp;

	//int opterr;
	int optopt;
	char *optarg;

	if(sp == 1){
		if(optind >= argc ||
		   argv[optind][0] != '-' || argv[optind][1] == '\0')
			return(EOF);
		else if(strcmp(argv[optind], "--") == NULL) {
			optind++;
			return(EOF);
		}
	}

	optopt = c = argv[optind][sp];

	if(c == ':' || (cp=strchr(opts, c)) == NULL) {
		//ERR(": illegal option -- ", c);
		if(argv[optind][++sp] == '\0') {
			optind++;
			sp = 1;
		}
		return('?');
	}
	if(*++cp == ':') {
		if(argv[optind][sp+1] != '\0')
			optarg = &argv[optind++][sp+1];
		else if(++optind >= argc) {
			//ERR(": option requires an argument -- ", c);
			sp = 1;
			return('?');
		} else
			optarg = argv[optind++];
		sp = 1;
	} else {
		if(argv[optind][++sp] == '\0') {
			sp = 1;
			optind++;
		}
		optarg = NULL;
	}
	return c;
}

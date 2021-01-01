/*
 * File: queue.c
 * Author: Mikey Brown
 * Project: CSCI 3753 Programming Assignment 4
 * Description:
 * 	This file is a single threaded implementation of lookup
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "util.h"

#define MINARGS 3
#define USAGE "<inputFilePath> <outputFilePath>"
#define MAX_NAME_LENGTH 1025
#define INPUTFS "%1024s"
#define MAX_INPUT_FILES 10


int main(int argc, char* argv[]){

  FILE* inFile;
  FILE* outFile;
  char hostname[MAX_NAME_LENGTH];
  char inet6_adr[INET6_ADDRSTRLEN];
  int i;

  if(argc < MINARGS){
    fprintf(stderr, "Not enough arguments: %d\n", (argc - 1));
    fprintf(stderr, "Usage:\n %s %s\n", argv[0], USAGE);
    return EXIT_FAILURE;
  }

  outFile = fopen(argv[(argc-1)], "w");
  if(!outFile){
    fprintf(stderr,"Error Opening Output File. Check file path %s", argv[(argc-1)]);
    return EXIT_FAILURE;
  }

  /* Loop for each input files */
  for(i=1; i<(argc-1); i++){
    inFile = fopen(argv[i], "r");
    if(!inFile){
        fprintf(stderr,"Error Opening Input File. Check file path %s", argv[i]);
        break;
    }

    /* Read File and Process*/
    while(fscanf(inFile, INPUTFS, hostname) > 0){

        /* Lookup hostname and get IP string */
        if(dnslookup(hostname, inet6_adr, sizeof(inet6_adr)) == UTIL_FAILURE){
          fprintf(stderr,"dnslookup error: %s\n", hostname);
          fprintf(outFile, "%s,\n", hostname);
        }else{
          /* Write to Output File */
          fprintf(outFile, "%s,%s\n", hostname, inet6_adr);
        }
    }
    /* Close Input File */
    fclose(inFile);
  }
  /* Close Output File */
  fclose(outFile);
  return EXIT_SUCCESS;
}

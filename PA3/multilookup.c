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
#include <unistd.h>
#include <sys/time.h> //?
#include <time.h> //?
#include <pthread.h>

#include "queue.h"
#include "multilookup.h"
#include "util.h"

#define MIN_ARGS 5
#define USAGE "<# requester> <# resolver> <requester log> <resolver log> [ <data file> ... "
#define INPUTFS "%1024s"
#define MAX_INPUT_FILES 10
#define MAX_RESOLVER_THREADS 10
#define MAX_REQUESTER_THREADS 5
#define MAX_NAME_LENGTH 1025


void *requester(void *arguments) {
  req_arg_struct *args = (req_arg_struct *) arguments;

  //important array of pointers loaded into queue
  char *inputs[128];
  char hostname[MAX_NAME_LENGTH+1];
  int numFilesServiced = 0; //local count of files serviced
  FILE* dataFile;
  unsigned fileIdx = 0;
  int i =0; //line number for file read
  // printf("requester created with id of %lu\n", pthread_self());

  while(args->totalFilesServiced < args->numDataFiles){
    /* file index increments with each file serviced */
    pthread_mutex_lock(&args->TFS_mutex);
    fileIdx = args->totalFilesServiced;
    args->totalFilesServiced++;
    pthread_mutex_unlock(&args->TFS_mutex);

    // printf("opening file %s, at index %d\n", args->dataFileNames[fileIdx].name, fileIdx);
    dataFile = fopen(args->dataFileNames[fileIdx].name, "r");       //////////////////////////////////
    if(!dataFile){
        perror("Failed: bogus data file name");
    }else{
      numFilesServiced++;
      while(fscanf(dataFile, INPUTFS, hostname) > 0){
        // printf("hostname found: %s\n", hostname);
        inputs[i] = strdup(hostname) ;
        //strncpy(inputs[i], hostname, strlen(hostname));

        /* Allow other threads */
        pthread_mutex_lock(&args->Q_mutex);
        while(-1 == enQueue(args->q, inputs[i])) {
          pthread_mutex_unlock(&args->Q_mutex);
          sleep(.5);
          pthread_mutex_lock(&args->Q_mutex);
        }
        pthread_mutex_unlock(&args->Q_mutex);
        i++;
        //free(inputs[i]);
      } //end file read
      fclose(dataFile);
    }
  }

  pthread_mutex_lock(&args->reqLog_mutex);
  fprintf(args->reqLog,"Thread %lu serviced %d files.\n", pthread_self(), numFilesServiced);
  fprintf(args->perfLog,"Thread %lu serviced %d files.\n", pthread_self(), numFilesServiced);

  pthread_mutex_unlock(&args->reqLog_mutex);
  // printf("exiting requester\n");
  return NULL;
}


/* reads from queue, writes to resolverLog */
void* resolver(void *arguments){
  req_arg_struct *args = (req_arg_struct *) arguments;
  int result = 0;
  char *hostname;
  char inet6_adr[INET6_ADDRSTRLEN];
  // printf("resolver created with id of %lu\n", pthread_self());

  pthread_mutex_lock(&args->Q_mutex);
  while(args->requesterWorking || !isEmptyQueue(args->q)) {
    if(!isEmptyQueue(args->q))
    {
      hostname = deQueue(args->q);
      pthread_mutex_unlock(&args->Q_mutex);

      result = dnslookup(hostname, inet6_adr, sizeof(inet6_adr));
      if(result == UTIL_FAILURE){
        fprintf(stderr,"Hostname causing error: %s\n", hostname);
        /* still write hostname */
        pthread_mutex_lock(&args->resLog_mutex);
        fprintf(args->resLog, "%s\n", hostname);
        pthread_mutex_unlock(&args->resLog_mutex);

      }else if (result == UTIL_SUCCESS){
        /* Store result */
      //  printf("%s,%s\n", hostname, inet6_adr);

        pthread_mutex_lock(&args->resLog_mutex);
        fprintf(args->resLog, "%s,%s\n", hostname, inet6_adr);
        pthread_mutex_unlock(&args->resLog_mutex);
      }
      free(hostname);
    }else{
      /* Allow other threads */
      pthread_mutex_unlock(&args->Q_mutex);
      sleep(.5); //allow other threads
    }
    pthread_mutex_lock(&args->Q_mutex); //lock after each loop to check while
  }
  pthread_mutex_unlock(&args->Q_mutex);
  return NULL;
}


int main(int argc, char* argv[]){
  unsigned curReqThreads = 0;
  unsigned curResThreads = 0;
  /* Reading CL args. "<# requester> <# resolver> <requester log> <resolver log> [ <data file> ... " */
  unsigned maxReqThreads = atoi(argv[1]);
  unsigned maxResThreads = atoi(argv[2]);
  unsigned numDataFiles = argc - 5;
  pthread_t requested[maxReqThreads]; //requester threads
  pthread_t resolved[maxResThreads]; //resolver threads
  int argvIdx; //for iterating console input

  /* For time elapsed */
  struct timeval start, end;
  gettimeofday(&start, NULL);

  if(maxReqThreads > numDataFiles){
      perror("Error more requester threads than files, changing numer of request threads to number of data files\n");
      printf("%u",numDataFiles);
      maxReqThreads = numDataFiles;
  }

  if(argc < MIN_ARGS){
    fprintf(stderr, "Not enough arguments: %d\n", (argc - 1));
    fprintf(stderr, "Usage:\n %s %s\n", argv[0], USAGE);
    return EXIT_FAILURE;
  }

  /* Shared queue for producers and consumers */
  queue q;
  if (createQueue(&q)!=0){
    return -1;
  }
  /*create argument struct for requester */
  req_arg_struct *req_args = malloc(sizeof(req_arg_struct));
  req_args->q= &q;
  req_args->numDataFiles = numDataFiles;
  req_args->numDataFiles = argc - 5;
  req_args->totalFilesServiced =0; //inter-thread count of files serviced
  req_args->requesterWorking = 0;
  req_args->perfLog = fopen("performance.txt", "a");
  if(!req_args->perfLog){
    fprintf(stderr,"Error opening performance log file.");
    return EXIT_FAILURE;
  }
  req_args->resLog = fopen(argv[4], "w");
  if(!req_args->resLog){
    fprintf(stderr,"Error opening resolver output file. Check file path");
    return EXIT_FAILURE;
  }
  req_args->reqLog = fopen(argv[3], "w");
  if(!req_args->reqLog){
    fprintf(stderr,"Error opening requester output file. Check file path");
    return EXIT_FAILURE;
  }
  pthread_mutex_init(&req_args->Q_mutex, NULL);
  pthread_mutex_init(&req_args->resLog_mutex, NULL);
  pthread_mutex_init(&req_args->reqLog_mutex, NULL);
  pthread_mutex_init(&req_args->TFS_mutex, NULL);

  /* Store dataFileNames */
  for(argvIdx=5; argvIdx < argc; argvIdx++){
    // printf("Input recieved: %s \n", argv[argvIdx]);
    // strncpy (req_args->dataFileNames[argvIdx-5].name ,argv[argvIdx], strlen(argv[argvIdx]) );
    req_args->dataFileNames[argvIdx-5].name = argv[argvIdx];
  }
  /* Create some requester threads */
  fprintf(req_args->perfLog,"Number of requester threads is %u\n", maxReqThreads);
  fprintf(req_args->perfLog,"Number of resolver threads is %u\n", maxResThreads);

  req_args->requesterWorking = 1;
  while(curReqThreads < maxReqThreads){
    pthread_create(&(requested[curReqThreads]), NULL, requester, (void *)req_args);
    curReqThreads++;
  }
  while(curResThreads < maxResThreads){
    pthread_create(&(resolved[curResThreads]), NULL, resolver, (void *)req_args);
    curResThreads++;
  }

  for(unsigned i = 0; i< maxReqThreads; i++){
    pthread_join(requested[i], NULL);
  }
  printf("requesters done\n");
  req_args->requesterWorking = 0;

  for(unsigned i = 0; i< maxResThreads; i++){
    pthread_join(resolved[i], NULL);
  }
  printf("resolvers done\n");

  gettimeofday(&end, NULL);
  printf("./multi-lookup: total time is %f seconds\n",
  ( (end.tv_sec - start.tv_sec) +
                ((end.tv_usec - start.tv_usec)/1000000.0) ));
  fprintf(req_args->perfLog,"./multi-lookup: total time is %f seconds\n\n", ( (end.tv_sec - start.tv_sec) +
                ((end.tv_usec - start.tv_usec)/1000000.0) ));

  /* Clean up */
  deleteQueue(&q);
  fclose(req_args->reqLog);
  fclose(req_args->resLog);
  fclose(req_args->perfLog);
  free(req_args);
  return EXIT_SUCCESS;
}

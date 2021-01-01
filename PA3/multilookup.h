/*
 * File: queue.c
 * Author: Mikey Brown
 * Project: CSCI 3753 Programming Assignment 4
 * Description:
 * 	Header file for multi-threaded implementation of lookup
 *
 */

 #ifndef MULTILOOKUP_H
 #define MULTILOOKUP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h> //?
#include <time.h> //?
#include "queue.h"
#include "util.h"

#define USAGE "<# requester> <# resolver> <requester log> <resolver log> [ <data file> ... "
#define INPUTFS "%1024s"
#define MAX_INPUT_FILES 10
#define MAX_RESOLVER_THREADS 10
#define MAX_REQUESTER_THREADS 5
#define MAX_NAME_LENGTH 1025
// #define MAX_IP_LENGTH INET6_ADDRSTRLEN



/*Arguments for requester */
typedef struct f_names_s {
  char *name;
}f_name;

typedef struct req_arg_struct_s {
  FILE* resLog;
  FILE* reqLog;
  FILE* perfLog;
  unsigned numDataFiles;
  f_name dataFileNames[MAX_INPUT_FILES];
  /* Locks for shared buffer(FIFO queue), requester log file, resolver log file */
  pthread_mutex_t Q_mutex;
  pthread_mutex_t reqLog_mutex;
  pthread_mutex_t resLog_mutex;
  pthread_mutex_t TFS_mutex;
  queue *q;
  unsigned totalFilesServiced; //inter-thread count of files serviced

  // for locking shared count of files serviced
  int requesterWorking;

}req_arg_struct;


void* requester(void *args);

void* resolver(void* resolverLog);

#endif

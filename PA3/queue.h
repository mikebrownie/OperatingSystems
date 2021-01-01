/*
 * File: queue.c
 * Author: Mikey Brown
 * Project: CSCI 3753 Programming Assignment 4
 * Description:
 * 	This file contains declarations of queue structure used for multi-lookup
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 20
#define MAX_IP_LENGTH 128

typedef struct ip_s {
    char *data;
} ip;

typedef struct myQueue_s {
    int front, rear;
    int size;
    ip *array;
} queue;

int createQueue(queue* q);
int isEmptyQueue(queue* q);
int isFullQueue(queue* q);
char *deQueue(queue* q);
int enQueue(queue* q, char *new_value);
int deleteQueue(queue* q);

#endif

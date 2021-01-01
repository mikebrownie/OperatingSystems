/*
 * File: queue.c
 * Author: Mikey Brown
 * Project: CSCI 3753 Programming Assignment 4
 * Description:
 * 	This file contains declarations of queue structure used for multi-lookup
 *
 */
 #include <stdlib.h>
  #include <string.h>
 #include "queue.h"

/* Parameters: pointer to queue object, size of queue object
 * Return:
 * -1 if error
 *  0 if successful
 */
 int createQueue(queue* q){
   int i;
   q->front = 0;
   q->rear = 0;
   q->size = 0;
   q->array = malloc(sizeof(ip)*MAX_SIZE );
   if(!(q->array)){
    	perror("Error on queue malloc");
    	return -1;
    }
    /* Set to NULL */
    for(i=0; i < MAX_SIZE; ++i){
    	q->array[i].data = NULL;
    }

   return 0;
 }

 int isEmptyQueue(queue* q){
   // printf("%d \n", q->size);
   return(q->size <= 0);
 }

 int isFullQueue(queue* q){
   return(q->size >= MAX_SIZE);
 }

char *deQueue(queue* q){
  if(isEmptyQueue(q)){
    // fprintf(stderr, "Can't dequeue empty queue\n");
    return NULL;
  }
  char *popped = q->array[q->front].data;
  // printf("DQ Popped: %s\n", popped);
  q->array[q->front].data = NULL;
  q->front = ((q->front + 1) % MAX_SIZE);
  q->size = q->size - 1;
  return popped;
 }


int enQueue(queue* q, char *new_value){
 if(isFullQueue(q)){
   // fprintf(stderr, "Can't enqueue, full queue\n");
   return -1;
  }
  // printf("EQ front: %d rear index we add at: %d data to add: %s \n\n", q->front,q->rear, new_value);
  q->array[q->rear].data = new_value;
  q->rear = (q->rear + 1) % MAX_SIZE; //never go past 19
  q->size = q->size + 1;
  return 0;
}

 int deleteQueue(queue* q){
   int i=0;
   while(!isEmptyQueue(q)){
     free(q->array[i].data);
     i++;
   }
    free(q->array);
    return 0;
 }

// NEW USAGE
// int main(int argc, char const *argv[]) {
//   queue q;
//   int i;
//   char *ptr;
//   char temp[100];
//   char *inputs[20];
//   printf("creating queue\n");
//
//   createQueue(&q);
//   printf("queue created\n");
//
//   i=0;
//   printf("%d\n", i);
//
//
//   while (!isFullQueue(&q)){
//     printf("i= %d\n",i);
//
//     sprintf(temp, "%d", i);
//     inputs[i] = (char*) malloc (strlen(temp)+1) ;
//     strncpy(inputs[i], temp, strlen(temp));
//     enQueue(&q, inputs[i]);
//     i++;
//   }
//   while (!isEmptyQueue(&q)) {
//     ptr = deQueue(&q);
//     printf("%s\n", ptr);
//   }
//
// }




// // tesing out the queue
// int main(int argc, char const *argv[]) {
//   queue q;
//   int i;
//   char *ptr;
//   char *str1 = "hello";
//   char *first = "FIRST STR INSERTED";
//
//   createQueue(&q);
//   enQueue(&q, str1);
//   enQueue(&q, first);
//   ptr = deQueue(&q);
//   printf("%s \n", ptr);
//   ptr = deQueue(&q);
//   printf("%s \n", ptr);
//   if (isEmptyQueue(&q)){
//     printf("Queue is empty, as it shouldbe\n");
//   }
//   printf("-testing lower bound by dequeing\n");
//   deQueue(&q);
//   printf("-Now filling queue with 20 elements\n");
//   enQueue(&q, first);
//   while(i<19){
//     enQueue(&q, str1);
//     i++;
//   }
//   if (isFullQueue(&q)){
//     printf("Queue is full, as it should be\n");
//   }
//   if (!isEmptyQueue(&q)){
//     printf("Queue is not empty, as it should be\n");
//   }
//
//   // enQueue(&q, data);
//   printf("-Now dequeing one element, printing, and enqueing another element\n");
//   ptr = deQueue(&q);
//   printf("%s \n", ptr);
//   enQueue(&q, str1);
//   if (!isEmptyQueue(&q)){
//     printf("Queue is NOT empty\n");
//   }
//   if (isFullQueue(&q)){
//     printf("Queue is full, as it should\n");
//   }
//   printf("-Now upper bound by enqueing another element\n");
//   enQueue(&q, str1);
//
//   printf("-Cleaning up Queue\n");
//   deleteQueue(&q);
//   // printf(isEmptyQueue(&q));
//   // printf(deQueue(&q));
//   // printf(isEmptyQueue(&q));
//
//   return 0;
// }

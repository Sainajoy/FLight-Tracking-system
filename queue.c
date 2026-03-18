//
// Created by hp on 22/11/2025.
//

#include "queue.h"

Queue CreateQueue()
{
    //To be completed
     Queue q = (Queue)malloc(sizeof(struct QueueRecord));

        if (q == NULL){
          printf("Memory allocation error\n");
          exit(1);
        }

        MakeEmptyQueue(q);

        return q;
}

void MakeEmptyQueue(Queue q)
{
    //To be completed

        struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));

        if (newNode == NULL){
          printf("Memory allocation error\n");
          exit(1);
        }
        q-> front = newNode;
        q -> front -> next = NULL;
        q -> rear = q -> front;
        q -> size = 0;

}

void Enqueue(Flight* newFlight, Queue q)
{
    //To be completed

    int priority;
    if(newFlight -> flightType == 'E') priority = 3;
    else if(newFlight -> flightType == 'I') priority = 2;
    else priority = 1;

    struct QueueNode* newNode = malloc(sizeof(struct QueueNode));
    if (newNode == NULL){
       printf("Memory allocation error\n");
       exit(1);
    }

    newNode->flightInfo = newFlight;
    newNode -> priority = priority;
    newNode->next = NULL;

    struct QueueNode* prev = q -> front;
    struct QueueNode* current = q -> front -> next;  //first node

    while (current != NULL && current -> priority >= priority){    //runs when the current flight priority is higher
      prev = current;
      current = current -> next;
    }

    //enqueue between prev and current
    prev -> next = newNode;
    newNode -> next = current;

    if (current == NULL){
      q -> rear = newNode;
    }

    q->size++;


}

Flight* Dequeue(Queue q)
{
    //To be completed
    if(IsEmptyQueue(q)){
      printf("Queue is empty\n");
      return NULL;
    }


    struct QueueNode * temp = q->front->next;
    q->front->next = q->front->next->next;
    Flight* removeFlight = temp -> flightInfo;
    free(temp);
    q->size--;

    //in the case this was the only element in the queue
    if(q->size == 0){
      q ->rear = q -> front;
    }
    return removeFlight;


}

int IsEmptyQueue(Queue q)
{
    //To be completed
    return q -> size == 0;
}

int QueueSize(Queue q)
{
    //To be completed
        return q->size;
}

Flight* FrontOfQueue(Queue q)
{
    //To be completed
        if(IsEmptyQueue(q)){
          printf("Queue is empty\n");
          return NULL;
        }

        Flight* front = q->front->next->flightInfo;
        return front;
}

Flight* RearOfQueue(Queue q)
{
    //To be completed
    if(IsEmptyQueue(q)){
        printf("Queue is empty\n");
        return NULL;
    }

    Flight* rear = q->rear->flightInfo;
    return rear;

}

void DisplayQueue(Queue q)
{
    //To be completed
    if(IsEmptyQueue(q)){
      printf("Queue is empty\n");
      return;
    }

    //print content of Queue
    struct QueueNode *current = q->front->next;

    while(current != NULL){
        printf("Flight type: %c\n", current->flightInfo->flightType);
        printf("ReadyTime: %d\n", current->flightInfo->readyTime);
        printf("ServiceTime: %d\n", current->flightInfo->serviceTime);
        printf("ServiceStartTime: %d\n", current->flightInfo->serviceStartTime);
        printf("RunwayNumber: %d\n", current->flightInfo->runwayNumber);
        printf("Airline: %s\n", current->flightInfo->airline);
        printf("Destination: %s\n", current->flightInfo->destination);
        current = current -> next;
    }


}

void deleteQueue(Queue toDeleteList)
{
    //To be completed

    struct QueueNode *current = toDeleteList->front; //start from dummy

    //free each node of the queue
    while(current != NULL){
      struct QueueNode *temp = current -> next;
      free(current);
      current = temp;
    }

    //free entire Queue
    free(toDeleteList);
}

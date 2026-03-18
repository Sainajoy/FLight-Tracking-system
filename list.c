//
// Created by hp on 22/11/2025.
//


#include "list.h"

List CreateList()
{
    //To be completed

    List l = (List)malloc(sizeof(struct ListRecord));  // *L

    if (l == NULL){
      printf("Out of memory\n");
      return NULL;
    }
    else{
      MakeEmptyList(l);
    }
    return l;
}


void MakeEmptyList(List l)
{
    //To be completed

    struct flightNode *dummy = (struct flightNode *)malloc(sizeof(struct flightNode));

    if (dummy == NULL){
      printf("Out of memory\n");
      return;
    }

    dummy->next = NULL;
    l->head = dummy;
    l->tail = dummy;
    l->length = 0;

}

void InsertList(List l, int pos, Flight* data)
{
    //To be completed

    //in the case pos is greater than the length
    if (pos > l->length + 1){
      pos = l->length + 1;
    }

    struct flightNode *newNode = (struct flightNode *)malloc(sizeof(struct flightNode));
    if (newNode == NULL){
      printf("Out of memory\n");
      return;
    }

   newNode -> flightInformation = data;
   newNode -> next = NULL;

  struct flightNode *current = l->head;  //start from dummy

  // Iterate to the node just before the insertion point
  for (int i = 1; i < pos; i++){
    current = current->next;
  }

   newNode -> next = current -> next;
   current -> next = newNode;

   //In the case the position is the last
   if(newNode -> next == NULL){
     l->tail = newNode;
   }

   l->length++;
}

void InsertToListEnd(List l, Flight* flight){
    //To be completed

    struct flightNode *newNode = (struct flightNode *)malloc(sizeof(struct flightNode));
    if (newNode == NULL){
      printf("Out of memory\n");
      return;
    }

    newNode -> flightInformation = flight;
    newNode -> next = NULL;

    //incase list was empty
    if (l->length == 0){
      l->head -> next = newNode;
      l->tail = newNode;
    }
    else{
      //add it to the tail
      l->tail->next = newNode;   //attach after tail
      l->tail = newNode;         //update tail
    }

  l->length++;

}

void InsertToListHead(List l, Flight* flight){
    //To be completed

    struct flightNode *newNode = (struct flightNode *)malloc(sizeof(struct flightNode));
    if (newNode == NULL){
      printf("Out of memory\n");
      return;
    }

    newNode -> flightInformation = flight;
    newNode->next = l->head->next;
    l->head->next = newNode;

    //In the case list was empty
    if (l->length == 0) {
        l->tail = newNode;
    }

  l->length++;

}

void InsertListOrderedByReadyTime(List l, Flight* newFlight){
    //To be completed

    struct flightNode * newNode= (struct flightNode *)malloc(sizeof(struct flightNode));
    if (newNode == NULL){
      printf("Out of memory\n");
      return ;
    }

    newNode -> flightInformation = newFlight;

    struct flightNode *prev = l->head;   //  dummy
    struct flightNode *current = l->head->next;   //after dummy

     //find correct position to insert newFlight in ascending order
    while (current != NULL && current -> flightInformation -> readyTime <= newFlight->readyTime){
      prev = current;  //move prev forward
      current = current -> next; //move current forward

    }

    //insert in correct position between prev and current
    prev -> next = newNode;
    newNode -> next = current;

    //update tail if inserted at the end
    if(current == NULL){
      l -> tail = newNode;
    }
    l->length ++;

}

Flight* DeleteFirstNode(List l){
    //To be completed

    if (l->head->next == NULL){
      printf("The list is empty\n");
      return NULL;
    }

    struct flightNode *temp = l -> head->next;
    l -> head -> next = temp -> next;     //skip temp
    Flight *removedFlight = temp -> flightInformation;
    free(temp);
    l->length--;

    // In the case this was the only element in the list
    if(l->length == 0){
      l -> tail = l -> head;
    }

    return removedFlight;

}

void DeleteFromList(List l, Flight* v)
{
    //To be completed
  if (l->head->next == NULL) {
    printf("The list is empty\n");
    return;
  }
  struct flightNode *current = l->head; //start from dummy

  //loop stops just before node to be removed
  while (current -> next != NULL && current -> flightInformation != v){
    current = current -> next;
  }

  if (current -> next != NULL) {
    struct flightNode *removeNode = current->next;
    current -> next = current -> next -> next;

    if (current -> next == NULL) {
      l->tail = current;
    }

    free(removeNode);
    l->length--;
  }
  else {
    printf("Flight not found in the list\n");
  }


}

int IsEmptyList(List l)
{
    //To be completed
    return l->length == 0;
}

int ListSize(List l)
{
    //To be completed

    return l->length;
}

Flight* HeadOfList(List l)
{
    //To be completed
    if(IsEmptyList(l)){
      printf("The list is empty\n");
      return NULL;
    }

    Flight* headOfList = l->head->next->flightInformation;
    return headOfList;
}

Flight* TailOfList(List l)
{
    //To be completed
    if(IsEmptyList(l)){
      printf("The list is empty\n");
      return NULL;
    }

    Flight* tailOfList = l->tail->flightInformation;
    return tailOfList;
}

void DisplayList(List l)
{
    //To be completed

    if (IsEmptyList(l)){
      printf("The list is empty\n");
      return;
    }

    //Display content of the list
     struct flightNode *current = l->head->next;
     while (current != NULL){
       printf("Flight type: %c\n", current->flightInformation->flightType);
       printf("ReadyTime: %d\n", current->flightInformation->readyTime);
       printf("ServiceTime: %d\n", current->flightInformation->serviceTime);
       printf("ServiceStartTime: %d\n", current->flightInformation->serviceStartTime);
       printf("RunwayNumber: %d\n", current->flightInformation->runwayNumber);
       printf("Airline: %s\n", current->flightInformation->airline);
       printf("Destination: %s\n", current->flightInformation->destination);
       current = current -> next;

     }
}

void deleteList(List toDeleteList)
{
    //To be completed

    struct flightNode *current = toDeleteList->head;  //start from dummy

    //free each node of the list

    while (current != NULL){
      struct flightNode *next = current -> next;
      free(current);
      current = next; //move current forward
    }

    //free entire list
    free(toDeleteList);
}

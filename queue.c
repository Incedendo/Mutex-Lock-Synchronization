/*
 * C Program to Implement Queue Data Structure using Linked List
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <queue.h>
#include <time.h>
 
/****************************************************
*
*
*   FUNCTION DECLARATION
*
*
*****************************************************/
int frontelement();
void enq(int data);
void deq();
bool isEmpty();
void display();
void create();
void queuesize();

/****************************************************
*
*
*   FUNCTION DEFINITION
*
*
*****************************************************/
/* Create an empty queue. Initialize the front and rear QueueNode Ptr to NULL*/
void queue_create(QueuePtr *anyQueueFront, QueuePtr *anyQueueRear)
{
    *anyQueueFront = NULL;
    *anyQueueRear = NULL;
    //printf("create Queue\n");
}

/* Enqueing QueueNode to the rear pointer */
QueuePtr queue_enq(QueuePtr *anyQueueFront, QueuePtr *anyQueueRear, int taskID, QueueTask operation, int operand)
{
    QueuePtr rear;
    QueuePtr temp;

    /*Initialize the local variables*/
    rear = *anyQueueRear;
    
    //queue is empty
    if (rear == NULL)
    {  
        rear = (QueuePtr)malloc(1*sizeof(QueueNode));
        rear->next = NULL;
        (rear->data).taskID = taskID;
        (rear->data).operation = operation;
        (rear->data).operand = operand;
        *anyQueueRear = rear;
        *anyQueueFront = *anyQueueRear;
        return rear;
    }
    else
    {
        temp = (QueuePtr)malloc(1*sizeof(QueueNode));
        (temp->data).taskID = taskID;
        (temp->data).operation = operation;
        (temp->data).operand = operand;
        temp->next = NULL;
        (*anyQueueRear)->next = temp;
        *anyQueueRear = temp;
        return temp;
    }
}
 
/* Displaying the queue elements */
void queue_display(QueuePtr anyQueueFront, QueuePtr anyQueueRear)
{
    QueuePtr front1 = NULL;
    front1 = anyQueueFront;
    QueuePtr rear1 = NULL;
    rear1 = anyQueueRear;
 
    /* queue is empty if both front and rear nodes are null */
    if ((front1 == NULL) && (rear1 == NULL))
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Display Task ID Queue: \n");
    /* while havent reached the rear node, print and traverse down the queue */
    while (front1 != rear1)
    {
        //printf("TaskID: %ld", (front1->info).taskID);
        queue_printTask(front1);
        front1 = front1->next;
    }
    if (front1 == rear1){
        //printf("%ld", (front1->info).taskID);
        queue_printTask(front1);
    }
        

    printf("\nDone display\n");
}

/* Figure out which Operation to print for each QueueNode */
void queue_printTask(QueuePtr anyQueue){
    QueueTask qt = (anyQueue->data).operation;
    //int opNum = (int) qt;
    printf("Main: Enqueue TaskID: %ld: ", (anyQueue->data).taskID);

    switch (qt){
        case TaskInsert:
            printf("Insert %d\n", (anyQueue->data).operand);
            break;
        case TaskDelete:
            printf("Delete %d\n", (anyQueue->data).operand);
            break;
        case TaskSearch:
            printf("Search %d\n", (anyQueue->data).operand);
            break;
        case TaskPrint:
            printf("Print\n");
            break;
        case TaskNull:
            break;
        default:
            printf("fail\n");
    }
}
 
/* 
 * Dequeing the queue, while doing that, pass in the value for the 
 * taskID, operation and operand by reference in the calling method
 * also free up the QueueNode just dequeued from the queue.
 * return true if succesfully dequeue a node from the queue
 */
bool queue_deq(QueuePtr *anyQueueFront, QueuePtr *anyQueueRear, int *taskID, QueueTask *operation, int *operand)
{
    QueuePtr front1 = *anyQueueFront;
    QueuePtr rear1 = *anyQueueRear;

    /**/
    /* check if front is null */
    if (front1 == NULL)
    {
        printf("\n Error: Trying to display elements from empty queue\n");
        return false;
    }
    else
        if (front1->next != NULL) /* the queue still has next Node */
        {
            *taskID = front1->data.taskID;
            *operation = front1->data.operation;
            *operand = front1->data.operand;
            
            front1 = *anyQueueFront;
            *anyQueueFront = (*anyQueueFront)->next;
            free(front1);
        }
        else /* reach end of the queue*/
        {
            *taskID = front1->data.taskID;
            *operation = front1->data.operation;
            *operand = front1->data.operand;
        
            *anyQueueFront = NULL;
            *anyQueueRear = NULL;
        }
        return true;

    ///////--------------------------------------------------------
    /*    
        QueuePtr temp;
        Bool retval;

        if(!queue_isEmpty(*anyQueue)){
            *taskID = anyQueue->front->TaskInfo.taskID;
            *operation = anyQueue->front->TaskInfo.taskID;
            *operand anyQueue->front->TaskInfo.operand;

            temp = anyQueue->front;
            anyQueue->front = anyQueue->front->next;
            free(temp);

            if(anyQueue->front == NULL)
                anyQueue->rear = NULL;

            retval = true;
        }

        return retval;
    */
    ///////--------------------------------------------------------
}

/* Display if queue is empty or not */
/* Function returns true if queue is Empty, false otherwise */
bool queue_isEmpty(QueuePtr anyQueueFront, QueuePtr anyQueueRear)
{
    // only need to check to make sure front and rear QueueNode is NULL or not
    if ((anyQueueFront == NULL) && (anyQueueRear == NULL)){
        return true;
    }
    else{
        return false;
    }
}

/* Free up all the QueueNode in the Queue */
void queue_destroy(QueuePtr *anyQueueFront, QueuePtr *anyQueueRear){

    int taskID; // long or int?
    QueueTask operation;
    int operand;

    /* while the queue is not empty*/
    while(!queue_isEmpty(*anyQueueFront, *anyQueueRear)){
        /* dequeue one node at a time*/
        queue_deq(anyQueueFront, anyQueueRear, &taskID, &operation, &operand);
    }
}





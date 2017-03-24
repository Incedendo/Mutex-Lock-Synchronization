#ifndef _QUEUE_H_
#define _QUEUE_H_


/****************************************************
*
*
*	DATA STRUCTURES and GLOBAL VARIABLES
*
*
*****************************************************/         

typedef enum task
{
  TaskInsert, TaskDelete, TaskSearch, TaskPrint, TaskNull
} QueueTask;

typedef struct info
{
    long taskID;
    QueueTask operation;
    int operand;
} TaskInfo;

typedef struct queuenode
{
    TaskInfo data;
    struct queuenode *next;
} QueueNode;

typedef QueueNode *QueuePtr;

/****************************************************
*
*
*	FUNCTION PROTOTYPES
*
*
*****************************************************/
void queue_create(QueuePtr *anyQueueFront, QueuePtr *anyQueueRear);
QueuePtr queue_enq(QueuePtr *anyQueueFront, QueuePtr *anyQueueRear, int taskID, QueueTask operation, int operand);
void queue_display(QueuePtr anyQueueFront, QueuePtr anyQueueRear);
bool queue_deq(QueuePtr *anyQueueFront, QueuePtr *anyQueueRear, int *taskID, QueueTask *operation, int *operand);
void queue_printTask(QueuePtr anyQueue);
bool queue_isEmpty(QueuePtr anyQueueFront, QueuePtr anyQueueRear);
void queue_destroy(QueuePtr *anyQueueFront, QueuePtr *anyQueueRear);

#endif
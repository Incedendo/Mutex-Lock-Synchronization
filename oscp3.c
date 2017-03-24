#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "LinkList.h"
#include <pthread.h>
#include "queue.h"

/* Global variables */
const int MAX_VAL = 100;
bool done;
int volatile thread_cond_wait = 0; /* number of threads waiting on condition wait*/
long numthreads;

pthread_mutex_t queue_mutex;
pthread_mutex_t ll_mutex;
pthread_mutex_t cond_mutex;
pthread_cond_t cond_task;

List intList;
QueuePtr queueFront;
QueuePtr queueRear;


/*********************************************************************************
*
*
*	Function Prototypes
*
*
*********************************************************************************/
void *handle_requests_loop(void* rank);
int randomNum();
QueueTask TaskGen();
void generate_task(int numtasks);
bool getTask(long *myrank, int *taskID, QueueTask *operation, int *operand);

/*********************************************************************************
*
*
*
*
*
*********************************************************************************/
int main(int argc, char *argv[]){
	
	int NUM_HANDLER_THREADS = 3;
	int  numtasks;
	long        	i;            /* loop counter          */
	int 		retval;
	pthread_t  	*p_threads;   /* thread's structures   */

	numtasks = 0;
	i = 0;
	retval = EXIT_SUCCESS;

	if(argc != 3){
		printf("Reenter Correct format\n");
		retval = EXIT_FAILURE;
	}
	else{
		numthreads = strtol(argv[1],NULL, 10); 
		numtasks = strtol(argv[2],NULL, 10);

		/*Allocate array for threads*/
		p_threads = malloc(numthreads*sizeof(pthread_t));

		// create the Linked List
		ll_create(&intList);

		// create the Task Queue
		queue_create(&queueFront, &queueRear);

		/*Initialize mutex and condition variables*/
		pthread_mutex_init(&queue_mutex, NULL);
		pthread_mutex_init(&ll_mutex, NULL);
		pthread_mutex_init(&cond_mutex, NULL);
		pthread_cond_init(&cond_task, NULL);

		/* create the request-handling threads */
	    for (i=0; i<numthreads; i++) {
	        pthread_create(&p_threads[i], NULL, handle_requests_loop, (void*)i);
	    }
	 
	 	/* Generate task for queue */
	 	srand((unsigned)time(NULL));  //this function generate a new seed everytime rand() is called to ensure true randomness
	   	generate_task(numtasks);

	   	//queue_display(queueFront, queueRear);

	   	/* print the final list*/
	   	printf("\n\nPrint the final list\n");
	   	ll_printall(intList);
	
		/* Wait for all the threads to complete*/
	    for (i=0; i<NUM_HANDLER_THREADS; i++) {
	    	pthread_join(p_threads[i], NULL);
	    }

	    /* Free the linked list*/
	    ll_destroy(&intList);

	    /* Free all the QueueNode*/
	    queue_destroy(&queueFront, &queueRear);

	    /* destroy mutexes and condition variables*/
	    pthread_mutex_destroy(&queue_mutex);
	    pthread_mutex_destroy(&ll_mutex);
	    pthread_mutex_destroy(&cond_mutex);
	    pthread_cond_destroy(&cond_task);

	    /*free thread array*/
	    free(p_threads);
	}

	return retval;
}

/*********************************************************************************
*
*	The thread calls this function to get a task from the queue
*
*	and execute the task accordingly
*
*********************************************************************************/
void *handle_requests_loop(void* rank){
	
	long myrank;
	int taskID; // long or int?
	QueueTask operation;
	int operand;
	bool success;

	/*Initialize local vars*/
	myrank = (long) rank;
	taskID = 0;
	operation = TaskNull;
	operand = 0;
	success = false;

	/* while you can get a task ....*/ 
	while(getTask(&myrank, &taskID, &operation, &operand)){

		/* lock the list and switch based on operation */
		pthread_mutex_lock(&ll_mutex);
			
		if(operation == TaskInsert){
			if(ll_insert(&intList,operand)){
				printf("[Thread %ld] taskID %d Insert: %d: INSERTED\n", myrank, taskID, operand);
			}
			else{
				printf("[Thread %ld] taskID %d Insert: %d: NOT INSERTED\n", myrank, taskID, operand);
			}
		}
		else if(operation == TaskDelete){
			if(ll_delete(&intList,operand)){
				printf("[Thread %ld] taskID %d Delete: %d: DELETED\n", myrank, taskID, operand);
			}
			else{
				printf("[Thread %ld] taskID %d Delete: %d: NOT DELETED\n", myrank, taskID, operand);
			}
		}
		else if(operation == TaskSearch){
			if(ll_search(intList, operand)){
				printf("[Thread %ld] taskID %d Search: %d: FOUND\n", myrank, taskID, operand);
			}
			else{
				printf("[Thread %ld] taskID %d Search: %d: NOT FOUND\n", myrank, taskID, operand);
			}
		}
		else if(operation == TaskPrint){
			printf("[Thread %ld] taskID %d ", myrank, taskID);
			ll_printall(intList);
		}
		else if(operation == TaskNull){
			printf("NO TASK\n");
		}
		
		/* Unlock the list */
		pthread_mutex_unlock(&ll_mutex);

	}

	/*return to calling function*/
	return NULL;
}

/*********************************************************************************
*
*	Generate a random number from 1 - MAXVAL
*	return that random number
*
*********************************************************************************/
int randomNum(){
	int randomnumber = rand() % MAX_VAL + 1;
	//printf("Random num: %d\n", randomnumber);
    return randomnumber;
}

/*********************************************************************************
*
*	Generate a random Task out of 4 given tasks
*
*********************************************************************************/
QueueTask TaskGen(){
	QueueTask qt;
	int randomnumber = rand() % 4 + 1;
	//printf("Task gen %d\n", randomnumber);
	switch(randomnumber){
		case 1:
			qt = TaskInsert;
			break;
		case 2:
			qt = TaskDelete;
			break;
		case 3:
			qt = TaskSearch;
			break;
		case 4:
			qt = TaskPrint;
			break;
		default:
			qt = TaskNull;
	}
    return qt;
}

/*********************************************************************************
*
*	MAIN THREAD call generate_task to generate (numtasks) amount of task
*
*	A random task generator() function called TaskGen() will randomize a task
*
*********************************************************************************/
void generate_task(int numtasks){
	/*local variable*/
	int taskID;
	QueueTask operation;
	int operand;
	int ii = 0;

	taskID = 0;

	/*for loop to create tasks */
	for(ii = 0; ii < numtasks; ii++){
		//lock the queue mutex
		pthread_mutex_lock(&queue_mutex);
		
			operand = randomNum();
			
			QueuePtr newInsertion = queue_enq(&queueFront, &queueRear, ii , TaskGen(), operand);

			/* output to stdout the message what task was enqueued */
			queue_printTask(newInsertion);

		pthread_mutex_unlock(&queue_mutex);

		/* If the number of threads waiting on cond_wait > 0 then signal cond_task*/
		if(thread_cond_wait > 0){

			pthread_cond_signal(&cond_task); 

		}
	}

	/* all tasks enqueued, keep signaling until thread_cond_wait == 0 */
	while (!queue_isEmpty(queueFront, queueRear) ){

		if (thread_cond_wait > 0){

			pthread_cond_signal(&cond_task);

		}

	}

	/* Now the queue is empty, wait for threads to terminate, then set DONE = TRUE*/
	while(thread_cond_wait < numthreads);

	done = true;

	/* Broadcast to all threads waiting on cond_task */
	if ( pthread_cond_broadcast(&cond_task) != 0) //success
	{
		printf("Cannot BROADCAST to ALL threads\n");
	}
}

/*********************************************************************************
*
*		Get a task from the Task Queue 
*
*		Fill the taskID, operation and operand with value from the dequeued NODE
*
*********************************************************************************/
bool getTask(long *myrank, int *taskID, QueueTask *operation, int *operand){
	/* local variables */
	bool success;
	bool retval;

	/*Initialize local variables*/
	success = false;
	retval = true;

	/* do forever: 
		A thread enter this function then wait for the main to signal,
		If main signals, a random thread wakes up
		First, check if DONE == TRUE
		Then, check if queue is empty then grab a task if queue is not empty  
		then return.
	*/
	while(1){
		/* use mutex to lock wait count*/
		pthread_mutex_lock(&cond_mutex);

		/* Update number for threads waiting on condition wait */
		thread_cond_wait++;

		/* mutex is now locked - wait on the condition variable.             */
		/* During the execution of pthread_cond_wait, the mutex is unlocked. */
		/* do a thread cond wait until on cond_task and cond_mutex until == 0 */
		while(pthread_cond_wait(&cond_task, &cond_mutex) != 0);

		thread_cond_wait--;

		/* Unlock mutex on condition wait */
		pthread_mutex_unlock(&cond_mutex);

		/* [check if queue is empty in GENERATETASK() ] set DONE = TRUE */
		if(done == true){
			return false;
		}

	/* if task queue is NOT empty, lock the queue and get the task */
		if(!queue_isEmpty(queueFront, queueRear) ){

			pthread_mutex_lock(&queue_mutex);

			//get a task 
			success = queue_deq(&queueFront, &queueRear, taskID, operation, operand);

			pthread_mutex_unlock(&queue_mutex);

		}

		// If successfully deque a task
		if(success){
			return true;
		}else{
			printf("task queue is empty\n");
			//return false;
		}

	}

	return(true);
}
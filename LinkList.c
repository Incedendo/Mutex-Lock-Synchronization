#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linklist.h"

/****************************************************
*
*	Initialize the head node of the linked list
*
*****************************************************/
void ll_create(List *anyList){
	*anyList = NULL;
}

/****************************************************
*
*	Check if the linked list is empty
*	return: true if linked list is empty
*		    false if not
*
*****************************************************/
bool ll_isEmpty(List anyList){
	return (anyList == NULL ? true : false);
}

/****************************************************
*
*	insert a value into the linked list in increading order
*	retun: true if success
*		   false if fail to insert
*
*
*****************************************************/
bool ll_insert(List *anyList, int num){

	List curr = *anyList;
	List prev = NULL;
	List temp = NULL;

	while((curr != NULL) && (curr->data < num)){
		//printf("in While: curr = %p ,curr->data = %d, insert num = %d\n", curr, curr->data, num);
		prev = curr;
		curr = curr->next;
		//printf("last while\n");
	}

	if( (temp = (List) malloc(sizeof(ListNode))) == 0){
		printf("linklist.c: ll_insert: Cannot create struct node");
		return false;
	}
	temp->data = num;
	temp->next = NULL;

	//insert new front node
	if(prev == NULL){
		*anyList = temp;
		temp->next = curr;
		return true;
	}else{
		//Case insert in the Middle or End
		prev->next = temp;
		temp->next = curr;
		return true;
	}
}

/****************************************************
*
*	delete a particular value from the link list
*	retun: true if success
*		   false if value does not exist
*
*****************************************************/
bool ll_delete(List *anyList, int num){
	List curr = NULL;
	List prev = NULL;

	curr = *anyList;
	prev = NULL;
	while(!ll_isEmpty(curr) && curr->data != num){
		prev = curr;
		curr = curr->next;
	}

	if(ll_isEmpty(curr)){
		return false;
	}else{
		if(prev == NULL){
			*anyList = (*anyList)->next; 
		}else{
			prev->next = curr->next;
		}
		free(curr);
		return true;
	}
}

/****************************************************
*
*
*	print all the element in the linked list
*
*
*****************************************************/
void ll_printall(List anyList){
	List curr = NULL;
	curr = anyList;

	printf("Print ALl: Node value: ");
	while(!ll_isEmpty(curr)){
		printf("%d, ", curr->data);
		curr = curr->next;
	}
	printf("Null\n");
}

/****************************************************
*
*	search a particular data value in the linked list
*	retun: true if found the value
*		   false if value does not exist
*
*****************************************************/
bool ll_search(List anyList, int data){
	List curr = NULL;
	curr = anyList;

	while(!ll_isEmpty(curr)){
		if(curr->data == data){
			//printf("Found %d\n", data);
			return true;
		}
		curr = curr->next;
	}
	//printf("Element %d is not in the list\n", data);
	return false;
}

/****************************************************
*
*
*	Free up all the list node in the linked list
*
*
*****************************************************/
void ll_destroy(List *anyList){
	List curr = NULL;
	List temp = NULL;
	curr = *anyList;

	while(!ll_isEmpty(curr)){
		temp = curr;
		curr = curr->next;
		free(temp);
	}

}
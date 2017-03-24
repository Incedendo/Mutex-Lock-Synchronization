#ifndef _LinkList_h_
#define _LinkList_h_

/****************************************************
*
*
*	DATA STRUCTURES
*
*
*****************************************************/
typedef struct ll_node{
	int data;
	struct ll_node *next;
} ListNode;

typedef ListNode *List;

/****************************************************
*
*
*	FUNCTION PROTOTYPES
*
*
*****************************************************/
void ll_create(List *anyList);
bool ll_insert(List *anyList,int num);
bool ll_delete(List *anyList, int num);
void ll_printall(List anyList);
bool ll_isEmpty(List anyList);
bool ll_search(List anyList, int data);
void ll_destroy(List *anyList);

#endif
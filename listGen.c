/**************/
/*   list.c   */
/**************/



#include "listGen.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL L_init(LIST* pList)
{
	if (pList == NULL) return False;	// no list to initialize

	pList->head.next = NULL;
	return True;
}


/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if (!pNode) return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
BOOL L_delete(NODE* pNode, void (*freeFunc)(void*))
{
	NODE* tmp;

	if (!pNode || !(tmp = pNode->next)) return False;

	pNode->next = tmp->next;
	if (freeFunc != NULL)
		freeFunc(tmp->key);
	free(tmp);
	return True;
}


/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
const NODE* L_find(const NODE* pNode, DATA value, int(*compare)(const void*, const void*))
{
	const NODE* temp = NULL;
	if (!pNode) return NULL;
	while (pNode != NULL)
	{
		if (compare(pNode->key, value) == 0)
		{
			temp = pNode;
			break;
		}
		pNode = pNode->next;
	}

	return temp;


}


////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
BOOL L_free(LIST* pList, void (*freeFunc)(void*))
{
	NODE* tmp;

	if (!pList) return False;
	tmp = &(pList->head);
	BOOL res = True;
	while (res)
	{
		res = L_delete(tmp, freeFunc);
	}

	return True;
}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
int L_print(const LIST* pList, void(*print)(const void*))
{
	NODE* tmp;
	int		c = 0;

	if (!pList) return 0;

	printf("\n");
	for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
		print(tmp->key);
	printf("\n");
	return c;
}


/////////////////////////////////////////////////////////////////
// InsertSorted
// Aim:		add new node in a sorted way
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insertSorted(LIST* pList, DATA Value, int(*compare)(const void*, const void*)) {
	if (pList == NULL) {
		return NULL;
	}
	NODE* ptr = &pList->head;
	if (ptr == NULL) {
		return NULL;
	}
	NODE* nextPtr = ptr->next;

	while (nextPtr != NULL) {
		if (compare(nextPtr->key, Value) > 0)
		{
			break;
		}
		ptr = nextPtr;
		nextPtr = nextPtr->next;
	}
	return L_insert(ptr, Value);
}





//////////////////////////////////////////////
// L_count
// Aim:		count the number of elements in the list
// Input:	pointer to the list structure
// Output:	number of elements in the list
//////////////////////////////////////////////
int L_count(const LIST* pList) {
	if (pList == NULL) {
		return 0;
	}
	NODE* ptr = pList->head.next;
	int count = 0;
	while (ptr != NULL) {
		count++;
		ptr = ptr->next;
	}

	return count;
}


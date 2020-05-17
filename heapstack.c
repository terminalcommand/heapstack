#include <stdio.h>
#include <stdarg.h>
#include "clinked.c"

#define ENDLIST (const char *)NULL

void swapnodes(struct node* c1, struct node* c2) {
	void *t = c1->value;
	c1->value = c2->value;
	c2->value = t;
}

void movetoend(struct node* l) {
	for(;;) {
		if (l->next == NULL) break;
		swapnodes(l, l->next);
		l=l->next;		
	}
}

int countlist(struct node* l) {
	int c = 1;
	for (struct node* i=l;i->next!=NULL;i=i->next) {
		c++;
	}
	return c;
}

struct node* getlast(struct node *cursor) {
	for (;;) {
		if (cursor->next==NULL) break;
		else cursor = cursor->next;
	}
	return cursor;
}

void reverselist(struct node* l) {
	int c = countlist(l);
	struct node* j = getlast(l);
	for (int i=1; i<=c; i++) {
		if (j->prev == NULL) {
			break;
		}
		movetoend(j->prev);
		j=j->prev;
	}
}

struct node* push(struct node* list, char* val) {
	if (list==NULL) {
		struct node *head = makenode(NULL, NULL, val);
		return head;
	} else {
		struct node* t = makenode(NULL, list, val);
		list->prev=t;
		list=t;
		return list;
	}
}

struct node* pop(struct node *list) {

	struct node* next = list->next;
	next->prev = NULL;
	freeitem(list);
	return next;
}

struct node* newlist(char *firstarg, ...) {
	va_list args;
	va_start(args, firstarg);
	struct node* list = processlist(1,&firstarg);
	
	char* nextarg = va_arg(args, char*);

	for (;;) {
		if (nextarg==NULL) break;
		else {
			list=push(list,nextarg);	
			nextarg=va_arg(args, char*);
		}
	}
	va_end(args);
	reverselist(list);
	return list;
}

char *getvalue(struct node *list) {
	return list->value;
}

 
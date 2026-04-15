#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pthread.h"
#include "linked_list.h"

// initialize head
node *head = NULL;

// sequence counter
int seq_ctr = 0;
/* // current node
node *cur = NULL;
// line counter
int line_ctr = 0; */
//Read the file on a line by line basis
char* read_line(char* fname, int line_no) 
{
	FILE *fp = fopen(fname, "r");
	if (!fp) {
		return NULL;
	}
	char buffer[LINE_SIZE];
	int current = 0;

	while(fgets(buffer, LINE_SIZE, fp)) {
		if (current == line_no) {
			fclose(fp);
			char *line = malloc(strlen(buffer) + 1);
			strcpy(line, buffer);
			return line;
		}
		current++;
	}
	fclose(fp);
	return NULL;
} 

//traverse the linked list
void traversal(node *head)
{
	while(head != NULL) {
		printf("%d, %d, %s", head->seq_no, head->line_no, head->content);
		head = head->next;
	}
}

// insert the node into the linked list
void insert(node **phead, node *newnode)
{
	if (*phead == NULL || newnode->line_no < (*phead)->line_no) {
		newnode->next = *phead;
		*phead = newnode;
		return;
	}
	
	node *curr = *phead;
	while (curr->next && curr->next->line_no < newnode->line_no) {
		curr = curr->next;
	}

	newnode->next = curr->next;
	curr->next = newnode;

	/* old code
	while(phead != NULL) {
		if(phead->next == NULL) {
			phead->next = newnode;
		}
		phead = phead->next;
	} */
}

//create a new node structure
node* create_node(int line_no, char *line)
{
	node *newnode = malloc(sizeof(node));
	newnode->line_no = line_no;
	newnode->content = line;
	newnode->next = NULL;
	newnode->seq_no = -1;
	return newnode;
}
